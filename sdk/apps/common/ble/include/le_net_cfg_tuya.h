// binary representation
// attribute size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#ifndef _LE_TUYA_DATA_H
#define _LE_TUYA_DATA_H

#include <stdint.h>
#if 1
static const uint8_t profile_data[] = {
    //////////////////////////////////////////////////////
    //
    // 0x0001 PRIMARY_SERVICE  1800
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
    // 0x0004 PRIMARY_SERVICE  FD50
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x28, 0x50, 0xfd,

    /* CHARACTERISTIC,  00000001-0000-1001-8001-00805F9B07D0, WRITE_WITHOUT_RESPONSE | DYNAMIC, */
    // 0x0005 CHARACTERISTIC 00000001-0000-1001-8001-00805F9B07D0 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x05, 0x00, 0x03, 0x28, 0x04, 0x06, 0x00, 0xd0, 0x07, 0x9b, 0x5f, 0x80, 0x00, 0x01, 0x80, 0x01, 0x10, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    // 0x0006 VALUE 00000001-0000-1001-8001-00805F9B07D0 WRITE_WITHOUT_RESPONSE | DYNAMIC
    0x16, 0x00, 0x04, 0x03, 0x06, 0x00, 0xd0, 0x07, 0x9b, 0x5f, 0x80, 0x00, 0x01, 0x80, 0x01, 0x10, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,

    /* CHARACTERISTIC,  00000002-0000-1001-8001-00805F9B07D0, NOTIFY | DYNAMIC, */
    // 0x0007 CHARACTERISTIC 00000002-0000-1001-8001-00805F9B07D0 NOTIFY | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x07, 0x00, 0x03, 0x28, 0x10, 0x08, 0x00, 0xd0, 0x07, 0x9b, 0x5f, 0x80, 0x00, 0x01, 0x80, 0x01, 0x10, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    // 0x0008 VALUE 00000002-0000-1001-8001-00805F9B07D0 NOTIFY | DYNAMIC
    0x16, 0x00, 0x10, 0x03, 0x08, 0x00, 0xd0, 0x07, 0x9b, 0x5f, 0x80, 0x00, 0x01, 0x80, 0x01, 0x10, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    // 0x0009 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x09, 0x00, 0x02, 0x29, 0x00, 0x00,

    /* CHARACTERISTIC,  00000003-0000-1001-8001-00805F9B07D0, READ | DYNAMIC, */
    // 0x000a CHARACTERISTIC 00000003-0000-1001-8001-00805F9B07D0 READ | DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x0a, 0x00, 0x03, 0x28, 0x02, 0x0b, 0x00, 0xd0, 0x07, 0x9b, 0x5f, 0x80, 0x00, 0x01, 0x80, 0x01, 0x10, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    // 0x000b VALUE 00000003-0000-1001-8001-00805F9B07D0 READ | DYNAMIC
    0x16, 0x00, 0x02, 0x03, 0x0b, 0x00, 0xd0, 0x07, 0x9b, 0x5f, 0x80, 0x00, 0x01, 0x80, 0x01, 0x10, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,

    // END
    0x00, 0x00,
};
//
// characteristics <--> handles
//
#define ATT_CHARACTERISTIC_2a00_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_00000001_0000_1001_8001_00805F9B07D0_01_VALUE_HANDLE 0x0006
#define ATT_CHARACTERISTIC_00000002_0000_1001_8001_00805F9B07D0_01_VALUE_HANDLE 0x0008
#define ATT_CHARACTERISTIC_00000002_0000_1001_8001_00805F9B07D0_01_CLIENT_CONFIGURATION_HANDLE 0x0009
#define ATT_CHARACTERISTIC_00000003_0000_1001_8001_00805F9B07D0_01_VALUE_HANDLE 0x000b
#endif // 0

#endif
