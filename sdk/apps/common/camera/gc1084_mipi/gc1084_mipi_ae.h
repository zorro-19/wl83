#ifndef __GC1084_AE_H__
#define __GC1084_AE_H__

#include "typedef.h"

#define AE_MAX_EV                   (9102000)
#define AE_MIN_EV                    512//220//((1<<5)*16)
#define AE_INIT_EV                  ((1 << 10) * 16)

#define AE_CURVE_TYPE               AE_CURVE_50HZ

#define AE_TARGET_LUMA              50

#define AE_PHASE_COMP               3

#define AE_LUMA_SMOOTH_NUM          3

#define AE_CONVER_H                 5//15//5
#define AE_CONVER_L                 5//15//5

#define AE_DIVER_H                  8
#define AE_DIVER_L                  8

#define AE_RATIO_MAX_H              2048    //base=1054
#define AE_RATIO_MAX_L              512     //base=1054

#define AE_RATIO_MAX2_H             1030//1036    //base=1054
#define AE_RATIO_MAX2_L             1018//1012    //base=1054

#define AE_RATIO_SLOPE              512     //base=1054

#define AE_EXPLINE_TH               0

#define AE_INIT_WEIGHT_TYPE         AE_WIN_WEIGHT_AVG

#endif // __GC1084_AE_H__
