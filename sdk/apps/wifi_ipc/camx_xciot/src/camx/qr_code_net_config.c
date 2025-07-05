#include "json_c/json.h"
#include "asm/jpeg_codec.h"
#include "qrcode/qrcode.h"
#include "json_c/json_tokener.h"
#include "mbedtls/base64.h"
#include "get_yuv_data.h"



typedef struct net_cfg_info {
    char ssid[33];
    char pwd[64];
    char vcode[13];
} NET_CFG_INFO;

static void *decoder = NULL;
static NET_CFG_INFO info;

void set_net_cfg_info(char *ssid, char *pwd, char *vcode)
{
    if (ssid) {
        strcpy(info.ssid, ssid);
    }
    if (pwd) {
        strcpy(info.pwd, pwd);
    }
    if (vcode) {
        strcpy(info.vcode, vcode);
    }

}

int get_net_cfg_info(char *ssid, char *pwd, char *vcode)
{
    if (!info.ssid[0]) {
        return -1;
    }
    if (ssid) {
        strcpy(ssid, info.ssid);
    }
    if (pwd) {
        strcpy(pwd, info.pwd);
    }
    if (vcode) {
        strcpy(vcode, info.vcode);
    }
    return 0;
}


void qrcode_process(char *inputFrame)
{
    char *buf;
    int buf_size = 0;
    char ssid[33];
    char pwd[64];
    char vcode[13];
    int ssid_len;
    int pwd_len;
    int offset = 0;
    int enc_type = 0;

    if (!decoder) {
        log_e("qrcode not init");
        return;
    }

    //md_detected：是否检测到运动物体
    int md_detected = 0;
    qrcode_detectAndDecode(decoder, inputFrame, &md_detected);

    qrcode_get_result(decoder, &buf, &buf_size, &enc_type);

    if (buf_size) {
        printf("\n buf================%s \n", buf);
        ssid_len = ((buf[offset] - '0') * 10) + (buf[offset + 1] - '0');
        int min_remain = buf_size - 2 - ssid_len - 2 - 0;//(默认没有密码)
        printf("\n ssid_len = %d min_remain = %d\n", ssid_len, min_remain);
        if (ssid_len > 32 || min_remain  < 6) {
            return;
        }
        memcpy(ssid, buf + 2, ssid_len);
        ssid[ssid_len] = 0;
        offset = 2 + ssid_len;
        pwd_len = ((buf[offset] - '0') * 10) + (buf[offset + 1] - '0');
        min_remain = buf_size - 2 - ssid_len - 2 - pwd_len;
        printf("\n pwd_len = %d min_remain = %d\n", pwd_len, min_remain);
        if (pwd_len > 63 || min_remain < 6) {
            return;
        }
        memcpy(pwd, buf + 2 + ssid_len + 2, pwd_len);
        pwd[pwd_len] = 0;

        memcpy(vcode, buf + 2 + ssid_len + 2 + pwd_len, buf_size - (2 + ssid_len + 2 + pwd_len));

        vcode[buf_size - (2 + ssid_len + 2 + pwd_len)] = 0;
        if (decoder) {
            qrcode_deinit(decoder);
            decoder = NULL;
        }
        printf("\nssid =  %s pwd =  %s vcode =  %s\n", ssid, pwd, vcode);
        void set_net_cfg_info(char *ssid, char *pwd, char *vcode);
        set_net_cfg_info(ssid, pwd, vcode);
        camx_uwifi_sta_connect(ssid, pwd, 1);


    }
}

void qr_net_cfg_init(void)
{
    //不镜像
    decoder = qrcode_init(YUV_DATA_WIDTH, YUV_DATA_HEIGHT, YUV_DATA_WIDTH, QRCODE_MODE_NORMAL/* QRCODE_MODE_FAST*/, 60, 2, 0);
    //垂直镜像
    //decoder = qrcode_init(YUV_DATA_WIDTH, YUV_DATA_HEIGHT, YUV_DATA_WIDTH, QRCODE_MODE_NORMAL/* QRCODE_MODE_FAST*/, 60, 2,1);
    //水平镜像
    //decoder = qrcode_init(YUV_DATA_WIDTH, YUV_DATA_HEIGHT, YUV_DATA_WIDTH, QRCODE_MODE_NORMAL/* QRCODE_MODE_FAST*/, 60, 2,2);
    if (!decoder) {
        printf("\n qrdecode init err\n");
    }

    get_qr_yuv_init(qrcode_process);

}


void qr_net_cfg_uninit(void)
{
    get_qr_yuv_uninit();
}
