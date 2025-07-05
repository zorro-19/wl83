#include "system/includes.h"
#include "app_database.h"
#include "app_config.h"
#include "generic/typedef.h"
#include "syscfg/syscfg_id.h"
#include "database.h"
//813d43e
/* #define CN_PA   (0x4EAC) */
//#define CN_PA   (0xE4BAAC)
//#define CN_PA   (0x4EAC)
/* #define CN_PB   (('A' << 24) | (' ' << 16) | ('1' << 8)  | ('2' << 0)) */
#define CN_PC   (('3' << 24) | ('4' << 16) | ('5' << 8) | (' ' << 0))


#define CN_PA   (('0' << 24) | ('A' << 16)  | (0xA9BE << 0))
#define CN_PB   (('0'    << 24) | ('0' << 16) | ('0' << 8) | ('0' << 0))

#define DB_UPDATE_TASK  "db_update_task"
extern const int config_vm_save_in_ram_enable;
static int task_pid;


//TODO 用户自定义配置项[2 ~ 58]
#define    VM_RES_INDEX                 3
#define    VM_CYC_INDEX                 4
#define    VM_GAP_INDEX                 5
#define    VM_TWO_INDEX                 6
#define    VM_NUM_INDEX                 7
#define    VM_MIC_INDEX                 8
#define    VM_PDAT_INDEX                9
#define    VM_CYT_INDEX                 10
#define    VM_QUA_INDEX                 11
#define    VM_ACU_INDEX                 12
#define    VM_PHM_INDEX                 13
#define    VM_PRES_INDEX                14
#define    VM_WBL_INDEX                 15
#define    VM_COL_INDEX                 16
#define    VM_SCA_INDEX                 17
//#define    VM_PEXP_INDEX                18
#define    VM_ISO_INDEX                 19
#define    VM_STK_INDEX                 20
#define    VM_DELAY_INDEX               21
#define    VM_RTF_INDEX                 22
#define    VM_RTB_INDEX                 23
#define    VM_WFO_INDEX                 24
#define    VM_WFMODE_INDEX              25
#define    VM_BVO_INDEX                 26
#define    VM_DAT_INDEX                 27
#define    VM_MOT_INDEX                 28
#define    VM_PAR_INDEX                 29
#define    VM_WDR_INDEX                 30
#define    VM_GRA_INDEX                 31
#define    VM_EXP_INDEX                 32
#define    VM_KVO_INDEX                 33
//#define    VM_KVO_INDEX                 34
#define    VM_CNA_INDEX                 34
#define    VM_CNB_INDEX                 35
#define    VM_CNC_INDEX                 36
#define    VM_LAN_INDEX                 37
#define    VM_PEXP_INDEX                38
#define    VM_LAG_INDEX                 39
#define    VM_HLW_INDEX                 40
#define    VM_FRE_INDEX                 41
#define    VM_AFF_INDEX                 42
#define    VM_DAC_INDEX                 43
#define    VM_TVM_INDEX                 44
#define    VM_PRO_INDEX                 45
#define    VM_HDR_INDEX                 46
#define    VM_SOK_INDEX                 47
#define    VM_DATEY_INDEX               48//年
#define    VM_DATEM_INDEX               49//月
#define    VM_DATED_INDEX               50//日
#define    VM_DATEH_INDEX               51//时
#define    VM_DATEMI_INDEX              52//分
#define    VM_DATES_INDEX              53//分
//#define    VM_PROC_INDEX                54 //省
#define    VM_ZOOM_INDEX                55
#define    VM_PROC_INDEX                56 //省

static const struct db_cfg config_table[] = {
    /*
     *  录像模式配置项
     */
    {"mic",     1,   VM_MIC_INDEX,  1},                         // 录音开关
    {"mot",     1,   VM_MOT_INDEX,  0},                         // 移动侦测开关
    {"par",     1,   VM_PAR_INDEX,  1},                         // 停车守卫开关
    {"wdr",     1,   VM_WDR_INDEX,  0},                         // 夜视增强开关
    {"num",     1,   VM_NUM_INDEX,  0},                         // 车牌开关
    {"dat",     1,   VM_DAT_INDEX,  1},                         // 时间标签开关
    {"two",     1,   VM_TWO_INDEX,  1},                         // 双路开关
    {"gra",     2,   VM_GRA_INDEX,  GRA_SEN_MD},               // 重力感应灵敏度
    {"gap",     4,      VM_GAP_INDEX, 0},                         // 间隔录影设置
    {"res",     3,   VM_RES_INDEX,  VIDEO_RES_720P},           // 录像分辨率
    {"cyc",     4,   VM_CYC_INDEX,  3},                         // 循环录像时间，单位分钟
    {"exp",     4,   VM_EXP_INDEX,  0},                         // 曝光, 范围-3到+3
    {"cna",     4,  VM_CNA_INDEX,  CN_PA},                     // 车牌号码--京
    {"cnb",     4,  VM_CNB_INDEX,  CN_PB},                     // 车牌号码 --A 12
    {"cnc",     4,  VM_CNC_INDEX,  CN_PC},                     // 车牌号码 --345
    {"proc",     4,  VM_PROC_INDEX,  0},                     // 车牌号码 --345
    {"hdr",     4,  VM_HDR_INDEX,  0},                     // HDR
    /*
     *  系统模式配置项
     */
    {"kvo",     1,  VM_KVO_INDEX,  1},                         // 按键音开关
    {"lag",     4,  VM_LAG_INDEX,  1},        // 语言设置
    {"fre",     4,  VM_FRE_INDEX,  50},                        // 灯光频率
    {"aff",     4,  VM_AFF_INDEX,  0},                         // 自动关机时间, 单位分钟
    {"pro",     4,  VM_PRO_INDEX,  0},                         // 屏幕保护时间, 单位秒
    {"tvm",     4,  VM_TVM_INDEX,  TVM_PAL},                   // 电视制式
    {"lan",     4, VM_LAN_INDEX,  0},                         // 轨道偏移
    {"hlw",     1,  VM_HLW_INDEX,  0},                         // 前照灯提醒开关
    {"datey",     4,  VM_DATEY_INDEX,  2024},                         // 年
    {"datem",     1,  VM_DATEM_INDEX,  5},                         // 月
    {"dated",     1,  VM_DATED_INDEX,  20},                         //日
    {"dateh",     1,  VM_DATEH_INDEX,  13},                         // 时
    {"datemi",     1,  VM_DATEMI_INDEX,  14},                         // 分
    {"dates",     1,  VM_DATES_INDEX,  10},                         // 秒

    /*
     *  拍照模式配置项
     */
    {"sok",     1,  VM_SOK_INDEX,   0},                         // 防手抖开关
    {"pdat",    1,  VM_PDAT_INDEX,   0},                         // 图片日期标签开关
    {"cyt",     1,  VM_CYT_INDEX,   0},                         // 连拍开关
    {"qua",     3,  VM_QUA_INDEX,   PHOTO_QUA_HI},              // 图片质量
    {"acu",     3,  VM_ACU_INDEX,   PHOTO_ACU_HI},              // 图片锐度
    {"phm",     4,  VM_PHM_INDEX,   0},                         // 延时拍照， 单位秒
    {"pres",    4,  VM_PRES_INDEX,   PHOTO_RES_1M},              // 图片分辨率
    {"wbl",     4,  VM_WBL_INDEX,   PHOTO_WBL_AUTO},            // 白平衡
    {"col",     4,  VM_COL_INDEX,   PHOTO_COLOR_NORMAL},        // 颜色模式
    {"sca",     4,  VM_SCA_INDEX,   0},                         // 快速预览时间，单位s
    {"pexp",    4,  VM_PEXP_INDEX,   0},                         // 曝光设置，范围-3到+3
    {"iso",     4, VM_ISO_INDEX,   0},                         // iso
    {"stk",     4,  VM_STK_INDEX,   0},                         // 大头贴索引
    {"zoom",     4,  VM_ZOOM_INDEX,   10},              // 数字变焦,为了方便传参,实际值除以10

    {"dac",     4, VM_DAC_INDEX,   0x55aa},                         // dac_trim
#ifdef CONFIG_WIFI_ENABLE
    /* {"res2",    3,      VIDEO_RES_VGA},           // 录像分辨率 */
    {"rtf",     3,  VM_RTF_INDEX,    VIDEO_RES_720P},            //预览前视分辨率
    {"rtb",     3,  VM_RTB_INDEX,    VIDEO_RES_VGA},             //预览后视分辨率
    {"wfo",     1,  VM_WFO_INDEX,    1},                         //wifi开关
    {"wfmode",  1,  VM_WFMODE_INDEX,    0},                        // wifi运行模式
    {"bvo",     1,  VM_BVO_INDEX,    1},                         // 开机音开关
#endif
};

int db_select(const char *name)
{
    int err;
    int value = 0;

    if (name == NULL) {
        return -EINVAL;
    }

    for (int i = 0; i < ARRAY_SIZE(config_table); i++) {
        if (!strcmp(name, config_table[i].name)) {
            ASSERT(config_table[i].len <= sizeof(value), "err in config_table index %d --> len = %d, but max_len = %d", config_table[i].index, config_table[i].len, sizeof(value));
            err = syscfg_read(config_table[i].index, &value, config_table[i].len);
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
    int msg;

    if (name == NULL) {
        return -EINVAL;
    }

    for (int i = 0; i < ARRAY_SIZE(config_table); i++) {
        if (!strcmp(name, config_table[i].name)) {
            ASSERT(config_table[i].len <= sizeof(value), "err in config_table index %d --> len = %d, but max_len = %d", config_table[i].index, config_table[i].len, sizeof(value));
            err = syscfg_write(config_table[i].index, &value, config_table[i].len);
            if (err <= 0) {
                puts(">>>syscfg_write err");
                return -EINVAL;
            }
            break;
        }
    }

    if (config_vm_save_in_ram_enable) {
        msg = config_vm_save_in_ram_enable;
        err = os_taskq_post_type(DB_UPDATE_TASK, Q_MSG, 1, &msg);
        if (err) {
            printf("database taskq post err:%d\n", err);
        }
    }

    return err;
}

int app_set_config(struct intent *it, const struct app_cfg *cfg, int size)
{
    int i;

    printf("app_set_config: %s, %d\n", it->data, it->exdata);

    for (i = 0; i < size; i++) {
        if (!strcmp(it->data, cfg[i].table)) {
            if (cfg[i].set) {
                int err = cfg[i].set(it->exdata);
                if (err) {
                    return err;
                }
            }
            db_update(cfg[i].table, it->exdata);
            return 0;
        }
    }

    return -EINVAL;
}


//恢复默认配置--用户配置项0~59
int db_reset(void)
{
    int err;
    int value;

    for (int i = 0; i < ARRAY_SIZE(config_table); i++) {
        value = 0;
        ASSERT(config_table[i].len <= sizeof(value), "err in config_table index %d --> len = %d, but max_len = %d", config_table[i].index, config_table[i].len, sizeof(value));
        err = syscfg_write(config_table[i].index, &config_table[i].value, config_table[i].len);
        printf("[chili] %s index:%d value:0x%x \n",  __func__, config_table[i].index, config_table[i].value);
        if (err <= 0) {
            puts(">>>db_reset err");
            return -EINVAL;
        }

    }
    puts(">>>db_reset okk~");
    return 0;
}


static void db_update_task(void)
{
    int res;
    int err;
    int msg[8];

    while (1) {
        res = os_task_pend("taskq", msg, ARRAY_SIZE(msg));

        switch (res) {
        case OS_TASKQ:
            switch (msg[0]) {
            case Q_EVENT:
                break;
            case Q_MSG:
                int update = msg[1];
                if (update) {
                    vm_in_ram_update();
                }
                break;
            case Q_USER:
                break;
            default:
                break;
            }
            break;
        case OS_TIMER:
            break;
        case OS_TIMEOUT:
            break;
        }
    }

}



static int app_config_init()
{
    int err;
    int value;

    for (int i = 0; i < ARRAY_SIZE(config_table); i++) {
        value = 0;
        ASSERT(config_table[i].len <= sizeof(value), "err in config_table index %d --> len = %d, but max_len = %d", config_table[i].index, config_table[i].len, sizeof(value));
        err = syscfg_read(config_table[i].index, &value, config_table[i].len);
        if (err < 0) {
            err = syscfg_write(config_table[i].index, &config_table[i].value, config_table[i].len);
            if (err <= 0) {
                puts(">>>app_config_init err");
                return -EINVAL;
            }
        }
    }

    if (config_vm_save_in_ram_enable) {
        thread_fork(DB_UPDATE_TASK, 10, 300, 300, &task_pid, db_update_task, NULL);
    }

    return 0;
}

__initcall(app_config_init);


