#include "system/includes.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "http/http_cli.h"
#include "baby_monitor.h"
#include "sock_api/sock_api.h"
#include "rt_stream_pkg.h"
#include "fs/fs.h"

#define HTTP_PORT               8080    //HTTP解析vs_list.txt端口
#define FILE_THUMB_PORT         2226    //缩略图数据端口
#define CTP_RECV_BUF_MAX_LEN    200 * 1024 //接收缓存,用于接收CTP包

static u32 task_name_cnt;
struct jpeg_http_info {
    char *file_name;
    u8 *buf;
    int *buf_len;
    int pid;
    u32 ip_addr;
};

struct avi_thumb_ctp_info {
    u8 *buf;
    int *buf_len;
};

static const char *fs_get_ext(const char *fn)
{
    size_t i;
    for (i = strlen(fn); i > 0; i--) {
        if (fn[i] == '.') {
            return &fn[i + 1];
        } else if (fn[i] == '/' || fn[i] == '\\') {
            return ""; /*No extension if a '\' or '/' found*/
        }
    }

    return ""; /*Empty string if no '.' in the file name.*/
}
static int check_fourcc(u8 *buf, const char *fourcc)
{
    return memcmp(buf, fourcc, 4) == 0;
}

static int read_fourcc_and_size(FILE *fd, u8 *fourcc, u32 *size)
{
    if (fread(fourcc, 4, 1, fd) != 4) {
        return -1;
    }
    if (fread(size, 4, 1, fd) != 4) {
        return -1;
    }
    return 0;
}
//获取AVI文件的第一帧
static u8 *get_avi_first_frame(FILE *fd, u32 *jpeg_size)
{
    static int read_times = 0;
    char fourcc[4];
    u32 size;

    fseek(fd, 0, SEEK_SET);

    if (read_fourcc_and_size(fd, fourcc, &size) != 0  || !check_fourcc(fourcc, "RIFF")) {
        printf("invalid RIFF header");
        return NULL;
    }
    if (read_fourcc_and_size(fd, fourcc, &size) != 0  || !check_fourcc(fourcc, "AVI ")) {
        printf("invalid AVI header");
        return NULL;
    }


    while (read_fourcc_and_size(fd, fourcc, &size) == 0) {
        if (check_fourcc(fourcc, "LIST")) {
            char list_type[4];
            if (fread(list_type, 1, 4, fd) != 4) {
                printf("invalid LIST type\n");
                return NULL;
            }
            if (check_fourcc(list_type, "movi")) {
                break;
            } else {
                fseek(fd, size - 4, SEEK_CUR);
            }
        } else {
            fseek(fd, size, SEEK_CUR);
        }
    }

    while (read_fourcc_and_size(fd, fourcc, &size) == 0) {
        if (read_times++ > 4) {
            //避免读太久,直接退出
            read_times = 0;
            break;
        }

        if (check_fourcc(fourcc, "00dc")) {
            read_times = 0;
            *jpeg_size = size;
            u8 *jpeg_buf = malloc(size);
            if (!jpeg_buf) {
                printf("jpeg_buf malloc fail\n");
                return NULL;
            }
            if (fread(jpeg_buf, size, 1, fd) != size) {
                printf("jpeg fread err\n");
                free(jpeg_buf);
                return NULL;
            }
            return jpeg_buf;
        } else {
            //跳过当前块
            fseek(fd, size, SEEK_CUR);
        }

    }
    printf("not found jpeg frame\n");
    return NULL;
}

int bbm_clean_file_list(void *priv)
{
    struct bbm_client_hdl *bbm_hdl = priv;
    int i;

    if (bbm_hdl->file_name_list) {
        for (i = 0; i < bbm_hdl->file_total_num; i++) {
            if (bbm_hdl->file_name_list[i]) {
                free(bbm_hdl->file_name_list[i]);
                bbm_hdl->file_name_list[i] = NULL;
            }
        }
        free(bbm_hdl->file_name_list);
        bbm_hdl->file_name_list = NULL;
        bbm_hdl->file_total_num = 0;
    }

    return 0;
}



static int http_get_mothed(const char *url, int (*cb)(char *, void *), void *priv, int body_buf_size)
{
    int error = 0;
    http_body_obj http_body_buf;
    httpcli_ctx ctx;
    printf("profile_get_url->%s\n", url);
    memset(&http_body_buf, 0x0, sizeof(http_body_obj));
    memset(&ctx, 0x0, sizeof(httpcli_ctx));

    http_body_buf.recv_len = 0;
    http_body_buf.buf_len = body_buf_size;
    http_body_buf.buf_count = 1;
    http_body_buf.p = (char *) malloc(http_body_buf.buf_len * sizeof(char));

    ctx.url = url;
    ctx.priv = &http_body_buf;
    ctx.connection = "close";
    ctx.timeout_millsec = 1000;
    error = httpcli_get(&ctx);
    if (error == HERROR_OK) {
        error = cb(&http_body_buf, priv);
    } else {
        printf("http get err :%d \n", error);
        error = -1;
    }
    //关闭连接
    httpcli_close(&ctx);
    if (http_body_buf.p) {
        free(http_body_buf.p);
    }
    return error;
}

static int get_file_name_cb(http_body_obj *http_body_buf, void *priv)
{
    int i;
    json_object *new_obj;
    json_object *new_obj2;
    const char *json_str;
    char *buf = http_body_buf->p;
    json_str = strstr(buf, "{\"");
    struct bbm_client_hdl *bbm_hdl = priv;

    if (!json_str) {
        printf("json buf err\n");
        return -1;
    }
    new_obj = json_tokener_parse(json_str);
    if (!new_obj) {
        printf("json_tokener_parse err\n");
        return -1;
    }

    json_object *file_list_array = json_object_object_get(new_obj, "file_list");
    if (file_list_array == NULL) {
        printf("file_list not found in JSON\n");
        json_object_put(new_obj);
        return -1;
    }

    int array_length = json_object_array_length(file_list_array);
    bbm_hdl->file_total_num = array_length;

    int list_size = bbm_hdl->file_total_num * sizeof(char *);
    bbm_hdl->file_name_list = (char **)malloc(list_size);
    if (!bbm_hdl->file_name_list) {
        printf("file_name_list malloc err \n");
        return -1;
    }
    memset(bbm_hdl->file_name_list, 0x00, list_size);

    for (i = 0; i < array_length; i++) {
        new_obj2 = json_object_array_get_idx(file_list_array, i);
        if (new_obj2 == NULL) {
            break;
        }

        const char *file_name = json_object_get_string(json_object_object_get(new_obj2, "f"));
        if (file_name == NULL) {
            printf("No 'f' field in file at index %d\n", i);
            continue;  // Skip this entry if no file name is found
        }

        bbm_hdl->file_name_list[i] = (char *)malloc(strlen(file_name) + 1);
        if (bbm_hdl->file_name_list[i] == NULL) {
            printf("malloc failed for file_list[%d]\n", i);
            json_object_put(new_obj);
            goto err;
        }
        strcpy(bbm_hdl->file_name_list[i], file_name);
    }

    json_object_put(new_obj);

    printf("total file num :%d \n", bbm_hdl->file_total_num);

    return 0;

err:
    bbm_clean_file_list(priv);
    return -1;
}

static void ctp_get_file_task(void *priv)
{
    int ret;
    char url[100];
    u8 timeout_cnt = 0;

    struct bbm_client_hdl *bbm_hdl = priv;
    struct sockaddr_in *sockaddr = ctp_cli_get_hdl_addr(bbm_hdl->ctp_cli_hdl);
    u32 ip_addr = sockaddr->sin_addr.s_addr;

    timeout_cnt = 0;

    bbm_clean_file_list(priv);

    while (1) {

        if (bbm_hdl->ctp_get_file_task_exit) {
            goto exit;
        }

        sprintf(url, "http://%s:%d/%s", inet_ntoa(ip_addr), HTTP_PORT, bbm_hdl->vf_list);
        ret = http_get_mothed(url, get_file_name_cb, priv, 10 * 1024);
        if (ret) {
            printf("http get mothed err\n");
            timeout_cnt++;
            if (timeout_cnt > 5) {
                printf("timeout exit !\n");
                goto exit;
            }
        } else {
            printf("http get mothed success\n");
            goto exit;
        }
    }
exit:
    printf("ctp_get_file_task exit\n");
}


static void recv_ctp_file_thumb(void *sockfd, void *priv, struct avi_thumb_ctp_info *avi_thumb_ctp)
{
    int recv_len = 0;
    int file_cnt = 0;
    int buf_len = 0;
    int recv_timeout_cnt = 0;

    struct bbm_client_hdl *bbm_hdl = priv;

    // 网络包接收缓存
    u8 *recv_buf = malloc(CTP_RECV_BUF_MAX_LEN);
    if (!recv_buf) {
        printf("ctp recv malloc recv buff err \n");
        goto exit;
    }

    sock_set_recv_timeout(sockfd, 200);

    while (1) {
        if (bbm_hdl->ctp_file_thumb_task_exit) {
            goto exit;
        }

        if (recv_timeout_cnt > 10) {
            goto exit;
        }

        recv_len = sock_recvfrom(sockfd, recv_buf + buf_len, CTP_RECV_BUF_MAX_LEN - buf_len, 0, NULL, NULL);
        if (recv_len <= 0) {
            printf("thumb packet recv err \n");
            recv_timeout_cnt++;
            continue;
        }
        recv_timeout_cnt = 0;
        buf_len += recv_len;

        while (buf_len >= sizeof(struct frm_head)) {
            struct frm_head *frame_head = (struct frm_head *)recv_buf;
            // 检查是否有完整的帧
            int frame_size = sizeof(struct frm_head) + frame_head->frm_sz;
            if (buf_len < frame_size) {
                break; // 不完整帧，等待更多数据
            }
            // 处理帧数据
            char *frame_data = recv_buf + sizeof(struct frm_head);

            switch (frame_head->type) {
            case MEDIA_INFO_TYPE:
                struct media_info *media = (struct media_info *)frame_data;
                printf("media info w:%d h:%d audio_rate:%d dur_time:%d \n"
                       , media->length, media->height, media->audio_rate, media->dur_time);
                break;
            case DATE_TIME_TYPE:
                break;
            case PREVIEW_TYPE:
                printf("recv thumb cnt:%d \n", file_cnt);
                if (avi_thumb_ctp[file_cnt].buf) {
                    memcpy(avi_thumb_ctp[file_cnt].buf, frame_data, frame_head->frm_sz);
                    int *buf_len = avi_thumb_ctp[file_cnt].buf_len;
                    *buf_len = frame_head->frm_sz;
                }
                file_cnt++;
                break;
            case PLAY_OVER_TYPE | LAST_FREG_MAKER:
                printf("recv end type \n");
                goto exit;
            default:
                printf("default frame type :%d  \n", frame_head->type);
                goto exit;
            }
            // 移动缓冲区内容，移除已处理的帧
            memmove(recv_buf, recv_buf + frame_size, buf_len - frame_size);
            buf_len -= frame_size;
        }
    }

exit:

    if (recv_buf) {
        free(recv_buf);
    }
    printf("recv ctp file thumb exit \n");

}

static int get_jpeg_cb(http_body_obj *http_body_buf, void *priv)
{
    u8 *in_buf = http_body_buf->p;
    u32 data_len = http_body_buf->recv_len;
    struct jpeg_http_info *jpeg_http = priv;
    u8 *out_buf = jpeg_http->buf;
    int *out_buf_len = jpeg_http->buf_len;
    int i;
    int start_idx = -1, end_idx = -1;

    for (i = 0; i < data_len - 1; i++) {
        if (((unsigned char)in_buf[i] == 0xFF) && ((unsigned char)in_buf[i + 1] == 0xD8)) {
            start_idx = i;
            break;
        }
    }
    if (start_idx < 0) {
        return -1;
    }

    for (i = start_idx; i < data_len - 1; i++) {
        if (((unsigned char)in_buf[i] == 0xFF) && ((unsigned char)in_buf[i + 1] == 0xD9)) {
            end_idx = i + 2;
            break;
        }
    }
    if (end_idx < 0) {
        return -1;
    }

    int jpeg_len = end_idx - start_idx;
    *out_buf_len = jpeg_len;
    memcpy(out_buf, in_buf + start_idx, jpeg_len);

    return 0;
}


static void ctp_get_jpeg_task(void *priv)
{
    char url[100];
    char ip_str[16];
    struct jpeg_http_info *jpeg_http = priv;
    int retry_cnt = 1;
    int ret;

    u8 *bytes = (u8 *)&jpeg_http->ip_addr;
    sprintf(ip_str, "%u.%u.%u.%u", bytes[0], bytes[1], bytes[2], bytes[3]);

    sprintf(url, "http://%s:%d/%s", ip_str, HTTP_PORT, jpeg_http->file_name);

    do {
        ret = http_get_mothed(url, get_jpeg_cb, jpeg_http, 100 * 1024);
    } while (ret && retry_cnt--);
}

static void ctp_file_thumb_task(void *priv)
{
    int ret = 0;
    int i;
    int msg[8];
    struct net_ctp_thumb *thumb_data;
    struct sockaddr_in dest;
    struct bbm_client_hdl *bbm_hdl = priv;
    void *ctp_file_thumb_sockfd;

    struct sockaddr_in *sockaddr = ctp_cli_get_hdl_addr(bbm_hdl->ctp_cli_hdl);
    u32 ip_addr = sockaddr->sin_addr.s_addr;

    char topic_1[] = "MULTI_COVER_FIGURE";
    char content_1[512];
    char temp_buf[128];

    while (1) {
        ret = os_task_pend("taskq", msg, ARRAY_SIZE(msg));
        switch (ret) {
        case OS_TASKQ:
            switch (msg[0]) {
            case Q_MSG:
                thumb_data = (struct net_ctp_thumb *)msg[1];
                break;
            case Q_USER:
                //exit
                goto exit;
            }
            break;
        default:
            break;
        }

        memset(content_1, 0x00, sizeof(content_1));
        strcat(content_1, "{\"op\":\"PUT\",\"param\":{");
        int avi_index = 0;
        int jpeg_index = 0;

        struct jpeg_http_info       jpeg_http[6];               //.jpeg
        struct avi_thumb_ctp_info   avi_thumb_ctp[6];               //.avi thumb(jpeg)
        memset(jpeg_http, 0x00, sizeof(jpeg_http));
        memset(avi_thumb_ctp, 0x00, sizeof(avi_thumb_ctp));

        for (i = 0; i <  thumb_data->file_num; i++) {
            char *file_name = bbm_hdl->file_name_list[thumb_data->start_index + i];
            char *ext = fs_get_ext(file_name);
            if (strcmp(ext, "jpg") == 0 || strcmp(ext, "JPG") == 0) {
                //JPG
                char task_name[32];
                sprintf(task_name, "get_jpeg_task%d", jpeg_index);
                jpeg_http[jpeg_index].file_name = file_name;
                jpeg_http[jpeg_index].buf = thumb_data->file_buf_list[i];
                jpeg_http[jpeg_index].buf_len  = &thumb_data->file_buf_len_list[i];
                jpeg_http[jpeg_index].ip_addr = ip_addr;
                thread_fork(task_name, 12, 2048, 2048
                            , &jpeg_http[jpeg_index].pid, ctp_get_jpeg_task, &jpeg_http[jpeg_index]);
                jpeg_index++;
            } else {
                //AVI
                avi_thumb_ctp[avi_index].buf = thumb_data->file_buf_list[i];
                avi_thumb_ctp[avi_index].buf_len = &thumb_data->file_buf_len_list[i];
                sprintf(temp_buf, "\"path_%d\":\"%s\",", avi_index, file_name);
                strcat(content_1, temp_buf);
                avi_index++;
            }
        }


        if (avi_index) {
            //去除,
            char *ptr = strrchr(content_1, ',');
            *ptr = '\0';
            strcat(content_1, "}}");
            printf("content: %s\n", content_1);

            ret = ctp_cli_send(bbm_hdl->ctp_cli_hdl, topic_1, content_1);
            if (ret) {
                printf("ctp_cli_send :%s err\n", topic_1);
            } else {
                ctp_file_thumb_sockfd = sock_reg(AF_INET, SOCK_STREAM, 0, NULL, NULL);
                if (ctp_file_thumb_sockfd  == NULL) {
                    printf("ctp file thumb sock_reg err\n");
                } else {
                    dest.sin_family = AF_INET;
                    dest.sin_addr.s_addr = ip_addr;
                    dest.sin_port = htons(FILE_THUMB_PORT);
                    sock_set_connect_to(ctp_file_thumb_sockfd, 1);
                    if (0 != sock_connect(ctp_file_thumb_sockfd, (struct sockaddr *)&dest, sizeof(struct sockaddr_in))) {
                        printf("sock_connect fail.\n");
                    } else {
                        recv_ctp_file_thumb(ctp_file_thumb_sockfd, priv, avi_thumb_ctp);
                    }
                    sock_unreg(ctp_file_thumb_sockfd);
                }
            }
        }

        for (i = 0; i < jpeg_index; i++) {
            if (jpeg_http[i].pid) {
                thread_kill(&jpeg_http[i].pid, KILL_WAIT);
            }
        }

        os_sem_post(&thumb_data->sem);
    }
exit:
    printf("ctp file thumb task exit \n");
}

static void local_file_thumb_task(void *priv)
{
    int ret = 0;
    int i;
    int msg[8];
    struct net_ctp_thumb *thumb_data;
    struct bbm_client_hdl *bbm_hdl = priv;
    char full_path[128];

    while (1) {
        ret = os_task_pend("taskq", msg, ARRAY_SIZE(msg));
        switch (ret) {
        case OS_TASKQ:
            switch (msg[0]) {
            case Q_MSG:
                thumb_data = (struct net_ctp_thumb *)msg[1];
                break;
            case Q_USER:
                //exit
                goto exit;
            }
            break;
        default:
            break;
        }

        for (i = 0; i < thumb_data->file_num; i++) {
            int num = thumb_data->start_index + i;
            void *fp = fselect(bbm_hdl->fs, FSEL_BY_NUMBER, bbm_hdl->file_total_num - num);
            if (!fp) {
                printf("thumb file open err \n");
                continue;
            }

            fget_name(fp, thumb_data->file_name_buf[i], sizeof(thumb_data->file_name_buf[i]));
            char *file_name = thumb_data->file_name_buf[i];

            if (strcmp(fs_get_ext(file_name), "jpg") == 0 || strcmp(fs_get_ext(file_name), "JPG") == 0) {
                //JPG
                int jpeg_size = flen(fp);
                if (fread(thumb_data->file_buf_list[i], jpeg_size, 1, fp) != jpeg_size) {
                    printf("jpeg file read err \n");
                    fclose(fp);
                    continue;
                }
                thumb_data->file_buf_len_list[i] = jpeg_size;
            } else {
                //AVI
                u32 jpeg_size;
                u8 *jpeg_buf = get_avi_first_frame(fp, &jpeg_size);
                if (jpeg_buf) {
                    thumb_data->file_buf_len_list[i] = jpeg_size;
                    memcpy(thumb_data->file_buf_list[i], jpeg_buf, jpeg_size);
                    free(jpeg_buf);
                }
            }
            fclose(fp);
        }

        os_sem_post(&thumb_data->sem);
    }
exit:
    printf("local file thumb task exit \n");
}

int bbm_ctp_file_delete(void *priv, file_entry *del_selected_files)
{
    struct bbm_client_hdl *bbm_hdl = priv;
    file_entry *current, *tmp;
    int ret, i, j, cnt = HASH_COUNT(del_selected_files);
    char topic_1[32];
    char content_1[64];


    if (bbm_hdl->is_local_dev) {
        if (cnt == 0) {
            void *fp = fselect(bbm_hdl->fs, FSEL_FIRST_FILE, 0);
            while (fp) {
                fdelete(fp);
                fp = fselect(bbm_hdl->fs, FSEL_NEXT_FILE, 0);
            }
        } else {
            HASH_ITER(hh, del_selected_files, current, tmp) {
                /* printf("del file index: %d\n", current->file_no); */
                void *fp = fselect(bbm_hdl->fs, FSEL_BY_NUMBER, bbm_hdl->file_total_num - current->file_no);
                if (fp) {
                    fdelete(fp);
                    fp = NULL;
                }
            }
        }
    } else {
        if (cnt == 0) {
            sprintf(topic_1, "FILES_DELETE_ALL");
            sprintf(content_1, "{\"op\":\"PUT\",\"param\":{\"status\":\"1\"}}");
            ret = ctp_cli_send(bbm_hdl->ctp_cli_hdl, topic_1, content_1);
            if (ret) {
                printf("ctp_cli_send :%s err\n", topic_1);
                return -1;
            }
            bbm_clean_file_list(priv);
        } else {
            sprintf(topic_1, "FILES_DELETE");
            json_object *root = json_object_new_object();
            json_object_object_add(root, "op", json_object_new_string("PUT"));

            json_object *param_obj = json_object_new_object();

            int i = 0;
            file_entry *current, *tmp;
            HASH_ITER(hh, del_selected_files, current, tmp) {
                char *file_name = bbm_hdl->file_name_list[current->file_no];

                char key[32];
                snprintf(key, sizeof(key), "path_%d", i);

                json_object_object_add(param_obj, key, json_object_new_string(file_name));
                i++;
            }

            json_object_object_add(root, "param", param_obj);

            const char *json_str = json_object_to_json_string_ext(root, JSON_C_TO_STRING_PLAIN);

            printf("del file:%s \n", json_str);

            ret = ctp_cli_send(bbm_hdl->ctp_cli_hdl, topic_1, json_str);
            if (ret) {
                printf("ctp_cli_send :%s err\n", topic_1);
                json_object_put(root);
                return -1;
            }
            json_object_put(root);

            int new_list_num = bbm_hdl->file_total_num - cnt;
            int new_list_size = new_list_num * sizeof(char *);
            char **new_file_name_list = (char **)calloc(new_list_size, 1);

            for (i = 0, j =  0; i < new_list_num; i++) {

                file_entry *entry;
                HASH_FIND_INT(del_selected_files, &j, entry);

                while (entry) {
                    j++;
                    HASH_FIND_INT(del_selected_files, &j, entry);
                }

                char *file_name = bbm_hdl->file_name_list[j];
                new_file_name_list[i] = (char *)malloc(strlen(file_name) + 1);
                strcpy(new_file_name_list[i], file_name);
                j++;
            }

            bbm_clean_file_list(priv);
            bbm_hdl->file_total_num = new_list_num;
            bbm_hdl->file_name_list = new_file_name_list;
        }

    }

    return 0;
}



int ctp_file_thumb_start(void *priv)
{
    struct bbm_client_hdl *bbm_hdl = priv;
    sprintf(bbm_hdl->ctp_file_thumb_task_name, "file_thumb_task%d", task_name_cnt++);
    char file_name[64];
    FILE *fp;
    int i;

    if (bbm_hdl->is_local_dev) {

        if (bbm_hdl->fs) {
            fscan_release(bbm_hdl->fs);
            bbm_hdl->fs = NULL;
            bbm_hdl->file_total_num = 0;
        }

        //fs
        printf("local_path:%s \n", bbm_hdl->local_path);
        bbm_hdl->fs = fscan(bbm_hdl->local_path, "-tMOVJPGAVI -sn", 3);
        if (!bbm_hdl->fs) {
            printf("file thumb fscan err \n");
            return -1;
        }
        bbm_hdl->file_total_num = bbm_hdl->fs->file_number;

        return thread_fork(bbm_hdl->ctp_file_thumb_task_name, 12, 2048, 2048,
                           &bbm_hdl->ctp_file_thumb_task_pid, local_file_thumb_task, priv);
    } else {
        return thread_fork(bbm_hdl->ctp_file_thumb_task_name, 12, 2048, 2048,
                           &bbm_hdl->ctp_file_thumb_task_pid, ctp_file_thumb_task, priv);
    }
}

int ctp_file_thumb_stop(void *priv)
{
    int msg = 1;
    struct bbm_client_hdl *bbm_hdl = priv;

    if (bbm_hdl->ctp_file_thumb_task_pid) {
        bbm_hdl->ctp_file_thumb_task_exit = 1;
        os_taskq_del_type(bbm_hdl->ctp_file_thumb_task_name, Q_MSG);
        os_taskq_post_type(bbm_hdl->ctp_file_thumb_task_name, Q_USER, 1, &msg);
        thread_kill(&bbm_hdl->ctp_file_thumb_task_pid, KILL_WAIT);
        bbm_hdl->ctp_file_thumb_task_pid = 0;
        bbm_hdl->ctp_file_thumb_task_exit = 0;
    }

    return 0;
}

int bbm_ctp_get_file_thumb(void *priv, struct net_ctp_thumb *thumb_data)
{
    int ret;
    int msg = thumb_data;
    struct bbm_client_hdl *bbm_hdl = priv;

    ret = os_taskq_post_type(bbm_hdl->ctp_file_thumb_task_name, Q_MSG, 1, &msg);
    if (ret) {
        printf("thumb post taskq err:%d \n", ret);
        return ret;
    }

    return 0;
}

int bbm_ctp_file_init(void *priv)
{
    struct bbm_client_hdl *bbm_hdl = priv;

    return thread_fork(NULL, 12, 2048, 2048
                       , &bbm_hdl->ctp_get_file_task_pid, ctp_get_file_task, priv);
}

int bbm_ctp_file_exit(void *priv)
{
    int i;
    struct bbm_client_hdl *bbm_hdl = priv;

    if (bbm_hdl->ctp_get_file_task_pid) {
        bbm_hdl->ctp_get_file_task_exit = 1;
        thread_kill(&bbm_hdl->ctp_get_file_task_pid, KILL_WAIT);
        bbm_hdl->ctp_get_file_task_pid = 0;
        bbm_hdl->ctp_get_file_task_exit = 0;
    }

    bbm_clean_file_list(priv);
}


