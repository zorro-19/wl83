#ifndef __RF_COEXISTENCE_CONFIG_H__
#define __RF_COEXISTENCE_CONFIG_H__

/*********************************************************************************************************
0 - 均衡模式1：适用于wifi连接路由器后且edr配对前
1 - 均衡模式2：适用于edr配对后(接收模式)，适用于蓝牙接收多，发送少的场景，wifi保持连接
2 - 蓝牙绝对优先模式：wifi只能在蓝牙空闲的片段里工作，对wifi的性能有较大影响
3 - wifi绝对优先模式：一般用于开机时wifi快速连上路由器，不受蓝牙回连干扰，但不抢BLE，对edr的性能有较大影响
4 - wifi相对优先模式：优先保证wifi收发，不保证蓝牙播歌通话不卡，不抢BLE
5 - 均衡模式3：适用于edr配对后(发送模式)，适用于蓝牙发送多，接收少的场景
6 - 均衡模式4：791x新增细调优先级测试，用于替代参数表1，适用于edr接收多的均衡共存模式
7 - 均衡模式5：一般用于设备edr主动回连时释放部分带宽给wifi
*********************************************************************************************************/

typedef enum : u8 {
    RF_COEXISTENCE_SCENE_WIFI_FAST_CONNECT,
    RF_COEXISTENCE_SCENE_WIFI_CONNECT,
    RF_COEXISTENCE_SCENE_LOCAL_TWS_TX,
    RF_COEXISTENCE_SCENE_LOCAL_TWS_RX,
    RF_COEXISTENCE_SCENE_A2DP_PLAY,

    RF_COEXISTENCE_SCENE_NORMAL = 0xfe,
    RF_COEXISTENCE_SCENE_MAX = 0xff,
} rf_scene_t;

/* --------------------------------------------------------------------------*/
/**
 * @brief 切换RF共存参数表
 * @param[in] index 参数表序号
 */
/* ----------------------------------------------------------------------------*/
void switch_rf_coexistence_config_table(u8 index);

/* --------------------------------------------------------------------------*/
/**
 * @brief 锁定RF共存参数表
 * @note  锁定后再切换参数表将无效
 */
/* ----------------------------------------------------------------------------*/
void switch_rf_coexistence_config_lock(void);

/* --------------------------------------------------------------------------*/
/**
 * @brief 解锁RF共存参数表
 */
/* ----------------------------------------------------------------------------*/
void switch_rf_coexistence_config_unlock(void);

/* --------------------------------------------------------------------------*/
/**
 * @brief 获取当前RF共存参数表的序号
 * @return 当前参数表的序号
 */
/* ----------------------------------------------------------------------------*/
u8 get_rf_coexistence_config_index(void);

int rf_coexistence_scene_enter(rf_scene_t scene, u32 run_duration_ms);

int rf_coexistence_scene_exit(rf_scene_t scene);

#endif
