#include "system/includes.h"
#include "app_config.h"
#include "os/os_api.h"
#include "system/init.h"
#include "asm/includes.h"
#include "server/audio_server.h"
#include "server/server_core.h"
#include "generic/circular_buf.h"
#include "server/ctp_server.h"


#if TCFG_HOST_AUDIO_ENABLE
#include "usb/host/usb_host.h"
#include "usb_ctrl_transfer.h"
#include "usb_bulk_transfer.h"
#include "audio.h"
#include "usb_config.h"

#define LOG_TAG_CONST       USB
#define LOG_TAG             "[AUDIO]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
/* #define LOG_DUMP_ENABLE */
#define LOG_CLI_ENABLE
#include "debug.h"
#endif



#define CACHE_BUF_LEN (8 * 1024)

struct {
    struct server *dec_server;
    u8 *cache_buf;
    cbuffer_t save_cbuf;
    volatile u8 run_flag;
} audio;

#define __this (&audio)


#if TCFG_HOST_AUDIO_ENABLE

int xc_talkback_read(void *data, u32 len)
{
    u32 rlen;

    do {
        rlen = cbuf_read(&__this->save_cbuf, data, len);
        if (rlen == len) {
            /* put_buf(data, 32); */
            break;
        }

        if (!__this->run_flag) {
            return 0;
        }
    } while (__this->run_flag);

    return len;
}


#endif




static int vfs_fread(void *file, void *data, u32 len)
{
    u32 rlen;

    do {
        rlen = cbuf_read(&__this->save_cbuf, data, len);
        if (rlen == len) {
            /* put_buf(data, 32); */
            break;
        }

        if (!__this->run_flag) {
            return 0;
        }
    } while (__this->run_flag);

    return len;
}

static int vfs_fclose(void *file)
{
    return 0;
}

static int vfs_flen(void *file)
{
    return 0;
}

static const struct audio_vfs_ops vfs_ops = {
    .fwrite = NULL,
    .fread  = vfs_fread,
    .fclose = vfs_fclose,
    .flen   = vfs_flen,
};


int xc_talkback_start(void)
{
    int err;

    union audio_req req = {0};

    if (__this->run_flag) {
        return -1;
    }

    __this->run_flag = 1;

    __this->cache_buf = (u8 *)malloc(CACHE_BUF_LEN);
    if (__this->cache_buf == NULL) {
        goto __err;
    }
    cbuf_init(&__this->save_cbuf, __this->cache_buf, CACHE_BUF_LEN);



#if !TCFG_HOST_AUDIO_ENABLE
    if (!__this->dec_server) {
        __this->dec_server = server_open("audio_server", "dec");
        if (!__this->dec_server) {
            goto __err;
        }
    }

    memset(&req, 0, sizeof(union audio_req));

    req.dec.cmd             = AUDIO_DEC_OPEN;
    req.dec.volume          = 100;
    req.dec.output_buf      = NULL;
    req.dec.output_buf_len  = 4096;
    req.dec.channel         = 1;
    req.dec.sample_rate     = 8000;
    req.dec.priority        = 1;
    req.dec.vfs_ops         = &vfs_ops;
    req.dec.dec_type 		= "pcm";
    req.dec.sample_source   = "dac";

    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        goto __err;
    }

    req.dec.cmd = AUDIO_DEC_START;
    err = server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
    if (err) {
        goto __err;
    }
#endif


    return 0;


__err:
#if TCFG_HOST_AUDIO_ENABLE
    if (__this->dec_server) {
        server_close(__this->dec_server);
        __this->dec_server = NULL;
    }
#endif

    if (__this->cache_buf) {
        free(__this->cache_buf);
        __this->cache_buf = NULL;
    }

    __this->run_flag = 0;

    return -1;


}
int xc_talkback(unsigned char *buf, int len)
{
    if (!__this->run_flag) {
        return 0;
    }


    int rlen = cbuf_write(&__this->save_cbuf, buf, len);
    if (rlen == 0) {
        putchar('B');
        cbuf_clear(&__this->save_cbuf);
    }
    return 0;


}

void xc_talkback_stop(void)
{

    union audio_req req = {0};


    if (!__this->run_flag) {
        return;
    }

    __this->run_flag = 0;


#if !TCFG_HOST_AUDIO_ENABLE
    if (__this->dec_server) {
        req.dec.cmd = AUDIO_DEC_STOP;
        server_request(__this->dec_server, AUDIO_REQ_DEC, &req);
        server_close(__this->dec_server);
        __this->dec_server = NULL;
    }
#endif

    if (__this->cache_buf) {
        free(__this->cache_buf);
        __this->cache_buf = NULL;
    }


    return;
}

