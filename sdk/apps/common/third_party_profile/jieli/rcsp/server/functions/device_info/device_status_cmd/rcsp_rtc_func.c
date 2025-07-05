#ifdef MEDIA_SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".rcsp_rtc_func.data.bss")
#pragma data_seg(".rcsp_rtc_func.data")
#pragma const_seg(".rcsp_rtc_func.text.const")
#pragma code_seg(".rcsp_rtc_func.text")
#endif
#include "rcsp_rtc_func.h"
#include "rcsp_device_status.h"
#include "rcsp_config.h"
#include "rcsp_event.h"
/* #include "app_action.h" */
#include "rcsp_music_info_setting.h"
#include "btstack/avctp_user.h"
#include "JL_rcsp_packet.h"
/* #include "key_event_deal.h" */
#include "app_msg.h"
#include "rcsp_manage.h"
#include "tone_player.h"
#include "rcsp_browser.h"
/* #include "app_protocol_common.h" */
/* #include "clock_manager/clock_manager.h" */
//#include "music/general_player.h"
#include "JL_rcsp_api.h"
#include "JL_rcsp_attr.h"

#if (RCSP_MODE && TCFG_APP_RTC_EN && RCSP_APP_RTC_EN)
#include "music/general_player.h"
#include "alarm.h"
#include "rcsp_device_info_func_common.h"
#if TCFG_APP_LINEIN_EN
/* #include "linein.h" */
#endif
#include "alarm.h"


#define RTC_INFO_ATTR_RTC_TIME                 (0)
#define RTC_INFO_ATTR_RTC_ALRAM                (1)
#define RTC_INFO_ATTR_RTC_ALRAM_ACTIVE         (2)
#define RTC_INFO_ATTR_RTC_ALRAM_UNACTIVE       (3)
#define RTC_INFO_ATTR_RTC_ALRAM_STRUCTURE      (4)
#define RTC_INFO_ATTR_RTC_ALRAM_DEFAULT_RING   (5)
#define RTC_INFO_ATTR_RTC_ALRAM_RING_AUDITION  (6)
#define RTC_INFO_ATTR_RTC_ALARM_EX			   (7)

// 0是不停止
#define RCSP_ALARM_RING_MAX		50

#pragma pack(1)
typedef struct __APP_ALARM__ {
    u8 index;
    u8 sw;
    u8 mode;
    u8 bHour;
    u8 bMin;
    u8 name_len;
} T_ALARM_APP, *PT_ALARM_APP;

typedef struct __APP_ALARM_EXTRA_DATA__ {
    u8 type;
    u8 dev;
    u32 clust;
    u8 ring_name_len;
    u8 ring_name[32];
} T_ALARM_APP_EXTRA_DATA, *PT_ALARM_APP_EXTRA_DATA;

typedef struct __APP_ALARM_RING_AUDITION__ {
    u8 prev_app_mode;
    u8 ring_op;
    u8 ring_type;
    u8 ring_dev;
    u32 ring_clust;
    u32 ring_timeout;
} T_ALARM_APP_RING_AUDITION, *PT_ALARM_APP_RING_AUDITION;

typedef struct __APP_ALARM_DATA_EX {
    u8 len;
    u8 index;
    u8 count;
    u8 interval;
    u8 alarmTime;
} T_ALARM_APP_DATA_EX, *PT_ALARM_APP_DATA_EX;

#pragma pack()

enum {
    E_ALARM_SET = 0x00,
    E_ALARM_DELETE,
    E_ALARM_UNACTIVE,
};

enum {
    ALARM_IDEX_TONE_NUM_0 = 0,
    ALARM_IDEX_TONE_NUM_1 = 1,
    ALARM_IDEX_TONE_NUM_2 = 2,
    ALARM_IDEX_TONE_NUM_3 = 3,
    ALARM_IDEX_TONE_NUM_4 = 4,
    ALARM_IDEX_TONE_NUM_5 = 5,
    ALARM_IDEX_TONE_NUM_6 = 6,
    ALARM_IDEX_TONE_NUM_7 = 7,
    ALARM_IDEX_TONE_NUM_8 = 8,
    ALARM_IDEX_TONE_NUM_9 = 9,

    ALARM_IDEX_TONE_MAX_NUM = 10,
};
static const char *default_ringtone_table[] = {
    [ALARM_IDEX_TONE_NUM_0] 			= "tone_zh/0.*",
    [ALARM_IDEX_TONE_NUM_1] 			= "tone_zh/1.*",
    [ALARM_IDEX_TONE_NUM_2] 			= "tone_zh/2.*",
    [ALARM_IDEX_TONE_NUM_3] 			= "tone_zh/3.*",
    [ALARM_IDEX_TONE_NUM_4] 			= "tone_zh/4.*",
    [ALARM_IDEX_TONE_NUM_5] 			= "tone_zh/5.*",
    [ALARM_IDEX_TONE_NUM_6] 			= "tone_zh/6.*",
    [ALARM_IDEX_TONE_NUM_7] 			= "tone_zh/7.*",
    [ALARM_IDEX_TONE_NUM_8] 			= "tone_zh/8.*",
    [ALARM_IDEX_TONE_NUM_9] 			= "tone_zh/8.*",
};

static const char *default_ringtone_name_table[] = {
    [ALARM_IDEX_TONE_NUM_0] 			= "提示音0",
    [ALARM_IDEX_TONE_NUM_1] 			= "1",
    [ALARM_IDEX_TONE_NUM_2] 			= "2",
    [ALARM_IDEX_TONE_NUM_3] 			= "3",
    [ALARM_IDEX_TONE_NUM_4] 			= "4",
    [ALARM_IDEX_TONE_NUM_5] 			= "5",
    [ALARM_IDEX_TONE_NUM_6] 			= "6",
    [ALARM_IDEX_TONE_NUM_7] 			= "7",
    [ALARM_IDEX_TONE_NUM_8] 			= "8",
    [ALARM_IDEX_TONE_NUM_9] 			= "9",
};

static void scan_enter(struct __dev *dev)
{
    /* clock_add_set(SCAN_DISK_CLK); */
    clock_alloc("SCAN_DISK_CLK", 120 * 1000000UL);
}

static void scan_exit(struct __dev *dev)
{
    /* clock_remove_set(SCAN_DISK_CLK); */
    clock_free("SCAN_DISK_CLK");
}

static const struct __scan_callback scan_cb = {
    .enter = scan_enter,
    .exit = scan_exit,
    .scan_break = general_player_scandisk_break,
};

static u8 rtc_func_structure_flag = CUR_RTC_ALARM_MODE;
static u8 rtc_ringing_prev_mode = -1;
static T_ALARM_APP_RING_AUDITION g_ring_audition = {
    .prev_app_mode = -1,
};

static u8 count = 0;
static u8 flag = 0;
static u8 count_flag = 0;
static u16 rcsp_rtc_ex_timer = 0;
static u16 rcsp_rtc_ex_timer1 = 0;
u8 index_flag = -1;

extern void file_trans_idle_set(u8 file_trans_idle_flag);

static u8 rcsp_rtc_get_alarm_info(PT_ALARM_APP p, u8 index)
{
    extern u8 alarm_get_info(PT_ALARM p, u8 index);
    u8 ret = 0;
    T_ALARM alarm_param;
    ret = alarm_get_info(&alarm_param, index);
    p->index = alarm_param.index;
    p->sw = alarm_param.sw;
    p->mode = alarm_param.mode;
    p->bHour = alarm_param.time.hour;
    p->bMin = alarm_param.time.min;
    p->name_len = alarm_param.name_len;
    return ret;
}

static u8 rcsp_rtc_get_alarm_total(void)
{
    extern u8 alarm_get_total(void);
    u8 total = 0;
    total = alarm_get_total();
    return total;
}

static u8 m_func_alarm_get_active_index(void)
{
    extern u8 alarm_get_active_index(void);
    return alarm_get_active_index();
}

static u8 m_func_alarm_name_get(u8 *p, u8 index)
{
    extern u8 alarm_name_get(u8 * p, u8 index);
    return alarm_name_get(p, index);
}

static void rcsp_rtc_update_time(RTC_TIME *p)
{
    extern void rtc_update_time_api(struct sys_time * time);
    struct sys_time time = {0};
    time.year = p->dYear;
    time.month = p->bMonth;
    time.day = p->bDay;
    time.hour = p->bHour;
    time.min = p->bMin;
    time.sec = p->bSec;
    rtc_update_time_api(&time);
}

static u8 mfunc_alarm_deal_data(PT_ALARM_APP p)
{
    extern u8 alarm_add(PT_ALARM p, u8 index);
    T_ALARM tmp_alarm 	 = {0};
    tmp_alarm.index 	 = p->index;
    tmp_alarm.sw         = p->sw;
    tmp_alarm.mode       = p->mode;
    tmp_alarm.time.hour  = p->bHour;
    tmp_alarm.time.min   = p->bMin;
    tmp_alarm.name_len   = p->name_len;
    return alarm_add(&tmp_alarm, p->index);
}

static void m_func_alarm_name_set(u8 *p, u8 index, u8 len)
{
    extern void alarm_name_set(u8 * p, u8 index, u8 len);
    alarm_name_set(p, index, len);
}

static void m_func_alarm_delete(u8 index)
{
    extern void alarm_delete(u8 index);
    alarm_delete(index);
}

static u8 rcsp_rtc_alarm_extra_data_set(u8 index, u8 *p, u8 len)
{
    u8 offset = 0;
    T_ALARM_APP_EXTRA_DATA data = {0};
    data.type = p[offset++];
    data.dev = p[offset++];
    data.clust = READ_BIG_U32(p + offset);
    offset += sizeof(data.clust);
    u8 data_len = p[offset++];
    data.ring_name_len = data_len > 32 ? 32 : data_len;
    memcpy(data.ring_name, p + offset, data.ring_name_len);
    offset += data.ring_name_len;
    printf("ring_type : %d, ring_dev : %d, ring_clust : %d, ring_name_len : %d\n", data.type, data.dev, data.clust, data.ring_name_len);
    syscfg_write(VM_ALARM_RING_NAME_0 + index, &data, sizeof(data));
    return offset;
}

static u8 rcsp_rtc_alarm_deal(void *priv, u8 *p, u8 len)
{
    u8 ret = E_SUCCESS;
    u8 op = 0;
    u8 nums = 0;
    u8 index = 0;
    u8 *pTmp = 0;
    u8 i = 0;
    u8 ring_info_offset = 0;

    T_ALARM_APP alarm_tab;

    if (len >= 3) {
        op = p[2];
        printf("op = %d\n", op);
    }
    if (len >= 4) {
        nums = p[3];
        printf("nums = %d\n", nums);
    }
    if (nums > M_MAX_ALARM_NUMS) {
        printf("nums is error\n");
        return E_FAILURE;
    }

    switch (op) {
    case E_ALARM_SET:
        printf("E_ALARM_SET\n");
        for (i = 0; i < nums; i++) {
            pTmp = &(p[4 + i * (6 + alarm_tab.name_len) + ring_info_offset]);
            alarm_tab.index = pTmp[0];
            alarm_tab.sw = pTmp[1];
            alarm_tab.mode = pTmp[2];
            alarm_tab.bHour = pTmp[3];
            alarm_tab.bMin = pTmp[4];
            alarm_tab.name_len = pTmp[5];

            printf("index : %d, sw : %d, mode : %d, hour : %d, min : %d, name_len : %d\n", pTmp[0], pTmp[1], pTmp[2], pTmp[3], pTmp[4], pTmp[5]);
            ret = mfunc_alarm_deal_data(&alarm_tab);
            if (E_SUCCESS == ret) {
                m_func_alarm_name_set(&(pTmp[6]), alarm_tab.index, alarm_tab.name_len);
            }

            if (rtc_func_structure_flag) {
                ring_info_offset += rcsp_rtc_alarm_extra_data_set(alarm_tab.index, &pTmp[6 + alarm_tab.name_len], len);
            }
        }
        if (rcsp_rtc_ex_timer) {
            sys_timer_del(rcsp_rtc_ex_timer);
            rcsp_rtc_ex_timer = 0;
        }
        if (rcsp_rtc_ex_timer1) {
            sys_timer_del(rcsp_rtc_ex_timer1);
            rcsp_rtc_ex_timer1 = 0;
        }
        break;
    case E_ALARM_DELETE:
        printf("E_ALARM_DELETE\n");
        for (i = 0; i < nums; i++) {
            index = p[4 + i];
            m_func_alarm_delete(index);
        }
        if (rcsp_rtc_ex_timer) {
            sys_timer_del(rcsp_rtc_ex_timer);
            rcsp_rtc_ex_timer = 0;
        }
        if (rcsp_rtc_ex_timer1) {
            sys_timer_del(rcsp_rtc_ex_timer1);
            rcsp_rtc_ex_timer1 = 0;
        }
        break;
    case E_ALARM_UNACTIVE:
        printf("E_ALARM_UNACTIVE\n");
        index_flag = -1;
        extern void alarm_stop(void);
        alarm_stop();
        if (rcsp_rtc_ex_timer) {
            sys_timer_del(rcsp_rtc_ex_timer);
            rcsp_rtc_ex_timer = 0;
        }
        if (rcsp_rtc_ex_timer1) {
            sys_timer_del(rcsp_rtc_ex_timer1);
            rcsp_rtc_ex_timer1 = 0;
        }
        rcsp_device_status_update(RTC_FUNCTION_MASK, BIT(RTC_INFO_ATTR_RTC_ALRAM_UNACTIVE));
        break;
    default:
        printf("alarm no action!\n");
        break;
    }
    return ret;
}

static u8 rcsp_rtc_play_dev_ring(PT_ALARM_APP_RING_AUDITION ring_param)
{
    u8 ret = (u8) - 1;
#if TCFG_APP_MUSIC_EN
    printf("neet to play the dev music, dev %s, clust %x\n", rcsp_browser_dev_remap(ring_param->ring_dev), ring_param->ring_clust);
    ret = general_play_by_sculst(rcsp_browser_dev_remap(ring_param->ring_dev), ring_param->ring_clust);
#endif /* #if TCFG_APP_MUSIC_EN */
    if (ret) {
        ring_param->ring_type = 0;
        ring_param->ring_clust = 0;
    }
    return ret;
}

static u8 rcsp_rtc_ring_audition_deal(PT_ALARM_APP_RING_AUDITION ring_param)
{
    u8 ret = 0;
    printf("ring stop");
    tone_player_stop();
#if TCFG_APP_MUSIC_EN
    general_player_stop(0);
#endif /* #if TCFG_APP_MUSIC_EN */
    if (1 == ring_param->ring_op) {
        printf("ringing\n");
        if (0 == ring_param->ring_type) {
#if TCFG_APP_MUSIC_EN
            general_player_stop(0);
#endif /* #if TCFG_APP_MUSIC_EN */
            play_tone_file(default_ringtone_table[ring_param->ring_clust]);
        } else if (1 == ring_param->ring_type) {
            tone_player_stop();
            rcsp_rtc_play_dev_ring(ring_param);
        }
    }
    return ret;
}

static u8 rcsp_rtc_ring_audition_prepare(void *priv, u8 *data, u16 len)
{
    u8 ret = 0;
    struct RcspModel *rcspModel = (struct RcspModel *)priv;
    g_ring_audition.ring_op = data[0];
    switch (g_ring_audition.ring_op) {
    case 0:
        // 回到原来的模式
        file_trans_idle_set(1);
        if ((u8) - 1 != g_ring_audition.prev_app_mode) {
            rcsp_msg_post(USER_MSG_RCSP_MODE_SWITCH, 2, (int)rcspModel, g_ring_audition.prev_app_mode);
            g_ring_audition.prev_app_mode = -1;
        } else {
            rcsp_rtc_ring_audition_deal(&g_ring_audition);
        }
        break;
    case 1:
        file_trans_idle_set(0);
        g_ring_audition.ring_type = data[1];
        g_ring_audition.ring_dev = data[2];
        g_ring_audition.ring_clust = READ_BIG_U32(data + 3);
        // 进入rtc模式
        if (RTC_FUNCTION != rcspModel->cur_app_mode) {
            g_ring_audition.prev_app_mode = rcspModel->cur_app_mode;
            // 切换rtc模式
            rcsp_msg_post(USER_MSG_RCSP_MODE_SWITCH, 2, (int)rcspModel, RTC_FUNCTION_MASK);
        } else {
            rcsp_rtc_ring_audition_deal(&g_ring_audition);
        }
        break;
    }
    return ret;
}

//设置固件rtc行为
bool rcsp_rtc_func_set(void *priv, u8 *data, u16 len)
{
    u8 ret = 0;
    u8 offset = 0;
    RTC_TIME time_info;
    while (offset < len) {
        u8 len_tmp = data[offset];
        u8 type = data[offset + 1];
        printf("rtc info:\n");
        put_buf(&data[offset], len_tmp + 1);

        switch (type) {
        case RTC_INFO_ATTR_RTC_TIME:
            printf("RTC_INFO_ATTR_RTC_TIME\n");
            memcpy((u8 *)&time_info, data + 2, sizeof(time_info));
            time_info.dYear = app_htons(time_info.dYear);
            rcsp_rtc_update_time(&time_info);
            break;
        case RTC_INFO_ATTR_RTC_ALRAM:
            printf("RTC_INFO_ATTR_RTC_ALRAM\n");
            put_buf(data, len);
            ret = rcsp_rtc_alarm_deal(priv, data, len);
            break;
        case RTC_INFO_ATTR_RTC_ALRAM_RING_AUDITION:
            printf("RTC_INFO_ATTR_RTC_ALRAM_RING_AUDITION\n");
            ret = rcsp_rtc_ring_audition_prepare(priv, data + offset + 2, len);
            break;
        }
        offset += len_tmp + 1;
    }
    return (E_SUCCESS == ret);
}

static bool rcsp_rtc_alarm_deal_ex(void *priv, u8 *data, u16 len)
{
    u8 *tmp_data = data;

    T_ALARM_APP_DATA_EX tmp = {0};
    tmp.len = tmp_data[0];
    tmp.index = tmp_data[1];
    tmp.count = tmp_data[2];
    tmp.interval = tmp_data[3];
    tmp.alarmTime = tmp_data[4];
    put_buf((u8 *)&tmp, sizeof(tmp));
    syscfg_write(VM_ALARM_EX0 + tmp.index, &tmp, sizeof(tmp));
    return 1;
}

bool rcsp_rtc_func_set_ex(void *priv, u8 *data, u16 len)
{
    printf("rtc_ex info:\n");
    put_buf(data, len);

    return rcsp_rtc_alarm_deal_ex(priv, data, len);
}

u16 rcsp_rtc_func_get_ex(void *priv, u8 *buf, u16 buf_size, u8 mask)
{
    u16 offset = 0;
    u8 index = 0;
    T_ALARM_APP_DATA_EX data = {0};
    data.len = 0x04;
    data.count |= 0x81;//可设置
    data.interval |= 0x85;
    data.alarmTime |= 0x85;
    u16 size = sizeof(data);
    printf("mask==%u", mask);
    do {
        if (mask & 0x01) {
            if (sizeof(data) != syscfg_read(VM_ALARM_EX0 + index, &data, size)) {
                printf("read VM_ALARM error\n");
            }
            data.index = index;
            put_buf((u8 *)&data, sizeof(data));
            memcpy(&buf[offset], (u8 *)&data, size);
            offset = offset + size;
        }
        mask = mask >> 1;
        index++;
    } while (index < 5);
    put_buf(buf, buf_size);

    return offset;
}

static u8 rcsp_rtc_alarm_extra_data_get(u8 *p, u8 index, u8 is_conversion)
{
    u8 offset = 0;
    T_ALARM_APP_EXTRA_DATA data = {0};
    if (sizeof(data) != syscfg_read(VM_ALARM_RING_NAME_0 + index, &data, sizeof(data))) {
        // 默认数据
        data.type = 0;
        data.dev = 0;
        data.clust = 0;
        memcpy(data.ring_name, default_ringtone_name_table[data.clust], strlen(default_ringtone_name_table[data.clust]) + 1);
        data.ring_name_len = strlen((const char *)data.ring_name) + 1;
    }
    p[offset++] = data.type;
    p[offset++] = data.dev;
    if (is_conversion) {
        WRITE_BIG_U32(p + offset, data.clust);
    } else {
        memcpy(p + offset, &data.clust, sizeof(data.clust));
    }
    offset += sizeof(data.clust);
    p[offset++] = data.ring_name_len;
    memcpy(p + offset, data.ring_name, data.ring_name_len);
    offset += data.ring_name_len;
    return offset;
}

//获取固件rtc信息
u32 rcsp_rtc_func_get(void *priv, u8 *buf, u16 buf_size, u32 mask)
{
    u16 offset = 0;
    if (mask & BIT(RTC_INFO_ATTR_RTC_TIME)) {
        printf("RTC_INFO_ATTR_RTC_TIME\n");
        RTC_TIME time_info = {
            .dYear = 2020,
            .bMonth = 5,
            .bDay = 15,
            .bHour = 19,
            .bMin = 55,
            .bSec = 40,
        };
        offset += add_one_attr(buf, buf_size, offset, RTC_INFO_ATTR_RTC_TIME, (u8 *)&time_info, sizeof(time_info));
    }

    if (mask & BIT(RTC_INFO_ATTR_RTC_ALRAM)) {
        printf("RTC_INFO_ATTR_RTC_ALRAM\n");
        u16 data_len = M_MAX_ALARM_NUMS * (sizeof(T_ALARM_APP) + M_MAX_ALARM_NAME_LEN + sizeof(T_ALARM_APP_EXTRA_DATA));
        u8 *alarm_data = zalloc(data_len);
        u8 total = 0;
        u8 index = 0;
        u8 name_len = 0;
        u8 *pTmp;
        u8 ret = 0;

        data_len = 0;
        pTmp = alarm_data;

        total = rcsp_rtc_get_alarm_total();
        printf("total %d alarm!\n", total);

        pTmp[0] = total;

        pTmp++;
        data_len++;

        for (index = 0; index < 5; index++) {
            ret = rcsp_rtc_get_alarm_info((PT_ALARM_APP)pTmp, index);
            printf("alarm_tab.sw get==%u&&&", ((PT_ALARM_APP)pTmp)->sw);
            if (0 == ret) {
                pTmp += sizeof(T_ALARM_APP);
                data_len += sizeof(T_ALARM_APP);

                name_len = m_func_alarm_name_get(pTmp, index);
                pTmp += name_len;
                data_len += name_len;

                if (rtc_func_structure_flag) {
                    name_len = rcsp_rtc_alarm_extra_data_get(pTmp, index, 1);
                    pTmp += name_len;
                    data_len += name_len;
                }

                printf("data_len = %d\n", data_len);
            }
        }

        put_buf(alarm_data, data_len);
        offset += add_one_attr(buf, buf_size, offset, RTC_INFO_ATTR_RTC_ALRAM, alarm_data, data_len);
        if (alarm_data) {
            free(alarm_data);
        }
    }

    if (mask & BIT(RTC_INFO_ATTR_RTC_ALRAM_ACTIVE)) {
        printf("RTC_INFO_ATTR_RTC_ALRAM_ACTIVE\n");
        u8 index_mask = 0;
        index_mask = m_func_alarm_get_active_index();
        printf("active alarm index : %d\n", index_mask);
        offset += add_one_attr(buf, buf_size, offset, RTC_INFO_ATTR_RTC_ALRAM_ACTIVE, (u8 *)&index_mask, sizeof(index_mask));

        /* extern void alarm_update_info_after_isr(void); */
        /* alarm_update_info_after_isr(); */
    }

    if (mask & BIT(RTC_INFO_ATTR_RTC_ALRAM_UNACTIVE)) {
        printf("RTC_INFO_ATTR_RTC_ALRAM_UNACTIVE\n");
        u8 index_mask = 0;
        index_mask = m_func_alarm_get_active_index();
        printf("active alarm index : %d\n", index_mask);
        offset += add_one_attr(buf, buf_size, offset, RTC_INFO_ATTR_RTC_ALRAM_UNACTIVE, (u8 *)&index_mask, sizeof(index_mask));
    }

    if (mask & BIT(RTC_INFO_ATTR_RTC_ALRAM_STRUCTURE)) {
        printf("RTC_INFO_ATTR_RTC_ALRAM_STRUCTURE\n");
        offset += add_one_attr(buf, buf_size, offset, RTC_INFO_ATTR_RTC_ALRAM_STRUCTURE, &rtc_func_structure_flag, sizeof(rtc_func_structure_flag));
    }

    if (mask & BIT(RTC_INFO_ATTR_RTC_ALRAM_DEFAULT_RING)) {
        printf("RTC_INFO_ATTR_RTC_ALRAM_DEFAULT_RING\n");
        u8 i;
        // total + index
        u8 ring_info_len = 1 + ALARM_IDEX_TONE_MAX_NUM;
        for (i = 0; i < ALARM_IDEX_TONE_MAX_NUM; i++) {
            // name_len + name_data
            ring_info_len += 1 + strlen(default_ringtone_name_table[i]) + 1;
        }

        u8 default_offset = 0;
        u8 ring_name_len = 0;
        u8 *default_ring = zalloc(ring_info_len);
        default_ring[default_offset++] = ALARM_IDEX_TONE_MAX_NUM;
        for (i = 0; i < ALARM_IDEX_TONE_MAX_NUM; i++) {
            ring_name_len = strlen(default_ringtone_name_table[i]) + 1;
            default_ring[default_offset++] = i;
            default_ring[default_offset++] = ring_name_len;
            if (ring_name_len) {
                memcpy(default_ring + default_offset, default_ringtone_name_table[i], ring_name_len);
            }
            default_offset += ring_name_len;
        }

        offset += add_one_attr(buf, buf_size, offset, RTC_INFO_ATTR_RTC_ALRAM_DEFAULT_RING, default_ring, ring_info_len);
        if (default_ring) {
            free(default_ring);
        }

    }

    if (mask & BIT(RTC_INFO_ATTR_RTC_ALARM_EX)) {
        printf("RTC_INFO_ATTR_RTC_ALARM_EX\n");
        u8 tmp[1] = {1};
        offset += add_one_attr(buf, buf_size, offset, RTC_INFO_ATTR_RTC_ALARM_EX, tmp, 1);
    }

    return offset;
}

//rtc消息处理
void rcsp_rtc_msg_deal(int msg)
{
    struct RcspModel *rcspModel = rcsp_handle_get();
    if (rcspModel == NULL) {
        return ;
    }

    switch (msg) {
    case (int)-1 :
        rtc_ringing_prev_mode = rcspModel->cur_app_mode;
        rcsp_device_status_update(RTC_FUNCTION_MASK, BIT(RTC_INFO_ATTR_RTC_ALRAM_ACTIVE));
        break;
    }
}

static void rtc_ring_stop_handle(void)
{
    struct RcspModel *rcspModel = rcsp_handle_get();
    if (rcspModel == NULL) {
        return ;
    }
    rcsp_device_status_update(RTC_FUNCTION_MASK, BIT(RTC_INFO_ATTR_RTC_ALRAM_STRUCTURE) | BIT(RTC_INFO_ATTR_RTC_ALRAM_UNACTIVE));
    rcsp_device_status_update(RTC_FUNCTION_MASK, BIT(RTC_INFO_ATTR_RTC_ALRAM));
    if ((u8) - 1 != rtc_ringing_prev_mode) {
#if RCSP_MODE == RCSP_MODE_SOUNDBOX
        extern void alarm_play_timer_del(void);
        alarm_play_timer_del();
        rcsp_msg_post(USER_MSG_RCSP_MODE_SWITCH, 2, (int)rcspModel, rtc_ringing_prev_mode);
#endif
        rtc_ringing_prev_mode = -1;
    }
}

u8 rtc_app_alarm_ring_play(u8 alarm_state);

void rcsp_rtc_ex_deal1(void *priv)
{
    rtc_app_alarm_ring_play(1);
}

void rcsp_rtc_ex_deal(void *priv)
{
    rtc_ringing_prev_mode = 8;
    rcsp_rtc_ex_timer1 = sys_timer_add(NULL, rcsp_rtc_ex_deal1, 500);
}

u8 rtc_get_active_index()
{
    u8 index = -1;
    u8 cur_active_index = alarm_get_active_index();
    for (int i = 0; i < M_MAX_ALARM_NUMS; i++) {
        if (cur_active_index & BIT(i)) {
            index = i;
            break;
        }
    }
    return index;
}

void rtc_sw_set(u8 sw, u8 index)
{
    T_ALARM alarm_param;
    int ret = alarm_get_info(&alarm_param, index);
    if (ret) {
        return;
    }
    if (alarm_param.mode == 0) {
        alarm_param.sw = sw;
        alarm_add(&alarm_param, index);
    }
}

void rtc_ring_sw_deal()
{
    if (index_flag != (u8) - 1) {
        if (rcsp_rtc_ex_timer1) {
            sys_timer_del(rcsp_rtc_ex_timer1);
            rcsp_rtc_ex_timer1 = 0;
        }
        if (rcsp_rtc_ex_timer) {
            sys_timer_del(rcsp_rtc_ex_timer);
            rcsp_rtc_ex_timer = 0;
        }
        flag = 0;
        count_flag = 0;
        rtc_sw_set(0, index_flag);
        index_flag = -1;
    }
}

static void ring_play_ex()
{
    T_ALARM_APP_DATA_EX data = {0};
    data.len = 0x04;
    data.count |= 0x80;//可设置
    data.interval |= 0x80;
    data.alarmTime |= 0x80;
    u16 size = sizeof(data);
    index_flag = rtc_get_active_index();
    if (sizeof(data) != syscfg_read(VM_ALARM_EX0 + index_flag, &data, size)) {
        printf("read alarm error\n");
    }
    put_buf((u8 *)&data, sizeof(data));
    if (count_flag == 0) {
        count = data.count & 0x0f;
        count_flag = 1;
    }

    u8 interval = data.interval & 0x1f;
    u8 alarmTime = data.alarmTime & 0x1f;
    flag++;
    if (flag == alarmTime * 3) { //闹铃结束
        flag = 0;
        count--;
        /* printf("count==================================================%d", count); */
        if (count) {
            rcsp_rtc_ex_timer = sys_timeout_add(NULL, rcsp_rtc_ex_deal, interval * 60 * 50);
        } else {
            count_flag = 0;
            rtc_sw_set(0, index_flag);
            index_flag = -1;
        }
        extern void alarm_stop(void);
        alarm_stop();
        if (rcsp_rtc_ex_timer1) {
            sys_timer_del(rcsp_rtc_ex_timer1);
            rcsp_rtc_ex_timer1 = 0;
        }
    }
}

u8 rtc_app_alarm_ring_play(u8 alarm_state)
{
    // 防止g_ring_audition成为临界资源，所以定义多一个局部变量
    static T_ALARM_APP_RING_AUDITION ringing_info = {0};
    u8 active_flag = m_func_alarm_get_active_index();
    u8 index;
    if (0 == active_flag && 0 == rtc_func_structure_flag) {
        return rtc_func_structure_flag;
    }

    if (0 == alarm_state) {
        file_trans_idle_set(1);
        ringing_info.prev_app_mode = 0;
        ringing_info.ring_op = 0;
        ringing_info.ring_timeout = 0;
        rcsp_rtc_ring_audition_deal(&ringing_info);
        if (index_flag != (u8) - 1) {
            rtc_sw_set(1, index_flag);
        }
        rtc_ring_stop_handle();
        return rtc_func_structure_flag;
    } else {
        if ((u32) - 1 == (--ringing_info.ring_timeout)) {
            ringing_info.ring_timeout = RCSP_ALARM_RING_MAX;
        } else if (0 == ringing_info.ring_timeout) {
#if RCSP_MODE == RCSP_MODE_SOUNDBOX
            ringing_info.ring_timeout = RCSP_ALARM_RING_MAX;
            ring_play_ex();
#else
            extern void alarm_stop(u8 reason);
            alarm_stop(1);
#endif
            return rtc_func_structure_flag;
        }
    }

    for (index = 0; index < 5; index++) {
        if (active_flag & BIT(index)) {
            break;
        }
    }

    if (index < 5) {
        if (0 == ringing_info.prev_app_mode) {
            // 响铃会进入始终模式，这个时全局变量prev_app_mode应该清除
            g_ring_audition.prev_app_mode = -1;
            // 暂停正在播放的提示音或设备音乐
            g_ring_audition.ring_op = 0;
            rcsp_rtc_ring_audition_deal(&g_ring_audition);

            T_ALARM_APP_EXTRA_DATA data = {0};
            u32 data_len = 0;

            rcsp_rtc_alarm_extra_data_get((u8 *)&data, index, 0);

            ringing_info.prev_app_mode = -1;
            ringing_info.ring_op = 1;
            ringing_info.ring_type = data.type;
            ringing_info.ring_dev = data.dev;
            ringing_info.ring_clust = data.clust;
        }

        if (get_rcsp_connect_status()) {
            rcsp_device_status_update(RTC_FUNCTION_MASK, BIT(RTC_INFO_ATTR_RTC_ALRAM_ACTIVE));
        }

#if TCFG_APP_MUSIC_EN
        file_trans_idle_set(0);
        if (ringing_info.ring_type) {
            if (!music_file_get_player_status(get_music_file_player())) {
                // 播放设备音乐
                printf("ringing............................\n");
                rcsp_rtc_play_dev_ring(&ringing_info);
            }
        } else
#endif /* #if TCFG_APP_MUSIC_EN */
        {
            play_tone_file(default_ringtone_table[ringing_info.ring_clust]);
        }
    }
    return rtc_func_structure_flag;
}

u8 rcsp_rtc_ring_tone(void)
{
#if TCFG_APP_MUSIC_EN
    general_player_init((struct __scan_callback *)&scan_cb);
#endif /* #if TCFG_APP_MUSIC_EN */
    if ((u8) - 1 != g_ring_audition.prev_app_mode) {
        rcsp_rtc_ring_audition_deal(&g_ring_audition);
    } else if ((u8) - 1 == rtc_ringing_prev_mode) {
    }
    return false;
}

void rcsp_rtc_mode_exit(void)
{
#if TCFG_APP_MUSIC_EN
    general_player_exit();
#endif /* #if TCFG_APP_MUSIC_EN */
    struct RcspModel *rcspModel = rcsp_handle_get();
    if (rcspModel == NULL) {
        return ;
    }
    file_trans_idle_set(1);
    if ((u8) - 1 != rtc_ringing_prev_mode) {
        rtc_ringing_prev_mode = rcspModel->cur_app_mode;
        rtc_ring_stop_handle();
    }
}

#endif
