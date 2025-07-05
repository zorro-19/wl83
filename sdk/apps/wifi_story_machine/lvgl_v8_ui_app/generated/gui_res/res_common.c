/*Generate Code, Do NOT Edit!*/
#include "./res_common.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

#if !LV_USE_GUIBUILDER_SIMULATOR
#define max(a, b) ((a) > (b) ? (a) : (b))
char sd_dir[] = "S:/";
char flash_dir[] = "mnt/sdfile/EXT_RESERVED/uipackres/ui/";
char path_buf[max(sizeof(sd_dir), sizeof(flash_dir)) + 20];
#endif

char *gui_get_res_path(int32_t id)
{
#if LV_USE_GUIBUILDER_SIMULATOR
    switch (id) {
    case GUI_RES_MONTSERRATMEDIUM_48_TTF:
        return "F:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000000.rle";
    case GUI_RES_FONTAWESOME5_24_TTF:
        return "F:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000001.rle";
    case GUI_RES_MONTSERRATMEDIUM_24_TTF:
        return "F:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000002.rle";
    case GUI_RES_FONTAWESOME5_40_TTF:
        return "F:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000003.rle";
    case GUI_RES_MONTSERRATMEDIUM_40_TTF:
        return "F:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000004.rle";
    case GUI_RES_MONTSERRATMEDIUM_30_TTF:
        return "F:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000005.rle";
    case GUI_RES_MONTSERRATMEDIUM_12_TTF:
        return "F:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000006.rle";
    case GUI_RES_FONTAWESOME5_18_TTF:
        return "F:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000007.rle";
    case GUI_RES_MERGE_FONTS_24_TTF:
        return "F:\\WL83\\ui_prj\\wifi_story_machine_480x800\\ui_res\\rle\\font\\10000008.rle";
    default:
        return NULL;
    }
#else
    memset(path_buf, 0, sizeof(path_buf));
    if (id >= 0x10000000 && id < 0x20000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.rle", flash_dir, id);
    } else if (id >= 0x20000000 && id < 0x30000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.json", flash_dir, id);
    } else if (id >= 0x30000000 && id < 0x31000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.mp4", flash_dir, id);
    } else if (id >= 0x31000000 && id < 0x32000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.avi", flash_dir, id);
    } else if (id >= 0x40000000 && id < 0x50000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.gif", flash_dir, id);
    } else if (id >= 0x50000000 && id < 0x51000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.png", flash_dir, id);
    } else if (id >= 0x51000000 && id < 0x52000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.jpg", flash_dir, id);
    } else if (id >= 0x52000000 && id < 0x53000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.jpeg", flash_dir, id);
    } else if (id >= 0x53000000 && id < 0x54000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.bmp", flash_dir, id);
    } else if (id >= 0x54000000 && id < 0x55000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.svg", flash_dir, id);
    } else if (id >= 0x55000000 && id < 0x56000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.bin", flash_dir, id);
    } else if (id >= 0x56000000 && id < 0x57000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.rle", flash_dir, id);
    } else if (id >= 0x57000000 && id < 0x58000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.etc", flash_dir, id);
    } else if (id >= 0x80000000 && id < 0x90000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.bin", flash_dir, id);
    } else if (id >= 0x90000000 && id < 0xA0000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.json", flash_dir, id);
    } else if (id >= 0xA0000000 && id < 0xA1000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.mp4", flash_dir, id);
    } else if (id >= 0xA1000000 && id < 0xA2000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.avi", flash_dir, id);
    } else if (id >= 0xB0000000 && id < 0xC0000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.gif", flash_dir, id);
    } else if (id >= 0xD0000000 && id < 0xD1000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.png", flash_dir, id);
    } else if (id >= 0xD1000000 && id < 0xD2000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.jpg", flash_dir, id);
    } else if (id >= 0xD2000000 && id < 0xD3000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.jpeg", flash_dir, id);
    } else if (id >= 0xD3000000 && id < 0xD4000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.bmp", flash_dir, id);
    } else if (id >= 0xD4000000 && id < 0xD5000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.svg", flash_dir, id);
    } else if (id >= 0xD5000000 && id < 0xD6000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.bin", flash_dir, id);
    } else if (id >= 0xD6000000 && id < 0xD7000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.rle", flash_dir, id);
    } else if (id >= 0xD7000000 && id < 0xD8000000) {
        snprintf(path_buf, sizeof(path_buf), "%s%x.etc", flash_dir, id);
    } else {
        return NULL;
    }
    return path_buf;
#endif
}
