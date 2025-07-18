#include "system/includes.h"
#include "syscfg_id.h"
#include "app_config.h"

#if TCFG_EXT_WIFI_ENABLE

#define INTERFACE              "wlan0"
#define DRIVER                 "rtl871xdrv"
#define DRIVER_NAME            "RTL818x"

#if TCFG_RTL8189E_ENABLE || TCFG_RTL8822CS_ENABLE || TCFG_RTL8733BS_ENABLE
static char hostapd_config_file[] = \
                                    "interface="INTERFACE"\n\
ssid=####SSID_LENTH_MUST_LESS_THAN_32\n\
channel=6\n\
macaddr_acl=0\n\
auth_algs=3\n\
ignore_broadcast_ssid=0\n\
wpa=#\n\
wpa_passphrase=#########wpa_passphrase_lenth_must_more_than_7_and_less_than_63\n\
wpa_key_mgmt=WPA-PSK\n\
wpa_pairwise=CCMP\n\
rsn_pairwise=CCMP\n\
wpa_group_rekey=86400\n\
wpa_gmk_rekey=86400\n\
wpa_ptk_rekey=86400\n\
driver="DRIVER"\n\
preamble=1\n\
hw_mode=g\n"
                                    "ieee80211n=1\n"
                                    "ht_capab=[SHORT-GI-20]\n\
wme_enabled=1\n\
device_name="DRIVER_NAME"\n\
manufacturer=Realtek\n\
logger_syslog=-1\n\
logger_syslog_level=2\n\
logger_stdout=-1\n\
logger_stdout_level=2\n\
ctrl_interface=/var/run/hostapd\n\
ctrl_interface_group=0\n\
beacon_int=100\n\
dtim_period=1\n\
max_num_sta=4\n\
rts_threshold=2347\n\
fragm_threshold=2346\n\
wmm_enabled=1\n\
wmm_ac_bk_cwmin=4\n\
wmm_ac_bk_cwmax=10\n\
wmm_ac_bk_aifs=7\n\
wmm_ac_bk_txop_limit=0\n\
wmm_ac_bk_acm=0\n\
wmm_ac_be_aifs=3\n\
wmm_ac_be_cwmin=4\n\
wmm_ac_be_cwmax=10\n\
wmm_ac_be_txop_limit=0\n\
wmm_ac_be_acm=0\n\
wmm_ac_vi_aifs=2\n\
wmm_ac_vi_cwmin=3\n\
wmm_ac_vi_cwmax=4\n\
wmm_ac_vi_txop_limit=94\n\
wmm_ac_vi_acm=0\n\
wmm_ac_vo_aifs=2\n\
wmm_ac_vo_cwmin=2\n\
wmm_ac_vo_cwmax=3\n\
wmm_ac_vo_txop_limit=47\n\
wmm_ac_vo_acm=0\n\
eapol_key_index_workaround=0\n\
eap_server=0\n\
own_ip_addr=192.168.1.1\n";

#elif TCFG_RTL8822ES_10M_ENABLE

static char hostapd_config_file[] =
    "interface=wlan0\n\
ssid=####SSID_LENTH_MUST_LESS_THAN_32\n\
channel=36\n\
macaddr_acl=0\n\
auth_algs=3\n\
ignore_broadcast_ssid=0\n\
wpa=#\n\
wpa_passphrase=#########wpa_passphrase_lenth_must_more_than_7_and_less_than_63\n\
wpa_key_mgmt=WPA-PSK\n\
wpa_pairwise=CCMP\n\
rsn_pairwise=CCMP\n\
wpa_group_rekey=86400\n\
wpa_gmk_rekey=86400\n\
wpa_ptk_rekey=86400\n\
driver=rtl871xdrv\n\
preamble=1\n\
hw_mode=a\n"
    "ieee80211n=0\n"
    "ht_capab=[SHORT-GI-20]\n\
wme_enabled=1\n\
device_name=RTL818x\n\
manufacturer=Realtek\n\
logger_syslog=-1\n\
logger_syslog_level=2\n\
logger_stdout=-1\n\
logger_stdout_level=2\n\
ctrl_interface=/var/run/hostapd\n\
ctrl_interface_group=0\n\
beacon_int=100\n\
dtim_period=1\n\
max_num_sta=4\n\
rts_threshold=2347\n\
fragm_threshold=2346\n\
wmm_enabled=1\n\
wmm_ac_bk_cwmin=4\n\
wmm_ac_bk_cwmax=10\n\
wmm_ac_bk_aifs=7\n\
wmm_ac_bk_txop_limit=0\n\
wmm_ac_bk_acm=0\n\
wmm_ac_be_aifs=3\n\
wmm_ac_be_cwmin=4\n\
wmm_ac_be_cwmax=10\n\
wmm_ac_be_txop_limit=0\n\
wmm_ac_be_acm=0\n\
wmm_ac_vi_aifs=2\n\
wmm_ac_vi_cwmin=3\n\
wmm_ac_vi_cwmax=4\n\
wmm_ac_vi_txop_limit=94\n\
wmm_ac_vi_acm=0\n\
wmm_ac_vo_aifs=2\n\
wmm_ac_vo_cwmin=2\n\
wmm_ac_vo_cwmax=3\n\
wmm_ac_vo_txop_limit=47\n\
wmm_ac_vo_acm=0\n\
eapol_key_index_workaround=0\n\
eap_server=0\n\
own_ip_addr=192.168.1.1\n";

#endif


/*wps channel only support 1 5 9 */

u8 set_sta_scan_ch_num()
{
    return 0;// 0为使用默认
}
u8 set_sta_scan_only_ch()
{
    return 0;// 0为使用默认
}
static char wps_hostapd_config_file[] = \
                                        "interface=wlan0\n\
ctrl_interface=/var/run/hostapd\n\
ctrl_interface_group=0\n\
macaddr_acl=0\n\
rsn_pairwise=CCMP\n\
wpa_gmk_rekey=86400\n\
wpa_ptk_rekey=86400\n\
preamble=1\n\
ht_capab=[SHORT-GI-20]\n\
logger_syslog=-1\n\
logger_syslog_level=2\n\
logger_stdout=-1\n\
logger_stdout_level=2\n\
dtim_period=1\n\
rts_threshold=2347\n\
fragm_threshold=2346\n\
wmm_enabled=1\n\
wmm_ac_bk_cwmin=4\n\
wmm_ac_bk_cwmax=10\n\
wmm_ac_bk_aifs=7\n\
wmm_ac_bk_txop_limit=0\n\
wmm_ac_bk_acm=0\n\
wmm_ac_be_aifs=3\n\
wmm_ac_be_cwmin=4\n\
wmm_ac_be_cwmax=10\n\
wmm_ac_be_txop_limit=0\n\
wmm_ac_be_acm=0\n\
wmm_ac_vi_aifs=2\n\
wmm_ac_vi_cwmin=3\n\
wmm_ac_vi_cwmax=4\n\
wmm_ac_vi_txop_limit=94\n\
wmm_ac_vi_acm=0\n\
wmm_ac_vo_aifs=2\n\
wmm_ac_vo_cwmin=2\n\
wmm_ac_vo_cwmax=3\n\
wmm_ac_vo_txop_limit=47\n\
wmm_ac_vo_acm=0\n\
eapol_key_index_workaround=0\n\
own_ip_addr=192.168.1.1\n\
ssid=wifi_camera_ac54_wlan_direct\n\
channel=06\n\
wpa=2\n\
wpa_passphrase=12345678\n\
auth_algs=3\n\
ignore_broadcast_ssid=0\n\
eap_server=1\n\
wps_state=2\n\
uuid=12345678-9abc-def0-1234-56789abcdef0\n\
device_name=wifi_camera_ac54_wlan_direct\n\
manufacturer=Realtek\n\
model_name=RTW_SOFTAP\n\
model_number=WLAN_ES\n\
serial_number=12345\n\
device_type=6-0050F204-1\n\
os_version=01020300\n\
config_methods=label display push_button keypad\n\
driver=rtl871xdrv\n\
beacon_int=100\n\
hw_mode=g\n\
ieee80211n=1\n\
wme_enabled=1\n\
wpa_key_mgmt=WPA-PSK\n\
wpa_pairwise=CCMP\n\
max_num_sta=4\n\
wpa_group_rekey=86400\n";


const char *get_hostapd_config_file(unsigned char enable_wps)
{
#if (TCFG_RTL8189E_ENABLE   || \
	 TCFG_RTL8822ES_10M_ENABLE  || \
	 TCFG_RTL8733BS_ENABLE  || \
	 TCFG_RTL8822CS_ENABLE)
    if (enable_wps) {
        return wps_hostapd_config_file;
    } else {
        return hostapd_config_file;
    }
#endif
    return (char *)0;
}


#if TCFG_RTL8822CS_ENABLE

static char rtw_8822cs_cache_efuse[1024] = {
    0x29, 0x81, 0x00, 0x8F, 0xFF, 0x20, 0x28, 0x00, 0x9A, 0x04, 0xED, 0x75, 0x10, 0x0F, 0xF1, 0xEB,
    0x57, 0x50, 0x54, 0x59, 0x59, 0x59, 0x4D, 0x4D, 0x4E, 0x52, 0x52, 0x26, 0x00, 0x00, 0xFF, 0xFF,
    0xFF, 0xFF, 0x54, 0x53, 0x52, 0x52, 0x54, 0x4F, 0x4A, 0x4B, 0x4C, 0x4C, 0x4E, 0x4E, 0x4E, 0x4E,
    0x26, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xE0, 0xA0, 0xFF, 0xFF, 0x61, 0x62, 0x62, 0x63, 0x63, 0x63,
    0x56, 0x56, 0x57, 0x59, 0x59, 0x26, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x4E, 0x4D, 0x4D, 0x4D,
    0x53, 0x4F, 0x4C, 0x4B, 0x4A, 0x4A, 0x49, 0x49, 0x49, 0x49, 0x26, 0x00, 0xFF, 0xFF, 0x00, 0xFF,
    0xE0, 0xA0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x55, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x21, 0x00, 0x10, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x33, 0x04, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x1E, 0x20, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF0, 0x94, 0x65, 0xD3, 0x58, 0xC5, 0xFF, 0xFF, 0xCD, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xC0, 0xC0, 0xFC, 0xA0, 0xD8, 0xD8, 0xFD, 0xFF, 0x35, 0x8C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFE, 0xDF, 0x01, 0x23, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x4C, 0x02, 0x22, 0xC8, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,/*mac*/0x7C, 0xA7, 0xB0, 0xC7, 0xFD, 0xBE, /*end of mac*/
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

#define MAC_ADDR_OFFSET 0X16A
#define GET_RTW_CACHE_EFUSE_ADDR	rtw_8822cs_cache_efuse

#define MAC_ADDR_LEN 6

#define PATHA_CCK_POWER_IDX_OFFSET 0X10
#define PATHA_CCK_POWER_IDX_LEN 6

#define PATHA_BW40_1S_POWER_IDX_OFFSET 0x16
#define PATHA_BW40_1S_POWER_IDX_LEN 5

#define PATHA_BW20_1S_DIFF_OFDM_1_POWER_IDX_DIFF_OFFSET 0x1B
#define PATHA_BW20_1S_DIFF_OFDM_1_POWER_IDX_DIFF_LEN 1

static int get_flash_mac_addr(char mac[6])
{
    if (syscfg_read(EXT_WIFI_MAC_IDX, mac, MAC_ADDR_LEN) == MAC_ADDR_LEN) {
        printf("get_flash_mac_addr valid [%x:%x:%x:%x:%x:%x] \r\n",
               (unsigned char)mac[0], (unsigned char)mac[1], (unsigned char)mac[2], (unsigned char)mac[3], (unsigned char)mac[4], (unsigned char)mac[5]);

        return 0;
    }

    return -1;

}

char *get_rtw_cache_efuse(void)
{
    return 0;

    char macaddr[MAC_ADDR_LEN];
    if (get_flash_mac_addr(macaddr) == 0) {
        memcpy(&GET_RTW_CACHE_EFUSE_ADDR[MAC_ADDR_OFFSET], macaddr, MAC_ADDR_LEN);
    } else {
        void get_random_bytes(char *buf, int nbytes);
        get_random_bytes(macaddr, MAC_ADDR_LEN);
        macaddr[0] &= ~((1 << 0) | (1 << 1));
        memcpy(&GET_RTW_CACHE_EFUSE_ADDR[MAC_ADDR_OFFSET], macaddr, MAC_ADDR_LEN);
        syscfg_write(EXT_WIFI_MAC_IDX, macaddr, MAC_ADDR_LEN);
        printf("wifi use random mac[%x:%x:%x:%x:%x:%x] \r\n", (unsigned char)macaddr[0], (unsigned char)macaddr[1], (unsigned char)macaddr[2], (unsigned char)macaddr[3], (unsigned char)macaddr[4], (unsigned char)macaddr[5]);
    }
    return GET_RTW_CACHE_EFUSE_ADDR;
}

int get_rtw_cache_mac_addr(char *mac)
{
    if (!mac) {
        return 0;
    }
    char macaddr[MAC_ADDR_LEN];
    if (get_flash_mac_addr(macaddr) == 0) {
        memcpy(mac, macaddr, MAC_ADDR_LEN);
    } else {
        void get_random_bytes(char *buf, int nbytes);
        get_random_bytes(macaddr, MAC_ADDR_LEN);
        macaddr[0] &= ~((1 << 0) | (1 << 1));
        memcpy(mac, macaddr, MAC_ADDR_LEN);
        syscfg_write(EXT_WIFI_MAC_IDX, macaddr, MAC_ADDR_LEN);
        printf(" wifi use random mac[%x:%x:%x:%x:%x:%x] \r\n", (unsigned char)macaddr[0], (unsigned char)macaddr[1], (unsigned char)macaddr[2], (unsigned char)macaddr[3], (unsigned char)macaddr[4], (unsigned char)macaddr[5]);
    }
    return MAC_ADDR_LEN;
}

void set_rtw_cache_efuse(char *buf, unsigned int len)
{
    if (len > sizeof(GET_RTW_CACHE_EFUSE_ADDR)) {
        printf("set_rtw_cache_efuse file size error!!!!, %u, while1", len);
        while (1);
    }
    memcpy(GET_RTW_CACHE_EFUSE_ADDR, buf, len);

    //put_buf(GET_RTW_CACHE_EFUSE_ADDR, len);
}

void set_rtw_cache_efuse_macaddr(char *macaddr[6])
{
    memcpy(&GET_RTW_CACHE_EFUSE_ADDR[MAC_ADDR_OFFSET], macaddr, MAC_ADDR_LEN);

    //第一个字节的BIT0和BIT1不能够为1, 另外不能够全0xff和全0x00
    GET_RTW_CACHE_EFUSE_ADDR[MAC_ADDR_OFFSET] &= ~((1 << 0) | (1 << 1));
}

void set_rtw_cache_efuse_power_index(void)
{
    memset(&GET_RTW_CACHE_EFUSE_ADDR[PATHA_CCK_POWER_IDX_OFFSET], 0x28, PATHA_CCK_POWER_IDX_LEN);
    memset(&GET_RTW_CACHE_EFUSE_ADDR[PATHA_BW40_1S_POWER_IDX_OFFSET], 0x28, PATHA_BW40_1S_POWER_IDX_LEN);
    memset(&GET_RTW_CACHE_EFUSE_ADDR[PATHA_BW20_1S_DIFF_OFDM_1_POWER_IDX_DIFF_OFFSET], 0x03, PATHA_BW20_1S_DIFF_OFDM_1_POWER_IDX_DIFF_LEN);
}

#endif

#endif

