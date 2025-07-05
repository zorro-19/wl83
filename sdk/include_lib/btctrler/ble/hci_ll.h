/*********************************************************************************************
    *   Filename        : hci_ll.h

    *   Description     : 提供Vendor Host 直接调用Controller API LL Part

    *   Author          : Bingquan

    *   Email           : bingquan_cai@zh-jieli.com

    *   Last modifiled  : 2018-12-04 11:58

    *   Copyright:(c)JIELI  2011-2017  @ , All Rights Reserved.
*********************************************************************************************/
#ifndef _HCI_LL_H_
#define _HCI_LL_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

#include "typedef.h"

#if 0
// LE CONTROLLER COMMANDS
#define HCI_LE_CREATE_CONNECTION_CANCEL                     0x0e
#define HCI_LE_READ_ISO_TX_SYNC                             0x0061
#define HCI_LE_SET_CIG_PARAMS                               0x0062
#define HCI_LE_SETUP_ISO_DATA_PATH                          0x006E
#define HCI_LE_CREATE_BIG                                   0x0068
#define HCI_LE_SET_EXTENDED_ADVERTISING_ENABLE              0x0039
#define HCI_LE_PERIODIC_ADVERTISING_TERMINATE_SYNC          0x0046
#define HCI_LE_TERMINATE_BIG                                0x006A

// LE EVENTS
#define HCI_LE_CIS_ESTABLISHED_EVENT                        0x19
#define HCI_LE_CIS_REQUEST_EVENT                            0x1A
#define HCI_LE_CREATE_BIG_COMPLETE_EVENT                    0x1B
#define HCI_SUBEVENT_LE_BIG_INFO_ADV_REPORT_EVT             0x22
#define HCI_SUBEVENT_LE_TERMINATE_BIG_CMPL_EVT              0x1C
#define HCI_SUBEVENT_LE_BIG_SYNC_EST_EVT                    0x1D
#define HCI_SUBEVENT_LE_BIG_SYNC_LOST_EVT                   0x1E
#define HCI_EVENT_NUMBER_OF_COMPLETED_PACKETS               0x13
#define HCI_SUBEVENT_LE_ADVERTISING_REPORT                  0x02

#endif

#define HCI_LE_CIS_ESTABLISHED_EVENT                        0x19
#define HCI_LE_CIS_REQUEST_EVENT                            0x1A
#define HCI_LE_CREATE_BIG_COMPLETE_EVENT                    0x1B

// Controller Error Codes
#define CONNECTION_TERMINATED_BY_LOCAL_HOST                 0x16
// #define CONNECTION_FAILED_TO_BE_ESTABLISHED                 0x3e

//使用的例子枚举
enum {
    NULL_SET = 0,
    BIG_RX,
    BIG_TX,
    CIG_RX,
    CIG_TX,
    SCAN,
    ADV,
    EXT_ADV,
    EXT_SCAN,
    HEART_SET_TX,
    HEART_SET_RX,
};

enum {
    LL_EVENT_SUPERVISION_TIMEOUT,
    LL_EVENT_RX,
    LL_EVENT_ACL_TX_POST,
};

typedef struct {
    u8 Own_Address_Type: 2;
    u8 Adv_Filter_Policy: 2;
    u8 Scan_Filter_Policy: 2;
    u8 initiator_filter_policy: 2;
} hci_ll_param_t;

/*! \brief      LE Advertising report event. */
typedef enum {
    EVT_TYPE_ADV_IND,
    EVT_TYPE_ADV_DIRECT_IND,
    EVT_TYPE_ADV_SCAN_IND,
    EVT_TYPE_ADV_NONCONN_IND,
    EVT_TYPE_SCAN_RSP,
} le_evt_type_e;

typedef struct {
    uint8_t         Subevent_Code;
    uint8_t         Num_Reports;
    uint8_t         Event_Type;
    uint8_t         Address_Type;
    uint8_t         Address[6];
    uint8_t         Data_Length;
    uint8_t         Data[0];
} _GNU_PACKED_ le_adv_report_evt_t;

/*! \brief      LE Extended Advertising report event. */
typedef union {
    struct {
        uint16_t Connectable_advertising    : 1,
                 Scannable_advertising      : 1,
                 Directed_advertising       : 1,
                 Scan_response              : 1,
                 Legacy_adv_PDUs_used       : 1,
                 Data_status                : 2,
                 All_other_bits             : 9;
    };

    uint16_t event_type;
} _GNU_PACKED_ le_evt_type_t;

typedef struct {
    uint8_t         Subevent_Code;
    uint8_t         Num_Reports;
    le_evt_type_t   Event_Type;
    uint8_t         Address_Type;
    uint8_t         Address[6];
    uint8_t         Primary_PHY;
    uint8_t         Secondary_PHY;
    uint8_t         Advertising_SID;
    uint8_t         Tx_Power;
    uint8_t         RSSI;
    uint16_t        Periodic_Advertising_Interval;
    uint8_t         Direct_Address_Type;
    uint8_t         Direct_Address[6];
    uint8_t         Data_Length;
    uint8_t         Data[0];
} _GNU_PACKED_ le_ext_adv_report_evt_t;

struct __periodic_adv_report_event {
    u8  Subevent_Code;
    u16 Sync_Handle;
    u8  Tx_Power;
    u8  RSSI;
    u8  Unused;
    u8  Data_Status;
    u8  Data_Length;
    u8  Data[0];
} _GNU_PACKED_ ;

struct __periodic_creat_sync {
    u8 Filter_Policy;
    u8 Advertising_SID;
    u8 Advertising_Address_Type;
    u8 Advertiser_Address[6];
    u8 Skip[2];
    u8 Sync_Timeout[2];
    u8 Unused;
} _GNU_PACKED_;

/*! \brief      LE Set Scan Parameters. */
typedef struct {
    uint8_t         LE_Scan_Type;
    uint16_t        LE_Scan_Interval;
    uint16_t        LE_Scan_Window;
    uint8_t         Own_Address_Type;
    uint8_t         Scanning_Filter_Policy;
} _GNU_PACKED_ le_set_scan_param_t;

typedef struct {
    uint8_t         Own_Address_Type;
    uint8_t         Scanning_Filter_Policy;
    uint8_t         Scanning_PHYs;
    uint8_t         Scan_Type;
    uint16_t        Scan_Interval;
    uint16_t        Scan_Window;
} _GNU_PACKED_ le_ext_scan_param_lite_t;

struct __ext_scan_param {
    u8 Own_Address_Type;
    u8 Scanning_Filter_Policy;
    u8 Scanning_PHYs;
    struct __scan_phy_param {
        u8  Scan_Type;
        u16 Scan_Interval;
        u16 Scan_Window;
    } _GNU_PACKED_ scan_phy_param[0];
} _GNU_PACKED_;

struct __ext_scan_enable {
    u8  Enable;
    u8  Filter_Duplicates;
    u16 Duration;
    u16 Period;
} _GNU_PACKED_;

/*! \brief      LE Set Extended Advertising Parameters. */
typedef struct {
    uint8_t         Advertising_Handle;
    uint16_t        Advertising_Event_Properties;
    uint8_t         Primary_Advertising_Interval_Min[3];
    uint8_t         Primary_Advertising_Interval_Max[3];
    uint8_t         Primary_Advertising_Channel_Map;
    uint8_t         Own_Address_Type;
    uint8_t         Peer_Address_Type;
    uint8_t         Peer_Address[6];
    uint8_t         Advertising_Filter_Policy;
    uint8_t         Advertising_Tx_Power;
    uint8_t         Primary_Advertising_PHY;
    uint8_t         Secondary_Advertising_Max_Skip;
    uint8_t         Secondary_Advertising_PHY;
    uint8_t         Advertising_SID;
    uint8_t         Scan_Request_Notification_Enable;
} _GNU_PACKED_ le_set_ext_adv_param_t;

#define ADVERTISING_DATE_LEN   96
/*! \brief      LE Set Extended Advertising Data. */
typedef struct {
    uint8_t         Advertising_Handle;
    uint8_t         Operation;
    uint8_t         Fragment_Preference;
    uint8_t         Advertising_Data_Length;
    uint8_t         Advertising_Data[ADVERTISING_DATE_LEN];
} _GNU_PACKED_ le_set_ext_adv_data_t;

/*! \brief      LE Set Extended Advertising Enable. */
typedef struct {
    uint8_t         Enable;
    uint8_t         Number_of_Sets;
    uint8_t         Advertising_Handle;
    uint16_t        Duration;
    uint8_t         Max_Extended_Advertising_Events;
} _GNU_PACKED_ le_set_ext_adv_en_t;

struct periodic_advertising_param {
    u8 Advertising_Handle;
    u16 Periodic_Advertising_Interval_Min;
    u16 Periodic_Advertising_Interval_Max;
    u16 Periodic_Advertising_Properties;
} _GNU_PACKED_;

struct periodic_advertising_data {
    u8 Advertising_Handle;
    u8 Operation;
    u8 Advertising_Data_Length;
    u8 Advertising_Data[255];
} _GNU_PACKED_;

typedef struct {
    uint8_t Advertising_Handle;
    uint8_t Operation;
    uint8_t Advertising_Data_Length; // 0 to 252
    uint8_t Advertising_Data[0];
} _GNU_PACKED_ le_set_prd_adv_data_t;

struct periodic_advertising_enable {
    u8  Enable;
    u8  Advertising_Handle;
} _GNU_PACKED_;

typedef struct {
    uint16_t Sync_Handle;
} _GNU_PACKED_ periodic_adv_terminate_sync;

/*! \brief      HCI ACL Data packets */
typedef struct {
    uint16_t        Handle              : 12;
    uint16_t        PB_Flag             : 2;
    uint16_t        BC_Flag             : 2;
    uint16_t        Data_Total_Length;

    uint8_t         Data[0];
} _GNU_PACKED_ hci_acl_data_packets_t ;

/*! \brief      LE Set CIG Parameters */
typedef struct {
    uint8_t         GIG_ID;
    uint8_t         SDU_Interval_C_To_P[3];
    uint8_t         SDU_Interval_P_To_C[3];
    uint8_t         Worst_Case_SCA;
    uint8_t         Packing;
    uint8_t         Framing;
    uint16_t        Max_Transport_Latency_C_To_P;
    uint16_t        Max_Transport_Latency_P_To_C;
    uint8_t         CIS_Count;
    struct le_cis_param_t {
        uint8_t         CIS_ID;
        uint16_t        Max_SDU_C_To_P;
        uint16_t        Max_SDU_P_To_C;
        uint8_t         PHY_C_To_P;
        uint8_t         PHY_P_To_C;
        uint8_t         RTN_C_To_P;
        uint8_t         RTN_P_To_C;
    } _GNU_PACKED_ param[0];
} _GNU_PACKED_ le_set_cig_param_t;

/*! \brief      LE Create CIS */
typedef struct {
    uint8_t         CIS_Count;
    struct le_cis_hdl_t {
        uint16_t        CIS_Connection_Handle;
        uint16_t        ACL_Connection_Handle;
    } _GNU_PACKED_ param[0];
} _GNU_PACKED_ le_create_cis_t;

/*! \brief      LE Remove CIS */
typedef struct {
    uint8_t         CIG_ID;
} _GNU_PACKED_ le_remove_cig_t;

/*! \brief      LE Setup ISO Data Path */
typedef struct {
    uint16_t        Connection_Handle;
    uint8_t         Data_Path_Direction;
    uint8_t         Data_Path_ID;
    struct {
        uint8_t         Coding_Format;
        uint16_t        Company_Identifier;
        uint16_t        Vendor_ID;
    } _GNU_PACKED_ Codec_ID;
    uint8_t         Controller_Delay[3];
    uint8_t         Codec_Configuratin_Length;
    uint8_t         Codec_Configuratin[0];
} _GNU_PACKED_ le_setup_iso_data_path_t;

/*! \brief      LE Remove ISO Data Path */
typedef struct {
    uint16_t        Connection_Handle;
    uint8_t         Data_Path_Direction;
} _GNU_PACKED_ le_remove_iso_data_path_t;

/*! \brief      LE Create BIG */
typedef struct {
    uint8_t         BIG_Handle;
    uint8_t         Advertising_Handle;
    uint8_t         Num_BIS;
    uint8_t         SDU_Interval[3];
    uint16_t        Max_SDU;
    uint16_t        Max_Transport_Latency;
    uint8_t         RTN;
    uint8_t         PHY;
    uint8_t         Packing;
    uint8_t         Framing;
    uint8_t         Encryption;
    uint8_t         Broadcast_Code[16];
} _GNU_PACKED_ le_create_big_t;

/*! \brief      LE Terminate BIG */
typedef struct {
    uint8_t         BIG_Handle;
    uint8_t         Reason;
} _GNU_PACKED_ le_terminate_big_t;

/*! \brief      LE BIG Create Sync */
typedef struct {
    uint8_t         BIG_Handle;
    uint16_t        Sync_Handle;
    uint8_t         Encryption;
    uint8_t         Broadcast_Code[16];
    uint8_t         MSE;
    uint16_t        BIG_Sync_Timeout;
    uint8_t         Num_BIS;
    uint8_t         BIS[0];
} _GNU_PACKED_ le_big_create_sync_t;

typedef struct {
    uint8_t         BIG_Handle;
    uint16_t        Sync_Handle;
    uint8_t         Encryption;
    uint8_t         Broadcast_Code[16];
    uint8_t         MSE;
    uint16_t        BIG_Sync_Timeout;
    uint8_t         Num_BIS;
    uint8_t         BIS[2];
} _GNU_PACKED_ le_big_create_sync_lite_t;

/*! \brief      LE BIG Terminate Sync */
typedef struct {
    uint8_t         BIG_Handle;
} _GNU_PACKED_ le_big_terminate_sync_t;

/*! \brief      LE Read ISO TX Sync */
typedef struct {
    uint16_t         Connection_Handle;
} _GNU_PACKED_ le_read_iso_tx_sync_t;

/*! \brief      HCI ISO Data packets */
typedef struct {
    uint32_t        Connection_Handle    : 12;
    uint32_t        PB_Flag              : 2;
    uint32_t        TS_Flag              : 1;
    uint32_t        RFU                  : 1;
    uint32_t        ISO_Data_Load_Length : 14;
    uint32_t        RFU2                 : 2;

    uint32_t        Time_Stamp;

    uint32_t        Packet_Sequence_Num : 16;
    uint32_t        ISO_SDU_Length      : 12;
    uint32_t        RFU3                : 2;
    uint32_t        Packet_Status_Flag  : 2;

    uint8_t         ISO_SDU_Fragment[0];
} _GNU_PACKED_ hci_iso_data_packets_t ;

typedef struct {
    u32 handle  : 12;
    //0b00 frist fragment of a fragmented SDU
    //0b01 a continuation fragment of a fragmented SDU
    //0b10 a complete SDU
    //0b11 the last fragment of an SDU
    u32 pb_flag : 2;
    u32 ts_flag : 1;
    u32 rfu     : 1;
    u32 iso_data_load_length : 14;
    u32 rfu2    : 2;

    u32 time_stamp;

    u32 packet_sequence_num : 16;
    u32 iso_sdu_length      : 12;
    u32 rfu3                : 2;
    //0b00 Valid data. The complete ISO_SDU was received correctly.
    //0b01 Possibly invalid data. The contents of the ISO_SDU may contain errors or
    //  part of the ISO_SDU may be missing. This is reported as "data with possible
    //  errors".
    //0b10 Part(s) of the ISO_SDU were not received correctly. This is reported as
    //  "lost data".
    u32 packet_status_flag  : 2;

    uint8_t *iso_sdu;
} hci_iso_hdr_t;

/*! \brief      LE BIGInfo Advertising report event */
typedef struct {
    // uint8_t         Subevent_Code;
    uint16_t        Sync_Handle;
    uint8_t         Num_BIS;
    uint8_t         NSE;
    uint16_t        ISO_Interval;
    uint8_t         BN;
    uint8_t         PTO;
    uint8_t         IRC;
    uint16_t        Max_PDU;
    uint8_t         SDU_Interval[3];
    uint16_t        Max_SDU;
    uint8_t         PHY;
    uint8_t         Framing;
    uint8_t         Encryption;
} _GNU_PACKED_ le_biginfo_adv_report_evt_t;

/*! \brief      LE Create BIG Complete event */
typedef struct {
    // uint8_t         Subevent_Code;
    uint8_t         Status;
    uint32_t        BIG_Handle     : 8,
                    BIG_Sync_Delay : 24;
    uint32_t        Transport_Latency_BIG : 24,
                    PHY                   : 8;
    uint8_t         NSE;
    uint8_t         BN;
    uint8_t         PTO;
    uint8_t         IRC;
    uint16_t        Max_PDU;
    uint16_t        ISO_Interval;
    uint8_t         Num_BIS;
    uint16_t        Connection_Handle[0];
} _GNU_PACKED_ le_create_big_complete_evt_t;

/*! \brief      LE BIG Sync Established event */
typedef struct {
    // uint8_t         Subevent_Code;
    uint8_t         Status;
    uint8_t         BIG_Handle;
    uint32_t        Transport_Latency_BIG : 24,
                    NSE                   : 8;
    uint8_t         BN;
    uint8_t         PTO;
    uint8_t         IRC;
    uint16_t        Max_PDU;
    uint16_t        ISO_Interval;
    uint8_t         Num_BIS;
    uint16_t        Connection_Handle[0];
} _GNU_PACKED_ le_big_sync_established_evt_t;

/*! \brief      LE Read ISO TX Sync Return Parameters */
typedef struct {
    uint8_t         Status;
    uint16_t        Connection_Handle;
    uint16_t        Paket_Sequence_Number;
    uint32_t        TX_Time_Stamp;
    uint32_t        Time_Offset;
} _GNU_PACKED_ le_read_iso_tx_sync_ret_t;

/*! \brief      LE BIG Sync Lost event */
typedef struct {
    uint8_t         BIG_Handle;
    uint8_t         Reason;
} _GNU_PACKED_ le_big_sync_lost_evt_t;

/*! \brief      LE CIS Request event */
typedef struct {
    // uint8_t         Subevent_Code;
    uint16_t        ACL_Connection_Handle;
    uint16_t        CIS_Connection_Handle;
    uint8_t         CIG_ID;
    uint8_t         CIS_ID;
} _GNU_PACKED_ le_cis_request_evt_t;

/*! \brief      LE CIS Established event */
typedef struct {
    // uint8_t         Subevent_Code;
    uint8_t         Status;
    uint16_t        Connection_Handle;
    uint8_t         CIG_Sync_Delay[3];
    uint8_t         CIS_Sync_Delay[3];
    uint8_t         Transport_Latency_C_To_P[3];
    uint8_t         Transport_Latency_P_To_C[3];
    uint8_t         PHY_C_To_P;
    uint8_t         PHY_P_To_C;
    uint8_t         NSE;
    uint8_t         BN_C_To_P;
    uint8_t         BN_P_To_C;
    uint8_t         FT_C_To_P;
    uint8_t         FT_P_To_C;
    uint16_t        Max_PDU_C_To_P;
    uint16_t        Max_PDU_P_To_C;
    uint16_t        ISO_Interval;
} _GNU_PACKED_ le_cis_established_evt_t;

/*! \brief      LE Vendor Set BIG Transfer Param */
typedef struct {
    uint16_t        auxHdl;
    uint8_t         bigHdl;
} _GNU_PACKED_ leVendorSetBigTransParam_t;

/*! \brief      LE Vendor BIG Sync Transfer */
typedef struct {
    uint8_t         bigHdl;
    uint8_t         maxPdu;
    uint8_t         nse;
    uint8_t         phys;
    uint16_t        auxHdl;
    uint16_t        interval;
    uint16_t        syncTimeoutMs;
    uint32_t        offset;
    uint8_t         encFormat;
    uint8_t         encSr;
    uint8_t         bst_nums;
} _GNU_PACKED_ leVendorBigSyncTrans_t;

typedef struct {
    // for BIG
    struct {
        uint32_t sync_offset;   // Sync offset (uints:us).
        uint32_t tx_delay;      // Tx delay    (uints:us).
        uint32_t big_offset;    // Big offset  (uints:us).
        uint32_t aux_offset;    // Aux offset  (uints:us).
        uint8_t  adv_cnt;       // ADV counter
        uint8_t  max_pdu;       // Max PDU size(uints:octets)
        uint32_t iso_interval;  // ISO interval(uints:us).
    };

    // for CIG
    struct {
        uint32_t cig_txDelay;   // Tx delay    (uints:us).
        uint32_t cig_offset;    // Cig offset  (uints:us).
        uint8_t  cis_maxPdu;    // Max PDU size(uints:octets)
        // for ACL
        uint8_t  aclMaxPduCToP; // Central ACL max transmit PDU.
        uint8_t  aclMaxPduPToC; // Peripheral ACL max transmit PDU.
    };
} llVdrparam_t;

/*! \brief      LE Set Periodic Advertising Receive Enable command */
typedef struct {
    uint16_t        Sync_Handle;
    uint8_t         Enable;
} _GNU_PACKED_ le_set_prd_adv_receive_en_t;

/*! \brief      LE Periodic Advertising Sync Transfer command */
typedef struct {
    uint16_t        Connection_Handle;
    uint16_t        Service_Data;
    uint16_t        Sync_Handle;
} _GNU_PACKED_ le_prd_adv_sync_trans_t;

/*! \brief      LE Periodic Advertising Set Info Transfer command */
typedef struct {
    uint16_t        Connection_Handle;
    uint16_t        Service_Data;
    uint8_t         Advertising_Handle;
} _GNU_PACKED_ le_prd_adv_set_info_trans_t;

/*! \brief      LE Set Periodic Advertising Sync Transfer Parameters command */
typedef struct {
    uint16_t        Connection_Handle;
    uint8_t         Mode;
    uint16_t        Skip;
    uint16_t        Sync_Timeout;
    uint8_t         CTE_Type;
} _GNU_PACKED_ le_set_prd_adv_sync_trans_param_t;

/*! \brief      LE Set Default Periodic Advertising Sync Transfer Parameters command */
typedef struct {
    uint8_t         Mode;
    uint16_t        Skip;
    uint16_t        Sync_Timeout;
    uint8_t         CTE_Type;
} _GNU_PACKED_ le_set_default_prd_adv_sync_trans_param_t;

/*! \brief      LE Periodic Advertising Sync Transfer Received event */
typedef struct {
    // uint8_t         Subevent_Code;
    uint8_t         Status;
    uint16_t        Connection_Handle;
    uint16_t        Service_Data;
    uint16_t        Sync_Handle;
    uint8_t         Advertising_SID;
    uint8_t         Advertiser_Address_Type;
    uint8_t         Advertiser_Address[6];
    uint8_t         Advertiser_PHY;
    uint16_t        Periodic_Advertising_Interval;
    uint8_t         Advertiser_Clock_Accuracy;
    uint8_t         Num_Subevents;
    uint8_t         Subevent_Interval;
    uint8_t         Response_Slot_Delay;
    uint8_t         Response_Slot_Spacing;
} _GNU_PACKED_ le_prd_adv_sync_trans_evt_t;

//Adjust Host part API
void ll_hci_init(void);

void ll_hci_reset(void);

void ll_hci_destory(void);

void ll_hci_set_event_mask(const u8 *mask);

void ll_hci_set_name(const char *name);

void ll_hci_adv_set_params(uint16_t adv_int_min, uint16_t adv_int_max, uint8_t adv_type,
                           uint8_t direct_address_type, uint8_t *direct_address,
                           uint8_t channel_map, uint8_t filter_policy);

void ll_hci_adv_set_data(uint8_t advertising_data_length, uint8_t *advertising_data);

void ll_hci_adv_scan_response_set_data(uint8_t scan_response_data_length, uint8_t *scan_response_data);

int ll_hci_adv_enable(bool enable);

void ll_hci_scan_set_params(uint8_t scan_type, uint16_t scan_interval, uint16_t scan_window);

void ll_hci_set_scan_parameters(uint8_t *data, size_t size);

int ll_hci_scan_enable(bool enable, u8 filter_duplicates);

int ll_hci_create_conn(u8 *conn_param, u8 *addr_param);

int ll_hci_create_conn_ext(void *param);

int ll_hci_create_conn_cancel(void);

int ll_hci_vendor_send_key_num(u16 con_handle, u8 num);

int ll_vendor_latency_hold_cnt(u16 conn_handle, u16 hold_cnt);

int ll_vendor_open_latency(u16 conn_handle);

int ll_vendor_close_latency(u16 conn_handle);

int ll_hci_encryption(u8 *key, u8 *plaintext_data);

int ll_hci_get_le_rand(void);


int ll_hci_start_encryption(u16 handle, u32 rand_low, u32 rand_high, u16 peer_ediv, u8 *ltk);

int ll_hci_long_term_key_request_reply(u16 handle, u8 *ltk);

int ll_hci_long_term_key_request_nagative_reply(u16 handle);

int ll_hci_connection_update(u16 handle, u16 conn_interval_min, u16 conn_interval_max,
                             u16 conn_latency, u16 supervision_timeout,
                             u16 minimum_ce_length, u16 maximum_ce_length);

u16 ll_hci_get_acl_data_len(void);

u16 ll_hci_get_acl_total_num(void);

void ll_hci_set_random_address(u8 *addr);

int ll_hci_disconnect(u16 handle, u8 reason);

int ll_hci_read_local_p256_pb_key(void);

int ll_hci_generate_dhkey(const u8 *data, u32 size);

//Adjust Controller part API
void ll_hci_cmd_handler(int *cmd);

void ll_event_handler(int *msg);

void ll_hci_private_free_dma_rx(u8 *rx_head);

void ll_hci_set_data_length(u16 conn_handle, u16 tx_octets, u16 tx_time);

hci_ll_param_t *ll_hci_param_config_get(void);
void hci_ll_get_device_address(uint8_t *addr_type, u8 *addr);
void ll_hci_set_host_channel_classification(u8 *channel_map);

// ble5
void ll_hci_set_ext_adv_params(u8 *data, u32 size);
void ll_hci_set_ext_adv_data(u8 *data, u32 size);
void ll_hci_set_ext_rsp_data(u8 *data, u32 size);
void ll_hci_set_ext_adv_enable(u8 *data, u32 size);
void ll_hci_set_phy(u16 conn_handle, u8 all_phys, u8 tx_phy, u8 rx_phy, u16 phy_options);
void ll_hci_set_ext_scan_params(u8 *data, u32 size);
void ll_hci_set_ext_scan_enable(u8 *data, u32 size);
void ll_hci_ext_create_conn(u8 *data, u32 size);
void ll_hci_set_periodic_adv_params(u8 *data, u32 size);
void ll_hci_set_periodic_adv_data(u8 *data, u32 size);
void ll_hci_set_periodic_adv_enable(u8 *data, u32 size);
void ll_hci_periodic_adv_creat_sync(u8 *data, u32 size);
void ll_hci_periodic_adv_terminate_sync(u8 *data, u32 size);
void ll_hci_periodic_adv_create_sync_cancel(void);
void ll_hci_set_cig_params(uint8_t *data, size_t size);
void ll_hci_create_cis(uint8_t *data, size_t size);
void ll_hci_remove_cig(uint8_t *data, size_t size);
void ll_hci_accept_cis_req(uint8_t *data, size_t size);
void ll_hci_create_big(uint8_t *data, size_t size);
void ll_hci_big_create_sync(uint8_t *data, size_t size);
void ll_hci_big_terminate_sync(uint8_t *data, size_t size);
void ll_hci_read_iso_tx_sync(uint8_t *data, size_t size);
void ll_hci_periodic_adv_receive_enable(uint8_t *data, size_t size);
void ll_hci_periodic_adv_sync_transfer(uint8_t *data, size_t size);
void ll_hci_periodic_adv_set_info_transfer(uint8_t *data, size_t size);
void ll_hci_set_periodic_adv_sync_transfer_param(uint8_t *data, size_t size);
void ll_hci_set_default_periodic_adv_sync_transfer_param(uint8_t *data, size_t size);
void ll_hci_setup_iso_data_path(uint8_t *data, size_t size);
void ll_hci_read_iso_tx_sync(uint8_t *data, size_t size);
void ll_hci_terminate_big(uint8_t *data, size_t size);
int ll_read_iso_tx_sync(u16 handle, u16 *pPsn, u32 *pTime_stamp, u32 *pTime_offset);

int le_controller_set_mac(void *addr);
void hci_add_event_handler(void *callback_handler);
void hci_remove_event_handler(void *callback_handler);

/* vendor */
void hci_iso_receive_callback_register(void *callback);
void nonstandard_pop_iso_dtata(uint8_t U_F_flag, uint8_t pdu_len, uint8_t offset, uint8_t pb_flag, uint8_t *sdu);
void ll_big_tx_align_callback_register(uint8_t big_handle, const void *callback);
void ll_config_ctrler_clk(uint16_t handle, uint8_t sel);
void ll_get_ctrler_clk(uint16_t hdl, uint16_t *us_1per12, uint32_t *ref_clk_us, uint32_t *evt);
void ll_set_vendor_param(uint8_t *vendor_param, size_t size);
void ll_big_set_vendor_param(uint8_t *vendor_param, size_t size);
void ll_cig_set_vendor_param(uint8_t *vendor_param, size_t size);
void ll_cig_tx_align_callback_register(uint8_t cig_id, const void *callback);
void ll_conn_rx_acl_callback_register(void (*callback)(uint8_t *packet, size_t size));
void ll_set_scan_priority(uint8_t priority);
void rf_mdm_con_ble_sync_word(int tws_esco);
uint8_t ll_iso_unpack_hdr(const uint8_t *sdu, hci_iso_hdr_t *hdr);
void access_addr_generate(u8 *aa);
int tws_host_ble_state_is_busy(void);
int tws_host_get_ble_core_data(u8 *packet, int size);

typedef void (*timeout_callback_t)(void *priv);

void bb_le_timer_set(uint8_t idx, uint32_t usec, timeout_callback_t callback, void *priv);
u32 bb_le_clk_get_time_us(void);
uint8_t bb_le_timer_get(void);
void bb_le_timer_reset(uint8_t idx, uint32_t usec);
uint8_t ble_vendor_priv_get_case_user();
void le_hci_shutdown_connection(u16 handle);
void ll_big_mst_get_rx_info(uint16_t bis_hdl, void *priv);
void ll_big_mst_clear_rx_info(uint16_t bis_hdl);
void ll_hci_event_callback_register(void (*callback)(uint8_t packet_type, uint8_t *packet, size_t size));
void ll_set_private_access_addr_pair_channel(uint32_t access_addr);
void bt_band_sw(unsigned char oob_en);
s8 le_hb_rssi();

void ll_hci_remove_iso_data_path(uint8_t *data, size_t size);

void ll_set_ext_scan_priority(uint8_t priority);
#endif
