#include "system/includes.h"
#include "server/ctp_server.h"
#include "sock_api/sock_api.h"
#include "baby_monitor.h"
#include "json_c/json.h"
#include "json_c/json_tokener.h"
#include "action.h"


#define CTP_CMD_PORT            3333    //CTP命令端口

static int json_parse_to_path(const char *parm_list, u8 *path)
{
    const char *tmp_value;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    new_obj = json_tokener_parse(parm_list);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "path");
    if (tmp == NULL) {
        printf("err no path object \n");
        json_object_put(new_obj);
        return -1;
    }
    tmp_value = json_object_get_string(tmp);

    strcpy(path, tmp_value);

    printf("content :%s \n", parm_list);
    printf("path:%s \n", path);

    json_object_put(new_obj);
    return 0;
}

static int json_parse_sd_status(const char *parm_list)
{
    const char *tmp_value;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *tmp = NULL;
    int online_status;
    new_obj = json_tokener_parse(parm_list);
    parm =  json_object_object_get(new_obj, "param");
    tmp =  json_object_object_get(parm, "online");
    if (tmp == NULL) {
        printf("err no online object \n");
        json_object_put(new_obj);
        return -1;
    }
    tmp_value = json_object_get_string(tmp);

    online_status = atoi(tmp_value);

    json_object_put(new_obj);

    return online_status;
}

static int json_parse_video_finish(const char *parm_list, char *fname)
{
    const char *tmp_value;
    json_object *new_obj = NULL;
    json_object *parm = NULL;
    json_object *desc = NULL;
    json_object *desc_obj = NULL;
    json_object *tmp = NULL;

    new_obj = json_tokener_parse(parm_list);
    if (!new_obj) {
        printf("json_tokener_parse err\n");
        return -1;
    }
    parm =  json_object_object_get(new_obj, "param");
    desc =  json_object_object_get(parm, "desc");

    if (!desc) {
        printf("no desc json obj\n");
        return -1;
    }

    desc_obj = json_tokener_parse(json_object_get_string(desc));
    tmp =  json_object_object_get(desc_obj, "f");
    if (tmp == NULL) {
        printf("err no f object \n");
        json_object_put(desc_obj);
        json_object_put(new_obj);
        return -1;
    }
    tmp_value = json_object_get_string(tmp);

    strcpy(fname, tmp_value);

    json_object_put(desc_obj);
    json_object_put(new_obj);

    return 0;
}

static int json_parse_err_value(const char *parm_list)
{
    json_object *new_obj = NULL;
    json_object *errno_obj = NULL;
    const char *tmp_value;

    new_obj = json_tokener_parse(parm_list);
    errno_obj =  json_object_object_get(new_obj, "errno");

    if (errno_obj == NULL) {
        json_object_put(new_obj);
        return 0;
    } else {
        json_object_put(new_obj);
        tmp_value = json_object_get_string(errno_obj);
        return atoi(tmp_value);
    }
}


static int ctp_recv_cb_action(int action, void *priv, void *arg)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = action;
    it.data = priv;
    it.exdata = arg;
    return start_app(&it);
}

static int bbm_ctp_recv_callback(void *hdl, enum ctp_cli_msg_type type, const char *topic, const char *parm_list, void *priv)
{
    int ret;

    struct bbm_client_hdl *bbm_hdl = priv;
    if (type == CTP_CLI_RECV_MSG) {
        if (strstr(topic, "FORWARD_MEDIA_FILES_LIST")) {
            ret = json_parse_to_path(parm_list, bbm_hdl->vf_list);
            ctp_recv_cb_action(ACTION_BBM_FILE_LIST_CREATE, priv, NULL);
        } else if (strstr(topic, "SD_STATUS")) {
            int status = json_parse_sd_status(parm_list);
            //offline
            if (!status) {
                printf("tx sd offline \n");
                ctp_recv_cb_action(ACTION_BBM_TX_SD_OFFLINE, priv, NULL);
            }
        } else if (strstr(topic, "APP_ACCESS")) {

        } else if (strstr(topic, "VIDEO_FINISH") || strstr(topic, "PHOTO_CTRL")) {
            char fname[32];
            ret = json_parse_video_finish(parm_list, fname);
            if (!ret) {
                printf("update file name list \n");
                ctp_recv_cb_action(ACTION_BBM_FILE_LIST_UPDATE, priv, fname);
            }
        } else if (strstr(topic, "OPEN_RT_STREAM")) {
            ret = json_parse_err_value(parm_list);
            if (ret == CTP_RT_OPEN_FAIL) {
                printf(" open rt stream err :%d \n", ret);
                bbm_ctp_send_rt_start(priv);
            } else {

            }

        }  else if (strstr(topic, "OPEN_REC")) {
            ret = json_parse_err_value(parm_list);
            if (ret == CTP_REC_OPEN_FAIL) {
                printf(" open rec err :%d \n", ret);
                ctp_recv_cb_action(ACTION_BBM_TX_START_REC_ERR, priv, NULL);
            }

        } else {
            /* printf("This msg not deal:topic:%s content:%s\n", topic, parm_list); */
        }
    } else if (type == CTP_CLI_DISCONNECT) {
        //TODO
    }


    return 0;
}

int bbm_ctp_send_access(void *ctp_cli_hdl)
{
    int ret = 0;
    const char topic_1[] = {"APP_ACCESS"};
    //区分BBM_RX和手机
    const char content_1[] = {"{\"op\":\"PUT\",\"param\":{\"type\":\"99\",\"ver\":\"20700\"}}"};

    printf("ctp send access \n");

    if (!ctp_cli_hdl) {
        printf("ctp client hdl invalid\n");
        return -1;
    }

    ret = ctp_cli_send(ctp_cli_hdl, topic_1, content_1);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_1);
        return ret;
    }


    return ret;
}

int bbm_ctp_send_modify_txrate(void *ctp_cli_hdl, int txrate)
{
    int ret = 0;
    char content_1[128];
    const char topic_1[] = {"MODIFY_TXRATE"};
    sprintf(content_1, "{\"op\":\"PUT\",\"param\":{\"txrate\":\"%d\"}}", txrate);

    printf("ctp send txrate val :%d  \n", txrate);

    if (!ctp_cli_hdl) {
        printf("ctp client hdl invalid\n");
        return -1;
    }

    ret = ctp_cli_send(ctp_cli_hdl, topic_1, content_1);
    if (ret) {
        printf("ctp_cli_send :%s err\n", topic_1);
        return ret;
    }

    return ret;
}

void ctp_alive_timer_cb(void *priv)
{
    struct bbm_client_hdl *bbm_hdl = priv;
    const char topic_0[] = {"KEEP_ALIVE_INTERVAL"};
    const char content_0[] = {"{\"op\":\"GET\"}"};

    if (!bbm_hdl || !bbm_hdl->ctp_cli_hdl) {
        return;
    }

    if (ctp_cli_send(bbm_hdl->ctp_cli_hdl, topic_0, content_0)) {
        printf("ctp send:%s err\n", topic_0);
    }
}

int bbm_ctp_client_init(void **ctp_cli_hdl, u32 dest_ip_addr, void *priv)
{
    int ret;
    struct sockaddr_in dest_addr = {0};
    void *hdl = NULL;
    struct bbm_client_hdl *bbm_hdl = priv;
    static int id = 1;

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = dest_ip_addr;
    dest_addr.sin_port = htons(CTP_CMD_PORT);

    os_sem_create(&bbm_hdl->ctp_msg_sem, 0);

    hdl = ctp_cli_reg(id++, &dest_addr, bbm_ctp_recv_callback, priv);

    if (hdl == NULL) {
        printf("\n----ctp_cli_reg err----\n");
        os_sem_del(&bbm_hdl->ctp_msg_sem, OS_DEL_ALWAYS);
        return -1;
    }

    *ctp_cli_hdl = hdl;

    bbm_ctp_send_access(hdl);

#if 0
    if (bbm_hdl->alive_timer) {
        sys_timer_del(bbm_hdl->alive_timer);
        bbm_hdl->alive_timer = 0;
    }

    bbm_hdl->alive_timer = sys_timer_add_to_task("app_core", priv, ctp_alive_timer_cb, 1000);
    if (!bbm_hdl->alive_timer) {
        printf("ctp alive timer add err \n");
        ctp_cli_unreg(hdl);
        os_sem_del(&bbm_hdl->ctp_msg_sem, OS_DEL_ALWAYS);
        *ctp_cli_hdl = NULL;
        return -1;
    }
#endif

    return 0;
}

int bbm_ctp_client_exit(void **ctp_cli_hdl)
{
    void *hdl = *ctp_cli_hdl;

    struct bbm_client_hdl *bbm_hdl = ctp_cli_get_hdl_priv(hdl);
    if (!bbm_hdl) {
        printf(" cli get priv err \n");
        return -1;
    }

    if (bbm_hdl->alive_timer) {
        sys_timer_del(bbm_hdl->alive_timer);
        bbm_hdl->alive_timer = 0;
    }

    bbm_ctp_file_exit(bbm_hdl);

    ctp_cli_unreg(hdl);
    os_sem_del(&bbm_hdl->ctp_msg_sem, OS_DEL_ALWAYS);

    *ctp_cli_hdl = NULL;
    return 0;
}


