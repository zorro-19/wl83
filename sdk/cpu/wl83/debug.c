#include "asm/debug.h"
#include "asm/cache.h"
#include "asm/wdt.h"
#include "asm/sfc_norflash_api.h"
#include "app_config.h"
#include "fs/fs.h"

#define LOG_TAG_CONST       DEBUG
#define LOG_TAG             "[DEBUG]"
#define LOG_ERROR_ENABLE
#define LOG_DEBUG_ENABLE
#define LOG_INFO_ENABLE
#define LOG_CLI_ENABLE
#include "debug.h"

#define EXPCPTION_IN_SRAM 		0			//如果出现死机不复位的情况务必需要打开，防止flash挂了,进入异常函数失败复位不了
#define DEBUG_UART				JL_UART0  	//debug串口

extern const char *os_current_task_rom();
extern void log_output_release_deadlock(void);
extern void exception_irq_handler();
extern void sdtap_init(u32 ch);
extern void __wdt_clear(void);
extern void __cpu_reset(void);


/*===========================================================================================
  异常管理单元结构:
 ---------          ---------          ---------           ---------
|   LSB   |        |         |        |         |         |         |
|ASS/VIDEO|  --->  |   HSB   |  --->  |  HCORE  |  --->   |   CPU   |
|   WL    |        |         |        |         |         |         |
 ---------          ---------          ---------           ---------
     |                  |                  |                   |
     |                  |                  |                   |
      -------------------------------------
	                  system                                  内核

1. CPU: 内核级异常
   1) 对应异常开关控制寄存器: q32DSP(n)->EMU_CON;
   2) 对应异常查询寄存器:     q32DSP(n)->EMU_MSG;

2. HCORE: 系统(system)级异常, 该级别通常与内存(Memory)和MMU异常有关
   1) 对应异常开关控制寄存器: JL_CEMU->CON0, JL_CEMU->CON1, JL_CEMU->CON2, JL_CEMU->CON3;
   2) 对应异常查询寄存器:     JL_CEMU->MSG0, JL_CEMU->MSG1, JL_CEMU->MSG2, JL_CEMU->MSG3;
   3) 异常外设查询寄存器:  	  JL_CEMU->LOG0;
   4) HCORE异常类型:
			MSG0和MSG1异常页触发模块的源头相同, 其中
				MSG0异常原因有:
					A)异常模块访问到hmem空白区域;
					B)访问到MMU的TLB_BEG和TLB_END范围;
				MSG1异常原因有:
					A)异常模块访问到已被释放的MMU地址;
					B)MMU TLB配置为空白区;
					C)访问 mmu 虚拟地址引起读 tlb1 的操作，tlb1 的索引范围大于 tlb1_beg/tlb1_end 分配的空间;

3. HSB: 系统(system)级异常, 通常与一些系统高速设备触发的异常有关
   1) 对应异常开关控制寄存器: JL_HEMU->CON0, JL_HEMU->CON1, JL_HEMU->CON2, JL_HEMU->CON3;
   2) 对应异常查询寄存器:     JL_HEMU->MSG0, JL_HEMU->MSG1, JL_HEMU->MSG2, JL_HEMU->MSG3;
   3) 异常外设查询寄存器:  	  JL_HEMU->LOG0;

4. LSB: 系统(system)级异常, 通常与一些系统低速设备触发的异常有关
   1) 对应异常开关控制寄存器: JL_LEMU->CON0, JL_LEMU->CON1, JL_LEMU->CON2, JL_LEMU->CON3;
   2) 对应异常查询寄存器:     JL_LEMU->MSG0, JL_LEMU->MSG1, JL_LEMU->MSG2, JL_LEMU->MSG3;
   3) 异常外设查询寄存器:  	  JL_LEMU->LOG0;

5. ASS: 系统(system)级异常, 通常与系统音频设备触发的异常有关
   1) 对应异常开关控制寄存器: JL_AEMU->CON0, JL_AEMU->CON1, JL_AEMU->CON2, JL_AEMU->CON3;
   2) 对应异常查询寄存器:     JL_AEMU->MSG0, JL_AEMU->MSG1, JL_AEMU->MSG2, JL_AEMU->MSG3;
   3) 异常外设查询寄存器:  	  JL_AEMU->LOG0;

6. VIDEO: 系统(system)级异常, 通常与系统视频设备触发的异常有关
   1) 对应异常开关控制寄存器: JL_VEMU->CON0, JL_VEMU->CON1, JL_VEMU->CON2, JL_VEMU->CON3;
   2) 对应异常查询寄存器:     JL_VEMU->MSG0, JL_VEMU->MSG1, JL_VEMU->MSG2, JL_VEMU->MSG3;
   3) 异常外设查询寄存器:  	  JL_VEMU->LOG0;

7. WL: 系统(system)级异常, 通常与系统RF设备触发的异常有关
   1) 对应异常开关控制寄存器: JL_WEMU->CON0, JL_WEMU->CON1, JL_WEMU->CON2, JL_WEMU->CON3;
   2) 对应异常查询寄存器:     JL_WEMU->MSG0, JL_WEMU->MSG1, JL_WEMU->MSG2, JL_WEMU->MSG3;
   3) 异常外设查询寄存器:  	  JL_WEMU->LOG0;
============================================================================================*/


//====================================================================//
//                         设备ID号                                   //
//====================================================================//
struct dev_id_str {
    const char *name;
    u8 id;
};

static const struct dev_id_str dev_id_list[] = {
    {"DBG_REVERSE",         0x00},
    {"DBG_ALNK",            0x01},
    {"DBG_AUDIO_DAC",       0x03},
    {"DBG_AUDIO_ADC",       0x04},
    {"DBG_ISP",             0x06},
    {"DBG_PLNK",            0x08},
    {"DBG_SBC",             0x09},
    {"DBG_HADC",            0x0b},
    {"DBG_SD0",             0x0c},
    {"DBG_SD1",             0x0d},
    {"DBG_SPI0",            0x0e},
    {"DBG_SPI1",            0x0f},
    {"DBG_SPI2",            0x10},
    {"DBG_UART0",           0x11},
    {"DBG_UART1",           0x12},
    {"DBG_UART2",           0x13},
    {"DBG_LEDC",            0x14},
    {"DBG_GPADC",           0x15},
    {"DBG_PAP",             0x16},
    {"DBG_CTM",             0x17},
    {"DBG_ANC",             0x18},
    {"DBG_SRC_SYNC",        0x19},
    {"DBG_IIC1",            0x1a},
    {"DBG_UART3",           0x1b},
    {"DBG_TDM",             0x1c},
    {"DBG_SHA",             0x1e},
    {"DBG_ETHMAC",          0x1f},
    {"DBG_Q32S_IF",         0x20},
    {"DBG_Q32S_RW",         0x21},
    {"DBG_SPI3",            0x22},
    {"DBG_IIC2",            0x23},
    {"DBG_CAN",             0x24},
    {"DBG_FLASH_SPI",       0x25},
    {"DBG_UART4",           0x26},
    {"DBG_DVB0",            0x27},
    {"DBG_DVB1",            0x28},

    {"DBG_AXI_M1",          0x80},
    {"DBG_AXI_M2",          0x81},
    {"DBG_AXI_M3",          0x82},
    {"DBG_AXI_M4",          0x83},
    {"DBG_AXI_M5",          0x84},
    {"DBG_AXI_M6",          0x85},
    {"DBG_AXI_M7",          0x86},
    {"DBG_AXI_M8",          0x87},
    {"DBG_AXI_M9",          0x88},
    {"DBG_AXI_MA",          0x89},
    {"DBG_AXI_MB",          0x8a},
    {"DBG_AXI_MC",          0x8b},
    {"DBG_AXI_MD",          0x8c},
    {"DBG_AXI_ME",          0x8d},
    {"DBG_AXI_MF",          0x8e},

    {"DBG_AXI_1F",          0x9f},

    {"DBG_USB",             0xa0},
    {"DBG_FM",              0xa1},
    {"DBG_BT",              0xa2},
    {"DBG_FFT",             0xa3},
    {"DBG_EQ",              0xa4},
    {"DBG_SRC",             0xa5},
    {"DBG_DMA_COPY",        0xa6},
    {"DBG_JPG",             0xa7},
    {"DBG_IMB",             0xa8},
    {"DBG_AES",             0xa9},
    {"DBG_BT_RF",           0xaa},
    {"DBG_BT_BLE",          0xab},
    {"DBG_BT_BREDR",        0xac},
    {"DBG_WF_SDC",          0xad},
    {"DBG_WF_SDD",          0xae},

    {"DBG_UDMA_00",         0xe0},
    {"DBG_UDMA_01",         0xe1},
    {"DBG_UDMA_02",         0xe2},
    {"DBG_UDMA_03",         0xe3},
    {"DBG_UDMA_04",         0xe4},
    {"DBG_UDMA_05",         0xe5},
    {"DBG_UDMA_06",         0xe6},
    {"DBG_UDMA_07",         0xe7},
    {"DBG_UDMA_08",         0xe8},
    {"DBG_UDMA_09",         0xe9},
    {"DBG_UDMA_0A",         0xea},
    {"DBG_UDMA_0B",         0xeb},
    {"DBG_UDMA_0C",         0xec},
    {"DBG_UDMA_0D",         0xed},
    {"DBG_UDMA_0E",         0xee},
    {"DBG_UDMA_0F",         0xef},

    {"DBG_CPU0_WR",         0xf0},
    {"DBG_CPU0_RD",         0xf1},
    {"DBG_CPU0_IF",         0xf2},
    {"DBG_CPU1_WR",         0xf3},
    {"DBG_CPU1_RD",         0xf4},
    {"DBG_CPU1_IF",         0xf5},
    {"DBG_CPU2_WR",         0xf6},
    {"DBG_CPU2_RD",         0xf7},
    {"DBG_CPU2_IF",         0xf8},
    {"DBG_CPU3_WR",         0xf9},
    {"DBG_CPU3_RD",         0xfa},
    {"DBG_CPU3_IF",         0xfb},

    {"DBG_SDTAP",           0xff},
    {"MSG_NULL",            0xff}
};

static const struct dev_id_str tzasc_dev_id_list[] = {
    {"TZASC_DCACHE",        0x00},
    {"TZASC_ICACHE",        0x01},
    {"TZASC_DMA_COPY",      0x02},
    {"TZASC_JPG0",          0x03},
    {"TZASC_JPG1",          0x04},
    {"TZASC_IMB",           0x05},
    {"TZASC_IMD",           0x06},
    {"TZASC_IMG",           0x07},
};

//====================================================================//
//                        CPU异常检测部分                             //
//====================================================================//
static const char *const emu_msg[32] = {
    "misalign_err",     //0
    "illeg_err",        //1
    "div0_err",         //2
    "stackoverflow",    //3

    "pc_limit_err",     //4
    "nsc_err",          //5
    "reserved",         //6
    "reserved",         //7

    "etm_wp0_err",      //8
    "reserved",         //9
    "reserved",         //10
    "reserved",         //11

    "reserved",         //12
    "reserved",         //13
    "reserved",         //14
    "reserved",         //15

    "fpu_ine_err",      //16
    "fpu_huge_err",     //17
    "fpu_tiny",         //18
    "fpu_inf_err",      //19

    "fpu_inv_err",      //20
    "reserved",         //21
    "reserved",         //22
    "reserved",         //23

    "reserved",         //24
    "reserved",         //25
    "reserved",         //26
    "reserved",         //27

    "reserved",         //28
    "dcu_emu_err",      //29
    "icu_emu_err",      //30
    "sys_emu_err",      //31
};

//====================================================================//
//                      HCORE异常检测部分                             //
//====================================================================//
static const char *const hcore_emu_msg0[] = {
    "hmem access mpu virtual exception",   //[0]: TZMPU检测到虚拟地址访问内存权限越界，需要读 EMU_ID 分析外设号;
    "hmem access mpu physical exception",  //[1]: TZMPU检测到物理地址访问内存权限越界，需要读 EMU_ID 分析外设号;
    "hmem access mmu exception",           //[2]: MMU访问TLB1异常，检测到TLB1的valid位为0或TLB1寻址范围超过设定的范围，需要读 EMU_ID 分析外设号;
    "hmem access inv exception",           //[3]: hemm内存操作访问到空白区或MMU的TLB1保护的空间或MMU的TLB1设置在空白区，需要读 EMU_ID 分析外设号;
    "sfr_wr_inv or csfr_wr_inv",           //[4]: 写到 syfssr 或者csfr 空白区，需要读 EMU_ID 分析外设号;
    "sfr_rd_inv or csfr_rd_inv",           //[5]: 读到 syfssr 或者csfr 空白区，需要读 EMU_ID 分析外设号;
    "sfr_ass_inv",                         //[6]: 在音频子系统未复位时访问到音频的SFR，需要读 EMU_ID 分析外设号;
    "sfr_video_inv",                       //[7]: 在视频子系统未复位时访问到视频的SFR，需要读 EMU_ID 分析外设号;
    "sfr_wl_inv",                          //[8]: 在WL子系统未复位时访问到WL的SFR，需要读 EMU_ID 分析外设号;
    "lsb emu err",                         //[9]: 非HCORE异常, 属于LSB异常, 需要分析LSB相关EMU_MSG;
    "hsb emu err",                         //[10]: 非HCORE异常, 属于HSB异常, 需要分析HSB相关EMU_MSG;
    "ass emu err",                         //[11]: 非HCORE异常, 属于ASS异常, 需要分析ASS相关EMU_MSG;
    "video emu err",                       //[12]: 非HCORE异常, 属于VIDEO异常, 需要分析VIDEO相关EMU_MSG;
    "wl emu err",                          //[13]: 非HCORE异常, 属于WL异常, 需要分析WL相关EMU_MSG;
    "ilock_err",                           //[14]: 多核互锁使用异常，同一个核连续调用lockset或者另外一个核调用lockclr;
    "l1p request write rocache err",       //[15]: 有写请求访问rocache，需要读 EMU_ID 分析外设号
    "l1p dcache emu err",                  //[16]: 需要调用DcuEmuMessage()分析异常原因
    "l1i ram mapping access excption",     //[17]: 访问到l1icache sfr或mapping预留区域
    "l1d ram mapping access excption",     //[18]: 访问到l1dcache sfr或mapping预留区域
    "l2i ram mapping access excption",     //[19]: 不存在L2I缓存时，访问到l2icache sfr或mapping预留区域
    "l2d ram mapping access excption",     //[20]: 不存在L2D缓存时，访问到l2dcache sfr或mapping预留区域
    "prp ram mapping access excption",     //[21]: 访问外设专用RAM异常，需要读 EMU_ID 分析外设号;
};

//====================================================================//
//                      HSB异常检测部分                               //
//====================================================================//
static const char *const hsb_emu_msg0[] = {
    "device write hsb sfr reserved memory",//[0]: hsb_sfr_wr_inv, 写到 HSB SFR 空白区，需要读 EMU_ID 分析外设号;
    "device read hsb sfr reserved memory", //[1]: hsb_sfr_rd_inv, 读到 HSB SFR 空白区，需要读 EMU_ID 分析外设号;
    "axi write reserved memory",           //[2]: axis_winv, Axi 主机，写到空白区，需要读 EMU_ID 分析外设号;
    "axi read reserved memory",            //[3]: axis_rinv, Axi 主机，读到空白区，需要读 EMU_ID 分析外设号;
    "hsb tzasc exception",                 //[4]: TZASC模块异常
    "sfc0 mmu exception",                  //[5]: SFC0_MMU模块异常
    "sfc1 mmu exception",                  //[6]: SFC1_MMU模块异常
    "watchdog time out",                   //[7]: watchdog_exception, 看门狗超时异常;
    "vlvd exception",                      //[8]: vlvd异常
    "dmc exception",                       //[9]: DMC控制器异常(主机端rready bready被拉低或dmc权限控制框越界)
};

//====================================================================//
//                      LSB异常检测部分                               //
//====================================================================//
static const char *const lsb_emu_msg0[] = {
    "device write lsb sfr reserved memory",//[0]: lsb_sfr_wr_inv, 写到 LSB SFR 空白区，需要读 EMU_ID 分析外设号;
    "device read lsb sfr reserved memory", //[1]: lsb_sfr_rd_inv, 读到 LSB SFR 空白区，需要读 EMU_ID 分析外设号;
};

//====================================================================//
//                      ASS异常检测部分                               //
//====================================================================//
static const char *const ass_emu_msg0[] = {
    "device write ass sfr reserved memory",//[0]: ass_sfr_wr_inv, 写到 ASS SFR 空白区，需要读 EMU_ID 分析外设号;
    "device read ass sfr reserved memory", //[1]: ass_sfr_rd_inv, 读到 ASS SFR 空白区，需要读 EMU_ID 分析外设号;
};

//====================================================================//
//                     VIDEO异常检测部分                              //
//====================================================================//
static const char *const video_emu_msg0[] = {
    "device write video sfr reserved memory",//[0]: video_sfr_wr_inv, 写到 VIDEO SFR 空白区，需要读 EMU_ID 分析外设号;
    "device read video sfr reserved memory", //[1]: video_sfr_rd_inv, 读到 VIDEO SFR 空白区，需要读 EMU_ID 分析外设号;
};

//====================================================================//
//                       WL异常检测部分                               //
//====================================================================//
static const char *const wl_emu_msg0[] = {
    "device write wl sfr reserved memory",//[0]: wl_sfr_wr_inv, 写到 WL SFR 空白区，需要读 EMU_ID 分析外设号;
    "device read wl sfr reserved memory", //[1]: wl_sfr_rd_inv, 读到 WL SFR 空白区，需要读 EMU_ID 分析外设号;
};

//====================================================================//
//                      CACHE异常检测部分                             //
//====================================================================//
static const char *const icache_emu_msg[] = {
    "icache emu error -> iway_rhit_err",   //[0]: 访问ICACHE时，命中了多块WAY，ITAG记录出错
    "icache emu error -> iway_lock_err",   //[1]: 访问ICACHE时，所有WAY都被锁定，无法缓存刚取的指令
    "icache emu error -> ireq_rack_inv",   //[2]: ICACHE关闭时，程序访问了ICACHE区域
    "icache emu error -> islv_inv",        //[3]: 访问到ICACHE_MAPPING的空白区，或ICACHE使用过程中，触发了ICACHE的写保护，需要读EMU_ID分析外设号
    "icache emu error -> icmd_wkst_err",   //[4]: ITAG命令正在进行时，又启动另一个命令
    "icache emu error -> icmd_lock_err",   //[5]: ICACHE锁定代码将所有WAY都锁定了
};

static const char *const dcache_emu_msg[] = {
    "dcache emu error -> rreq_err",        //[0]: 读请求访问DCACHE时，发现DTAG记录出错，命中了多块WAY，或读请求传输的CACHE属性不支持
    "dcache emu error -> wreq_err",        //[1]: 写请求访问DCACHE时，发现DTAG记录出错，命中了多块WAY，或写请求传输的CACHE属性不支持
    "dcache emu error -> snoop_err",       //[2]: 监听器访问DCACHE时，发现DTAG记录出错，命中了多块WAY，或监听器的CACHE属性不支持
    "dcache emu error -> miss_err",        //[3]: MISS通道返回的读响应信息出错
    "dcache emu error -> dcu_ack_inv",     //[4]: DCACHE在DCU_EN未打开时，接受到读写请求或维护请求
    "dcache emu error -> dslv_inv",        //[5]: 访问到DCACHE_MAPPING的空白区，或DCACHE使用的过程中，触发了DCACHE的写保护，需要读EMU_ID分析外设号
};

//====================================================================//
//                        MMU异常检测部分                             //
//====================================================================//
static const char *const sfc_mmu_err_msg[] = {
    "sfc mmu no error",                    //[0]: 无异常
    "sfc mmu close",                       //[1]: 在MMU_EN=0的情况下访问虚拟空间
    "sfc mmu virtual addr error",          //[2]: 在地址转换过程中访问TLB1，但访问的地址不属于TLB1空间
    "sfc mmu TLB1 is invalid",             //[3]: 在地址转换过程中访问TLB1，读到的TLB1数据是无效的
};


const char *get_debug_dev_name(u32 id)
{
    for (int i = 0; i < ARRAY_SIZE(dev_id_list); ++i) {
        if (dev_id_list[i].id == (id & 0xff)) {
            return dev_id_list[i].name;
        }
    }
    return NULL;
}

const char *get_debug_tzasc_dev_name(u32 id)
{
    for (int i = 0; i < ARRAY_SIZE(tzasc_dev_id_list); ++i) {
        if (tzasc_dev_id_list[i].id == (id & 0xff)) {
            return tzasc_dev_id_list[i].name;
        }
    }
    return NULL;
}

u32 get_debug_dev_id(const char *name)
{
    for (int i = 0; i < ARRAY_SIZE(dev_id_list); ++i) {
        if (!strcmp(dev_id_list[i].name, name)) {
            return dev_id_list[i].id;
        }
    }

    return -1;
}

#ifdef CONFIG_SAVE_EXCEPTION_LOG_IN_FLASH

static u32 exception_log_flash_addr sec(.volatile_ram);
static char exception_log_buf[1024];

#define LOG_PATH "mnt/sdfile/EXT_RESERVED/log"

static int get_exception_log_flash_addr(void)
{
    struct vfs_attr file_attr;

    FILE *fp = fopen(LOG_PATH, "r");
    if (fp == NULL) {
        return -1;
    }
    fget_attrs(fp, &file_attr);
    fclose(fp);
    exception_log_flash_addr = file_attr.sclust;
    exception_log_buf[0] = -1;
    sdfile_reserve_zone_read(exception_log_buf, exception_log_flash_addr, sizeof(exception_log_buf), 0);
    if (exception_log_buf[0] != -1) {
        printf("last exception log : \n%s\n", exception_log_buf);
        sdfile_reserve_zone_erase(exception_log_flash_addr, SDFILE_SECTOR_SIZE, 0);
    }
    memset(exception_log_buf, 0, sizeof(exception_log_buf));
    return 0;
}
platform_initcall(get_exception_log_flash_addr);

static void write_exception_log_to_flash(void *data, u32 len)
{
    extern void set_os_init_flag(u8 value);
    set_os_init_flag(0);
    extern void norflash_set_write_cpu_hold(u8 hold_en);
    norflash_set_write_cpu_hold(0);
    sdfile_reserve_zone_erase(exception_log_flash_addr, SDFILE_SECTOR_SIZE, 0);
    sdfile_reserve_zone_write(data, exception_log_flash_addr, len, 0);
}
#endif

static void trace_call_stack(int *len)
{
    for (int c = 0; c < CPU_CORE_NUM; c++) {
        printf("CPU%d %x-->%x-->%x-->%x-->%x-->%x", c,
               q32DSP(c)->ETM_PC5, q32DSP(c)->ETM_PC4,
               q32DSP(c)->ETM_PC3, q32DSP(c)->ETM_PC2,
               q32DSP(c)->ETM_PC1, q32DSP(c)->ETM_PC0);
#ifdef CONFIG_SAVE_EXCEPTION_LOG_IN_FLASH
        *len += snprintf(exception_log_buf + *len, sizeof(exception_log_buf) - *len, "CPU%d %x-->%x-->%x-->%x-->%x-->%x\r\n", c,
                         q32DSP(c)->ETM_PC5, q32DSP(c)->ETM_PC4,
                         q32DSP(c)->ETM_PC3, q32DSP(c)->ETM_PC2,
                         q32DSP(c)->ETM_PC1, q32DSP(c)->ETM_PC0);
#endif
    }
}

#if EXPCPTION_IN_SRAM

AT(.volatile_ram_code)
static char excep_str[] = "\n\n---------------------exception error ------------------------\n";
AT(.volatile_ram_code)
static char debug_msg_str[32][32] = {
    /*0---7*/
    "wdt_timout_err",
    "prp_rd_mmu_err",
    "prp_wr_limit_err",
    "prp_wr_mmu_err",
    "axi_rd_inv",
    "axi_wr_inv",
    "c1_rd_mmu_expt",
    "c0_rd_mmu_expt",
    /*8---15*/
    "c1_wr_mmu_expt",
    "c0_wr_mmu_expt",
    "c1_pc_limit_err_r",
    "c1_wr_limit_err_r",
    "c0_pc_limit_err_r",
    "c0_wr_limit_err_r",
    "dmc_pnd",
    "dbg_pnd",
    /*16---23*/
    "c1_if_bus_inv",
    "c1_rd_bus_inv",
    "c1_wr_bus_inv",
    "c0_if_bus_inv",
    "c0_rd_bus_inv",
    "c0_wr_bus_inv",
    "reserved",
    "reserved",
    /*24---31*/
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
};
extern void putbyte(char a);
AT(.volatile_ram_code)
static void uart_putchar(char a)
{
    if (DEBUG_UART->CON0 & BIT(0)) {
        if (a == '\n') {
            DEBUG_UART->CON0 |= BIT(13);
            DEBUG_UART->BUF = '\r';
            __asm_csync();
            while ((DEBUG_UART->CON0 & BIT(15)) == 0);
        }
        DEBUG_UART->CON0 |= BIT(13);
        DEBUG_UART->BUF = a;
        __asm_csync();
        while ((DEBUG_UART->CON0 & BIT(15)) == 0);
    }
}
AT(.volatile_ram_code)
static void putbuffer(char *buf)
{
    while (*buf != 0) {
        uart_putchar(*buf++);
    }
}
AT(.volatile_ram_code)
static void puthex(int hex)
{
    uart_putchar(' ');
    uart_putchar('0');
    uart_putchar('x');
    for (char i = 28, p = 0, f = 0; i >= 0; i -= 4) {
        p = (char)(hex >> i) & 0xF;
        if (p || f || i == 0) {
            f = 1;
            uart_putchar(p > 9 ? ('A' + (p - 10)) : ('0' + p));
        }
    }
}
AT(.volatile_ram_code)
static void putretis(unsigned int reti, unsigned int rets)
{
    uart_putchar('r');
    uart_putchar('e');
    uart_putchar('t');
    uart_putchar('i');
    uart_putchar(':');
    puthex(reti);
    uart_putchar('\n');
    uart_putchar('r');
    uart_putchar('e');
    uart_putchar('t');
    uart_putchar('s');
    uart_putchar(':');
    puthex(rets);
    uart_putchar('\n');
}
AT(.volatile_ram_code)
static void putstrandhex(char c0, char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8, char c9, int hex, int hex1)
{
    char bf[10];
    bf[0] = c0, bf[1] = c1, bf[2] = c2, bf[3] = c3, bf[4] = c4, bf[5] = c5, bf[6] = c6, bf[7] = c7, bf[8] = c8, bf[9] = c9;
    for (int i = 0; i < sizeof(bf); i++) {
        if (bf[i]) {
            uart_putchar(bf[i]);
        }
    }
    puthex(hex);
    if (hex1) {
        puthex(hex1);
    }
    uart_putchar('\n');
}
AT(.volatile_ram_code)
static void putpchex(int cpu_id)
{
    q32DSP(!cpu_id)->CMD_PAUSE = -1;
    if (cpu_id) {
        corex2(0)->C0_CON &= ~BIT(3);
        corex2(0)->C0_CON |= BIT(1);
    } else {
        corex2(0)->C1_CON &= ~BIT(3);
        corex2(0)->C1_CON |= BIT(1);
    }
    putstrandhex('e', 'r', 'r', ' ', 'C', 'P', 'U', '0' + cpu_id, 0, 0, cpu_id, 0);
    for (int c = 0; c < CPU_CORE_NUM; c++) {
        uart_putchar('C');
        uart_putchar('P');
        uart_putchar('U');
        uart_putchar('0' + c);
        uart_putchar(':');
        puthex(q32DSP(c)->ETM_PC3);
        uart_putchar(' ');
        uart_putchar('-');
        uart_putchar('-');
        uart_putchar('>');
        puthex(q32DSP(c)->ETM_PC2);
        uart_putchar(' ');
        uart_putchar('-');
        uart_putchar('-');
        uart_putchar('>');
        puthex(q32DSP(c)->ETM_PC1);
        uart_putchar(' ');
        uart_putchar('-');
        uart_putchar('-');
        uart_putchar('>');
        puthex(q32DSP(c)->ETM_PC0);
        uart_putchar('\n');
    }
}
AT(.volatile_ram_code)
static void putdebugreg(void)
{
    putstrandhex('D', 'B', 'G', '_', 'M', 'S', 'G', ':', 0, 0, corex2(0)->DBG_MSG, 0);
    for (int i = 0, j = 0, num = 0; i < 32; i++) {
        if (BIT(i) & corex2(0)->DBG_MSG) {
            j = 0;
            if (i == 2 || i == 11 || i == 13) {
                num = j == 2 ? corex2(0)->PRP_WR_LIMIT_ERR_NUM : (j == 11 ? corex2(0)->C1_WR_LIMIT_ERR_NUM : corex2(0)->C0_WR_LIMIT_ERR_NUM);
                while (!(num & BIT(j)) && ++j < 8);
                putstrandhex('W', 'R', '_', 'L', 'I', 'M', 'I', 'T', 'L', ':', ((volatile u32 *)(&corex2(0)->WR_LIMIT0_H))[j], ((volatile u32 *)(&corex2(0)->WR_LIMIT0_L))[j]);
            } else if (i == 10 || i == 12) {
                putstrandhex('P', 'C', '_', 'L', 'M', 'T', '0', 'L', '-', 'H', corex2(0)->PC_LIMIT0_L, corex2(0)->PC_LIMIT0_H);
                putstrandhex('P', 'C', '_', 'L', 'M', 'T', '1', 'L', '-', 'H', corex2(0)->PC_LIMIT1_L, corex2(0)->PC_LIMIT1_H);
            } else if (i == 14) {
                putstrandhex('S', 'D', 'R', ' ', 'D', 'B', 'G', 'I', 'N', 'F', JL_SDR->DBG_INFO, 0);
                putstrandhex('S', 'D', 'R', ' ', 'D', 'B', 'G', 'A', 'D', 'R', JL_SDR->DBG_ADR, 0);
                putstrandhex('S', 'D', 'R', ' ', 'D', 'B', 'G', 'S', 'T', 'A', JL_SDR->DBG_START, 0);
                putstrandhex('S', 'D', 'R', ' ', 'D', 'B', 'G', 'E', 'N', 'D', JL_SDR->DBG_END, 0);
            } else if (i == 15) {
                putstrandhex('A', 'X', 'I', '_', 'L', 'M', 'T', 'L', '_', 'H', JL_DBG->LIMIT_L, JL_DBG->LIMIT_H);
                putstrandhex('W', 'R', '_', 'A', 'L', 'W', ' ', 'I', 'D', '0', JL_DBG->WR_ALLOW_ID0, 0);
                putstrandhex('W', 'R', '_', 'A', 'L', 'W', ' ', 'I', 'D', '1', JL_DBG->WR_ALLOW_ID1, 0);
                putstrandhex('W', 'R', '_', 'L', 'M', 'T', ' ', 'I', 'D', ':',  JL_DBG->WR_ALLOW_ID0, 0);
            }
            uart_putchar('R');
            uart_putchar('e');
            uart_putchar('a');
            uart_putchar('s');
            uart_putchar('o');
            uart_putchar('n');
            uart_putchar(':');
            putbuffer((char *)&debug_msg_str[i]);
        }
    }
    uart_putchar('\n');
    uart_putchar('\n');
}
AT(.volatile_ram_code)
___interrupt
static void exception_analyze_sram(void)
{
#if 0
    u32 rets, reti, cpu_id;
    __asm__ volatile("%0 = rets ;" : "=r"(rets));
    __asm__ volatile("%0 = reti ;" : "=r"(reti));
    __asm__ volatile("%0 = cnum" : "=r"(cpu_id) ::);
    putbuffer(excep_str);
    putretis(reti, rets);
    putpchex(cpu_id);
    putdebugreg();
#endif
    __wdt_clear();
    __cpu_reset();
}
#endif

void exception_analyze(int *sp)
{
    int len = 0;

    log_output_release_deadlock();

    u32 cpu_id = current_cpu_id();
    q32DSP(!cpu_id)->CMD_PAUSE = -1;
    q32DSP(!cpu_id)->PMU_CON0 &= ~BIT(0);
    __asm_csync();

    printf("\n\n---------------------exception error ------------------------\n\n");
    printf("CPU%d %s, EMU_MSG = 0x%x", cpu_id, __func__, q32DSP(cpu_id)->EMU_MSG);
    printf("CPU%d run addr = 0x%x", !cpu_id, q32DSP(!cpu_id)->PCRS);

    printf("JL_CEMU->MSG0:0x%x, MSG1:0x%x, MSG2:0x%x, ID:0x%x, 0x%x, 0x%x, 0x%x", JL_CEMU->MSG0, JL_CEMU->MSG1, JL_CEMU->MSG2, JL_CEMU->LOG0, JL_CEMU->LOG1, JL_CEMU->LOG2, JL_CEMU->LOG3);
    printf("JL_HEMU->MSG0:0x%x, MSG1:0x%x, MSG2:0x%x, ID:0x%x, 0x%x, 0x%x, 0x%x", JL_HEMU->MSG0, JL_HEMU->MSG1, JL_HEMU->MSG2, JL_HEMU->LOG0, JL_HEMU->LOG1, JL_HEMU->LOG2, JL_HEMU->LOG3);
    printf("JL_LEMU->MSG0:0x%x, MSG1:0x%x, MSG2:0x%x, ID:0x%x, 0x%x, 0x%x, 0x%x", JL_LEMU->MSG0, JL_LEMU->MSG1, JL_LEMU->MSG2, JL_LEMU->LOG0, JL_LEMU->LOG1, JL_LEMU->LOG2, JL_LEMU->LOG3);
    printf("JL_AEMU->MSG0:0x%x, MSG1:0x%x, MSG2:0x%x, ID:0x%x, 0x%x, 0x%x, 0x%x", JL_AEMU->MSG0, JL_AEMU->MSG1, JL_AEMU->MSG2, JL_AEMU->LOG0, JL_AEMU->LOG1, JL_AEMU->LOG2, JL_AEMU->LOG3);
    printf("JL_VEMU->MSG0:0x%x, MSG1:0x%x, MSG2:0x%x, ID:0x%x, 0x%x, 0x%x, 0x%x", JL_VEMU->MSG0, JL_VEMU->MSG1, JL_VEMU->MSG2, JL_VEMU->LOG0, JL_VEMU->LOG1, JL_VEMU->LOG2, JL_VEMU->LOG3);
    printf("JL_WEMU->MSG0:0x%x, MSG1:0x%x, MSG2:0x%x, ID:0x%x, 0x%x, 0x%x, 0x%x", JL_WEMU->MSG0, JL_WEMU->MSG1, JL_WEMU->MSG2, JL_WEMU->LOG0, JL_WEMU->LOG1, JL_WEMU->LOG2, JL_WEMU->LOG3);

#ifdef CONFIG_SAVE_EXCEPTION_LOG_IN_FLASH
    len += snprintf(exception_log_buf + len, sizeof(exception_log_buf) - len, "CPU%d run addr = 0x%x\r\ncpu%d EMU_MSG = 0x%x\r\n",
                    !cpu_id, q32DSP(!cpu_id)->PCRS, cpu_id, q32DSP(cpu_id)->EMU_MSG);
#endif

    trace_call_stack(&len);

    unsigned int reti = sp[16];
    unsigned int rete = sp[17];
    unsigned int retx = sp[18];
    unsigned int rets = sp[19];
    unsigned int psr  = sp[20];
    unsigned int icfg = sp[21];
    unsigned int usp  = sp[22];
    unsigned int ssp  = sp[23];
    unsigned int _sp  = sp[24];

    printf("exception cpu %d info : ", cpu_id);

    for (int r = 0; r < 16; r++) {
        printf("R%d: %x\n", r, sp[r]);
    }

    printf("icfg: %x", icfg);
    printf("psr:  %x", psr);
    printf("rets: 0x%x", rets);
    printf("reti: 0x%x", reti);
    printf("usp : %x, ssp : %x sp: %x\n\n", usp, ssp, _sp);

    const volatile u32 *rm = &(q32DSP(!cpu_id)->DR00);
    printf("other cpu %d info : ", !cpu_id);

    for (int r = 0; r < 16; r++) {
        printf("R%d: %x\n", r, rm[r]);
    }

    printf("icfg: %x", q32DSP(!cpu_id)->ICFG);
    printf("psr:  %x", q32DSP(!cpu_id)->PSR);
    printf("rets: 0x%x", q32DSP(!cpu_id)->RETS);
    printf("reti: 0x%x", q32DSP(!cpu_id)->RETI);
    printf("usp : %x, ssp : %x sp: %x\n\n", q32DSP(!cpu_id)->USP, q32DSP(!cpu_id)->SSP, q32DSP(!cpu_id)->SP);

#ifdef CONFIG_SAVE_EXCEPTION_LOG_IN_FLASH
    len += snprintf(exception_log_buf + len, sizeof(exception_log_buf) - len, "icfg: %x\r\n", icfg);
    len += snprintf(exception_log_buf + len, sizeof(exception_log_buf) - len, "psr : %x\r\n", psr);
    len += snprintf(exception_log_buf + len, sizeof(exception_log_buf) - len, "rets: 0x%x\r\n", rets);
    len += snprintf(exception_log_buf + len, sizeof(exception_log_buf) - len, "reti: 0x%x\r\n", reti);
    len += snprintf(exception_log_buf + len, sizeof(exception_log_buf) - len, "usp : %x, ssp : %x sp: %x\r\n", usp, ssp, _sp);
#endif

    // CPU -> HCORE -> HSB -> LSB ASS VIDEO WL

    /*------------------------------------
      CPU 内核
      ------------------------------------*/
    for (int i = 0; i < 32; ++i) {
        if (q32DSP(cpu_id)->EMU_MSG & BIT(i)) {
            printf("[0-CPU] cpu%d emu err msg : %s", cpu_id, emu_msg[i]);

            if (i == 3) {
                if (os_current_task_rom()) {
                    printf("current_task : %s", os_current_task_rom());
                }
                printf("usp limit %x %x, ssp limit %x %x",
                       q32DSP(cpu_id)->EMU_USP_L, q32DSP(cpu_id)->EMU_USP_H, q32DSP(cpu_id)->EMU_SSP_L, q32DSP(cpu_id)->EMU_SSP_H);
            } else if (i == 4) {
                printf("PC_LIMIT0_L:0x%x, PC_LIMIT0_H:0x%x, PC_LIMIT1_L:0x%x, PC_LIMIT1_H:0x%x, PC_LIMIT2_L:0x%x, PC_LIMIT2_H:0x%x",
                       q32DSP(cpu_id)->LIM_PC0_L, q32DSP(cpu_id)->LIM_PC0_H,
                       q32DSP(cpu_id)->LIM_PC1_L, q32DSP(cpu_id)->LIM_PC1_H,
                       q32DSP(cpu_id)->LIM_PC2_L, q32DSP(cpu_id)->LIM_PC2_H);
            } else if (i == 8) {
                printf("ETM limit exception datl:0x%x, dath:0x%x, addrl:0x%x, addrh:0x%x",
                       q32DSP(cpu_id)->WP0_DATL, q32DSP(cpu_id)->WP0_DATH, q32DSP(cpu_id)->WP0_ADRL, q32DSP(cpu_id)->WP0_ADRH);
            } else if (i == 29) {
                DcuEmuMessage();
                printf("except at dev : %s %s", get_debug_dev_name(JL_L1P->EMU_ID & 0xff), (JL_L1P->EMU_ID & BIT(31)) ? "not safe" : "safe");
            } else if (i == 30) {
                for (int j = 0; j < ARRAY_SIZE(icache_emu_msg); ++j) {
                    if (q32DSP_icu(cpu_id)->EMU_MSG & BIT(j)) {
                        printf("[X-ICACHE] emu err msg : %s", icache_emu_msg[j]);
                        if (j == 3) {
                            printf("except at dev : %s %s", get_debug_dev_name(q32DSP_icu(cpu_id)->EMU_ID & 0xff), (q32DSP_icu(cpu_id)->EMU_ID & BIT(31)) ? "not safe" : "safe");
                        }
                    }
                }
            } else if (i == 31) {
                /*------------------------------------
                  HCORE
                  ------------------------------------*/
                for (int j = 0; j < ARRAY_SIZE(hcore_emu_msg0); ++j) {
                    if (JL_CEMU->MSG0 & BIT(j)) {
                        printf("[1-HCORE] emu err msg : %s", hcore_emu_msg0[j]);
                        if (j == 14) {
                            DcuEmuMessage();
                            printf("except at dev : %s %s", get_debug_dev_name(JL_L1P->EMU_ID & 0xff), (JL_L1P->EMU_ID & BIT(31)) ? "not safe" : "safe");
                        }
                        if (j < 8 || j == 13 || j == 19) {
                            printf("except at dev : %s", get_debug_dev_name(JL_CEMU->LOG0 & 0xff));
                        }
                        if (j < 4) {
                            if (JL_CEMU->LOG1 && (j == 0 || j == 2)) {
                                printf("%s virtual memory err, addr : 0x%x", (JL_CEMU->LOG0 & BIT(30)) ? "write" : "read", JL_CEMU->LOG1);
                            }
                            if (JL_CEMU->LOG2 && (j == 1 || j == 3)) {
                                printf("%s physical memory err, addr : 0x%x", (JL_CEMU->LOG0 & BIT(29)) ? "write" : "read", JL_CEMU->LOG2);
                            }
                        } else if (j < 6 || j == 19) {
                            printf("except memory addr : 0x%x, %s", JL_CEMU->LOG1, (JL_CEMU->LOG0 & BIT(31)) ? "not safe" : "safe");
                        }
                        if (j < 2) {
                            int k = 0;
                            int id = JL_CEMU->LOG3 & 0xff;
                            while (!(id & BIT(k)) && ++k < 8);
                            printf("tzmpu limit range index : %d", k);
                        }
                    }
                }
                /*------------------------------------
                  HSB
                  ------------------------------------*/
                if (JL_CEMU->MSG0 & BIT(10)) {
                    for (int j = 0; j < ARRAY_SIZE(hsb_emu_msg0); ++j) {
                        if (JL_HEMU->MSG0 & BIT(j)) {
                            printf("[2-HSB] emu err msg : %s", hsb_emu_msg0[j]);
                            if (j < 4) {
                                printf("except at dev : %s, sfr addr : 0x%x", get_debug_dev_name(JL_HEMU->LOG0 & 0xff), hs_base | (JL_HEMU->LOG1 & 0xffff));
                            } else if (j == 4) {
                                printf("except at dev : %s, %s, %s, if over 4KB %s, err len %d, err each size %d, mem addr : 0x%x(align 32 bytes)",
                                       get_debug_tzasc_dev_name((JL_HEMU->LOG0 & 0x7fff) >> 8),
                                       (JL_HEMU->LOG0 & BIT(30)) ? "write" : "read",
                                       (JL_HEMU->LOG0 & BIT(31)) ? "not safe" : "safe",
                                       (JL_HEMU->LOG0 & BIT(15)) ? "true" : "flase",
                                       (JL_HEMU->LOG0 >> 16) & 0x7f,
                                       (JL_HEMU->LOG0 >> 24) & 0x7,
                                       JL_HEMU->LOG1);
                                int k = 0;
                                int id = JL_HEMU->LOG2 & 0x1f;
                                while (!(id & BIT(k)) && ++k < 4);
                                printf("tzasc limit range index : %d", k);
                            } else if (j < 7) {
                                printf("sfc mmu err msg : %s", sfc_mmu_err_msg[j == 5 ? (JL_SFC0_MMU->CON0 >> 30) : (JL_SFC1_MMU->CON0 >> 30)]);
                            }
                        }
                    }
                }
                /*------------------------------------
                  LSB
                  ------------------------------------*/
                if (JL_CEMU->MSG0 & BIT(9)) {
                    for (int j = 0; j < ARRAY_SIZE(lsb_emu_msg0); ++j) {
                        if (JL_LEMU->MSG0 & BIT(j)) {
                            printf("[3-LSB] emu err msg : %s", lsb_emu_msg0[j]);
                            printf("except at dev : %s, sfr addr : 0x%x", get_debug_dev_name(JL_LEMU->LOG0 & 0xff), ls_base | (JL_LEMU->LOG1 & 0xffff));
                        }
                    }
                }
                /*------------------------------------
                  ASS
                  ------------------------------------*/
                if (JL_CEMU->MSG0 & BIT(11)) {
                    for (int j = 0; j < ARRAY_SIZE(ass_emu_msg0); ++j) {
                        if (JL_AEMU->MSG0 & BIT(j)) {
                            printf("[4-ASS] emu err msg : %s", ass_emu_msg0[j]);
                            printf("except at dev : %s, sfr addr : 0x%x", get_debug_dev_name(JL_AEMU->LOG0 & 0xff), as_base | (JL_AEMU->LOG1 & 0xffff));
                        }
                    }
                }
                /*------------------------------------
                  VIDEO
                  ------------------------------------*/
                if (JL_CEMU->MSG0 & BIT(12)) {
                    for (int j = 0; j < ARRAY_SIZE(video_emu_msg0); ++j) {
                        if (JL_VEMU->MSG0 & BIT(j)) {
                            printf("[5-VIDEO] emu err msg : %s", video_emu_msg0[j]);
                            printf("except at dev : %s, sfr addr : 0x%x", get_debug_dev_name(JL_VEMU->LOG0 & 0xff), JL_VEMU->LOG1 & 0xffff);
                        }
                    }
                }
                /*------------------------------------
                  WL
                  ------------------------------------*/
                if (JL_CEMU->MSG0 & BIT(13)) {
                    for (int j = 0; j < ARRAY_SIZE(wl_emu_msg0); ++j) {
                        if (JL_WEMU->MSG0 & BIT(j)) {
                            printf("[6-WL] emu err msg : %s", wl_emu_msg0[j]);
                            printf("except at dev : %s, sfr addr : 0x%x", get_debug_dev_name(JL_WEMU->LOG0 & 0xff), wl_base | (JL_WEMU->LOG1 & 0x1ffff));
                        }
                    }
                }
            }
        }
    }

#ifdef CONFIG_SAVE_EXCEPTION_LOG_IN_FLASH
    printf("exception log buf len : %d\n", len);
    write_exception_log_to_flash(exception_log_buf, len + 1);
#endif

    printf("system_reset...\r\n\r\n\r\n");
    log_flush();    //只能在异常中断里调用
    __wdt_clear();
#ifdef SDTAP_DEBUG
    sdtap_init(2);//防止IO被占据,重新初始化SDTAP
    while (1);
#endif
#ifndef CONFIG_FPGA_ENABLE
    __cpu_reset();
    while (1);
#else
    while (1);
#endif
}


static void pc0_rang_limit(void *low_addr, void *high_addr)
{
    log_info("pc0 :%x---%x", (u32)low_addr, (u32)high_addr);

    q32DSP(current_cpu_id())->LIM_PC0_H = (u32)high_addr;
    q32DSP(current_cpu_id())->LIM_PC0_L = (u32)low_addr;
}

static void pc1_rang_limit(void *low_addr, void *high_addr)
{
    log_info("pc1 :%x---%x", (u32)low_addr, (u32)high_addr);

    q32DSP(current_cpu_id())->LIM_PC1_H = (u32)high_addr;
    q32DSP(current_cpu_id())->LIM_PC1_L = (u32)low_addr;
}

static void pc2_rang_limit(void *low_addr, void *high_addr)
{
    log_info("pc2 :%x---%x", (u32)low_addr, (u32)high_addr);

    q32DSP(current_cpu_id())->LIM_PC2_H = (u32)high_addr;
    q32DSP(current_cpu_id())->LIM_PC2_L = (u32)low_addr;
}

void pc_rang_limit(void *low_addr0, void *high_addr0, void *low_addr1, void *high_addr1, void *low_addr2, void *high_addr2)
{
    if (low_addr2 && high_addr2 && high_addr2 > low_addr2) {
        pc2_rang_limit(low_addr2, high_addr2);
    }

    if (low_addr1 && high_addr1 && high_addr1 > low_addr1) {
        pc1_rang_limit(low_addr1, high_addr1);
    }

    if (low_addr0 && high_addr0 && high_addr0 > low_addr0) {
        pc0_rang_limit(low_addr0, high_addr0);
    }
}

void cpu_etm_range_value_limit_detect(void *low_addr, void *high_addr, u32 low_limit_value, u32 high_limit_value, ETM_DETECT_MODE mode, int limit_range_out)
{
    int cpu_id = current_cpu_id();

    q32DSP(cpu_id)->ETM_CON &= ~(0x7 << 9);

    if (limit_range_out) {
        q32DSP(cpu_id)->ETM_CON |= BIT(8);
    } else {
        q32DSP(cpu_id)->ETM_CON &= ~BIT(8);
    }

    q32DSP(cpu_id)->WP0_DATL = low_limit_value;
    q32DSP(cpu_id)->WP0_DATH = high_limit_value;
    q32DSP(cpu_id)->WP0_ADRL = (u32)low_addr;
    q32DSP(cpu_id)->WP0_ADRH = (u32)high_addr;

    q32DSP(cpu_id)->ETM_CON |= mode << 9;

    log_debug("CPU%d ETM_CON:%x, WP0_DATL:0x%x, WP0_DATH:0x%x, WP0_ADRL:0x%x, WP0_ADRH:0x%x",
              cpu_id, q32DSP(cpu_id)->ETM_CON, q32DSP(cpu_id)->WP0_DATL, q32DSP(cpu_id)->WP0_DATH, q32DSP(cpu_id)->WP0_ADRL, q32DSP(cpu_id)->WP0_ADRH);
}

//====================================================================//
//                    MPU权限越界检测设置                             //
//====================================================================//
#define MPU_MAX_SIZE    		8 //MPU区域限制框个数

#define TZMPU_LOCK              (1u<<31)
#define TZMPU_HIDE              (1u<<30)
#define TZMPU_SSMODE            (1u<<29)
#define TZMPU_VCHECK            (1u<<28)
#define TZMPU_INV               (1u<<27)

static int mpu_privilege(int idx, u8 type, u8 did, u8 x, u8 r, u8 w, u8 ns)
{
    u8 i;

    switch (type) {
    case 'C':
        log_info("C[%d] : x(%d) : r(%d) : w(%d)", idx, x, r, w);
        if (ns) {
            return ((x) ? TZMPU_U_XEN : 0) | ((r) ? TZMPU_U_REN : 0) | ((w) ? TZMPU_U_WEN : 0);
        } else {
            return ((x) ? TZMPU_S_XEN : 0) | ((r) ? TZMPU_S_REN : 0) | ((w) ? TZMPU_S_WEN : 0);
        }
        break;
    case 'P':
        log_info("P[%d] : r(%d) : w(%d)", idx, r, w);
        if (ns) {
            return ((r) ? TZMPU_U_PREN : 0) | ((w) ? TZMPU_U_PWEN : 0);
        } else {
            return ((r) ? TZMPU_S_PREN : 0) | ((w) ? TZMPU_S_PWEN : 0);
        }
        break;
    case '0':
    case '1':
    case '2':
    case '3':
        i = type - '0';
        log_info("PID[%d][%d] : did 0x%x : r(%d) : w(%d)", idx, i, did, r, w);
        JL_TZMPU->CID[idx] |= TZMPU_IDx_cfg(i, did);
        if (ns) {
            return TZMPU_UID_pen(i, ((r) ? 1 : 0), ((w) ? 1 : 0));
        } else {
            return TZMPU_SID_pen(i, ((r) ? 1 : 0), ((w) ? 1 : 0));
        }
        break;
    default:
        break;
    }

    return 0;
}

// [MPU format]
// begin | end | privilege | inv | pid0_privilege |
static int __parser(int idx, const char *format, va_list argptr)
{
    u8 type = 0;
    u8 did = 0; //device id
    u8 privilege = 0;
    int opt = 0;

    while (*format) {
        switch (*format) {
        case 'C':
            opt |= mpu_privilege(idx, type, did, privilege & BIT(2), privilege & BIT(1), privilege & BIT(0), privilege & BIT(3)); //set last device privilege
            did = 0;
            type = *format;
            privilege = 0; //dev init, clear privilege
            break;
        case 'P':
            opt |= mpu_privilege(idx, type, did, privilege & BIT(2), privilege & BIT(1), privilege & BIT(0), privilege & BIT(3)); //set last device privilege
            did = 0;
            type = *format;
            privilege = 0;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
            opt |= mpu_privilege(idx, type, did, privilege & BIT(2), privilege & BIT(1), privilege & BIT(0), privilege & BIT(3)); //set last device privilege
            did = va_arg(argptr, int);
            type = *format;
            privilege = 0;
            break;

        case 'w':
            privilege |= BIT(0); //cpu/peripheral write en
            break;
        case 'r':
            privilege |= BIT(1); //cpu/peripheral read en
            break;
        case 'x':
            privilege |= BIT(2); //cpu/peripheral execute en
            break;
        case 'n':
            privilege |= BIT(3); //no secure
            break;
        case 'l':
            opt |= TZMPU_LOCK;
            break;
        case 'h':
            opt |= TZMPU_HIDE;
            break;
        case 'v':
            opt |= TZMPU_VCHECK;
            break;
        default:
            break;
        }
        format++;
    }
    opt |= mpu_privilege(idx, type, did, privilege & BIT(2), privilege & BIT(1), privilege & BIT(0), privilege & BIT(3)); //set the last device privilege

    return opt;
}

//=================================================================================//
//@brief: 内存权限保护接口, 可用于对某区域地址配置访问权限, 超出权限则触发系统异常
//@input:
// 		idx: 内存保护框索引, 0 ~ 7, 其中系统保留使用限制框6~7, 用户可以使用限制框0~5, 用于调试;
// 		begin: 保护内存开始地址，4字节对齐;
//      end:   保护内存结束地址，4字节对齐-1;
//      inv:   0: 内存权限检测框内, 1: 内存权限检测框外;
//      format:  设置设备权限, 最多支持cpu + 4个外设读写权限;
//@return:  NULL;
//@note: 当允许所有外设可读写时Prw, 传入的id0/1/2/3变为不允许访问
//@example: 设置限制框2, cpu可读写权限, USB可以读写, BT可读
//        mpu_enable_by_index(2, begin, end, 0, "Crw0rw1r", get_debug_dev_id("DBG_USB"), get_debug_dev_id("DBG_BT"));
//=================================================================================//
void mpu_enable_by_index(int idx, u32 begin, u32 end, u32 inv, const char *format, ...)
{
    int opt = 0;

    if (idx >= MPU_MAX_SIZE) {
        return;
    }

    if (JL_TZMPU->CON[idx] & TZMPU_LOCK) {
        return;
    }

    JL_TZMPU->CON[idx] = 0;
    JL_TZMPU->END[idx] = 0;
    JL_TZMPU->BEG[idx] = 0;
    JL_TZMPU->CID[idx] = 0;

    va_list argptr;
    va_start(argptr, format);

    opt = __parser(idx, format, argptr);

    va_end(argptr);

    if (begin >= 0x400000 && end <= 0x800000) {
        opt |= TZMPU_VCHECK;
    }
    if (inv) {
        opt |= TZMPU_INV;
    }

    JL_TZMPU->BEG[idx] = begin;
    JL_TZMPU->END[idx] = end;

    log_info("JL_TZMPU->CID[%d] 0x%x", idx, JL_TZMPU->CID[idx]);
    log_info("JL_TZMPU->BEG[%d] 0x%x", idx, JL_TZMPU->BEG[idx]);
    log_info("JL_TZMPU->END[%d] 0x%x", idx, JL_TZMPU->END[idx]);

    JL_TZMPU->CON[idx] = opt;

    log_info("JL_TZMPU->CON[%d] 0x%x", idx, JL_TZMPU->CON[idx]);
}

void mpu_disable_by_index(u8 idx)
{
    if (JL_TZMPU->CON[idx] & TZMPU_LOCK) {
        return;
    }
    JL_TZMPU->CON[idx] = 0;
    JL_TZMPU->END[idx] = 0;
    JL_TZMPU->BEG[idx] = 0;
    JL_TZMPU->CID[idx] = 0;
}

void mpu_diasble_all(void)
{
    for (u8 idx = 0; idx < MPU_MAX_SIZE; idx++) {
        if (JL_TZMPU->CON[idx] & TZMPU_LOCK) {
            continue;
        }
        JL_TZMPU->CON[idx] = 0;
        JL_TZMPU->END[idx] = 0;
        JL_TZMPU->BEG[idx] = 0;
        JL_TZMPU->CID[idx] = 0;
    }
}

//====================================================================//
//                   TZASC权限越界检测设置                            //
//====================================================================//
#define TZASC_MAX_SIZE          4 //TZASC区域限制框个数

#define TZASC_LOCK              (1u<<31)
#define TZASC_HIDE              (1u<<30)
#define TZASC_U_WEN             (1u<<11)
#define TZASC_U_REN             (1u<<10)
#define TZASC_S_WEN             (1u<<1)
#define TZASC_S_REN             (1u<<0)
#define TZASC_SID_pen(n, pr, pw) ((pr<<(2+n)) | (pw<<(6+n)))
#define TZASC_UID_pen(n, pr, pw) ((pr<<(12+n)) | (pw<<(16+n)))

static int tzasc_privilege(int idx, u8 type, u16 did, u8 r, u8 w, u8 ns)
{
    u8 i = type - '0';

    switch (type) {
    case 'P':
        log_info("P[%d] : r(%d) : w(%d)", idx, r, w);
        if (ns) {
            return ((r) ? TZASC_U_REN : 0) | ((w) ? TZASC_U_WEN : 0);
        } else {
            return ((r) ? TZASC_S_REN : 0) | ((w) ? TZASC_S_WEN : 0);
        }
        break;
    case '0':
        log_info("PID[%d][%d] : did 0x%x : r(%d) : w(%d)", idx, i, did, r, w);
        JL_TZASC->IDA[idx] |= did;
        if (ns) {
            return TZASC_UID_pen(i, ((r) ? 1 : 0), ((w) ? 1 : 0));
        } else {
            return TZASC_SID_pen(i, ((r) ? 1 : 0), ((w) ? 1 : 0));
        }
        break;
    case '1':
        log_info("PID[%d][%d] : did 0x%x : r(%d) : w(%d)", idx, i, did, r, w);
        JL_TZASC->IDA[idx] |= did << 16;
        if (ns) {
            return TZASC_UID_pen(i, ((r) ? 1 : 0), ((w) ? 1 : 0));
        } else {
            return TZASC_SID_pen(i, ((r) ? 1 : 0), ((w) ? 1 : 0));
        }
        break;
    case '2':
        log_info("PID[%d][%d] : did 0x%x : r(%d) : w(%d)", idx, i, did, r, w);
        JL_TZASC->IDB[idx] |= did;
        if (ns) {
            return TZASC_UID_pen(i, ((r) ? 1 : 0), ((w) ? 1 : 0));
        } else {
            return TZASC_SID_pen(i, ((r) ? 1 : 0), ((w) ? 1 : 0));
        }
        break;
    case '3':
        log_info("PID[%d][%d] : did 0x%x : r(%d) : w(%d)", idx, i, did, r, w);
        JL_TZASC->IDB[idx] |= did << 16;
        if (ns) {
            return TZASC_UID_pen(i, ((r) ? 1 : 0), ((w) ? 1 : 0));
        } else {
            return TZASC_SID_pen(i, ((r) ? 1 : 0), ((w) ? 1 : 0));
        }
        break;
    default:
        break;
    }

    return 0;
}

// [TZASC format]
// begin | end | privilege | pid0_privilege |
static int __tzasc_parser(int idx, const char *format, va_list argptr)
{
    u8 type = 0;
    u16 did = 0; //axi id
    u8 privilege = 0;
    int opt = 0;

    while (*format) {
        switch (*format) {
        case 'P':
            opt |= tzasc_privilege(idx, type, did, privilege & BIT(1), privilege & BIT(0), privilege & BIT(2)); //set last device privilege
            did = 0;
            type = *format;
            privilege = 0;
            break;
        case '0':
        case '1':
        case '2':
        case '3':
            opt |= tzasc_privilege(idx, type, did, privilege & BIT(1), privilege & BIT(0), privilege & BIT(2)); //set last device privilege
            did = va_arg(argptr, int);
            type = *format;
            privilege = 0;
            break;

        case 'w':
            privilege |= BIT(0); //cpu/peripheral write en
            break;
        case 'r':
            privilege |= BIT(1); //cpu/peripheral read en
            break;
        case 'n':
            privilege |= BIT(2); //no secure
            break;
        case 'l':
            opt |= TZASC_LOCK;
            break;
        case 'h':
            opt |= TZASC_HIDE;
            break;
        default:
            break;
        }
        format++;
    }
    opt |= tzasc_privilege(idx, type, did, privilege & BIT(1), privilege & BIT(0), privilege & BIT(2)); //set the last device privilege

    return opt;
}

//=================================================================================//
//@brief: 外存权限保护接口, 可用于对某区域地址配置访问权限, 超出权限则触发系统异常
//@input:
// 		idx: 外存保护框索引, 0 ~ 3, 其中系统保留使用限制框3和框0（背景区域）, 用户可以使用限制框1~2, 用于调试;
// 		begin: 保护外存开始地址，4字节对齐;
//      end:   保护外存结束地址，4字节对齐-1;
//      format:  设置设备权限, 最多支持4个外设读写权限;
//@return:  NULL;
//@note: 当允许所有外设可读写时Prw, 传入的id0/1/2/3变为不允许访问
//@example: 设置限制框1, 只允许JPG访问
//        tzasc_enable_by_index(1, begin, end, "0rw", AXI_MASTER_JPG);
//=================================================================================//
void tzasc_enable_by_index(int idx, u32 begin, u32 end, const char *format, ...)
{
    int opt = 0;

    if (idx >= TZASC_MAX_SIZE) {
        return;
    }

    if (JL_TZASC->CON[idx] & TZASC_LOCK) {
        return;
    }

    JL_TZASC->CON[idx] = 0;
    JL_TZASC->RGN[idx] = 0;
    JL_TZASC->IDA[idx] = 0;
    JL_TZASC->IDB[idx] = 0;

    va_list argptr;
    va_start(argptr, format);

    opt = __tzasc_parser(idx, format, argptr);

    va_end(argptr);

    u32 size = end - begin + 1;
    u32 sub_region_size, base_addr, region_size = 32 * 1024;
    u8 index = 0;

    while (size > region_size || (begin / region_size) != (end / region_size)) {
        region_size <<= 1;
        ++index;
    }

    base_addr = begin / region_size * region_size;
    sub_region_size = region_size >> 3;

    for (u8 i = 0; i < 8; ++i) {
        if (begin >= base_addr + sub_region_size * (i + 1) || end < base_addr + sub_region_size * i) {
            JL_TZASC->RGN[idx] |= BIT(i);
        }
    }

    JL_TZASC->RGN[idx] |= base_addr;
    JL_TZASC->RGN[idx] |= index << 8;

    if (begin % sub_region_size) {
        log_error("JL_TZASC%d begin addr 0x%x not align %d", idx, begin, sub_region_size);
    }
    if ((end + 1) % sub_region_size) {
        log_error("JL_TZASC%d end addr 0x%x not align %d", idx, end, sub_region_size);
    }

    log_info("JL_TZASC%d base:0x%x, region_size:%d, sub_region_size:%d", idx, base_addr, region_size, sub_region_size);
    log_info("JL_TZASC->RGN[%d] 0x%x", idx, JL_TZASC->RGN[idx]);
    log_info("JL_TZASC->IDA[%d] 0x%x", idx, JL_TZASC->IDA[idx]);
    log_info("JL_TZASC->IDB[%d] 0x%x", idx, JL_TZASC->IDB[idx]);

    JL_TZASC->CON[idx] = opt;

    log_info("JL_TZASC->CON[%d] 0x%x", idx, JL_TZASC->CON[idx]);
}

void tzasc_disable_by_index(u8 idx)
{
    if (JL_TZASC->CON[idx] & TZASC_LOCK) {
        return;
    }
    JL_TZASC->CON[idx] = 0;
    JL_TZASC->RGN[idx] = 0;
    JL_TZASC->IDA[idx] = 0;
    JL_TZASC->IDB[idx] = 0;
}

void tzasc_diasble_all(void)
{
    for (u8 idx = 0; idx < TZASC_MAX_SIZE; idx++) {
        if (JL_TZASC->CON[idx] & TZASC_LOCK) {
            continue;
        }
        JL_TZASC->CON[idx] = 0;
        JL_TZASC->RGN[idx] = 0;
        JL_TZASC->IDA[idx] = 0;
        JL_TZASC->IDB[idx] = 0;
    }
}


#ifdef CONFIG_CPU_EFFICIENCY_CALCULATE_ENABLE
void cpu_efficiency_calculate_show(void)
{
    for (int id = 0; id < CPU_CORE_NUM; id++) {
        //读取统计值
        u32 cnt_chit = q32DSP(id)->CNT_CHIT;
        u32 cnt_cmis = q32DSP(id)->CNT_CMIS;
        u32 cnt_fill = q32DSP(id)->CNT_FILL;
        u32 cnt_ihit = q32DSP(id)->CNT_IHIT;
        u32 cnt_imis = q32DSP(id)->CNT_IMIS;
        u32 cnt_rhit = q32DSP(id)->CNT_RHIT;
        u32 cnt_rmis = q32DSP(id)->CNT_RMIS;
        u32 cnt_whit = q32DSP(id)->CNT_WHIT;
        u32 cnt_wmis = q32DSP(id)->CNT_WMIS;
        //重新统计
        //q32DSP(id)->ESU_CON |= BIT(31);

        log_debug("cpu%d c_hist = 0x%x", id, cnt_chit);
        log_debug("cpu%d i_hist = 0x%x", id, cnt_ihit);
        log_debug("cpu%d r_hist = 0x%x", id, cnt_rhit);
        log_debug("cpu%d w_hist = 0x%x", id, cnt_whit);

        log_debug("cpu%d c_mis  = 0x%x", id, cnt_cmis);
        log_debug("cpu%d i_mis  = 0x%x", id, cnt_imis);
        log_debug("cpu%d r_mis  = 0x%x", id, cnt_rmis);
        log_debug("cpu%d w_mis  = 0x%x", id, cnt_wmis);
        log_debug("cpu%d cnt_fill = 0x%x", id, cnt_fill);

        if (!cnt_chit || !cnt_ihit) {
            q32DSP(id)->ESU_CON |= BIT(31);
            continue;
        }

        u64 all;
        all	= cnt_chit + cnt_cmis;
        //内核流水线工作成功的占比
        log_info("cpu%d c_hist = %d%%", id, (u32)((u64)cnt_chit * 100 / all));
        //内核流水线工作等待的占比
        log_info("cpu%d c_mis  = %d%%", id, (u32)((u64)cnt_cmis * 100 / all));

        all = cnt_ihit + cnt_imis;
        //内核取指令总线真正访问总线的占比
        log_info("cpu%d i_hist = %d%%", id, (u32)((u64)cnt_ihit * 100 / all));
        //内核取指令总线等待访问总线的占比
        log_info("cpu%d i_mis  = %d%%", id, (u32)((u64)cnt_imis * 100 / all));

        all = cnt_rhit + cnt_rmis;
        //内核读数据总线真正访问总线的占比
        log_info("cpu%d r_hist = %d%%", id, (u32)((u64)cnt_rhit * 100 / all));
        //内核读数据总线等待访问总线的占比
        log_info("cpu%d r_mis  = %d%%", id, (u32)((u64)cnt_rmis * 100 / all));

        all = cnt_whit + cnt_wmis;
        //内核写数据总线真正访问总线的占比
        log_info("cpu%d w_hist = %d%%", id, (u32)((u64)cnt_whit * 100 / all));
        //内核写数据总线等待访问内存的占比
        log_info("cpu%d w_mis  = %d%%", id, (u32)((u64)cnt_wmis * 100 / all));

        log_info("cpu%d c_fill = %d%%", id, (u32)((u64)cnt_fill * 100 / cnt_cmis));
    }
}

void cpu_efficiency_calculate_init(void)
{
    q32DSP(current_cpu_id())->ESU_CON = 0xffffffff;
}

void cpu_efficiency_calculate_uninit(void)
{
    q32DSP(current_cpu_id())->ESU_CON = BIT(31);
}
#endif

void efficiency_calculate_show(void)
{
#ifdef CONFIG_CPU_EFFICIENCY_CALCULATE_ENABLE
    cpu_efficiency_calculate_show();
#endif
#ifdef CONFIG_ICACHE_EFFICIENCY_CALCULATE_ENABLE
    IcuReportPrintf();
#endif
#ifdef CONFIG_DCACHE_EFFICIENCY_CALCULATE_ENABLE
    DcuReportPrintf();
#endif
}


extern u32 cpu0_sstack_begin[];
extern u32 cpu0_sstack_end[];
extern u32 cpu1_sstack_begin[];
extern u32 cpu1_sstack_end[];

__attribute__((noinline))
void sp_ovf_unen(void)
{
    int cpu_id = current_cpu_id();

    q32DSP(cpu_id)->EMU_CON &= ~BIT(3);
#if defined CONFIG_TRUSTZONE_ENABLE
    q32DSP(cpu_id)->EMU_SSP_H = 0xffffffff;
    q32DSP(cpu_id)->EMU_SSP_L = 0;
#endif
    __asm_csync();	//不能屏蔽，否则会有流水线问题
}

__attribute__((noinline))
void sp_ovf_en(void)
{
    int cpu_id = current_cpu_id();
#if defined CONFIG_TRUSTZONE_ENABLE
    q32DSP(cpu_id)->EMU_SSP_L = cpu_id ? (u32)cpu1_sstack_begin : (u32)cpu0_sstack_begin;
    q32DSP(cpu_id)->EMU_SSP_H = cpu_id ? (u32)cpu1_sstack_end : (u32)cpu0_sstack_end;
#endif
#ifndef SDTAP_DEBUG
    q32DSP(cpu_id)->EMU_CON |= BIT(3); //如果用户使用setjmp longjmp, 或者使用sdtap gdb调试 务必要删掉这句话
    __asm_csync();
#endif
}


#if defined CONFIG_TRUSTZONE_ENABLE

extern u32 _TRUSTZONE_CODE_START;
extern u32 _TRUSTZONE_CODE_END;

//安全模式切换时如果有外设同时访问dcache，可能会出现问题？
AT(.trustzone)
void trustzone_enter(void)
{
    OS_ENTER_CRITICAL();

    IcuFlushinvAll();
    DcuFlushinvAll();

    NSMODE(0);

    __asm_csync();

    OS_EXIT_CRITICAL();
}

AT(.trustzone)
void trustzone_exit(void)
{
    OS_ENTER_CRITICAL();

    IcuFlushinvAll();
    DcuFlushinvAll();

    NSMODE(1);

    __asm_csync();

    OS_EXIT_CRITICAL();
}

void trustzone_init(void)
{
    int cpu_id = current_cpu_id();

    q32DSP(cpu_id)->NSC_ADRL = (u32)&_TRUSTZONE_CODE_START;
    q32DSP(cpu_id)->NSC_ADRH = (u32)&_TRUSTZONE_CODE_END;
    q32DSP(cpu_id)->NSC_CON0 = 1;
}

void trustzone_init_all_cpu(void)
{
    q32DSP(0)->NSC_ADRL = (u32)&_TRUSTZONE_CODE_START;
    q32DSP(0)->NSC_ADRH = (u32)&_TRUSTZONE_CODE_END;
    q32DSP(0)->NSC_CON0 = 1;

    q32DSP(1)->NSC_ADRL = (u32)&_TRUSTZONE_CODE_START;
    q32DSP(1)->NSC_ADRH = (u32)&_TRUSTZONE_CODE_END;
    q32DSP(1)->NSC_CON0 = 1;
}

#else

void trustzone_enter(void)
{

}

void trustzone_exit(void)
{

}

#endif


void debug_msg_clear(void)
{
#ifdef CONFIG_NET_ENABLE
    if (!(JL_WEMU->WREN & BIT(0))) {
        JL_WEMU->WREN = 0xe7;
    }
    JL_WEMU->MSG0 = 0xffffffff;
    JL_WEMU->MSG1 = 0xffffffff;
    JL_WEMU->MSG2 = 0xffffffff;
    JL_WEMU->MSG3 = 0xffffffff;
    if (JL_WEMU->WREN & BIT(0)) {
        JL_WEMU->WREN = 0xe7;
    }
#endif

#ifdef CONFIG_VIDEO_ENABLE
    if (!(JL_VEMU->WREN & BIT(0))) {
        JL_VEMU->WREN = 0xe7;
    }
    JL_VEMU->MSG0 = 0xffffffff;
    JL_VEMU->MSG1 = 0xffffffff;
    JL_VEMU->MSG2 = 0xffffffff;
    JL_VEMU->MSG3 = 0xffffffff;
    if (JL_VEMU->WREN & BIT(0)) {
        JL_VEMU->WREN = 0xe7;
    }
#endif

#ifdef CONFIG_AUDIO_ENABLE
    if (!(JL_AEMU->WREN & BIT(0))) {
        JL_AEMU->WREN = 0xe7;
    }
    JL_AEMU->MSG0 = 0xffffffff;
    JL_AEMU->MSG1 = 0xffffffff;
    JL_AEMU->MSG2 = 0xffffffff;
    JL_AEMU->MSG3 = 0xffffffff;
    if (JL_AEMU->WREN & BIT(0)) {
        JL_AEMU->WREN = 0xe7;
    }
#endif

    if (!(JL_LEMU->WREN & BIT(0))) {
        JL_LEMU->WREN = 0xe7;
    }
    JL_LEMU->MSG0 = 0xffffffff;
    JL_LEMU->MSG1 = 0xffffffff;
    JL_LEMU->MSG2 = 0xffffffff;
    JL_LEMU->MSG3 = 0xffffffff;
    if (JL_LEMU->WREN & BIT(0)) {
        JL_LEMU->WREN = 0xe7;
    }

    if (!(JL_HEMU->WREN & BIT(0))) {
        JL_HEMU->WREN = 0xe7;
    }
    JL_HEMU->MSG0 = 0xffffffff;
    JL_HEMU->MSG1 = 0xffffffff;
    JL_HEMU->MSG2 = 0xffffffff;
    JL_HEMU->MSG3 = 0xffffffff;
    if (JL_HEMU->WREN & BIT(0)) {
        JL_HEMU->WREN = 0xe7;
    }

    if (!(JL_CEMU->WREN & BIT(0))) {
        JL_CEMU->WREN = 0xe7;
    }
    JL_CEMU->MSG0 = 0xffffffff;
    JL_CEMU->MSG1 = 0xffffffff;
    JL_CEMU->MSG2 = 0xffffffff;
    JL_CEMU->MSG3 = 0xffffffff;
    if (JL_CEMU->WREN & BIT(0)) {
        JL_CEMU->WREN = 0xe7;
    }

    JL_L1P->EMU_MSG = 0xffffffff;
    q32DSP_icu(0)->EMU_MSG = 0xffffffff;
    q32DSP_icu(1)->EMU_MSG = 0xffffffff;
    q32DSP(0)->EMU_MSG = 0xffffffff;
    q32DSP(1)->EMU_MSG = 0xffffffff;
}

static int wwdg_isr_callback(void)
{
    return 0;
}

void debug_init(void)
{
    int cpu_id = current_cpu_id();

#if EXPCPTION_IN_SRAM
    request_irq(IRQ_EXCEPTION_IDX, 7, exception_analyze_sram, 0xff);
#else
    request_irq(IRQ_EXCEPTION_IDX, 7, exception_irq_handler, 0xff);
#endif

#ifdef SDTAP_DEBUG
    sdtap_init(2);
#endif

    q32DSP(cpu_id)->EMU_CON = 0;

    if (cpu_id == 0) {
        debug_msg_clear();

        //初始化窗口看门狗
        wwdg_init(0x76, 0x7f, wwdg_isr_callback);
        /* wwdg_enable(); */
    }

    pc_rang_limit(&rom_text_code_begin, &rom_text_code_end,
                  (void *)0xf0000, &ram_text_code_end,
                  /* &ram_text_code_begin, &ram_text_code_end, */
#ifndef CONFIG_NO_SDRAM_ENABLE
                  &sdram_text_code_begin, &sdram_text_code_end
#else
                  NULL, NULL
#endif
                 );

    q32DSP(cpu_id)->EMU_CON &= ~BIT(3);
    q32DSP(cpu_id)->EMU_SSP_L = cpu_id ? (u32)cpu1_sstack_begin : (u32)cpu0_sstack_begin;
    q32DSP(cpu_id)->EMU_SSP_H = cpu_id ? (u32)cpu1_sstack_end : (u32)cpu0_sstack_end;
    q32DSP(cpu_id)->EMU_USP_L = 0;
    q32DSP(cpu_id)->EMU_USP_H = 0xffffffff;
    q32DSP(cpu_id)->EMU_CON |= BIT(3);

    log_info("cpu %d usp limit %x %x", cpu_id, q32DSP(cpu_id)->EMU_USP_L, q32DSP(cpu_id)->EMU_USP_H);
    log_info("cpu %d ssp limit %x %x", cpu_id, q32DSP(cpu_id)->EMU_SSP_L, q32DSP(cpu_id)->EMU_SSP_H);

#ifdef CONFIG_FLOAT_DEBUG_ENABLE
    q32DSP(cpu_id)->EMU_CON |= (0x1f << 16);
#endif
    q32DSP(cpu_id)->EMU_CON |= BIT(4);
    q32DSP(cpu_id)->EMU_CON |= BIT(0) | BIT(1) | BIT(2) | BIT(5) | BIT(8);
    q32DSP(cpu_id)->EMU_CON |= BIT(29) | BIT(30) | BIT(31);
    q32DSP(cpu_id)->ETM_CON |= BIT(0);

    if (cpu_id == 0) {
        log_debug("JL_CEMU->CON0 : 0x%x", JL_CEMU->CON0);
        log_debug("JL_CEMU->CON1 : 0x%x", JL_CEMU->CON1);
        log_debug("JL_CEMU->CON2 : 0x%x", JL_CEMU->CON2);
        log_debug("JL_HEMU->CON0 : 0x%x", JL_HEMU->CON0);
        log_debug("JL_HEMU->CON1 : 0x%x", JL_HEMU->CON1);
        log_debug("JL_HEMU->CON2 : 0x%x", JL_HEMU->CON2);
        log_debug("JL_LEMU->CON0 : 0x%x", JL_LEMU->CON0);
        log_debug("JL_LEMU->CON1 : 0x%x", JL_LEMU->CON1);
        log_debug("JL_LEMU->CON2 : 0x%x", JL_LEMU->CON2);
        log_debug("JL_AEMU->CON0 : 0x%x", JL_AEMU->CON0);
        log_debug("JL_AEMU->CON1 : 0x%x", JL_AEMU->CON1);
        log_debug("JL_AEMU->CON2 : 0x%x", JL_AEMU->CON2);
        log_debug("JL_VEMU->CON0 : 0x%x", JL_VEMU->CON0);
        log_debug("JL_VEMU->CON1 : 0x%x", JL_VEMU->CON1);
        log_debug("JL_VEMU->CON2 : 0x%x", JL_VEMU->CON2);
        log_debug("JL_WEMU->CON0 : 0x%x", JL_WEMU->CON0);
        log_debug("JL_WEMU->CON1 : 0x%x", JL_WEMU->CON1);
        log_debug("JL_WEMU->CON2 : 0x%x", JL_WEMU->CON2);
    }

    log_debug("ICU_EMU_CON->CON0 : 0x%x", q32DSP_icu(cpu_id)->EMU_CON);
    log_debug("DCU_EMU_CON->CON0 : 0x%x", JL_L1P->EMU_CON);

#ifdef CONFIG_CPU_EFFICIENCY_CALCULATE_ENABLE
    cpu_efficiency_calculate_init();
#endif
#ifdef CONFIG_ICACHE_EFFICIENCY_CALCULATE_ENABLE
    IcuReportEnable();
#endif
#ifdef CONFIG_DCACHE_EFFICIENCY_CALCULATE_ENABLE
    DcuReportEnable();
#endif

#if defined CONFIG_TRUSTZONE_ENABLE
    //该步骤应该在跳转到SDK前实现
    trustzone_init();
    trustzone_exit();
#endif

    if (cpu_id == 0) {
#if defined CONFIG_MPU_DEBUG_ENABLE
        //保护ram code不被篡改，只允许CPU执行
#if defined CONFIG_TRUSTZONE_ENABLE
        mpu_enable_by_index(7, (u32)&ram_text_code_begin, (u32)&ram_text_code_end - 1, 0, "Crxn");
#else
        mpu_enable_by_index(7, (u32)&ram_text_code_begin, (u32)&ram_text_code_end - 1, 0, "Crx");
#endif
#if !defined CONFIG_NO_SDRAM_ENABLE
#if defined CONFIG_SFC_ENABLE
        //保护sdram code不被外设篡改，但没办法捕捉CPU读写，因为CPU经过cache没有覆盖MPU功能
#if defined CONFIG_TRUSTZONE_ENABLE
        mpu_enable_by_index(6, (u32)&sdram_text_code_begin, (u32)&sdram_text_code_end - 1, 0, "Crxn");
        tzasc_enable_by_index(3, NO_CACHE_ADDR((u32)&sdram_text_code_begin), NO_CACHE_ADDR((u32)&sdram_text_code_end - 1), "0rn1rn", AXI_MASTER_ICACHE, AXI_MASTER_DCACHE);
#else
        mpu_enable_by_index(6, (u32)&sdram_text_code_begin, (u32)&sdram_text_code_end - 1, 0, "Crx");
        tzasc_enable_by_index(3, NO_CACHE_ADDR((u32)&sdram_text_code_begin), NO_CACHE_ADDR((u32)&sdram_text_code_end - 1), "0r1r", AXI_MASTER_ICACHE, AXI_MASTER_DCACHE);
#endif
#endif
#endif
#endif
    }
}

