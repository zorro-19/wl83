#include "../../lv_examples.h"
#if LV_BUILD_EXAMPLES
#if LV_USE_FREETYPE && LV_USE_DRAW_JLVG_LABEL_ENABLE && LV_USE_DRAW_JLVG

#if LV_FREETYPE_USE_LVGL_PORT
#define PATH_PREFIX "A:"
#else
#define PATH_PREFIX CONFIG_ROOT_PATH
#endif

// 使用 GPU 绘制矢量路径字体

//#define CONFIG_FONT_TTF_PATH CONFIG_UI_RES_PATH"font/simkai.ttf"    // windos 下完整楷体字库
#define CONFIG_FONT_TTF_PATH "mnt/sdfile/EXT_RESERVED/uipackres/ui/sub1.ttf" // 龘: flash
//#define CONFIG_FONT_TTF_PATH "mnt/sdfile/EXT_RESERVED/uipackres/ui/sub2.ttf"  // 《生僻字部分歌词》: flash

/**
 * Load a font with FreeType
 */
void lv_example_freetype_2(void)
{
    /*Create a font*/
    lv_font_t *font = lv_freetype_font_create(CONFIG_FONT_TTF_PATH,
                      LV_FREETYPE_FONT_RENDER_MODE_OUTLINE,
                      48,
                      LV_FREETYPE_FONT_STYLE_NORMAL);

    if (!font) {
        LV_LOG_ERROR("freetype font create failed.");
        return;
    }

    /*Create style with the new font*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "Hello world\nI'm a font created with FreeType");
    lv_obj_center(label);
}
#else

void lv_example_freetype_2(void)
{
    /*TODO
     *fallback for online examples*/

    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "FreeType example 2 requires \nLV_USE_FREETYPE and LV_USE_DRAW_JLVG_LABEL_ENABLE");
    lv_obj_center(label);
}

#endif
#endif
