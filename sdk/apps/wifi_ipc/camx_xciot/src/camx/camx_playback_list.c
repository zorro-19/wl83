#define _STDIO_H_
#include "xciot_api.h"
#include "xciot_cmd_ipc.h"

#include "app_config.h"
#include "json_c/json.h"
#include "generic/list.h"
#include "simple_mov_unpkg.h"
#include "time.h"
#include "system/init.h"
#include "os/os_api.h"

#include "bplus.h"

#if defined CONFIG_XCIOT_ENABLE
#define CONFIG_PLAYBACK_LIST_ENABLE  1


typedef struct cloud_playback_list_info {
    /* struct list_head entry; */
    u32 name_num;//文件名 ,为了省内存，文件名字固定
    int32_t day;//用于检索文件名
    uint32_t start_time;
    char      length;
//    uint64_t file_id;
//    uint64_t thum_fig;

} CLOUD_PLAYBACK_LIST_INFO;

/* static CLOUD_PLAYBACK_LIST_INFO  cloud_playback_list_info[1024]; */
/* static LIST_HEAD(cloud_playback_file_list_head); */
static OS_MUTEX sd_status_to_app_mutex;
extern OS_MUTEX get_cloud_playback_list_mutex();
extern uint64_t covBeijing2UnixTimeStp(struct tm *p);
extern bp_db_t get_db_element(int index);


static int _History_days_range_cb(void *__rsp, const bp_key_t *key, const bp_value_t *value)
{
    int i = 0;
    ipc_HistoryDays_Resp *rsp = (ipc_HistoryDays_Resp *)__rsp;

    int j = sizeof(rsp->days) / sizeof(int32_t);
    /* printf("key:%s \n",key->value); */
    CLOUD_PLAYBACK_LIST_INFO *p  = (CLOUD_PLAYBACK_LIST_INFO *) value->value;

    for (i = 0; i <= rsp->days_count; i++) {
        if (!rsp->days[i] || rsp->days[i] == (p->day % 100)) {
            break;
        }
    }
    if (!rsp->days[i] && rsp->days_count < (j - 1)) {
        rsp->days[i] = (p->day % 100);
        rsp->days_count++;
        rsp->total++;
    }
    return 0;

}

int cloud_playback_list_get_days(void *__req, void *__rsp)
{
    ipc_HistoryDays_Req *req = (ipc_HistoryDays_Req *)__req;
    ipc_HistoryDays_Resp *rsp = (ipc_HistoryDays_Resp *)__rsp;
    CLOUD_PLAYBACK_LIST_INFO p = {0};
    OS_MUTEX cloud_playback_list_mutex = get_cloud_playback_list_mutex();
    bp_db_t db = get_db_element(0);//todo
    int i;
    int j = sizeof(rsp->days) / sizeof(int32_t);
    rsp->days_count = 0;

    /* u32  date =   req->year * 100 + (req->month / 10) * 10 + (req->month % 10); */
    for (int i = 0; i < j; i++) {
        rsp->days[i] = 0;
    }
    os_mutex_pend(&cloud_playback_list_mutex, 0);

    struct tm t = {0};
    t.tm_year = req->year;
    t.tm_mon = req->month;

    u32 start_time = covBeijing2UnixTimeStp(&t);

    u32 end_time = start_time + 2678400;
    printf("start_time:%d   end_time:%d\n", start_time, end_time);
    char start_time_str[20] = {0};
    char end_time_str[20]    = {0};
    sprintf(start_time_str, "%d", start_time);
    sprintf(end_time_str, "%d", end_time);
    int matched = 0;
    bp_get_ranges(&db, start_time_str, end_time_str, _History_days_range_cb, rsp);

    os_mutex_post(&cloud_playback_list_mutex);

    return 0;
}



static int _Cloud_playback_file_cb(void *__p, const bp_key_t *key, const bp_value_t *value)
{
    uint64_t *utc_time = (uint64_t *)__p;
    /* printf("key:%s utc:%ld\n", key->value, *utc_time); */
    CLOUD_PLAYBACK_LIST_INFO *info  = (CLOUD_PLAYBACK_LIST_INFO *) value->value;
    /* printf("start_time:%ld length:%d utc:%ld\n", info->start_time, info->length, *utc_time); */
    if (info->start_time + info->length >= *utc_time && info->start_time <= *utc_time) {
        *utc_time = info->name_num;
    }
    return 0;

}


int cloud_playback_file(uint64_t stramptime)
{
    OS_MUTEX cloud_playback_list_mutex = get_cloud_playback_list_mutex();
    bp_db_t db = get_db_element(0);//todo
#define REC_TIME   (60)   // db_select("cyc")
    char start_time_str[20] = {0};
    char end_time_str[20]    = {0};
    uint64_t arg = stramptime;
    sprintf(start_time_str, "%ld", stramptime - REC_TIME);
    sprintf(end_time_str, "%ld", stramptime);
    os_mutex_pend(&cloud_playback_list_mutex, 0);
    bp_get_ranges(&db, start_time_str, end_time_str, _Cloud_playback_file_cb, &arg);
    os_mutex_post(&cloud_playback_list_mutex);
    return arg;
}

static u8 first_get = 0;
static int _Cloud_playback_file_next_cb(void *__p, const bp_key_t *key, const bp_value_t *value)
{
    uint64_t *arg = (uint64_t *)__p;
    CLOUD_PLAYBACK_LIST_INFO *info  = (CLOUD_PLAYBACK_LIST_INFO *) value->value;
    /* printf("start_time:%ld length:%d name_num:%d\n", info->start_time, info->length, info->name_num); */
    if (first_get) {
        first_get = 0;
        *arg = info->name_num;
    }
    return 0;


}


int cloud_playback_file_next(uint64_t start_time, uint64_t end_time)
{
    OS_MUTEX cloud_playback_list_mutex = get_cloud_playback_list_mutex();
    bp_db_t db = get_db_element(0);//todo
    char start_time_str[20] = {0};
    char end_time_str[20]    = {0};
    int arg = -1;
    first_get = 1;
    sprintf(start_time_str, "%ld", start_time);
    sprintf(end_time_str, "%ld", end_time);
    os_mutex_pend(&cloud_playback_list_mutex, 0);
    bp_get_ranges(&db, start_time_str, end_time_str, _Cloud_playback_file_next_cb, &arg);
    os_mutex_post(&cloud_playback_list_mutex);
    return arg;
}





struct _Playback_lists_range_info {
    int page_offset;
    void *req;
    void *rsp;
    uint64_t start_time;
    uint64_t end_time;

};

#if 1
static int _Playback_lists_range_cb(void *__p, const bp_key_t *key, const bp_value_t *value)
{
    struct _Playback_lists_range_info *p_info = (struct _Playback_lists_range_info *)__p;
    ipc_HistoryDayList_Req *req = (ipc_HistoryDayList_Req *)p_info->req;
    ipc_HistoryDayList_Resp *rsp = (ipc_HistoryDayList_Resp *)p_info->rsp;
    CLOUD_PLAYBACK_LIST_INFO *info = (CLOUD_PLAYBACK_LIST_INFO *)value->value;

    if (atol(key->value) > p_info->end_time) {
        return 0;
    }
    if (req->rtype) {
        rsp->historys[p_info->page_offset].start_time = info->start_time;
        rsp->historys[p_info->page_offset].length = info->length;
        rsp->historys[p_info->page_offset].file_id = info->name_num;
        rsp->historys[p_info->page_offset].thum_fid = info->name_num;

        rsp->historys[p_info->page_offset].history_type = 255; //视频类型
        p_info->page_offset++;

        if (p_info->page_offset == 50) {
            return -1;
        }

    } else {
        rsp->history_range[p_info->page_offset].start_time = info->start_time;
        rsp->history_range[p_info->page_offset].length = info->length;
        rsp->history_range[p_info->page_offset].history_type = 255; //视频类型
        p_info->page_offset++;

        /* printf("\n  p_info->page_offset = %d \n",  p_info->page_offset); */
        if (p_info->page_offset == 50) {
            return -1;
        }
    }
    return 0;
}
#else

static int _Playback_lists_range_cb(void *__p, const bp_key_t *key, const bp_value_t *value)
{
    struct _Playback_lists_range_info *p_info = (struct _Playback_lists_range_info *)__p;
    ipc_HistoryDayList_Req *req = (ipc_HistoryDayList_Req *)p_info->req;
    ipc_HistoryDayList_Resp *rsp = (ipc_HistoryDayList_Resp *)p_info->rsp;
    CLOUD_PLAYBACK_LIST_INFO *info = (CLOUD_PLAYBACK_LIST_INFO *)value->value;
    int ret = 0;
    int page_offset = p_info->page_offset;
    int page_size = req->page_size;
    int page = req->page;
    int total = rsp->total;
    if (atol(key->value) > p_info->end_time) {
        return 0;
    }
    if (req->rtype) {
        if (total == page_offset && page_offset < ((page - 1) * page_size + page_size)) {
            /* printf("page_offset:%d total:%d file_name:%d start_time:%ld\n", page_offset, total,info->name_num,info->start_time); */

            int history_index = page_offset - ((page - 1) * page_size);
            rsp->historys[history_index].start_time = info->start_time;
            rsp->historys[history_index].length = info->length;
            rsp->historys[history_index].file_id = info->name_num;
            rsp->historys[history_index].thum_fid = info->name_num;
            rsp->historys[history_index].history_type = 255; //视频类型
            page_offset++;

            /* printf("history_index:%d  start:%d file_id:%d\n" */
            /* ,history_index */
            /* ,rsp->historys[history_index].start_time */
            /* ,rsp->historys[history_index].file_id); */

        }
        total++;
        rsp->historys_count = page_offset - ((page - 1) * page_size);
    } else {
        /* printf("page_offset:%d total:%d\n", page_offset, total); */
        /* if (total >= (page - 1) * page_size && total < ((page - 1) * page_size + page_size)) { */
        /* int history_index = page_offset - ((page - 1) * page_size); */
        /* printf("page_offset:%d  history_index:%d\n", page_offset, history_index); */
        rsp->history_range[page_offset].start_time = info->start_time;
        rsp->history_range[history_index].length = info->length;
        rsp->history_range[history_index].history_type = 255; //视频类型
        page_offset++;
        /* } */
        if () {
            rsp->total = xxx
                         return -1;
        }
        total++;
        rsp->history_range_count = page_offset - ((page - 1) * page_size);
    }

    p_info->page_offset = page_offset;
    rsp->total = total;
    return 0;
}

#endif


int cloud_playback_list_get(void *__req, void *__rsp)
{
    OS_MUTEX cloud_playback_list_mutex = get_cloud_playback_list_mutex();
    bp_db_t db = get_db_element(0);//todo

    ipc_HistoryDayList_Req *req = (ipc_HistoryDayList_Req *)__req;
    ipc_HistoryDayList_Resp *rsp = (ipc_HistoryDayList_Resp *)__rsp;
    CLOUD_PLAYBACK_LIST_INFO p = {0};

    int i = 0;
    int j = 0;

    struct tm t = {0};
    char start_time_str[20] = {0};
    char end_time_str[20]    = {0};

    /* int page_offset = (req->page - 1) * req->page_size; */

    if (!storage_device_ready()) {
        return -1;
    }


    if (!get_db_status()) {
        return 0;
    }

    struct _Playback_lists_range_info info = {0};
    /* info.page_offset = page_offset; */
    info.req         = __req;
    info.rsp         = __rsp;

#if 0
    printf("day:%d  page:%d  page_size:%d order:%d  start_time:%d history_type_count:%d type:%d\n"
           , req->day
           , req->page
           , req->page_size
           , req->order
           , req->start_time
           , req->history_type_count
           , req->rtype
          );
#endif


    if (!req->day) {

        t.tm_year = 2022;
        t.tm_mon = 7;
        t.tm_mday = 1;
        u64 start_time = covBeijing2UnixTimeStp(&t);
        t.tm_year = 2036;
        t.tm_mon = 7;
        t.tm_mday = 1;
        u64 end_time = covBeijing2UnixTimeStp(&t);
        info.start_time = start_time;
        info.end_time = end_time;

        sprintf(start_time_str, "%ld", start_time);
        sprintf(end_time_str, "%ld", end_time);

    } else {
        t.tm_year = (req->day / 10000);
        t.tm_mon = (req->day % 10000) / 100;
        t.tm_mday = (req->day) % 100;
        /* printf("day:%d-%d-%d\n", t.tm_year, t.tm_mon, t.tm_mday); */
        u64 start_time = covBeijing2UnixTimeStp(&t);
        u64 end_time = start_time + (24 * 60 * 60 - 1);
        info.start_time = start_time;
        info.end_time = end_time;
        sprintf(start_time_str, "%ld", start_time);
        sprintf(end_time_str, "%ld", end_time);
    }


    if (req->start_time) { //这个参数app设置了可以减小搜索范围
        sprintf(start_time_str, "%ld", req->start_time);
    }


    /* printf("start_time_str:%s  end_time_str:%s\n", start_time_str, end_time_str); */
    os_mutex_pend(&cloud_playback_list_mutex, 0);
    bp_get_ranges(&db, start_time_str, end_time_str, _Playback_lists_range_cb, &info);

    if (req->rtype) {
        rsp->total = rsp->historys_count = info.page_offset;

    } else {
        rsp->total = rsp->history_range_count = info.page_offset;
    }

    os_mutex_post(&cloud_playback_list_mutex);
    /* printf("\n  rsp->total = %d \n",  rsp->total); */
    /* printf("\n rsp->history_count = %d \n",  rsp->historys_count); */
    /* printf("\n rsp->history_range_count = %d \n",  rsp->history_range_count); */
    return 0;
}

int cloud_playback_list_remove(void *__req, void *__rsp)
{
#if 1

    OS_MUTEX cloud_playback_list_mutex = get_cloud_playback_list_mutex();
    bp_db_t db = get_db_element(0);//todo
    ipc_HistoryDel_Req *req = (ipc_HistoryDel_Req *)__req;
    ipc_HistoryDel_Resp *rsp = (ipc_HistoryDel_Resp *)__rsp;
    CLOUD_PLAYBACK_LIST_INFO info = {0};
    uint64_t file_id = 0;
    char name[128];
    struct vfs_attr attr;
    int i;
    for (i = 0; i < req->file_id_count ; i++) {
#if NAME_FILE_BY_DATE
        printf("\nreq->file_id =%llu \n", req->file_id[i]);
        char time_str[64] = {0};
        u8 dir_len = 0;
        struct tm timeinfo = {0};
        /* time_t timestamp = file_id + 28800; */
        time_t timestamp = req->file_id[i];
        localtime_r(&timestamp, &timeinfo);
        strcpy(time_str, CONFIG_REC_PATH_0);
        dir_len = strlen(time_str);
        strftime(time_str + dir_len, sizeof(time_str) - dir_len, "VID_%Y%m%d_%H%M%S.AVI", &timeinfo);
        log_i("recorder file name : %s\n", time_str);

        memcpy(name, time_str, sizeof(time_str));


        printf("\nname = %s \n", name);

        char path_file[128];
        int len;

        len = long_file_name_encode(name, (u8 *)path_file, sizeof(path_file));
        memcpy(name, path_file, len);

#else
        snprintf(name, sizeof(name), "%sVID_%04d.AVI", CONFIG_REC_PATH_0, req->file_id[i]);
        printf("\nname = %s \n", name);
#endif

        void *fd = fopen(name, "r");
        if (!fd) {
            printf("fopen fail %s\n", name);
            continue;
        }

        fget_attrs(fd, &attr);
        struct tm p;
        p.tm_year = attr.crt_time.year;
        p.tm_mday  = attr.crt_time.day;
        p.tm_mon = attr.crt_time.month;
        p.tm_hour   = attr.crt_time.hour;
        p.tm_min  = attr.crt_time.min;
        p.tm_sec  = attr.crt_time.sec;


        u32 start_time = covBeijing2UnixTimeStp(&p);

        char str[20] = {0};
        snprintf(str, 20, "%d", start_time);

        os_mutex_pend(&cloud_playback_list_mutex, 0);
        bp_removes(&db, str);

        os_mutex_post(&cloud_playback_list_mutex);

        if (fd) {
            fdelete(fd);
        }



    }
#endif
    return 0;
}










#endif
/* late_initcall(cloud_playback_list_init); */
