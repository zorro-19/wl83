/****************************************************************************/
/* camx_plat.c
 *
 ****************************************************************************/

/****************************************************************************/
/* Included Files                                                           */
/****************************************************************************/
/* #include "asm/system_reset_reason.h" */
#include "camx.h"

/****************************************************************************/
/* Trace Definitions                                                        */
/****************************************************************************/

#define EVOS_LOG_COMPILE_LEVEL EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_RUN_LEVEL     EVOS_LOG_LEVEL_DEBUG
#define EVOS_LOG_DOMAIN        "plat"
#include "xc_log.h"
/****************************************************************************/
/* Pre-processor Definitions                                                */
/****************************************************************************/

/****************************************************************************/
/* Private Types                                                            */
/****************************************************************************/

/****************************************************************************/
/* Private Function Prototypes                                              */
/****************************************************************************/

/****************************************************************************/
/* Private Data                                                             */
/****************************************************************************/

/****************************************************************************/
/* Public Data                                                              */
/****************************************************************************/

/****************************************************************************/
/* Private Functions                                                        */
/****************************************************************************/

/****************************************************************************/
/* Public Functions                                                         */
/****************************************************************************/




void reboot_async(int sleep_ms);
bool camx_plat_network_is_started(void)
{
    u8 state = wifi_get_sta_connect_state();
    if (WIFI_STA_NETWORK_STACK_DHCP_SUCC == state) {
        T_I("wifi sta is connected....");
        return (true);
    } else {
        return (false);
    }
}

void camx_plat_get_mac(uint8_t macaddr[6])
{
    u8 mac_t[6];

    wifi_get_mac(mac_t);

    memcpy(macaddr, mac_t, sizeof(mac_t));
}

void camx_plat_reboot(uint8_t flag)
{
    system_reset(1);
}

void camx_plat_reset_reason(void)
{

    reset_source_value_dump();
    /* T_I("camx reset reason:%d, %s", reason, name); */

    // setup info
    //
    T_I("CAMX WL83(AC792N) CHIP_ID: 0x%x", JL_SYSTEM->CHIP_ID);
    /* T_I("CAMX WL83(AC792N) CHIP_ID: 0x%x", JL_INTEST->CHIP_ID); */
    extern u32 SDRAM_SIZE, RAM0_SIZE, CACHE_RAM_SIZE, text_size, data_size,
           bss_size, ram0_bss_size, ram0_data_size, cache_ram_bss_size,
           cache_ram_data_size, HEAP_END, HEAP_BEGIN;
    T_I("sys_clk = %d,sdram_clk = %d,hsb_clk = %d,lsb_clk = %d, sfc_clk = %d",
        clk_get("sys"),
        clk_get("sdram"),
        clk_get("hsb"),
        clk_get("timer"),
        /* clk_get("hsb") / (JL_SFC->BAUD + 1)); */
        clk_get("sfc"));
    T_I("CODE+CONST SIZE = %d", (u32)&text_size);
    T_I("SDRAM_SIZE = %d, DATA_SIZE = %d,BSS_SIZE = %d,REMAIN_SIZE = %d",
        (u32)&SDRAM_SIZE,
        (u32)&data_size,
        (u32)&bss_size,
        (u32)&SDRAM_SIZE - (u32)&data_size - (u32)&bss_size);
    T_I("RAM_SIZE = %d,DATA_SIZE = %d,BSS_SIZE = %d,REMAIN_SIZE = %d",
        (u32)&RAM0_SIZE,
        (u32)&ram0_data_size,
        (u32)&ram0_bss_size,
        (u32)&RAM0_SIZE - (u32)&ram0_data_size - (u32)&ram0_bss_size);
    T_I("CACHE_RAM_SIZE = %d,DATA_SIZE = %d, BSS_SIZE = %d,REMAIN_SIZE = %d",
        (u32)&CACHE_RAM_SIZE,
        (u32)&cache_ram_data_size,
        (u32)&cache_ram_bss_size,
        (u32)&CACHE_RAM_SIZE - (u32)&cache_ram_data_size -
        (u32)&cache_ram_bss_size);
    T_I("HEAP_SIZE = %d", (u32)&HEAP_END - (u32)&HEAP_BEGIN);
}

#if 0
void camx_plat_reset_reason(void)
{
    int         reason = system_reset_reason_get();
    const char *name   = NULL;

    if (reason & SYS_RST_12V) {
        name = "SYS_RST_12V";
    } else if (reason & SYS_RST_WDT) {
        name = "SYS_RST_WDT";
    } else if (reason & SYS_RST_VCM) {
        name = "SYS_RST_VCM";
    } else if (reason & SYS_RST_SOFT) {
        name = "SYS_RST_SOFT";
    } else if (reason & SYS_RST_ALM_WKUP) {
        name = "SYS_RST_ALM_WKUP";
    } else if (reason & SYS_RST_PORT_WKUP) {
        name = "SYS_RST_PORT_WKUP";
    } else if (reason & SYS_RST_LONG_PRESS) {
        name = "SYS_RST_LONG_PRESS";
    } else if (reason & SYS_RST_VDDIO_PWR_ON) {
        name = "SYS_RST_VDDIO_PWR_ON";
    } else if (reason & SYS_RST_VDDIO_LOW_PWR) {
        name = "SYS_RST_VDDIO_LOW_PWR";
    } else {
        name = "unkown";
    }
    T_I("camx reset reason:%d, %s", reason, name);

    // setup info
    T_I("CAMX WL83(AC792N) CHIP_ID: 0x%x", JL_SYSTEM->CHIP_ID);
    extern u32 SDRAM_SIZE, RAM0_SIZE, CACHE_RAM_SIZE, text_size, data_size,
           bss_size, ram0_bss_size, ram0_data_size, cache_ram_bss_size,
           cache_ram_data_size, HEAP_END, HEAP_BEGIN;
    T_I("sys_clk = %d,sdram_clk = %d,hsb_clk = %d,lsb_clk = %d, sfc_clk = %d",
        clk_get("sys"),
        clk_get("sdram"),
        clk_get("hsb"),
        clk_get("timer"),
        /* clk_get("hsb") / (JL_SFC->BAUD + 1)); */
        clk_get("sfc"));
    T_I("CODE+CONST SIZE = %d", (u32)&text_size);
    T_I("SDRAM_SIZE = %d, DATA_SIZE = %d,BSS_SIZE = %d,REMAIN_SIZE = %d",
        (u32)&SDRAM_SIZE,
        (u32)&data_size,
        (u32)&bss_size,
        (u32)&SDRAM_SIZE - (u32)&data_size - (u32)&bss_size);
    T_I("RAM_SIZE = %d,DATA_SIZE = %d,BSS_SIZE = %d,REMAIN_SIZE = %d",
        (u32)&RAM0_SIZE,
        (u32)&ram0_data_size,
        (u32)&ram0_bss_size,
        (u32)&RAM0_SIZE - (u32)&ram0_data_size - (u32)&ram0_bss_size);
    T_I("CACHE_RAM_SIZE = %d,DATA_SIZE = %d, BSS_SIZE = %d,REMAIN_SIZE = %d",
        (u32)&CACHE_RAM_SIZE,
        (u32)&cache_ram_data_size,
        (u32)&cache_ram_bss_size,
        (u32)&CACHE_RAM_SIZE - (u32)&cache_ram_data_size -
        (u32)&cache_ram_bss_size);
    T_I("HEAP_SIZE = %d", (u32)&HEAP_END - (u32)&HEAP_BEGIN);
}
#endif

int camx_plat_reset(uint32_t flag)
{
    T_I("`camx_reset` called, flag(0x%x)", flag);
    (void)flag;

    void **user_video_handle = get_user_video_handle();
    if (*user_video_handle) {
        user_video_rec_close(*user_video_handle);
        *user_video_handle = NULL;

    }

    /* motion_detection_uninit(); */

    dev_cs_video_end();


    struct intent it;
    init_intent(&it);
    it.name	= "video_rec";//APP状态机在：video_rec.c
    it.action = ACTION_BACK;
    start_app(&it);



    /* do net cfg */

    /* led_status_speed(5); */
    /* wifi_enter_ap_mode("", ""); */

    struct wifi_stored_sta_info wifi_stored_sta_info[32];
    u8 ssid_stored_cnt;
    ssid_stored_cnt = wifi_get_stored_sta_info(wifi_stored_sta_info);
    for (int i = 0; i < ssid_stored_cnt; i++) {
        printf("1:wifi_get_stored_sta_info[%d]= %s \r\n", i, wifi_stored_sta_info[i].ssid);

        wifi_del_stored_sta_info(wifi_stored_sta_info[i].ssid); //删除

    }
    ssid_stored_cnt = wifi_get_stored_sta_info(wifi_stored_sta_info);
    for (int i = 0; i < ssid_stored_cnt; i++) {
        printf("2:wifi_get_stored_sta_info[%d]= %s \r\n", i, wifi_stored_sta_info[i].ssid);
    }

    reboot_async(1000);

    return 0;
}

void _reboot_work(void *arg)
{
    int sleep_ms = arg;
    if (sleep_ms > 15000 || sleep_ms < 0) {
        sleep_ms = 2000;
    }
    osal_mdelay(sleep_ms);
    camx_plat_reboot(0);
}

void reboot_async(int sleep_ms)
{
    osal_thr_dowork("xreboot", _reboot_work, (void *)sleep_ms);
}

void camx_plat_os_stats(void)
{
    // task
#if 0
    do {
        char *pbuf = osal_mem_alloc(4096);
        if (!pbuf) {
            break;
        }
        extern void vTaskList(char *pbuf);
        vTaskList(pbuf);
        //camx_log_printf("\r\n\r\ntask_name          task_state priority stack task_num\r\n%s\r\n", pbuf);
        camx_log_printf("\r\n------------------task------------------\r\n");
        camx_log_printf("%s", pbuf);
        osal_mem_free(pbuf);
        camx_log_printf("\r\n----------------------------------------\r\n");
    } while (0);
#endif
    /* extern void get_task_state(void *parm); */
    /* get_task_state(NULL); //1分钟以内调用一次才准确 */
    // mem
    malloc_stats();
#if 0
    T_I("mem, %u/%u/%u",
        (uint32_t)xPortGetPhysiceMemorySize(),
        (uint32_t)xPortGetFreeHeapSize(),
        (uint32_t)xPortGetMinimumEverFreeHeapSize());
#endif
}

void camx_plat_mem_stats(void)
{
    malloc_stats();
}


int camx_plat_wifi_qos(void)
{
    int qos;
    // WIFI连接的STA通信丢包质量,0-100,
    //一般认为大于50为较好,20-50之间为一般,小于20较差
    char cqi = wifi_get_cqi();

    // 网络质量: 1-6数字越大网络质量越好
    // 0 - 不支持，1 - 无信号
    if (cqi > 60) {
        qos = 6;
    } else if (cqi > 50) {
        qos = 5;
    } else if (cqi > 20) {
        qos = 3;
    } else if (cqi > 10) {
        qos = 2;
    } else {
        qos = 1;
    }

    return (qos);
}


int xc_iotcfg_read(uint8_t *data, uint16_t *len, uint16_t cap)
{
    int rc;
    /* flash start addr */
    struct vfs_attr file_attr;
    FILE *pfp = fopen("mnt/sdfile/app/iotcfg", "r");
    if (pfp == NULL) {
        T_E("Failed to fopen camx_storage_iotcfg_area_path(%s)",
            "mnt/sdfile/app/iotcfg");
        return (-1);
    }
    fget_attrs(pfp, &file_attr);
    uint32_t iotcfg_fal_addr = sdfile_cpu_addr2flash_addr(file_attr.sclust);
    uint32_t iotcfg_fal_size = file_attr.fsize;
    int      rlen = (int)fread(data, 1, cap, pfp);
    T_I("iotcfg fal addr:%x, size:%u, rlen:%d, cap(%d)",
        iotcfg_fal_addr,
        iotcfg_fal_size,
        rlen,
        cap);

    *len = rlen;
    fclose(pfp);

    return (0);
}


//uint64_t osal_clock_utctime(void)
//{
//    return 0;
//}
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
