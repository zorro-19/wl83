/**
* @file tkl_spi.h
* @brief Common process - adapter the spi api
* @version 0.1
* @date 2021-08-06
*
* @copyright Copyright 2021-2030 Tuya Inc. All Rights Reserved.
*
*/
#ifndef __TKL_SPI_H__
#define __TKL_SPI_H__

#include "tuya_cloud_types.h"
#include "tkl_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief spi init
 *
 * @param[in] port: spi port
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_spi_init(TUYA_SPI_NUM_E port, CONST TUYA_SPI_BASE_CFG_T *cfg);

/**
 * @brief spi deinit
 *
 * @param[in] port: spi port
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_spi_deinit(TUYA_SPI_NUM_E port);

/**
 * Spi send
 *
 * @param[in]  port      the spi device
 * @param[in]  data     spi send data
 * @param[in]  size     spi send data size
 *
 * @return  OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_spi_send(TUYA_SPI_NUM_E port, VOID_T *data, UINT16_T size);

/**
 * spi_recv
 *
 * @param[in]   port      the spi device
 * @param[out]  data     spi recv data
 * @param[in]   size     spi recv data size
 *
 * @return  OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_spi_recv(TUYA_SPI_NUM_E port, VOID_T *data, UINT16_T size);

/**
 * @brief spi transfer
 *
 * @param[in] port: spi port
 * @param[in] send_buf: spi send buf
 * @param[out] send_buf:spi recv buf
 * @param[in] length: spi msg length
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_spi_transfer(TUYA_SPI_NUM_E port, VOID_T *send_buf, VOID_T *receive_buf, UINT32_T length);

/**
 * @brief spi transfer
 *
 * @param[in] port: spi port
 * @param[in] send_buf: spi send buf
 * @param[in] send_len: send_len
 * @param[out] receive_buf:spi recv buf
 * @param[in] receive_len: receive_len
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_spi_transfer_with_length(TUYA_SPI_NUM_E port, VOID_T *send_buf, UINT32_T send_len, VOID_T *receive_buf, UINT32_T receive_len);
/**
 * @brief adort spi transfer,or spi send, or spi recv
 *
 * @param[in] port: spi port
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */

OPERATE_RET tkl_spi_abort_transfer(TUYA_SPI_NUM_E port);

/**
 * @brief get spi status.
 *
 * @param[in] port: spi port
 * @param[out]  TUYA_SPI_STATUS_T,please refer to tuya_cloud_types.h
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_spi_get_status(TUYA_SPI_NUM_E port, TUYA_SPI_STATUS_T *status);

/**
 * @brief spi irq init
 * NOTE: call this API will not enable interrupt
 *
 * @param[in] port: spi port, id index starts at 0
 * @param[in] cb:  spi irq cb
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_spi_irq_init(TUYA_SPI_NUM_E port, TUYA_SPI_IRQ_CB cb);

/**
 * @brief spi irq enable
 *
 * @param[in] port: spi port id, id index starts at 0
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_spi_irq_enable(TUYA_SPI_NUM_E port);

/**
 * @brief spi irq disable
 *
 * @param[in] port: spi port id, id index starts at 0
 *
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_spi_irq_disable(TUYA_SPI_NUM_E port);

/**
 * @brief spi transferred data count.
 *
 * @param[in] port: spi port id, id index starts at 0
 *
 * @return >=0,number of currently transferred data items. <0,err.
 * during  tkl_spi_send, tkl_spi_recv and tkl_spi_transfer operation.
 */
INT32_T tkl_spi_get_data_count(TUYA_SPI_NUM_E port);

/**
 * @brief spi ioctl
 *
 * @param[in]       cmd     user def
 * @param[in]       args    args associated with the command
 * @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
 */
OPERATE_RET tkl_spi_ioctl(TUYA_SPI_NUM_E port, UINT32_T cmd,  VOID *args);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


