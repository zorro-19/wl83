#ifndef __AVDD_CONFIG_H__
#define __AVDD_CONFIG_H__

/**
 * @brief 设置PV口的方向
 * @param gpio 参考宏IO_PORT_PV_0X
 * @param dir 1: 输入       0: 输出
 * @return 0: 成功  非0: 失败
 */
int avdd_port_pv_dir(int port, u8 dir);

/**
 * @brief 获取PV口输入电平
 * @param gpio 参考宏IO_PORT_PV_0X
 * @return 0: 低电平  1: 高电平
 */
int avdd_port_pv_read(int port);

/**
 * @brief 设置PV口的输出电平
 * @param gpio 参考宏IO_PORT_PV_0X
 * @param on 1: 高电平       0: 低电平
 * @return 0: 成功  非0: 失败
 */
int avdd_port_pv_out(int port, u8 on);

/**
 * @brief 设置PV口的强驱
 * @param gpio 参考宏IO_PORT_PV_0X
 * @param on 1: 打开       0: 关闭
 * @return 0: 成功  非0: 失败
 */
int avdd_port_pv_hd(int port, u8 on);

/**
 * @brief 设置PV口的上拉电阻
 * @param gpio 参考宏IO_PORT_PV_0X
 * @param on 1: 打开       0: 关闭
 * @return 0: 成功  非0: 失败
 */
int avdd_port_pv_pu(int port, u8 on);

/**
 * @brief 设置PV口的下拉电阻
 * @param gpio 参考宏IO_PORT_PV_0X
 * @param on 1: 打开       0: 关闭
 * @return 0: 成功  非0: 失败
 */
int avdd_port_pv_pd(int port, u8 on);

/**
 * @brief 设置PV口的数字输入功能
 * @param gpio 参考宏IO_PORT_PV_0X
 * @param on 1: 打开       0: 关闭
 * @return 0: 成功  非0: 失败
 */
int avdd_port_pv_die(int port, u8 on);

#endif
