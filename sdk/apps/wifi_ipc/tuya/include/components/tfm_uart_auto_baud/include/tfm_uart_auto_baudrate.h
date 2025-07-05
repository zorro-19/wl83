/**
 * @file tfm_uart_auto_baudrate.h
 * @author mengjinlong@tuya.com
 * @brief  Automatically adapt to all serial port baud rates.
 * @version 1.0
 * @date 2020-11-04
 * @copyright Copyright (c) tuya.inc 2020
 * Provides interface that adapt to serial port baud rates.
 */
#ifndef _TFM_UART_AUTO_BAUDRATE_H
#define _TFM_UART_AUTO_BAUDRATE_H

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
** INCLUDE                                                           **
**********************************************************************/
#include "tuya_cloud_types.h"

/***********************************************************************
 ** CONSTANT ( MACRO AND ENUM )                                       **
 **********************************************************************/
/**
 * After the serial port baud rate is detected successfully, the data callback function of this packet is received.
 * @param  data    received data.
 * @param  len     received data len.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
typedef OPERATE_RET(*DETECT_DATA_RECV)(IN CHAR_T *data, UINT_T len);

/**
 * Device baud rate setting function.
 * @param  baud_rate    baud rate.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
typedef OPERATE_RET(*DETECT_BAUD_DEV_INIT)(UINT_T baud_rate);

/**
 * Device baud rate deinit function.
 * @param  null.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
typedef OPERATE_RET(*DETECT_BAUD_DEV_DEINIT)(VOID);

/**
 * Device send detection frame callback function.
 * @param  null.
 * @return Function Operation Result  OPRT_OK is ok other is fail
 */
typedef OPERATE_RET(*DETECT_BAUD_DEV_SEND_PACKET)(VOID);

/**
 * Device read data callback function.
 * @param  buf Data buffer pointer.
 * @param  len Data buffer len.
 * @return Length of data actually read.
 */
typedef UINT_T(*DETECT_BAUD_DEV_READ_DATA)(OUT CHAR_T *buf, IN CONST UINT_T len);

/***********************************************************************
** STRUCT                                                            **
**********************************************************************/
typedef struct {
    UINT_T arry_num;   /*Probe baud rate list number*/
    UINT_T *baud_arry; /*Probe baud rate list array*/
} DETECT_BAUD_LIST_S;

typedef struct {
    DETECT_BAUD_DEV_INIT dev_init;               /*Device baud rate setting function*/
    DETECT_BAUD_DEV_DEINIT dev_deinit;           /*Device baud rate deinit function*/
    DETECT_BAUD_DEV_SEND_PACKET dev_send_packet; /*Device send detection frame callback functio*/
    DETECT_BAUD_DEV_READ_DATA dev_read_data;     /*Device read data callback function*/
} DETECT_BAUD_CB_S;

typedef struct {
    BOOL_T is_enable;
    UCHAR_T cmd; /* Specify the command to lock the baud rate */
} DETECT_BAUD_CMD_S;

typedef struct {
    UINT_T send_probe_interval;   /*Send probe switching time. If set to 0, the default value of 500ms will be used.*/
    UINT_T read_detect_interval;  /*Read the detection response frame time. This time must be less than the probe
                                     switching time.If set to 0, the default value of 20ms will be used. Set this value
                                     according to the data length of the reply frame.*/
    DETECT_BAUD_LIST_S baud_list; /*The baud rate list needing to adapt */
    DETECT_DATA_RECV data_recv;   /*Receive a data callback function that conforms to the tuya protocol*/
    DETECT_BAUD_CB_S dev_cbs;     /*Various data callback functions of the device*/
    DETECT_BAUD_CMD_S dev_cmd;    /* Specify the command to lock the baud rate */
} TY_BAUD_CFG_S;

/***********************************************************************
 ** FUNCTON                                                           **
 **********************************************************************/
/**
 * Device baud rate adaptive interface function, this function is blocking mode.
 * @param  p_baud_cfg  Device baud rate configuration.
 * @param  detect_baud Detected device baud rate.
 * @return Function Operation Result  OPRT_OK is ok other is fail.
 */
OPERATE_RET tfm_uart_auto_adapt_baud_block(IN TY_BAUD_CFG_S *p_baud_cfg, OUT UINT_T *detect_baud);

#ifdef __cplusplus
}
#endif

#endif
