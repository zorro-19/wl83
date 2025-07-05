
#ifndef _EXT_WPA_SUPPLICANT_EVENT_H_
#define _EXT_WPA_SUPPLICANT_EVENT_H_

enum wpa_supplicant_state {
    STA_WPA_DISCONNECTED,
    STA_WPA_CONNECT_TIMEOUT_NOT_FOUND_SSID,
    STA_WPA_CONNECT_TIMEOUT_ASSOCIAT_FAIL,
    STA_WPA_SCANNING,
    STA_WPA_SCAN_COMPLETED,
    STA_WPA_CONNECT_COMPLETED,
};

enum wpa_supplicant_state ext_wpa_supplicant_get_state(void);

#endif  //_WPA_SUPPLICANT_EVENT_H_

