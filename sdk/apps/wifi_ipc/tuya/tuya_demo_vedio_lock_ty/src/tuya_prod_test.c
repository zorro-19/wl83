/* Includes ------------------------------------------------------------------*/

#include "mem_pool.h"
#include "tuya_hal_system.h"
#include "uni_thread.h"
#include "tuya_uart.h"
#include "tuya_prod_test.h"
#include "mf_test.h"
#include "sys_timer.h"
#include "uni_msg_queue.h"
#include "tuya_hal_semaphore.h"
#include "tuya_ws_db.h"
#include "tuya_device.h"
#include "tbl_common_basic_service.h"
/* Private macros ------------------------------------------------------------*/


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/**
 * @brief: 获取产测类型
 * @param obj: 待检测json对象
 * @attention:
 * @retval: type字符串
 */
CHAR_T *product_test_get_test_item(IN ty_cJSON *obj, IN CHAR_T *string_item)
{
    ty_cJSON *item = NULL;

    if (obj == NULL) {
        return NULL;
    }

    //获取type字段
    item = ty_cJSON_GetObjectItem(obj, string_item);
    if (item == NULL) {
        return NULL;
    }

    //查看字段是否为字符类型
    if ((item->type & 0xFF) != ty_cJSON_String) {
        return NULL;
    }

    return item->valuestring;
}


/**
 * @brief: 获取产测类型
 * @param obj: 待检测json对象
 * @attention:
 * @retval: type字符串
 */
CHAR_T *product_test_get_test_item_or_type(IN ty_cJSON *obj)
{
    ty_cJSON *item = NULL;

    if (obj == NULL) {
        return NULL;
    }

    //获取type字段
    item = ty_cJSON_GetObjectItem(obj, "testItem");
    if (item == NULL) {
        //获取testItem对象失败
        //获取type
        item = ty_cJSON_GetObjectItem(obj, "type");
        if (item == NULL) {
            return NULL;
        }
    }

    //查看字段是否为字符类型
    if ((item->type & 0xFF) != ty_cJSON_String) {
        return NULL;
    }

    return item->valuestring;
}

STATIC OPERATE_RET product_test_pid_Para(CHAR_T *param)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;
    ty_cJSON *root = NULL;
    ty_cJSON *cjson = NULL;
    INT_T read_len = 0;
    CHAR_T pid_buf[20] = {0};

    root = ty_cJSON_Parse(param);
    if (NULL == root) {
        PR_ERR(" parse err");
        return OPRT_CJSON_PARSE_ERR;
    }

    cjson = ty_cJSON_GetObjectItem(root, "pid");
    if (cjson) {
        memset(pid_buf, 0, sizeof(pid_buf));
        strcpy(pid_buf, cjson->valuestring);
    } else {
        wd_common_delete(PID_CFG_PARAM_E);
    }

    ty_cJSON_Delete(root);

    if (pid_buf[0] == 0) {
        return OPRT_INVALID_PARM;
    }
    ty_param_save(PID_CFG_PARAM_E, pid_buf, strlen(pid_buf));
    return OPRT_OK;
}
OPERATE_RET product_test_common_device_Para(CHAR_T *param)
{
    ty_cJSON *obj_cjson = NULL;
    ty_cJSON *obj_obj_cjson = NULL;
    CHAR_T *devic_data = NULL;
    UINT_T device_len = 0;
    OPERATE_RET op_ret = OPRT_COM_ERROR;

    obj_cjson = ty_cJSON_Parse(param);
    if (NULL == obj_cjson) {
        PR_ERR("value parse err");
    } else {
        PR_NOTICE("extConfig= %s", ty_cJSON_GetObjectItem(obj_cjson, "extConfig")->valuestring);
        obj_obj_cjson = ty_cJSON_Parse(ty_cJSON_GetObjectItem(obj_cjson, "extConfig")->valuestring);
        if (NULL == obj_obj_cjson) {
            PR_ERR("extConfig parse err");
        } else {
            PR_NOTICE("lockConfig= %s", ty_cJSON_GetObjectItem(obj_obj_cjson, "lockConfig")->valuestring);
            if (ty_cJSON_GetObjectItem(obj_obj_cjson, "lockConfig")->valuestring != NULL) {
                //获取json长度
                device_len = strlen(ty_cJSON_GetObjectItem(obj_obj_cjson, "lockConfig")->valuestring);
                devic_data = Malloc(device_len + 1);
                memset(devic_data, 0, device_len + 1);
                memcpy(devic_data, ty_cJSON_GetObjectItem(obj_obj_cjson, "lockConfig")->valuestring, device_len);
                product_test_pid_Para(devic_data);
                op_ret = OPRT_OK;
            }
            ty_cJSON_Delete(obj_obj_cjson);
        }
        ty_cJSON_Delete(obj_cjson);
    }
    return op_ret;
}

OPERATE_RET product_test_get_common_device_Para(IN CHAR_T *data_in)
{
    OPERATE_RET op_ret = OPRT_COM_ERROR;

    CHAR_T *ret_data = NULL;
    CHAR_T *obj_data = NULL;
    CHAR_T *ext_cjson_data = NULL;
    CHAR_T *cjson_data = NULL;
    UINT_T read_len = 0;
    ty_cJSON *root = NULL;
    ty_cJSON *obj = NULL;
    ty_cJSON *cjson = NULL;
    ty_cJSON *ext_cjson = NULL;
    CHAR_T  code_data[32] = {0};
    UINT_T ret_data_len = 0;
    CHAR_T pid_buf[20] = {0};

    memset(pid_buf, 0, sizeof(pid_buf));
    op_ret = ty_param_load(PID_CFG_PARAM_E, pid_buf, SIZEOF(pid_buf), &read_len);
    if ((op_ret != OPRT_OK)) {
        goto DEAL_ERR;
    }

    root = ty_cJSON_Parse(data_in);
    if (root == NULL) {
        goto DEAL_ERR;
    }
    cjson = ty_cJSON_GetObjectItem(root, "value");
    if (cjson && ty_cJSON_GetObjectItem(ty_cJSON_Parse(cjson->valuestring), "code")) {
        strcpy(code_data, ty_cJSON_GetObjectItem(ty_cJSON_Parse(cjson->valuestring), "code")->valuestring);
        PR_NOTICE("code=%s", code_data);
    }
    ty_cJSON_Delete(root);
    root = NULL;
    cjson = NULL;

    obj = ty_cJSON_CreateObject();
    if (obj == NULL) {
        goto DEAL_ERR;
    }

    ty_cJSON_AddStringToObject(obj, "pid", pid_buf);

    obj_data = (CHAR_T *)ty_cJSON_PrintUnformatted(obj);
    if (obj_data == NULL) {
        goto DEAL_ERR;
    }

    cjson = ty_cJSON_CreateObject();
    if (cjson == NULL) {
        goto DEAL_ERR;
    }
    ty_cJSON_AddStringToObject(cjson, "lockConfig", obj_data);
    cjson_data = (CHAR_T *)ty_cJSON_PrintUnformatted(cjson);
    if (cjson_data == NULL) {
        goto DEAL_ERR;
    }


    ext_cjson = ty_cJSON_CreateObject();
    if (ext_cjson == NULL) {
        goto DEAL_ERR;
    }
    ty_cJSON_AddStringToObject(ext_cjson, "code", code_data);
    ty_cJSON_AddStringToObject(ext_cjson, "extConfig", cjson_data);
    ext_cjson_data = (CHAR_T *)ty_cJSON_PrintUnformatted(ext_cjson);
    if (ext_cjson_data == NULL) {
        goto DEAL_ERR;
    }


    root = ty_cJSON_CreateObject();
    if (root == NULL) {
        goto DEAL_ERR;
    }
    ty_cJSON_AddTrueToObject(root, "ret");
    ty_cJSON_AddStringToObject(root, "testItem", "transProductionInstructions");
    ty_cJSON_AddStringToObject(root, "type", "string");
    ty_cJSON_AddStringToObject(root, "value", ext_cjson_data);
    ret_data = (CHAR_T *)ty_cJSON_PrintUnformatted(root);
    PR_NOTICE("ret_data=%s", ret_data);
    op_ret = OPRT_OK;
    ret_data_len = strlen(ret_data);
    mf_cmd_product_send(PRODUCT_TEST_GET_COMMON_CMD, ret_data, ret_data_len);


DEAL_ERR:
    if (obj_data) {
        ty_cJSON_FreeBuffer(obj_data);
    }

    if (cjson_data) {
        ty_cJSON_FreeBuffer(cjson_data);
    }

    if (ext_cjson_data) {
        ty_cJSON_FreeBuffer(ext_cjson_data);
    }

    if (ext_cjson) {
        ty_cJSON_Delete(ext_cjson);
    }

    if (cjson) {
        ty_cJSON_Delete(cjson);
    }
    if (obj) {
        ty_cJSON_Delete(obj);
    }

    if (root) {
        ty_cJSON_Delete(root);
    }

    return op_ret;
}



OPERATE_RET tuya_prod_test(USHORT_T cmd, UCHAR_T *data, UINT_T len, OUT UCHAR_T **ret_data, OUT USHORT_T *ret_len)
{

    OPERATE_RET op_ret = OPRT_COM_ERROR;
    ty_cJSON *root = NULL;
    ty_cJSON *val_arr = NULL;
    ty_cJSON *recv = NULL;
    CHAR_T *type = NULL;
    CHAR_T *data_temp = NULL;

    PR_DEBUG("###########cmd:%02x len:%d###########", cmd, len);
    tuya_print_data(data, len);

    root = ty_cJSON_CreateObject();

    switch (cmd) {
    case PRODUCT_TEST_BUTTON_SUM_CMD: {
        PR_DEBUG("button test");
        //todo
        op_ret = OPRT_OK;
    }
    break;

    case PRODUCT_TEST_WRITE_SN_CMD: {
        PR_DEBUG("sn write %s", data);
        op_ret = ty_param_save(SN_CFG_TYPE_PARAM_E, data, len);
        if (op_ret == OPRT_OK) {
            ty_cJSON_AddTrueToObject(root, "ret");
        } else {
            ty_cJSON_AddFalseToObject(root, "ret");
        }
    }
    break;

    case PRODUCT_TEST_READ_SN_CMD: {
        PR_DEBUG("sn read");
        data_temp = Malloc(128);
        memset(data_temp, 0, 128);
        UINT_T len;
        op_ret = ty_param_load(SN_CFG_TYPE_PARAM_E, data_temp, 128, &len);
    }
    break;

    case PRODUCT_TEST_MIC_SPEAKER_START_CMD: {
        PR_DEBUG("product test - mic_speaker_start");
        // //todo

        if (op_ret == OPRT_OK) {
            ty_cJSON_AddTrueToObject(root, "ret");
        } else {
            ty_cJSON_AddFalseToObject(root, "ret");
        }
    }
    break;
    case PRODUCT_TEST_MIC_SPEAKER_STOP_CMD: {
        PR_DEBUG("product test - mic_speaker_stop");
        //    //todo


        if (op_ret == OPRT_OK) {
            ty_cJSON_AddTrueToObject(root, "ret");
        } else {
            ty_cJSON_AddFalseToObject(root, "ret");
        }
    }
    break;

    //通用测试
    case PRODUCT_TEST_COMMON_BOOL_SUB_CMD: {
        PR_DEBUG("common bool product test");
        recv = ty_cJSON_Parse((CHAR_T *)data);
        type = product_test_get_test_item(recv, "testItem");
        if (NULL == type) {
            op_ret = OPRT_NOT_SUPPORTED;
        }
        if (0 == strncmp(type, "start_lcd_test", strlen("start_lcd_test"))) {
            // //todo

            if (op_ret == OPRT_OK) {
                ty_cJSON_AddTrueToObject(root, "ret");
            } else {
                ty_cJSON_AddFalseToObject(root, "ret");
            }
        } else if (0 == strncmp(type, "end_lcd_test", strlen("end_lcd_test"))) {
            // //todo

            if (op_ret == OPRT_OK) {
                ty_cJSON_AddTrueToObject(root, "ret");
            } else {
                ty_cJSON_AddFalseToObject(root, "ret");
            }
        }  else if (0 == strncmp(type, "sleep", strlen("sleep"))) {
            PR_DEBUG("======================enter low power=====================");
            //todo
            if (op_ret == OPRT_OK) {
                ty_cJSON_AddTrueToObject(root, "ret");
            } else {
                ty_cJSON_AddFalseToObject(root, "ret");
            }

        } else {
            //不支持其他的类型
            op_ret = OPRT_NOT_SUPPORTED;
        }
    }
    break;
    //参数配置
    case PRODUCT_TEST_COMMON_CMD: {
        PR_DEBUG("PRODUCT_TEST_COMMON_CMD cmd !");
        recv = ty_cJSON_Parse((CHAR_T *)data);
        //检测类型是否为相机参数
        if (((type = product_test_get_test_item_or_type(recv)) != NULL) && (strncmp(type, "transProductionInstructions", strlen("transProductionInstructions")) == 0))  {
            //红外产测执行
            PR_NOTICE("param=%s", data);
            ty_cJSON *p_item = NULL;
            p_item = ty_cJSON_GetObjectItem(recv, "value");
            if (p_item != NULL) {
                if ((op_ret = product_test_common_device_Para(p_item->valuestring)) == OPRT_OK) {
                    //执行成功
                    ty_cJSON_AddTrueToObject(root, "ret");
                } else {
                    op_ret = OPRT_INVALID_PARM;
                }
            }

        } else {
            //不支持以外的类型
            PR_NOTICE("data=%s", data);
            op_ret = OPRT_NOT_SUPPORTED;
        }
    }
    break;

    case PRODUCT_TEST_GET_COMMON_CMD: {
        CHAR_T *temp = Malloc(len + 1);
        if (NULL == temp) {
            op_ret = OPRT_INVALID_PARM;
            break;
        }
        memset(temp, 0, len + 1);
        memcpy(temp, data, len);
        PR_NOTICE("PRODUCT_TEST_GET_COMMON_CMD cmd =%s", temp);
        op_ret = product_test_get_common_device_Para(temp);
        if (OPRT_OK == op_ret) {
        } else {
            PR_ERR("Product_TEST_GET_COMMON_CMD");
            op_ret = OPRT_INVALID_PARM;
        }
        Free(temp);
    }
    break;


    default:
        break;
    }

    if (op_ret != OPRT_OK) {
        PR_DEBUG("test error %d", op_ret);
    } else {
        //成功
        PR_NOTICE("test ok");
    }


    if ((cmd != PRODUCT_TEST_IPC_IMG_GET_SUB_CMD) && (cmd != PRODUCT_TEST_BUTTON_SUM_CMD) && (cmd != PRODUCT_TEST_GET_COMMON_CMD)) {

        //生成json字符串
        if (PRODUCT_TEST_READ_SN_CMD != cmd) {
            if (op_ret == OPRT_OK) {
                *ret_data = (UCHAR_T *)ty_cJSON_PrintUnformatted(root);

                if (*ret_data != NULL) {
                    //获取json长度
                    *ret_len = strlen((CHAR_T *)(*ret_data));
                }
                PR_DEBUG_RAW("response: ");
                tuya_print_data(*ret_data, *ret_len);
                PR_DEBUG("data %s", *ret_data);
            }
        } else {
            if (data_temp) {
                if (op_ret == OPRT_OK) {
                    *ret_data = data_temp;
                    *ret_len = strlen((CHAR_T *)(*ret_data));
                    PR_DEBUG_RAW("response: ");
                    tuya_print_data(*ret_data, *ret_len);
                    PR_DEBUG("data %s", *ret_data);
                } else {
                    Free(data_temp);
                }
            }
        }


    }

    //释放root
    if (root != NULL) {
        ty_cJSON_Delete(root);
        root = NULL;
    } else {
        //创建json对象失败
        op_ret = OPRT_CR_CJSON_ERR;
    }

    //释放recv
    if (recv != NULL) {
        ty_cJSON_Delete(recv);
        recv = NULL;
        type = NULL;
    }

    return op_ret;

}




//串口产测命令
OPERATE_RET kiwi_uart_product_test(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    //todo

    return op_ret;
}
