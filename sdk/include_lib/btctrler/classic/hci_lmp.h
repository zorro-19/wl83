#ifndef LMP_API_H
#define LMP_API_H


#include "generic/typedef.h"

struct a2dp_media_frame {
    u8 *packet;
    u32 clkn;
    u8 coding_type;
};
enum {
    SEND_ACL_ESCO_MODE = 1,
    SEND_ACL_SHARE_MODE,
    SEND_ACL_A2DP_SOURCE_MODE = 0xfa,

};

struct lp_ws_t {
    u16 lrc_ws_inc;
    u16 lrc_ws_init;
    u16 bt_osc_ws_inc;
    u16 bt_osc_ws_init;
    u8  osc_change_mode;
};

void lmp_private_a2dp_start(void *_conn);

void lmp_private_a2dp_stop(void *_conn);

int lmp_private_is_clearing_a2dp_packet(void *_conn);

int lmp_private_a2dp_channel_exist(void *_conn);

int lmp_private_get_sbc_remain_time(void *_conn, u8 include_tws);

void lmp_private_set_media_type(u8 *addr, u8 type);

u8 lmp_private_get_media_open_state_for_addr(u8 *addr);
u8 lmp_private_get_media_type_for_addr(u8 *addr);
u8 lmp_private_get_media_type(void *conn);
u32 lmp_private_get_media_sample_rate(void *conn);
u8 lmp_private_get_media_bit_wide(void *_conn);
u16 lmp_private_get_media_codec_version(void *_conn);

void *lmp_private_open_sbc_channel(u8 *addr);

void lmp_private_set_a2dp_rx_notify(void *_conn, void *priv, void (*notify)(void *));

void lmp_private_free_sbc_packet(void *_conn, void *packet);

int lmp_private_get_sbc_data_len(void *_conn);

int lmp_private_get_rx_buffer_size();

void lmp_private_set_max_rx_buf_persent(u8 *addr, int persent);

void *lmp_private_fetch_sbc_packet(void *_conn, int *len, void *_prev, int);

int lmp_private_get_sbc_packet_num(void *_conn);
void lmp_private_close_sbc_channel(void *_conn);

void lmp_private_a2dp_mute(u8 *addr);

void lmp_private_a2dp_unmute(void *addr);

bool lmp_private_a2dp_is_mute(void *addr);

int lmp_private_get_sbc_packet(void *_conn, struct a2dp_media_frame *frame, int block);

void lmp_private_put_sbc_packet(void *_conn, void *packet);

u8 *lmp_private_get_tx_packet_buffer(int size);

int lmp_private_clear_a2dp_packet(void *_conn, u16 seqn_number);


u8 *lmp_get_esco_link_addr(void);
u8 check_esco_conn_exist(u8 *current_addr);
int lmp_private_get_esco_packet_type();

u8 check_esco_conn_exist(u8 *current_addr);
void *lmp_private_get_esco_packet(int *len, u32 *hash);

void lmp_private_free_esco_packet(void *packet);

int lmp_private_send_esco_packet(void *priv, u8 *packet, int len);

int lmp_private_get_esco_tx_packet_num();

void lmp_esco_set_rx_notify(u8 *addr, void *priv, void (*notify)(void *));

u8 *lmp_private_remote_addr_for_handler(int handle);

u16 lmp_private_handler_for_remote_addr(u8 *addr, int link_type);

int lmp_private_get_rx_buffer_total_size(void *_conn);

int lmp_private_get_rx_buffer_remain_size(void *_conn);

void lmp_hci_private_hold_acl_packet(u8 *packet);

void lmp_hci_private_free_acl_packet(u8 *packet);

void lmp_hci_private_try_free_acl_packet(u8 *packet);

int lmp_hci_send_packet(u8 *packet, int len, u8 mode);
u16 lmp_private_get_acl_u_tx_packet_num(void *_conn, int mode);
void lmp_private_del_acl_u_tx_packet(void *_conn, u8 tx_mode, u32 del_num);
u16 lmp_private_get_acl_u_tx_packet_len(void *_conn, int mode);

int lmp_hci_send_packet_standard(const u8 *packet, int len);
int lmp_hci_send_broadcase_packet_standard(const u8 *packet, int len);

int lmp_hci_reset();

int lmp_hci_write_scan_enable(u8 enable);
int lmp_hci_write_quick_scan_enable(u8 enable);

void lmp_hci_write_class_of_device(int dev_class);

void lmp_hci_write_local_name(const char *name);
void lmp_hci_write_local_priv_version(const char *ic_verson, const char *priv_version, u8 *tws_local_addr);

void lmp_hci_write_local_address(const u8 *addr);

void lmp_hci_write_simple_pairing_mode(u8 enable);

void lmp_hci_write_super_timeout(u16 timeout);
void lmp_hci_write_page_timeout(u16 timeout);
void lmp_hci_write_tws_internal_addr(u8 *internal_addr_local, u8 *internal_addr_remote);

void lmp_hci_write_link_supervision_timeout(u16 handle, int);

int lmp_hci_write_le_host_support(int features);

int lmp_hci_read_pin_type();

void lmp_hci_write_build_publickey(u16 mode);

void lmp_hci_set_pin_code(const char *code, u8 len);

void lmp_hci_pin_code_request_reply(u8 *addr, u8 len, u8 *pin_code);

void lmp_hci_pin_code_request_negative_reply(u8 *addr);

int lmp_hci_write_pin_type(u8 type);

int lmp_hci_set_connection_encryption(u16 handle, int enable);

void lmp_hci_io_capability_request_reply(u8 *addr, u8 io_cap, u8 oob_data, u8 auth_req);

void lmp_hci_user_confirmation_request_reply(u8 *address);

void lmp_hci_user_confirmation_request_negative_reply(u8 *addr);

int lmp_hci_disconnect(u16 handle, u8 reason);
int lmp_hci_test_key_cmd(u8 cmd, u16 handle);
int lmp_hci_send_user_info_cmd(u32 info, u16 handle);

void lmp_hci_accept_connection_request(u8 *addr, u8 role);

void lmp_hci_accept_sco_connection_request(u8 *addr, u32 tx_bandwidth,
        u32 rx_bandwidth, u16 max_latency, u16 content_format,
        u8 retransmission, u16 packey_type);

void lmp_hci_reject_connection_request(u8 *addr, u8 reason);

void lmp_hci_switch_role_command(u8 *addr, u8 role);

void lmp_hci_authentication_requested(u8 *addr);

void lmp_hci_link_key_request_reply(u8 *addr, u8 *link_key);

void lmp_hci_link_key_request_negative_reply(u8 *addr);

void lmp_hci_write_default_link_policy_settings(u16 setting);

void lmp_hci_release_packet(u8 *packet);

void lmp_hci_create_connection(const u8 *addr, u16 packet_type,
                               u8 repetition_mode, u8 reserved,
                               u16 clk_offset, u8 allow_role_switch);

void lmp_hci_connection_cancel(u8 *addr);;

void lmp_hci_cancel_page();
void lmp_hci_inquiry(int lap, u8 length, u8 num);
void lmp_hci_cancel_inquiry();
void lmp_hci_sniff_mode_command(u16 handle, u16 max_interval, u16 min_interval, u16 attempt, u16 timeout);
void lmp_hci_exit_sniff_mode_command(u16 handle);

void lmp_hci_host_num_of_completed_packets(u16 handle, u16 num_of_completed_packet);

int lmp_hci_read_remote_version_information(u16 handle);

void lmp_hci_read_remote_supported_features(u16 handle);

void lmp_hci_read_remote_extended_features(u16 handle, u8 page_num);

void lmp_hci_role_discovery(u16 handle);

void lmp_hci_read_clock_offset(u16 handle);
void lmp_hci_change_conn_packet_type(u16 handle, u16 type);

void lmp_hci_tx_qos_req(u16 handle);
void lmp_hci_read_link_policy_settings(u16 handle);
void lmp_hci_write_link_policy_settings(u16 handle, u16 policy);

void lmp_hci_remote_name_request(u8 *addr, u8 page_scan_repetition_mode, u16 clk_offset);

void lmp_set_sniff_establish_by_remote(u8 enable);

void lmp_set_sniff_disable(void);


u8 lmp_hci_read_local_supported_features(int octet);

void lmp_hci_write_local_supported_features(u8 features, int octet);


u8 lmp_standard_connect_check(void);

void lmp_hci_send_keypress_notification(u8 *addr, u8 key);
void lmp_hci_user_keypress_request_reply(u8 *addr, u32 key);
void lmp_hci_user_keypress_request_negative_reply(u8 *addr, u8 key);


void lmp_hci_set_role_switch_supported(bool enable);
void lmp_hci_tx_channel_chassification(u8 *map);


extern int lmp_speak_mic_send_internal(void *priv, u8 *data, int len);

u8 *get_tws_internal_addr(int channel);

extern int lmp_private_esco_suspend_resume(int flag);;

void user_set_tws_box_mode(u8 mode);


void bt_set_tx_power(u8 txpower);


void bredr_bulk_change(u8 mode);


extern u8 get_bredr_link_state();

extern u32 get_bt_slot_time(u8 type, u32 time, int *ret_time, int (*local_us_time)(void));
extern u32 get_sync_rec_instant_us_time();
extern u8 tws_remote_state_check(void);
extern void tws_remote_state_clear(void);
extern void user_set_tws_box_mode(u8 mode);


extern void bredr_fcc_init(u8 mode, u8 fre);
extern void bredr_set_dut_enble(u8 en, u8 phone);



struct link_fix_rx_result {
    s8 rx_rssi;
    u32 rx_err_b;  //接收到err bit
    u32 rx_sum_b;  //接收到正确bit
    u32 rx_perr_p;  //接收到crc 错误 包数
    u32 rx_herr_p;  //接收到crc 以外其他错误包数
    u32 rx_invail_p; //接收到crc错误bit太多的包数，丢弃不统计到err bit中

    u32 rx_right_sum_p;  //接收到正确包数
    u32 rx_err_sum_p;  //接收到错误包数
};

#define DH1_1        0
#define DH3_1        1
#define DH5_1        2
#define DH1_2        3
#define DH3_2        4
#define DH5_2        5

int link_fix_tx_enable(u8 *remote_addr, u8 fre, u8 packet_type, u16 payload, u16 payload_len, u8 pwr);
int link_fix_rx_enable(u8 *remote_addr, u8 fre, u8 packet_type, u16 payload, u16 payload_len, u8 pwr);
void link_fix_txrx_disable();
void link_fix_rx_update_result(struct link_fix_rx_result *result);
void link_fix_rx_dump_result();
void bt_lmp_store_16(uint8_t *buffer, uint16_t pos, uint16_t value);
extern u8 *get_audio_share_master_addr();
extern u8 *get_audio_share_slave_addr();
extern bool is_master_device_tws_share_conn(u8 *addr);
extern bool is_slave_device_tws_share_conn(u8 *addr);
extern void lmp_private_close_share_sbc_channel(u8 *addr);
extern void *lmp_private_open_share_sbc_channel(u8 *addr, u16 channel_remote_cid, u8 codec_type, u16 simple);
extern void set_donlge_quick_sniff_run_slot(int quick_sniff_run_slot);
extern bool is_priority_device_tws_share_conn(u8 *addr);
extern bool is_master_device_tws_share_conn_tx(u8 *addr);

void lp_winsize_init(const struct lp_ws_t *lp);

void bt_max_pwr_set(u8 pwr, u8 pg_pwr, u8 iq_pwr, u8 ble_pwr);
void lmp_esco_set_tx_notify(u8 *addr, void *priv, void (*notify)(void *, u32 clk));

int lmp_private_get_speak_mic_data_len() ;
u32 lmp_media_get_speak_mic_packet_num();
void lmp_private_free_speak_mic_packet(void *packet);
void *lmp_private_get_speak_mic_packet(int *len, u32 *hash);
void lmp_jl_dongle_mic_set_rx_notify(u8 *addr, void *priv, void (*notify)(void *));
int check_a2dp_source_send_packet_limit_cnt(u8 *addr, u8 dump_limit);

#endif
