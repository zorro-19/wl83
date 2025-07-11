/**
 * @file tkl_lwip.c
 * @brief this file was auto-generated by tuyaos v&v tools, developer can add implements between BEGIN and END
 *
 * @warning: changes between user 'BEGIN' and 'END' will be keeped when run tuyaos v&v tools
 *           changes in other place will be overwrited and lost
 *
 * @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
 *
 */

// --- BEGIN: user defines and implements ---
#include "tkl_lwip.h"
#include "tuya_error_code.h"
// --- END: user defines and implements ---

/**
 * @brief ethernet interface hardware init
 *
 * @param[in]      netif     the netif to which to send the packet
 * @return  err_t  SEE "err_enum_t" in "lwip/err.h" to see the lwip err(ERR_OK: SUCCESS other:fail)
 */
OPERATE_RET tkl_ethernetif_init(TKL_NETIF_HANDLE netif)
{
    // --- BEGIN: user implements ---
    return OPRT_NOT_SUPPORTED;
    // --- END: user implements ---
}

/**
 * @brief ethernet interface sendout the pbuf packet
 *
 * @param[in]      netif     the netif to which to send the packet
 * @param[in]      p         the packet to be send, in pbuf mode
 * @return  err_t  SEE "err_enum_t" in "lwip/err.h" to see the lwip err(ERR_OK: SUCCESS other:fail)
 */
OPERATE_RET tkl_ethernetif_output(TKL_NETIF_HANDLE netif, TKL_PBUF_HANDLE p)
{
    // --- BEGIN: user implements ---
    return OPRT_NOT_SUPPORTED;
    // --- END: user implements ---
}

/**
 * @brief ethernet interface recv the packet
 *
 * @param[in]      netif       the netif to which to recieve the packet
 * @param[in]      total_len   the length of the packet recieved from the netif
 * @return  void
 */
OPERATE_RET tkl_ethernetif_recv(TKL_NETIF_HANDLE netif, TKL_PBUF_HANDLE p)
{
    // --- BEGIN: user implements ---
    return OPRT_NOT_SUPPORTED;
    // --- END: user implements ---
}

