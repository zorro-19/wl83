/*********************************************************************************************
    *   Filename        : btstack_event.h

    *   Description     :

    *   Author          : Tongai

    *   Email           : laotongai@zh-jieli.com

    *   Last modifiled  : 2020-07-01 16:23

    *   Copyright:(c)JIELI  2011-2019  @ , All Rights Reserved.
*********************************************************************************************/

#ifndef __BTSTACK_EVENT_H
#define __BTSTACK_EVENT_H

#if defined __cplusplus
extern "C" {
#endif

#include "btstack/btstack_typedef.h"
#include <stdint.h>

#define ENABLE_BLE

#ifdef ENABLE_BLE
#include "le/gatt.h"
#endif

    /* API_START */

    /**
     * @brief Get event type
     * @param event
     * @return type of event
     */
    static inline uint8_t hci_event_packet_get_type(const uint8_t *event)
    {
        return event[0];
    }

    /***
     * @brief Get subevent code for ancs event
     * @param event packet
     * @return subevent_code
     */
    static inline uint8_t hci_event_ancs_meta_get_subevent_code(const uint8_t *event)
    {
        return event[2];
    }
    /***
     * @brief Get subevent code for avdtp event
     * @param event packet
     * @return subevent_code
     */
    static inline uint8_t hci_event_avdtp_meta_get_subevent_code(const uint8_t *event)
    {
        return event[2];
    }
    /***
     * @brief Get subevent code for a2dp event
     * @param event packet
     * @return subevent_code
     */
    static inline uint8_t hci_event_a2dp_meta_get_subevent_code(const uint8_t *event)
    {
        return event[2];
    }
    /***
     * @brief Get subevent code for avrcp event
     * @param event packet
     * @return subevent_code
     */
    static inline uint8_t hci_event_avrcp_meta_get_subevent_code(const uint8_t *event)
    {
        return event[2];
    }
    /***
     * @brief Get subevent code for goep event
     * @param event packet
     * @return subevent_code
     */
    static inline uint8_t hci_event_goep_meta_get_subevent_code(const uint8_t *event)
    {
        return event[2];
    }
    /***
     * @brief Get subevent code for hfp event
     * @param event packet
     * @return subevent_code
     */
    static inline uint8_t hci_event_hfp_meta_get_subevent_code(const uint8_t *event)
    {
        return event[2];
    }
    /***
     * @brief Get subevent code for hsp event
     * @param event packet
     * @return subevent_code
     */
    static inline uint8_t hci_event_hsp_meta_get_subevent_code(const uint8_t *event)
    {
        return event[2];
    }
    /***
     * @brief Get subevent code for pbap event
     * @param event packet
     * @return subevent_code
     */
    static inline uint8_t hci_event_pbap_meta_get_subevent_code(const uint8_t *event)
    {
        return event[2];
    }
    /***
     * @brief Get subevent code for le event
     * @param event packet
     * @return subevent_code
     */
    static inline uint8_t hci_event_le_meta_get_subevent_code(const uint8_t *event)
    {
        return event[2];
    }
    /***
     * @brief Get subevent code for hid event
     * @param event packet
     * @return subevent_code
     */
    static inline uint8_t hci_event_hid_meta_get_subevent_code(const uint8_t *event)
    {
        return event[2];
    }
    /***
     * @brief Get subevent code for hids event
     * @param event packet
     * @return subevent_code
     */
    static inline uint8_t hci_event_hids_meta_get_subevent_code(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field status from event HCI_EVENT_INQUIRY_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_inquiry_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }

    /**
     * @brief Get field num_responses from event HCI_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return num_responses
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_inquiry_result_get_num_responses(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field bd_addr from event HCI_EVENT_INQUIRY_RESULT
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_inquiry_result_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[3], bd_addr);
    }
    /**
     * @brief Get field page_scan_repetition_mode from event HCI_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return page_scan_repetition_mode
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_inquiry_result_get_page_scan_repetition_mode(const uint8_t *event)
    {
        return event[9];
    }
    /**
     * @brief Get field reserved1 from event HCI_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return reserved1
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_inquiry_result_get_reserved1(const uint8_t *event)
    {
        return event[10];
    }
    /**
     * @brief Get field reserved2 from event HCI_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return reserved2
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_inquiry_result_get_reserved2(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field class_of_device from event HCI_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return class_of_device
     * @note: btstack_type 3
     */
    static inline uint32_t hci_event_inquiry_result_get_class_of_device(const uint8_t *event)
    {
        return little_endian_read_24(event, 12);
    }
    /**
     * @brief Get field clock_offset from event HCI_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return clock_offset
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_inquiry_result_get_clock_offset(const uint8_t *event)
    {
        return little_endian_read_16(event, 15);
    }

    /**
     * @brief Get field status from event HCI_EVENT_CONNECTION_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_connection_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field connection_handle from event HCI_EVENT_CONNECTION_COMPLETE
     * @param event packet
     * @return connection_handle
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_connection_complete_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field bd_addr from event HCI_EVENT_CONNECTION_COMPLETE
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_connection_complete_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[5], bd_addr);
    }
    /**
     * @brief Get field link_type from event HCI_EVENT_CONNECTION_COMPLETE
     * @param event packet
     * @return link_type
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_connection_complete_get_link_type(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field encryption_enabled from event HCI_EVENT_CONNECTION_COMPLETE
     * @param event packet
     * @return encryption_enabled
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_connection_complete_get_encryption_enabled(const uint8_t *event)
    {
        return event[12];
    }

    /**
     * @brief Get field bd_addr from event HCI_EVENT_CONNECTION_REQUEST
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_connection_request_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[2], bd_addr);
    }
    /**
     * @brief Get field class_of_device from event HCI_EVENT_CONNECTION_REQUEST
     * @param event packet
     * @return class_of_device
     * @note: btstack_type 3
     */
    static inline uint32_t hci_event_connection_request_get_class_of_device(const uint8_t *event)
    {
        return little_endian_read_24(event, 8);
    }
    /**
     * @brief Get field link_type from event HCI_EVENT_CONNECTION_REQUEST
     * @param event packet
     * @return link_type
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_connection_request_get_link_type(const uint8_t *event)
    {
        return event[11];
    }

    /**
     * @brief Get field status from event HCI_EVENT_DISCONNECTION_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_disconnection_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field connection_handle from event HCI_EVENT_DISCONNECTION_COMPLETE
     * @param event packet
     * @return connection_handle
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_disconnection_complete_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field reason from event HCI_EVENT_DISCONNECTION_COMPLETE
     * @param event packet
     * @return reason
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_disconnection_complete_get_reason(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field status from event HCI_EVENT_AUTHENTICATION_COMPLETE_EVENT
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_authentication_complete_event_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field connection_handle from event HCI_EVENT_AUTHENTICATION_COMPLETE_EVENT
     * @param event packet
     * @return connection_handle
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_authentication_complete_event_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field status from event HCI_EVENT_REMOTE_NAME_REQUEST_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_remote_name_request_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field bd_addr from event HCI_EVENT_REMOTE_NAME_REQUEST_COMPLETE
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_remote_name_request_complete_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[3], bd_addr);
    }
    /**
     * @brief Get field remote_name from event HCI_EVENT_REMOTE_NAME_REQUEST_COMPLETE
     * @param event packet
     * @return remote_name
     * @note: btstack_type N
     */
    static inline const char *hci_event_remote_name_request_complete_get_remote_name(const uint8_t *event)
    {
        return (const char *) &event[9];
    }

    /**
     * @brief Get field status from event HCI_EVENT_ENCRYPTION_CHANGE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_encryption_change_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field connection_handle from event HCI_EVENT_ENCRYPTION_CHANGE
     * @param event packet
     * @return connection_handle
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_encryption_change_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field encryption_enabled from event HCI_EVENT_ENCRYPTION_CHANGE
     * @param event packet
     * @return encryption_enabled
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_encryption_change_get_encryption_enabled(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field status from event HCI_EVENT_CHANGE_CONNECTION_LINK_KEY_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_change_connection_link_key_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field connection_handle from event HCI_EVENT_CHANGE_CONNECTION_LINK_KEY_COMPLETE
     * @param event packet
     * @return connection_handle
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_change_connection_link_key_complete_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field status from event HCI_EVENT_MASTER_LINK_KEY_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_master_link_key_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field connection_handle from event HCI_EVENT_MASTER_LINK_KEY_COMPLETE
     * @param event packet
     * @return connection_handle
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_master_link_key_complete_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field key_flag from event HCI_EVENT_MASTER_LINK_KEY_COMPLETE
     * @param event packet
     * @return key_flag
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_master_link_key_complete_get_key_flag(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field num_hci_command_packets from event HCI_EVENT_COMMAND_COMPLETE
     * @param event packet
     * @return num_hci_command_packets
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_command_complete_get_num_hci_command_packets(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field command_opcode from event HCI_EVENT_COMMAND_COMPLETE
     * @param event packet
     * @return command_opcode
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_command_complete_get_command_opcode(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field return_parameters from event HCI_EVENT_COMMAND_COMPLETE
     * @param event packet
     * @return return_parameters
     * @note: btstack_type R
     */
    static inline const uint8_t *hci_event_command_complete_get_return_parameters(const uint8_t *event)
    {
        return &event[5];
    }

    /**
     * @brief Get field status from event HCI_EVENT_COMMAND_STATUS
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_command_status_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field num_hci_command_packets from event HCI_EVENT_COMMAND_STATUS
     * @param event packet
     * @return num_hci_command_packets
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_command_status_get_num_hci_command_packets(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field command_opcode from event HCI_EVENT_COMMAND_STATUS
     * @param event packet
     * @return command_opcode
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_command_status_get_command_opcode(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }

    /**
     * @brief Get field hardware_code from event HCI_EVENT_HARDWARE_ERROR
     * @param event packet
     * @return hardware_code
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_hardware_error_get_hardware_code(const uint8_t *event)
    {
        return event[2];
    }

    /**
     * @brief Get field status from event HCI_EVENT_ROLE_CHANGE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_role_change_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field bd_addr from event HCI_EVENT_ROLE_CHANGE
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_role_change_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[3], bd_addr);
    }
    /**
     * @brief Get field role from event HCI_EVENT_ROLE_CHANGE
     * @param event packet
     * @return role
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_role_change_get_role(const uint8_t *event)
    {
        return event[9];
    }

    /**
     * @brief Get field status from event HCI_EVENT_MODE_CHANGE_EVENT
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_mode_change_event_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field handle from event HCI_EVENT_MODE_CHANGE_EVENT
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_event_mode_change_event_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field mode from event HCI_EVENT_MODE_CHANGE_EVENT
     * @param event packet
     * @return mode
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_mode_change_event_get_mode(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field interval from event HCI_EVENT_MODE_CHANGE_EVENT
     * @param event packet
     * @return interval
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_mode_change_event_get_interval(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }

    /**
     * @brief Get field bd_addr from event HCI_EVENT_PIN_CODE_REQUEST
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_pin_code_request_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[2], bd_addr);
    }

    /**
     * @brief Get field bd_addr from event HCI_EVENT_LINK_KEY_REQUEST
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_link_key_request_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[2], bd_addr);
    }

    /**
     * @brief Get field link_type from event HCI_EVENT_DATA_BUFFER_OVERFLOW
     * @param event packet
     * @return link_type
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_data_buffer_overflow_get_link_type(const uint8_t *event)
    {
        return event[2];
    }

    /**
     * @brief Get field handle from event HCI_EVENT_MAX_SLOTS_CHANGED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_event_max_slots_changed_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field lmp_max_slots from event HCI_EVENT_MAX_SLOTS_CHANGED
     * @param event packet
     * @return lmp_max_slots
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_max_slots_changed_get_lmp_max_slots(const uint8_t *event)
    {
        return event[4];
    }

    /**
     * @brief Get field status from event HCI_EVENT_READ_CLOCK_OFFSET_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_read_clock_offset_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field handle from event HCI_EVENT_READ_CLOCK_OFFSET_COMPLETE
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_event_read_clock_offset_complete_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field clock_offset from event HCI_EVENT_READ_CLOCK_OFFSET_COMPLETE
     * @param event packet
     * @return clock_offset
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_read_clock_offset_complete_get_clock_offset(const uint8_t *event)
    {
        return little_endian_read_16(event, 5);
    }

    /**
     * @brief Get field status from event HCI_EVENT_CONNECTION_PACKET_TYPE_CHANGED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_connection_packet_type_changed_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field handle from event HCI_EVENT_CONNECTION_PACKET_TYPE_CHANGED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_event_connection_packet_type_changed_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field packet_types from event HCI_EVENT_CONNECTION_PACKET_TYPE_CHANGED
     * @param event packet
     * @return packet_types
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_connection_packet_type_changed_get_packet_types(const uint8_t *event)
    {
        return little_endian_read_16(event, 5);
    }

    /**
     * @brief Get field num_responses from event HCI_EVENT_INQUIRY_RESULT_WITH_RSSI
     * @param event packet
     * @return num_responses
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_inquiry_result_with_rssi_get_num_responses(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field bd_addr from event HCI_EVENT_INQUIRY_RESULT_WITH_RSSI
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_inquiry_result_with_rssi_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[3], bd_addr);
    }
    /**
     * @brief Get field page_scan_repetition_mode from event HCI_EVENT_INQUIRY_RESULT_WITH_RSSI
     * @param event packet
     * @return page_scan_repetition_mode
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_inquiry_result_with_rssi_get_page_scan_repetition_mode(const uint8_t *event)
    {
        return event[9];
    }
    /**
     * @brief Get field reserved from event HCI_EVENT_INQUIRY_RESULT_WITH_RSSI
     * @param event packet
     * @return reserved
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_inquiry_result_with_rssi_get_reserved(const uint8_t *event)
    {
        return event[10];
    }
    /**
     * @brief Get field class_of_device from event HCI_EVENT_INQUIRY_RESULT_WITH_RSSI
     * @param event packet
     * @return class_of_device
     * @note: btstack_type 3
     */
    static inline uint32_t hci_event_inquiry_result_with_rssi_get_class_of_device(const uint8_t *event)
    {
        return little_endian_read_24(event, 11);
    }
    /**
     * @brief Get field clock_offset from event HCI_EVENT_INQUIRY_RESULT_WITH_RSSI
     * @param event packet
     * @return clock_offset
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_inquiry_result_with_rssi_get_clock_offset(const uint8_t *event)
    {
        return little_endian_read_16(event, 14);
    }
    /**
     * @brief Get field rssi from event HCI_EVENT_INQUIRY_RESULT_WITH_RSSI
     * @param event packet
     * @return rssi
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_inquiry_result_with_rssi_get_rssi(const uint8_t *event)
    {
        return event[16];
    }

    /**
     * @brief Get field status from event HCI_EVENT_SYNCHRONOUS_CONNECTION_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_synchronous_connection_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field handle from event HCI_EVENT_SYNCHRONOUS_CONNECTION_COMPLETE
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_event_synchronous_connection_complete_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field bd_addr from event HCI_EVENT_SYNCHRONOUS_CONNECTION_COMPLETE
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_synchronous_connection_complete_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[5], bd_addr);
    }
    /**
     * @brief Get field link_type from event HCI_EVENT_SYNCHRONOUS_CONNECTION_COMPLETE
     * @param event packet
     * @return link_type
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_synchronous_connection_complete_get_link_type(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field transmission_interval from event HCI_EVENT_SYNCHRONOUS_CONNECTION_COMPLETE
     * @param event packet
     * @return transmission_interval
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_synchronous_connection_complete_get_transmission_interval(const uint8_t *event)
    {
        return event[12];
    }
    /**
     * @brief Get field retransmission_interval from event HCI_EVENT_SYNCHRONOUS_CONNECTION_COMPLETE
     * @param event packet
     * @return retransmission_interval
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_synchronous_connection_complete_get_retransmission_interval(const uint8_t *event)
    {
        return event[13];
    }
    /**
     * @brief Get field rx_packet_length from event HCI_EVENT_SYNCHRONOUS_CONNECTION_COMPLETE
     * @param event packet
     * @return rx_packet_length
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_synchronous_connection_complete_get_rx_packet_length(const uint8_t *event)
    {
        return little_endian_read_16(event, 14);
    }
    /**
     * @brief Get field tx_packet_length from event HCI_EVENT_SYNCHRONOUS_CONNECTION_COMPLETE
     * @param event packet
     * @return tx_packet_length
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_synchronous_connection_complete_get_tx_packet_length(const uint8_t *event)
    {
        return little_endian_read_16(event, 16);
    }
    /**
     * @brief Get field air_mode from event HCI_EVENT_SYNCHRONOUS_CONNECTION_COMPLETE
     * @param event packet
     * @return air_mode
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_synchronous_connection_complete_get_air_mode(const uint8_t *event)
    {
        return event[18];
    }

    /**
     * @brief Get field num_responses from event HCI_EVENT_EXTENDED_INQUIRY_RESPONSE
     * @param event packet
     * @return num_responses
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_extended_inquiry_response_get_num_responses(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field bd_addr from event HCI_EVENT_EXTENDED_INQUIRY_RESPONSE
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_extended_inquiry_response_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[3], bd_addr);
    }
    /**
     * @brief Get field page_scan_repetition_mode from event HCI_EVENT_EXTENDED_INQUIRY_RESPONSE
     * @param event packet
     * @return page_scan_repetition_mode
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_extended_inquiry_response_get_page_scan_repetition_mode(const uint8_t *event)
    {
        return event[9];
    }
    /**
     * @brief Get field reserved from event HCI_EVENT_EXTENDED_INQUIRY_RESPONSE
     * @param event packet
     * @return reserved
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_extended_inquiry_response_get_reserved(const uint8_t *event)
    {
        return event[10];
    }
    /**
     * @brief Get field class_of_device from event HCI_EVENT_EXTENDED_INQUIRY_RESPONSE
     * @param event packet
     * @return class_of_device
     * @note: btstack_type 3
     */
    static inline uint32_t hci_event_extended_inquiry_response_get_class_of_device(const uint8_t *event)
    {
        return little_endian_read_24(event, 11);
    }
    /**
     * @brief Get field clock_offset from event HCI_EVENT_EXTENDED_INQUIRY_RESPONSE
     * @param event packet
     * @return clock_offset
     * @note: btstack_type 2
     */
    static inline uint16_t hci_event_extended_inquiry_response_get_clock_offset(const uint8_t *event)
    {
        return little_endian_read_16(event, 14);
    }
    /**
     * @brief Get field rssi from event HCI_EVENT_EXTENDED_INQUIRY_RESPONSE
     * @param event packet
     * @return rssi
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_extended_inquiry_response_get_rssi(const uint8_t *event)
    {
        return event[16];
    }

    /**
     * @brief Get field status from event HCI_EVENT_ENCRYPTION_KEY_REFRESH_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_encryption_key_refresh_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field handle from event HCI_EVENT_ENCRYPTION_KEY_REFRESH_COMPLETE
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_event_encryption_key_refresh_complete_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field bd_addr from event HCI_EVENT_USER_CONFIRMATION_REQUEST
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_user_confirmation_request_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[2], bd_addr);
    }
    /**
     * @brief Get field numeric_value from event HCI_EVENT_USER_CONFIRMATION_REQUEST
     * @param event packet
     * @return numeric_value
     * @note: btstack_type 4
     */
    static inline uint32_t hci_event_user_confirmation_request_get_numeric_value(const uint8_t *event)
    {
        return little_endian_read_32(event, 8);
    }

    /**
     * @brief Get field bd_addr from event HCI_EVENT_USER_PASSKEY_REQUEST
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_user_passkey_request_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[2], bd_addr);
    }

    /**
     * @brief Get field bd_addr from event HCI_EVENT_REMOTE_OOB_DATA_REQUEST
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_remote_oob_data_request_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[2], bd_addr);
    }

    /**
     * @brief Get field status from event HCI_EVENT_SIMPLE_PAIRING_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_simple_pairing_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field bd_addr from event HCI_EVENT_SIMPLE_PAIRING_COMPLETE
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hci_event_simple_pairing_complete_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[3], bd_addr);
    }

    /**
     * @brief Get field state from event BTSTACK_EVENT_STATE
     * @param event packet
     * @return state
     * @note: btstack_type 1
     */
    static inline uint8_t btstack_event_state_get_state(const uint8_t *event)
    {
        return event[2];
    }

    /**
     * @brief Get field number_connections from event BTSTACK_EVENT_NR_CONNECTIONS_CHANGED
     * @param event packet
     * @return number_connections
     * @note: btstack_type 1
     */
    static inline uint8_t btstack_event_nr_connections_changed_get_number_connections(const uint8_t *event)
    {
        return event[2];
    }


    /**
     * @brief Get field discoverable from event BTSTACK_EVENT_DISCOVERABLE_ENABLED
     * @param event packet
     * @return discoverable
     * @note: btstack_type 1
     */
    static inline uint8_t btstack_event_discoverable_enabled_get_discoverable(const uint8_t *event)
    {
        return event[2];
    }

    /**
     * @brief Get field active from event HCI_EVENT_TRANSPORT_SLEEP_MODE
     * @param event packet
     * @return active
     * @note: btstack_type 1
     */
    static inline uint8_t hci_event_transport_sleep_mode_get_active(const uint8_t *event)
    {
        return event[2];
    }

    /**
     * @brief Get field handle from event HCI_EVENT_SCO_CAN_SEND_NOW
     * @param event packet
     * @param Pointer to storage for handle
     * @note: btstack_type B
     */
    static inline void hci_event_sco_can_send_now_get_handle(const uint8_t *event, bd_addr_t handle)
    {
        reverse_bd_addr(&event[2], handle);
    }

    /**
     * @brief Get field status from event L2CAP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t l2cap_event_channel_opened_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field address from event L2CAP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void l2cap_event_channel_opened_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[3], address);
    }
    /**
     * @brief Get field handle from event L2CAP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t l2cap_event_channel_opened_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }
    /**
     * @brief Get field psm from event L2CAP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return psm
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_channel_opened_get_psm(const uint8_t *event)
    {
        return little_endian_read_16(event, 11);
    }
    /**
     * @brief Get field local_cid from event L2CAP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_channel_opened_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 13);
    }
    /**
     * @brief Get field remote_cid from event L2CAP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return remote_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_channel_opened_get_remote_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 15);
    }
    /**
     * @brief Get field local_mtu from event L2CAP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return local_mtu
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_channel_opened_get_local_mtu(const uint8_t *event)
    {
        return little_endian_read_16(event, 17);
    }
    /**
     * @brief Get field remote_mtu from event L2CAP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return remote_mtu
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_channel_opened_get_remote_mtu(const uint8_t *event)
    {
        return little_endian_read_16(event, 19);
    }
    /**
     * @brief Get field flush_timeout from event L2CAP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return flush_timeout
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_channel_opened_get_flush_timeout(const uint8_t *event)
    {
        return little_endian_read_16(event, 21);
    }
    /**
     * @brief Get field incoming from event L2CAP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return incoming
     * @note: btstack_type 1
     */
    static inline uint8_t l2cap_event_channel_opened_get_incoming(const uint8_t *event)
    {
        return event[23];
    }

    /**
     * @brief Get field local_cid from event L2CAP_EVENT_CHANNEL_CLOSED
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_channel_closed_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }

    /**
     * @brief Get field address from event L2CAP_EVENT_INCOMING_CONNECTION
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void l2cap_event_incoming_connection_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[2], address);
    }
    /**
     * @brief Get field handle from event L2CAP_EVENT_INCOMING_CONNECTION
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t l2cap_event_incoming_connection_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 8);
    }
    /**
     * @brief Get field psm from event L2CAP_EVENT_INCOMING_CONNECTION
     * @param event packet
     * @return psm
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_incoming_connection_get_psm(const uint8_t *event)
    {
        return little_endian_read_16(event, 10);
    }
    /**
     * @brief Get field local_cid from event L2CAP_EVENT_INCOMING_CONNECTION
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_incoming_connection_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 12);
    }
    /**
     * @brief Get field remote_cid from event L2CAP_EVENT_INCOMING_CONNECTION
     * @param event packet
     * @return remote_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_incoming_connection_get_remote_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 14);
    }

    /**
     * @brief Get field handle from event L2CAP_EVENT_CONNECTION_PARAMETER_UPDATE_REQUEST
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t l2cap_event_connection_parameter_update_request_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field interval_min from event L2CAP_EVENT_CONNECTION_PARAMETER_UPDATE_REQUEST
     * @param event packet
     * @return interval_min
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_connection_parameter_update_request_get_interval_min(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field interval_max from event L2CAP_EVENT_CONNECTION_PARAMETER_UPDATE_REQUEST
     * @param event packet
     * @return interval_max
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_connection_parameter_update_request_get_interval_max(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field latencey from event L2CAP_EVENT_CONNECTION_PARAMETER_UPDATE_REQUEST
     * @param event packet
     * @return latencey
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_connection_parameter_update_request_get_latencey(const uint8_t *event)
    {
        return little_endian_read_16(event, 8);
    }
    /**
     * @brief Get field timeout_multiplier from event L2CAP_EVENT_CONNECTION_PARAMETER_UPDATE_REQUEST
     * @param event packet
     * @return timeout_multiplier
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_connection_parameter_update_request_get_timeout_multiplier(const uint8_t *event)
    {
        return little_endian_read_16(event, 10);
    }

    /**
     * @brief Get field handle from event L2CAP_EVENT_CONNECTION_PARAMETER_UPDATE_RESPONSE
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t l2cap_event_connection_parameter_update_response_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field result from event L2CAP_EVENT_CONNECTION_PARAMETER_UPDATE_RESPONSE
     * @param event packet
     * @return result
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_connection_parameter_update_response_get_result(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }

    /**
     * @brief Get field local_cid from event L2CAP_EVENT_CAN_SEND_NOW
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_can_send_now_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }

    /**
     * @brief Get field local_cid from event L2CAP_EVENT_PACKET_SENT
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_packet_sent_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }

    /**
     * @brief Get field address_type from event L2CAP_EVENT_LE_INCOMING_CONNECTION
     * @param event packet
     * @return address_type
     * @note: btstack_type 1
     */
    static inline uint8_t l2cap_event_le_incoming_connection_get_address_type(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field address from event L2CAP_EVENT_LE_INCOMING_CONNECTION
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void l2cap_event_le_incoming_connection_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[3], address);
    }
    /**
     * @brief Get field handle from event L2CAP_EVENT_LE_INCOMING_CONNECTION
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t l2cap_event_le_incoming_connection_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }
    /**
     * @brief Get field psm from event L2CAP_EVENT_LE_INCOMING_CONNECTION
     * @param event packet
     * @return psm
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_incoming_connection_get_psm(const uint8_t *event)
    {
        return little_endian_read_16(event, 11);
    }
    /**
     * @brief Get field local_cid from event L2CAP_EVENT_LE_INCOMING_CONNECTION
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_incoming_connection_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 13);
    }
    /**
     * @brief Get field remote_cid from event L2CAP_EVENT_LE_INCOMING_CONNECTION
     * @param event packet
     * @return remote_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_incoming_connection_get_remote_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 15);
    }
    /**
     * @brief Get field remote_mtu from event L2CAP_EVENT_LE_INCOMING_CONNECTION
     * @param event packet
     * @return remote_mtu
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_incoming_connection_get_remote_mtu(const uint8_t *event)
    {
        return little_endian_read_16(event, 17);
    }

    /**
     * @brief Get field status from event L2CAP_EVENT_LE_CHANNEL_OPENED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t l2cap_event_le_channel_opened_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field address_type from event L2CAP_EVENT_LE_CHANNEL_OPENED
     * @param event packet
     * @return address_type
     * @note: btstack_type 1
     */
    static inline uint8_t l2cap_event_le_channel_opened_get_address_type(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field address from event L2CAP_EVENT_LE_CHANNEL_OPENED
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void l2cap_event_le_channel_opened_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[4], address);
    }
    /**
     * @brief Get field handle from event L2CAP_EVENT_LE_CHANNEL_OPENED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t l2cap_event_le_channel_opened_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 10);
    }
    /**
     * @brief Get field incoming from event L2CAP_EVENT_LE_CHANNEL_OPENED
     * @param event packet
     * @return incoming
     * @note: btstack_type 1
     */
    static inline uint8_t l2cap_event_le_channel_opened_get_incoming(const uint8_t *event)
    {
        return event[12];
    }
    /**
     * @brief Get field psm from event L2CAP_EVENT_LE_CHANNEL_OPENED
     * @param event packet
     * @return psm
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_channel_opened_get_psm(const uint8_t *event)
    {
        return little_endian_read_16(event, 13);
    }
    /**
     * @brief Get field local_cid from event L2CAP_EVENT_LE_CHANNEL_OPENED
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_channel_opened_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 15);
    }
    /**
     * @brief Get field remote_cid from event L2CAP_EVENT_LE_CHANNEL_OPENED
     * @param event packet
     * @return remote_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_channel_opened_get_remote_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 17);
    }
    /**
     * @brief Get field local_mtu from event L2CAP_EVENT_LE_CHANNEL_OPENED
     * @param event packet
     * @return local_mtu
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_channel_opened_get_local_mtu(const uint8_t *event)
    {
        return little_endian_read_16(event, 19);
    }
    /**
     * @brief Get field remote_mtu from event L2CAP_EVENT_LE_CHANNEL_OPENED
     * @param event packet
     * @return remote_mtu
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_channel_opened_get_remote_mtu(const uint8_t *event)
    {
        return little_endian_read_16(event, 21);
    }

    /**
     * @brief Get field local_cid from event L2CAP_EVENT_LE_CHANNEL_CLOSED
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_channel_closed_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }

    /**
     * @brief Get field local_cid from event L2CAP_EVENT_LE_CAN_SEND_NOW
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_can_send_now_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }

    /**
     * @brief Get field local_cid from event L2CAP_EVENT_LE_PACKET_SENT
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_le_packet_sent_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }

    /**
     * @brief Get field address_type from event L2CAP_EVENT_ECBM_INCOMING_CONNECTION
     * @param event packet
     * @return address_type
     * @note: btstack_type 1
     */
    static inline uint8_t l2cap_event_ecbm_incoming_connection_get_address_type(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field address from event L2CAP_EVENT_ECBM_INCOMING_CONNECTION
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void l2cap_event_ecbm_incoming_connection_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bytes(&event[3], address, 6);
    }
    /**
     * @brief Get field handle from event L2CAP_EVENT_ECBM_INCOMING_CONNECTION
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t l2cap_event_ecbm_incoming_connection_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }
    /**
     * @brief Get field psm from event L2CAP_EVENT_ECBM_INCOMING_CONNECTION
     * @param event packet
     * @return psm
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_ecbm_incoming_connection_get_psm(const uint8_t *event)
    {
        return little_endian_read_16(event, 11);
    }
    /**
     * @brief Get field num_channels from event L2CAP_EVENT_ECBM_INCOMING_CONNECTION
     * @param event packet
     * @return num_channels
     * @note: btstack_type 1
     */
    static inline uint8_t l2cap_event_ecbm_incoming_connection_get_num_channels(const uint8_t *event)
    {
        return event[13];
    }
    /**
     * @brief Get field local_cid from event L2CAP_EVENT_ECBM_INCOMING_CONNECTION
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_ecbm_incoming_connection_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 14);
    }

    /**
     * @brief Get field status from event L2CAP_EVENT_ECBM_CHANNEL_OPENED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t l2cap_event_ecbm_channel_opened_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field address_type from event L2CAP_EVENT_ECBM_CHANNEL_OPENED
     * @param event packet
     * @return address_type
     * @note: btstack_type 1
     */
    static inline uint8_t l2cap_event_ecbm_channel_opened_get_address_type(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field address from event L2CAP_EVENT_ECBM_CHANNEL_OPENED
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void l2cap_event_ecbm_channel_opened_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bytes(&event[4], address, 6);
    }
    /**
     * @brief Get field handle from event L2CAP_EVENT_ECBM_CHANNEL_OPENED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t l2cap_event_ecbm_channel_opened_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 10);
    }
    /**
     * @brief Get field incoming from event L2CAP_EVENT_ECBM_CHANNEL_OPENED
     * @param event packet
     * @return incoming
     * @note: btstack_type 1
     */
    static inline uint8_t l2cap_event_ecbm_channel_opened_get_incoming(const uint8_t *event)
    {
        return event[12];
    }
    /**
     * @brief Get field psm from event L2CAP_EVENT_ECBM_CHANNEL_OPENED
     * @param event packet
     * @return psm
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_ecbm_channel_opened_get_psm(const uint8_t *event)
    {
        return little_endian_read_16(event, 13);
    }
    /**
     * @brief Get field local_cid from event L2CAP_EVENT_ECBM_CHANNEL_OPENED
     * @param event packet
     * @return local_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_ecbm_channel_opened_get_local_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 15);
    }
    /**
     * @brief Get field remote_cid from event L2CAP_EVENT_ECBM_CHANNEL_OPENED
     * @param event packet
     * @return remote_cid
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_ecbm_channel_opened_get_remote_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 17);
    }
    /**
     * @brief Get field local_mtu from event L2CAP_EVENT_ECBM_CHANNEL_OPENED
     * @param event packet
     * @return local_mtu
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_ecbm_channel_opened_get_local_mtu(const uint8_t *event)
    {
        return little_endian_read_16(event, 19);
    }
    /**
     * @brief Get field remote_mtu from event L2CAP_EVENT_ECBM_CHANNEL_OPENED
     * @param event packet
     * @return remote_mtu
     * @note: btstack_type 2
     */
    static inline uint16_t l2cap_event_ecbm_channel_opened_get_remote_mtu(const uint8_t *event)
    {
        return little_endian_read_16(event, 21);
    }


    /**
     * @brief Get field status from event RFCOMM_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t rfcomm_event_channel_opened_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field bd_addr from event RFCOMM_EVENT_CHANNEL_OPENED
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void rfcomm_event_channel_opened_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[3], bd_addr);
    }
    /**
     * @brief Get field con_handle from event RFCOMM_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return con_handle
     * @note: btstack_type 2
     */
    static inline uint16_t rfcomm_event_channel_opened_get_con_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }
    /**
     * @brief Get field server_channel from event RFCOMM_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return server_channel
     * @note: btstack_type 1
     */
    static inline uint8_t rfcomm_event_channel_opened_get_server_channel(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field rfcomm_cid from event RFCOMM_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return rfcomm_cid
     * @note: btstack_type 2
     */
    static inline uint16_t rfcomm_event_channel_opened_get_rfcomm_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 12);
    }
    /**
     * @brief Get field max_frame_size from event RFCOMM_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return max_frame_size
     * @note: btstack_type 2
     */
    static inline uint16_t rfcomm_event_channel_opened_get_max_frame_size(const uint8_t *event)
    {
        return little_endian_read_16(event, 14);
    }
    /**
     * @brief Get field incoming from event RFCOMM_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return incoming
     * @note: btstack_type 1
     */
    static inline uint8_t rfcomm_event_channel_opened_get_incoming(const uint8_t *event)
    {
        return event[16];
    }

    /**
     * @brief Get field rfcomm_cid from event RFCOMM_EVENT_CHANNEL_CLOSED
     * @param event packet
     * @return rfcomm_cid
     * @note: btstack_type 2
     */
    static inline uint16_t rfcomm_event_channel_closed_get_rfcomm_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }

    /**
     * @brief Get field bd_addr from event RFCOMM_EVENT_INCOMING_CONNECTION
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void rfcomm_event_incoming_connection_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[2], bd_addr);
    }
    /**
     * @brief Get field server_channel from event RFCOMM_EVENT_INCOMING_CONNECTION
     * @param event packet
     * @return server_channel
     * @note: btstack_type 1
     */
    static inline uint8_t rfcomm_event_incoming_connection_get_server_channel(const uint8_t *event)
    {
        return event[8];
    }
    /**
     * @brief Get field rfcomm_cid from event RFCOMM_EVENT_INCOMING_CONNECTION
     * @param event packet
     * @return rfcomm_cid
     * @note: btstack_type 2
     */
    static inline uint16_t rfcomm_event_incoming_connection_get_rfcomm_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }

    /**
     * @brief Get field rfcomm_cid from event RFCOMM_EVENT_REMOTE_LINE_STATUS
     * @param event packet
     * @return rfcomm_cid
     * @note: btstack_type 2
     */
    static inline uint16_t rfcomm_event_remote_line_status_get_rfcomm_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field line_status from event RFCOMM_EVENT_REMOTE_LINE_STATUS
     * @param event packet
     * @return line_status
     * @note: btstack_type 1
     */
    static inline uint8_t rfcomm_event_remote_line_status_get_line_status(const uint8_t *event)
    {
        return event[4];
    }

    /**
     * @brief Get field rfcomm_cid from event RFCOMM_EVENT_REMOTE_MODEM_STATUS
     * @param event packet
     * @return rfcomm_cid
     * @note: btstack_type 2
     */
    static inline uint16_t rfcomm_event_remote_modem_status_get_rfcomm_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field modem_status from event RFCOMM_EVENT_REMOTE_MODEM_STATUS
     * @param event packet
     * @return modem_status
     * @note: btstack_type 1
     */
    static inline uint8_t rfcomm_event_remote_modem_status_get_modem_status(const uint8_t *event)
    {
        return event[4];
    }

    /**
     * @brief Get field rfcomm_cid from event RFCOMM_EVENT_CAN_SEND_NOW
     * @param event packet
     * @return rfcomm_cid
     * @note: btstack_type 2
     */
    static inline uint16_t rfcomm_event_can_send_now_get_rfcomm_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }

    /**
     * @brief Get field status from event SDP_EVENT_QUERY_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t sdp_event_query_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }

    /**
     * @brief Get field rfcomm_channel from event SDP_EVENT_QUERY_RFCOMM_SERVICE
     * @param event packet
     * @return rfcomm_channel
     * @note: btstack_type 1
     */
    static inline uint8_t sdp_event_query_rfcomm_service_get_rfcomm_channel(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field name from event SDP_EVENT_QUERY_RFCOMM_SERVICE
     * @param event packet
     * @return name
     * @note: btstack_type T
     */
    static inline const char *sdp_event_query_rfcomm_service_get_name(const uint8_t *event)
    {
        return (const char *) &event[3];
    }

    /**
     * @brief Get field record_id from event SDP_EVENT_QUERY_ATTRIBUTE_BYTE
     * @param event packet
     * @return record_id
     * @note: btstack_type 2
     */
    static inline uint16_t sdp_event_query_attribute_byte_get_record_id(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field attribute_id from event SDP_EVENT_QUERY_ATTRIBUTE_BYTE
     * @param event packet
     * @return attribute_id
     * @note: btstack_type 2
     */
    static inline uint16_t sdp_event_query_attribute_byte_get_attribute_id(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field attribute_length from event SDP_EVENT_QUERY_ATTRIBUTE_BYTE
     * @param event packet
     * @return attribute_length
     * @note: btstack_type 2
     */
    static inline uint16_t sdp_event_query_attribute_byte_get_attribute_length(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field data_offset from event SDP_EVENT_QUERY_ATTRIBUTE_BYTE
     * @param event packet
     * @return data_offset
     * @note: btstack_type 2
     */
    static inline uint16_t sdp_event_query_attribute_byte_get_data_offset(const uint8_t *event)
    {
        return little_endian_read_16(event, 8);
    }
    /**
     * @brief Get field data from event SDP_EVENT_QUERY_ATTRIBUTE_BYTE
     * @param event packet
     * @return data
     * @note: btstack_type 1
     */
    static inline uint8_t sdp_event_query_attribute_byte_get_data(const uint8_t *event)
    {
        return event[10];
    }

    /**
     * @brief Get field record_id from event SDP_EVENT_QUERY_ATTRIBUTE_VALUE
     * @param event packet
     * @return record_id
     * @note: btstack_type 2
     */
    static inline uint16_t sdp_event_query_attribute_value_get_record_id(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field attribute_id from event SDP_EVENT_QUERY_ATTRIBUTE_VALUE
     * @param event packet
     * @return attribute_id
     * @note: btstack_type 2
     */
    static inline uint16_t sdp_event_query_attribute_value_get_attribute_id(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field attribute_length from event SDP_EVENT_QUERY_ATTRIBUTE_VALUE
     * @param event packet
     * @return attribute_length
     * @note: btstack_type L
     */
    static inline int sdp_event_query_attribute_value_get_attribute_length(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field attribute_value from event SDP_EVENT_QUERY_ATTRIBUTE_VALUE
     * @param event packet
     * @return attribute_value
     * @note: btstack_type V
     */
    static inline const uint8_t *sdp_event_query_attribute_value_get_attribute_value(const uint8_t *event)
    {
        return &event[8];
    }

    /**
     * @brief Get field total_count from event SDP_EVENT_QUERY_SERVICE_RECORD_HANDLE
     * @param event packet
     * @return total_count
     * @note: btstack_type 2
     */
    static inline uint16_t sdp_event_query_service_record_handle_get_total_count(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field record_index from event SDP_EVENT_QUERY_SERVICE_RECORD_HANDLE
     * @param event packet
     * @return record_index
     * @note: btstack_type 2
     */
    static inline uint16_t sdp_event_query_service_record_handle_get_record_index(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field record_handle from event SDP_EVENT_QUERY_SERVICE_RECORD_HANDLE
     * @param event packet
     * @return record_handle
     * @note: btstack_type 4
     */
    static inline uint32_t sdp_event_query_service_record_handle_get_record_handle(const uint8_t *event)
    {
        return little_endian_read_32(event, 6);
    }

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_QUERY_COMPLETE
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_query_complete_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field status from event GATT_EVENT_QUERY_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t gatt_event_query_complete_get_status(const uint8_t *event)
    {
        return event[4];
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_SERVICE_QUERY_RESULT
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_service_query_result_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field service from event GATT_EVENT_SERVICE_QUERY_RESULT
     * @param event packet
     * @param Pointer to storage for service
     * @note: btstack_type X
     */
    static inline void gatt_event_service_query_result_get_service(const uint8_t *event, gatt_client_service_t *service)
    {
        gatt_client_deserialize_service(event, 4, service);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_CHARACTERISTIC_QUERY_RESULT
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_characteristic_query_result_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field characteristic from event GATT_EVENT_CHARACTERISTIC_QUERY_RESULT
     * @param event packet
     * @param Pointer to storage for characteristic
     * @note: btstack_type Y
     */
    static inline void gatt_event_characteristic_query_result_get_characteristic(const uint8_t *event, gatt_client_characteristic_t *characteristic)
    {
        gatt_client_deserialize_characteristic(event, 4, characteristic);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_INCLUDED_SERVICE_QUERY_RESULT
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_included_service_query_result_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field include_handle from event GATT_EVENT_INCLUDED_SERVICE_QUERY_RESULT
     * @param event packet
     * @return include_handle
     * @note: btstack_type 2
     */
    static inline uint16_t gatt_event_included_service_query_result_get_include_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field service from event GATT_EVENT_INCLUDED_SERVICE_QUERY_RESULT
     * @param event packet
     * @param Pointer to storage for service
     * @note: btstack_type X
     */
    static inline void gatt_event_included_service_query_result_get_service(const uint8_t *event, gatt_client_service_t *service)
    {
        gatt_client_deserialize_service(event, 6, service);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_ALL_CHARACTERISTIC_DESCRIPTORS_QUERY_RESULT
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_all_characteristic_descriptors_query_result_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field characteristic_descriptor from event GATT_EVENT_ALL_CHARACTERISTIC_DESCRIPTORS_QUERY_RESULT
     * @param event packet
     * @param Pointer to storage for characteristic_descriptor
     * @note: btstack_type Z
     */
    static inline void gatt_event_all_characteristic_descriptors_query_result_get_characteristic_descriptor(const uint8_t *event, gatt_client_characteristic_descriptor_t *characteristic_descriptor)
    {
        gatt_client_deserialize_characteristic_descriptor(event, 4, characteristic_descriptor);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_CHARACTERISTIC_VALUE_QUERY_RESULT
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_characteristic_value_query_result_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field value_handle from event GATT_EVENT_CHARACTERISTIC_VALUE_QUERY_RESULT
     * @param event packet
     * @return value_handle
     * @note: btstack_type 2
     */
    static inline uint16_t gatt_event_characteristic_value_query_result_get_value_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field value_length from event GATT_EVENT_CHARACTERISTIC_VALUE_QUERY_RESULT
     * @param event packet
     * @return value_length
     * @note: btstack_type L
     */
    static inline int gatt_event_characteristic_value_query_result_get_value_length(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field value from event GATT_EVENT_CHARACTERISTIC_VALUE_QUERY_RESULT
     * @param event packet
     * @return value
     * @note: btstack_type V
     */
    static inline const uint8_t *gatt_event_characteristic_value_query_result_get_value(const uint8_t *event)
    {
        return &event[8];
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_LONG_CHARACTERISTIC_VALUE_QUERY_RESULT
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_long_characteristic_value_query_result_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field value_handle from event GATT_EVENT_LONG_CHARACTERISTIC_VALUE_QUERY_RESULT
     * @param event packet
     * @return value_handle
     * @note: btstack_type 2
     */
    static inline uint16_t gatt_event_long_characteristic_value_query_result_get_value_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field value_offset from event GATT_EVENT_LONG_CHARACTERISTIC_VALUE_QUERY_RESULT
     * @param event packet
     * @return value_offset
     * @note: btstack_type 2
     */
    static inline uint16_t gatt_event_long_characteristic_value_query_result_get_value_offset(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field value_length from event GATT_EVENT_LONG_CHARACTERISTIC_VALUE_QUERY_RESULT
     * @param event packet
     * @return value_length
     * @note: btstack_type L
     */
    static inline int gatt_event_long_characteristic_value_query_result_get_value_length(const uint8_t *event)
    {
        return little_endian_read_16(event, 8);
    }
    /**
     * @brief Get field value from event GATT_EVENT_LONG_CHARACTERISTIC_VALUE_QUERY_RESULT
     * @param event packet
     * @return value
     * @note: btstack_type V
     */
    static inline const uint8_t *gatt_event_long_characteristic_value_query_result_get_value(const uint8_t *event)
    {
        return &event[10];
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_NOTIFICATION
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_notification_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field value_handle from event GATT_EVENT_NOTIFICATION
     * @param event packet
     * @return value_handle
     * @note: btstack_type 2
     */
    static inline uint16_t gatt_event_notification_get_value_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field value_length from event GATT_EVENT_NOTIFICATION
     * @param event packet
     * @return value_length
     * @note: btstack_type L
     */
    static inline int gatt_event_notification_get_value_length(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field value from event GATT_EVENT_NOTIFICATION
     * @param event packet
     * @return value
     * @note: btstack_type V
     */
    static inline const uint8_t *gatt_event_notification_get_value(const uint8_t *event)
    {
        return &event[8];
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_INDICATION
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_indication_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field value_handle from event GATT_EVENT_INDICATION
     * @param event packet
     * @return value_handle
     * @note: btstack_type 2
     */
    static inline uint16_t gatt_event_indication_get_value_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field value_length from event GATT_EVENT_INDICATION
     * @param event packet
     * @return value_length
     * @note: btstack_type L
     */
    static inline int gatt_event_indication_get_value_length(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field value from event GATT_EVENT_INDICATION
     * @param event packet
     * @return value
     * @note: btstack_type V
     */
    static inline const uint8_t *gatt_event_indication_get_value(const uint8_t *event)
    {
        return &event[8];
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_CHARACTERISTIC_DESCRIPTOR_QUERY_RESULT
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_characteristic_descriptor_query_result_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field descriptor_handle from event GATT_EVENT_CHARACTERISTIC_DESCRIPTOR_QUERY_RESULT
     * @param event packet
     * @return descriptor_handle
     * @note: btstack_type 2
     */
    static inline uint16_t gatt_event_characteristic_descriptor_query_result_get_descriptor_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field descriptor_length from event GATT_EVENT_CHARACTERISTIC_DESCRIPTOR_QUERY_RESULT
     * @param event packet
     * @return descriptor_length
     * @note: btstack_type L
     */
    static inline int gatt_event_characteristic_descriptor_query_result_get_descriptor_length(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field descriptor from event GATT_EVENT_CHARACTERISTIC_DESCRIPTOR_QUERY_RESULT
     * @param event packet
     * @return descriptor
     * @note: btstack_type V
     */
    static inline const uint8_t *gatt_event_characteristic_descriptor_query_result_get_descriptor(const uint8_t *event)
    {
        return &event[8];
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_LONG_CHARACTERISTIC_DESCRIPTOR_QUERY_RESULT
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_long_characteristic_descriptor_query_result_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field descriptor_offset from event GATT_EVENT_LONG_CHARACTERISTIC_DESCRIPTOR_QUERY_RESULT
     * @param event packet
     * @return descriptor_offset
     * @note: btstack_type 2
     */
    static inline uint16_t gatt_event_long_characteristic_descriptor_query_result_get_descriptor_offset(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field descriptor_length from event GATT_EVENT_LONG_CHARACTERISTIC_DESCRIPTOR_QUERY_RESULT
     * @param event packet
     * @return descriptor_length
     * @note: btstack_type L
     */
    static inline int gatt_event_long_characteristic_descriptor_query_result_get_descriptor_length(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field descriptor from event GATT_EVENT_LONG_CHARACTERISTIC_DESCRIPTOR_QUERY_RESULT
     * @param event packet
     * @return descriptor
     * @note: btstack_type V
     */
    static inline const uint8_t *gatt_event_long_characteristic_descriptor_query_result_get_descriptor(const uint8_t *event)
    {
        return &event[8];
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event GATT_EVENT_MTU
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gatt_event_mtu_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field MTU from event GATT_EVENT_MTU
     * @param event packet
     * @return MTU
     * @note: btstack_type 2
     */
    static inline uint16_t gatt_event_mtu_get_MTU(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
#endif

    /**
     * @brief Get field handle from event ATT_EVENT_MTU_EXCHANGE_COMPLETE
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t att_event_mtu_exchange_complete_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field MTU from event ATT_EVENT_MTU_EXCHANGE_COMPLETE
     * @param event packet
     * @return MTU
     * @note: btstack_type 2
     */
    static inline uint16_t att_event_mtu_exchange_complete_get_MTU(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }

    /**
     * @brief Get field status from event ATT_EVENT_HANDLE_VALUE_INDICATION_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t att_event_handle_value_indication_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field conn_handle from event ATT_EVENT_HANDLE_VALUE_INDICATION_COMPLETE
     * @param event packet
     * @return conn_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t att_event_handle_value_indication_complete_get_conn_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field attribute_handle from event ATT_EVENT_HANDLE_VALUE_INDICATION_COMPLETE
     * @param event packet
     * @return attribute_handle
     * @note: btstack_type 2
     */
    static inline uint16_t att_event_handle_value_indication_complete_get_attribute_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 5);
    }


    /**
     * @brief Get field status from event BNEP_EVENT_SERVICE_REGISTERED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t bnep_event_service_registered_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field service_uuid from event BNEP_EVENT_SERVICE_REGISTERED
     * @param event packet
     * @return service_uuid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_service_registered_get_service_uuid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field status from event BNEP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t bnep_event_channel_opened_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field bnep_cid from event BNEP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return bnep_cid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_channel_opened_get_bnep_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field source_uuid from event BNEP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return source_uuid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_channel_opened_get_source_uuid(const uint8_t *event)
    {
        return little_endian_read_16(event, 5);
    }
    /**
     * @brief Get field destination_uuid from event BNEP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return destination_uuid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_channel_opened_get_destination_uuid(const uint8_t *event)
    {
        return little_endian_read_16(event, 7);
    }
    /**
     * @brief Get field mtu from event BNEP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @return mtu
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_channel_opened_get_mtu(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }
    /**
     * @brief Get field remote_address from event BNEP_EVENT_CHANNEL_OPENED
     * @param event packet
     * @param Pointer to storage for remote_address
     * @note: btstack_type B
     */
    static inline void bnep_event_channel_opened_get_remote_address(const uint8_t *event, bd_addr_t remote_address)
    {
        reverse_bd_addr(&event[11], remote_address);
    }

    /**
     * @brief Get field bnep_cid from event BNEP_EVENT_CHANNEL_CLOSED
     * @param event packet
     * @return bnep_cid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_channel_closed_get_bnep_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field source_uuid from event BNEP_EVENT_CHANNEL_CLOSED
     * @param event packet
     * @return source_uuid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_channel_closed_get_source_uuid(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field destination_uuid from event BNEP_EVENT_CHANNEL_CLOSED
     * @param event packet
     * @return destination_uuid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_channel_closed_get_destination_uuid(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field remote_address from event BNEP_EVENT_CHANNEL_CLOSED
     * @param event packet
     * @param Pointer to storage for remote_address
     * @note: btstack_type B
     */
    static inline void bnep_event_channel_closed_get_remote_address(const uint8_t *event, bd_addr_t remote_address)
    {
        reverse_bd_addr(&event[8], remote_address);
    }

    /**
     * @brief Get field bnep_cid from event BNEP_EVENT_CHANNEL_TIMEOUT
     * @param event packet
     * @return bnep_cid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_channel_timeout_get_bnep_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field source_uuid from event BNEP_EVENT_CHANNEL_TIMEOUT
     * @param event packet
     * @return source_uuid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_channel_timeout_get_source_uuid(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field destination_uuid from event BNEP_EVENT_CHANNEL_TIMEOUT
     * @param event packet
     * @return destination_uuid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_channel_timeout_get_destination_uuid(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field remote_address from event BNEP_EVENT_CHANNEL_TIMEOUT
     * @param event packet
     * @param Pointer to storage for remote_address
     * @note: btstack_type B
     */
    static inline void bnep_event_channel_timeout_get_remote_address(const uint8_t *event, bd_addr_t remote_address)
    {
        reverse_bd_addr(&event[8], remote_address);
    }
    /**
     * @brief Get field channel_state from event BNEP_EVENT_CHANNEL_TIMEOUT
     * @param event packet
     * @return channel_state
     * @note: btstack_type 1
     */
    static inline uint8_t bnep_event_channel_timeout_get_channel_state(const uint8_t *event)
    {
        return event[14];
    }

    /**
     * @brief Get field bnep_cid from event BNEP_EVENT_CAN_SEND_NOW
     * @param event packet
     * @return bnep_cid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_can_send_now_get_bnep_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field source_uuid from event BNEP_EVENT_CAN_SEND_NOW
     * @param event packet
     * @return source_uuid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_can_send_now_get_source_uuid(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field destination_uuid from event BNEP_EVENT_CAN_SEND_NOW
     * @param event packet
     * @return destination_uuid
     * @note: btstack_type 2
     */
    static inline uint16_t bnep_event_can_send_now_get_destination_uuid(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field remote_address from event BNEP_EVENT_CAN_SEND_NOW
     * @param event packet
     * @param Pointer to storage for remote_address
     * @note: btstack_type B
     */
    static inline void bnep_event_can_send_now_get_remote_address(const uint8_t *event, bd_addr_t remote_address)
    {
        reverse_bd_addr(&event[8], remote_address);
    }

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_JUST_WORKS_REQUEST
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_just_works_request_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_JUST_WORKS_REQUEST
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_just_works_request_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_JUST_WORKS_REQUEST
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_just_works_request_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_JUST_WORKS_CANCEL
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_just_works_cancel_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_JUST_WORKS_CANCEL
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_just_works_cancel_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_JUST_WORKS_CANCEL
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_just_works_cancel_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_PASSKEY_DISPLAY_NUMBER
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_passkey_display_number_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_PASSKEY_DISPLAY_NUMBER
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_passkey_display_number_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_PASSKEY_DISPLAY_NUMBER
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_passkey_display_number_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
    /**
     * @brief Get field passkey from event SM_EVENT_PASSKEY_DISPLAY_NUMBER
     * @param event packet
     * @return passkey
     * @note: btstack_type 4
     */
    static inline uint32_t sm_event_passkey_display_number_get_passkey(const uint8_t *event)
    {
        return little_endian_read_32(event, 11);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_PASSKEY_DISPLAY_CANCEL
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_passkey_display_cancel_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_PASSKEY_DISPLAY_CANCEL
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_passkey_display_cancel_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_PASSKEY_DISPLAY_CANCEL
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_passkey_display_cancel_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_PASSKEY_INPUT_NUMBER
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_passkey_input_number_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_PASSKEY_INPUT_NUMBER
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_passkey_input_number_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_PASSKEY_INPUT_NUMBER
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_passkey_input_number_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_PASSKEY_INPUT_CANCEL
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_passkey_input_cancel_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_PASSKEY_INPUT_CANCEL
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_passkey_input_cancel_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_PASSKEY_INPUT_CANCEL
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_passkey_input_cancel_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_NUMERIC_COMPARISON_REQUEST
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_numeric_comparison_request_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_NUMERIC_COMPARISON_REQUEST
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_numeric_comparison_request_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_NUMERIC_COMPARISON_REQUEST
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_numeric_comparison_request_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
    /**
     * @brief Get field passkey from event SM_EVENT_NUMERIC_COMPARISON_REQUEST
     * @param event packet
     * @return passkey
     * @note: btstack_type 4
     */
    static inline uint32_t sm_event_numeric_comparison_request_get_passkey(const uint8_t *event)
    {
        return little_endian_read_32(event, 11);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_NUMERIC_COMPARISON_CANCEL
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_numeric_comparison_cancel_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_NUMERIC_COMPARISON_CANCEL
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_numeric_comparison_cancel_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_NUMERIC_COMPARISON_CANCEL
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_numeric_comparison_cancel_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_IDENTITY_RESOLVING_STARTED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_identity_resolving_started_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_IDENTITY_RESOLVING_STARTED
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_identity_resolving_started_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_IDENTITY_RESOLVING_STARTED
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_identity_resolving_started_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_IDENTITY_RESOLVING_FAILED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_identity_resolving_failed_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_IDENTITY_RESOLVING_FAILED
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_identity_resolving_failed_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_IDENTITY_RESOLVING_FAILED
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_identity_resolving_failed_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_IDENTITY_RESOLVING_SUCCEEDED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_identity_resolving_succeeded_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_IDENTITY_RESOLVING_SUCCEEDED
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_identity_resolving_succeeded_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_IDENTITY_RESOLVING_SUCCEEDED
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_identity_resolving_succeeded_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
    /**
     * @brief Get field identity_addr_type from event SM_EVENT_IDENTITY_RESOLVING_SUCCEEDED
     * @param event packet
     * @return identity_addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_identity_resolving_succeeded_get_identity_addr_type(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field identity_address from event SM_EVENT_IDENTITY_RESOLVING_SUCCEEDED
     * @param event packet
     * @param Pointer to storage for identity_address
     * @note: btstack_type B
     */
    static inline void sm_event_identity_resolving_succeeded_get_identity_address(const uint8_t *event, bd_addr_t identity_address)
    {
        reverse_bd_addr(&event[12], identity_address);
    }
    /**
     * @brief Get field index_internal from event SM_EVENT_IDENTITY_RESOLVING_SUCCEEDED
     * @param event packet
     * @return index_internal
     * @note: btstack_type 2
     */
    static inline uint16_t sm_event_identity_resolving_succeeded_get_index_internal(const uint8_t *event)
    {
        return little_endian_read_16(event, 18);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_AUTHORIZATION_REQUEST
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_authorization_request_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_AUTHORIZATION_REQUEST
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_authorization_request_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_AUTHORIZATION_REQUEST
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_authorization_request_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_AUTHORIZATION_RESULT
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_authorization_result_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_AUTHORIZATION_RESULT
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_authorization_result_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_AUTHORIZATION_RESULT
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_authorization_result_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
    /**
     * @brief Get field authorization_result from event SM_EVENT_AUTHORIZATION_RESULT
     * @param event packet
     * @return authorization_result
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_authorization_result_get_authorization_result(const uint8_t *event)
    {
        return event[11];
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_KEYPRESS_NOTIFICATION
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_keypress_notification_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field action from event SM_EVENT_KEYPRESS_NOTIFICATION
     * @param event packet
     * @return action
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_keypress_notification_get_action(const uint8_t *event)
    {
        return event[4];
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event SM_EVENT_IDENTITY_CREATED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t sm_event_identity_created_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field addr_type from event SM_EVENT_IDENTITY_CREATED
     * @param event packet
     * @return addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_identity_created_get_addr_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field address from event SM_EVENT_IDENTITY_CREATED
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void sm_event_identity_created_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[5], address);
    }
    /**
     * @brief Get field identity_addr_type from event SM_EVENT_IDENTITY_CREATED
     * @param event packet
     * @return identity_addr_type
     * @note: btstack_type 1
     */
    static inline uint8_t sm_event_identity_created_get_identity_addr_type(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field identity_address from event SM_EVENT_IDENTITY_CREATED
     * @param event packet
     * @param Pointer to storage for identity_address
     * @note: btstack_type B
     */
    static inline void sm_event_identity_created_get_identity_address(const uint8_t *event, bd_addr_t identity_address)
    {
        reverse_bd_addr(&event[12], identity_address);
    }
#endif

    /**
     * @brief Get field handle from event GAP_EVENT_SECURITY_LEVEL
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t gap_event_security_level_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 2);
    }
    /**
     * @brief Get field security_level from event GAP_EVENT_SECURITY_LEVEL
     * @param event packet
     * @return security_level
     * @note: btstack_type 1
     */
    static inline uint8_t gap_event_security_level_get_security_level(const uint8_t *event)
    {
        return event[4];
    }

    /**
     * @brief Get field status from event GAP_EVENT_DEDICATED_BONDING_COMPLETED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t gap_event_dedicated_bonding_completed_get_status(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field address from event GAP_EVENT_DEDICATED_BONDING_COMPLETED
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void gap_event_dedicated_bonding_completed_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[3], address);
    }

    /**
     * @brief Get field advertising_event_type from event GAP_EVENT_ADVERTISING_REPORT
     * @param event packet
     * @return advertising_event_type
     * @note: btstack_type 1
     */
    static inline uint8_t gap_event_advertising_report_get_advertising_event_type(const uint8_t *event)
    {
        return event[2];
    }
    /**
     * @brief Get field address_type from event GAP_EVENT_ADVERTISING_REPORT
     * @param event packet
     * @return address_type
     * @note: btstack_type 1
     */
    static inline uint8_t gap_event_advertising_report_get_address_type(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field address from event GAP_EVENT_ADVERTISING_REPORT
     * @param event packet
     * @param Pointer to storage for address
     * @note: btstack_type B
     */
    static inline void gap_event_advertising_report_get_address(const uint8_t *event, bd_addr_t address)
    {
        reverse_bd_addr(&event[4], address);
    }
    /**
     * @brief Get field rssi from event GAP_EVENT_ADVERTISING_REPORT
     * @param event packet
     * @return rssi
     * @note: btstack_type 1
     */
    static inline uint8_t gap_event_advertising_report_get_rssi(const uint8_t *event)
    {
        return event[10];
    }
    /**
     * @brief Get field data_length from event GAP_EVENT_ADVERTISING_REPORT
     * @param event packet
     * @return data_length
     * @note: btstack_type J
     */
    static inline int gap_event_advertising_report_get_data_length(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field data from event GAP_EVENT_ADVERTISING_REPORT
     * @param event packet
     * @return data
     * @note: btstack_type V
     */
    static inline const uint8_t *gap_event_advertising_report_get_data(const uint8_t *event)
    {
        return &event[12];
    }

    /**
     * @brief Get field bd_addr from event GAP_EVENT_INQUIRY_RESULT
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void gap_event_inquiry_result_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[2], bd_addr);
    }
    /**
     * @brief Get field page_scan_repetition_mode from event GAP_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return page_scan_repetition_mode
     * @note: btstack_type 1
     */
    static inline uint8_t gap_event_inquiry_result_get_page_scan_repetition_mode(const uint8_t *event)
    {
        return event[8];
    }
    /**
     * @brief Get field class_of_device from event GAP_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return class_of_device
     * @note: btstack_type 3
     */
    static inline uint32_t gap_event_inquiry_result_get_class_of_device(const uint8_t *event)
    {
        return little_endian_read_24(event, 9);
    }
    /**
     * @brief Get field clock_offset from event GAP_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return clock_offset
     * @note: btstack_type 2
     */
    static inline uint16_t gap_event_inquiry_result_get_clock_offset(const uint8_t *event)
    {
        return little_endian_read_16(event, 12);
    }
    /**
     * @brief Get field rssi_available from event GAP_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return rssi_available
     * @note: btstack_type 1
     */
    static inline uint8_t gap_event_inquiry_result_get_rssi_available(const uint8_t *event)
    {
        return event[14];
    }
    /**
     * @brief Get field rssi from event GAP_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return rssi
     * @note: btstack_type 1
     */
    static inline uint8_t gap_event_inquiry_result_get_rssi(const uint8_t *event)
    {
        return event[15];
    }
    /**
     * @brief Get field name_available from event GAP_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return name_available
     * @note: btstack_type 1
     */
    static inline uint8_t gap_event_inquiry_result_get_name_available(const uint8_t *event)
    {
        return event[16];
    }
    /**
     * @brief Get field name_len from event GAP_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return name_len
     * @note: btstack_type J
     */
    static inline int gap_event_inquiry_result_get_name_len(const uint8_t *event)
    {
        return event[17];
    }
    /**
     * @brief Get field name from event GAP_EVENT_INQUIRY_RESULT
     * @param event packet
     * @return name
     * @note: btstack_type V
     */
    static inline const uint8_t *gap_event_inquiry_result_get_name(const uint8_t *event)
    {
        return &event[18];
    }

    /**
     * @brief Get field status from event GAP_EVENT_INQUIRY_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t gap_event_inquiry_complete_get_status(const uint8_t *event)
    {
        return event[2];
    }

    /**
     * @brief Get field status from event HCI_SUBEVENT_LE_CONNECTION_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_subevent_le_connection_complete_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field connection_handle from event HCI_SUBEVENT_LE_CONNECTION_COMPLETE
     * @param event packet
     * @return connection_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_subevent_le_connection_complete_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field role from event HCI_SUBEVENT_LE_CONNECTION_COMPLETE
     * @param event packet
     * @return role
     * @note: btstack_type 1
     */
    static inline uint8_t hci_subevent_le_connection_complete_get_role(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field peer_address_type from event HCI_SUBEVENT_LE_CONNECTION_COMPLETE
     * @param event packet
     * @return peer_address_type
     * @note: btstack_type 1
     */
    static inline uint8_t hci_subevent_le_connection_complete_get_peer_address_type(const uint8_t *event)
    {
        return event[7];
    }
    /**
     * @brief Get field peer_address from event HCI_SUBEVENT_LE_CONNECTION_COMPLETE
     * @param event packet
     * @param Pointer to storage for peer_address
     * @note: btstack_type B
     */
    static inline void hci_subevent_le_connection_complete_get_peer_address(const uint8_t *event, bd_addr_t peer_address)
    {
        reverse_bd_addr(&event[8], peer_address);
    }
    /**
     * @brief Get field conn_interval from event HCI_SUBEVENT_LE_CONNECTION_COMPLETE
     * @param event packet
     * @return conn_interval
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_connection_complete_get_conn_interval(const uint8_t *event)
    {
        return little_endian_read_16(event, 14);
    }
    /**
     * @brief Get field conn_latency from event HCI_SUBEVENT_LE_CONNECTION_COMPLETE
     * @param event packet
     * @return conn_latency
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_connection_complete_get_conn_latency(const uint8_t *event)
    {
        return little_endian_read_16(event, 16);
    }
    /**
     * @brief Get field supervision_timeout from event HCI_SUBEVENT_LE_CONNECTION_COMPLETE
     * @param event packet
     * @return supervision_timeout
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_connection_complete_get_supervision_timeout(const uint8_t *event)
    {
        return little_endian_read_16(event, 18);
    }
    /**
     * @brief Get field master_clock_accuracy from event HCI_SUBEVENT_LE_CONNECTION_COMPLETE
     * @param event packet
     * @return master_clock_accuracy
     * @note: btstack_type 1
     */
    static inline uint8_t hci_subevent_le_connection_complete_get_master_clock_accuracy(const uint8_t *event)
    {
        return event[20];
    }

    /**
     * @brief Get field status from event HCI_SUBEVENT_LE_CONNECTION_UPDATE_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_subevent_le_connection_update_complete_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field connection_handle from event HCI_SUBEVENT_LE_CONNECTION_UPDATE_COMPLETE
     * @param event packet
     * @return connection_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_subevent_le_connection_update_complete_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field conn_interval from event HCI_SUBEVENT_LE_CONNECTION_UPDATE_COMPLETE
     * @param event packet
     * @return conn_interval
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_connection_update_complete_get_conn_interval(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }
    /**
     * @brief Get field conn_latency from event HCI_SUBEVENT_LE_CONNECTION_UPDATE_COMPLETE
     * @param event packet
     * @return conn_latency
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_connection_update_complete_get_conn_latency(const uint8_t *event)
    {
        return little_endian_read_16(event, 8);
    }
    /**
     * @brief Get field supervision_timeout from event HCI_SUBEVENT_LE_CONNECTION_UPDATE_COMPLETE
     * @param event packet
     * @return supervision_timeout
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_connection_update_complete_get_supervision_timeout(const uint8_t *event)
    {
        return little_endian_read_16(event, 10);
    }

    /**
     * @brief Get field connection_handle from event HCI_SUBEVENT_LE_READ_REMOTE_USED_FEATURES_COMPLETE
     * @param event packet
     * @return connection_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_subevent_le_read_remote_used_features_complete_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field random_number from event HCI_SUBEVENT_LE_READ_REMOTE_USED_FEATURES_COMPLETE
     * @param event packet
     * @return random_number
     * @note: btstack_type D
     */
    static inline const uint8_t *hci_subevent_le_read_remote_used_features_complete_get_random_number(const uint8_t *event)
    {
        return (const uint8_t *) &event[5];
    }
    /**
     * @brief Get field encryption_diversifier from event HCI_SUBEVENT_LE_READ_REMOTE_USED_FEATURES_COMPLETE
     * @param event packet
     * @return encryption_diversifier
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_read_remote_used_features_complete_get_encryption_diversifier(const uint8_t *event)
    {
        return little_endian_read_16(event, 13);
    }

    /**
     * @brief Get field connection_handle from event HCI_SUBEVENT_LE_LONG_TERM_KEY_REQUEST
     * @param event packet
     * @return connection_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_subevent_le_long_term_key_request_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field random_number from event HCI_SUBEVENT_LE_LONG_TERM_KEY_REQUEST
     * @param event packet
     * @return random_number
     * @note: btstack_type D
     */
    static inline const uint8_t *hci_subevent_le_long_term_key_request_get_random_number(const uint8_t *event)
    {
        return (const uint8_t *) &event[5];
    }
    /**
     * @brief Get field encryption_diversifier from event HCI_SUBEVENT_LE_LONG_TERM_KEY_REQUEST
     * @param event packet
     * @return encryption_diversifier
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_long_term_key_request_get_encryption_diversifier(const uint8_t *event)
    {
        return little_endian_read_16(event, 13);
    }

    /**
     * @brief Get field connection_handle from event HCI_SUBEVENT_LE_REMOTE_CONNECTION_PARAMETER_REQUEST
     * @param event packet
     * @return connection_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_subevent_le_remote_connection_parameter_request_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field interval_min from event HCI_SUBEVENT_LE_REMOTE_CONNECTION_PARAMETER_REQUEST
     * @param event packet
     * @return interval_min
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_remote_connection_parameter_request_get_interval_min(const uint8_t *event)
    {
        return little_endian_read_16(event, 5);
    }
    /**
     * @brief Get field interval_max from event HCI_SUBEVENT_LE_REMOTE_CONNECTION_PARAMETER_REQUEST
     * @param event packet
     * @return interval_max
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_remote_connection_parameter_request_get_interval_max(const uint8_t *event)
    {
        return little_endian_read_16(event, 7);
    }
    /**
     * @brief Get field latency from event HCI_SUBEVENT_LE_REMOTE_CONNECTION_PARAMETER_REQUEST
     * @param event packet
     * @return latency
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_remote_connection_parameter_request_get_latency(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }
    /**
     * @brief Get field timeout from event HCI_SUBEVENT_LE_REMOTE_CONNECTION_PARAMETER_REQUEST
     * @param event packet
     * @return timeout
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_remote_connection_parameter_request_get_timeout(const uint8_t *event)
    {
        return little_endian_read_16(event, 11);
    }

    /**
     * @brief Get field connection_handle from event HCI_SUBEVENT_LE_DATA_LENGTH_CHANGE
     * @param event packet
     * @return connection_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_subevent_le_data_length_change_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field max_tx_octets from event HCI_SUBEVENT_LE_DATA_LENGTH_CHANGE
     * @param event packet
     * @return max_tx_octets
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_data_length_change_get_max_tx_octets(const uint8_t *event)
    {
        return little_endian_read_16(event, 5);
    }
    /**
     * @brief Get field max_tx_time from event HCI_SUBEVENT_LE_DATA_LENGTH_CHANGE
     * @param event packet
     * @return max_tx_time
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_data_length_change_get_max_tx_time(const uint8_t *event)
    {
        return little_endian_read_16(event, 7);
    }
    /**
     * @brief Get field max_rx_octets from event HCI_SUBEVENT_LE_DATA_LENGTH_CHANGE
     * @param event packet
     * @return max_rx_octets
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_data_length_change_get_max_rx_octets(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }
    /**
     * @brief Get field max_rx_time from event HCI_SUBEVENT_LE_DATA_LENGTH_CHANGE
     * @param event packet
     * @return max_rx_time
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_data_length_change_get_max_rx_time(const uint8_t *event)
    {
        return little_endian_read_16(event, 11);
    }

    /**
     * @brief Get field status from event HCI_SUBEVENT_LE_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_subevent_le_read_local_p256_public_key_complete_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field dhkey_x from event HCI_SUBEVENT_LE_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE
     * @param event packet
     * @param Pointer to storage for dhkey_x
     * @note: btstack_type Q
     */
    static inline void hci_subevent_le_read_local_p256_public_key_complete_get_dhkey_x(const uint8_t *event, uint8_t *dhkey_x)
    {
        reverse_bytes(&event[4], dhkey_x, 32);
    }
    /**
     * @brief Get field dhkey_y from event HCI_SUBEVENT_LE_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE
     * @param event packet
     * @param Pointer to storage for dhkey_y
     * @note: btstack_type Q
     */
    static inline void hci_subevent_le_read_local_p256_public_key_complete_get_dhkey_y(const uint8_t *event, uint8_t *dhkey_y)
    {
        reverse_bytes(&event[36], dhkey_y, 32);
    }

    /**
     * @brief Get field status from event HCI_SUBEVENT_LE_GENERATE_DHKEY_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_subevent_le_generate_dhkey_complete_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field dhkey from event HCI_SUBEVENT_LE_GENERATE_DHKEY_COMPLETE
     * @param event packet
     * @param Pointer to storage for dhkey
     * @note: btstack_type Q
     */
    static inline void hci_subevent_le_generate_dhkey_complete_get_dhkey(const uint8_t *event, uint8_t *dhkey)
    {
        reverse_bytes(&event[4], dhkey, 32);
    }

    /**
     * @brief Get field status from event HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hci_subevent_le_enhanced_connection_complete_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field connection_handle from event HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE
     * @param event packet
     * @return connection_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hci_subevent_le_enhanced_connection_complete_get_connection_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field role from event HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE
     * @param event packet
     * @return role
     * @note: btstack_type 1
     */
    static inline uint8_t hci_subevent_le_enhanced_connection_complete_get_role(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field peer_address_type from event HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE
     * @param event packet
     * @return peer_address_type
     * @note: btstack_type 1
     */
    static inline uint8_t hci_subevent_le_enhanced_connection_complete_get_peer_address_type(const uint8_t *event)
    {
        return event[7];
    }
    /**
     * @brief Get field perr_addresss from event HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE
     * @param event packet
     * @param Pointer to storage for perr_addresss
     * @note: btstack_type B
     */
    static inline void hci_subevent_le_enhanced_connection_complete_get_peer_addresss(const uint8_t *event, bd_addr_t perr_addresss)
    {
        reverse_bd_addr(&event[8], perr_addresss);
    }
    static inline uint8_t *hci_subevent_le_enhanced_connection_complete_get_peer_addresss_ptr(const uint8_t *event)
    {
        return (uint8_t *)&event[8];
    }
    /**
     * @brief Get field local_resolvable_private_addres from event HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE
     * @param event packet
     * @param Pointer to storage for local_resolvable_private_addres
     * @note: btstack_type B
     */
    static inline void hci_subevent_le_enhanced_connection_complete_get_local_resolvable_private_addres(const uint8_t *event, bd_addr_t local_resolvable_private_addres)
    {
        reverse_bd_addr(&event[14], local_resolvable_private_addres);
    }
    /**
     * @brief Get field peer_resolvable_private_addres from event HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE
     * @param event packet
     * @param Pointer to storage for peer_resolvable_private_addres
     * @note: btstack_type B
     */
    static inline void hci_subevent_le_enhanced_connection_complete_get_peer_resolvable_private_addres(const uint8_t *event, bd_addr_t peer_resolvable_private_addres)
    {
        reverse_bd_addr(&event[20], peer_resolvable_private_addres);
    }
    /**
     * @brief Get field conn_interval from event HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE
     * @param event packet
     * @return conn_interval
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_enhanced_connection_complete_get_conn_interval(const uint8_t *event)
    {
        return little_endian_read_16(event, 26);
    }
    /**
     * @brief Get field conn_latency from event HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE
     * @param event packet
     * @return conn_latency
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_enhanced_connection_complete_get_conn_latency(const uint8_t *event)
    {
        return little_endian_read_16(event, 28);
    }
    /**
     * @brief Get field supervision_timeout from event HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE
     * @param event packet
     * @return supervision_timeout
     * @note: btstack_type 2
     */
    static inline uint16_t hci_subevent_le_enhanced_connection_complete_get_supervision_timeout(const uint8_t *event)
    {
        return little_endian_read_16(event, 30);
    }
    /**
     * @brief Get field master_clock_accuracy from event HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE
     * @param event packet
     * @return master_clock_accuracy
     * @note: btstack_type 1
     */
    static inline uint8_t hci_subevent_le_enhanced_connection_complete_get_master_clock_accuracy(const uint8_t *event)
    {
        return event[32];
    }

    /**
     * @brief Get field status from event HSP_SUBEVENT_RFCOMM_CONNECTION_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hsp_subevent_rfcomm_connection_complete_get_status(const uint8_t *event)
    {
        return event[3];
    }

    /**
     * @brief Get field status from event HSP_SUBEVENT_RFCOMM_DISCONNECTION_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hsp_subevent_rfcomm_disconnection_complete_get_status(const uint8_t *event)
    {
        return event[3];
    }

    /**
     * @brief Get field status from event HSP_SUBEVENT_AUDIO_CONNECTION_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hsp_subevent_audio_connection_complete_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field handle from event HSP_SUBEVENT_AUDIO_CONNECTION_COMPLETE
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hsp_subevent_audio_connection_complete_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }

    /**
     * @brief Get field status from event HSP_SUBEVENT_AUDIO_DISCONNECTION_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hsp_subevent_audio_disconnection_complete_get_status(const uint8_t *event)
    {
        return event[3];
    }


    /**
     * @brief Get field gain from event HSP_SUBEVENT_MICROPHONE_GAIN_CHANGED
     * @param event packet
     * @return gain
     * @note: btstack_type 1
     */
    static inline uint8_t hsp_subevent_microphone_gain_changed_get_gain(const uint8_t *event)
    {
        return event[3];
    }

    /**
     * @brief Get field gain from event HSP_SUBEVENT_SPEAKER_GAIN_CHANGED
     * @param event packet
     * @return gain
     * @note: btstack_type 1
     */
    static inline uint8_t hsp_subevent_speaker_gain_changed_get_gain(const uint8_t *event)
    {
        return event[3];
    }

    /**
     * @brief Get field value_length from event HSP_SUBEVENT_HS_COMMAND
     * @param event packet
     * @return value_length
     * @note: btstack_type J
     */
    static inline int hsp_subevent_hs_command_get_value_length(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field value from event HSP_SUBEVENT_HS_COMMAND
     * @param event packet
     * @return value
     * @note: btstack_type V
     */
    static inline const uint8_t *hsp_subevent_hs_command_get_value(const uint8_t *event)
    {
        return &event[4];
    }

    /**
     * @brief Get field value_length from event HSP_SUBEVENT_AG_INDICATION
     * @param event packet
     * @return value_length
     * @note: btstack_type J
     */
    static inline int hsp_subevent_ag_indication_get_value_length(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field value from event HSP_SUBEVENT_AG_INDICATION
     * @param event packet
     * @return value
     * @note: btstack_type V
     */
    static inline const uint8_t *hsp_subevent_ag_indication_get_value(const uint8_t *event)
    {
        return &event[4];
    }

    /**
     * @brief Get field status from event HFP_SUBEVENT_SERVICE_LEVEL_CONNECTION_ESTABLISHED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_service_level_connection_established_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field con_handle from event HFP_SUBEVENT_SERVICE_LEVEL_CONNECTION_ESTABLISHED
     * @param event packet
     * @return con_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hfp_subevent_service_level_connection_established_get_con_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field bd_addr from event HFP_SUBEVENT_SERVICE_LEVEL_CONNECTION_ESTABLISHED
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hfp_subevent_service_level_connection_established_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[6], bd_addr);
    }


    /**
     * @brief Get field status from event HFP_SUBEVENT_AUDIO_CONNECTION_ESTABLISHED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_audio_connection_established_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field handle from event HFP_SUBEVENT_AUDIO_CONNECTION_ESTABLISHED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hfp_subevent_audio_connection_established_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 4);
    }
    /**
     * @brief Get field bd_addr from event HFP_SUBEVENT_AUDIO_CONNECTION_ESTABLISHED
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hfp_subevent_audio_connection_established_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[6], bd_addr);
    }
    /**
     * @brief Get field negotiated_codec from event HFP_SUBEVENT_AUDIO_CONNECTION_ESTABLISHED
     * @param event packet
     * @return negotiated_codec
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_audio_connection_established_get_negotiated_codec(const uint8_t *event)
    {
        return event[12];
    }


    /**
     * @brief Get field status from event HFP_SUBEVENT_COMPLETE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_complete_get_status(const uint8_t *event)
    {
        return event[3];
    }

    /**
     * @brief Get field indicator_index from event HFP_SUBEVENT_AG_INDICATOR_STATUS_CHANGED
     * @param event packet
     * @return indicator_index
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_ag_indicator_status_changed_get_indicator_index(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field indicator_status from event HFP_SUBEVENT_AG_INDICATOR_STATUS_CHANGED
     * @param event packet
     * @return indicator_status
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_ag_indicator_status_changed_get_indicator_status(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field indicator_name from event HFP_SUBEVENT_AG_INDICATOR_STATUS_CHANGED
     * @param event packet
     * @return indicator_name
     * @note: btstack_type T
     */
    static inline const char *hfp_subevent_ag_indicator_status_changed_get_indicator_name(const uint8_t *event)
    {
        return (const char *) &event[5];
    }

    /**
     * @brief Get field network_operator_mode from event HFP_SUBEVENT_NETWORK_OPERATOR_CHANGED
     * @param event packet
     * @return network_operator_mode
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_network_operator_changed_get_network_operator_mode(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field network_operator_format from event HFP_SUBEVENT_NETWORK_OPERATOR_CHANGED
     * @param event packet
     * @return network_operator_format
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_network_operator_changed_get_network_operator_format(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field network_operator_name from event HFP_SUBEVENT_NETWORK_OPERATOR_CHANGED
     * @param event packet
     * @return network_operator_name
     * @note: btstack_type T
     */
    static inline const char *hfp_subevent_network_operator_changed_get_network_operator_name(const uint8_t *event)
    {
        return (const char *) &event[5];
    }

    /**
     * @brief Get field error from event HFP_SUBEVENT_EXTENDED_AUDIO_GATEWAY_ERROR
     * @param event packet
     * @return error
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_extended_audio_gateway_error_get_error(const uint8_t *event)
    {
        return event[3];
    }




    /**
     * @brief Get field number from event HFP_SUBEVENT_PLACE_CALL_WITH_NUMBER
     * @param event packet
     * @return number
     * @note: btstack_type T
     */
    static inline const char *hfp_subevent_place_call_with_number_get_number(const uint8_t *event)
    {
        return (const char *) &event[3];
    }


    /**
     * @brief Get field number from event HFP_SUBEVENT_NUMBER_FOR_VOICE_TAG
     * @param event packet
     * @return number
     * @note: btstack_type T
     */
    static inline const char *hfp_subevent_number_for_voice_tag_get_number(const uint8_t *event)
    {
        return (const char *) &event[3];
    }

    /**
     * @brief Get field dtmf from event HFP_SUBEVENT_TRANSMIT_DTMF_CODES
     * @param event packet
     * @return dtmf
     * @note: btstack_type T
     */
    static inline const char *hfp_subevent_transmit_dtmf_codes_get_dtmf(const uint8_t *event)
    {
        return (const char *) &event[3];
    }




    /**
     * @brief Get field status from event HFP_SUBEVENT_SPEAKER_VOLUME
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_speaker_volume_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field gain from event HFP_SUBEVENT_SPEAKER_VOLUME
     * @param event packet
     * @return gain
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_speaker_volume_get_gain(const uint8_t *event)
    {
        return event[4];
    }

    /**
     * @brief Get field status from event HFP_SUBEVENT_MICROPHONE_VOLUME
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_microphone_volume_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field gain from event HFP_SUBEVENT_MICROPHONE_VOLUME
     * @param event packet
     * @return gain
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_microphone_volume_get_gain(const uint8_t *event)
    {
        return event[4];
    }

    /**
     * @brief Get field type from event HFP_SUBEVENT_CALL_WAITING_NOTIFICATION
     * @param event packet
     * @return type
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_call_waiting_notification_get_type(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field number from event HFP_SUBEVENT_CALL_WAITING_NOTIFICATION
     * @param event packet
     * @return number
     * @note: btstack_type T
     */
    static inline const char *hfp_subevent_call_waiting_notification_get_number(const uint8_t *event)
    {
        return (const char *) &event[4];
    }

    /**
     * @brief Get field type from event HFP_SUBEVENT_CALLING_LINE_IDENTIFICATION_NOTIFICATION
     * @param event packet
     * @return type
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_calling_line_identification_notification_get_type(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field number from event HFP_SUBEVENT_CALLING_LINE_IDENTIFICATION_NOTIFICATION
     * @param event packet
     * @return number
     * @note: btstack_type T
     */
    static inline const char *hfp_subevent_calling_line_identification_notification_get_number(const uint8_t *event)
    {
        return (const char *) &event[4];
    }

    /**
     * @brief Get field clcc_idx from event HFP_SUBEVENT_ENHANCED_CALL_STATUS
     * @param event packet
     * @return clcc_idx
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_enhanced_call_status_get_clcc_idx(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field clcc_dir from event HFP_SUBEVENT_ENHANCED_CALL_STATUS
     * @param event packet
     * @return clcc_dir
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_enhanced_call_status_get_clcc_dir(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field clcc_status from event HFP_SUBEVENT_ENHANCED_CALL_STATUS
     * @param event packet
     * @return clcc_status
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_enhanced_call_status_get_clcc_status(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field clcc_mpty from event HFP_SUBEVENT_ENHANCED_CALL_STATUS
     * @param event packet
     * @return clcc_mpty
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_enhanced_call_status_get_clcc_mpty(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field bnip_type from event HFP_SUBEVENT_ENHANCED_CALL_STATUS
     * @param event packet
     * @return bnip_type
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_enhanced_call_status_get_bnip_type(const uint8_t *event)
    {
        return event[7];
    }
    /**
     * @brief Get field bnip_number from event HFP_SUBEVENT_ENHANCED_CALL_STATUS
     * @param event packet
     * @return bnip_number
     * @note: btstack_type T
     */
    static inline const char *hfp_subevent_enhanced_call_status_get_bnip_number(const uint8_t *event)
    {
        return (const char *) &event[8];
    }

    /**
     * @brief Get field status from event HFP_SUBEVENT_SUBSCRIBER_NUMBER_INFORMATION
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_subscriber_number_information_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field bnip_type from event HFP_SUBEVENT_SUBSCRIBER_NUMBER_INFORMATION
     * @param event packet
     * @return bnip_type
     * @note: btstack_type 1
     */
    static inline uint8_t hfp_subevent_subscriber_number_information_get_bnip_type(const uint8_t *event)
    {
        return event[4];
    }
    /**
     * @brief Get field bnip_number from event HFP_SUBEVENT_SUBSCRIBER_NUMBER_INFORMATION
     * @param event packet
     * @return bnip_number
     * @note: btstack_type T
     */
    static inline const char *hfp_subevent_subscriber_number_information_get_bnip_number(const uint8_t *event)
    {
        return (const char *) &event[5];
    }

    /**
     * @brief Get field value from event HFP_SUBEVENT_RESPONSE_AND_HOLD_STATUS
     * @param event packet
     * @return value
     * @note: btstack_type T
     */
    static inline const char *hfp_subevent_response_and_hold_status_get_value(const uint8_t *event)
    {
        return (const char *) &event[3];
    }

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event ANCS_SUBEVENT_CLIENT_CONNECTED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t ancs_subevent_client_connected_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event ANCS_SUBEVENT_CLIENT_NOTIFICATION
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t ancs_subevent_client_notification_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field attribute_id from event ANCS_SUBEVENT_CLIENT_NOTIFICATION
     * @param event packet
     * @return attribute_id
     * @note: btstack_type 2
     */
    static inline uint16_t ancs_subevent_client_notification_get_attribute_id(const uint8_t *event)
    {
        return little_endian_read_16(event, 5);
    }
    /**
     * @brief Get field text from event ANCS_SUBEVENT_CLIENT_NOTIFICATION
     * @param event packet
     * @return text
     * @note: btstack_type T
     */
    static inline const char *ancs_subevent_client_notification_get_text(const uint8_t *event)
    {
        return (const char *) &event[7];
    }
#endif

#ifdef ENABLE_BLE
    /**
     * @brief Get field handle from event ANCS_SUBEVENT_CLIENT_DISCONNECTED
     * @param event packet
     * @return handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t ancs_subevent_client_disconnected_get_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
#endif

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_SIGNALING_ACCEPT
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_accept_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event AVDTP_SUBEVENT_SIGNALING_ACCEPT
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_accept_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field signal_identifier from event AVDTP_SUBEVENT_SIGNALING_ACCEPT
     * @param event packet
     * @return signal_identifier
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_accept_get_signal_identifier(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_SIGNALING_REJECT
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_reject_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event AVDTP_SUBEVENT_SIGNALING_REJECT
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_reject_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field signal_identifier from event AVDTP_SUBEVENT_SIGNALING_REJECT
     * @param event packet
     * @return signal_identifier
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_reject_get_signal_identifier(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_SIGNALING_GENERAL_REJECT
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_general_reject_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event AVDTP_SUBEVENT_SIGNALING_GENERAL_REJECT
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_general_reject_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field signal_identifier from event AVDTP_SUBEVENT_SIGNALING_GENERAL_REJECT
     * @param event packet
     * @return signal_identifier
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_general_reject_get_signal_identifier(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_SIGNALING_CONNECTION_ESTABLISHED
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_connection_established_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field bd_addr from event AVDTP_SUBEVENT_SIGNALING_CONNECTION_ESTABLISHED
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void avdtp_subevent_signaling_connection_established_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[5], bd_addr);
    }
    /**
     * @brief Get field status from event AVDTP_SUBEVENT_SIGNALING_CONNECTION_ESTABLISHED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_connection_established_get_status(const uint8_t *event)
    {
        return event[11];
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_SIGNALING_CONNECTION_RELEASED
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_connection_released_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_SIGNALING_SEP_FOUND
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_sep_found_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field remote_seid from event AVDTP_SUBEVENT_SIGNALING_SEP_FOUND
     * @param event packet
     * @return remote_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_sep_found_get_remote_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field in_use from event AVDTP_SUBEVENT_SIGNALING_SEP_FOUND
     * @param event packet
     * @return in_use
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_sep_found_get_in_use(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field media_type from event AVDTP_SUBEVENT_SIGNALING_SEP_FOUND
     * @param event packet
     * @return media_type
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_sep_found_get_media_type(const uint8_t *event)
    {
        return event[7];
    }
    /**
     * @brief Get field sep_type from event AVDTP_SUBEVENT_SIGNALING_SEP_FOUND
     * @param event packet
     * @return sep_type
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_sep_found_get_sep_type(const uint8_t *event)
    {
        return event[8];
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_media_codec_sbc_capability_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_capability_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field remote_seid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY
     * @param event packet
     * @return remote_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_capability_get_remote_seid(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field media_type from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY
     * @param event packet
     * @return media_type
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_capability_get_media_type(const uint8_t *event)
    {
        return event[7];
    }
    /**
     * @brief Get field sampling_frequency_bitmap from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY
     * @param event packet
     * @return sampling_frequency_bitmap
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_capability_get_sampling_frequency_bitmap(const uint8_t *event)
    {
        return event[8];
    }
    /**
     * @brief Get field channel_mode_bitmap from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY
     * @param event packet
     * @return channel_mode_bitmap
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_capability_get_channel_mode_bitmap(const uint8_t *event)
    {
        return event[9];
    }
    /**
     * @brief Get field block_length_bitmap from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY
     * @param event packet
     * @return block_length_bitmap
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_capability_get_block_length_bitmap(const uint8_t *event)
    {
        return event[10];
    }
    /**
     * @brief Get field subbands_bitmap from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY
     * @param event packet
     * @return subbands_bitmap
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_capability_get_subbands_bitmap(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field allocation_method_bitmap from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY
     * @param event packet
     * @return allocation_method_bitmap
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_capability_get_allocation_method_bitmap(const uint8_t *event)
    {
        return event[12];
    }
    /**
     * @brief Get field min_bitpool_value from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY
     * @param event packet
     * @return min_bitpool_value
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_capability_get_min_bitpool_value(const uint8_t *event)
    {
        return event[13];
    }
    /**
     * @brief Get field max_bitpool_value from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CAPABILITY
     * @param event packet
     * @return max_bitpool_value
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_capability_get_max_bitpool_value(const uint8_t *event)
    {
        return event[14];
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CAPABILITY
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_media_codec_other_capability_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CAPABILITY
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_other_capability_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field remote_seid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CAPABILITY
     * @param event packet
     * @return remote_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_other_capability_get_remote_seid(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field media_type from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CAPABILITY
     * @param event packet
     * @return media_type
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_other_capability_get_media_type(const uint8_t *event)
    {
        return event[7];
    }
    /**
     * @brief Get field media_codec_type from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CAPABILITY
     * @param event packet
     * @return media_codec_type
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_media_codec_other_capability_get_media_codec_type(const uint8_t *event)
    {
        return little_endian_read_16(event, 8);
    }
    /**
     * @brief Get field media_codec_information_len from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CAPABILITY
     * @param event packet
     * @return media_codec_information_len
     * @note: btstack_type L
     */
    static inline int avdtp_subevent_signaling_media_codec_other_capability_get_media_codec_information_len(const uint8_t *event)
    {
        return little_endian_read_16(event, 10);
    }
    /**
     * @brief Get field media_codec_information from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CAPABILITY
     * @param event packet
     * @return media_codec_information
     * @note: btstack_type V
     */
    static inline const uint8_t *avdtp_subevent_signaling_media_codec_other_capability_get_media_codec_information(const uint8_t *event)
    {
        return &event[12];
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field remote_seid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return remote_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_remote_seid(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field reconfigure from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return reconfigure
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_reconfigure(const uint8_t *event)
    {
        return event[7];
    }
    /**
     * @brief Get field media_type from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return media_type
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_media_type(const uint8_t *event)
    {
        return event[8];
    }
    /**
     * @brief Get field sampling_frequency from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return sampling_frequency
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_sampling_frequency(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }
    /**
     * @brief Get field channel_mode from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return channel_mode
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_channel_mode(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field num_channels from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return num_channels
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_num_channels(const uint8_t *event)
    {
        return event[12];
    }
    /**
     * @brief Get field block_length from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return block_length
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_block_length(const uint8_t *event)
    {
        return event[13];
    }
    /**
     * @brief Get field subbands from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return subbands
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_subbands(const uint8_t *event)
    {
        return event[14];
    }
    /**
     * @brief Get field allocation_method from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return allocation_method
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_allocation_method(const uint8_t *event)
    {
        return event[15];
    }
    /**
     * @brief Get field min_bitpool_value from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return min_bitpool_value
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_min_bitpool_value(const uint8_t *event)
    {
        return event[16];
    }
    /**
     * @brief Get field max_bitpool_value from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return max_bitpool_value
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_sbc_configuration_get_max_bitpool_value(const uint8_t *event)
    {
        return event[17];
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_media_codec_other_configuration_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_other_configuration_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field remote_seid from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return remote_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_other_configuration_get_remote_seid(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field reconfigure from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return reconfigure
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_other_configuration_get_reconfigure(const uint8_t *event)
    {
        return event[7];
    }
    /**
     * @brief Get field media_type from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return media_type
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_signaling_media_codec_other_configuration_get_media_type(const uint8_t *event)
    {
        return event[8];
    }
    /**
     * @brief Get field media_codec_type from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return media_codec_type
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_signaling_media_codec_other_configuration_get_media_codec_type(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }
    /**
     * @brief Get field media_codec_information_len from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return media_codec_information_len
     * @note: btstack_type L
     */
    static inline int avdtp_subevent_signaling_media_codec_other_configuration_get_media_codec_information_len(const uint8_t *event)
    {
        return little_endian_read_16(event, 11);
    }
    /**
     * @brief Get field media_codec_information from event AVDTP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return media_codec_information
     * @note: btstack_type V
     */
    static inline const uint8_t *avdtp_subevent_signaling_media_codec_other_configuration_get_media_codec_information(const uint8_t *event)
    {
        return &event[13];
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_STREAMING_CONNECTION_ESTABLISHED
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_streaming_connection_established_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field bd_addr from event AVDTP_SUBEVENT_STREAMING_CONNECTION_ESTABLISHED
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void avdtp_subevent_streaming_connection_established_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[5], bd_addr);
    }
    /**
     * @brief Get field local_seid from event AVDTP_SUBEVENT_STREAMING_CONNECTION_ESTABLISHED
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_streaming_connection_established_get_local_seid(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field remote_seid from event AVDTP_SUBEVENT_STREAMING_CONNECTION_ESTABLISHED
     * @param event packet
     * @return remote_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_streaming_connection_established_get_remote_seid(const uint8_t *event)
    {
        return event[12];
    }
    /**
     * @brief Get field status from event AVDTP_SUBEVENT_STREAMING_CONNECTION_ESTABLISHED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_streaming_connection_established_get_status(const uint8_t *event)
    {
        return event[13];
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_STREAMING_CONNECTION_RELEASED
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_streaming_connection_released_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event AVDTP_SUBEVENT_STREAMING_CONNECTION_RELEASED
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_streaming_connection_released_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field avdtp_cid from event AVDTP_SUBEVENT_STREAMING_CAN_SEND_MEDIA_PACKET_NOW
     * @param event packet
     * @return avdtp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_streaming_can_send_media_packet_now_get_avdtp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event AVDTP_SUBEVENT_STREAMING_CAN_SEND_MEDIA_PACKET_NOW
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t avdtp_subevent_streaming_can_send_media_packet_now_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field sequence_number from event AVDTP_SUBEVENT_STREAMING_CAN_SEND_MEDIA_PACKET_NOW
     * @param event packet
     * @return sequence_number
     * @note: btstack_type 2
     */
    static inline uint16_t avdtp_subevent_streaming_can_send_media_packet_now_get_sequence_number(const uint8_t *event)
    {
        return little_endian_read_16(event, 6);
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_STREAMING_CAN_SEND_MEDIA_PACKET_NOW
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_streaming_can_send_media_packet_now_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event A2DP_SUBEVENT_STREAMING_CAN_SEND_MEDIA_PACKET_NOW
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_streaming_can_send_media_packet_now_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field int_seid from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return int_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_int_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field acp_seid from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return acp_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_acp_seid(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field reconfigure from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return reconfigure
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_reconfigure(const uint8_t *event)
    {
        return event[7];
    }
    /**
     * @brief Get field media_type from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return media_type
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_media_type(const uint8_t *event)
    {
        return event[8];
    }
    /**
     * @brief Get field sampling_frequency from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return sampling_frequency
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_sampling_frequency(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }
    /**
     * @brief Get field channel_mode from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return channel_mode
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_channel_mode(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field num_channels from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return num_channels
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_num_channels(const uint8_t *event)
    {
        return event[12];
    }
    /**
     * @brief Get field block_length from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return block_length
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_block_length(const uint8_t *event)
    {
        return event[13];
    }
    /**
     * @brief Get field subbands from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return subbands
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_subbands(const uint8_t *event)
    {
        return event[14];
    }
    /**
     * @brief Get field allocation_method from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return allocation_method
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_allocation_method(const uint8_t *event)
    {
        return event[15];
    }
    /**
     * @brief Get field min_bitpool_value from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return min_bitpool_value
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_min_bitpool_value(const uint8_t *event)
    {
        return event[16];
    }
    /**
     * @brief Get field max_bitpool_value from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_SBC_CONFIGURATION
     * @param event packet
     * @return max_bitpool_value
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_sbc_configuration_get_max_bitpool_value(const uint8_t *event)
    {
        return event[17];
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_signaling_media_codec_other_configuration_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field int_seid from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return int_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_other_configuration_get_int_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field acp_seid from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return acp_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_other_configuration_get_acp_seid(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field reconfigure from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return reconfigure
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_other_configuration_get_reconfigure(const uint8_t *event)
    {
        return event[7];
    }
    /**
     * @brief Get field media_type from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return media_type
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_signaling_media_codec_other_configuration_get_media_type(const uint8_t *event)
    {
        return event[8];
    }
    /**
     * @brief Get field media_codec_type from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return media_codec_type
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_signaling_media_codec_other_configuration_get_media_codec_type(const uint8_t *event)
    {
        return little_endian_read_16(event, 9);
    }
    /**
     * @brief Get field media_codec_information_len from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return media_codec_information_len
     * @note: btstack_type L
     */
    static inline int a2dp_subevent_signaling_media_codec_other_configuration_get_media_codec_information_len(const uint8_t *event)
    {
        return little_endian_read_16(event, 11);
    }
    /**
     * @brief Get field media_codec_information from event A2DP_SUBEVENT_SIGNALING_MEDIA_CODEC_OTHER_CONFIGURATION
     * @param event packet
     * @return media_codec_information
     * @note: btstack_type V
     */
    static inline const uint8_t *a2dp_subevent_signaling_media_codec_other_configuration_get_media_codec_information(const uint8_t *event)
    {
        return &event[13];
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_STREAM_ESTABLISHED
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_stream_established_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field bd_addr from event A2DP_SUBEVENT_STREAM_ESTABLISHED
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void a2dp_subevent_stream_established_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[5], bd_addr);
    }
    /**
     * @brief Get field local_seid from event A2DP_SUBEVENT_STREAM_ESTABLISHED
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_stream_established_get_local_seid(const uint8_t *event)
    {
        return event[11];
    }
    /**
     * @brief Get field remote_seid from event A2DP_SUBEVENT_STREAM_ESTABLISHED
     * @param event packet
     * @return remote_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_stream_established_get_remote_seid(const uint8_t *event)
    {
        return event[12];
    }
    /**
     * @brief Get field status from event A2DP_SUBEVENT_STREAM_ESTABLISHED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_stream_established_get_status(const uint8_t *event)
    {
        return event[13];
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_STREAM_STARTED
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_stream_started_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event A2DP_SUBEVENT_STREAM_STARTED
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_stream_started_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_STREAM_SUSPENDED
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_stream_suspended_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event A2DP_SUBEVENT_STREAM_SUSPENDED
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_stream_suspended_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_STREAM_STOPPED
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_stream_stopped_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event A2DP_SUBEVENT_STREAM_STOPPED
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_stream_stopped_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_STREAM_RELEASED
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_stream_released_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event A2DP_SUBEVENT_STREAM_RELEASED
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_stream_released_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_COMMAND_ACCEPTED
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_command_accepted_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event A2DP_SUBEVENT_COMMAND_ACCEPTED
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_command_accepted_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field signal_identifier from event A2DP_SUBEVENT_COMMAND_ACCEPTED
     * @param event packet
     * @return signal_identifier
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_command_accepted_get_signal_identifier(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_COMMAND_REJECTED
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_command_rejected_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field local_seid from event A2DP_SUBEVENT_COMMAND_REJECTED
     * @param event packet
     * @return local_seid
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_command_rejected_get_local_seid(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field signal_identifier from event A2DP_SUBEVENT_COMMAND_REJECTED
     * @param event packet
     * @return signal_identifier
     * @note: btstack_type 1
     */
    static inline uint8_t a2dp_subevent_command_rejected_get_signal_identifier(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_INCOMING_CONNECTION_ESTABLISHED
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_incoming_connection_established_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field bd_addr from event A2DP_SUBEVENT_INCOMING_CONNECTION_ESTABLISHED
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void a2dp_subevent_incoming_connection_established_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[5], bd_addr);
    }

    /**
     * @brief Get field a2dp_cid from event A2DP_SUBEVENT_SIGNALING_CONNECTION_RELEASED
     * @param event packet
     * @return a2dp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t a2dp_subevent_signaling_connection_released_get_a2dp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field status from event AVRCP_SUBEVENT_CONNECTION_ESTABLISHED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_connection_established_get_status(const uint8_t *event)
    {
        return event[3];
    }
    /**
     * @brief Get field bd_addr from event AVRCP_SUBEVENT_CONNECTION_ESTABLISHED
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void avrcp_subevent_connection_established_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[4], bd_addr);
    }
    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_CONNECTION_ESTABLISHED
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_connection_established_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 10);
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_CONNECTION_RELEASED
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_connection_released_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_SHUFFLE_AND_REPEAT_MODE
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_shuffle_and_repeat_mode_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_SHUFFLE_AND_REPEAT_MODE
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_shuffle_and_repeat_mode_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field repeat_mode from event AVRCP_SUBEVENT_SHUFFLE_AND_REPEAT_MODE
     * @param event packet
     * @return repeat_mode
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_shuffle_and_repeat_mode_get_repeat_mode(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field shuffle_mode from event AVRCP_SUBEVENT_SHUFFLE_AND_REPEAT_MODE
     * @param event packet
     * @return shuffle_mode
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_shuffle_and_repeat_mode_get_shuffle_mode(const uint8_t *event)
    {
        return event[7];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_PLAY_STATUS
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_play_status_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_PLAY_STATUS
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_play_status_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field song_length from event AVRCP_SUBEVENT_PLAY_STATUS
     * @param event packet
     * @return song_length
     * @note: btstack_type 4
     */
    static inline uint32_t avrcp_subevent_play_status_get_song_length(const uint8_t *event)
    {
        return little_endian_read_32(event, 6);
    }
    /**
     * @brief Get field song_position from event AVRCP_SUBEVENT_PLAY_STATUS
     * @param event packet
     * @return song_position
     * @note: btstack_type 4
     */
    static inline uint32_t avrcp_subevent_play_status_get_song_position(const uint8_t *event)
    {
        return little_endian_read_32(event, 10);
    }
    /**
     * @brief Get field play_status from event AVRCP_SUBEVENT_PLAY_STATUS
     * @param event packet
     * @return play_status
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_play_status_get_play_status(const uint8_t *event)
    {
        return event[14];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOTIFICATION_PLAYBACK_STATUS_CHANGED
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_notification_playback_status_changed_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOTIFICATION_PLAYBACK_STATUS_CHANGED
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_notification_playback_status_changed_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field play_status from event AVRCP_SUBEVENT_NOTIFICATION_PLAYBACK_STATUS_CHANGED
     * @param event packet
     * @return play_status
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_notification_playback_status_changed_get_play_status(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOTIFICATION_TRACK_CHANGED
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_notification_track_changed_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOTIFICATION_TRACK_CHANGED
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_notification_track_changed_get_command_type(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOTIFICATION_NOW_PLAYING_CONTENT_CHANGED
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_notification_now_playing_content_changed_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOTIFICATION_NOW_PLAYING_CONTENT_CHANGED
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_notification_now_playing_content_changed_get_command_type(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOTIFICATION_AVAILABLE_PLAYERS_CHANGED
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_notification_available_players_changed_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOTIFICATION_AVAILABLE_PLAYERS_CHANGED
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_notification_available_players_changed_get_command_type(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOTIFICATION_VOLUME_CHANGED
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_notification_volume_changed_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOTIFICATION_VOLUME_CHANGED
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_notification_volume_changed_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field absolute_volume from event AVRCP_SUBEVENT_NOTIFICATION_VOLUME_CHANGED
     * @param event packet
     * @return absolute_volume
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_notification_volume_changed_get_absolute_volume(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_SET_ABSOLUTE_VOLUME_RESPONSE
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_set_absolute_volume_response_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_SET_ABSOLUTE_VOLUME_RESPONSE
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_set_absolute_volume_response_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field absolute_volume from event AVRCP_SUBEVENT_SET_ABSOLUTE_VOLUME_RESPONSE
     * @param event packet
     * @return absolute_volume
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_set_absolute_volume_response_get_absolute_volume(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_ENABLE_NOTIFICATION_COMPLETE
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_enable_notification_complete_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_ENABLE_NOTIFICATION_COMPLETE
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_enable_notification_complete_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field notification_id from event AVRCP_SUBEVENT_ENABLE_NOTIFICATION_COMPLETE
     * @param event packet
     * @return notification_id
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_enable_notification_complete_get_notification_id(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_OPERATION_START
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_operation_start_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_OPERATION_START
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_operation_start_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field operation_id from event AVRCP_SUBEVENT_OPERATION_START
     * @param event packet
     * @return operation_id
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_operation_start_get_operation_id(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_OPERATION_COMPLETE
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_operation_complete_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_OPERATION_COMPLETE
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_operation_complete_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field operation_id from event AVRCP_SUBEVENT_OPERATION_COMPLETE
     * @param event packet
     * @return operation_id
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_operation_complete_get_operation_id(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_PLAYER_APPLICATION_VALUE_RESPONSE
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_player_application_value_response_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_PLAYER_APPLICATION_VALUE_RESPONSE
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_player_application_value_response_get_command_type(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_COMPANY_IDS_QUERY
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_company_ids_query_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_EVENT_IDS_QUERY
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_event_ids_query_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_PLAY_STATUS_QUERY
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_play_status_query_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_OPERATION
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_operation_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field operation_id from event AVRCP_SUBEVENT_OPERATION
     * @param event packet
     * @return operation_id
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_operation_get_operation_id(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field operands_length from event AVRCP_SUBEVENT_OPERATION
     * @param event packet
     * @return operands_length
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_operation_get_operands_length(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field operand from event AVRCP_SUBEVENT_OPERATION
     * @param event packet
     * @return operand
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_operation_get_operand(const uint8_t *event)
    {
        return event[7];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOW_PLAYING_TRACK_INFO
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_now_playing_track_info_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOW_PLAYING_TRACK_INFO
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_now_playing_track_info_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field track from event AVRCP_SUBEVENT_NOW_PLAYING_TRACK_INFO
     * @param event packet
     * @return track
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_now_playing_track_info_get_track(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOW_PLAYING_TOTAL_TRACKS_INFO
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_now_playing_total_tracks_info_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOW_PLAYING_TOTAL_TRACKS_INFO
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_now_playing_total_tracks_info_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field total_tracks from event AVRCP_SUBEVENT_NOW_PLAYING_TOTAL_TRACKS_INFO
     * @param event packet
     * @return total_tracks
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_now_playing_total_tracks_info_get_total_tracks(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOW_PLAYING_SONG_LENGTH_MS_INFO
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_now_playing_song_length_ms_info_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOW_PLAYING_SONG_LENGTH_MS_INFO
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_now_playing_song_length_ms_info_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field song_length from event AVRCP_SUBEVENT_NOW_PLAYING_SONG_LENGTH_MS_INFO
     * @param event packet
     * @return song_length
     * @note: btstack_type 4
     */
    static inline uint32_t avrcp_subevent_now_playing_song_length_ms_info_get_song_length(const uint8_t *event)
    {
        return little_endian_read_32(event, 6);
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOW_PLAYING_TITLE_INFO
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_now_playing_title_info_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOW_PLAYING_TITLE_INFO
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_now_playing_title_info_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field value_len from event AVRCP_SUBEVENT_NOW_PLAYING_TITLE_INFO
     * @param event packet
     * @return value_len
     * @note: btstack_type J
     */
    static inline int avrcp_subevent_now_playing_title_info_get_value_len(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field value from event AVRCP_SUBEVENT_NOW_PLAYING_TITLE_INFO
     * @param event packet
     * @return value
     * @note: btstack_type V
     */
    static inline const uint8_t *avrcp_subevent_now_playing_title_info_get_value(const uint8_t *event)
    {
        return &event[7];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOW_PLAYING_ARTIST_INFO
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_now_playing_artist_info_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOW_PLAYING_ARTIST_INFO
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_now_playing_artist_info_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field value_len from event AVRCP_SUBEVENT_NOW_PLAYING_ARTIST_INFO
     * @param event packet
     * @return value_len
     * @note: btstack_type J
     */
    static inline int avrcp_subevent_now_playing_artist_info_get_value_len(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field value from event AVRCP_SUBEVENT_NOW_PLAYING_ARTIST_INFO
     * @param event packet
     * @return value
     * @note: btstack_type V
     */
    static inline const uint8_t *avrcp_subevent_now_playing_artist_info_get_value(const uint8_t *event)
    {
        return &event[7];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOW_PLAYING_ALBUM_INFO
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_now_playing_album_info_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOW_PLAYING_ALBUM_INFO
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_now_playing_album_info_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field value_len from event AVRCP_SUBEVENT_NOW_PLAYING_ALBUM_INFO
     * @param event packet
     * @return value_len
     * @note: btstack_type J
     */
    static inline int avrcp_subevent_now_playing_album_info_get_value_len(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field value from event AVRCP_SUBEVENT_NOW_PLAYING_ALBUM_INFO
     * @param event packet
     * @return value
     * @note: btstack_type V
     */
    static inline const uint8_t *avrcp_subevent_now_playing_album_info_get_value(const uint8_t *event)
    {
        return &event[7];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOW_PLAYING_GENRE_INFO
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_now_playing_genre_info_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOW_PLAYING_GENRE_INFO
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_now_playing_genre_info_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field value_len from event AVRCP_SUBEVENT_NOW_PLAYING_GENRE_INFO
     * @param event packet
     * @return value_len
     * @note: btstack_type J
     */
    static inline int avrcp_subevent_now_playing_genre_info_get_value_len(const uint8_t *event)
    {
        return event[6];
    }
    /**
     * @brief Get field value from event AVRCP_SUBEVENT_NOW_PLAYING_GENRE_INFO
     * @param event packet
     * @return value
     * @note: btstack_type V
     */
    static inline const uint8_t *avrcp_subevent_now_playing_genre_info_get_value(const uint8_t *event)
    {
        return &event[7];
    }

    /**
     * @brief Get field avrcp_cid from event AVRCP_SUBEVENT_NOW_PLAYING_INFO_DONE
     * @param event packet
     * @return avrcp_cid
     * @note: btstack_type 2
     */
    static inline uint16_t avrcp_subevent_now_playing_info_done_get_avrcp_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field command_type from event AVRCP_SUBEVENT_NOW_PLAYING_INFO_DONE
     * @param event packet
     * @return command_type
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_now_playing_info_done_get_command_type(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field status from event AVRCP_SUBEVENT_NOW_PLAYING_INFO_DONE
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t avrcp_subevent_now_playing_info_done_get_status(const uint8_t *event)
    {
        return event[6];
    }

    /**
     * @brief Get field goep_cid from event GOEP_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return goep_cid
     * @note: btstack_type 2
     */
    static inline uint16_t goep_subevent_connection_opened_get_goep_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field status from event GOEP_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t goep_subevent_connection_opened_get_status(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field bd_addr from event GOEP_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void goep_subevent_connection_opened_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[6], bd_addr);
    }
    /**
     * @brief Get field con_handle from event GOEP_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return con_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t goep_subevent_connection_opened_get_con_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 12);
    }
    /**
     * @brief Get field incoming from event GOEP_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return incoming
     * @note: btstack_type 1
     */
    static inline uint8_t goep_subevent_connection_opened_get_incoming(const uint8_t *event)
    {
        return event[14];
    }

    /**
     * @brief Get field goep_cid from event GOEP_SUBEVENT_CONNECTION_CLOSED
     * @param event packet
     * @return goep_cid
     * @note: btstack_type 2
     */
    static inline uint16_t goep_subevent_connection_closed_get_goep_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field goep_cid from event GOEP_SUBEVENT_CAN_SEND_NOW
     * @param event packet
     * @return goep_cid
     * @note: btstack_type 2
     */
    static inline uint16_t goep_subevent_can_send_now_get_goep_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field pbap_cid from event PBAP_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return pbap_cid
     * @note: btstack_type 2
     */
    static inline uint16_t pbap_subevent_connection_opened_get_pbap_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field status from event PBAP_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t pbap_subevent_connection_opened_get_status(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field bd_addr from event PBAP_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void pbap_subevent_connection_opened_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[6], bd_addr);
    }
    /**
     * @brief Get field con_handle from event PBAP_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return con_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t pbap_subevent_connection_opened_get_con_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 12);
    }
    /**
     * @brief Get field incoming from event PBAP_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return incoming
     * @note: btstack_type 1
     */
    static inline uint8_t pbap_subevent_connection_opened_get_incoming(const uint8_t *event)
    {
        return event[14];
    }

    /**
     * @brief Get field goep_cid from event PBAP_SUBEVENT_CONNECTION_CLOSED
     * @param event packet
     * @return goep_cid
     * @note: btstack_type 2
     */
    static inline uint16_t pbap_subevent_connection_closed_get_goep_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field goep_cid from event PBAP_SUBEVENT_OPERATION_COMPLETED
     * @param event packet
     * @return goep_cid
     * @note: btstack_type 2
     */
    static inline uint16_t pbap_subevent_operation_completed_get_goep_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field status from event PBAP_SUBEVENT_OPERATION_COMPLETED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t pbap_subevent_operation_completed_get_status(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field hid_cid from event HID_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return hid_cid
     * @note: btstack_type 2
     */
    static inline uint16_t hid_subevent_connection_opened_get_hid_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field status from event HID_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return status
     * @note: btstack_type 1
     */
    static inline uint8_t hid_subevent_connection_opened_get_status(const uint8_t *event)
    {
        return event[5];
    }
    /**
     * @brief Get field bd_addr from event HID_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @param Pointer to storage for bd_addr
     * @note: btstack_type B
     */
    static inline void hid_subevent_connection_opened_get_bd_addr(const uint8_t *event, bd_addr_t bd_addr)
    {
        reverse_bd_addr(&event[6], bd_addr);
    }
    /**
     * @brief Get field con_handle from event HID_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return con_handle
     * @note: btstack_type H
     */
    static inline hci_con_handle_t hid_subevent_connection_opened_get_con_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 12);
    }
    /**
     * @brief Get field incoming from event HID_SUBEVENT_CONNECTION_OPENED
     * @param event packet
     * @return incoming
     * @note: btstack_type 1
     */
    static inline uint8_t hid_subevent_connection_opened_get_incoming(const uint8_t *event)
    {
        return event[14];
    }

    /**
     * @brief Get field hid_cid from event HID_SUBEVENT_CONNECTION_CLOSED
     * @param event packet
     * @return hid_cid
     * @note: btstack_type 2
     */
    static inline uint16_t hid_subevent_connection_closed_get_hid_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field hid_cid from event HID_SUBEVENT_CAN_SEND_NOW
     * @param event packet
     * @return hid_cid
     * @note: btstack_type 2
     */
    static inline uint16_t hid_subevent_can_send_now_get_hid_cid(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field con_handle from event HIDS_SUBEVENT_CAN_SEND_NOW
     * @param event packet
     * @return con_handle
     * @note: btstack_type 2
     */
    static inline uint16_t hids_subevent_can_send_now_get_con_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }

    /**
     * @brief Get field con_handle from event HIDS_SUBEVENT_PROTOCOL_MODE
     * @param event packet
     * @return con_handle
     * @note: btstack_type 2
     */
    static inline uint16_t hids_subevent_protocol_mode_get_con_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field protocol_mode from event HIDS_SUBEVENT_PROTOCOL_MODE
     * @param event packet
     * @return protocol_mode
     * @note: btstack_type 1
     */
    static inline uint8_t hids_subevent_protocol_mode_get_protocol_mode(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field con_handle from event HIDS_SUBEVENT_BOOT_MOUSE_INPUT_REPORT_ENABLE
     * @param event packet
     * @return con_handle
     * @note: btstack_type 2
     */
    static inline uint16_t hids_subevent_boot_mouse_input_report_enable_get_con_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field enable from event HIDS_SUBEVENT_BOOT_MOUSE_INPUT_REPORT_ENABLE
     * @param event packet
     * @return enable
     * @note: btstack_type 1
     */
    static inline uint8_t hids_subevent_boot_mouse_input_report_enable_get_enable(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field con_handle from event HIDS_SUBEVENT_BOOT_KEYBOARD_INPUT_REPORT_ENABLE
     * @param event packet
     * @return con_handle
     * @note: btstack_type 2
     */
    static inline uint16_t hids_subevent_boot_keyboard_input_report_enable_get_con_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field enable from event HIDS_SUBEVENT_BOOT_KEYBOARD_INPUT_REPORT_ENABLE
     * @param event packet
     * @return enable
     * @note: btstack_type 1
     */
    static inline uint8_t hids_subevent_boot_keyboard_input_report_enable_get_enable(const uint8_t *event)
    {
        return event[5];
    }

    /**
     * @brief Get field con_handle from event HIDS_SUBEVENT_INPUT_REPORT_ENABLE
     * @param event packet
     * @return con_handle
     * @note: btstack_type 2
     */
    static inline uint16_t hids_subevent_input_report_enable_get_con_handle(const uint8_t *event)
    {
        return little_endian_read_16(event, 3);
    }
    /**
     * @brief Get field enable from event HIDS_SUBEVENT_INPUT_REPORT_ENABLE
     * @param event packet
     * @return enable
     * @note: btstack_type 1
     */
    static inline uint8_t hids_subevent_input_report_enable_get_enable(const uint8_t *event)
    {
        return event[5];
    }


    static inline uint8_t hci_event_le_meta_get_phy_update_complete_status(const uint8_t *event)
    {
        return event[3];
    }
    static inline uint8_t hci_event_le_meta_get_phy_update_complete_tx_phy(const uint8_t *event)
    {
        return event[6];
    }
    static inline uint8_t hci_event_le_meta_get_phy_update_complete_rx_phy(const uint8_t *event)
    {
        return event[7];
    }


    /* API_END */

#if defined __cplusplus
}
#endif

#endif // __BTSTACK_EVENT_H
