#include "system/includes.h"
#include "app_database.h"
#include "app_config.h"
#include "generic/typedef.h"
#include "syscfg/syscfg_id.h"

#define CN_PA   ((0xA9BE << 16) | ('A' << 8)  | ('B' << 0))
#define CN_PB   (('C'    << 24) | ('D' << 16) | ('E' << 8) | ('F' << 0))


#define    CFG_USER_POWER_OFF           2
#define    CFG_USER_NET_CFG             3
#define    CFG_USER_NET_CFG_REST        4//配网前的重启
#define    VM_RES_INDEX                 5
#define    VM_CYC_INDEX                 6
#define    VM_MIC_INDEX                 7
#define    VM_DAT_INDEX                 8


/*
 * app配置项表
 * 参数1: 配置项名字
 * 参数2: 配置项需要多少个字节存储(最大4字节)
 * 参数3: 配置项INDEX
 * 参数4: 配置项的默认值
 */

const struct db_cfg db_config_table[] = {
    {"res",     1,   VM_RES_INDEX,   	VIDEO_RES_VGA},           	// 录像分辨率
    {"cyc",     1,   VM_CYC_INDEX,   	1 },                         // 循环录像时间，单位分钟
    {"mic",     1,   VM_MIC_INDEX,   	1 },                         // 录音开关
    {"dat",     1,   VM_DAT_INDEX,   	1 },                         // 时间标签开关
    {"mir",     1,   CFG_REMOTE_DB_03,   	0 },                         // 摄像头镜像标签开关
    {"irc",     1,   CFG_REMOTE_DB_04,   	2 },                         // 摄像头夜视标签开关
    {"tzone",     2,   CFG_REMOTE_DB_05,   	480 },                         // rtc时区标签开关
    {"rec_evet",     1,   CFG_REMOTE_DB_06,   	1 },                         // 录像事件标签开关
    {"motion",     2,   CFG_REMOTE_DB_07,   	350 },                         // 移动侦测触发灵敏度
    {"time_level",     2,   CFG_REMOTE_DB_08,   	30 },                         // 移动侦测触推送事件间隔
};

int get_db_config_table_size()
{
    size_t size = ARRAY_SIZE(db_config_table);
    return size;
}

int db_select(const char *name)
{
    int err;
    int value = 0;

    if (name == NULL) {
        return -EINVAL;
    }

    for (int i = 0; i < ARRAY_SIZE(db_config_table); i++) {
        if (!strcmp(name, db_config_table[i].name)) {
            err = syscfg_read(db_config_table[i].index, &value, db_config_table[i].len);
            if (err <= 0) {
                puts(">>>syscfg_read err");
                return -EINVAL;
            }
            return value;
        }
    }
    return -EINVAL;
}

int db_update(const char *name, u32 value)
{
    int err;

    if (name == NULL) {
        return -EINVAL;
    }

    for (int i = 0; i < ARRAY_SIZE(db_config_table); i++) {
        if (!strcmp(name, db_config_table[i].name)) {
            err = syscfg_write(db_config_table[i].index, &value, db_config_table[i].len);
            if (err <= 0) {
                puts(">>>syscfg_write err");
                return -EINVAL;
            }
            return 0;
        }
    }
    return -EINVAL;
}

static int app_config_init()
{
    int err;
    int value;

    for (int i = 0; i < ARRAY_SIZE(db_config_table); i++) {
        value = 0;
        err = syscfg_read(db_config_table[i].index, &value, db_config_table[i].len);
        if (err < 0) {
            err = syscfg_write(db_config_table[i].index, &db_config_table[i].value, db_config_table[i].len);
            if (err <= 0) {
                puts(">>>app_config_init err");
                return -EINVAL;
            }
        }
    }

    return 0;
}

__initcall(app_config_init);
