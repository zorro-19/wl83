#include "update.h"
#include "update_loader_download.h"
#include "asm/crc16.h"
#include "asm/wdt.h"
#include "os/os_api.h"
#include "app_config.h"
#include "cpu.h"
#include "syscfg_id.h"
#include "btcontroller_modules.h"
#include "system/includes.h"
#include "uart_update.h"
#include "ota_impl.h"
#include "btstack/avctp_user.h"
#include "asm/power_interface.h"

#define LOG_TAG "[APP-UPDATE]"
#define LOG_INFO_ENABLE
#define LOG_ERROR_ENABLE
#include "system/debug.h"

#define LOADER_NAME		"LOADER.BIN"
#define DEVICE_UPDATE_KEY_ERR  BIT(30)
#define DEVICE_FIRST_START     BIT(31)

extern void vm_reverse_addr_size_get(u32 *addr, u32 *len);
extern void update_module_init(void (*cbk)(update_mode_info_t *, u32, void *));
extern void hwi_all_close(void);
extern void wifi_det_close();

extern u8 get_ota_status();
extern int get_nor_update_param(void *buf);
extern void sys_auto_sniff_controle(u8 enable, u8 *addr);

extern const int support_vm_data_keep;
extern const int support_norflash_update_en;
extern const int support_norflash_update_en;
const char updata_file_name[] = "/*.UFW";
static u32 g_updata_flag = 0;
static volatile u8 ota_status = 0;
static succ_report_t succ_report;

bool vm_need_recover(void)
{
    return ((g_updata_flag & 0xffff) == UPDATA_SUCC) ? true : false;
}

u16 update_result_get(void)
{
    u16 ret = UPDATA_NON;

    if (!UPDATE_SUPPORT_DEV_IS_NULL()) {
        UPDATA_PARM *p = UPDATA_FLAG_ADDR;
        u16 crc_cal;
        crc_cal = CRC16(((u8 *)p) + 2, sizeof(UPDATA_PARM) - 2);	//2 : crc_val
        if (crc_cal && crc_cal == p->parm_crc) {
            ret =  p->parm_result;
        }
        g_updata_flag = ret;
        g_updata_flag |= ((u32)(p->magic)) << 16;

        memset(p, 0x00, sizeof(UPDATA_PARM));
    }

    return ret;
}

void update_result_set(u16 result)
{
    if (!UPDATE_SUPPORT_DEV_IS_NULL()) {
        UPDATA_PARM *p = UPDATA_FLAG_ADDR;

        /* memset(p, 0x00, sizeof(UPDATA_PARM)); */
        p->parm_result = result;
        p->parm_crc = CRC16(((u8 *)p) + 2, sizeof(UPDATA_PARM) - 2);
    }
}

bool update_success_boot_check(void)
{
    if (!UPDATE_SUPPORT_DEV_IS_NULL()) {
        u16 result = g_updata_flag & 0xffff;
        u16 up_tpye = g_updata_flag >> 16;
        if ((UPDATA_SUCC == result) && ((SD0_UPDATA == up_tpye) || (SD1_UPDATA == up_tpye) || (USB_UPDATA == up_tpye))) {
            printf("The upgrade is successful, no need to upgrade again!");
            return true;
        }
    }
    return false;
}

bool device_is_first_start(void)
{
    log_info("g_updata_flag=0x%x\n", g_updata_flag);
    if ((g_updata_flag & DEVICE_FIRST_START) || (g_updata_flag & DEVICE_UPDATE_KEY_ERR) || (g_updata_flag == UPDATA_SUCC)) {
        puts("\n=================device_is_first_start=========================\n");
        return true;
    }
    return false;
}

void led_update_start(void)
{
}

void led_update_finish(void)
{
}

static inline void dev_update_close_ui()
{

}

int update_result_deal(void)
{
#ifdef CONFIG_FPGA_ENABLE
    return 0;
#endif

    u16 result = 0;
    result = (g_updata_flag & 0xffff);
    log_info("<--------update_result_deal=0x%x %x--------->\n", result, g_updata_flag >> 16);

    if (result == UPDATA_NON || 0 == result) {
        return 0;
    }
    if (result == UPDATA_SUCC) {
    }

    while (1) {
        wdt_clear();
        //注:关机要慎重,要设置开机键
        //enter_sys_soft_poweroff();
    }

    return 1;
}

void clr_update_ram_info(void)
{
    UPDATA_PARM *p = UPDATA_FLAG_ADDR;
    memset(p, 0x00, sizeof(UPDATA_PARM));
}

void update_close_hw(void *filter_name)
{
    const struct update_target *p;
    list_for_each_update_target(p) {
        if (memcmp(filter_name, p->name, strlen(filter_name)) != 0) {
            printf("close Hw Name : %s\n", p->name);
            p->driver_close();
        }
    }
}

static void update_before_jump_common_handle(UPDATA_TYPE up_type)
{
    dev_update_close_ui();

    local_irq_disable();
    hwi_all_close();

#ifdef CONFIG_SUPPORT_WIFI_DETECT
    wifi_det_close();
#endif
    /*跳转的时候遇到死掉的情况很可能是硬件模块没关导致，加上保护可以判断哪个异常，保护的地址根据不同SDK而定*/
    /* u8 inv = 0; */
    /* mpu_set(1, (u32)&test_pro_addr, (u32)test_pro_addr, inv, "0r", DBG_FM); */
}

//ota.bin 放到exflash升级的方式，parm_priv存放了norflash的参数，对应实际升级方式的参数需要放在norflash参数之后
void update_param_priv_fill(UPDATA_PARM *p, void *priv, u16 priv_len)
{
    int parm_offset = 0;
    if (support_norflash_update_en) {
        parm_offset = get_nor_update_param(p->parm_priv);          //如果loader放在外挂norflash,parm_priv前面放norflash参数，后面才是升级类型本身的参数
    }
    memcpy(p->parm_priv + parm_offset, priv, priv_len);
}

//fill common content \ private content \ crc16
static void update_param_content_fill(int type, UPDATA_PARM *p, void (*priv_param_fill_hdl)(UPDATA_PARM *P))
{
    if (support_norflash_update_en) {
        p->parm_type = NORFLASH_UPDATA;                                //uboot通过该标识从外挂flash读取ota.bin
        *((u16 *)((u8 *)p + sizeof(UPDATA_PARM) + 32)) = (u16)type;    //将实际的升级类型保存到UPDATA_PARM后
    } else {
        p->parm_type = (u16)type;
    }

    p->parm_result = (u16)UPDATA_READY;
    p->magic = UPDATE_PARAM_MAGIC;
    p->ota_addr = succ_report.loader_saddr;

    //支持loader放到外挂flash里ota_addr为0
    if (0 == p->ota_addr && !support_norflash_update_en) {
        log_error("ota addr err\n");
        return;
    }

    if (priv_param_fill_hdl) {
        priv_param_fill_hdl(p);
    }

    p->parm_crc = CRC16(((u8 *)p) + 2, sizeof(UPDATA_PARM) - 2);	//2 : crc_val
}

static void update_param_ram_set(u8 *buf, u16 len)
{
    u8 *update_ram = UPDATA_FLAG_ADDR;
    memcpy(update_ram, (u8 *)buf, len);
}

void update_mode_api_v2(UPDATA_TYPE type, void (*priv_param_fill_hdl)(UPDATA_PARM *p), void (*priv_update_jump_handle)(int type))
{
    u16 update_param_len = sizeof(UPDATA_PARM) + UPDATE_PRIV_PARAM_LEN;

    UPDATA_PARM *p = malloc(update_param_len);

    if (p) {
        memset((u8 *)p, 0x00, sizeof(UPDATA_PARM));
#if 0 //兼容新的ota loader
        if (support_vm_data_keep) {//单备份升级，parm_priv参数存vm_addr和vm_len到ota.bin的，传给net_ota.bin网络升级使用
            u32 vm_addr = 0, vm_len = 0;
            vm_reverse_addr_size_get(&vm_addr, &vm_len);
            memcpy(p->parm_priv, &vm_addr, sizeof(vm_addr));
            memcpy(p->parm_priv + sizeof(vm_addr), &vm_len, sizeof(vm_len));
        }
#endif
        update_param_content_fill(type, p, priv_param_fill_hdl);

        if (succ_report.update_param_write_hdl) {
            succ_report.update_param_write_hdl(succ_report.priv_param, (u8 *)p, update_param_len);
        }

        //此处不能关闭硬件，不能关注中断 ，由应用层自行处理
        //update_before_jump_common_handle(type);

        update_param_ram_set((u8 *)p, update_param_len);

        if (priv_update_jump_handle) {
            priv_update_jump_handle(type);
        }

        free(p);
    } else {
        ASSERT(p, "malloc update param err \n");
    }
}

int update_check_sniff_en(void)
{
    if (!UPDATE_SUPPORT_DEV_IS_NULL()) {
        if (get_ota_status()) {
            log_info("ota ing...");
            return 0;
        } else {
            return 1;
        }
    }
    return 1;
}

void set_ota_status(u8 stu)
{
    ota_status = stu;
}

u8 get_ota_status(void)
{
    return ota_status;
}

static u8 ota_idle_query(void)
{
    return !ota_status;
}

//防止升级过程进入powerdown
REGISTER_LP_TARGET(ota_lp_target) = {
    .name = "ota",
    .is_idle = ota_idle_query,
};

extern const int support_dual_bank_update_en;

static void update_init_common_handle(int type)
{
    ota_status = 1;
    if (UPDATE_DUAL_BANK_IS_SUPPORT()) {
#if TCFG_AUTO_SHUT_DOWN_TIME
        sys_auto_shut_down_disable();
#endif
    }
}

static void update_exit_common_handle(int type, void *priv)
{
#if TCFG_AUTO_SHUT_DOWN_TIME
    sys_auto_shut_down_enable();
#endif

    ota_status = 0;
}

static void update_common_state_cbk(update_mode_info_t *info, u32 state, void *priv)
{
    int type = info->type;

    log_info("type:%x state:%x code:%x\n", type, state, priv);

    switch (state) {
    case UPDATE_CH_INIT:
        memset((u8 *)&succ_report, 0x00, sizeof(succ_report_t));
        update_init_common_handle(info->type);
        break;

    case UPDATE_CH_SUCESS_REPORT:
        log_info("succ report stored\n");
        memcpy((u8 *)&succ_report, (u8 *)priv, sizeof(succ_report_t));
        break;
    }

    if (info->state_cbk) {
        info->state_cbk(type, state, priv);
    }

    switch (state) {
    case UPDATE_CH_EXIT:
        update_exit_common_handle(info->type, priv);
        break;
    }
}

static int app_update_init(void)
{
    update_module_init(update_common_state_cbk);
    return 0;
}
__initcall(app_update_init);

void update_start_exit_sniff(void)
{
#ifdef CONFIG_BT_ENABLE
    bt_cmd_prepare(USER_CTRL_ALL_SNIFF_EXIT, 0, NULL);
    sys_auto_sniff_controle(0, NULL);
#endif
}

