#include "system/includes.h"
#include "server/audio_server.h"
#include "baby_monitor.h"

static OS_SEM  bbm_audio_enc_sem;
static struct server *audio_enc_server;
static u8 *audio_enc_buf;

struct lbuf_data_head {
    int len;
    u8 data[0];
};

static struct lbuff_head *lbuf_handle;


//编码器输出PCM数据
static int vfs_audio_enc_fwrite(void *file, void *data, u32 len)
{
    struct lbuf_data_head *lbuf_data = lbuf_alloc(lbuf_handle, len);
    if (!lbuf_data) {
        printf("bbm enc lbuf_alloc err \n");
        return len;
    }

    lbuf_data->len = len;
    memcpy(lbuf_data->data, data, len);
    lbuf_push(lbuf_data, BIT(0));
    os_sem_post(&bbm_audio_enc_sem);

    //此回调返回0录音就会自动停止
    return len;
}

static int vfs_audio_enc_fread(void *file, void *data, u32 len)
{
    return 0;
}

static int vfs_audio_enc_fclose(void *file)
{
    return 0;
}

static int vfs_audio_enc_flen(void *file)
{
    return 0;
}

static const struct audio_vfs_ops vfs_audio_enc_ops = {
    .fwrite = vfs_audio_enc_fwrite,
    .fread  = vfs_audio_enc_fread,
    .fclose = vfs_audio_enc_fclose,
    .flen   = vfs_audio_enc_flen,
};


int bbm_audio_enc_get_data(u8 *data_buf)
{
    int ret;
    struct lbuf_data_head *lbuf_data = lbuf_pop(lbuf_handle, BIT(0));
    while (!lbuf_data) {
        ret = os_sem_pend(&bbm_audio_enc_sem, 100);
        if (ret) {
            printf("bbm enc lbuf pop err");
            return 0;
        }
        lbuf_data = lbuf_pop(lbuf_handle, BIT(0));
    }
    memcpy(data_buf, lbuf_data->data, lbuf_data->len);
    lbuf_free(lbuf_data);

    return lbuf_data->len;
}

int bbm_audio_enc_init(void)
{
    union audio_req req = {0};
    int err;

    os_sem_create(&bbm_audio_enc_sem, 0);

    audio_enc_server = server_open("audio_server", "enc");
    if (!audio_enc_server) {
        printf("open audio_enc_server fail");
        goto __err;
    }

    audio_enc_buf = (u8 *)malloc(AUDIO_RX_ENC_BUF_MAX_LEN);
    if (audio_enc_buf == NULL) {
        printf("audio_enc_buf malloc fail");
        goto __err;

    }
    lbuf_handle = lbuf_init(audio_enc_buf, AUDIO_RX_ENC_BUF_MAX_LEN, 4, sizeof(struct lbuf_data_head));

    req.enc.frame_size = AUDIO_RX_ENC_FRAME_SIZE;
    req.enc.output_buf_len = 64 * 1024; //底层缓冲buf至少设成3倍frame_size
    req.enc.cmd = AUDIO_ENC_OPEN;
    req.enc.channel = 1;
    req.enc.volume =  100;
    req.enc.sample_rate = AUDIO_RX_ENC_SAMPLE_RATE;
    req.enc.format = "pcm";
    req.enc.sample_source = "mic";
    req.enc.vfs_ops = &vfs_audio_enc_ops;

    //回声消除,默认使用软件的
    //如要改动其他采样率或硬件回声消除请查看开源文档
    req.enc.aec_enable = 1;
    struct aec_s_attr aec_param = {0};
    req.enc.aec_attr = &aec_param;

    extern void get_cfg_file_aec_config(struct aec_s_attr * aec_param);
    get_cfg_file_aec_config(&aec_param);

    if (aec_param.EnableBit == 0) {
        req.enc.aec_enable = 0;
        req.enc.aec_attr = NULL;
    }
    aec_param.wideband = 0;
    aec_param.hw_delay_offset = 75;


    err = server_request(audio_enc_server, AUDIO_REQ_ENC, &req);
    if (err) {
        goto __err;
    }

    return 0;

__err:
    if (audio_enc_server) {
        req.enc.cmd = AUDIO_ENC_CLOSE;
        server_request(audio_enc_server, AUDIO_REQ_ENC, &req);

        server_close(audio_enc_server);
        audio_enc_server = NULL;
    }
    if (audio_enc_buf) {
        free(audio_enc_buf);
        audio_enc_buf = NULL;
    }

    os_sem_del(&bbm_audio_enc_sem, OS_DEL_ALWAYS);

    return -1;
}

int bbm_audio_enc_exit(void)
{
    union audio_req req = {0};

    if (audio_enc_server) {
        req.enc.cmd = AUDIO_ENC_CLOSE;
        server_request(audio_enc_server, AUDIO_REQ_ENC, &req);

        server_close(audio_enc_server);
        audio_enc_server = NULL;
    }
    if (audio_enc_buf) {
        free(audio_enc_buf);
        audio_enc_buf = NULL;
    }

    os_sem_del(&bbm_audio_enc_sem, OS_DEL_ALWAYS);

    return 0;
}


