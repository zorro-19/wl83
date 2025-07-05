#ifndef FPE_FF1_H
#define FPE_FF1_H

#include <stdlib.h>
//#include <stdbool.h>
#include <stdint.h>

#define INPUT_MIN_LENGTH 2
#define INPUT_MAX_LENGTH 18

#define INVALID_KEY_LENGTH 1
#define INVALID_INPUT_LENGTH 2
#define INVALID_TWEAK_LENGTH 3

typedef struct {
    uint8_t *buf;
    int len;
} byte_str, num_str;

#ifdef FPE_LOG_PRINT
#define  FPE_PRINT_STR(s, round, desc, ctx) \
    printf("Round #%d,%s is:\t[", round, desc);\
    for (int i = 0; i < s.len; i++) {\
        printf("%d,", s.buf[i]);\
    }\
    printf("]\n");
#else
#define FPE_PRINT_STR(s, round, desc, ctx)
#endif

void fpe_release_str(byte_str s);
num_str decrypt(byte_str key, byte_str tweak, num_str cipher);

#endif //FPE_FF1_H
