#ifndef CONFIG_CHIP_CFG_H
#define CONFIG_CHIP_CFG_H

#if defined CONFIG_BOARD_TC7920   // 16M-sdram，外置flash
#define __FLASH_SIZE__    (8 * 1024 * 1024)
#define __SDRAM_SIZE__    (16 * 1024 * 1024)
#define __EXTERN_FLASH_SIZE_MB__  32
#define __EXTERN_FLASH_SIZE__     (__EXTERN_FLASH_SIZE_MB__ * 1024 * 1024)
#endif

#if defined CONFIG_BOARD_AC7921A  // 8M-ddr，外置flash
#define __FLASH_SIZE__    (8 * 1024 * 1024)
#define __SDRAM_SIZE__    (8 * 1024 * 1024)
#define __EXTERN_FLASH_SIZE_MB__  32
#define __EXTERN_FLASH_SIZE__     (__EXTERN_FLASH_SIZE_MB__ * 1024 * 1024)
#endif

#if defined CONFIG_BOARD_AC7922A  // 16M-ddr，外置flash
#define __FLASH_SIZE__    (8 * 1024 * 1024)
#define __SDRAM_SIZE__    (16 * 1024 * 1024)
#define __EXTERN_FLASH_SIZE_MB__  32
#define __EXTERN_FLASH_SIZE__     (__EXTERN_FLASH_SIZE_MB__ * 1024 * 1024)
#endif

#if defined CONFIG_BOARD_AC7923A  // 8M-ddr，外置flash
#define __FLASH_SIZE__    (8 * 1024 * 1024)
#define __SDRAM_SIZE__    (8 * 1024 * 1024)
#define __EXTERN_FLASH_SIZE_MB__  32
#define __EXTERN_FLASH_SIZE__     (__EXTERN_FLASH_SIZE_MB__ * 1024 * 1024)
#endif

#if defined CONFIG_BOARD_AC7923B  // 8M-ddr，外置flash
#define __FLASH_SIZE__    (8 * 1024 * 1024)
#define __SDRAM_SIZE__    (8 * 1024 * 1024)
#define __EXTERN_FLASH_SIZE_MB__  32
#define __EXTERN_FLASH_SIZE__     (__EXTERN_FLASH_SIZE_MB__ * 1024 * 1024)
#endif

#if defined CONFIG_BOARD_AC7925A  // 8M-ddr，外置flash
#define __FLASH_SIZE__    (8 * 1024 * 1024)
#define __SDRAM_SIZE__    (8 * 1024 * 1024)
#define __EXTERN_FLASH_SIZE_MB__  32
#define __EXTERN_FLASH_SIZE__     (__EXTERN_FLASH_SIZE_MB__ * 1024 * 1024)
#endif

#if defined CONFIG_BOARD_AC7925B  // 8M-ddr，外置flash
#define __FLASH_SIZE__    (8 * 1024 * 1024)
#define __SDRAM_SIZE__    (8 * 1024 * 1024)
#define __EXTERN_FLASH_SIZE_MB__  32
#define __EXTERN_FLASH_SIZE__     (__EXTERN_FLASH_SIZE_MB__ * 1024 * 1024)
#endif

#if defined CONFIG_BOARD_AC7925C  // 8M-ddr，外置flash
#define __FLASH_SIZE__    (8 * 1024 * 1024)
#define __SDRAM_SIZE__    (8 * 1024 * 1024)
#define __EXTERN_FLASH_SIZE_MB__  32
#define __EXTERN_FLASH_SIZE__     (__EXTERN_FLASH_SIZE_MB__ * 1024 * 1024)
#endif

#if defined CONFIG_BOARD_AC7926A  // 16M-ddr，外置flash
#define __FLASH_SIZE__    (8 * 1024 * 1024)
#define __SDRAM_SIZE__    (16 * 1024 * 1024)
#define __EXTERN_FLASH_SIZE_MB__  32
#define __EXTERN_FLASH_SIZE__     (__EXTERN_FLASH_SIZE_MB__ * 1024 * 1024)
#endif

#if defined CONFIG_BOARD_FCC_TEST  // 8M-ddr，外置flash
#define __FLASH_SIZE__    (2 * 1024 * 1024)
#define __SDRAM_SIZE__    (8 * 1024 * 1024)
#define __EXTERN_FLASH_SIZE_MB__  32
#define __EXTERN_FLASH_SIZE__     (__EXTERN_FLASH_SIZE_MB__ * 1024 * 1024)
#endif

#endif
