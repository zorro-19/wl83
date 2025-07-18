#include "../../lv_examples.h"
#if LV_BUILD_EXAMPLES
#if LV_USE_RLOTTIE

/**
 * Load an lottie animation from flash
 */
void lv_example_rlottie_1(void)
{
    extern const uint8_t lv_example_rlottie_anim[];
    lv_obj_t *lottie1 = lv_rlottie_create_from_raw(lv_screen_active(), 480, 480, (const void *)lv_example_rlottie_anim);
    lv_obj_center(lottie1);

    extern const uint8_t lv_example_rlottie_approve[];
    lv_obj_t *lottie2 = lv_rlottie_create_from_raw(lv_screen_active(), 100, 100, (const void *)lv_example_rlottie_approve);
    lv_obj_center(lottie2);


    /*extern const char FingerprintRaw[];*/
    /*lv_obj_t *lottie3 = lv_rlottie_create_from_raw(lv_screen_active(), 32, 32, (const void*)FingerprintRaw);*/
    /*lv_obj_center(lottie3);*/
}

const uint8_t lv_example_rlottie_anim[] = {
    0x7B, 0x22, 0x76, 0x22, 0x3A, 0x22, 0x35, 0x2E, 0x36, 0x2E, 0x31, 0x30, 0x22, 0x2C, 0x22, 0x66,
    0x72, 0x22, 0x3A, 0x33, 0x30, 0x2C, 0x22, 0x69, 0x70, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6F, 0x70,
    0x22, 0x3A, 0x36, 0x31, 0x2C, 0x22, 0x77, 0x22, 0x3A, 0x34, 0x38, 0x30, 0x2C, 0x22, 0x68, 0x22,
    0x3A, 0x34, 0x38, 0x30, 0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0x79, 0x65, 0x6C, 0x6C, 0x6F,
    0x77, 0x22, 0x2C, 0x22, 0x64, 0x64, 0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x61, 0x73, 0x73, 0x65,
    0x74, 0x73, 0x22, 0x3A, 0x5B, 0x5D, 0x2C, 0x22, 0x6C, 0x61, 0x79, 0x65, 0x72, 0x73, 0x22, 0x3A,
    0x5B, 0x7B, 0x22, 0x64, 0x64, 0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x6E, 0x64, 0x22, 0x3A,
    0x31, 0x2C, 0x22, 0x74, 0x79, 0x22, 0x3A, 0x34, 0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0x34,
    0x22, 0x2C, 0x22, 0x73, 0x72, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x73, 0x22, 0x3A, 0x7B, 0x22,
    0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x7B,
    0x22, 0x69, 0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D,
    0x2C, 0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x7D, 0x2C, 0x22, 0x6F,
    0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x2C, 0x22,
    0x79, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22, 0x3A,
    0x31, 0x39, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x5B, 0x30, 0x5D, 0x7D, 0x2C, 0x7B, 0x22, 0x69, 0x22,
    0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22, 0x79,
    0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B,
    0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A,
    0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22, 0x3A, 0x32, 0x34, 0x2C,
    0x22, 0x73, 0x22, 0x3A, 0x5B, 0x31, 0x30, 0x30, 0x5D, 0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x22, 0x3A,
    0x36, 0x30, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x5B, 0x34, 0x32, 0x5D, 0x7D, 0x5D, 0x2C, 0x22, 0x69,
    0x78, 0x22, 0x3A, 0x31, 0x31, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A,
    0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x30, 0x7D,
    0x2C, 0x22, 0x70, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A,
    0x5B, 0x34, 0x38, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x32,
    0x7D, 0x2C, 0x22, 0x61, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22,
    0x3A, 0x5B, 0x32, 0x32, 0x36, 0x2E, 0x35, 0x37, 0x37, 0x2C, 0x2D, 0x32, 0x33, 0x38, 0x2E, 0x32,
    0x31, 0x37, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x7D, 0x2C, 0x22, 0x73,
    0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x7B, 0x22,
    0x69, 0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30,
    0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A,
    0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38,
    0x33, 0x33, 0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30,
    0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37,
    0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31,
    0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22, 0x3A, 0x31,
    0x39, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x5B, 0x37, 0x34, 0x2C, 0x37, 0x34, 0x2C, 0x31, 0x30, 0x30,
    0x5D, 0x7D, 0x2C, 0x7B, 0x22, 0x69, 0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E,
    0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D,
    0x2C, 0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33,
    0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22,
    0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C,
    0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36,
    0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C,
    0x22, 0x74, 0x22, 0x3A, 0x32, 0x34, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x5B, 0x38, 0x30, 0x2C, 0x38,
    0x30, 0x2C, 0x31, 0x30, 0x30, 0x5D, 0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x22, 0x3A, 0x36, 0x30, 0x2C,
    0x22, 0x73, 0x22, 0x3A, 0x5B, 0x31, 0x30, 0x33, 0x2C, 0x31, 0x30, 0x33, 0x2C, 0x31, 0x30, 0x30,
    0x5D, 0x7D, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x36, 0x7D, 0x7D, 0x2C, 0x22, 0x61, 0x6F,
    0x22, 0x3A, 0x30, 0x2C, 0x22, 0x73, 0x68, 0x61, 0x70, 0x65, 0x73, 0x22, 0x3A, 0x5B, 0x7B, 0x22,
    0x74, 0x79, 0x22, 0x3A, 0x22, 0x67, 0x72, 0x22, 0x2C, 0x22, 0x69, 0x74, 0x22, 0x3A, 0x5B, 0x7B,
    0x22, 0x64, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x74, 0x79, 0x22, 0x3A, 0x22, 0x65, 0x6C, 0x22, 0x2C,
    0x22, 0x73, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B,
    0x33, 0x39, 0x32, 0x2E, 0x38, 0x39, 0x32, 0x2C, 0x33, 0x39, 0x32, 0x2E, 0x38, 0x39, 0x32, 0x5D,
    0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x32, 0x7D, 0x2C, 0x22, 0x70, 0x22, 0x3A, 0x7B, 0x22, 0x61,
    0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69,
    0x78, 0x22, 0x3A, 0x33, 0x7D, 0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xCD, 0xD6, 0xD4, 0xB2,
    0xC2, 0xB7, 0xBE, 0xB6, 0x20, 0x31, 0x22, 0x2C, 0x22, 0x6D, 0x6E, 0x22, 0x3A, 0x22, 0x41, 0x44,
    0x42, 0x45, 0x20, 0x56, 0x65, 0x63, 0x74, 0x6F, 0x72, 0x20, 0x53, 0x68, 0x61, 0x70, 0x65, 0x20,
    0x2D, 0x20, 0x45, 0x6C, 0x6C, 0x69, 0x70, 0x73, 0x65, 0x22, 0x2C, 0x22, 0x68, 0x64, 0x22, 0x3A,
    0x66, 0x61, 0x6C, 0x73, 0x65, 0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x79, 0x22, 0x3A, 0x22, 0x66, 0x6C,
    0x22, 0x2C, 0x22, 0x63, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22,
    0x3A, 0x5B, 0x30, 0x2E, 0x39, 0x31, 0x32, 0x31, 0x37, 0x37, 0x31, 0x31, 0x32, 0x30, 0x35, 0x36,
    0x2C, 0x30, 0x2E, 0x37, 0x31, 0x32, 0x32, 0x30, 0x38, 0x37, 0x30, 0x36, 0x37, 0x32, 0x35, 0x2C,
    0x30, 0x2E, 0x33, 0x32, 0x30, 0x36, 0x30, 0x33, 0x38, 0x35, 0x33, 0x31, 0x31, 0x34, 0x2C, 0x31,
    0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x34, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22,
    0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x31, 0x30, 0x30, 0x2C, 0x22, 0x69, 0x78,
    0x22, 0x3A, 0x35, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A,
    0x30, 0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xCC, 0xEE, 0xB3, 0xE4, 0x20, 0x31, 0x22, 0x2C,
    0x22, 0x6D, 0x6E, 0x22, 0x3A, 0x22, 0x41, 0x44, 0x42, 0x45, 0x20, 0x56, 0x65, 0x63, 0x74, 0x6F,
    0x72, 0x20, 0x47, 0x72, 0x61, 0x70, 0x68, 0x69, 0x63, 0x20, 0x2D, 0x20, 0x46, 0x69, 0x6C, 0x6C,
    0x22, 0x2C, 0x22, 0x68, 0x64, 0x22, 0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x7D, 0x2C, 0x7B, 0x22,
    0x74, 0x79, 0x22, 0x3A, 0x22, 0x74, 0x72, 0x22, 0x2C, 0x22, 0x70, 0x22, 0x3A, 0x7B, 0x22, 0x61,
    0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x32, 0x32, 0x36, 0x2E, 0x35, 0x37, 0x37,
    0x2C, 0x2D, 0x32, 0x33, 0x38, 0x2E, 0x32, 0x31, 0x37, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A,
    0x32, 0x7D, 0x2C, 0x22, 0x61, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B,
    0x22, 0x3A, 0x5B, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x7D, 0x2C,
    0x22, 0x73, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B,
    0x31, 0x31, 0x36, 0x2E, 0x39, 0x38, 0x36, 0x2C, 0x31, 0x31, 0x36, 0x2E, 0x39, 0x38, 0x36, 0x5D,
    0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x33, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x7B, 0x22, 0x61,
    0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x36,
    0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22,
    0x3A, 0x31, 0x30, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x37, 0x7D, 0x2C, 0x22, 0x73, 0x6B,
    0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22,
    0x69, 0x78, 0x22, 0x3A, 0x34, 0x7D, 0x2C, 0x22, 0x73, 0x61, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x35, 0x7D,
    0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xB1, 0xE4, 0xBB, 0xBB, 0x22, 0x7D, 0x5D, 0x2C, 0x22,
    0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xCD, 0xD6, 0xD4, 0xB2, 0x20, 0x31, 0x22, 0x2C, 0x22, 0x6E, 0x70,
    0x22, 0x3A, 0x33, 0x2C, 0x22, 0x63, 0x69, 0x78, 0x22, 0x3A, 0x32, 0x2C, 0x22, 0x62, 0x6D, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6D, 0x6E, 0x22, 0x3A, 0x22,
    0x41, 0x44, 0x42, 0x45, 0x20, 0x56, 0x65, 0x63, 0x74, 0x6F, 0x72, 0x20, 0x47, 0x72, 0x6F, 0x75,
    0x70, 0x22, 0x2C, 0x22, 0x68, 0x64, 0x22, 0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x7D, 0x5D, 0x2C,
    0x22, 0x69, 0x70, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6F, 0x70, 0x22, 0x3A, 0x31, 0x35, 0x30, 0x2C,
    0x22, 0x73, 0x74, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A, 0x30, 0x7D, 0x2C, 0x7B,
    0x22, 0x64, 0x64, 0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x6E, 0x64, 0x22, 0x3A, 0x32, 0x2C,
    0x22, 0x74, 0x79, 0x22, 0x3A, 0x34, 0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0x31, 0x22, 0x2C,
    0x22, 0x73, 0x72, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x73, 0x22, 0x3A, 0x7B, 0x22, 0x6F, 0x22,
    0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x7B, 0x22, 0x69,
    0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22,
    0x79, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A,
    0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x2C, 0x22, 0x79, 0x22,
    0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22, 0x3A, 0x30, 0x2C,
    0x22, 0x73, 0x22, 0x3A, 0x5B, 0x31, 0x30, 0x30, 0x5D, 0x7D, 0x2C, 0x7B, 0x22, 0x69, 0x22, 0x3A,
    0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22, 0x79, 0x22,
    0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22,
    0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A, 0x5B,
    0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22, 0x3A, 0x32, 0x33, 0x2C, 0x22,
    0x73, 0x22, 0x3A, 0x5B, 0x37, 0x30, 0x5D, 0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x22, 0x3A, 0x36, 0x30,
    0x2C, 0x22, 0x73, 0x22, 0x3A, 0x5B, 0x33, 0x30, 0x5D, 0x7D, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22,
    0x3A, 0x31, 0x31, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C,
    0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x30, 0x7D, 0x2C, 0x22,
    0x70, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x34,
    0x38, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x32, 0x7D, 0x2C,
    0x22, 0x61, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B,
    0x32, 0x32, 0x36, 0x2E, 0x35, 0x37, 0x37, 0x2C, 0x2D, 0x32, 0x33, 0x38, 0x2E, 0x32, 0x31, 0x37,
    0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x7D, 0x2C, 0x22, 0x73, 0x22, 0x3A,
    0x7B, 0x22, 0x61, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x7B, 0x22, 0x69, 0x22,
    0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38,
    0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30,
    0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33,
    0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31,
    0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x2C,
    0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37,
    0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22, 0x3A, 0x30, 0x2C, 0x22,
    0x73, 0x22, 0x3A, 0x5B, 0x38, 0x32, 0x2C, 0x38, 0x32, 0x2C, 0x31, 0x30, 0x30, 0x5D, 0x7D, 0x2C,
    0x7B, 0x22, 0x69, 0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33,
    0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22, 0x79,
    0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30,
    0x2E, 0x38, 0x33, 0x33, 0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A,
    0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31,
    0x36, 0x37, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30,
    0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22,
    0x3A, 0x33, 0x30, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x5B, 0x31, 0x30, 0x32, 0x2C, 0x31, 0x30, 0x32,
    0x2C, 0x31, 0x30, 0x30, 0x5D, 0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x22, 0x3A, 0x36, 0x30, 0x2C, 0x22,
    0x73, 0x22, 0x3A, 0x5B, 0x31, 0x32, 0x32, 0x2C, 0x31, 0x32, 0x32, 0x2C, 0x31, 0x30, 0x30, 0x5D,
    0x7D, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x36, 0x7D, 0x7D, 0x2C, 0x22, 0x61, 0x6F, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x73, 0x68, 0x61, 0x70, 0x65, 0x73, 0x22, 0x3A, 0x5B, 0x7B, 0x22, 0x74,
    0x79, 0x22, 0x3A, 0x22, 0x67, 0x72, 0x22, 0x2C, 0x22, 0x69, 0x74, 0x22, 0x3A, 0x5B, 0x7B, 0x22,
    0x64, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x74, 0x79, 0x22, 0x3A, 0x22, 0x65, 0x6C, 0x22, 0x2C, 0x22,
    0x73, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x33,
    0x39, 0x32, 0x2E, 0x38, 0x39, 0x32, 0x2C, 0x33, 0x39, 0x32, 0x2E, 0x38, 0x39, 0x32, 0x5D, 0x2C,
    0x22, 0x69, 0x78, 0x22, 0x3A, 0x32, 0x7D, 0x2C, 0x22, 0x70, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78,
    0x22, 0x3A, 0x33, 0x7D, 0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xCD, 0xD6, 0xD4, 0xB2, 0xC2,
    0xB7, 0xBE, 0xB6, 0x20, 0x31, 0x22, 0x2C, 0x22, 0x6D, 0x6E, 0x22, 0x3A, 0x22, 0x41, 0x44, 0x42,
    0x45, 0x20, 0x56, 0x65, 0x63, 0x74, 0x6F, 0x72, 0x20, 0x53, 0x68, 0x61, 0x70, 0x65, 0x20, 0x2D,
    0x20, 0x45, 0x6C, 0x6C, 0x69, 0x70, 0x73, 0x65, 0x22, 0x2C, 0x22, 0x68, 0x64, 0x22, 0x3A, 0x66,
    0x61, 0x6C, 0x73, 0x65, 0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x79, 0x22, 0x3A, 0x22, 0x66, 0x6C, 0x22,
    0x2C, 0x22, 0x63, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A,
    0x5B, 0x30, 0x2E, 0x39, 0x35, 0x32, 0x39, 0x34, 0x31, 0x32, 0x33, 0x36, 0x33, 0x30, 0x39, 0x2C,
    0x30, 0x2E, 0x37, 0x35, 0x36, 0x38, 0x36, 0x32, 0x38, 0x30, 0x34, 0x39, 0x33, 0x36, 0x2C, 0x30,
    0x2E, 0x33, 0x36, 0x34, 0x37, 0x30, 0x35, 0x38, 0x38, 0x32, 0x33, 0x35, 0x33, 0x2C, 0x31, 0x5D,
    0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x34, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x61,
    0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x31, 0x30, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22,
    0x3A, 0x35, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A, 0x30,
    0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xCC, 0xEE, 0xB3, 0xE4, 0x20, 0x31, 0x22, 0x2C, 0x22,
    0x6D, 0x6E, 0x22, 0x3A, 0x22, 0x41, 0x44, 0x42, 0x45, 0x20, 0x56, 0x65, 0x63, 0x74, 0x6F, 0x72,
    0x20, 0x47, 0x72, 0x61, 0x70, 0x68, 0x69, 0x63, 0x20, 0x2D, 0x20, 0x46, 0x69, 0x6C, 0x6C, 0x22,
    0x2C, 0x22, 0x68, 0x64, 0x22, 0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x7D, 0x2C, 0x7B, 0x22, 0x74,
    0x79, 0x22, 0x3A, 0x22, 0x74, 0x72, 0x22, 0x2C, 0x22, 0x70, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x32, 0x32, 0x36, 0x2E, 0x35, 0x37, 0x37, 0x2C,
    0x2D, 0x32, 0x33, 0x38, 0x2E, 0x32, 0x31, 0x37, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x32,
    0x7D, 0x2C, 0x22, 0x61, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22,
    0x3A, 0x5B, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x7D, 0x2C, 0x22,
    0x73, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x31,
    0x31, 0x36, 0x2E, 0x39, 0x38, 0x36, 0x2C, 0x31, 0x31, 0x36, 0x2E, 0x39, 0x38, 0x36, 0x5D, 0x2C,
    0x22, 0x69, 0x78, 0x22, 0x3A, 0x33, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x36, 0x7D,
    0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A,
    0x31, 0x30, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x37, 0x7D, 0x2C, 0x22, 0x73, 0x6B, 0x22,
    0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69,
    0x78, 0x22, 0x3A, 0x34, 0x7D, 0x2C, 0x22, 0x73, 0x61, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A,
    0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x35, 0x7D, 0x2C,
    0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xB1, 0xE4, 0xBB, 0xBB, 0x22, 0x7D, 0x5D, 0x2C, 0x22, 0x6E,
    0x6D, 0x22, 0x3A, 0x22, 0xCD, 0xD6, 0xD4, 0xB2, 0x20, 0x31, 0x22, 0x2C, 0x22, 0x6E, 0x70, 0x22,
    0x3A, 0x33, 0x2C, 0x22, 0x63, 0x69, 0x78, 0x22, 0x3A, 0x32, 0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A,
    0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6D, 0x6E, 0x22, 0x3A, 0x22, 0x41,
    0x44, 0x42, 0x45, 0x20, 0x56, 0x65, 0x63, 0x74, 0x6F, 0x72, 0x20, 0x47, 0x72, 0x6F, 0x75, 0x70,
    0x22, 0x2C, 0x22, 0x68, 0x64, 0x22, 0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x7D, 0x5D, 0x2C, 0x22,
    0x69, 0x70, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6F, 0x70, 0x22, 0x3A, 0x31, 0x35, 0x30, 0x2C, 0x22,
    0x73, 0x74, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A, 0x30, 0x7D, 0x2C, 0x7B, 0x22,
    0x64, 0x64, 0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x6E, 0x64, 0x22, 0x3A, 0x33, 0x2C, 0x22,
    0x74, 0x79, 0x22, 0x3A, 0x34, 0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0x32, 0x22, 0x2C, 0x22,
    0x73, 0x72, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x73, 0x22, 0x3A, 0x7B, 0x22, 0x6F, 0x22, 0x3A,
    0x7B, 0x22, 0x61, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x7B, 0x22, 0x69, 0x22,
    0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22, 0x79,
    0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B,
    0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A,
    0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22, 0x3A, 0x30, 0x2C, 0x22,
    0x73, 0x22, 0x3A, 0x5B, 0x31, 0x30, 0x30, 0x5D, 0x7D, 0x2C, 0x7B, 0x22, 0x69, 0x22, 0x3A, 0x7B,
    0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A,
    0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x78,
    0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30,
    0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22, 0x3A, 0x33, 0x30, 0x2C, 0x22, 0x73,
    0x22, 0x3A, 0x5B, 0x36, 0x30, 0x5D, 0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x22, 0x3A, 0x36, 0x30, 0x2C,
    0x22, 0x73, 0x22, 0x3A, 0x5B, 0x30, 0x5D, 0x7D, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31,
    0x31, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B,
    0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x30, 0x7D, 0x2C, 0x22, 0x70, 0x22,
    0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x34, 0x38, 0x30,
    0x2C, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x32, 0x7D, 0x2C, 0x22, 0x61,
    0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x32, 0x32,
    0x36, 0x2E, 0x35, 0x37, 0x37, 0x2C, 0x2D, 0x32, 0x33, 0x38, 0x2E, 0x32, 0x31, 0x37, 0x2C, 0x30,
    0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x7D, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x7B, 0x22,
    0x61, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x7B, 0x22, 0x69, 0x22, 0x3A, 0x7B,
    0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33,
    0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38,
    0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x7D,
    0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37,
    0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x2C, 0x22, 0x79,
    0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30,
    0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x73, 0x22,
    0x3A, 0x5B, 0x31, 0x30, 0x32, 0x2C, 0x31, 0x30, 0x32, 0x2C, 0x31, 0x30, 0x30, 0x5D, 0x7D, 0x2C,
    0x7B, 0x22, 0x69, 0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33,
    0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22, 0x79,
    0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30,
    0x2E, 0x38, 0x33, 0x33, 0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A,
    0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31,
    0x36, 0x37, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30,
    0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22,
    0x3A, 0x33, 0x30, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x5B, 0x31, 0x32, 0x32, 0x2C, 0x31, 0x32, 0x32,
    0x2C, 0x31, 0x30, 0x30, 0x5D, 0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x22, 0x3A, 0x36, 0x30, 0x2C, 0x22,
    0x73, 0x22, 0x3A, 0x5B, 0x31, 0x34, 0x32, 0x2C, 0x31, 0x34, 0x32, 0x2C, 0x31, 0x30, 0x30, 0x5D,
    0x7D, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x36, 0x7D, 0x7D, 0x2C, 0x22, 0x61, 0x6F, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x73, 0x68, 0x61, 0x70, 0x65, 0x73, 0x22, 0x3A, 0x5B, 0x7B, 0x22, 0x74,
    0x79, 0x22, 0x3A, 0x22, 0x67, 0x72, 0x22, 0x2C, 0x22, 0x69, 0x74, 0x22, 0x3A, 0x5B, 0x7B, 0x22,
    0x64, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x74, 0x79, 0x22, 0x3A, 0x22, 0x65, 0x6C, 0x22, 0x2C, 0x22,
    0x73, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x33,
    0x39, 0x32, 0x2E, 0x38, 0x39, 0x32, 0x2C, 0x33, 0x39, 0x32, 0x2E, 0x38, 0x39, 0x32, 0x5D, 0x2C,
    0x22, 0x69, 0x78, 0x22, 0x3A, 0x32, 0x7D, 0x2C, 0x22, 0x70, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78,
    0x22, 0x3A, 0x33, 0x7D, 0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xCD, 0xD6, 0xD4, 0xB2, 0xC2,
    0xB7, 0xBE, 0xB6, 0x20, 0x31, 0x22, 0x2C, 0x22, 0x6D, 0x6E, 0x22, 0x3A, 0x22, 0x41, 0x44, 0x42,
    0x45, 0x20, 0x56, 0x65, 0x63, 0x74, 0x6F, 0x72, 0x20, 0x53, 0x68, 0x61, 0x70, 0x65, 0x20, 0x2D,
    0x20, 0x45, 0x6C, 0x6C, 0x69, 0x70, 0x73, 0x65, 0x22, 0x2C, 0x22, 0x68, 0x64, 0x22, 0x3A, 0x66,
    0x61, 0x6C, 0x73, 0x65, 0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x79, 0x22, 0x3A, 0x22, 0x66, 0x6C, 0x22,
    0x2C, 0x22, 0x63, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A,
    0x5B, 0x30, 0x2E, 0x39, 0x36, 0x30, 0x37, 0x38, 0x34, 0x33, 0x37, 0x33, 0x35, 0x36, 0x34, 0x2C,
    0x30, 0x2E, 0x38, 0x30, 0x33, 0x39, 0x32, 0x31, 0x36, 0x32, 0x38, 0x34, 0x36, 0x36, 0x2C, 0x30,
    0x2E, 0x34, 0x38, 0x32, 0x33, 0x35, 0x32, 0x39, 0x37, 0x31, 0x30, 0x39, 0x36, 0x2C, 0x31, 0x5D,
    0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x34, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x61,
    0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x31, 0x30, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22,
    0x3A, 0x35, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A, 0x30,
    0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xCC, 0xEE, 0xB3, 0xE4, 0x20, 0x31, 0x22, 0x2C, 0x22,
    0x6D, 0x6E, 0x22, 0x3A, 0x22, 0x41, 0x44, 0x42, 0x45, 0x20, 0x56, 0x65, 0x63, 0x74, 0x6F, 0x72,
    0x20, 0x47, 0x72, 0x61, 0x70, 0x68, 0x69, 0x63, 0x20, 0x2D, 0x20, 0x46, 0x69, 0x6C, 0x6C, 0x22,
    0x2C, 0x22, 0x68, 0x64, 0x22, 0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x7D, 0x2C, 0x7B, 0x22, 0x74,
    0x79, 0x22, 0x3A, 0x22, 0x74, 0x72, 0x22, 0x2C, 0x22, 0x70, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x32, 0x32, 0x36, 0x2E, 0x35, 0x37, 0x37, 0x2C,
    0x2D, 0x32, 0x33, 0x38, 0x2E, 0x32, 0x31, 0x37, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x32,
    0x7D, 0x2C, 0x22, 0x61, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22,
    0x3A, 0x5B, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x7D, 0x2C, 0x22,
    0x73, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x31,
    0x31, 0x36, 0x2E, 0x39, 0x38, 0x36, 0x2C, 0x31, 0x31, 0x36, 0x2E, 0x39, 0x38, 0x36, 0x5D, 0x2C,
    0x22, 0x69, 0x78, 0x22, 0x3A, 0x33, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x36, 0x7D,
    0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A,
    0x31, 0x30, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x37, 0x7D, 0x2C, 0x22, 0x73, 0x6B, 0x22,
    0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69,
    0x78, 0x22, 0x3A, 0x34, 0x7D, 0x2C, 0x22, 0x73, 0x61, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A,
    0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x35, 0x7D, 0x2C,
    0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xB1, 0xE4, 0xBB, 0xBB, 0x22, 0x7D, 0x5D, 0x2C, 0x22, 0x6E,
    0x6D, 0x22, 0x3A, 0x22, 0xCD, 0xD6, 0xD4, 0xB2, 0x20, 0x31, 0x22, 0x2C, 0x22, 0x6E, 0x70, 0x22,
    0x3A, 0x33, 0x2C, 0x22, 0x63, 0x69, 0x78, 0x22, 0x3A, 0x32, 0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A,
    0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6D, 0x6E, 0x22, 0x3A, 0x22, 0x41,
    0x44, 0x42, 0x45, 0x20, 0x56, 0x65, 0x63, 0x74, 0x6F, 0x72, 0x20, 0x47, 0x72, 0x6F, 0x75, 0x70,
    0x22, 0x2C, 0x22, 0x68, 0x64, 0x22, 0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x7D, 0x5D, 0x2C, 0x22,
    0x69, 0x70, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6F, 0x70, 0x22, 0x3A, 0x31, 0x35, 0x30, 0x2C, 0x22,
    0x73, 0x74, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A, 0x30, 0x7D, 0x2C, 0x7B, 0x22,
    0x64, 0x64, 0x64, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x6E, 0x64, 0x22, 0x3A, 0x34, 0x2C, 0x22,
    0x74, 0x79, 0x22, 0x3A, 0x34, 0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0x33, 0x22, 0x2C, 0x22,
    0x73, 0x72, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x73, 0x22, 0x3A, 0x7B, 0x22, 0x6F, 0x22, 0x3A,
    0x7B, 0x22, 0x61, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x7B, 0x22, 0x69, 0x22,
    0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22, 0x79,
    0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B,
    0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A,
    0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22, 0x3A, 0x30, 0x2C, 0x22,
    0x73, 0x22, 0x3A, 0x5B, 0x31, 0x30, 0x30, 0x5D, 0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x22, 0x3A, 0x33,
    0x30, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x5B, 0x30, 0x5D, 0x7D, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22,
    0x3A, 0x31, 0x31, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C,
    0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x30, 0x7D, 0x2C, 0x22,
    0x70, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x34,
    0x38, 0x30, 0x2C, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x32, 0x7D, 0x2C,
    0x22, 0x61, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B,
    0x32, 0x32, 0x36, 0x2E, 0x35, 0x37, 0x37, 0x2C, 0x2D, 0x32, 0x33, 0x38, 0x2E, 0x32, 0x31, 0x37,
    0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x7D, 0x2C, 0x22, 0x73, 0x22, 0x3A,
    0x7B, 0x22, 0x61, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x7B, 0x22, 0x69, 0x22,
    0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38,
    0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x5D, 0x2C, 0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30,
    0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33, 0x2C, 0x30, 0x2E, 0x38, 0x33, 0x33,
    0x5D, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x78, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31,
    0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x2C,
    0x22, 0x79, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37,
    0x2C, 0x30, 0x2E, 0x31, 0x36, 0x37, 0x5D, 0x7D, 0x2C, 0x22, 0x74, 0x22, 0x3A, 0x30, 0x2C, 0x22,
    0x73, 0x22, 0x3A, 0x5B, 0x31, 0x32, 0x32, 0x2C, 0x31, 0x32, 0x32, 0x2C, 0x31, 0x30, 0x30, 0x5D,
    0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x22, 0x3A, 0x33, 0x30, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x5B, 0x31,
    0x34, 0x32, 0x2C, 0x31, 0x34, 0x32, 0x2C, 0x31, 0x30, 0x30, 0x5D, 0x7D, 0x5D, 0x2C, 0x22, 0x69,
    0x78, 0x22, 0x3A, 0x36, 0x7D, 0x7D, 0x2C, 0x22, 0x61, 0x6F, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x73,
    0x68, 0x61, 0x70, 0x65, 0x73, 0x22, 0x3A, 0x5B, 0x7B, 0x22, 0x74, 0x79, 0x22, 0x3A, 0x22, 0x67,
    0x72, 0x22, 0x2C, 0x22, 0x69, 0x74, 0x22, 0x3A, 0x5B, 0x7B, 0x22, 0x64, 0x22, 0x3A, 0x31, 0x2C,
    0x22, 0x74, 0x79, 0x22, 0x3A, 0x22, 0x65, 0x6C, 0x22, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x7B, 0x22,
    0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x33, 0x39, 0x32, 0x2E, 0x38, 0x39,
    0x32, 0x2C, 0x33, 0x39, 0x32, 0x2E, 0x38, 0x39, 0x32, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A,
    0x32, 0x7D, 0x2C, 0x22, 0x70, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B,
    0x22, 0x3A, 0x5B, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x33, 0x7D, 0x2C,
    0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xCD, 0xD6, 0xD4, 0xB2, 0xC2, 0xB7, 0xBE, 0xB6, 0x20, 0x31,
    0x22, 0x2C, 0x22, 0x6D, 0x6E, 0x22, 0x3A, 0x22, 0x41, 0x44, 0x42, 0x45, 0x20, 0x56, 0x65, 0x63,
    0x74, 0x6F, 0x72, 0x20, 0x53, 0x68, 0x61, 0x70, 0x65, 0x20, 0x2D, 0x20, 0x45, 0x6C, 0x6C, 0x69,
    0x70, 0x73, 0x65, 0x22, 0x2C, 0x22, 0x68, 0x64, 0x22, 0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x7D,
    0x2C, 0x7B, 0x22, 0x74, 0x79, 0x22, 0x3A, 0x22, 0x66, 0x6C, 0x22, 0x2C, 0x22, 0x63, 0x22, 0x3A,
    0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x30, 0x2E, 0x39, 0x37,
    0x36, 0x34, 0x37, 0x30, 0x36, 0x34, 0x38, 0x30, 0x37, 0x34, 0x2C, 0x30, 0x2E, 0x38, 0x35, 0x34,
    0x39, 0x30, 0x32, 0x30, 0x32, 0x30, 0x36, 0x32, 0x33, 0x2C, 0x30, 0x2E, 0x36, 0x32, 0x33, 0x35,
    0x32, 0x39, 0x34, 0x31, 0x31, 0x37, 0x36, 0x35, 0x2C, 0x31, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22,
    0x3A, 0x34, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22,
    0x6B, 0x22, 0x3A, 0x31, 0x30, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x35, 0x7D, 0x2C, 0x22,
    0x72, 0x22, 0x3A, 0x31, 0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6E, 0x6D, 0x22,
    0x3A, 0x22, 0xCC, 0xEE, 0xB3, 0xE4, 0x20, 0x31, 0x22, 0x2C, 0x22, 0x6D, 0x6E, 0x22, 0x3A, 0x22,
    0x41, 0x44, 0x42, 0x45, 0x20, 0x56, 0x65, 0x63, 0x74, 0x6F, 0x72, 0x20, 0x47, 0x72, 0x61, 0x70,
    0x68, 0x69, 0x63, 0x20, 0x2D, 0x20, 0x46, 0x69, 0x6C, 0x6C, 0x22, 0x2C, 0x22, 0x68, 0x64, 0x22,
    0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x7D, 0x2C, 0x7B, 0x22, 0x74, 0x79, 0x22, 0x3A, 0x22, 0x74,
    0x72, 0x22, 0x2C, 0x22, 0x70, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B,
    0x22, 0x3A, 0x5B, 0x32, 0x32, 0x36, 0x2E, 0x35, 0x37, 0x37, 0x2C, 0x2D, 0x32, 0x33, 0x38, 0x2E,
    0x32, 0x31, 0x37, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x32, 0x7D, 0x2C, 0x22, 0x61, 0x22,
    0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x30, 0x2C, 0x30,
    0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x7D, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x7B, 0x22,
    0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x31, 0x31, 0x36, 0x2E, 0x39, 0x38,
    0x36, 0x2C, 0x31, 0x31, 0x36, 0x2E, 0x39, 0x38, 0x36, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A,
    0x33, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B,
    0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x36, 0x7D, 0x2C, 0x22, 0x6F, 0x22, 0x3A,
    0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x31, 0x30, 0x30, 0x2C, 0x22,
    0x69, 0x78, 0x22, 0x3A, 0x37, 0x7D, 0x2C, 0x22, 0x73, 0x6B, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x34, 0x7D,
    0x2C, 0x22, 0x73, 0x61, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x35, 0x7D, 0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A,
    0x22, 0xB1, 0xE4, 0xBB, 0xBB, 0x22, 0x7D, 0x5D, 0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0xCD,
    0xD6, 0xD4, 0xB2, 0x20, 0x31, 0x22, 0x2C, 0x22, 0x6E, 0x70, 0x22, 0x3A, 0x33, 0x2C, 0x22, 0x63,
    0x69, 0x78, 0x22, 0x3A, 0x32, 0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78,
    0x22, 0x3A, 0x31, 0x2C, 0x22, 0x6D, 0x6E, 0x22, 0x3A, 0x22, 0x41, 0x44, 0x42, 0x45, 0x20, 0x56,
    0x65, 0x63, 0x74, 0x6F, 0x72, 0x20, 0x47, 0x72, 0x6F, 0x75, 0x70, 0x22, 0x2C, 0x22, 0x68, 0x64,
    0x22, 0x3A, 0x66, 0x61, 0x6C, 0x73, 0x65, 0x7D, 0x5D, 0x2C, 0x22, 0x69, 0x70, 0x22, 0x3A, 0x30,
    0x2C, 0x22, 0x6F, 0x70, 0x22, 0x3A, 0x31, 0x35, 0x30, 0x2C, 0x22, 0x73, 0x74, 0x22, 0x3A, 0x30,
    0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A, 0x30, 0x7D, 0x2C, 0x7B, 0x22, 0x64, 0x64, 0x64, 0x22, 0x3A,
    0x30, 0x2C, 0x22, 0x69, 0x6E, 0x64, 0x22, 0x3A, 0x35, 0x2C, 0x22, 0x74, 0x79, 0x22, 0x3A, 0x31,
    0x2C, 0x22, 0x6E, 0x6D, 0x22, 0x3A, 0x22, 0x62, 0x67, 0x22, 0x2C, 0x22, 0x73, 0x72, 0x22, 0x3A,
    0x31, 0x2C, 0x22, 0x6B, 0x73, 0x22, 0x3A, 0x7B, 0x22, 0x6F, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22,
    0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x31, 0x30, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A,
    0x31, 0x31, 0x7D, 0x2C, 0x22, 0x72, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22,
    0x6B, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x31, 0x30, 0x7D, 0x2C, 0x22, 0x70,
    0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A, 0x5B, 0x32, 0x34,
    0x30, 0x2C, 0x32, 0x34, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x32, 0x7D,
    0x2C, 0x22, 0x61, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6B, 0x22, 0x3A,
    0x5B, 0x32, 0x34, 0x30, 0x2C, 0x32, 0x34, 0x30, 0x2C, 0x30, 0x5D, 0x2C, 0x22, 0x69, 0x78, 0x22,
    0x3A, 0x31, 0x7D, 0x2C, 0x22, 0x73, 0x22, 0x3A, 0x7B, 0x22, 0x61, 0x22, 0x3A, 0x30, 0x2C, 0x22,
    0x6B, 0x22, 0x3A, 0x5B, 0x31, 0x30, 0x30, 0x2C, 0x31, 0x30, 0x30, 0x2C, 0x31, 0x30, 0x30, 0x5D,
    0x2C, 0x22, 0x69, 0x78, 0x22, 0x3A, 0x36, 0x7D, 0x7D, 0x2C, 0x22, 0x61, 0x6F, 0x22, 0x3A, 0x30,
    0x2C, 0x22, 0x73, 0x77, 0x22, 0x3A, 0x34, 0x38, 0x30, 0x2C, 0x22, 0x73, 0x68, 0x22, 0x3A, 0x34,
    0x38, 0x30, 0x2C, 0x22, 0x73, 0x63, 0x22, 0x3A, 0x22, 0x23, 0x66, 0x61, 0x65, 0x33, 0x62, 0x34,
    0x22, 0x2C, 0x22, 0x69, 0x70, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x6F, 0x70, 0x22, 0x3A, 0x31, 0x35,
    0x30, 0x2C, 0x22, 0x73, 0x74, 0x22, 0x3A, 0x30, 0x2C, 0x22, 0x62, 0x6D, 0x22, 0x3A, 0x30, 0x7D,
    0x5D, 0x2C, 0x22, 0x6D, 0x61, 0x72, 0x6B, 0x65, 0x72, 0x73, 0x22, 0x3A, 0x5B, 0x5D, 0x7D
};

#else
void lv_example_rlottie_1(void)
{
    /*TODO
     *fallback for online examples*/

    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Rlottie is not installed");
    lv_obj_center(label);
}

#endif
#endif
