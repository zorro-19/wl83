#include "app_config.h"
#include "btstack/btstack_task.h"
#include "btcontroller_modules.h"
#include "btstack/avctp_user.h"
#include "classic/hci_lmp.h"
#include "bt_ble/bt_emitter.h"
#include "generic/list.h"
#include "os/os_api.h"
#include "syscfg_id.h"
#include "system/timer.h"
#include "asm/crc16.h"
#include "asm/rf_coexistence_config.h"
#include "event/key_event.h"

#if TCFG_USER_EMITTER_ENABLE

#define LOG_TAG_CONST        BT_EMITTER
#define LOG_TAG             "[BT_EMITTER]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_DUMP_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"

#define  SEARCH_BD_ADDR_LIMITED 0
#define  SEARCH_BD_NAME_LIMITED 1
#define  SEARCH_CUSTOM_LIMITED  2
#define  SEARCH_NULL_LIMITED    3

#define SEARCH_LIMITED_MODE  SEARCH_BD_NAME_LIMITED

struct remote_name {
    u16 crc;
    u8 addr[6];
    u8 name[32];
};

static struct list_head inquiry_noname_list = LIST_HEAD_INIT(inquiry_noname_list);

struct inquiry_noname_remote {
    struct list_head entry;
    u8 match;
    s8 rssi;
    u8 addr[6];
    u32 class;
};

static OS_MUTEX mutex;
static u8 emitter_or_receiver;
static u8 read_name_start = 0;
static u8 bt_search_busy = 0;
static u16 bt_emitter_fix_timer;
static u16 bt_emitter_a2dp_resume_timer;
static void *last_server = NULL;

extern u8 hci_standard_connect_check(void);
extern u8 get_remote_dev_info_index(void);
extern u8 restore_remote_device_info_profile(bd_addr_t mac_addr, u8 device_num, u8 id, u8 profile);
extern void bt_set_emitter_enable_flag(bool flag);
extern u8 connect_last_device_from_vm(void);

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射发起搜索设备
   @param    无
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
void bt_search_device(void)
{
    if (bt_search_busy) {
        //return;
    }
    bt_cmd_prepare(USER_CTRL_WRITE_SCAN_DISABLE, 0, NULL);
    bt_cmd_prepare(USER_CTRL_WRITE_CONN_DISABLE, 0, NULL);

#if TCFG_WIFI_ENABLE
    if (bt_get_total_connect_dev() == 0) {
        switch_rf_coexistence_config_table(7);
    }
#endif

    read_name_start = 0;
    bt_search_busy = 1;
    //在同时打开wifi的场景下，搜索设备的时间不宜过长，一般不超过12秒，否则容易出现wifi断开的情况，建议分多次搜索
    u8 inquiry_length = 10;   // inquiry_length * 1.28s
    bt_cmd_prepare(USER_CTRL_SEARCH_DEVICE, 1, &inquiry_length);
    log_info("bt_search_start");
}

static void bt_emitter_fix_search_device(void *p)
{
    bt_emitter_fix_timer = 0;
    bt_cmd_prepare(USER_CTRL_WRITE_CONN_DISABLE, 0, NULL);
    bt_search_device();
}

u8 bt_search_status(void)
{
    return bt_search_busy;
}

u8 bt_emitter_role_get(void)
{
    return emitter_or_receiver;
}

void bt_emitter_stop_search_device(void)
{
    bt_cmd_prepare(USER_CTRL_INQUIRY_CANCEL, 0, NULL);
}

void emitter_bt_connect(u8 *mac)
{
    if (emitter_or_receiver != BT_EMITTER_EN) {
        return;
    }

    while (hci_standard_connect_check() == 0x80) {
        //wait profile connect ok;
        if (bt_get_curr_channel_state()) {
            break;
        }
        os_time_dly(10);
    }

    ////断开链接
    if (bt_get_curr_channel_state() != 0) {
        bt_cmd_prepare(USER_CTRL_POWER_OFF, 0, NULL);
    } else {
        if (hci_standard_connect_check()) {
            bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
            bt_cmd_prepare(USER_CTRL_CONNECTION_CANCEL, 0, NULL);
        }
    }
    /* if there are some connected channel ,then disconnect*/
    while (hci_standard_connect_check() != 0) {
        //wait disconnect;
        os_time_dly(10);
    }

#if TCFG_WIFI_ENABLE
    if (bt_get_total_connect_dev() == 0) {
        switch_rf_coexistence_config_table(7);
    }
#endif
    bt_cmd_prepare(USER_CTRL_START_CONNEC_VIA_ADDR, 6, mac);
}

void bt_emitter_start_search_device(void)
{
    if (emitter_or_receiver != BT_EMITTER_EN) {
        return;
    }

    while (hci_standard_connect_check() == 0x80) {
        //wait profile connect ok;
        if (bt_get_curr_channel_state()) {
            break;
        }
        os_time_dly(10);
    }

    ////断开链接
    if (bt_get_curr_channel_state() != 0) {
        bt_cmd_prepare(USER_CTRL_POWER_OFF, 0, NULL);
    } else {
        if (hci_standard_connect_check()) {
            bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
            bt_cmd_prepare(USER_CTRL_CONNECTION_CANCEL, 0, NULL);
        }
    }
    /* if there are some connected channel ,then disconnect*/
    while (hci_standard_connect_check() != 0) {
        //wait disconnect;
        os_time_dly(10);
    }

    ////关闭可发现可链接
    bt_cmd_prepare(USER_CTRL_WRITE_SCAN_DISABLE, 0, NULL);
    bt_cmd_prepare(USER_CTRL_WRITE_CONN_DISABLE, 0, NULL);
    ////切换样机状态
    bt_search_device();
}

////回链耳机音箱
u8 connect_last_sink_device_from_vm(void)
{
    bd_addr_t mac_addr;
    u8 flag = 0;
    flag = restore_remote_device_info_profile(mac_addr, 1, get_remote_dev_info_index(), REMOTE_SINK);
    if (flag) {
        //connect last conn
        log_info("last source device addr from vm:");
        log_info_hexdump(mac_addr, 6);
#if TCFG_WIFI_ENABLE
        if (bt_get_total_connect_dev() == 0) {
            switch_rf_coexistence_config_table(7);
        }
#endif
        bt_cmd_prepare(USER_CTRL_START_CONNEC_VIA_ADDR, 6, mac_addr);
    }

    return flag;
}

////回链手机
u8 connect_last_source_device_from_vm(void)
{
    bd_addr_t mac_addr;
    u8 flag = 0;
    flag = restore_remote_device_info_profile(mac_addr, 1, get_remote_dev_info_index(), REMOTE_SOURCE);
    if (flag) {
        //connect last conn
        log_info("last source device addr from vm:");
        log_info_hexdump(mac_addr, 6);
#if TCFG_WIFI_ENABLE
        if (bt_get_total_connect_dev() == 0) {
            switch_rf_coexistence_config_table(7);
        }
#endif
        bt_cmd_prepare(USER_CTRL_START_CONNEC_VIA_ADDR, 6, mac_addr);
    }

    return flag;
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射 提供按键切换发射器或者是音箱功能
   @param    2:发射    1：接收   0: 关闭
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
void emitter_or_receiver_switch(u8 flag)
{
    /* log_info("===emitter_or_receiver_switch %d %x\n", flag, hci_standard_connect_check()); */
    /*如果上一次操作记录跟传进来的参数一致，则不操作*/
    if (bt_emitter_fix_timer) {
        sys_timeout_del(bt_emitter_fix_timer);
        bt_emitter_fix_timer = 0;
    }

    if (emitter_or_receiver == flag) {
        return;
    }

    if (!os_mutex_valid(&mutex)) {
        os_mutex_create(&mutex);
    }

    while (hci_standard_connect_check() == 0x80) {
        //wait profile connect ok;
        if (emitter_or_receiver == BT_EMITTER_EN) {
            if (bt_emitter_get_curr_channel_state()) {
                break;
            }
        } else {
            if (bt_get_curr_channel_state()) {
                break;
            }
        }
        os_time_dly(10);
    }

    ////断开链接
    if (bt_get_curr_channel_state() || bt_emitter_get_curr_channel_state()) {
        bt_cmd_prepare(USER_CTRL_POWER_OFF, 0, NULL);
    } else {
        if (hci_standard_connect_check()) {
            bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
            bt_cmd_prepare(USER_CTRL_CONNECTION_CANCEL, 0, NULL);
        }
    }
    /* if there are some connected channel ,then disconnect*/
    while (hci_standard_connect_check() != 0) {
        //wait disconnect;
        os_time_dly(10);
    }

    /* g_printf("===wait to switch to mode %d\n", flag); */
    emitter_or_receiver = flag;

    config_btctler_bredr_master = flag == BT_EMITTER_EN ? 1 : 0;

    if (flag == BT_EMITTER_EN) {   ///蓝牙发射器
#if TCFG_BT_SNIFF_ENABLE && !defined CONFIG_LOW_POWER_ENABLE
        void lmp_set_sniff_disable(void);
        lmp_set_sniff_disable();
#endif
        lmp_hci_write_class_of_device(BD_CLASS_SMART_PHONE);
        bt_set_simple_pair_param(1, 0, 2);
        bredr_bulk_change(0);
        ////关闭可发现可链接
        bt_cmd_prepare(USER_CTRL_WRITE_SCAN_DISABLE, 0, NULL);
        bt_cmd_prepare(USER_CTRL_WRITE_CONN_DISABLE, 0, NULL);
        ////切换样机状态
        bt_set_emitter_enable_flag(1);
        bt_a2dp_source_init(NULL, 0, 1);
#if (TCFG_BT_SUPPORT_PROFILE_HFP_AG==1)
        bt_hfp_ag_buf_init(NULL, 0, 1);
#endif
        ////开启搜索设备
        if (connect_last_device_from_vm()) {
#if TCFG_WIFI_ENABLE
            switch_rf_coexistence_config_table(7);
#endif
            log_info("start connect device vm addr");
        } else {
#if TCFG_BT_SUPPORT_EMITTER_PAGE_SCAN
            bt_cmd_prepare(USER_CTRL_WRITE_SCAN_ENABLE, 0, NULL);
            bt_cmd_prepare(USER_CTRL_WRITE_CONN_ENABLE, 0, NULL);
#else
            bt_search_device();
#endif
        }
    } else {  ///蓝牙接收
#if TCFG_BT_SNIFF_ENABLE
        void lmp_set_sniff_enable(void);
        lmp_set_sniff_enable();
#endif
#if TCFG_BT_SUPPORT_PROFILE_PBAP
        lmp_hci_write_class_of_device(BD_CLASS_CAR_AUDIO);
#else
        lmp_hci_write_class_of_device(BD_CLASS_WEARABLE_HEADSET);
#endif
        bt_set_simple_pair_param(3, 0, 2);
        bredr_bulk_change(1);
        ////切换样机状态
        bt_set_emitter_enable_flag(0);
        emitter_media_source(1, 0);
        bt_cmd_prepare(USER_CTRL_INQUIRY_CANCEL, 0, NULL);
        bt_a2dp_source_init(NULL, 0, 0);
#if (TCFG_BT_SUPPORT_PROFILE_HFP_AG==1)
        bt_hfp_ag_buf_init(NULL, 0, 0);
#endif
        /*
        ////开启可发现可链接
        if (connect_last_device_from_vm()) {
            log_info("start connect vm addr phone \n");
        } else {
            bt_cmd_prepare(USER_CTRL_WRITE_SCAN_ENABLE, 0, NULL);
            bt_cmd_prepare(USER_CTRL_WRITE_CONN_ENABLE, 0, NULL);
        }
        */
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射搜索设备没有名字的设备，放进需要获取名字链表
   @param    status : 获取成功     0：获取失败
  			 addr:设备地址
		     name：设备名字
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
void emitter_search_noname(u8 status, u8 *addr, char *name)
{
    struct inquiry_noname_remote *remote, *n;
    u8 res = 0;

    if (emitter_or_receiver != BT_EMITTER_EN) {
        return;
    }

    os_mutex_pend(&mutex, 0);

    if (status) {
        list_for_each_entry_safe(remote, n, &inquiry_noname_list, entry) {
            if (!memcmp(addr, remote->addr, 6)) {
                list_del(&remote->entry);
                free(remote);
            }
        }
        goto __find_next;
    }
    list_for_each_entry_safe(remote, n, &inquiry_noname_list, entry) {
        if (!memcmp(addr, remote->addr, 6)) {
            res = emitter_search_result(name, strlen(name), addr, remote->class, remote->rssi);
            if (res) {
                read_name_start = 0;
                remote->match = 1;
                bt_cmd_prepare(USER_CTRL_INQUIRY_CANCEL, 0, NULL);
                os_mutex_post(&mutex);
                return;
            }
            list_del(&remote->entry);
            free(remote);
        }
    }

__find_next:

    read_name_start = 0;
    remote = NULL;
    if (!list_empty(&inquiry_noname_list)) {
        remote =  list_first_entry(&inquiry_noname_list, struct inquiry_noname_remote, entry);
    }

    if (remote) {
        read_name_start = 1;
        bt_cmd_prepare(USER_CTRL_READ_REMOTE_NAME, 6, remote->addr);
    }

    os_mutex_post(&mutex);
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射停止搜索
   @param    无
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
void emitter_search_stop(u8 result)
{
    struct inquiry_noname_remote *remote, *n;
    bt_search_busy = 0;
    u8 wait_connect_flag = 1;

    if (emitter_or_receiver != BT_EMITTER_EN) {
        return;
    }

    os_mutex_pend(&mutex, 0);

    if (!list_empty(&inquiry_noname_list)) {
        bt_cmd_prepare(USER_CTRL_PAGE_CANCEL, 0, NULL);
    }

    if (!result) {
#if TCFG_WIFI_ENABLE
        if (bt_get_total_connect_dev() == 0) {
            switch_rf_coexistence_config_table(0);
        }
#endif

        list_for_each_entry_safe(remote, n, &inquiry_noname_list, entry) {
            if (remote->match) {
#if TCFG_WIFI_ENABLE
                switch_rf_coexistence_config_table(7);
#endif
                bt_cmd_prepare(USER_CTRL_START_CONNEC_VIA_ADDR, 6, remote->addr);
                wait_connect_flag = 0;
            }
            list_del(&remote->entry);
            free(remote);
        }
    }
    read_name_start = 0;

    if (wait_connect_flag) {
        /* log_info("wait conenct\n"); */
        bt_cmd_prepare(USER_CTRL_WRITE_SCAN_DISABLE, 0, NULL);
        if (!result) {
            bt_cmd_prepare(USER_CTRL_WRITE_CONN_DISABLE, 0, NULL);
            if (!bt_emitter_fix_timer) {
                if (bt_get_total_connect_dev() == 0) {
                    bt_cmd_prepare(USER_CTRL_WRITE_CONN_ENABLE, 0, NULL);
                }
                bt_emitter_fix_timer = sys_timeout_add(NULL, bt_emitter_fix_search_device, 1500);
            }
        }
    }

    os_mutex_post(&mutex);
}

int bt_emitter_page_timeout(void)
{
    if (emitter_or_receiver == BT_RECEIVER_EN) {
        return 1;
    }
    if (emitter_or_receiver != BT_EMITTER_EN) {
        return -1;
    }
#if TCFG_BT_SUPPORT_EMITTER_PAGE_SCAN
    bt_cmd_prepare(USER_CTRL_WRITE_CONN_ENABLE, 0, NULL);
    bt_cmd_prepare(USER_CTRL_WRITE_SCAN_ENABLE, 0, NULL);
#else
    bt_search_device();
#endif
    return 0;
}

int bt_emitter_disconnect(void)
{
    if (emitter_or_receiver != BT_EMITTER_EN) {
        return -1;
    }
    bt_cmd_prepare(USER_CTRL_WRITE_CONN_ENABLE, 0, NULL);
#if TCFG_BT_SUPPORT_EMITTER_PAGE_SCAN
    bt_cmd_prepare(USER_CTRL_WRITE_SCAN_ENABLE, 0, NULL);
#endif
    return 0;
}

#if (SEARCH_LIMITED_MODE == SEARCH_BD_ADDR_LIMITED)
static const u8 bd_addr_filt[][6] = {
    {0x8E, 0xA7, 0xCA, 0x0A, 0x5E, 0xC8}, /*S10_H*/
    {0xA7, 0xDD, 0x05, 0xDD, 0x1F, 0x00}, /*ST-001*/
    {0xE9, 0x73, 0x13, 0xC0, 0x1F, 0x00}, /*HBS 730*/
    {0x38, 0x7C, 0x78, 0x1C, 0xFC, 0x02}, /*Bluetooth*/
};

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射搜索通过地址过滤
   @param    无
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
static u8 search_bd_addr_filt(const u8 *addr)
{
    log_info("bd_addr:");
    log_info_hexdump(addr, 6);

    for (u8 i = 0; i < (sizeof(bd_addr_filt) / sizeof(bd_addr_filt[0])); i++) {
        if (memcmp(addr, bd_addr_filt[i], 6) == 0) {
            /* log_info("bd_addr match:%d\n", i); */
            return TRUE;
        }
    }
    /*log_info("bd_addr not match\n"); */
    return FALSE;
}
#endif


#if (SEARCH_LIMITED_MODE == SEARCH_BD_NAME_LIMITED)
#if 0
static const u8 bd_name_filt[][32] = {
    "BeMine",
    "EDIFIER CSR8635",/*CSR*/
    "JL-BT-SDK",/*Realtek*/
    "I7-TWS",/*ZKLX*/
    "TWS-i7",/*ZKLX*/
    "I9",/*ZKLX*/
    "小米小钢炮蓝牙音箱",/*XiaoMi*/
    "小米蓝牙音箱",/*XiaoMi*/
    "XMFHZ02",/*XiaoMi*/
    "JBL GO 2",
    "i7mini",/*JL tws AC690x*/
    "S08U",
    "AI8006B_TWS00",
    "S046",/*BK*/
    "AirPods",
    "CSD-TWS-01",
    "AC692X_wh",
    "JBL GO 2",
    "JBL Flip 4",
    "BT Speaker",
    "CSC608",
    "QCY-QY19",
    "Newmine",
    "HT1+",
    "S-35",
    "T12-JL",
    "Redmi AirDots_R",
    "Redmi AirDots_L",
    "AC69_Bluetooth",
    "FlyPods 3",
    "MNS",
    "Jam Heavy Metal",
    "Bluedio",
    "HR-686",
    "BT MUSIC",
    "BW-USB-DONGLE",
    "S530",
    "XPDQ7",
    "MICGEEK Q9S",
    "S10_H",
    "S10",/*JL AC690x*/
    "S11",/*JL AC460x*/
    "HBS-730",
    "SPORT-S9",
    "Q5",
    "IAEB25",
    "T5-JL",
    "MS-808",
    "LG HBS-730",
    "NG-BT07"
};
#else
static const char *bd_name_filt[] = {
    "JL-AC79XX-AF0B",
    "JL-AC79XX-FFAA",
    "JL-AC79XX-AAFF",
    "CAR MULTIMEDIA",
    "MTU-Android",
    "GEELY_BT",
    "Audi_MMI_0303",
    "Clancey",
    "BC8-Android",
    "QCY-T13",
    "T28",
    "Bluetooth music",
    "S16",
    "887",
    "Mi True Wireless Earphones",
};
#endif

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射搜索通过名字过滤
   @param    无
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
u8 search_bd_name_filt(const char *data, u8 len, u32 dev_class, char rssi)
{
    char bd_name[64] = {0};
    char db_name[64] = {0};

    if ((len > (sizeof(bd_name))) || (len == 0)) {
        return FALSE;
    }

    memcpy(bd_name, data, len);
    log_info("name:%s,len:%d,class %x ,rssi %d", bd_name, len, dev_class, rssi);

    if (syscfg_read(CFG_REMOTE_DB_INFO, db_name, sizeof(db_name)) == sizeof(db_name)) {
        if (memcmp(data, db_name, len) == 0) {
            log_info("*****find dev ok******");
            return TRUE;
        }
        return FALSE;
    }

    for (u8 i = 0; i < (sizeof(bd_name_filt) / sizeof(bd_name_filt[0])); i++) {
        if (memcmp(data, bd_name_filt[i], len) == 0) {
            log_info("*****find dev ok******");
            return TRUE;
        }
    }

    return FALSE;
}
#endif

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射搜索结果回调处理
   @param    name : 设备名字
			 name_len: 设备名字长度
			 addr:   设备地址
			 dev_class: 设备类型
			 rssi:   设备信号强度
   @return   无
   @note
 			蓝牙设备搜索结果，可以做名字/地址过滤，也可以保存搜到的所有设备
 			在选择一个进行连接，获取其他你想要的操作。
 			返回TRUE，表示搜到指定的想要的设备，搜索结束，直接连接当前设备
 			返回FALSE，则继续搜索，直到搜索完成或者超时
*/
/*----------------------------------------------------------------------------*/
u8 emitter_search_result(char *name, u8 name_len, u8 *addr, u32 dev_class, char rssi)
{
    if (emitter_or_receiver != BT_EMITTER_EN) {
        return 0;
    }

#if (SEARCH_LIMITED_MODE == SEARCH_BD_NAME_LIMITED)
    if (name == NULL) {
        struct inquiry_noname_remote *remote = zalloc(sizeof(struct inquiry_noname_remote));
        remote->match = 0;
        remote->class = dev_class;
        remote->rssi = rssi;
        memcpy(remote->addr, addr, 6);
        os_mutex_pend(&mutex, 0);
        list_add_tail(&remote->entry, &inquiry_noname_list);
        if (read_name_start == 0) {
            read_name_start = 1;
            bt_cmd_prepare(USER_CTRL_READ_REMOTE_NAME, 6, addr);
        }
        os_mutex_post(&mutex);
    }
#endif

#if (SEARCH_LIMITED_MODE == SEARCH_BD_NAME_LIMITED)
    return search_bd_name_filt(name, name_len, dev_class, rssi);
#endif

#if (SEARCH_LIMITED_MODE == SEARCH_BD_ADDR_LIMITED)
    return search_bd_addr_filt(addr);
#endif

#if (SEARCH_LIMITED_MODE == SEARCH_CUSTOM_LIMITED)
    /*以下为搜索结果自定义处理*/
    char bt_name[63] = {0};
    u8 len;
    if (name_len == 0) {
        log_info("No_eir");
    } else {
        len = (name_len > 63) ? 63 : name_len;
        /* display bd_name */
        memcpy(bt_name, name, len);
        log_info("name:%s,len:%d,class %x ,rssi %d", bt_name, name_len, dev_class, rssi);
    }

    /* display bd_addr */
    log_info_hexdump(addr, 6);

    /* You can connect the specified bd_addr by below api      */
    //bt_cmd_prepare(USER_CTRL_START_CONNEC_VIA_ADDR,6,addr);

    return FALSE;
#endif

#if (SEARCH_LIMITED_MODE == SEARCH_NULL_LIMITED)
    /*没有指定限制，则搜到什么就连接什么*/
    return TRUE;
#endif
}

typedef enum {
    AVCTP_OPID_VOLUME_UP   = 0x41,
    AVCTP_OPID_VOLUME_DOWN = 0x42,
    AVCTP_OPID_MUTE        = 0x43,
    AVCTP_OPID_PLAY        = 0x44,
    AVCTP_OPID_STOP        = 0x45,
    AVCTP_OPID_PAUSE       = 0x46,
    AVCTP_OPID_NEXT        = 0x4B,
    AVCTP_OPID_PREV        = 0x4C,
} AVCTP_CMD_TYPE;

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射接收到设备按键消息
   @param    cmd:按键命令
   @return   无
   @note
 			发射器收到接收器发过来的控制命令处理
 			根据实际需求可以在收到控制命令之后做相应的处理
 			蓝牙库里面定义的是weak函数，直接再定义一个同名可获取信息
*/
/*----------------------------------------------------------------------------*/
void emitter_rx_avctp_opid_deal(u8 cmd, u8 id)
{
    struct key_event key = {0};
    log_info("avctp_rx_cmd:%x", cmd);

    switch (cmd) {
    case AVCTP_OPID_NEXT:
        log_info("AVCTP_OPID_NEXT");
        key.action = KEY_EVENT_LONG;
        key.value = KEY_VOLUME_INC;
        key.type = KEY_EVENT_USER;
        key_event_notify(KEY_EVENT_FROM_USER, &key);
        break;
    case AVCTP_OPID_PREV:
        log_info("AVCTP_OPID_PREV");
        key.action = KEY_EVENT_LONG;
        key.value = KEY_VOLUME_DEC;
        key.type = KEY_EVENT_USER;
        key_event_notify(KEY_EVENT_FROM_USER, &key);
        break;
    case AVCTP_OPID_PLAY:
    case AVCTP_OPID_PAUSE:
        log_info("AVCTP_OPID_PP");
#if 0
        bt_emitter_pp(1);
#else
        /* key.action = KEY_EVENT_UP; */
        /* key.value = KEY_LOCAL; */
        key.action = KEY_EVENT_CLICK;
        key.value = KEY_OK;
        key.type = KEY_EVENT_USER;
        key_event_notify(KEY_EVENT_FROM_USER, &key);
#endif
        break;
    case AVCTP_OPID_STOP:
        //停止时可能需要停止当前播放的音频，不然会一直堵塞解码
        log_info("AVCTP_OPID_STOP");
#if 0//!BT_SUPPORT_EMITTER_AUTO_A2DP_START || CONFIG_POWER_ON_ENABLE_EMITTER
        bt_emitter_pp(0);
#else
        key.action = KEY_EVENT_HOLD;
        key.value = KEY_LOCAL;
        key.type = KEY_EVENT_USER;
        key_event_notify(KEY_EVENT_FROM_USER, &key);
#endif
        break;
    case AVCTP_OPID_VOLUME_UP:
        log_info("AVCTP_OPID_VOLUME_UP");
        key.action = KEY_EVENT_CLICK;
        key.value = KEY_VOLUME_INC;
        key.type = KEY_EVENT_USER;
        key_event_notify(KEY_EVENT_FROM_USER, &key);
        break;
    case AVCTP_OPID_VOLUME_DOWN:
        log_info("AVCTP_OPID_VOLUME_DOWN");
        key.action = KEY_EVENT_CLICK;
        key.value = KEY_VOLUME_DEC;
        key.type = KEY_EVENT_USER;
        key_event_notify(KEY_EVENT_FROM_USER, &key);
        break;
    default:
        break;
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射接收设备同步音量
   @param    vol:接收到设备同步音量
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
void emitter_rx_vol_change(u8 vol)
{
    log_info("vol_change:%d", vol);
}

typedef struct _EMITTER_INFO {
    volatile u8 role;
    u8 media_source;
    u8 source_record;/*统计当前有多少设备可用*/
    u8 reserve;
} EMITTER_INFO_T;

static EMITTER_INFO_T emitter_info = {
    .role = 0/*EMITTER_ROLE_SLAVE*/,
};

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射接收设备同步音量
   @param    source: 高级音频角色  1：source  0：sink
  			 en:关闭source
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
void emitter_media_source(u8 source, u8 en)
{
    if (en) {
        /*关闭当前的source通道*/
        //emitter_media_source_close(emitter_info.media_source);
        emitter_info.source_record |= source;
        if (emitter_info.media_source == source) {
            return;
        }
        emitter_info.media_source = source;
        bt_emitter_send_media_toggle(NULL, 1);
    } else {
        emitter_info.source_record &= ~source;
        if (emitter_info.media_source == source) {
            emitter_info.media_source = 0/*EMITTER_SOURCE_NULL*/;
            bt_emitter_send_media_toggle(NULL, 0);
            //emitter_media_source_next();
        }
    }
    log_info("current source: %x-%x", source, emitter_info.source_record);
}

u8 bt_emitter_stu_set(u8 on)
{
    if (emitter_or_receiver != BT_EMITTER_EN) {
        return 0;
    }
    if (!(bt_emitter_get_curr_channel_state() & A2DP_SRC_CH)) {
        emitter_media_source(1, 0);
        return 0;
    }
    log_info("total con dev:%d", bt_get_total_connect_dev());
    if (on && (bt_get_total_connect_dev() == 0)) {
        on = 0;
    }
    emitter_media_source(1, on);
    return on;
}

u8 bt_emitter_pp(u8 pp)
{
    if (bt_emitter_a2dp_resume_timer) {
        sys_timeout_del(bt_emitter_a2dp_resume_timer);
        bt_emitter_a2dp_resume_timer = 0;
    }
    if (emitter_or_receiver != BT_EMITTER_EN) {
        return 0;
    }
    if (bt_get_total_connect_dev() == 0) {
        //如果没有连接就启动一下搜索
        /* bt_search_device(); */
        return 0;
    }
    if (!(bt_emitter_get_curr_channel_state() & A2DP_SRC_CH)) {
        return 0;
    }
    return bt_emitter_stu_set(pp);
}

u8 bt_emitter_stu_sw(void)
{
    return bt_emitter_pp(!bt_emitter_stu_get());
}

//pin code 轮询功能
static const char pin_code_list[][4] = {
    {'0', '0', '0', '0'},
    {'1', '2', '3', '4'},
    {'8', '8', '8', '8'},
    {'1', '3', '1', '4'},
    {'4', '3', '2', '1'},
    {'1', '1', '1', '1'},
    {'2', '2', '2', '2'},
    {'3', '3', '3', '3'},
    {'5', '6', '7', '8'},
    {'5', '5', '5', '5'},
    {'5', '5', '6', '6'},
};

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射链接pincode 轮询
   @param    无
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
const char *bt_get_emitter_pin_code(u8 flag)
{
    static u8 index_flag = 0;
    int pincode_num = sizeof(pin_code_list) / sizeof(pin_code_list[0]);
    if (flag == 1) {
        //reset index
        index_flag = 0;
    } else if (flag == 2) {
        //查询是否要开始继续回连尝试pin code。
        if (index_flag + 1 >= pincode_num) {
            //之前已经遍历完了
            return NULL;
        } else {
            index_flag++; //准备使用下一个
        }
    } else {
        log_info("get pin code index %d", index_flag);
    }
    return &pin_code_list[index_flag][0];
}

#if 1
/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射链接保存远端设备名字
   @param    addr:远端设备地址
			 name:远端设备名字
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
void emitter_save_remote_name(u8 *addr, u8 *name)
{
    struct remote_name remote_n;
    u16 id = CFG_REMOTE_DN_00;

    while (1) {
        syscfg_read(id, &remote_n, sizeof(struct remote_name));
        if (remote_n.crc == CRC16(&remote_n.addr, sizeof(struct remote_name) - 2)) {
            if (!memcmp(addr, remote_n.addr, 6)) {
                return;
            }
        } else {
            break;
        }
        if (++id > CFG_REMOTE_DN_END) {
            break;
        }
    }
    memset(&remote_n, 0, sizeof(struct remote_name));
    memcpy(remote_n.addr, addr, 6);
    memcpy(remote_n.name, name, strlen((char *)name));

    remote_n.crc = CRC16((u8 *)&remote_n.addr, sizeof(struct remote_name) - 2);

    syscfg_write(id, &remote_n, sizeof(struct remote_name));
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射通过地址来获取设备名字
   @param    addr:远端设备地址
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
int emitter_get_remote_name(u8 *addr, struct remote_name *remote_n)
{
    u16 id = CFG_REMOTE_DN_00;

    while (1) {
        syscfg_read(id, remote_n, sizeof(struct remote_name));
        if (remote_n->crc == CRC16(remote_n->addr, sizeof(struct remote_name) - 2)) {
            if (!memcmp(addr, remote_n->addr, 6)) {
                return 0;
            }
        } else {
            break;
        }
        if (++id > CFG_REMOTE_DN_END) {
            break;
        }
    }

    memset(remote_n, 0, sizeof(struct remote_name));

    return -1;
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射通过地址来删除vm的设备名字
   @param    addr:远端设备地址
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
void emitter_delete_remote_name(u8 *addr)
{
    struct remote_name remote_n;
    u16 id = CFG_REMOTE_DN_00;

    while (1) {
        syscfg_read(id, &remote_n, sizeof(struct remote_name));
        if (remote_n.crc == CRC16(&remote_n.addr, sizeof(struct remote_name) - 2)) {
            if (!memcmp(addr, remote_n.addr, 6)) {
                memset(&remote_n, 0xff, sizeof(struct remote_name));
                syscfg_write(id, &remote_n, sizeof(struct remote_name));
                return;
            }
        }
        if (++id > CFG_REMOTE_DN_END) {
            break;
        }
    }
}

/*----------------------------------------------------------------------------*/
/**@brief    蓝牙发射获取vm设备记忆
   @param    无
   @return   无
   @note
*/
/*----------------------------------------------------------------------------*/
void emitter_get_vm_device(void)
{
    bd_addr_t remote_addr[10];
    memset(remote_addr, 0, sizeof(remote_addr));
    u8 flag = bt_restore_remote_device_info_opt(remote_addr, 10, get_remote_dev_info_index());
    for (u8 i = 0; i < flag; i++) {
        log_info_hexdump(remote_addr[i], 6);
    }
}

#endif

void bredr_ag_a2dp_open_and_close(void)
{
    if (bt_emitter_get_curr_channel_state() & A2DP_SRC_CH) {
        log_info("start to disconnect a2dp");
        bt_emitter_cmd_prepare(USER_CTRL_DISCONN_A2DP, 0, NULL);
    } else {
        log_info("start to connect a2dp");
        bt_emitter_cmd_prepare(USER_CTRL_CONN_A2DP, 0, NULL);
    }
}

void bredr_ag_hfp_open_and_close(void)
{
    if (bt_emitter_get_curr_channel_state() & HFP_AG_CH) {
        log_info("start to disconnect HFP");
        bt_emitter_cmd_prepare(USER_CTRL_HFP_DISCONNECT, 0, NULL);
    } else {
        log_info("start to connect HFP");
        bt_emitter_cmd_prepare(USER_CTRL_HFP_CMD_BEGIN, 0, NULL);
    }
}

static void bt_emitter_a2dp_resume(void *p)
{
    last_server = NULL;

    if (emitter_or_receiver != BT_EMITTER_EN) {
        return;
    }
    if (bt_get_total_connect_dev() == 0) {
        //如果没有连接就启动一下搜索
        /* bt_search_device(); */
        return;
    }
    if (!(bt_emitter_get_curr_channel_state() & A2DP_SRC_CH)) {
        return;
    }

    bt_emitter_stu_set((u8)p);
}

void bt_emitter_esco_pp(u8 pp)
{
    if (emitter_or_receiver != BT_EMITTER_EN) {
        return;
    }
    if (bt_get_total_connect_dev() == 0) {
        return;
    }
    if (!(bt_emitter_get_curr_channel_state() & HFP_AG_CH)) {
        return;
    }
    if (pp) {
        if (bt_get_call_status() == BT_CALL_HANGUP) {
            if (bt_emitter_a2dp_resume_timer) {
                sys_timeout_del(bt_emitter_a2dp_resume_timer);
                bt_emitter_a2dp_resume_timer = 0;
            }
            last_server = get_bt_emitter_audio_server();
            bt_emitter_pp(!pp);
            bt_emitter_cmd_prepare(USER_CTRL_HFP_CALL_LAST_NO, 0, NULL);
            os_time_dly(5);
            set_bt_emitter_virtual_hdl(NULL);
            bt_emitter_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
        }
    } else {
        if (bt_get_call_status() == BT_CALL_INCOMING) {
            bt_emitter_pp(0);
            bt_emitter_cmd_prepare(USER_CTRL_HFP_CALL_ANSWER, 0, NULL);
        } else if (bt_get_call_status() != BT_CALL_HANGUP) {
            bt_emitter_cmd_prepare(USER_CTRL_HFP_CALL_HANGUP, 0, NULL);
            if (last_server) {
                bt_emitter_a2dp_resume_timer = sys_timeout_add((void *)(!pp), bt_emitter_a2dp_resume, 500);
            }
        }
    }
}

#endif

