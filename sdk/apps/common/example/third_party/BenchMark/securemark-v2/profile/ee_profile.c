/*
 * Copyright (C) EEMBC(R). All Rights Reserved
 *
 * All EEMBC Benchmark Software are products of EEMBC and are provided under the
 * terms of the EEMBC Benchmark License Agreements. The EEMBC Benchmark Software
 * are proprietary intellectual properties of EEMBC and its Members and is
 * protected under all applicable laws, including all applicable copyright laws.
 *
 * If you received this EEMBC Benchmark Software without having a currently
 * effective EEMBC Benchmark License Agreement, you must discontinue use.
 */

#include "ee_profile.h"

#if EE_CFG_SELFHOSTED != 1

/* See `th_api/th_lib.c` for explanation */
extern bool g_mute_timestamps;

/* Verify mode means extra output will be sent to the host. */
static bool g_verify_mode = false;

arg_claimed_t
ee_profile_parse(char *p_command)
{
    char *p_next;
    long  hex;

    if (th_strncmp(p_command, "profile", EE_CMD_SIZE) == 0) {
        th_printf("m-profile[%s]\r\n", EE_FW_VERSION);
    } else if (th_strncmp(p_command, "verify", EE_CMD_SIZE) == 0) {
        p_next = th_strtok(NULL, EE_CMD_DELIMITER);
        if (p_next) {
            g_verify_mode = (th_atoi(p_next) != 0);
        }
        th_printf("m-verify[%s]\r\n", g_verify_mode ? "on" : "off");
    } else if (th_strncmp(p_command, "timer", EE_CMD_SIZE) == 0) {
        p_next = th_strtok(NULL, EE_CMD_DELIMITER);
        if (p_next) {
            g_mute_timestamps = (th_atoi(p_next) != 0);
        }
        th_printf("m-timer[%s]\r\n", g_mute_timestamps ? "on" : "off");
    } else if (th_strncmp(p_command, "srand", EE_CMD_SIZE) == 0) {
        p_next = th_strtok(NULL, EE_CMD_DELIMITER);

        if (p_next == NULL) {
            th_printf("e-[Command srand requires a seed byte, in hex]\r\n");
        } else {
            hex = ee_hexdec(p_next);

            if (hex < 0) {
                th_printf("e-[Invalid hex byte given to srand: %s]\r\n",
                          p_next);
            } else {
                ee_srand((uint8_t)hex);
            }
        }
    } else if (th_strncmp(p_command, "help", EE_CMD_SIZE) == 0) {
        th_printf("%s\r\n", EE_FW_VERSION);
        th_printf("\r\n");
        th_printf(
            "help                : Print this information\r\n"
            "name                : Print the name of this device\r\n"
            "profile             : Print the benchmark profile & version\r\n"
            "verify [0|1]        : Get or set verify mode\r\n"
            "timer [0|1]         : Get or set timestamp generation\r\n"
            "srand XX            : Seed the PSRN with a hex byte, e.g 7F\r\n"
            "bench SUBCMD S N I  : Issue a 'bench' subcommand & parameters\r\n"
            "  sha[256|384]\r\n"
            "  aes[128|256]-[ecb|ctr|ccm|gcm]-[enc|dec]\r\n"
            "  chachapoly-[enc|dec]\r\n"
            "  ecdh-[p256|p384]\r\n"
            "  ecdsa-[p256|p384|ed25519]-[sign|verify]\r\n"
            "  rsa[1024|3072|4096]-verify\r\n"
            "  var01             :Varation #1 (mixed contexts)\r\n"
            "     Where S N I = seed datasize #iterations\r\n"
            "     Each subcmd takes a PRNG seed, #bytes & #iterations\r\n"
            "buffer SUBCMD       : Issue a 'buffer' subcommand\r\n"
            "  fill XX           : File the buffer with XX hex byte\r\n"
            "  add XX[ XX]*      : Add hex byte(s) XX to current buffer\r\n"
            "                      pointer (it will wrap)\r\n"
            "  rewind            : Rewind the buffer pointer to the start\r\n"
            "  print             : Print ALL buffer bytes (as hex)\r\n");
    } else if (ee_bench_parse(p_command, g_verify_mode) == EE_ARG_CLAIMED) {
    } else if (ee_buffer_parse(p_command) == EE_ARG_CLAIMED) {
    } else {
        return EE_ARG_UNCLAIMED;
    }
    return EE_ARG_CLAIMED;
}

void
ee_profile_initialize(void)
{
    th_buffer_initialize();
    th_profile_initialize();
    g_mute_timestamps = false;
    if (th_buffer_size() < EE_MINBUF) {
        /* The host will catch this, rather than returning a value. */
        th_printf("e-[Buffer must be at least %u bytes]\r\n", EE_MINBUF);
    }
}

#endif /* EE_CFG_SELFHOSTED */
