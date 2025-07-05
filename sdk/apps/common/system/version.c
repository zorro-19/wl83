#include "system/includes.h"
#include "generic/log.h"
#include "app_config.h"

extern char __VERSION_BEGIN[];
extern char __VERSION_END[];

const char *sdk_version(void)
{
    return "AC792N SDK on branch [release/AC792N_SDK_V2] tag AC792N_SDK_RELEASE_V2.2.2_2025-04-22";
}

static int app_version_check()
{
    char *version;

    printf("================= SDK Version    %s     ===============\n", sdk_version());
    for (version = __VERSION_BEGIN; version < __VERSION_END;) {
        printf("%s\n", version);
        version += strlen(version) + 1;
    }
    puts("=======================================\n");

    return 0;
}
early_initcall(app_version_check);

