#include "server/ctp_server.h"
#include "server/net_server.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "server/server_core.h"
#include "system/app_core.h"
#include "action.h"
#include "storage_device.h"
#include "app_config.h"
#include "fs/fs.h"
#include "app_database.h"
#include "http/http_server.h"
#include "ctp.h"
#include "cdp.h"
#include "os/os_api.h"
#include "action.h"
#include "wifi/wifi_connect.h"
#include "event/key_event.h"
#include "asm/includes.h"
#include "baby_monitor.h"

#define CTP_CMD_HEADER "{\"errno\":%d,\"op\":\"%s\",\"param\":{"
#define CTP_CMD_HEADER_WITHOUT_ERR "{\"op\":\"%s\",\"param\":{"
#define CTP_CMD_END "}}"
#define CTP_ERR_MESSAGE "{\"errno\":%d}"

#define VFLIST_FILE_NAME "vf_list.txt"

static struct ctp_arg info;
static u8 is_phone;

int send_ctp_string(int cmd_type, char *buf, const char *_req, void *priv)
{
    struct ctp_req req;
    struct server *ctp = NULL;

    ctp = get_ctp_server_hander();
    if (ctp == NULL) {
        return -1;
    }

    req.parm = buf;
    req.topic = _req;
    req.cli = priv;
    if (!priv) {
        req.cli = info.cli;
    }
    printf("buf:%s ", buf);
    if (server_request(ctp, cmd_type, (void *)&req)) {
        return -1;
    }

    return 0;
}

static inline int _CTP_CMD_COMBINED(int cmd_type, void *priv, u32 err, const char *_req, const char *mothod, char *str)
{
    char *buf = NULL;
    int ret;
    int id = 0;
    char tmp[64];
    char *tmp1 = NULL;
    buf = (char *)malloc(512);

    if (buf == NULL) {
        printf("%s %d mem is fail \n", __func__, __LINE__);
        return -1;
    }

    if (err) {
        ret = snprintf(buf, 512, CTP_CMD_HEADER, err, mothod);
    } else {
        ret = snprintf(buf, 512, CTP_CMD_HEADER_WITHOUT_ERR, mothod);
    }

    char *key;
    char *value;

    if (!err && str != NULL) {
        while (1) {
            key = strtok_r(str, ":", &tmp1); //这函数会改数组，不能用const
            value = strtok_r(NULL, ",", &tmp1);

            if (key == NULL || value == NULL) {
                break;
            }

            ret = sprintf(tmp, "\"%s\":\"%s\",", key, value);
            tmp[ret] = '\0';
            ret = snprintf(buf, 512, "%s%s", buf, tmp);
            str = NULL;
        }

        buf[ret - 1] = '\0';//主要是去掉最后的逗号
        ret = snprintf(buf, 512, "%s%s", buf, CTP_CMD_END);
    } else {
        snprintf(buf, 512, "{\"op\":\"NOTIFY\",\"errno\":%d,\"param\":{%s}}", err, str);
    }

//打开ctp_server
//
    void *cli = NULL;
    if (!strcmp(_req, info.topic) || !priv) {
        cli = info.cli;
    } else {
        cli = priv;
    }


    if (send_ctp_string(cmd_type, buf, _req, cli) < 0) {
        free(buf);
        return -1;
    }
    return 0;
}

int CTP_CMD_COMBINED(void *priv, u32 err, const char *_req, const char *mothod, char *str)
{
    return _CTP_CMD_COMBINED(CTP_NOTIFY_COMMAND, priv, err, _req, mothod, str);
}

static void __all_get_cmd_run(void *priv, char *content)
{
    const struct ctp_map_entry *map = NULL;
    list_for_ctp_mapping_tab(map) {
        if (map->get != NULL) {
            map->get(priv, content);    //执行map中所有get命令
        }
    }
}

int ctp_cmd_analysis(const char *topic, char *content, void *priv)
{
    struct ctp_map_entry *map = NULL;
    char buf[128];
    struct intent it;
    int ret = -1;

    if (strlen(topic) <= 0 || strlen(content) <= 0) {
        printf("%s  %d err....\n", __func__, __LINE__);
        return -1;
    }

    strcpy(info.topic, topic);
    info.content = NULL;
    info.cli = priv;

    list_for_ctp_mapping_tab(map) {
        if (!strcmp(topic, map->ctp_command)) {
            if (strstr(content, "PUT") && map->put != NULL) {
                if (map->sync != true) {
                    map->sync = true;  //防止APP多次发送重发命令
                    ret =  map->put(priv, content);
                } else {
                    printf("Warnning CTP<%s> is doing now\n", map->ctp_command);
                    ret = 0;
                }
            } else if (strstr(content, "GET") && map->get != NULL) {
                if (map->sync != true) {
                    map->sync = true;
                    ret = map->get(priv, content);
                } else {
                    printf("Warnning CTP<%s> is doing now\n", map->ctp_command);
                    ret = 0;
                }
            } else {
                puts("content is error \n\n");
            }

        }

        if (ret != -1) {
            return ret;
        }
    }

    CTP_CMD_COMBINED(priv, CTP_NO_TOPIC, topic, "NOTIFY", CTP_NO_TOPIC_MSG);
    printf("%s %d topic:%s not find it or cb is NULL\n", __func__, __LINE__, topic);
    return -1;

}

int cmd_put_app_access(void *priv, char *content)
{
    char buf[64];
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *key = NULL;
    int type_num;

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    key =  json_object_object_get(parm, "type");

    const char *type = json_object_get_string(key);
    key =  json_object_object_get(parm, "ver");
    const char *ver = json_object_get_string(key);

    snprintf(buf, sizeof(buf), "type:%s,ver:%s", type, ver);
    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "APP_ACCESS", "NOTIFY", buf);

    //区分BBM_RX/手机
    type_num = atoi(type);
    if (type_num == 99) {
        //BBM
        is_phone = 0;
        if (FILE_IS_INIT_CHECK()) {
            FILE_GEN();
            snprintf(buf, sizeof(buf), "type:1,path:%s", CONFIG_REC_PATH_0"vf_list.txt");
            CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", buf);
        }
    } else {
        //手机
        is_phone = 1;
        //app_access命令完成后，随后发送所有get命令
        __all_get_cmd_run(priv, content);
    }

    json_object_put(new_obj);
    return 0;
}

int cmd_put_modify_txrate(void *priv, char *content)
{
    char buf[64];
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    char *txrate;
    int val;

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    txrate = json_object_get_string(json_object_object_get(parm, "txrate"));

    val = atoi(txrate);

    printf("modify txrate val:%d  \n", val);

    wifi_raw_set_txrate(val);

    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "MODIFY_TXRATE", "NOTIFY", buf);

    json_object_put(new_obj);

    return 0;
}

int cmd_put_open_rt_stream(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;

    const char *h, *w, *fps, *abr, *id, *sub_id;
    struct sockaddr_in *addr;
    struct video_rec_config config = {0};
    char net_path[64];
    int ret;

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    h = json_object_get_string(json_object_object_get(parm, "h"));
    w = json_object_get_string(json_object_object_get(parm, "w"));
    abr = json_object_get_string(json_object_object_get(parm, "abr"));
    fps = json_object_get_string(json_object_object_get(parm, "fps"));
    id = json_object_get_string(json_object_object_get(parm, "id"));
    sub_id = json_object_get_string(json_object_object_get(parm, "sub_id"));
    addr = ctp_srv_get_cli_addr(priv);
    sprintf(net_path, "udp://%s:%d", inet_ntoa(addr->sin_addr.s_addr)
            , _FORWARD_PORT);

    config.net_path    = net_path;
    config.width       = atoi(w);
    config.height      = atoi(h);
    config.fps         = atoi(fps);

    //TODO
    //兼容手机DVRunning2命令
    if (abr && id && sub_id) {
        config.abr_kbps    = atoi(abr);
        config.id          = atoi(id);
        config.sub_id      = atoi(sub_id);
    } else {
        config.abr_kbps    = 2000;
        config.id          = 1;
        config.sub_id      = 0;
    }

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_START;
    it.exdata = &config;
    ret = start_app(&it);

    if (ret) {
        CTP_CMD_COMBINED(NULL, CTP_RT_OPEN_FAIL, "OPEN_RT_STREAM", "NOTIFY", CTP_RT_OPEN_FAIL_MSG);
    } else {
        char buf[128];
        sprintf(buf, "format:0,w:%d,h:%d,fps:%d,rate:8000", config.width, config.height, config.fps);
        CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_RT_STREAM", "NOTIFY", buf);
    }

    json_object_put(new_obj);

    return 0;
}

static int cmd_put_close_rt_stream(void *priv, char *content)
{
    int ret;
    char buf[64];
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    const char *id, *sub_id;
    struct video_rec_config config = {0};

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    id = json_object_get_string(json_object_object_get(parm, "id"));
    sub_id = json_object_get_string(json_object_object_get(parm, "sub_id"));

    //TODO
    //兼容手机DVRunning2命令
    if (id && sub_id) {
        config.id          = atoi(id);
        config.sub_id      = atoi(sub_id);
    } else {
        config.id          = 1;
        config.sub_id      = 0;
    }

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_STOP;
    it.exdata = &config;
    ret = start_app(&it);

    if (ret) {
        printf("CLOE_RT_STREAM err!!!\n\n");
        strcpy(buf, "status:0");
    } else {
        strcpy(buf, "status:1");
    }

    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "CLOSE_RT_STREAM", "NOTIFY", buf);

    json_object_put(new_obj);

    return 0;
}

//TODO
int cmd_put_open_rec(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;

    const char *h, *w, *fps, *id, *sub_id, *abr, *cycle_time;
    struct video_rec_config config = {0};
    int ret;

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    h = json_object_get_string(json_object_object_get(parm, "h"));
    w = json_object_get_string(json_object_object_get(parm, "w"));
    fps = json_object_get_string(json_object_object_get(parm, "fps"));
    abr = json_object_get_string(json_object_object_get(parm, "abr"));
    id = json_object_get_string(json_object_object_get(parm, "id"));
    sub_id = json_object_get_string(json_object_object_get(parm, "sub_id"));
    cycle_time = json_object_get_string(json_object_object_get(parm, "cycle_time"));

    config.width       = atoi(w);
    config.height      = atoi(h);
    config.fps         = atoi(fps);
    config.id          = atoi(id);
    config.sub_id      = atoi(sub_id);
    config.cycle_time  = atoi(cycle_time);
    config.abr_kbps    = atoi(abr);

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_START;
    it.exdata = &config;
    ret = start_app(&it);

    if (ret) {
        CTP_CMD_COMBINED(NULL, CTP_REC_OPEN_FAIL, "OPEN_REC", "NOTIFY", CTP_REC_OPEN_FAIL_MSG);
    } else {
        char buf[128];
        sprintf(buf, "w:%d h:%d fps:%d abr:%d", config.width, config.height, config.fps, config.abr_kbps);
        CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "OPEN_REC", "NOTIFY", buf);
    }

    json_object_put(new_obj);

    return 0;
}

static int cmd_put_close_rec(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    const char *id, *sub_id;
    struct video_rec_config config = {0};

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    id = json_object_get_string(json_object_object_get(parm, "id"));
    sub_id = json_object_get_string(json_object_object_get(parm, "sub_id"));

    config.id          = atoi(id);
    config.sub_id      = atoi(sub_id);

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_STOP;
    it.exdata = &config;
    start_app(&it);

    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "CLOSE_REC", "NOTIFY", NULL);

    json_object_put(new_obj);

    return 0;
}


int cmd_put_set_video_abr(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;

    int ret;
    const char *abr, *id, *sub_id;
    struct video_rec_config config = {0};
    char buf[128];

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    abr = json_object_get_string(json_object_object_get(parm, "abr"));
    id = json_object_get_string(json_object_object_get(parm, "id"));
    sub_id = json_object_get_string(json_object_object_get(parm, "sub_id"));

    config.abr_kbps    = atoi(abr);
    config.id          = atoi(id);
    config.sub_id      = atoi(sub_id);

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_SET_ABR;
    it.exdata = &config;
    ret = start_app(&it);

    if (ret) {
        CTP_CMD_COMBINED(NULL, CTP_SET_PRARM, "SET_VIDEO_ABR", "NOTIFY", buf);
    } else {
        CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "SET_VIDEO_ABR", "NOTIFY", buf);
    }

    json_object_put(new_obj);

    return 0;
}


static int cmd_put_make_forward_files_list(void *priv, char *content)
{
    char buf[128];
    char path[64];
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    char type = 0;
    u32 file_num = 0;
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "type");

    const char *tmp_value = json_object_get_string(tmp);

    tmp =  json_object_object_get(parm, "num");
    if (tmp != NULL) {
        const char *num = json_object_get_string(tmp);
        if (num != NULL && atoi(num) != 0) {
            file_num = atoi(num);
        }
    }
    if (tmp_value == NULL) {
        type = VID_JPG;
    } else {
        type = atoi(tmp_value);
    }
    switch (type) {
    case -1 :
        CTP_CMD_COMBINED(priv, CTP_SD_OFFLINE, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", CTP_SD_OFFLINE_MSG);
        break;
    case NONE:
        /*snprintf(buf, sizeof(buf), "type:0,path:%s", CONFIG_REC_PATH_1"vf_list.txt");*/
        snprintf(buf, sizeof(buf), "type:0,path:%s", CONFIG_REC_PATH_0"vf_list.txt");
        CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", buf);
        break;
    case VID_JPG:

        if (!file_num) {

#if defined CONFIG_ENABLE_VLIST
            if (!FILE_INITIND_CHECK()) {
                FILE_GEN();
                /*snprintf(buf, sizeof(buf), "type:1,path:%s", CONFIG_REC_PATH_1"vf_list.txt");*/
                snprintf(buf, sizeof(buf), "type:1,path:%s", CONFIG_REC_PATH_0"vf_list.txt");
                CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", buf);

            } else {
                CTP_CMD_COMBINED(priv, CTP_REQUEST, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", CTP_REQUEST_MSG);
            }
        } else {
            FILE_LIST_INIT_SMALL(file_num);
            /*snprintf(buf, sizeof(buf), "type:1,path:%s", CONFIG_REC_PATH_1"vf_list_small.txt");*/
            snprintf(buf, sizeof(buf), "type:1,path:%s", CONFIG_REC_PATH_0"vf_list_small.txt");
            CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", buf);
#endif
        }
        break;
    case VIDEO:
        vf_list(type, 1, path);
        snprintf(buf, sizeof(buf), "type:2,path:%s", path);
        CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", buf);
        break;
    case JPG:
        vf_list(type, 1, path);
        snprintf(buf, sizeof(buf), "type:3,path:%s", path);
        CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FORWARD_MEDIA_FILES_LIST", "NOTIFY", buf);
        break;
    default:
        break;
    }


    json_object_put(new_obj);
    return 0;
}

static int cmd_put_multi_cover_figure(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    char buf[128];
    u32 i = 0;
    char filename[8];
    u32 ret = 0;
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    char (*file_name_array)[64] = calloc(1, 51 * 64);
    if (file_name_array == NULL) {
        CTP_CMD_COMBINED(priv, CTP_REQUEST, "MULTI_COVER_FIGURE", "NOTIFY", CTP_REQUEST_MSG);
        return 0;
    }

    while (1) {
        sprintf(filename, "path_%d", i);
        tmp =  json_object_object_get(parm, filename);

        if (tmp == NULL) {
            break;
        }

        if (i > 50) {
            printf("path is too many\n");
            CTP_CMD_COMBINED(priv, CTP_REQUEST, "MULTI_COVER_FIGURE", "NOTIFY", CTP_REQUEST_MSG);
            break;
        }

        const char *tmp_value = json_object_get_string(tmp);
        strcpy(file_name_array[i], tmp_value);
        /* printf("%d filename %s \n", i, file_name_array[i]); */
        i++;
    }

    if (!i) {
        free(file_name_array);
        file_name_array = NULL;
        CTP_CMD_COMBINED(priv, CTP_REQUEST, "MULTI_COVER_FIGURE", "NOTIFY", CTP_REQUEST_MSG);
        json_object_put(new_obj);
        return 0;
    }

    struct net_req req;
    memset(&req, 0, sizeof(struct net_req));
    req.pre.type = PREVIEW;
    req.pre.filename = file_name_array;
#ifdef CONFIG_ENABLE_VLIST
    if (video_preview_post_msg(&req)) {
        CTP_CMD_COMBINED(priv, CTP_REQUEST, "MULTI_COVER_FIGURE", "NOTIFY", CTP_REQUEST_MSG);
        json_object_put(new_obj);
        free(file_name_array);
        file_name_array = NULL;
        return 0;
    }
#endif
    json_object_put(new_obj);

    return 0;

}

static int cmd_put_time_axis_play(void *priv, char *content)
{
    struct server *net = NULL;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    u32 i = 0;
    char filename[8];
    u32 ret = 0;
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "path");
    const char *file_name = json_object_get_string(tmp);

    tmp =  json_object_object_get(parm, "offset");
    const char *msec = json_object_get_string(tmp);

    printf("filename :%s   msec:%s\n", file_name, msec);
    struct net_req req;
    memset(&req, 0, sizeof(struct net_req));
    strcpy(req.playback.file_name, file_name);
    req.playback.msec = atoi(msec);

    struct sockaddr_in *dst_addr = ctp_srv_get_cli_addr(priv);

    req.remote_addr.sin_family = AF_INET;
    req.remote_addr.sin_addr.s_addr = dst_addr->sin_addr.s_addr;
    req.remote_addr.sin_port = htons(2223);

#ifdef CONFIG_ENABLE_VLIST
    if (is_phone) {
        if (video_playback_post_msg(&req)) {
            CTP_CMD_COMBINED(priv, CTP_REQUEST, "TIME_AXIS_PLAY", "NOTIFY", CTP_REQUEST_MSG);
            json_object_put(new_obj);
            return 0;
        }
    } else {
        if (video_playback_post_msg_udp(&req)) {
            CTP_CMD_COMBINED(priv, CTP_REQUEST, "TIME_AXIS_PLAY", "NOTIFY", CTP_REQUEST_MSG);
            json_object_put(new_obj);
            return 0;
        }
    }
#endif
    json_object_put(new_obj);

    return 0;

}

static int cmd_put_time_axis_play_ctrl(void *priv, char *content)
{
    char buf[128];
    struct server *net = NULL;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    u32 i = 0;
    char filename[8];
    u32 ret = 0;
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "status");
    const char *status = json_object_get_string(tmp);

    struct sockaddr_in *dst_addr = ctp_srv_get_cli_addr(priv);
    if (!dst_addr) {
        dst_addr = cdp_srv_get_cli_addr(priv);
    }
    printf("status:%s\n", status);

    switch (atoi(status)) {
    case FILE_PLAY_VIDEO_CONTINUE:
#ifdef CONFIG_ENABLE_VLIST
        if (is_phone) {
            ret = playback_cli_continue(dst_addr);
        } else {
            ret = playback_udp_cli_continue(dst_addr);
        }
#endif
        break;

    case FILE_PLAY_VIDEO_PAUSE:
#ifdef CONFIG_ENABLE_VLIST
        if (is_phone) {
            ret = playback_cli_pause(dst_addr);
        } else {
            ret = playback_udp_cli_pause(dst_addr);
        }
#endif
        break;

    case FILE_PLAY_VIDEO_STOP:
#ifdef CONFIG_ENABLE_VLIST
        if (is_phone) {
            ret = playback_disconnect_cli(dst_addr);
        } else {
            ret = playback_udp_disconnect_cli(dst_addr);
        }
#endif
        break;

    default:
        ret = -1;
        break;
    }

    if (!ret) {

        snprintf(buf, sizeof(buf), "status:%s", status);
        CTP_CMD_COMBINED(priv, CTP_NO_ERR, "TIME_AXIS_PLAY_CTRL", "NOTIFY", buf);
    } else {
        CTP_CMD_COMBINED(priv, CTP_REQUEST, "TIME_AXIS_PLAY_CTRL", "NOTIFY", CTP_REQUEST_MSG);
    }

    json_object_put(new_obj);

    return 0;

}

void ctp_cmd_socket_unregister(void *priv)
{
    if (!priv) {
        priv = info.cli;
        if (!priv) {
            return;
        }
    }
    struct sockaddr_in *addr;
    addr = (struct sockaddr_in *)ctp_srv_get_cli_addr(priv);
    if (!addr) {
        addr = (struct sockaddr_in *)cdp_srv_get_cli_addr(priv);
    }
    if (addr) {
        extern int TCP_client_socket_quit(int addr);
        extern int UDP_client_socket_unreg(int addr);
        TCP_client_socket_quit(addr->sin_addr.s_addr);
        UDP_client_socket_unreg(addr->sin_addr.s_addr);
    }
}

static int cmd_put_ctp_cli_connected(void *priv, char *content)
{
    return 0;
}

static int cmd_put_ctp_cli_disconnect(void *priv, char *content)
{
    char buf[32];
    struct sockaddr_in *dest_addr;
    struct ctp_map_entry *map;
    dest_addr = ctp_srv_get_cli_addr(priv);
    if (!dest_addr) {
        dest_addr = cdp_srv_get_cli_addr(priv);
    }
    info.dest_addr = NULL;
    info.cli = NULL;

    ctp_cmd_socket_unregister(priv);

    printf("|CLI_DISCONNECT 0x%x, 0x%x\n", (u32)priv, (u32)dest_addr->sin_addr.s_addr);

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_STOP_ALL;
    start_app(&it);

#ifdef CONFIG_ENABLE_VLIST
    video_preview_and_thus_disconnect(dest_addr);
    playback_disconnect_cli(dest_addr);
#endif
    http_get_server_discpnnect_cli(dest_addr);
    strcpy(buf, "status:1");
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "CTP_CLI_DISCONNECT", "NOTIFY", buf);
    list_for_ctp_mapping_tab(map) {
        map->sync = false;
    }

    ctp_srv_free_cli(priv);
    cdp_srv_free_cli(priv);

    return 0;
}

static int cmd_put_ap_ssid_info(void *priv, char *content)
{
    char buf[128];
    struct server *net = NULL;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    struct sys_time time;

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "ssid");
    const char *ssid = json_object_get_string(tmp);

    tmp =  json_object_object_get(parm, "pwd");

    const char *pwd = json_object_get_string(tmp);
    tmp =  json_object_object_get(parm, "status");
    const char *status = json_object_get_string(tmp);


    printf("cmd_put_ap_ssid_info : ssid:%s   pwd:%s \n%s\n", ssid, pwd, content);
    if (strlen(pwd) == 0) {

        snprintf(buf, sizeof(buf), "ssid:%s,status:%s", ssid,  status);
    } else {
        snprintf(buf, sizeof(buf), "ssid:%s,pwd:%s,status:%s", ssid, pwd, status);
    }
    if (ssid == NULL || (strlen(pwd) > 0 && strlen(pwd) < 8)
        || strlen(ssid) >= 32) {
        printf("ssid is null or pwd is less than 7\n");
        CTP_CMD_COMBINED(priv, CTP_REQUEST, "AP_SSID_INFO", "NOTIFY", buf);
        return 0;
    }

    struct wifi_mode_info info;
    if (!strcmp("", ssid)) {
        info.mode = AP_MODE;
        wifi_get_mode_cur_info(&info);
    } else {
        info.ssid = (char *)ssid;
        info.pwd = (char *)pwd;
    }
    wifi_store_mode_info(AP_MODE, info.ssid, info.pwd);

    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "AP_SSID_INFO", "NOTIFY", buf);

    if (atoi(status)) {
        os_time_dly(300);//重启太快，没回复
        cpu_reset();
    }

    json_object_put(new_obj);

    return 0;
}

int cmd_get_keep_alive_interval(void *priv, char *content)
{
    int timeout;
    char buf[16];
    //分解content字段
    timeout = ctp_srv_get_keep_alive_timeout();
    snprintf(buf, sizeof(buf), "timeout:%d", timeout);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "KEEP_ALIVE_INTERVAL", "NOTIFY", buf);


    return 0;

}

//APP使用
int cmd_put_video_ctrl(void *priv, char *content)
{
    char buf[128];
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    struct json_object *sta = NULL;
    const char *status;
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    sta =  json_object_object_get(parm, "status");
    int cur_state = 0;
    int set_state = 0;
    int ret;
    struct video_rec_config config = {0};

    printf("cmd_put_video_ctrl : %s \n", content);
    status = json_object_get_string(sta);

    //录像对应ID
    config.id = 1;
    config.sub_id = 1;
    config.width       = 640;
    config.height      = 480;
    config.fps         = 25;
    config.cycle_time  = 3;
    config.abr_kbps    = 1000;

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_GET_STATUS;
    it.exdata = &config;
    it.data = &cur_state;
    ret = start_app(&it);

    set_state = atoi(status);

    if (set_state) {
        //开启
        if (cur_state != set_state) {
            it.action = ACTION_VIDEO_START;
            ret = start_app(&it);
            if (ret) {
                set_state = cur_state;
            }
        }
    } else {
        //关闭
        if (cur_state != set_state) {
            it.action = ACTION_VIDEO_STOP;
            ret = start_app(&it);
            if (ret) {
                set_state = cur_state;
            }
        }
    }

    snprintf(buf, sizeof(buf), "status:%d", set_state);
    CTP_CMD_COMBINED(NULL, CTP_NO_ERR, "VIDEO_CTRL", "NOTIFY", buf);

    return 0;
}

int cmd_get_video_ctrl(void *priv, char *content)
{
    char buf[128];
    int status = 0;;
    struct video_rec_config config = {0};

    //录像对应ID
    config.id = 1;
    config.sub_id = 1;

    struct intent it;
    init_intent(&it);
    it.name = "video_rec";
    it.action = ACTION_VIDEO_GET_STATUS;
    it.exdata = &config;
    it.data = &status;
    start_app(&it);

    snprintf(buf, sizeof(buf), "status:%d", status);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "VIDEO_CTRL", "NOTIFY", buf);

    return 0;
}

int cmd_get_sd_status(void *priv, char *content)
{
    char buf[16];

    snprintf(buf, sizeof(buf), "online:%d", storage_device_ready());
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "SD_STATUS", "NOTIFY", buf);

    return 0;

}

int cmd_get_bat_status(void *priv, char *content)
{
    char buf[32];
    //分解content字段

    snprintf(buf, sizeof(buf), "level:%d", 4);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "BAT_STATUS", "NOTIFY", buf); //目前没有电池状态，先写充电中 4

    return 0;

}

int cmd_get_uuid(void *priv, char *content)
{
    char buf[128] = {0};
    u8 mac[6];

    wifi_get_mac(mac);
    snprintf(buf, sizeof(buf), "uuid:%s%02x%02x%02x%02x%02x%02x", "f2dd3cd7-b026-40aa-aaf4-", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "UUID", "NOTIFY", buf);
    return 0;
}

int cmd_get_sd_size(void *priv, char *content)
{
    char buf[32];
    u32 space;
    struct vfs_partition *part;

    if (storage_device_ready() == 0) {
        CTP_CMD_COMBINED(priv, CTP_SD_OFFLINE, "TF_CAP", "NOTIFY", CTP_SD_OFFLINE_MSG);
    } else {
        part = fget_partition(CONFIG_ROOT_PATH);
        fget_free_space(CONFIG_ROOT_PATH, &space);
        snprintf(buf, sizeof(buf), "left:%d,total:%d", space / 1024, part->total_size / 1024);
        CTP_CMD_COMBINED(priv, CTP_NO_ERR, "TF_CAP", "NOTIFY", buf);

    }

    return 0;
}

#define VERSION_ID "6.6.6"
int cmd_get_info_product(void *priv, char *content)

{
    static u8 buf[128] = {0};
    u8 *mac;
//    extern u8 *wifi_get_module_mac_addr(void);
//    mac = wifi_get_module_mac_addr();
//    sprintf(buf, "%s", "JL;jl5701;XD36;B112;00;MT02101;01;01;%02x:%02x:%02x:%02x;", mac[2], mac[3], mac[4], mac[5]);
    memset(buf, 0, 128);
#ifdef SYS_PARAM_SET_ENABLE
    if (sys_version_updata_enable2) {
        sprintf(buf, "%s:%s%s:%s", "sp:XD,model", VERSION_BOARD, ",brand:V02,version", sys_version2);
    } else
#endif
    {
        sprintf(buf, "%s:%s%s:%s", "sp:XD,model", "CC31", ",brand:V02,version", VERSION_ID);
    }
    printf("========cmd_get_info_product:%s\n", buf);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "PRODUCT_INFO", "NOTIFY", buf);
    return 0;
}

static int cmd_get_date_time(void *priv, char *content)
{
    struct sys_time time;
    char buf[128];
    void *rtc_fd = NULL;
    rtc_fd = dev_open("rtc", NULL);
    if (!rtc_fd) {
        printf("rtc open err !!\n\n");
        return 0;
    }
    dev_ioctl(rtc_fd, IOCTL_GET_SYS_TIME, (u32)&time);
    dev_close(rtc_fd);

    snprintf(buf, sizeof(buf), "date:%04d%02d%02d%02d%02d%02d", time.year, time.month, time.day, time.hour, time.min, time.sec);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "DATE_TIME", "NOTIFY", buf);

    return 0;
}

static int cmd_get_sta_ssid_info(void *priv, char *content)
{
    char buf[128];
    struct wifi_mode_info info;
    info.mode = STA_MODE;
    wifi_get_mode_cur_info(&info);
    printf("sta get ssid:%s   pwd:%s  \n", info.ssid, info.pwd);
    snprintf(buf, sizeof(buf), "ssid:%s,pwd:%s", info.ssid, info.pwd);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "STA_SSID_INFO", "NOTIFY", buf);
    return 0;
}

static int cmd_put_sta_ssid_info(void *priv, char *content)
{
    char buf[128];
    struct server *net = NULL;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    struct sys_time time;

    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "ssid");
    const char *ssid = json_object_get_string(tmp);

    tmp =  json_object_object_get(parm, "pwd");

    const char *pwd = json_object_get_string(tmp);
    tmp =  json_object_object_get(parm, "status");
    const char *status = json_object_get_string(tmp);



    printf("ssid:%s   pwd:%s \n", ssid, pwd);
    if (strlen(pwd) == 0) {

        snprintf(buf, sizeof(buf), "ssid:%s,status:%s", ssid, status);
    } else {
        snprintf(buf, sizeof(buf), "ssid:%s,pwd:%s,status:%s", ssid, pwd, status);
    }

    if (ssid == NULL || (strlen(pwd) > 0 && strlen(pwd) < 8)) {
        printf("ssid is null or pwd is less than 7\n");
        CTP_CMD_COMBINED(priv, CTP_REQUEST, "STA_SSID_INFO", "NOTIFY", CTP_REQUEST_MSG);
        return 0;
    }

    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "STA_SSID_INFO", "NOTIFY", buf);

    //断开所有客户端

    ctp_srv_disconnect_all_cli();
    cdp_srv_disconnect_all_cli();

    info.dest_addr = NULL;

    if (atoi(status)) {
        wifi_store_mode_info(STA_MODE, ssid, pwd);
    }

    //切换WIFI模式到STA模式,切换成功后设备自行连接上热点
    wifi_enter_sta_mode(ssid, pwd);
    //选择是否保存当前WIFI模式信息
    json_object_put(new_obj);

    return 0;
}


static int cmd_get_ap_ssid_info(void *priv, char *content)
{
    char buf[128];
    struct wifi_mode_info info;
    info.mode = AP_MODE;
    wifi_get_mode_cur_info(&info);
    printf("ap get ssid:%s   pwd:%s  \n", info.ssid, info.pwd);
    snprintf(buf, sizeof(buf), "ssid:%s,pwd:%s", info.ssid, info.pwd);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "AP_SSID_INFO", "NOTIFY", buf);
    return 0;
}

/* 设备能力集获取 */
//0-App决定，1-SDK，2-HTTP，3-SDK回放、HTTP下载，4-HTTP回放、SDK下载
int cmd_get_camera_capability(void *priv, char *content)
{
    char buf[128];
    snprintf(buf, sizeof(buf), "value:%s", "00100100002");

    printf("buf -> %s\n", buf);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "CAMERA_CAPABILITY", "NOTIFY", buf);
    return 0;
}

static void date_time(const char *date, struct sys_time *tm)
{
    char *f = NULL;
    char *b = NULL;
    char buf[5] = {0};

    memcpy(buf, date, 4);
    tm->year = atoi(buf);
    memcpy(buf, date + 4, 2);
    buf[2] = '\0';
    tm->month = atoi(buf);
    memcpy(buf, date + 6, 2);
    buf[2] = '\0';
    tm->day = atoi(buf);
    memcpy(buf, date + 8, 2);
    buf[2] = '\0';
    tm->hour = atoi(buf);
    memcpy(buf, date + 10, 2);
    buf[2] = '\0';
    tm->min = atoi(buf);
    memcpy(buf, date + 12, 2);
    buf[2] = '\0';
    tm->sec = atoi(buf);

}

static int cmd_put_date_time(void *priv, char *content)
{
    char buf[128];
    struct server *net = NULL;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    struct sys_time time;
    void *rtc_fd = NULL;


    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "date");
    const char *date = json_object_get_string(tmp);



    printf("date:%s\n", date);
    if (date != NULL) {
        date_time(date, &time);
    }
    printf("date->year:%04d month:%02d day:%02d hour:%02d min:%02d sec:%02d", time.year, time.month, time.day, time.hour, time.min, time.sec);
    rtc_fd = dev_open("rtc", NULL);
    if (!rtc_fd) {
        printf("open rtd err \n\n");
        json_object_put(new_obj);
        return 0;
    }
    dev_ioctl(rtc_fd, IOCTL_SET_SYS_TIME, (u32)&time);
    dev_close(rtc_fd);
    snprintf(buf, sizeof(buf), "date:%04d%02d%02d%02d%02d%02d", time.year, time.month, time.day, time.hour, time.min, time.sec);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "DATE_TIME", "NOTIFY", buf);
    json_object_put(new_obj);
    db_update("datey", time.year);
    db_update("datem", time.month);
    db_update("dated", time.day);
    db_update("dateh", time.hour);
    db_update("datemi", time.min);
    db_update("dates", time.sec);
    return 0;
}

static int cmd_get_generic_cmd(void *priv, char *content)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "status:%d", 1);
    printf("GENERIC_CMD  GET\n");
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "GENERIC_CMD", "NOTIFY", buf);
    return 0;
}

static int cmd_put_generic_cmd(void *priv, char *content)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "status:%d", 1);

    printf("GENERIC_CMD  PUT\n");
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "GENERIC_CMD", "NOTIFY", buf);

    return 0;
}

int cmd_get_video_size(void *priv, char *content)
{
    char buf[128];
    char str[32] = "NA;720P;480P";

    /*     case VIDEO_RES_720P: */
    /* snprintf(buf, sizeof(buf), "str:%s,val:%d", str, 1); */
    /* break; */
    /* case VIDEO_RES_VGA: */

    snprintf(buf, sizeof(buf), "str:%s,val:%d", str, 2);

    printf("buf -> %s\n", buf);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "VIDEO_SIZE", "NOTIFY", buf);
    return 0;
}

int cmd_put_video_size(void *priv,  char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *v = NULL;
    struct intent it;
    char buf[128];
    /* const char *height, *width, *format; */
    const char *val;
    /* char str[32] = "4K;2K;1080P"; */
    char str[32] = "NA;720P;480P";
    //分解content字段
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    v =  json_object_object_get(parm, "val");
    val = json_object_get_string(v);

    printf("val : %s\n", val);

    u32 res = atoi(val);
    if (res == 1) {
        /* db_update("res", VIDEO_RES_720P); */
    } else if (res == 2) {
        /* db_update("res", VIDEO_RES_VGA); */
    } else {
        /* db_update("res", VIDEO_RES_720P); */
    }
    snprintf(buf, sizeof(buf), "str:%s,val:%d", str, res);

    printf("buf -> %s\n", buf);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "VIDEO_SIZE", "NOTIFY", buf);

    json_object_put(new_obj);
    return 0;
}

int cmd_get_video_param(void *priv, char *content)
{
    char buf[128];

    /*     case VIDEO_RES_720P: */
    /* snprintf(buf, sizeof(buf), "w:%d,h:%d,format:0,fps:%d,rate:%d", 640, 480, net_video_rec_get_fps(), net_video_rec_get_audio_rate()); */
    /* break; */
    /* case VIDEO_RES_VGA: */
    snprintf(buf, sizeof(buf), "w:%d,h:%d,format:0,fps:%d,rate:%d", 640, 480, 25, 8000);

    printf("buf -> %s\n", buf);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "VIDEO_PARAM", "NOTIFY", buf);
    return 0;

}

int cmd_put_video_param(void *priv,  char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *h = NULL;
    json_object *w = NULL;
    struct intent it;
    char buf[128];
    const char *height, *width, *format;
    //分解content字段
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    h =  json_object_object_get(parm, "h");
    w =  json_object_object_get(parm, "w");
    width = json_object_get_string(w);
    height = json_object_get_string(h);

    printf("width :%s height : %s %s\n", width, height);

    snprintf(buf, sizeof(buf), "w:%d,h:%d,format:%d,fps:%d,rate:%d", 640, 480, 0, 25, 8000);

    printf("buf -> %s\n", buf);
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "VIDEO_PARAM", "NOTIFY", buf);

    json_object_put(new_obj);
    return 0;

}

static int cmd_put_files_delete(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    char buf[256 ] = {0};
    u32 i = 0;
    char filename[8];
    u32 ret = 0;
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");

    while (1) {
        sprintf(filename, "path_%d", i);
        tmp =  json_object_object_get(parm, filename);

        if (tmp == NULL) {
            break;
        }

        const char *tmp_value = json_object_get_string(tmp);
        printf("filename %s \n", tmp_value);

        if (fdelete_by_name(tmp_value)) {
            printf("fdelete by name\n");
            ret = snprintf(buf, sizeof(buf), "status:%d,path:%s", 0, tmp_value);
            CTP_CMD_COMBINED(priv, CTP_OPEN_FILE, "FILES_DELETE", "NOTIFY", buf);
        } else {

#if defined CONFIG_ENABLE_VLIST
            FILE_DELETE(tmp_value, 1);
#endif
            snprintf(buf, sizeof(buf), "status:%d,path:%s", 1, tmp_value);
            CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FILES_DELETE", "NOTIFY", buf);

        }

        i++;
    }

    json_object_put(new_obj);
    return 0;

}

static int cmd_put_files_delete_all(void *priv, char *content)
{
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    char buf[128] = {0};
    char file_name[128];
    u32 i = 0;
    u32 ret = 0;
    new_obj = json_tokener_parse(content);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "status");

    if (tmp && atoi(tmp)) {
        printf("delete all files \n");
        goto err;
    }

    struct vfscan *fs = fscan(CONFIG_REC_PATH_0, "-tMOVJPGAVI -sn", 3);
    if (!fs) {
        printf("delet files fscan err \n");
        goto err;
    }

    void *fp = fselect(fs, FSEL_FIRST_FILE, 0);

    while (fp) {

#if defined CONFIG_ENABLE_VLIST
        if (fget_name(fp, file_name, sizeof(file_name))) {
            FILE_DELETE(file_name, 1);
        }
#endif
        fdelete(fp);
        fp = fselect(fs, FSEL_NEXT_FILE, 0);
    }

    fscan_release(fs);

    snprintf(buf, sizeof(buf), "status:1");
    CTP_CMD_COMBINED(priv, CTP_NO_ERR, "FILES_DELETE_ALL", "NOTIFY", buf);

    json_object_put(new_obj);
    return 0;

err:
    snprintf(buf, sizeof(buf), "status:0");
    CTP_CMD_COMBINED(priv, CTP_OPEN_FILE, "FILES_DELETE_ALL", "NOTIFY", buf);
    json_object_put(new_obj);
    return -1;
}


int cmd_put_photo_ctrl(void *priv, char *content)
{
    char buf[128];
    struct intent it;
    int ret;

    struct video_rec_config config = {0};

    if (is_phone) {
        config.id = 1;
        config.sub_id = 0;
    } else {
        json_object *new_obj = NULL;
        json_object *parm = NULL;
        const char *id, *sub_id;
        new_obj = json_tokener_parse(content);
        parm =  json_object_object_get(new_obj, "param");
        id = json_object_get_string(json_object_object_get(parm, "id"));
        sub_id = json_object_get_string(json_object_object_get(parm, "sub_id"));

        if (id && sub_id) {
            config.id          = atoi(id);
            config.sub_id      = atoi(sub_id);
        }
        json_object_put(new_obj);
    }

    if (storage_device_ready() == 0) {
        CTP_CMD_COMBINED(priv, CTP_SD_OFFLINE, "PHOTO_CTRL", "NOTIFY", CTP_SD_OFFLINE_MSG);
    } else {
        init_intent(&it);
        it.name = "video_rec";
        it.action = ACTION_VIDEO_TAKE_PHOTO;
        it.exdata = &config;
        ret = start_app(&it);
        if (ret) {
            printf("cmd_put_photo_ctrl err \n");
            CTP_CMD_COMBINED(NULL, CTP_REQUEST, "PHOTO_CTRL", "NOTIFY", CTP_REQUEST_MSG);
            return -1;
        }
    }

    //media_file_list会发;
    /* snprintf(buf, sizeof(buf), "status:1"); */
    /* CTP_CMD_COMBINED(priv, CTP_NO_ERR, "PHOTO_CTRL", "NOTIFY", buf); */

    return 0;
}

const struct ctp_map_entry ctp_video_cmd_tab[] SEC_USED(.ctp_video_cmd) = {
    {NULL, "APP_ACCESS", NULL, cmd_put_app_access},
    {NULL, "OPEN_RT_STREAM", NULL, cmd_put_open_rt_stream},
    {NULL, "CLOSE_RT_STREAM", NULL, cmd_put_close_rt_stream},
    {NULL, "OPEN_REC", NULL, cmd_put_open_rec},
    {NULL, "CLOSE_REC", NULL, cmd_put_close_rec},
    {NULL, "MODIFY_TXRATE", NULL, cmd_put_modify_txrate},
    {NULL, "SET_VIDEO_ABR", NULL, cmd_put_set_video_abr},
    {NULL, "VIDEO_SIZE", cmd_get_video_size, cmd_put_video_size},
    {NULL, "VIDEO_PARAM", cmd_get_video_param, cmd_put_video_param},
    {NULL, "VIDEO_CTRL", cmd_get_video_ctrl, cmd_put_video_ctrl},
    {NULL, "PHOTO_CTRL", NULL, cmd_put_photo_ctrl},

    {NULL, "CTP_CLI_DISCONNECT", NULL, cmd_put_ctp_cli_disconnect},
    {NULL, "CTP_CLI_CONNECTED", NULL, cmd_put_ctp_cli_connected},

    {NULL, "FILES_DELETE", NULL, cmd_put_files_delete},
    {NULL, "FILES_DELETE_ALL", NULL, cmd_put_files_delete_all},

    //TODO
    //以下命令移植行车工程ctp_cmd暂未做修改
    {NULL, "FORWARD_MEDIA_FILES_LIST", NULL, cmd_put_make_forward_files_list},
    {NULL, "MULTI_COVER_FIGURE", NULL, cmd_put_multi_cover_figure},
    {NULL,  "TIME_AXIS_PLAY", NULL, cmd_put_time_axis_play},
    {NULL,  "TIME_AXIS_PLAY_CTRL", NULL, cmd_put_time_axis_play_ctrl},

    {"kep", "KEEP_ALIVE_INTERVAL", cmd_get_keep_alive_interval, NULL},
    {"sd", "SD_STATUS", cmd_get_sd_status, NULL},
    {"bat", "BAT_STATUS", cmd_get_bat_status, NULL},
    {"uuid", "UUID", cmd_get_uuid, NULL},
    {"fp", "TF_CAP", cmd_get_sd_size, NULL},
    {NULL, "PRODUCT_INFO", cmd_get_info_product, NULL},
    {NULL, "DATE_TIME", cmd_get_date_time, cmd_put_date_time},
    {NULL, "AP_SSID_INFO", cmd_get_ap_ssid_info, cmd_put_ap_ssid_info},
    {NULL, "STA_SSID_INFO", cmd_get_sta_ssid_info, cmd_put_sta_ssid_info},
    {NULL, "CAMERA_CAPABILITY", cmd_get_camera_capability, NULL},   /* 设备能力集获取 */
    {NULL, "GENERIC_CMD", cmd_get_generic_cmd, cmd_put_generic_cmd},
};


