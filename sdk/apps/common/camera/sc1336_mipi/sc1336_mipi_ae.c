/******************************************************************************************
 *  File Name:  sc1336_mipi_ae.c
 *  Created on: 2024/7/31
 *  Author:
 ******************************************************************************************/
#include "sc1336_mipi_ae.h"
#include "sc1336_mipi.h"

#include "asm/isp_alg.h"

extern u32 sc1336_mipi_calc_shutter(isp_ae_shutter_t *shutter, u32 exp_time_us, u32 gain);
extern u32 sc1336_mipi_set_shutter(isp_ae_shutter_t *shutter);
extern void  *sc1336_mipi_get_ae_curve(u32 type, u32 fps, int *min_ev, int *max_ev);

//Anti-flicker:50Hz
const static u32 sc1336_mipi_ae_50hz_25fps[][AE_CURVE_INFO_MAX] = {

    // EV       ExpoTime    ISO     INTERPOLATE
    {9102000,     30,       100,    AE_INTERP_EXP},  // lv = 20
    {27306,    10000,       100,    AE_INTERP_GAIN}, // lv = 10.74
    {13653,    20000,       100,    AE_INTERP_GAIN},
    {6826,     40000,       100,    AE_INTERP_GAIN},
    {3413,     40000,       200,    AE_INTERP_GAIN},
    {1707,     40000,       400,    AE_INTERP_GAIN},
    {853,      40000,       800,    AE_INTERP_GAIN},
    {427,      40000,      1600,    AE_INTERP_GAIN},
    {213,      40000,      3200,    AE_INTERP_GAIN}, // lv = 3.73
    {106,      40000,      6400,    AE_INTERP_GAIN}, // lv = 3.73
    {53,       40000,     12800,    AE_INTERP_GAIN}, // lv = 3.73
    {26,       40000,     25600,    AE_INTERP_GAIN}, // lv = 3.73
    {0,        40000,     51200,    AE_INTERP_GAIN},
    {AE_CURVE_END, 0,         0,              0}
};

const static u32 sc1336_mipi_ae_50hz_30fps[][AE_CURVE_INFO_MAX] = {
    // EV       ExpoTime    ISO     INTERPOLATE
    {9102000,     30,       100,    AE_INTERP_EXP},  // lv = 20
    {27306,    10000,       100,    AE_INTERP_GAIN}, // lv = 10.74
    {13653,    20000,       100,    AE_INTERP_GAIN},
    {6826,     30000,       133,    AE_INTERP_GAIN},
    {3413,     30000,       266,    AE_INTERP_GAIN},
    {1707,     30000,       533,    AE_INTERP_GAIN},
    {853,      30000,      1066,    AE_INTERP_GAIN},
    {427,      30000,      2133,    AE_INTERP_GAIN},
    {213,      30000,      4266,    AE_INTERP_GAIN}, // lv = 3.73
    {106,      30000,      8532,    AE_INTERP_GAIN}, // lv = 3.73
    {53,       30000,     17064,    AE_INTERP_GAIN}, // lv = 3.73
    {26,       30000,     34128,    AE_INTERP_GAIN}, // lv = 3.73
    {0,        30000,     68256,    AE_INTERP_GAIN},
    {AE_CURVE_END, 0,         0,              0}
};

const static u32 sc1336_mipi_ae_60hz_30fps[][AE_CURVE_INFO_MAX] = {

    // EV       ExpoTime    ISO     INTERPOLATE
    {9102000,     30,       100,    AE_INTERP_EXP},  //lv = 20
    {32768,     8333,       100,    AE_INTERP_GAIN}, //lv=11
    {16348,    16666,       100,    AE_INTERP_GAIN},
    {8192,     33333,       100,    AE_INTERP_GAIN},
    {4096,     33333,       200,    AE_INTERP_GAIN},
    {2048,     33333,       400,    AE_INTERP_GAIN},
    {1024,     33333,       800,    AE_INTERP_GAIN},
    {512,      33333,      1600,    AE_INTERP_GAIN},
    {256,      33333,      3200,    AE_INTERP_GAIN}, //lv=4
    {128,      33333,      6400,    AE_INTERP_GAIN}, //lv=4
    {64,       33333,     12800,    AE_INTERP_GAIN}, //lv=4
    {32,       33333,     25600,    AE_INTERP_GAIN}, //lv=4
    {0,        33333,     51200,    AE_INTERP_GAIN},
    {AE_CURVE_END, 0,         0,              0}
};

const static u32 sc1336_mipi_ae_50hz_var_fps[][AE_CURVE_INFO_MAX] = {
    // EV       ExpoTime    ISO     INTERPOLATE

    {9102000,     30,       100,    AE_INTERP_EXP},  // lv = 20
    {27306,    10000,       100,    AE_INTERP_GAIN}, // lv = 10.74
    {13653,    20000,       100,    AE_INTERP_GAIN},
    {6826,     30000,       133,    AE_INTERP_GAIN},
    {3413,     40000,       200,    AE_INTERP_GAIN},
    {1707,     50000,       320,    AE_INTERP_GAIN}, // (40000*200*2(gain)/50000) from 25fps to 15fps
    {853,      60000,       533,    AE_INTERP_GAIN},
    {427,      60000,      1067,    AE_INTERP_GAIN},
    {213,      60000,      2133,    AE_INTERP_GAIN}, // lv = 3.73
    {0,        60000,      4267,    AE_INTERP_GAIN},
    {AE_CURVE_END, 0,         0,              0}
};

static u32 user_ev_value_table[] = {86, 98, 112, 128, 144, 162, 182}; //q7

static u8 ae_weight_cust[] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1
};

static isp_ae_params_t  sc1336_mipi_ae_params = {

    .ae_max_ev = AE_MAX_EV,
    .ae_min_ev = AE_MIN_EV,
    .ae_init_ev = AE_INIT_EV,

    .ae_curve_type = AE_CURVE_TYPE,

    .ae_target = AE_TARGET_LUMA,

    .ae_phase_comp = AE_PHASE_COMP,

    .ae_conver_h = AE_CONVER_H,
    .ae_conver_l = AE_CONVER_L,
    .ae_diver_h = AE_DIVER_H,
    .ae_diver_l = AE_DIVER_L,

    .ae_ratio_max_h = AE_RATIO_MAX_H,
    .ae_ratio_max_l = AE_RATIO_MAX_L,

    .ae_ratio_max2_h = AE_RATIO_MAX2_H,
    .ae_ratio_max2_l = AE_RATIO_MAX2_L,

    .ae_ratio_slope = AE_RATIO_SLOPE,

    .ae_expline_th = AE_EXPLINE_TH,

    .ae_luma_smooth_num = AE_LUMA_SMOOTH_NUM,

    .ae_user_ev_value_table = &user_ev_value_table,
    .ae_user_ev_value_table_size = sizeof(user_ev_value_table) / sizeof(u32),
    .ae_user_ev_value = 0, // centered to zero

    .ae_init_weight_type = AE_INIT_WEIGHT_TYPE,
    .ae_win_cust_weights = &ae_weight_cust,

    .ae_ops = {
        .calc_shutter = sc1336_mipi_calc_shutter,
        .set_shutter = sc1336_mipi_set_shutter,
        .get_ae_curve = sc1336_mipi_get_ae_curve,
    },

#if 1
    .ae_hl_comp_en = 1,
    .ae_hl_count_th0 = 5000,
    .ae_hl_count_th1 = 9500, // 10000
    .ae_hl_lv_th = 1024 * 1, // 8192
    .ae_hl_comp_max = 1024 * 13 / 10, // x2 gain
#endif // 0

};


void sc1336_mipi_ae_ev_init(u32 fps)
{
    u32 time, gain;
    int minev, maxev;
    static isp_ae_shutter_t ae_shutter;
    u32(*ae_curve)[AE_CURVE_INFO_MAX];

    ae_curve = sc1336_mipi_get_ae_curve(AE_CURVE_TYPE, fps, &minev, &maxev);
#ifdef ISP0_EN
    isp_ae_curve_interp(ae_curve, AE_INIT_EV, &time, &gain);
#endif

    sc1336_mipi_calc_shutter(&ae_shutter, time, gain);

    sc1336_mipi_set_shutter(&ae_shutter);
}

void  *sc1336_mipi_get_ae_curve(u32 type, u32 fps, int *min_ev, int *max_ev)
{
    void *curve;

    *min_ev = AE_MIN_EV;
    *max_ev = AE_MAX_EV;
    curve = &sc1336_mipi_ae_50hz_25fps;

    if (type == AE_CURVE_50HZ) {
        if (fps == 25) {
            curve = &sc1336_mipi_ae_50hz_25fps;
            x_printf("\n----ppk 25fps SC1336_MIPI ppk-----\n");
        } else if (fps == 30) {
            curve = &sc1336_mipi_ae_50hz_30fps;
            x_printf("\n----ppk 30fps SC1336_MIPI ppk-----\n");

        }
    } else {
        curve = &sc1336_mipi_ae_60hz_30fps;
        x_printf("\n----ppk 30fps 60hz SC1336_MIPI ppk-----\n");
    }

    return curve;
}

void *sc1336_mipi_get_ae_params()
{
    return (void *)&sc1336_mipi_ae_params;
}


