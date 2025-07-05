#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#include "app_core.h"
#include "app_config.h"
#include "action.h"
#include "ui.h"
#include "baby_monitor.h"
#include "asm/jpeg_codec.h"
#include "asm/hwi.h"
#include "system/includes.h"
#include "video_ioctl.h"
#include "video.h"
#include "pipeline_core.h"
#include "asm/jldma2d.h"
#endif

#if !LV_USE_GUIBUILDER_SIMULATOR

#define IMG_W                192
#define IMG_H                160
#define MAX_FILE_SIZE        100*1024
#define ONE_PAGE_MAX_NUM     6   //一页文件数量
#define THUMB_DEC_TASK_NAME  "FILE_BROWSER_THUMB_DEC_TASK"

struct file_browser_handle {
    u8 *file_buf_list[ONE_PAGE_MAX_NUM];
    int file_buf_len_list[ONE_PAGE_MAX_NUM];

    u8 *img_buf_list[ONE_PAGE_MAX_NUM];
    lv_img_dsc_t image_dsc_list[ONE_PAGE_MAX_NUM];


    char **file_list;
    int cur_page;
    int file_total_num;
    int file_total_page;
    int file_cur_page;
    int file_cur_page_num;
    int to_play_page;

    u8 deleting;
    file_entry *del_selected_files;

    int thumb_dec_task_pid;

    struct net_ctp_thumb thumb_data;

    OS_SEM pipe_sem;
    pipe_core_t *pipe_core;

    char full_path[128];

};
static struct file_browser_handle file_hdl;
#define __this (&file_hdl)


static void thumb_dec_task(void);
static void jpeg2yuv_pipeline_uninit(void);
static int file_browser_screen_load(void);
static int file_browser_screen_unload(void);


int gui_bbm_start_file_browser(void)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_START_FILE_BROWSER;
    sprintf(__this->full_path, "%s%d/", gui_bbm_get_cur_dev_path(), gui_bbm_get_cur_dir_ch());
    it.data = __this->full_path;
    return start_app(&it);
}

int gui_bbm_stop_file_browser(void)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_STOP_FILE_BROWSER;
    it.data = __this->full_path;

    return start_app(&it);
}

int gui_bbm_get_file_num(int *file_num)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_GET_FILE_NUM;
    it.data = __this->full_path;
    it.exdata = file_num;

    return start_app(&it);
}

int gui_bbm_get_file_list(void)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_GET_FILE_LIST;
    it.data = __this->full_path;
    it.exdata = &__this->file_list;

    return start_app(&it);
}

int gui_bbm_file_to_play(int index)
{
    int list_index = (__this->file_cur_page - 1) * ONE_PAGE_MAX_NUM + index;
    gui_bbm_set_cur_play_index(list_index);

    __this->to_play_page = __this->file_cur_page;

    return 0;
}

int gui_bbm_file_reset_to_play_page(void)
{
    __this->to_play_page = 0;
    return 0;
}

int bbm_get_file_thumb_req(int index, int file_num)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_GET_FILE_THUMB_REQ;

    __this->thumb_data.start_index = index;
    __this->thumb_data.file_num = file_num;
    __this->thumb_data.file_buf_list = __this->file_buf_list;
    __this->thumb_data.file_buf_len_list = __this->file_buf_len_list;

    it.data = __this->full_path;
    it.exdata = &__this->thumb_data;
    start_app(&it);

    return 0;
}


// 添加文件到哈希表
static void add_file(file_entry **hash_table, int file_no)
{
    file_entry *entry = malloc(sizeof(file_entry));
    if (entry == NULL) {

    }
    entry->file_no = file_no;
    HASH_ADD_INT(*hash_table, file_no, entry);
}

// 查找文件是否已选中
static file_entry *find_file(file_entry *hash_table, int file_no)
{
    file_entry *entry;
    HASH_FIND_INT(hash_table, &file_no, entry);
    return entry;
}

// 从哈希表中删除文件
static void delete_file(file_entry **hash_table, int file_no)
{
    file_entry *entry = find_file(*hash_table, file_no);
    if (entry) {
        HASH_DEL(*hash_table, entry);
        free(entry);
    }
}

// 释放整个哈希表
static void free_all(file_entry **hash_table)
{
    file_entry *current, *tmp;
    HASH_ITER(hh, *hash_table, current, tmp) {
        HASH_DEL(*hash_table, current);
        free(current);
    }
}

static int file_brwser_enter_del(void)
{
    int i;
    lvgl_module_msg_send_value(GUI_FILE_BROWSER_MSG_ID_CHECK_BOX_DEL, 1, 0);

    for (i = 0; i < ONE_PAGE_MAX_NUM; i++) {
        lvgl_module_msg_send_value(GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX0 + i, 0, 0);
    }

    __this->deleting = 1;

    return 0;
}

static int file_brwser_exit_del(void)
{
    lvgl_module_msg_send_value(GUI_FILE_BROWSER_MSG_ID_CHECK_BOX_DEL, 0, 0);

    if (__this->del_selected_files) {
        free_all(&__this->del_selected_files);
        __this->del_selected_files = NULL;
    }

    __this->deleting = 0;

    return 0;
}

static int flush_del_check_box(void)
{
    int i;
    int list_index, list_index_start = (__this->file_cur_page - 1) * ONE_PAGE_MAX_NUM;

    for (i = 0; i < __this->file_cur_page_num; i++) {
        list_index = list_index_start + i;
        if (find_file(__this->del_selected_files, list_index)) {
            //模型ID对应
            lvgl_module_msg_send_value(GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX0 + i, 1, 0);
        } else {
            //模型ID对应
            lvgl_module_msg_send_value(GUI_FILE_BROWSER_MSG_ID_SEL_CHECK_BOX0 + i, 0, 0);
        }
    }

    return 0;
}

void gui_bbm_add_del_file(int index)
{
    int list_index = (__this->file_cur_page - 1) * ONE_PAGE_MAX_NUM + index;
    printf("add del file:%d ", list_index);

    add_file(&__this->del_selected_files, list_index);
}

void gui_bbm_remove_del_file(int index)
{
    int i;
    int list_index = (__this->file_cur_page - 1) * ONE_PAGE_MAX_NUM + index;
    printf("remove del file:%d ", list_index);

    delete_file(&__this->del_selected_files, list_index);
}

static void gui_bbm_file_confirm_delete(void)
{
    struct intent it;
    init_intent(&it);
    it.name	= "baby_monitor";
    it.action = ACTION_BBM_DELETE_FILE;
    it.data = __this->full_path;
    it.exdata = __this->del_selected_files;
    start_app(&it);

    file_browser_screen_unload();
    file_browser_screen_load();
}

static void gui_bbm_file_cancel_delete(void)
{
    file_brwser_exit_del();
}

//入口,click回调
int gui_bbm_file_del(void)
{
    if (__this->deleting) {
        char lab[128];
        int cnt = HASH_COUNT(__this->del_selected_files);
        if (cnt > 0) {
            sprintf(lab, "Are you sure you want to delete these %d files?", cnt);
        } else {
            sprintf(lab, "Are you sure you want to delete \n All files? !!!!!!");
        }
        gui_set_sys_options_yes_cb(gui_bbm_file_confirm_delete);
        gui_set_sys_options_no_cb(gui_bbm_file_cancel_delete);
        post_home_msg_to_ui("show_sys_options", lab);
    } else {
        file_brwser_enter_del();
    }

    return 0;
}

static int file_browser_update_file_num(void)
{
    char *ptr = lvgl_module_msg_get_ptr(GUI_FILE_BROWSER_MSG_ID_FILE_NUM, 24);
    u16 cur_num = __this->file_cur_page * ONE_PAGE_MAX_NUM;
    cur_num = cur_num > __this->file_total_num ? __this->file_total_num : cur_num;
    sprintf(ptr, "%d\n/\n%d", cur_num, __this->file_total_num);
    lvgl_module_msg_send_ptr(ptr, 0);
}

static int file_browser_update_file_cont(void)
{
    int i;
    int ret = 0;
    int start_index = (__this->file_cur_page - 1) * ONE_PAGE_MAX_NUM;
    int msg[3];

    //先发送获取缩略图(jpg)请求,解码线程中信号量同步
    //post解码线程.
    os_taskq_del_type(THUMB_DEC_TASK_NAME, Q_MSG);
    os_taskq_post_type(THUMB_DEC_TASK_NAME, Q_MSG, 1, msg);

    lv_ui_file_browser *_ui_file_browser = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_FILE_BROWSER);
    if (!_ui_file_browser) {
        printf("ui get scr NULL !\n");
        return -1;
    }

    for (i = 0; i < __this->file_cur_page_num; i++) {

        lv_obj_t *contain = lv_obj_get_child(_ui_file_browser->file_browser_browser_cont, i);
        lv_obj_clear_flag(contain, LV_OBJ_FLAG_HIDDEN);

        //图片控件
        lv_obj_t *img = lv_obj_get_child(contain, 0);
        lv_img_set_src(img, &__this->image_dsc_list[i]);

        //文件名控件
        lv_obj_t *lab = lv_obj_get_child(contain, 1);
        if (__this->file_list) {
            char *path = __this->file_list[start_index + i];
            char *file_name = strrchr(path, '/');
            if (file_name) {
                lv_label_set_text(lab, ++file_name);
            } else {
                lv_label_set_text(lab, path);
            }
        }
    }

    for (i = __this->file_cur_page_num; i < ONE_PAGE_MAX_NUM; i++) {
        lv_obj_t *contain = lv_obj_get_child(_ui_file_browser->file_browser_browser_cont, i);
        lv_obj_add_flag(contain, LV_OBJ_FLAG_HIDDEN);
    }


    return ret;
}

static void cal_cur_page_file_num(void)
{
    if (__this->file_cur_page < __this->file_total_page) {
        __this->file_cur_page_num = ONE_PAGE_MAX_NUM;
    } else {
        __this->file_cur_page_num = __this->file_total_num - (__this->file_cur_page - 1) * ONE_PAGE_MAX_NUM;
    }
}

static void file_browser_update(void)
{
    cal_cur_page_file_num();

    if (__this->deleting) {
        flush_del_check_box();
    }

    file_browser_update_file_num();
    file_browser_update_file_cont();
}

static int file_browser_buf_init(void)
{
    int i;
    for (i = 0; i < ONE_PAGE_MAX_NUM; i++) {
        __this->file_buf_list[i] = malloc(MAX_FILE_SIZE); //jpg
        __this->img_buf_list[i] = malloc(IMG_W * IMG_H * 2);        //rgb16

        //lvgl img
        memset(__this->img_buf_list[i], 0x00, IMG_W * IMG_H * 2);
        __this->image_dsc_list[i].header.always_zero = 0;
        __this->image_dsc_list[i].header.w = IMG_W;
        __this->image_dsc_list[i].header.h = IMG_H;
        __this->image_dsc_list[i].data_size = IMG_W * IMG_H * 2;
        __this->image_dsc_list[i].header.cf = LV_IMG_CF_TRUE_COLOR;
        __this->image_dsc_list[i].data = __this->img_buf_list[i];

        if ((!__this->file_buf_list[i]) || (!__this->img_buf_list[i])) {
            printf("file browser buf init err\n");
            goto err;
        }
    }

    return 0;
err:
    for (i = 0; i < ONE_PAGE_MAX_NUM; i++) {
        if (__this->file_buf_list[i]) {
            free(__this->file_buf_list[i]);
            __this->file_buf_list[i] = NULL;
        }
        if (__this->img_buf_list[i]) {
            free(__this->img_buf_list[i]);
            __this->img_buf_list[i] = NULL;
        }
    }
    return -1;
}


static int file_browser_buf_exit(void)
{
    int i;
    for (i = 0; i < ONE_PAGE_MAX_NUM; i++) {
        if (__this->file_buf_list[i]) {
            free(__this->file_buf_list[i]);
            __this->file_buf_list[i] = NULL;
        }
        if (__this->img_buf_list[i]) {
            free(__this->img_buf_list[i]);
            __this->img_buf_list[i] = NULL;
        }
    }
}


int gui_bbm_next_page(void)
{
    __this->file_cur_page++;
    if (__this->file_cur_page > __this->file_total_page) {
        __this->file_cur_page = __this->file_total_page;
        return -1;
    }

    file_browser_update();

    return 0;
}

int gui_bbm_prev_page()
{
    __this->file_cur_page--;
    if (__this->file_cur_page < 1) {
        __this->file_cur_page = 1;
        return -1;
    }

    file_browser_update();

    return 0;
}

static int gui_bbm_thumb_task_init(void)
{
    return thread_fork(THUMB_DEC_TASK_NAME, 10, 1024, 1024, &__this->thumb_dec_task_pid, thumb_dec_task, NULL);
}


static void gui_bbm_thumb_task_exit(void)
{
    int msg = 1;
    if (__this->thumb_dec_task_pid) {
        os_taskq_del_type(THUMB_DEC_TASK_NAME, Q_MSG);
        os_sem_post(&__this->thumb_data.sem);
        os_taskq_post_type(THUMB_DEC_TASK_NAME, Q_USER, 1, &msg);
        thread_kill(&__this->thumb_dec_task_pid, KILL_WAIT);
        __this->thumb_dec_task_pid = 0;
    }
}


static int file_browser_screen_load(void)
{
    int ret;
    char *lab;

    //开启ctp文件流程
    ret = gui_bbm_start_file_browser();
    if (ret) {
        post_home_msg_to_ui("back_home_page", 0);
        lab = "File Load Error !";
        post_home_msg_to_ui("show_sys_prompt", lab);

        return -1;
    }

    //获取文件数量
    ret = gui_bbm_get_file_num(&__this->file_total_num);
    if (ret) {
        post_home_msg_to_ui("back_folder_sel_page", 0);
        lab = "Folder is empty !";
        post_home_msg_to_ui("show_sys_prompt", lab);
        return -1;
    }
    //获取文件名列表
    ret = gui_bbm_get_file_list();
    if (ret) {
        post_home_msg_to_ui("back_folder_sel_page", 0);
        lab = "Folder is empty !";
        post_home_msg_to_ui("show_sys_prompt", lab);
        return -1;
    }

    //内存申请
    ret = file_browser_buf_init();
    if (ret) {
        post_home_msg_to_ui("back_home_page", 0);
        lab = "File Load Error !";
        post_home_msg_to_ui("show_sys_prompt", lab);
        return -1;
    }
    //缩略图解码线程
    gui_bbm_thumb_task_init();

    //缩略图同步信号量
    os_sem_create(&__this->thumb_data.sem, 0);

    __this->file_total_page = ceil((float)__this->file_total_num / ONE_PAGE_MAX_NUM);
    if (__this->to_play_page) {
        __this->file_cur_page = __this->to_play_page;
        __this->to_play_page = 0;
    } else {
        __this->file_cur_page = 1;
    }

    //更新UI
    file_browser_update();

    return 0;
}

static int file_browser_screen_unload(void)
{
    //关闭ctp文件流程
    gui_bbm_stop_file_browser();

    //关闭缩略图解码线程
    gui_bbm_thumb_task_exit();

    //释放内存
    file_browser_buf_exit();
    //缩略图信号量
    os_sem_del(&__this->thumb_data.sem, OS_DEL_ALWAYS);

    file_brwser_exit_del();

    return 0;
}


static int gui_src_action_file_browser(int action)
{
    int ret;

    switch (action) {
    case GUI_SCREEN_ACTION_LOAD:
        file_browser_screen_load();
        break;
    case GUI_SCREEN_ACTION_UNLOAD:
        file_browser_screen_unload();
        break;
    }
}
REGISTER_UI_SCREEN_ACTION_HANDLER(GUI_SCREEN_FILE_BROWSER)
.onchange = gui_src_action_file_browser,
};

static void clean_thumb_buf(void)
{
    int i;
    for (i = 0; i < ONE_PAGE_MAX_NUM; i++) {
        memset(__this->img_buf_list[i], 0x00, IMG_W * IMG_H * 2);
        memset(__this->file_buf_list[i], 0x00, MAX_FILE_SIZE);
    }
}

static void post_func_flush_img(void)
{
    lv_ui_file_browser *_ui_file_browser = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_FILE_BROWSER);

    if (_ui_file_browser && lv_obj_is_valid(_ui_file_browser->file_browser_browser_cont)) {
        lv_obj_invalidate(_ui_file_browser->file_browser_browser_cont);
    }
}

static void post_func_flush_lab(void)
{
    int i;
    lv_ui_file_browser *_ui_file_browser = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_FILE_BROWSER);
    if (_ui_file_browser && lv_obj_is_valid(_ui_file_browser->file_browser_browser_cont)) {
        for (i = 0; i < __this->file_cur_page_num; i++) {
            lv_obj_t *contain = lv_obj_get_child(_ui_file_browser->file_browser_browser_cont, i);
            //文件名控件
            lv_obj_t *lab = lv_obj_get_child(contain, 1);
            lv_label_set_text(lab, __this->thumb_data.file_name_buf[i]);
        }
        lv_obj_invalidate(_ui_file_browser->file_browser_browser_cont);
    }
}

static void thumb_dec_task(void)
{
    int res;
    int i;
    int msg[8];

    while (1) {
        res = os_task_pend("taskq", msg, ARRAY_SIZE(msg));

        switch (res) {
        case OS_TASKQ:
            switch (msg[0]) {
            case Q_MSG:
                clean_thumb_buf();
                int start_index = (__this->file_cur_page - 1) * ONE_PAGE_MAX_NUM;
                bbm_get_file_thumb_req(start_index, __this->file_cur_page_num);
                //等待获取jpg数据
                os_sem_pend(&__this->thumb_data.sem, 0);

                //todo
                //切换页面
                int cur_index = (__this->file_cur_page - 1) * ONE_PAGE_MAX_NUM;
                if (cur_index != start_index) {
                    break;
                }

                //本地模式
                if (!__this->file_list) {
                    lvgl_rpc_post_func(post_func_flush_lab, 0);
                }

                for (i = 0; i < __this->thumb_data.file_num; i++) {
                    u8 *jpeg_buf = __this->thumb_data.file_buf_list[i];
                    int jpeg_len = __this->thumb_data.file_buf_len_list[i];
                    u8 *rgb_buf = __this->img_buf_list[i];
                    jpeg2yuv_with_pipeline(jpeg_buf, jpeg_len, rgb_buf, IMG_W, IMG_H);
                }
                //刷新UI
                lvgl_rpc_post_func(post_func_flush_img, 0);
                break;
            case Q_USER:
                printf("bbm thumb dec task exit\n");
                goto exit;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

exit:
    jpeg2yuv_pipeline_uninit();
}


static int yuyv2rgb16_dma2d(u8 *yuv_buf, u8 *rgb_buf, int width, int height)
{
    int err;

    u32 in_format = JLDMA2D_FORMAT_YUV422_BT709;
    u32 out_format = JLDMA2D_FORMAT_RGB565;
    u32 dest_stride = width * dma2d_get_format_bpp(out_format) / 8;
    u32 src_stride = width * dma2d_get_format_bpp(in_format) / 8;
    err = jldma2d_format(rgb_buf, \
                         yuv_buf, \
                         dest_stride, \
                         src_stride, \
                         in_format, \
                         out_format, \
                         width, \
                         height, \
                         0, \
                         0);
    return err;
}

static void on_event2(const char *name, int type, void *arg)
{
    OS_SEM *sem = (OS_SEM *)arg;
    switch (type) {
    case EVENT_FRAME_DONE:
        if (!strncmp(name, "yuv", 3)) {
            os_sem_post(sem);
        }
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

static int jpeg2yuv_pipeline_init(struct video_format *f)
{
    pipe_filter_t *jpeg_dec_filter, *imc_filter, *rep_filter, *yuv_filter, *virtual_filter;
    os_sem_create(&__this->pipe_sem, 0);
    __this->pipe_core = pipeline_init(on_event2, &__this->pipe_sem);
    if (!__this->pipe_core) {
        printf("pipeline init err\n");
        return -1;
    }

    char *source_name = plugin_factory_find("virtual");

    __this->pipe_core->channel = plugin_source_to_channel(source_name);
    virtual_filter = pipeline_filter_add(__this->pipe_core, source_name);
    jpeg_dec_filter = pipeline_filter_add(__this->pipe_core, plugin_factory_find("jpeg_dec"));
    rep_filter = pipeline_filter_add(__this->pipe_core, plugin_factory_find("rep"));
    imc_filter = pipeline_filter_add(__this->pipe_core, plugin_factory_find("imc"));
    yuv_filter = pipeline_filter_add(__this->pipe_core, plugin_factory_find("yuv"));

    pipeline_param_set(__this->pipe_core, NULL, PIPELINE_SET_FORMAT, f);

    int out_format = FORMAT_YUV422_UYVY;
    pipeline_param_set(__this->pipe_core, NULL, PIPELINE_SET_SINK_OUT_FORMAT, (int)&out_format);

    int line_cnt = 16;
    pipeline_param_set(__this->pipe_core, NULL, PIPELINE_SET_BUFFER_LINE, (int)&line_cnt);

    pipeline_filter_link(virtual_filter, jpeg_dec_filter);

    pipeline_filter_link(jpeg_dec_filter, rep_filter);

    pipeline_filter_link(rep_filter, imc_filter);

    pipeline_filter_link(imc_filter, yuv_filter);

    pipeline_prepare(__this->pipe_core);

    pipeline_start(__this->pipe_core);
}

static void jpeg2yuv_pipeline_uninit(void)
{
    if (!__this->pipe_core) {
        return;
    }

    pipeline_stop(__this->pipe_core);

    pipeline_reset(__this->pipe_core);

    pipeline_uninit(__this->pipe_core);

    os_sem_del(&__this->pipe_sem, 0);
    __this->pipe_core = NULL;
}


static int jpeg2yuv_with_pipeline(u8 *jpeg_buf, int jpeg_len, u8 *img_buf, int dst_w, int dst_h)
{
    int err = 0;
    u8 *yuv_buf;
    static int last_width, last_height, last_format;

    struct jpeg_image_info info = {0};
    struct video_format f  = {0};
    int fmt;
    info.input.data.buf = jpeg_buf;
    info.input.data.len = jpeg_len;
    err = jpeg_decode_image_info(&info);
    if (err) {
        printf("jpeg_decode_image_info err:%d\n", err);
        goto exit;
    }
    switch (info.sample_fmt) {
    case JPG_SAMP_FMT_YUV444:
        fmt = VIDEO_PIX_FMT_YUV444;
        break;
    case JPG_SAMP_FMT_YUV422:
        fmt = VIDEO_PIX_FMT_YUV422;
        break;
    case JPG_SAMP_FMT_YUV420:
        fmt = VIDEO_PIX_FMT_YUV420;
        break;
    default:
        printf("input err fmt\n");
        goto exit;
        break;
    }
    f.src_width = info.width;
    f.src_height = info.height;
    f.win.width = dst_w;
    f.win.height = dst_h;
    f.type = VIDEO_BUF_TYPE_VIDEO_PLAY;
    f.pixelformat = VIDEO_PIX_FMT_JPEG | fmt;
    f.private_data = "fb5";

    if ((last_height != info.height) || (last_width != info.width)
        || (last_format != fmt) || (__this->pipe_core == NULL)) {

        jpeg2yuv_pipeline_uninit();
        jpeg2yuv_pipeline_init(&f);
    }
    last_width = info.width;
    last_height = info.height;
    last_format = fmt;

    //设置jpeg buf
    struct video_cap_buffer buffer ;
    buffer.buf = jpeg_buf;
    buffer.size = jpeg_len;
    pipeline_param_set(__this->pipe_core, NULL, VIDIOC_RDBUF, &buffer);

    err = os_sem_pend(&__this->pipe_sem, 200);
    if (err) {
        log_e("jpeg2yuv timeout\n");
        goto exit;
    }
    printf("jpeg2yuv ok\n");

    //获取YUV
    pipeline_param_get(__this->pipe_core, NULL, PIPELINE_GET_YUV_BUF, &yuv_buf);
    if (!yuv_buf) {
        printf("get yuv buf err\n");
        err = -EFAULT;
        goto exit;
    }

    //yuv to rgb
    yuyv2rgb16_dma2d(yuv_buf, img_buf, dst_w, dst_h);

exit:
    if (err) {
        memset(img_buf, 0x00, dst_w * dst_h * 2);
    }
    return err;
}

static void update_file_browser_clickable(int disable_clickable)
{
    lv_ui_file_browser *_ui_file_browser = ui_get_scr_ptr(&guider_ui, GUI_SCREEN_FILE_BROWSER);
    if (!_ui_file_browser) {
        return;
    }

    lv_obj_t *objs[] = {
        _ui_file_browser->file_browser_file_cont1,
        _ui_file_browser->file_browser_file_cont2,
        _ui_file_browser->file_browser_file_cont3,
        _ui_file_browser->file_browser_file_cont4,
        _ui_file_browser->file_browser_file_cont5,
        _ui_file_browser->file_browser_file_cont6,
    };

    uint8_t cnt = sizeof(objs) / sizeof(objs[0]);

    if (disable_clickable) {
        /* 禁用点击：清除控件的点击标志，并将控件从组中移除 */
        for (uint8_t i = 0; i < cnt; i++) {
            if (objs[i] && lv_obj_is_valid(objs[i])) {
                lv_obj_clear_flag(objs[i], LV_OBJ_FLAG_CLICKABLE);
                lv_group_remove_obj(objs[i]);
            }
        }
    } else {
        /* 启用点击：添加控件的点击标志，并将控件加入默认组 */
        lv_group_t *def_group = lv_group_get_default();
        if (def_group == NULL) {
            def_group = lv_group_create();
        }
        for (uint8_t i = 0; i < cnt; i++) {
            if (objs[i] && lv_obj_is_valid(objs[i])) {
                lv_obj_add_flag(objs[i], LV_OBJ_FLAG_CLICKABLE);
                lv_group_add_obj(def_group, objs[i]);
            }
        }
    }
}

int gui_file_browser_msg_check_box_del_cb(gui_msg_action_t access, gui_msg_data_t *data, gui_msg_data_type_t type)
{

    if (access == GUI_MSG_ACCESS_SET) {
        update_file_browser_clickable(data->value_int);
    } else if (access == GUI_MSG_ACCESS_GET) {
        data->value_int = 0;
    }

    return 0;
}

REGISTER_UI_MODULE_EVENT_HANDLER(GUI_FILE_BROWSER_MSG_ID_CHECK_BOX_DEL)
.onchange = gui_file_browser_msg_check_box_del_cb,
};


#endif




