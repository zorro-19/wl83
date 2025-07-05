#ifndef _RCSP_EXTRA_FLASH_OPT_H_
#define _RCSP_EXTRA_FLASH_OPT_H_
#include "typedef.h"
// #include "system/event.h"
#include "event/event.h"

//*----------------------------------------------------------------------------*/
/**@brief    外部flash操作函数
   @param    param:数据, len:数据长度，OpCode:命令号，OpCode_SN:数据包序列号
   @return   0-成功，其他-失败
   @note
*/
/*----------------------------------------------------------------------------*/
int rcsp_extra_flash_opt(u8 *data, u16 len, u8 OpCode, u8 OpCode_SN);
//*----------------------------------------------------------------------------*/
/**@brief    填充表盘操作第一条命令的数据回复包
   @param    resp_data:数据回复包
   @return   负数-失败，正数-数据长度
   @note
*/
/*----------------------------------------------------------------------------*/
int rcsp_get_extra_flash_info(void *priv, u8 *resp_data);
//*----------------------------------------------------------------------------*/
/**@brief    外部flash开始操作
   @param
   @return   0-成功，其他-失败
   @note
*/
/*----------------------------------------------------------------------------*/
int rcsp_extra_flash_opt_start(void);
//*----------------------------------------------------------------------------*/
/**@brief    外部flash结束操作
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void rcsp_extra_flash_opt_stop(void);

//*----------------------------------------------------------------------------*/
/**@brief    主动通知app当前表盘路径，用于表盘操作
   @param    file_path:路径名，file_path_size:路名名长度
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void rcsp_extra_flash_opt_dial_nodify(void);
//*----------------------------------------------------------------------------*/
/**@brief    设置异常状态标志位
   @param    eflash_state_type:标志位
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void rcsp_eflash_flag_set(u8 eflash_state_type);
//*----------------------------------------------------------------------------*/
/**@brief    获取异常状态标志位
   @param
   @return   1-处于异常，0-正常
   @note
*/
/*----------------------------------------------------------------------------*/
u8 rcsp_eflash_flag_get(void);
//*----------------------------------------------------------------------------*/
/**@brief    获取升级异常状态标志位
   @param
   @return   1-处于异常，0-正常
   @note
*/
/*----------------------------------------------------------------------------*/
void rcsp_eflash_update_flag_set(u8 eflash_state_type);
//*----------------------------------------------------------------------------*/
/**@brief    获取升级异常状态标志位
   @param
   @return   1-处于异常，0-正常
   @note
*/
/*----------------------------------------------------------------------------*/
u8 rcsp_eflash_update_flag_get(void);

// rcsp外挂flash初始化
void rcsp_extra_flash_init(void);
// rcsp外挂flash事件处理
int rcsp_extra_flash_event_deal(struct sys_event *event);
// rcsp外挂flash关闭
void rcsp_extra_flash_close(void);

// rcsp外挂flash无线断开后操作
void rcsp_extra_flash_disconnect_tips(u32 sec);

//*----------------------------------------------------------------------------*/
/**@brief    检查当前是否处于表盘升级状态
   @param    param:状态标志
   @return   true-处于升级状态，false-其他状态
   @note
*/
/*----------------------------------------------------------------------------*/
bool rcsp_exflash_flash_opt_check(void *param);

#endif
