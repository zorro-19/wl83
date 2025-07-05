#ifndef VIRTUALBASS_API_H
#define VIRTUALBASS_API_H

#include "AudioEffect_DataType.h"

#ifdef WIN32

#define AT_VBSS(x)
#define AT_VBSS_CODE
#define AT_VBSS_CONST
#define AT_VBSS_SPARSE_CODE
#define AT_VBSS_SPARSE_CONST

#else
#define AT_VBSS(x)           __attribute((section(#x)))
#define AT_VBSS_CODE         AT_VBSS(.vbss_code)
#define AT_VBSS_CONST        AT_VBSS(.vbss_const)
#define AT_VBSS_SPARSE_CODE  AT_VBSS(.vbss_sparse_code)
#define AT_VBSS_SPARSE_CONST AT_VBSS(.vbss_sparse_const)
#endif


typedef struct _VirtualBassParam {
    int ratio;  //Virtual bass intensity 虚拟低音强度建议值 4-10
    int boost;  //Automatic gain switch  1:on  0:off
    int fc;     //cut-off frequency 截止频率建议值 40-100
    int channel;
    int SampleRate;
    af_DataType pcm_info;
} VirtualBassParam;

int getVirtualBassBuf();
int VirtualBassInit(void *WorkBuf, VirtualBassParam *param);
int VirtualBassReserveLowFreq(void *WorkBuf, VirtualBassParam *param, int ReserveLowFreqEnable);
void VirtualBassUpdate(void *WorkBuf, VirtualBassParam *param);
int VirtualBassRun(void *WorkBuf, int *tmpbuf, void *in, void *out, int per_channel_npoint);
#endif // !VIRTUALBASS_API_H


