#include "system/includes.h"
#include "pipeline_core.h"
#include "asm/jpeg_codec.h"

static void on_event(const char *name, int type, void *arg)
{
    switch (type) {
    case EVENT_FRAME_DONE:
        break;
    case EVENT_PREPARE_DONE:
        printf("PREPARE %s done", name);
        break;
    case EVENT_START_DONE:
        printf("START %s done", name);
        break;
    case EVENT_STOP_DONE:
        printf("STOP %s done", name);
        break;
    case EVENT_RESET_DONE:
        printf("RESET %s done", name);
        break;
    case EVENT_BW_FULL:
    case EVENT_BUFFER_FULL:
    case EVENT_SPEED_FULL:
    case EVENT_OSD_ERR:
    case EVENT_LINE_ERR:
        printf("err %s ", name);
        break;
    }
}

int bbm_pipe_disp_one_frame(pipe_core_t *pipeline_core, u8 *buf, int len)
{
    if (!pipeline_core) {
        return -1;
    }

    struct video_cap_buffer buffer;
    buffer.buf = buf;
    buffer.size = len;
    pipeline_param_set(pipeline_core, NULL, VIDIOC_RDBUF, &buffer);

    return 0;
}

int bbm_video_pipe_init(pipe_core_t **pipe_core, struct video_window *win, int src_w, int src_h)
{
    int ret;
    pipe_core_t *pipeline_core = NULL;
    pipe_filter_t *virtual_filter, *jpeg_dec_filter, *rep_filter, *imc_filter, *disp_filter, *sft_filter;

    struct video_format f = {0};

    f.src_width = src_w;
    f.src_height = src_h;
    f.type = VIDEO_BUF_TYPE_VIDEO_PLAY;
    f.pixelformat = VIDEO_PIX_FMT_JPEG | VIDEO_PIX_FMT_YUV420;
    memcpy(&f.win, win, sizeof(struct video_window));

    pipeline_core = pipeline_init(on_event, NULL);
    if (!pipeline_core) {
        printf("pipeline init err\n");
        return -1;
    }

    char *rep_name = NULL;
    char *source_name = plugin_factory_find("virtual");

    pipeline_core->channel = plugin_source_to_channel(source_name);
    virtual_filter = pipeline_filter_add(pipeline_core, source_name);

    //todo
    rep_name = plugin_factory_find("rep");
    if (rep_name) {
        rep_filter = pipeline_filter_add(pipeline_core, rep_name);
        jpeg_dec_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("jpeg_dec"));
        imc_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("imc"));
        disp_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("disp"));

        pipeline_param_set(pipeline_core, NULL, PIPELINE_SET_FORMAT, &f);

        int line_cnt = 16;
        pipeline_param_set(pipeline_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

        pipeline_filter_link(virtual_filter, jpeg_dec_filter);

        pipeline_filter_link(jpeg_dec_filter, rep_filter);

        pipeline_filter_link(rep_filter, imc_filter);

        pipeline_filter_link(imc_filter, disp_filter);
    } else {
        jpeg_dec_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("jpeg_dec"));
        sft_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("sft"));
        disp_filter = pipeline_filter_add(pipeline_core, plugin_factory_find("disp"));

        pipeline_param_set(pipeline_core, NULL, PIPELINE_SET_FORMAT, &f);

        f.three_way_type = 1;
        pipeline_param_set(pipeline_core, jpeg_dec_filter, PIPELINE_SET_FORMAT, &f);

        //TODO jpeg按行解
        int line_cnt = 16;
        pipeline_param_set(pipeline_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

        line_cnt = 0;
        pipeline_param_set(pipeline_core, sft_filter, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

        pipeline_filter_link(virtual_filter, jpeg_dec_filter);

        pipeline_filter_link(jpeg_dec_filter, sft_filter);

        pipeline_filter_link(sft_filter, disp_filter);

        line_cnt = 16;
        pipeline_param_set(pipeline_core, sft_filter, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);
    }

    pipeline_prepare(pipeline_core);

    pipeline_start(pipeline_core);

    *pipe_core = pipeline_core;

    return 0;
}



int bbm_video_pipe_exit(pipe_core_t **pipe_core)
{
    pipe_core_t *pipeline_core = *pipe_core;

    if (!pipeline_core) {
        return -1;
    }

    pipeline_stop(pipeline_core);

    pipeline_reset(pipeline_core);

    pipeline_uninit(pipeline_core);

    *pipe_core = NULL;

    return 0;
}

int bbm_video_pipe_set_zoom(pipe_core_t *pipe_core, void *arg)
{
    if (!pipe_core) {
        return -1;
    }
    return pipeline_param_set(pipe_core, NULL, VIDIOC_SET_DIS_CROP, arg);
}


