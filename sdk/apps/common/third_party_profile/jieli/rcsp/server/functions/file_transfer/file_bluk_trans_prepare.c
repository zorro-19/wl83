#ifdef MEDIA_SUPPORT_MS_EXTENSIONS
#pragma bss_seg(".file_bluk_trans_prepare.data.bss")
#pragma data_seg(".file_bluk_trans_prepare.data")
#pragma const_seg(".file_bluk_trans_prepare.text.const")
#pragma code_seg(".file_bluk_trans_prepare.text")
#endif
#include "file_bluk_trans_prepare.h"
#include "rcsp.h"
#include "system/includes.h"
#include "file_operate/file_manager.h"

#if (RCSP_MODE && TCFG_DEV_MANAGER_ENABLE)
enum {
    FILE_BLUK_TRANS_BEGIN,
    FILE_BLUK_TRANS_END = 0x80,
    FILE_BLUK_TRANS_CANCEL = 0x81,
};

static void (*g_end_callback)(void);

//文件流传输准备
void rcsp_file_bluk_trans_prepare(void *priv, u8 OpCode_SN, u8 *data, u16 len)
{
    int ret = 0;
    u8 offset = 0;
    u8 op = data[offset++];
    u8 resp_data[2] = {0};
    resp_data[0] = op;
    switch (op) {
    case FILE_BLUK_TRANS_BEGIN:
        app_rcsp_task_prepare(0, RCSP_TASK_ACTION_BLUK_TRANSFER, OpCode_SN);
        break;
    case FILE_BLUK_TRANS_CANCEL:
    case FILE_BLUK_TRANS_END:
        rcsp_file_bluk_trans_close(0);
        break;
    }
    JL_CMD_response_send(JL_OPCODE_FILE_BLUK_TRANSFER, JL_PRO_STATUS_SUCCESS, OpCode_SN, resp_data, sizeof(resp_data), 0, NULL);
}

//文件流传输初始化
void rcsp_file_bluk_trans_init(void (*end_callback)(void))
{
    g_end_callback = end_callback;
}

//文件流传输关闭
void rcsp_file_bluk_trans_close(u8 dire)
{
    if (g_end_callback) {
        g_end_callback();
        g_end_callback = NULL;
        if (dire) {
            u8 resp_data[2] = {FILE_BLUK_TRANS_CANCEL, 0};
            JL_CMD_send(JL_OPCODE_FILE_BLUK_TRANSFER, resp_data, sizeof(resp_data), 1, 0, NULL);
        }
    }
}

#endif
