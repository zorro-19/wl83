// binary representation
// attribute size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#ifndef _LE_XC_CFG_H
#define _LE_XC_CFG_H

#include <stdint.h>

//
// gatt profile include file, generated by jieli gatt_inc_generator.exe
//

static const uint8_t profile_data[] = {
    //////////////////////////////////////////////////////
    //
    // 0x0001 PRIMARY_SERVICE  0x1800
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x00, 0x18,

    /* CHARACTERISTIC,  2a00, READ | DYNAMIC, */
    // 0x0002 CHARACTERISTIC 2a00 READ | DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x02, 0x03, 0x00, 0x00, 0x2a,
    // 0x0003 VALUE 2a00 READ | DYNAMIC
    0x08, 0x00, 0x02, 0x01, 0x03, 0x00, 0x00, 0x2a,

    //////////////////////////////////////////////////////
    //
    // 0x0004 PRIMARY_SERVICE  865300b1-43e6-47b7-9cb0-5fc21d4ae340
    //
    //////////////////////////////////////////////////////
    0x18, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x28, 0x40, 0xe3, 0x4a, 0x1d, 0xc2, 0x5f, 0xb0, 0x9c, 0xb7, 0x47, 0xe6, 0x43, 0xb1, 0x00, 0x53, 0x86,

    /* CHARACTERISTIC,  865300b3-43e6-47b7-9cb0-5fc21d4ae340,  WRITE |READ| NOTIFY | DYNAMIC */
    // 0x0005 CHARACTERISTIC 865300b3-43e6-47b7-9cb0-5fc21d4ae340 WRITE |READ| NOTIFY | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x05, 0x00, 0x03, 0x28, 0x1a, 0x06, 0x00, 0x40, 0xe3, 0x4a, 0x1d, 0xc2, 0x5f, 0xb0, 0x9c, 0xb7, 0x47, 0xe6, 0x43, 0xb3, 0x00, 0x53, 0x86,
    // 0x0006 VALUE 865300b3-43e6-47b7-9cb0-5fc21d4ae340 WRITE |READ| NOTIFY | DYNAMIC
    0x16, 0x00, 0x1a, 0x03, 0x06, 0x00, 0x40, 0xe3, 0x4a, 0x1d, 0xc2, 0x5f, 0xb0, 0x9c, 0xb7, 0x47, 0xe6, 0x43, 0xb3, 0x00, 0x53, 0x86,
    // 0x0007 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x07, 0x00, 0x02, 0x29, 0x00, 0x00,

    /* CHARACTERISTIC,  865300b2-43e6-47b7-9cb0-5fc21d4ae340, READ | NOTIFY | DYNAMIC */
    // 0x0008 CHARACTERISTIC 865300b2-43e6-47b7-9cb0-5fc21d4ae340 READ | NOTIFY | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x08, 0x00, 0x03, 0x28, 0x12, 0x09, 0x00, 0x40, 0xe3, 0x4a, 0x1d, 0xc2, 0x5f, 0xb0, 0x9c, 0xb7, 0x47, 0xe6, 0x43, 0xb2, 0x00, 0x53, 0x86,
    // 0x0009 VALUE 865300b2-43e6-47b7-9cb0-5fc21d4ae340 READ | NOTIFY | DYNAMIC
    0x16, 0x00, 0x12, 0x03, 0x09, 0x00, 0x40, 0xe3, 0x4a, 0x1d, 0xc2, 0x5f, 0xb0, 0x9c, 0xb7, 0x47, 0xe6, 0x43, 0xb2, 0x00, 0x53, 0x86,
    // 0x000a CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x0a, 0x00, 0x02, 0x29, 0x00, 0x00,

    // END
    0x00, 0x00,
};
//
// characteristics <--> handles
//
#define ATT_CHARACTERISTIC_2a00_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_865300b3_43e6_47b7_9cb0_5fc21d4ae340_01_VALUE_HANDLE 0x0006
#define ATT_CHARACTERISTIC_865300b3_43e6_47b7_9cb0_5fc21d4ae340_01_CLIENT_CONFIGURATION_HANDLE 0x0007
#define ATT_CHARACTERISTIC_865300b2_43e6_47b7_9cb0_5fc21d4ae340_01_VALUE_HANDLE 0x0009
#define ATT_CHARACTERISTIC_865300b2_43e6_47b7_9cb0_5fc21d4ae340_01_CLIENT_CONFIGURATION_HANDLE 0x000a







#endif
