#include "app_config.h"
#include "system/init.h"
#include "generic/typedef.h"
#include "syscfg/syscfg_id.h"
#include "json_c/json_tokener.h"
#include "fs/fs.h"

int ai_platform_if_support_poweron_recommend(void)
{
    return 1;
}

char flash_profile_version(void)
{
#if defined CONFIG_PROFILE_UPDATE && defined CONFIG_SERVER_ASSIGN_PROFILE
    return 0;//设置获取profile强制从服务器更新
#endif
    return 2;
}

char *get_auth_key(void)
{
#ifdef CONFIG_SERVER_ASSIGN_PROFILE
    /*#ifdef CONFIG_DUI_SDK_ENABLE*/
    /*return "hE9yfseX6UdK7rFh";*/
    /*#endif*/
#ifdef CONFIG_DUER_SDK_ENABLE
    return "hE9yfseX6UdK7rFh";
#endif
#ifdef CONFIG_TURING_SDK_ENABLE
    return "hE9yfseX6UdK7rFh";
#endif
#ifdef CONFIG_DEEPBRAIN_SDK_ENABLE
    return "E8PNL31m6cZKZAgM";
#endif
#ifdef	PAYMENT_AUDIO_SDK_ENABLE
    return "hE9yfseX6UdK7rFh";
#endif
#ifdef	CONFIG_TELECOM_SDK_ENABLE
    return "ffffffffffffffff";
#endif
#endif
    return NULL;
}
char *get_code(void)
{
#ifdef CONFIG_SERVER_ASSIGN_PROFILE
    /*#ifdef CONFIG_DUI_SDK_ENABLE*/
    /*return "jieli_ai_speech_0408";*/
    /*#endif*/
#ifdef CONFIG_DUER_SDK_ENABLE
    return "jl_story_baidu";
#endif
#ifdef CONFIG_TURING_SDK_ENABLE
    return "jl_story_turing";
#endif
#ifdef CONFIG_DEEPBRAIN_SDK_ENABLE
    return "story_test_deepbrain_ec1f";
#endif
#ifdef PAYMENT_AUDIO_SDK_ENABLE
    return "jieli_payassistant_demo";
#endif
#ifdef	CONFIG_TELECOM_SDK_ENABLE
    return "000000000000001";
#endif
#endif
    return NULL;
}

#ifdef CONFIG_ASSIGN_MACADDR_ENABLE
char *get_macaddr_auth_key(void)
{
    char *ret;
    ret = get_auth_key();
    if (!ret) {
        ret =  "hE9yfseX6UdK7rFh";
    }
    return ret;
}
char *get_macaddr_code(void)
{
    char *ret;
    ret = get_code();
    if (!ret) {
        ret =  "jl_story_baidu";
    }
    return ret;
}
#endif

#if (defined CONFIG_ASR_ALGORITHM) && (CONFIG_ASR_ALGORITHM == AISP_ALGORITHM)
char *get_aisp_auth_key(void)
{
    return "aisp_test_key";
}

char *get_aisp_code(void)
{
    return "aisp_test_code";
}
#endif

#if (defined CONFIG_ASR_ALGORITHM) && (CONFIG_ASR_ALGORITHM == JLKWS_ALGORITHM)
char *get_kws_auth_key(void)
{
    return "kws_test_key";
}

char *get_kws_code(void)
{
    return "jieli_TWbvCB";
}
#endif

#ifdef CONFIG_WT_SDK_ENABLE

const char *get_wt_license_text(void)
{
#define LICENSE_TEXT "OUM2MTZEOTIyRjE2MDA3RUU2REYwNjQzNDQ1OEZEOTlBNTBBNDJCRkI3NkM2OERBNzEyNTU1RTJDQUIyMjc0QUYzMTZCRTE3RkIxN0I3MTZCQ0YyNDIwNDg1Q0QwNzc3NEZEMTJFRTQzMjM1QkI0NTYyRjg4MDM5NDA5RjMzQUFDODM1MDk2QUYyQUJFRTZBOUYxOEQ5Njg0RUM5M0E1OEE4RThFRDUzRTA2OENFOTU5RTM2NkIxNTk4NTI5NjJGQzAyMUNGNjU2MTQzRkM1OEQ0QjlENkE5NzkzOTE1QTdDRjIwREMwQURBQUI2MTc0MjY0QkMxNzRGNDQyRjFFQUNDODE5MjBDNDdCQjQ0RTQ1NUQzNkRCNDU4ODhCMDU5OTUxNDAyMDI0Q0QxNjZDREU0NTE4NEE1NzAzQzEwRDI5NzNEMzg0Q0U5ODgwODM3Mzc5QUVDQkM3MDEwRkEyNkQyMjFGOEEzN0Q4QzQzOUExOTUwRkEyQzY2N0YxQUZDRDRFODM1RUU1MTNDMjM0RDkwNjMxNjZFOTMxODJFMzU0NkFGRkZEMEYzRDkwMDVFNzgwNEM4MUVBRThBNEU2NTM0OTNCMjFCQjhERkI5QUM5QzhCMjU4RDc0QzU5NkYxQzQ0Q0EzN0QzNzU2MzU3QTE2QTU3NUE3Q0NEQTJFNTg3RjA5QzRGQjJFNzUyMjNDQ0VFMjIyRTAwNEIwOUFBQ0NBNjM3MTQ1REFEODlDQkFDRDFGNzY4QzEzNkU4NzVD"
    return LICENSE_TEXT;
}

const char *get_wt_device_id(void)
{
    return "DamB4dtHjfne";
}

const char *get_wt_module_type(void)
{
    return "rtos_test";
}

#endif


#ifdef CONFIG_TURING_SDK_ENABLE

int get_turing_camera_id(void)
{
    return 291;
}

int get_turing_typeflag(void)
{
    return 6;
}

void set_turing_request_para(u8 *speed, u8 *pitch, u8 *volume, u8 *tone)
{

}

const char *get_turing_version_code(void)
{
    return "1.0.0";
}

#endif


#ifdef CONFIG_DEEPBRAIN_SDK_ENABLE

const char *get_deepbrain_client_version(void)
{
    return "1.0.0";
}

const char *get_deepbrain_os_version(void)
{
    return "1.0.0";
}

u8 if_deepbrain_upgrade_support(void)
{
    return 0;
}

#endif


#ifdef CONFIG_DUER_SDK_ENABLE
#if 1 //如果需要使用私有服务器分配profile就打开

static char *dueros_profile;

const char *get_dueros_profile(void)
{
    if (dueros_profile) {
        return dueros_profile;
    }

    u8 magic = 0;
    int addr = sdile_get_ext_reserve_zone_addr("dueros");
    if (addr != -1) {
        sdfile_reserve_zone_read(&magic, addr, sizeof(magic), 0);
        if (magic == '{') {
            dueros_profile = (char *)malloc(2048);
            if (dueros_profile) {
                sdfile_reserve_zone_read(dueros_profile, addr, 2048, 0);
                return dueros_profile;
            }
        }
    }

    return "";
}
#endif

//客户自行根据自己申请的profile修改，不要使用默认值
const char *get_dueros_client_id(void)
{
    return "mlOx3DROc78yDMGV5XYZuS8MrfVGPb7b";
}

const char *get_dueros_device_id(void)
{
    static char device_id[16];

    if (device_id[0] != 0) {
        return device_id;
    }

    const char *profile = get_dueros_profile();
    if (!profile) {
        return NULL;
    }

    json_object *obj = json_tokener_parse(profile);
    if (!obj) {
        return NULL;
    }

    json_object *uuid = json_object_object_get(obj, "uuid");
    if (uuid && json_object_get_string(uuid)) {
        strncpy(device_id, json_object_get_string(uuid), sizeof(device_id) - 1);
        json_object_put(obj);
        return device_id;
    }

    json_object_put(obj);

    return NULL;
}

const char *get_dueros_pub_key(void)
{
    return "Ajb3QJMvem+qdJF7+VySniWGY7Wan1ofpa2tw6Q1Obdx";
}

extern void set_duer_package_info(const char *product,
                                  const char *batch,
                                  const char *os_name,
                                  const char *developer,
                                  const char *os_version,
                                  const char *staged_version);

static int set_dueros_system_info(void)
{
#define OTA_VERSION "1.0.0"
    char version[17] = {0};		//1字节类型+版本号(15个字节)+0

    if (syscfg_read(VM_VERSION_INDEX, version, 16) > 0) {
        if (version[0] == 0) {
            set_duer_package_info("WIFI_SOUNDBOX", "12", "JLOS", "lyx", version + 1, version + 1);	//设置版本号
            printf("version : %s", version + 1);
            return 0;
        }
    }

    memset(version, 0, sizeof(version));
    version[0] = 0;	//升级类型是SD卡升级的话要改回0
    memcpy(version + 1, OTA_VERSION, strlen(OTA_VERSION));
    syscfg_write(VM_VERSION_INDEX, version, 16);
    set_duer_package_info("WIFI_SOUNDBOX", "12", "JLOS", "lyx", version + 1, version + 1);	//设置版本号

    return 0;
}
late_initcall(set_dueros_system_info);

#endif


#ifdef CONFIG_ECHO_CLOUD_SDK_ENABLE

int get_echo_cloud_device_id(char *device_id, u32 len)
{
    return 0;
}

int get_echo_cloud_hash_key(char *hash_key, u32 len)
{
    return 0;
}

int get_echo_cloud_uuid(char *uuid, u32 len)
{
    return 0;
}

const char *get_echo_cloud_firmware_version(void)
{
    return OTA_VERSION;
}

int check_echo_cloud_firmware_version(const char *url, const char *new_ver, const char *checksum)
{
    return 0;
}

#endif

#ifdef CONFIG_TELECOM_SDK_ENABLE
char *get_device_ctei(void)
{
    return get_code();
}

char *get_device_key(void)
{
    return get_auth_key();
}
#endif

#ifdef CONFIG_DUI_SDK_ENABLE
const char *get_dui_auth_product_key(void)
{
    return "321af2bf1b52c93d75db7d300ee5f5b0";
}

const char *get_dui_auth_product_id(void)
{
    return "279593780";
}

const char *get_dui_auth_product_secret(void)
{
    return "cd474e21e4f7b8725f78024a945df569";
}

const char *get_dui_auth_deviceid(void)
{
    return "ceed10b41feb";
}
#endif
