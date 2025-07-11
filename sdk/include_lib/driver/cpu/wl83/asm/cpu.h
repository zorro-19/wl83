#ifndef __ASM_CPU_H__
#define __ASM_CPU_H__

#ifndef __ASSEMBLY__

#include "WL83.h"

#if ((!defined __cplusplus) && (!defined BOOL_DEFINE_CONFLICT))
typedef unsigned char   		bool;
#endif
typedef unsigned char   		u8, BOOL, uint8_t;
typedef char            		s8;
typedef signed char            	int8_t;
typedef unsigned short  		u16, uint16_t, u_int16_t;
typedef signed short    		s16, int16_t;
typedef unsigned int    		u32, uint32_t;
typedef signed int      		s32;
typedef unsigned long long 		u64;
typedef u32						FOURCC;
typedef long long               s64;
typedef unsigned long long      u64, uint64_t;

#endif

#define ___trig        __asm__ volatile ("trigger")

#ifndef BIG_ENDIAN
#define BIG_ENDIAN 			0x3021
#endif
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 		0x4576
#endif
#define CPU_ENDIAN 			LITTLE_ENDIAN

#define CPU_CORE_NUM     2

#define __NONCPU_ADDR__         ((u8 *)0x18000000)
#define __SFC0_ADDR_BEGIN__			((u32)0x8000000)
#define __SFC0_ADDR_END__			((u32)0xC000000)
#define __SFC1_ADDR_BEGIN__			((u32)0x10000000)
#define __SFC1_ADDR_END__			((u32)0x14000000)

#define NO_CACHE_ADDR(addr) \
	(u32)(((u32)(addr) >=0x18000000)?((u32)(addr)+(0x1C000000-0x18000000)):(u32)(addr))

#define CPU_ADDR(addr) \
	(u32)(((u32)(addr) >=0x1C000000)?((u32)(addr)-(0x1C000000-0x18000000)):(u32)(addr))

#define  CPU_TASK_CLR(a)
#define  CPU_TASK_SW(a) 		\
    do { \
		extern void wdt_clear(void);\
		/*wl83 双核要分开配置q32DSP*/ \
        q32DSP(a)->ILAT_SET|=BIT(7-a); \
        extern const int config_clear_wdg_in_idle_hook; \
        if (config_clear_wdg_in_idle_hook) { \
            wdt_clear(); \
        } \
    } while (0)

#define  CPU_INT_NESTING 	2

#define CPU_RAND()	(JL_RAND->R64L)

#ifndef __ASSEMBLY__

__attribute__((always_inline))
static inline u32 rand32(void)
{
    return JL_RAND->R64L;
}

__attribute__((always_inline))
static inline int current_cpu_id(void)
{
    unsigned id;
    asm volatile("%0 = cnum" : "=r"(id) ::);
    return id ;
}

__attribute__((always_inline))
static int core_num(void)
{
    u32 num;
    asm volatile("%0 = cnum" : "=r"(num) :);
    return num;
}

extern int cpu_in_irq(void);
extern int cpu_irq_disabled(void);

__attribute__((always_inline))
static inline int data_sat_s16(int ind)
{
    __asm__ volatile(
        " %0 = sat16(%0)(s)  \t\n"
        : "=&r"(ind)
        : "0"(ind)
        :);
    return ind;
}

__attribute__((always_inline))
static inline u32 reverse_u32(u32 data32)
{
#if 1
    u8 *dataptr = (u8 *)(&data32);
    data32 = (((u32)dataptr[0] << 24) | ((u32)dataptr[1] << 16) | ((u32)dataptr[2] << 8) | (u32)dataptr[3]);
#else
    __asm__ volatile("%0 = rev8(%0) \t\n" : "=&r"(data32) : "0"(data32) :);
#endif
    return data32;
}

__attribute__((always_inline))
static inline u32 reverse_u16(u16 data16)
{
    u32 retv;
#if 1
    u8 *dataptr = (u8 *)(&data16);
    retv = (((u32)dataptr[0] << 8) | ((u32)dataptr[1]));
#else
    retv = ((u32)data16) << 16;
    __asm__ volatile("%0 = rev8(%0) \t\n" : "=&r"(retv) : "0"(retv) :);
#endif
    return retv;
}
#endif


#ifndef __ASSEMBLY__ //assembly

#define __asm_csync() \
    do { \
		asm volatile("csync;"); \
    } while (0)

#define __asm_ssync() \
    do { \
		asm volatile("ssync;"); \
    } while (0)

#include "asm/irq.h"
#include "generic/printf.h"
#include "system/generic/log.h"

#define arch_atomic_read(v)  \
	({ \
        __asm_csync(); \
		(*(volatile int *)&(v)->counter); \
	 })

extern volatile int cpu_lock_cnt[];
extern volatile int irq_lock_cnt[];

extern volatile char cpu1_run_flag;

extern void __local_irq_disable(void);
extern void __local_irq_enable(void);
extern int __local_irq_lock_cnt(void);
extern void local_irq_disable(void);
extern void local_irq_enable(void);
extern void sys_local_irq_disable(void);
extern void sys_local_irq_enable(void);


#if 1
// low power
#define arch_spin_lock(lock) do{__asm__ volatile ( \
        " sevl          \n\t " \
        " 1:            \n\t " \
        " wfe           \n\t " \
        " testset b[%0] \n\t " \
        " ifeq goto 1b  \n\t " \
        :                      \
        : "p"(&(lock)->rwlock) \
        : "memory"             \
		);}while(0)


#define arch_spin_unlock(lock) do{__asm__ volatile ( \
        " b[%0] = %1    \n\t "          \
        " csync         \n\t "          \
        " sevg          \n\t "          \
        :                               \
        : "p"(&(lock)->rwlock), "r"(0)  \
        : "memory"                      \
		);}while(0)

#else
// normal
#define arch_spin_lock(lock) do{__asm__ volatile ( \
        " 1:            \n\t "  \
        " testset b[%0] \n\t "  \
        " ifeq goto 1b  \n\t "  \
        :                       \
        : "p"(&(lock)->rwlock)  \
        : "memory"              \
		);}while(0)

#define arch_spin_unlock(lock) do{__asm__ volatile ( \
        " b[%0] = %1    \n\t "         \
        :                              \
        : "p"(&(lock)->rwlock), "r"(0) \
        : "memory"                     \
		);}while(0)

#endif


#define	CPU_SR_ALLOC() 	\
//	int flags

#define CPU_CRITICAL_ENTER()  \
	do { \
		sys_local_irq_disable(); \
	}while(0)

#define CPU_CRITICAL_EXIT() \
	do { \
		sys_local_irq_enable(); \
	}while(0)

extern void cpu_reset(void);
extern void assert_reset(void);
extern void exception_reset(void);
extern void system_soft_reset(void);
extern void cpu_assert_debug(void);
extern const char *os_current_task_rom(void);
extern const int config_asser;
#define ASSERT(a,...)   \
        do { \
            if(config_asser){\
                if(!(a)){ \
                    printf("file:%s, line:%d, task:%s", __FILE__, __LINE__,os_current_task_rom()); \
                    printf("ASSERT-FAILD: " #a " " __VA_ARGS__); \
                    cpu_assert_debug(); \
                } \
            }else {\
                if(!(a)){ \
                    cpu_reset(); \
                }\
            }\
        }while(0);

#endif

/*#define MULU(Rm,Rn) __builtin_pi32_umul64(Rm,Rn);*/
/*#define MUL(Rm,Rn)  __builtin_pi32_smul64(Rm,Rn);*/
/*#define MLA(Rm,Rn)  __builtin_pi32_smla64(Rm,Rn);*/
/*#define MLA0(Rm,Rn) MUL(Rm,Rn);*/
/*#define MLS(Rm,Rn)  __builtin_pi32_smls64(Rm,Rn);*/
/*#define MLS0(Rm,Rn) MUL(-Rm,Rn);*/
/*#define MRSIS(Rm,Rn) (Rm = __builtin_pi32_sreadmacc(Rn));//mac read right shift imm&sat*/
/*#define MRSRS(Rm,Rn) (Rm = __builtin_pi32_sreadmacc(Rn)); //mac read right shift reg&sat*/
/*#define MACCLR()  __asm__ volatile ("clrmacc");*/
/*#define MACSET(h,l) __asm__ volatile ("mov maccl, %0; mov macch, %1"::"r" (l), "r" (h));*/
/*#define MACRL(l) __asm__ volatile ("mov %0, maccl":"=r" (l));*/
/*#define MACRH(l) __asm__ volatile ("mov %0, macch":"=r" (l));*/
/*#define MULSIS(Ro,Rm,Rn,Rp) MUL(Rm, Rn); MRSIS(Ro, Rp);*/
/*#define MULSRS(Ro,Rm,Rn,Rp) MUL(Rm, Rn); MRSRS(Ro, Rp);*/

#endif

