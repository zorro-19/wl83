#ifndef __PRODUCT_TEST_H__
#define __PRODUCT_TEST_H__
/**
* @file tuya_prod_test.h
* @brief 产测
* @version 1.0
* @date 2021-07-06
*
* @copyright Copyright (c) tuya.inc 2019
*
*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/* Includes ------------------------------------------------------------------*/
#include "tuya_cloud_com_defs.h"

/* Private maros -------------------------------------------------------------*/
//command define


#define PRODUCT_TEST_BUTTON_SUM_CMD             0x0003
#define PRODUCT_TEST_WRITE_SN_CMD               0x000f
#define PRODUCT_TEST_READ_SN_CMD                0x0010
#define PRODUCT_TEST_IPC_IMG_CATCH_SUB_CMD      0x0020
#define PRODUCT_TEST_IPC_IMG_GET_SUB_CMD        0x002E
#define PRODUCT_TEST_MIC_SPEAKER_START_CMD      0x0028
#define PRODUCT_TEST_MIC_SPEAKER_STOP_CMD       0x002A
#define PRODUCT_TEST_LDR_SUM_CMD                0x0030
#define PRODUCT_TEST_GET_COMMON_CMD             0x0035
#define PRODUCT_TEST_COMMON_CMD                 0x0014
#define PRODUCT_TEST_COMMON_BOOL_SUB_CMD        0xFF03



/* Export functions ----------------------------------------------------------*/
OPERATE_RET tuya_prod_test(USHORT_T cmd, UCHAR_T *data, UINT_T len, OUT UCHAR_T **ret_data, OUT USHORT_T *ret_len);


VOID ty_prod_test_audio(BOOL_T open);


OPERATE_RET kiwi_uart_product_test(VOID);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PRODUCT_TEST_H__ */


