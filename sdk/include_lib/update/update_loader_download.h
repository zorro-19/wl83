#ifndef _UPDATE_LOADER_DOWNLOAD_H_
#define _UPDATE_LOADER_DOWNLOAD_H_

#include "typedef.h"
#include "error_code.h"

extern const int config_update_mode;
extern const int support_dual_bank_update_en;

extern const int CONFIG_UPDATE_ENABLE;
extern const int CONFIG_UPDATE_STORAGE_DEV_EN;
extern const int CONFIG_UPDATE_BLE_TEST_EN;
extern const int CONFIG_UPDATE_BT_LMP_EN;

#define UPDATE_MODULE_IS_SUPPORT(x) 		(config_update_mode & x)
#define UPDATE_SUPPORT_DEV_IS_NULL()		(config_update_mode == UPDATE_DEV_NULL)
#define UPDATE_DUAL_BANK_IS_SUPPORT()		(1 == support_dual_bank_update_en)

struct __tws_ota_para {
    u32 fm_size;
    u32 fm_crc;
    u16 max_pkt_len;
};

typedef struct _ret_code {
    int stu;
    update_err_t err_code;
} update_ret_code_t;

typedef struct _update_op_api_tws {
    //for tws ota start
    int (*tws_ota_start)(void *priv);
    int (*tws_ota_data_send)(u8 *buf, u16 len);
    int (*tws_ota_err)(u8);
    u16(*enter_verfiy_hdl)(void *priv);
    u16(*exit_verify_hdl)(u8 *, u8 *);
    u16(*update_boot_info_hdl)(void *priv);
    int (*tws_ota_result_hdl)(u8);
    int (*tws_ota_data_send_pend)(void);
    //for user chip update
    int (*tws_ota_user_chip_update_send)(u8 cmd, u8 *buf, u16 len);
} update_op_tws_api_t;  //给tws同步升级用的接口

update_op_tws_api_t *get_tws_update_api(void);
void tws_sync_update_crc_handler_register(void (*crc_init_hdl)(void), u32(*crc_calc_hdl)(u32 init_crc, u8 *data, u32 len));
void update_start_exit_sniff(void);
void set_ota_status(u8 status);

typedef struct _update_op_api_t {
    void (*ch_init)(void (*resume_hdl)(void *priv), int (*sleep_hdl)(void *priv));
    u16(*f_open)(void);
    u16(*f_read)(void *fp, u8 *buff, u16 len);
    int (*f_seek)(void *fp, u8 type, u32 offset);
    u16(*f_stop)(update_err_t err);
    int (*notify_update_content_size)(void *priv, u32 size);
    void (*ch_exit)(void *priv);
    int (*version_cmp)(void *version, u32 len);
} update_op_api_t;

extern const update_op_api_t lmp_ch_update_op;
extern const update_op_api_t strg_ch_update_op;
extern const update_op_api_t rcsp_update_op;

#define UPDATE_SEAGNMENT_EN	0

enum {
    UPDATE_LOADER_OK  = 1,
    UPDATE_LOADER_ERR,
};

enum {
    PKT_FLAG_MIDDLE = 0,
    PKT_FLAG_FIRST,
    PKT_FLAG_LAST,
};

//update result code bitmap
#define UPDATE_RESULT_FLAG_BITMAP 		BIT(7)

#include "system/task.h"
typedef struct _update_type_info_t {
    int type;
    u8  task_en;
    void (*cb)(void *priv, int type, u8 cmd);
    void *cb_priv;
    update_op_api_t *p_op_api;
    void (*common_state_cbk)(int type, u32 status, u32 code);
    OS_SEM update_sem;
} update_type_info_t;

typedef struct _update_mode_info_t {
    s32 type;
    void (*state_cbk)(int type, u32 status, void *priv);
    const update_op_api_t *p_op_api;
    u8 task_en;
} update_mode_info_t;

typedef struct _succ_report_t {
    u32 loader_saddr;
    u32 priv_param;
    update_err_t (*update_param_write_hdl)(u32 priv, u8 *buf, u16 len);
} succ_report_t;

#define UPDATE_DEV_NULL			0
#define UPDATE_BT_LMP_EN		BIT(0)
#define UPDATE_STORAGE_DEV_EN	BIT(1)
#define UPDATE_UART_EN			BIT(2)
#define UPDATE_APP_EN	     	BIT(3)   //包括APP升级还有其他升级方式，如串口升级（非测试盒方式）
#define UPDATE_BLE_TEST_EN		BIT(4)

typedef struct _user_chip_update_t {
    u8 *file_name;
    int (*update_init)(void *priv, const update_op_api_t *file_ops);
    int (*update_get_len)(void);
    int (*update_loop)(void *priv);
} user_chip_update_t;

typedef struct _user_chip_info_t {
    union {
        struct {
            u32 file_addr;
        };
        struct {
            u32 addr;
        };
    };
    u32 len;
    u16 crc;
    u32 dev_addr;
} user_chip_update_info_t;

typedef struct _update_size_t {
    u8 type;
} update_type_t;

enum UPDATE_SIZE_TYPE {
    UPDATE_LEN_TYPE_CONTENT = 0,
    UPDATE_LEN_TYPE_LOADER,
    UPDATE_LEN_TYPE_EX_IC,
};

void register_user_chip_update_handle(const user_chip_update_t *user_update_ins);
void rcsp_update_loader_download_init(int update_type, void (*result_cbk)(void *priv, u8 type, u8 cmd));

int app_active_update_task_init(update_mode_info_t *info);
update_err_t update_file_verify(u32 ufw_addr, u32(*ufw_read)(void *buf, u32 addr, u32 len));

//==========================================================//
//  		           获取升级进度信息                     //
//注意: 只有双备份升级可以获取该信息                        //
//==========================================================//
typedef struct _update_percent_info {
    u32 total_len;  //固件总升级大小
    u32 finish_len; //当前完成升级大小
    u32 percent;    //当前进度百分比
} update_percent_info;

//注册升级进度更新回调函数:
void register_update_percent_info_callback_handle(void (*handle)(update_percent_info *info));

//查询当前升级进度信息:
void update_percent_info_query(update_percent_info *info);

#endif /*_UPDATE_LOADER_DOWNLOAD_H_*/

