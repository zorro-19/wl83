
#include "app_config.h"
#include "btcontroller_config.h"
#include "btctrler/btctrler_task.h"
#include "btstack/btstack_task.h"
#include "btstack/le/att.h"
#include "btstack/le/le_user.h"
#include "btstack/avctp_user.h"
#include "bt_common.h"
#include "le_common.h"
#include "le_net_central.h"
#include "event/bt_event.h"
#include "syscfg/syscfg_id.h"
#include "../multi_demo/le_multi_common.h"

void (*lmp_ch_update_resume_hdl)(void *priv) = NULL;

static bool s_ble_module_init_done = false;

void bt_ble_module_init(void)
{
    if (s_ble_module_init_done) {
        return ;
    }
    void lmp_set_sniff_disable(void);
    lmp_set_sniff_disable();

#if TCFG_USER_BLE_ENABLE
    u8 tmp_ble_addr[6];
    extern const u8 *bt_get_mac_addr(void);
    /* extern void lib_make_ble_address(u8 * ble_address, u8 * edr_address); */
    extern void bt_make_ble_address(u8 * ble_address, u8 * edr_address);
    extern int le_controller_set_mac(void *addr);
    /* lib_make_ble_address(tmp_ble_addr, (u8 *)bt_get_mac_addr()); */
    bt_make_ble_address(tmp_ble_addr, (u8 *)bt_get_mac_addr());
    le_controller_set_mac((void *)tmp_ble_addr);
    printf("\n-----edr + ble 's address-----");
    put_buf((void *)bt_get_mac_addr(), 6);
    put_buf((void *)tmp_ble_addr, 6);
#if BT_NET_CENTRAL_EN || TRANS_MULTI_BLE_MASTER_NUMS
    extern void ble_client_config_init(void);
    ble_client_config_init();
#endif
#endif

    btstack_init();

    s_ble_module_init_done = true;
}

void bt_ble_module_fini(void)
{
    if (s_ble_module_init_done) {
        /* btstack_exit(); */
        s_ble_module_init_done = false;
    }
}

static int bt_connction_status_event_handler(struct bt_event *bt)
{
    switch (bt->event) {
    case BT_STATUS_INIT_OK:
        puts("BT_STATUS_INIT_OK");
        bt_ble_init();
        break;
    }

    return 0;
}

int ble_bt_event_handler(struct sys_event *event)
{
    if (event->from == BT_EVENT_FROM_CON) {
        return bt_connction_status_event_handler((struct bt_event *)event->payload);
    }

    return 0;
}

/*
 * 静态注册设备事件回调函数，优先级为0
 */
SYS_EVENT_STATIC_HANDLER_REGISTER(camx_bt_event, 0) = {
    .event_type     = SYS_BT_EVENT,
    .prob_handler   = ble_bt_event_handler,
    .post_handler   = NULL,
};


