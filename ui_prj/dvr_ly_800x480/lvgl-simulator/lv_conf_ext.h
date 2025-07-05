/*
 * lv_conf_ext.h for custom lvconf file.
 * example : 
 *	#undef LV_FONT_FMT_TXT_LARGE
 *  #define LV_FONT_FMT_TXT_LARGE 1
 */

#ifndef LV_CONF_EXT_H
#define LV_CONF_EXT_H
/* common code begin  */
#define GUIBUILDER_HOR_RES 800
#define GUIBUILDER_VER_RES 480


/* common code end */
#define LV_USE_GUIBUILDER_SIMULATOR 1
#if LV_USE_GUIBUILDER_SIMULATOR
/* code for simulator begin  */
#define LV_COLOR_SCREEN_TRANSP 0
/* code for simulator end */
#else
/* code for board begin */

/* code for board end */	
#endif

#ifdef SDL_HOR_RES
  #undef SDL_HOR_RES
#endif
#ifdef SDL_VER_RES
  #undef SDL_VER_RES
#endif
#ifdef LV_USE_PERF_MONITOR
  #undef LV_USE_PERF_MONITOR
#endif
#ifdef LV_USE_MEM_MONITOR
  #undef LV_USE_MEM_MONITOR
#endif
#ifdef LV_DISP_DEF_REFR_PERIOD
  #undef LV_DISP_DEF_REFR_PERIOD
#endif
#ifdef LV_COLOR_DEPTH
  #undef LV_COLOR_DEPTH
#endif
#ifdef LV_COLOR_16_SWAP
  #undef LV_COLOR_16_SWAP
#endif
#ifdef LV_MEM_SIZE
  #undef LV_MEM_SIZE
#endif

#define SDL_HOR_RES GUIBUILDER_HOR_RES
#define SDL_VER_RES GUIBUILDER_VER_RES
#define LV_USE_PERF_MONITOR 0
#define LV_USE_MEM_MONITOR 0
#define LV_DISP_DEF_REFR_PERIOD 30
#define LV_COLOR_DEPTH 16
#define LV_COLOR_16_SWAP 0
#define LV_MEM_SIZE (2048 * 1024U) 
#define LV_USE_MODEL_DEBUG 0
#define LV_USE_HARDWARE_SIMULATOR 0

#endif  /* LV_CONF_EXT_H */	