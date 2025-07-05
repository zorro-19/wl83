#include "app_config.h"
#ifdef CONFIG_UI_STYLE_LY_ENABLE 
#include "./lv_i18n.h"

#define UNUSED(x) (void)(x)

static inline uint32_t op_n(int32_t val) { return (uint32_t)(val < 0 ? -val : val); }
static inline uint32_t op_i(uint32_t val) { return val; }
// always zero, when decimal part not exists.
static inline uint32_t op_v(uint32_t val) { UNUSED(val); return 0;}
static inline uint32_t op_w(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_f(uint32_t val) { UNUSED(val); return 0; }
static inline uint32_t op_t(uint32_t val) { UNUSED(val); return 0; }

static lv_i18n_phrase_t zh_cn_singulars[] = {
  { "lcdprotect", "屏保", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "poweroff", "自动关机", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "frequency", "光源频率", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "speaker", "按键声音", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "language", "语言设置", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "carnum", "车牌号码", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "roadline", "车道偏移", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "lamp", "前照灯", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "formatting", "格式化", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "reset", "默认设置", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "close", "关闭", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "open", "打开", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "subpagewarning0", "警告\n\n点击确认删除所有数据", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "subpagewarning1", "警告\n\n没有内存卡", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "subpagewarning2", "警告\n\n(version:BETA 004)\n恢复出厂设置", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "YES", "确认", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "CANCEL", "取消", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "date", "日期时间", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "shoot", "拍摄方式", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "dealy10s", "10秒定时", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "dealy5s", "5秒定时", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "dealy2s", "2秒定时", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "nodealy", "单拍", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "standard", "标准", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "pool", "经济", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "high", "优质", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "strong", "强烈", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "soft", "柔和", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "mono", "黑白", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "Nostalgia", "怀旧", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "acuity", "图像锐度", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "sunshine", "日光", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "cloudy", "阴天", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "fluolamp", "荧光灯", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "default", "默认", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "resolution", "图像大小", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "shots", "连拍", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "quality", "图像质量", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "sharpness", "锐度", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "exposure", "曝光补偿", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "awb", "白平衡", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "color", "色彩", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "handshake", "防手抖", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "preview", "快速预览", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "doublerec", "双路录像", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "cycrec", "循环录像", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "gaprec", "间隔录像", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "motion", "运动检测", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "gsensor", "重力感应", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "record", "录音", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "guard", "停车守卫", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "Lsensitive", "低灵敏度", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "Msensitive", "中灵敏度", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "Hsensitive", "高灵敏度", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "tung", "钨丝灯", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "sysprompt", "准备好了吗~", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "lowpow", "电量不足", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "nofile", "没有文件", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "nosd", "SD卡未插入", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "nocamera", "摄像头掉线了", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "fileerr", "文件损坏", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "format_succ", "格式化成功！", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "sys_reset", "恢复出厂设置成功！", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "format_failed", "格式化失败！", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "sys_reset_failed", "恢复出厂设置失败！", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "software", "软件版本", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "subpagewarning3", "版本: JL V1.0.0", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "update_tips", "请勿断电，升级中", "lv_font_FangZhengKaiTiJianTi_1_26" },
  { "line_drift_car", "请移动至车头", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "line_drift_horizon", "请移动至地平线", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "cancel", "取消", "lv_font_FangZhengKaiTiJianTi_1_24" },
  { "ensure", "确定", "lv_font_FangZhengKaiTiJianTi_1_24" },
  { "sd_update", "是否进行 SD卡升级？", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "Mon", "星期一", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Tue", "星期二", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Wed", "星期三", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Thu", "星期四", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Fir", "星期五", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Sat", "星期六", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Sun", "星期日", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "del_file", "是否删除选中的文件？", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "lock_file", "是否加锁选中的文件？", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "unlock_file", "是否解锁选中的文件？", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "file_is_lock", "文件已加锁", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "del_all", "是否删除全部文件？", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "unlock_all", "是否解锁全部文件？", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "lock_all", "是否加锁全部文件？", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "chinese_simplified", "简体中文", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "hdr", "高动态范围", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "tv_mode", "电视制式", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "ver", "版本", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "msd", "存储器", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "pc_cam", "PC摄像头", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "video_rec", "录像模式", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "format_warning", "格式化\n删除所有数据", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "reset_warning", "恢复默认设置？", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "delete", "删除", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "protection", "保护", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "delete_current", "删除当前", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "delete_all", "全部删除", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "lock_one", "加锁当前", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "ulock_one", "解锁当前", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "all_lock", "全部加锁", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "all_ulock", "解锁全部", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "del_cur_file", "删除当前文件？", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "del_all_file", "删除所有文件？", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "reso", "分辨率", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "date_label", "日期标签", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "iso", "ISO", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "auto", "自动", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "normal", "无特效", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "being_formatted", "正在格式化中...", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "fs_err", "TF卡异常!", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "gap_err", "请关闭缩时录影!", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { NULL, NULL, NULL }
};

static lv_i18n_phrase_t zh_cn_plurals_other[] = {

  { NULL, NULL, NULL }
};

static uint8_t zh_cn_plural_fn(int32_t num)
{
  uint32_t n = op_n(num); UNUSED(n);
  uint32_t i = op_i(n); UNUSED(i);
  uint32_t v = op_v(n); UNUSED(v);

  if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
  return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t zh_cn_lang = {
  .locale_name = "zh_cn",
  .singulars = zh_cn_singulars,
  .plurals[LV_I18N_PLURAL_TYPE_OTHER] = zh_cn_plurals_other,
  .locale_plural_fn = zh_cn_plural_fn
};
static lv_i18n_phrase_t en_singulars[] = {
  { "lcdprotect", "screensaver", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "poweroff", "auto shutdown", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "frequency", "frequency", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "reset", "default setting", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "formatting", "formatting", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "lamp", "headlamp", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "roadline", "Lane drift", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "carnum", "License plate", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "language", "language", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "speaker", "keying tone", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "close", "close", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "open", "open", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "subpagewarning0", "Warning\n\n Click to confirm deletion of all data", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "subpagewarning1", "Warning\n\n No memory card", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "subpagewarning2", "Warning\n\n (version:BETA 004)\n Restore factory settings", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "YES", "YES", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "CANCEL", "CANCEL", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "date", "date", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "shoot", "Shooting method", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "dealy10s", "timing 10s", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "dealy5s", "timing 5s", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "dealy2s", "timing 2s", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "nodealy", "Single shot", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "standard", "standard", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "pool", "pool", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "high", "high quality", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "strong", "strong", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "soft", "soft", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "mono", "black and white", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "Nostalgia", "Nostalgia", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "acuity", "acuity", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "sunshine", "sunshine", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "cloudy", "cloudy", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "fluolamp", "fluorescent", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "default", "default", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "resolution", "resolution", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "shots", "shots", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "quality", "image quality", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "sharpness", "sharpness", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "exposure", "exposure", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "awb", "AWB", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "color", "COLOR", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "handshake", "handshake", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "preview", "preview", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "guard", "Parking Guard", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "record", "sound recording", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "gsensor", "Gravity induction", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "motion", "motion detection", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "gaprec", "Interval recording", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "doublerec", "Dual channel recording", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "cycrec", "Loop recording", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "Lsensitive", "Low sensitive", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "Msensitive", "middle sensitive", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "Hsensitive", "high sensitive", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "tung", "Tungsten lamp", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "sysprompt", "are you ready？", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "lowpow", "low battery", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "nofile", "no file", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "nosd", "no sd card", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "nocamera", "camera lost", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "fileerr", "file err", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "format_succ", "format successfully!", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "sys_reset", "system reset successfully!", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "format_failed", "format failed!", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "sys_reset_failed", "system reset failed!", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "software", "software version", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "subpagewarning3", "Version: JL V1.0.0", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "update_tips", "Do not power off, upgrade", "lv_font_FangZhengKaiTiJianTi_1_26" },
  { "line_drift_car", "Please move to the front", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "line_drift_horizon", "Please move to the horizon", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "cancel", "cancel", "lv_font_FangZhengKaiTiJianTi_1_24" },
  { "ensure", "ensure", "lv_font_FangZhengKaiTiJianTi_1_24" },
  { "sd_update", "Whether to upgrade the SD card?", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "Mon", "Monday", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Tue", "Tuesday", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Wed", "Wednesday", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Thu", "Thursday", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Fir", "Firday", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Sat", "Saturday", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "Sun", "星期天", "lv_font_FangZhengKaiTiJianTi_1_48" },
  { "del_file", "Do you want to delete the selected file?", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "lock_file", "Do you want to lock the selected file?", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "unlock_file", "Do you want to unlock the selected file?", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "file_is_lock", "The file is locked!", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "del_all", "Do you want to delete all files?", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "unlock_all", "Do you want to unlock all files?", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "lock_all", "Do you want to lock all files?", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "chinese_simplified", "chinese simplified", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "hdr", "HDR", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "tv_mode", "TV Mode", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "ver", "version", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "msd", "Mass Storage", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "pc_cam", "PC Camera", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "video_rec", "REC_mode", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "format_warning", "Format\nDelete all data", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "reset_warning", "Restore Default", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "delete", "Delete", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "protection", "Protection", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "delete_current", "Delete Current", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "delete_all", "Delete All", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "lock_one", "Lock One", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "ulock_one", "Ulock One", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "all_lock", "Lock All", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "all_ulock", "Ulock All", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "del_cur_file", "Erase This ?", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "del_all_file", "Erase All File ?", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "reso", "Resolution", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "date_label", "Date Stamp", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "iso", "ISO", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "auto", "Auto", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "normal", "Normal", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "being_formatted", "Being formatted...", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "fs_err", "The TF card is abnormal!", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { "gap_err", "Please turn off the time-lapse recording!", "lv_font_FangZhengKaiTiJianTi_1_22" },
  { NULL, NULL, NULL }
};

static lv_i18n_phrase_t en_plurals_other[] = {

  { NULL, NULL, NULL }
};

static uint8_t en_plural_fn(int32_t num)
{
  uint32_t n = op_n(num); UNUSED(n);
  uint32_t i = op_i(n); UNUSED(i);
  uint32_t v = op_v(n); UNUSED(v);

  if ((i == 1 && v == 0)) return LV_I18N_PLURAL_TYPE_ONE;
  return LV_I18N_PLURAL_TYPE_OTHER;
}

static const lv_i18n_lang_t en_lang = {
  .locale_name = "en",
  .singulars = en_singulars,
  .plurals[LV_I18N_PLURAL_TYPE_OTHER] = en_plurals_other,
  .locale_plural_fn = en_plural_fn
};
const lv_i18n_language_pack_t lv_i18n_language_pack[] = {
  &zh_cn_lang,
  &en_lang,
NULL // End mark
};
////////////////////////////////////////////////////////////////////////////////

// Internal state
static const lv_i18n_language_pack_t * current_lang_pack;
static const lv_i18n_lang_t * current_lang;


/**
* Reset internal state. For testing.
*/
void __lv_i18n_reset(void)
{
  current_lang_pack = NULL;
  current_lang = NULL;
}

/**
* Set the languages for internationalization
* @param langs pointer to the array of languages. (Last element has to be `NULL`)
*/
int lv_i18n_init(const lv_i18n_language_pack_t * langs)
{
  if(langs == NULL) return -1;
  if(langs[0] == NULL) return -1;

  current_lang_pack = langs;
  current_lang = langs[0];     /*Automatically select the first language*/
  return 0;
  }

  /**
  * Change the localization (language)
  * @param l_name name of the translation locale to use. E.g. "en-GB"
  */
  int lv_i18n_set_locale(const char * l_name)
  {
  if(current_lang_pack == NULL) return -1;

  uint16_t i;

  for(i = 0; current_lang_pack[i] != NULL; i++) {
    // Found -> finish
    if(strcmp(current_lang_pack[i]->locale_name, l_name) == 0) {
      current_lang = current_lang_pack[i];
      return 0;
    }
  }

  return -1;
}


static const char * __lv_i18n_get_text_core(lv_i18n_phrase_t * trans, const char * msg_id)
{
  uint16_t i;
  for(i = 0; trans[i].msg_id != NULL; i++) {
    if(strcmp(trans[i].msg_id, msg_id) == 0) {
      /*The msg_id has found. Check the translation*/
      if(trans[i].translation) return trans[i].translation;
    }
  }

  return NULL;
}


/**
* Get the translation from a message ID
* @param msg_id message ID
* @return the translation of `msg_id` on the set local
*/
const char * lv_i18n_get_text(const char * msg_id)
{
  if(current_lang == NULL) return msg_id;

  const lv_i18n_lang_t * lang = current_lang;
  const void * txt;

  // Search in current locale
  if(lang->singulars != NULL) {
    txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
    if (txt != NULL) return txt;
  }

  // Try to fallback
  if(lang == current_lang_pack[0]) return msg_id;
  lang = current_lang_pack[0];

  // Repeat search for default locale
  if(lang->singulars != NULL) {
    txt = __lv_i18n_get_text_core(lang->singulars, msg_id);
    if (txt != NULL) return txt;
  }

  return msg_id;
}

/**
* Get the translation from a message ID and apply the language's plural rule to get correct form
* @param msg_id message ID
* @param num an integer to select the correct plural form
* @return the translation of `msg_id` on the set local
*/
const char * lv_i18n_get_text_plural(const char * msg_id, int32_t num)
{
  if(current_lang == NULL) return msg_id;

  const lv_i18n_lang_t * lang = current_lang;
  const void * txt;
  lv_i18n_plural_type_t ptype;

  // Search in current locale
  if(lang->locale_plural_fn != NULL) {
    ptype = lang->locale_plural_fn(num);

    if(lang->plurals[ptype] != NULL) {
      txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
      if (txt != NULL) return txt;
    }
  }

  // Try to fallback
  if(lang == current_lang_pack[0]) return msg_id;
  lang = current_lang_pack[0];

  // Repeat search for default locale
  if(lang->locale_plural_fn != NULL) {
    ptype = lang->locale_plural_fn(num);

    if(lang->plurals[ptype] != NULL) {
      txt = __lv_i18n_get_text_core(lang->plurals[ptype], msg_id);
      if (txt != NULL) return txt;
    }
  }

  return msg_id;
}

typedef struct {
  const char * font_name;
  const lv_font_t * font_ptr;
} font_mapping_t;

static const font_mapping_t font_mapping[] = {
  {"lv_font_FangZhengKaiTiJianTi_1_22", &lv_font_FangZhengKaiTiJianTi_1_22},
  {"lv_font_FangZhengKaiTiJianTi_1_26", &lv_font_FangZhengKaiTiJianTi_1_26},
  {"lv_font_FangZhengKaiTiJianTi_1_24", &lv_font_FangZhengKaiTiJianTi_1_24},
  {"lv_font_FangZhengKaiTiJianTi_1_48", &lv_font_FangZhengKaiTiJianTi_1_48},
  {NULL, NULL} // End mark
};

const lv_font_t * lv_i18n_get_font_by_name(const char * font_name)
{
  if(font_name == NULL) return NULL;

  for(uint16_t i = 0; font_mapping[i].font_name != NULL; i++) {
    if(strcmp(font_mapping[i].font_name, font_name) == 0) {
      return font_mapping[i].font_ptr;
    }
  }

  return NULL;
}

/*
* Get the font for a message ID
* @param msg_id message ID
*/
const lv_font_t * lv_i18n_get_font(const char * msg_id)
{
  if(current_lang == NULL) return NULL;

  const lv_i18n_lang_t * lang = current_lang;
  const lv_font_t * font = NULL;

  // Search in current locale singulars
  if(lang->singulars != NULL) {
    for(uint16_t i = 0; lang->singulars[i].msg_id != NULL; i++) {
      if(strcmp(lang->singulars[i].msg_id, msg_id) == 0) {
        const char * font_name = lang->singulars[i].font_name;
        font = lv_i18n_get_font_by_name(font_name);
        return font;
      }
    }
  }

  // Search in current locale plurals for type ONE
  if(lang->plurals[LV_I18N_PLURAL_TYPE_ONE] != NULL) {
    for(uint16_t i = 0; lang->plurals[LV_I18N_PLURAL_TYPE_ONE][i].msg_id != NULL; i++) {
      if(strcmp(lang->plurals[LV_I18N_PLURAL_TYPE_ONE][i].msg_id, msg_id) == 0) {
        const char * font_name = lang->plurals[LV_I18N_PLURAL_TYPE_ONE][i].font_name;
        font = lv_i18n_get_font_by_name(font_name);
        return font;
      }
    }
  }

  // Search in current locale plurals for type OTHER
  if(lang->plurals[LV_I18N_PLURAL_TYPE_OTHER] != NULL) {
    for(uint16_t i = 0; lang->plurals[LV_I18N_PLURAL_TYPE_OTHER][i].msg_id != NULL; i++) {
      if(strcmp(lang->plurals[LV_I18N_PLURAL_TYPE_OTHER][i].msg_id, msg_id) == 0) {
        const char * font_name = lang->plurals[LV_I18N_PLURAL_TYPE_OTHER][i].font_name;
        font = lv_i18n_get_font_by_name(font_name);
        return font;
      }
    }
  }

  return NULL;
}

/**
* Get the name of the currently used locale.
* @return name of the currently used locale. E.g. "en-GB"
*/
const char * lv_i18n_get_current_locale(void)
{
  if(!current_lang) return NULL;
  return current_lang->locale_name;
}

/** 
 * Get the default locale
 * @return the default locale. E.g. "en_GB"
 */
GUI_WEAK const char * lv_i18n_get_default_locale(void)
{
  return "zh_CN";
}

#endif
