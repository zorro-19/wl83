// binary representation
// attribute size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#ifndef _BT_COMMON_H
#define _BT_COMMON_H
#include <stdint.h>
#include "app_config.h"

#include "generic/typedef.h"
#include "bt_profile_cfg.h"

enum {
    ST_BIT_INQUIRY = 0,
    ST_BIT_PAGE_SCAN,
    ST_BIT_BLE_ADV,
    ST_BIT_SPP_CONN,
    ST_BIT_BLE_CONN,
    ST_BIT_WEIXIN_CONN,
};

enum {
    BLE_PRIV_MSG_PAIR_CONFIRM = 0xF0,
    BLE_PRIV_PAIR_ENCRYPTION_CHANGE,
};//ble_state_e

enum {
    COMMON_EVENT_EDR_REMOTE_TYPE = 1,
    COMMON_EVENT_BLE_REMOTE_TYPE,
};

extern uint16_t little_endian_read_16(const uint8_t *buffer, int pos);
extern uint32_t little_endian_read_24(const uint8_t *buffer, int pos);
extern uint32_t little_endian_read_32(const uint8_t *buffer, int pos);
extern void swapX(const uint8_t *src, uint8_t *dst, int len);

//common api
void bt_ble_init(void);
void bt_ble_exit(void);
void bt_ble_adv_enable(u8 enable);
void ble_app_disconnect(void);
void bt_master_ble_init(void);
void bt_master_ble_exit(void);
const u8 *bt_get_mac_addr(void);
void bt_update_mac_addr(u8 *addr);
const char *bt_get_local_name(void);

#endif
