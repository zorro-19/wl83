#ifdef MEDIA_SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".rcsp_browser.data.bss")
#pragma data_seg(".rcsp_browser.data")
#pragma const_seg(".rcsp_browser.text.const")
#pragma code_seg(".rcsp_browser.text")
#endif
#include "rcsp_browser.h"
#include "app_config.h"
#include "rcsp.h"
#include "dev_manager.h"
#include "file_operate/file_bs_deal.h"
#include "rcsp_event.h"
#include "ble_rcsp_server.h"
#include "JL_rcsp_api.h"

#if RCSP_MODE && RCSP_FILE_OPT
#include "music/music_player.h"

#define FILE_BROWSE_BUF_LEN    			250//要小于RCSP MTU, 不要随意改大
#define FILE_BROWSE_NAME_MAX_LIMIT  	128//限制最大文件夹名称大小

#define FILE_BROWSE_TASK_NAME			"rcsp_file_bs"
#define MAX_DEEPTH 						9/* 0~9 deepth of system */


typedef enum {
    RCSPBrowserObjectTypeFolder = 0,
    RCSPBrowserObjectTypeFile,
} RCSPBrowserObjectType;

typedef enum {
    RCSPBrowserFileDataFormatUnicode = 0,
    RCSPBrowserFileDataFormatANSI,
} RCSPBrowserFileDataFormat;

static const char *dev_logo[] = {
    [RCSPDevMapUDISK] = "udisk0",
    [RCSPDevMapSD0] = "sd0",
    [RCSPDevMapSD1] = "sd1",
    [RCSPDevMapFLASH] = "virfat_flash",
    [RCSPDevMapFLASH_2] = "fat_nor",
};

#pragma pack(1)
struct __browser {
    u8 path_type;///
    u8 read_file_num;
    u16 start_num;
    u32 dev_handle;
    u16 path_len;
    u32 path_clust[MAX_DEEPTH];
};

struct JL_FILE_DATA {
    u8 type : 1;
    RCSPBrowserFileDataFormat format : 1;
    u8 device : 3;
    u8 reserve : 3;

    u32 clust;
    u16 file_num;
    u8 name_len;
    u8 file_data[0];
};
#pragma pack()



static const char dec_file_ext[][3] = {
#if (WATCH_FILE_TO_FLASH)
    {"ALL"},
    {'\0'},
#else // WATCH_FILE_TO_FLASH
#if (TCFG_DEC_MP3_ENABLE)
    {"MP1"},
    {"MP2"},
    {"MP3"},
#endif

#if (TCFG_DEC_WMA_ENABLE)
    {"WMA"},
#endif

#if (TCFG_DEC_WAV_ENABLE || TCFG_DEC_DTS_ENABLE)
    {"WAV"},
#endif

#if (TCFG_DEC_FLAC_ENABLE)
    {"FLA"},
#endif

#if (TCFG_DEC_APE_ENABLE)
    {"APE"},
#endif

#if (TCFG_DEC_DECRYPT_ENABLE)
    {"SMP"},
#endif

#if (TCFG_DEC_AMR_ENABLE)
    {"AMR"},
#endif

#if (TCFG_DEC_M4A_ENABLE)
    {"M4A"},
    {"AAC"},
#endif
#if (TCFG_DEC_M4A_ENABLE || TCFG_DEC_ALAC_ENABLE)
    {"MP4"},
#endif
    {"TMP"},
    {'\0'},
#endif // WATCH_FILE_TO_FLASH
};

static struct __browser *browser = NULL;

//rcsp获取文件浏览后缀配置
char *rcsp_browser_file_ext(void)
{
    return (char *)dec_file_ext;
}

//rcsp获取文件浏览后缀配置数据长度
u16 rcsp_browser_file_ext_size(void)
{
    return strlen((const char *)dec_file_ext);
}

//rcsp浏览设备映射
char *rcsp_browser_dev_remap(RCSPDevMap index)
{
    if (index >= RCSPDevMapMax) {
        return NULL;
    }
    return (char *)dev_logo[index];
}

//rcsp限制文件名长度（包括文件夹,如：xxx~~~, 省略以"~~~"表示）
u16 rcsp_file_name_cut(u8 *name, u16 len, u16 len_limit)
{
    u8 ex_type[8];
    u8 three_point_hex[] = {0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x00}; //... 显示unicode码
    if (len > len_limit) {
        memcpy(name + len_limit - sizeof(three_point_hex), three_point_hex, sizeof(three_point_hex));
        return len_limit;
    }
    return len;
}

static bool browser_get_dir_info(FILE_BS_DEAL *fil_bs, u8 *path_buf, u16 len, RCSPBrowserObjectType type, void *ptr)
{
    s16 ret = 0;
    u16 i, j = 0;
    u32 deep_clust = 0;
    FS_DIR_INFO dir_info;
    //open root
    ret = file_bs_entern_dir(fil_bs, NULL);
    if (ret == 0) {
        goto end;
    }

    if (len == 4 && type == RCSPBrowserObjectTypeFolder) {
        /* printf("root deep\n"); */
        if (ptr) {
            *((u32 *)ptr) = ret;
        }
        goto end;
    } else if (len == 4 && type == RCSPBrowserObjectTypeFile) {
        /* printf("play file path\n"); */
        memcpy((u8 *)&deep_clust, path_buf, 4);
        deep_clust = app_ntohl(deep_clust);
        if (ptr) {
            *((u32 *)ptr) = deep_clust;
        }
        goto end;
    }
    //deep check
    u8 deep = len / 4;
    if (deep >  MAX_DEEPTH) {
        printf("deep err : %d\n", deep);
        return false;
    }
    /* printf("get deep%d data\n", deep - 1); */
    for (i = 1; i < deep; i++) {
        memcpy((u8 *)&deep_clust, path_buf + 4 * i, 4);
        deep_clust = app_ntohl(deep_clust);
        /* printf("deep_clust:%x\n", deep_clust); */
        for (j = 1; j < ret + 1; j++) {
            file_bs_get_dir_info(fil_bs, &dir_info, j, 1);
            if (dir_info.sclust == deep_clust) {
                break;
            }
        }
        if (i < deep - 1) {
            ret = file_bs_entern_dir(fil_bs, &dir_info);
            if (ret == 0) {
                goto end;
            }
        }
    }
    if (type == RCSPBrowserObjectTypeFile) {
        if (ptr) {
            *((u32 *)ptr) = dir_info.sclust;    //file return clust
        }
        goto end;
    } else {
        ret = file_bs_entern_dir(fil_bs, &dir_info);
        if (ret == 0) {
            goto end;
        }

        if (ptr) {
            *((u32 *)ptr) = ret;    //file return clust
        }
    }
end:
    return true;
}

static u32 browse_open_dir(FILE_BS_DEAL *fil_bs, u8 *path_buf, u16 len)
{
    u32 file_cnt = 0;
    browser_get_dir_info(fil_bs, path_buf, len, RCSPBrowserObjectTypeFolder, (void *)&file_cnt);
    return file_cnt;
}

static void file_printf_dir(FS_DIR_INFO *dir_inf, u8 cnt)
{
    u8 i;
    LONG_FILE_NAME *l_name_pt;

    for (i = 0; i < cnt; i++) {
        /* printf("file type %d nt:%d clust %x \n", dir_inf[i].dir_type, dir_inf[i].fn_type, dir_inf[i].sclust); */
        l_name_pt = &dir_inf[i].lfn_buf;
        if (dir_inf[i].fn_type == BS_FNAME_TYPE_SHORT) {
            file_comm_display_83name((void *)&l_name_pt->lfn[32], (void *)l_name_pt->lfn);
            strcpy(l_name_pt->lfn, &l_name_pt->lfn[32]);
            l_name_pt->lfn_cnt = strlen(l_name_pt->lfn);
            printf("%s\n", l_name_pt->lfn);
        } else {
            if (l_name_pt->lfn_cnt > 510) {
                l_name_pt->lfn_cnt = 510;
                puts("***get long name err!!!");
            }
            l_name_pt->lfn_cnt = file_comm_long_name_fix((void *)l_name_pt->lfn, l_name_pt->lfn_cnt);
            l_name_pt->lfn[l_name_pt->lfn_cnt] = 0;
            l_name_pt->lfn[l_name_pt->lfn_cnt + 1] = 0;

            /* printf("file name len : %d \n", l_name_pt->lfn_cnt); */
            /* put_buf((u8 *)l_name_pt->lfn, l_name_pt->lfn_cnt); */
        }
    }
}
static u16 add_one_iterm_to_sendbuf(u8 *dest, u16 max_buf_len, u16 offset, FS_DIR_INFO *p_dir_info, u16 file_cnt, u8 dev_type)
{
    struct JL_FILE_DATA file_data;
    memset((u8 *)&file_data, 0, sizeof(struct JL_FILE_DATA));


    file_data.type = p_dir_info->dir_type;

    if (p_dir_info->fn_type == BS_FNAME_TYPE_SHORT) {
        file_data.format = RCSPBrowserFileDataFormatANSI;
    } else {
        file_data.format = RCSPBrowserFileDataFormatUnicode;
    }

    ///限制文件名长度
    p_dir_info->lfn_buf.lfn_cnt = rcsp_file_name_cut((u8 *)p_dir_info->lfn_buf.lfn, p_dir_info->lfn_buf.lfn_cnt, FILE_BROWSE_NAME_MAX_LIMIT);

    file_data.device = dev_type;
    file_data.clust = app_htonl(p_dir_info->sclust);
    file_data.file_num = app_htons(file_cnt);
    file_data.name_len = p_dir_info->lfn_buf.lfn_cnt;

    memcpy(dest + offset, (u8 *)&file_data, sizeof(struct JL_FILE_DATA));
    memcpy(dest + offset + sizeof(struct JL_FILE_DATA), (u8 *)p_dir_info->lfn_buf.lfn, p_dir_info->lfn_buf.lfn_cnt);

    /* printf("add send data:"); */
    /* put_buf(dest+offset,p_dir_info->lfn_buf.lfn_cnt + sizeof(struct JL_FILE_DATA)); */
    return (p_dir_info->lfn_buf.lfn_cnt + sizeof(struct JL_FILE_DATA));
}

static void rcsp_browser_task(void *p)
{
    u8 reason = 0;
    u32 play_file_clust = 0;
    FS_DIR_INFO dir_info;
    FILE_BS_DEAL fil_bs;
    u8 *path_data = NULL;

    memset((u8 *)&dir_info, 0, sizeof(FS_DIR_INFO));
    memset((u8 *)&fil_bs, 0, sizeof(FILE_BS_DEAL));

    fil_bs.dev = dev_manager_find_spec(rcsp_browser_dev_remap(browser->dev_handle), 0);
    if (fil_bs.dev == NULL) {
        reason = 1;
        printf("dev nofound!!!\n");
        goto _EXIT;
    }
    file_bs_open_handle(&fil_bs, rcsp_browser_file_ext());

    u32 dir_file_cnt = browse_open_dir(&fil_bs, (u8 *)browser->path_clust, browser->path_len);
    if (browser->start_num  + browser->read_file_num >= dir_file_cnt) {
        printf("file range err\n");
        reason = 1;
        browser->read_file_num =  dir_file_cnt - browser->start_num + 1;
    }
    /* printf("start num:%d read file num:%d\n", browser->start_num, browser->read_file_num); */

    u16 offset = 0;
    u32 ret = 0;
    path_data = (u8 *)zalloc(FILE_BROWSE_BUF_LEN);
    if (path_data == NULL) {
        reason = 1;
        printf("no ram for path_data!! \n");
        goto _EXIT;
    }
    for (int i = browser->start_num ; i < (browser->start_num + browser->read_file_num); i++) {
        ret = file_bs_get_dir_info(&fil_bs, &dir_info, i, 1);
        if (!ret) {
            break;
        }

        file_printf_dir(&dir_info, 1);
        if (offset && ((offset + dir_info.lfn_buf.lfn_cnt + sizeof(struct JL_FILE_DATA)) > FILE_BROWSE_BUF_LEN)) {
            ///如果buf不够填充了， 先将数据发送了先，再重新填充
            ret = JL_DATA_send(JL_OPCODE_DATA, JL_OPCODE_FILE_BROWSE_REQUEST_START, path_data, offset, JL_NOT_NEED_RESPOND, 0, NULL);
            if (ret) {
                printf("send data err: %d, %d\n", ret, offset);
                goto _EXIT;
            }
            //reset send buf
            offset = 0;
            memset(path_data, 0, FILE_BROWSE_BUF_LEN);
            offset += add_one_iterm_to_sendbuf(path_data, FILE_BROWSE_BUF_LEN, offset, &dir_info, i, browser->dev_handle);
        } else {
            offset += add_one_iterm_to_sendbuf(path_data, FILE_BROWSE_BUF_LEN, offset, &dir_info, i, browser->dev_handle);
        }
    }

    //send last package
    if (offset) {
        ret = JL_DATA_send(JL_OPCODE_DATA, JL_OPCODE_FILE_BROWSE_REQUEST_START, path_data, offset, JL_NOT_NEED_RESPOND, 0, NULL);
        if (ret) {
            printf("send data err: %d\n", ret);
            goto _EXIT;
        }
    }

_EXIT:
    file_bs_close_handle(&fil_bs);
    if (path_data) {
        free(path_data);
    }
    rcsp_msg_post(
        USER_MSG_RCSP_BS_END,
        4,
        (int)rcsp_handle_get(),
        (int)reason,
        (int)rcsp_browser_dev_remap(browser->dev_handle),
        (int)play_file_clust);

    while (1) {
        os_time_dly(10);
    }
}

//rcsp文件浏览开始
void rcsp_browser_start(u8 *data, u16 len)
{
    ///检查数据是否有效
    printf("%s\n", __func__);
    if (len > sizeof(struct __browser)) {
        return ;
    }
    ///创建数据解析句柄
    browser = (struct __browser *)zalloc(sizeof(struct __browser));
    if (browser == NULL) {
        return ;
    }
    ///解析数据
    memcpy((u8 *)browser, data, sizeof(struct __browser));
    browser->start_num = app_ntohs(browser->start_num);
    browser->dev_handle = app_ntohl(browser->dev_handle);
    browser->path_len = app_ntohs(browser->path_len);

    ///检查设备范围
    if (browser->dev_handle >= RCSPDevMapMax) {
        printf("bs dev hdl err !!\n");
        free(browser);
        browser = NULL;
        return ;
    }
    ///检查是否是已经选定好文件播放
    if (browser->path_type) {
        u8 reason = 2;
        u32 play_file_clust = app_ntohl(browser->path_clust[0]);
        rcsp_msg_post(
            USER_MSG_RCSP_BS_END,
            4,
            (int)rcsp_handle_get(),
            (int)reason,
            (int)rcsp_browser_dev_remap(browser->dev_handle),
            (int)play_file_clust);
        return ;
    }
    ///目录浏览线程创建
    if (task_create(rcsp_browser_task, (void *)NULL, FILE_BROWSE_TASK_NAME)) {
        free(browser);
        browser = NULL;
        printf("rcsp_browser_task creat fail\n");
    }
}

//rcsp文件浏览繁忙查询
bool rcsp_browser_busy(void)
{
    if (browser) {
        return false;
    } else {
        return true;
    }
}

//rcsp文件浏览停止
void rcsp_browser_stop(void)
{
    ///删除线程，释放资源
    task_kill(FILE_BROWSE_TASK_NAME);
    if (browser) {
        free(browser);
        browser = NULL;
    }
}


#endif
