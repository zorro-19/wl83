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

#include "ee_aes.h"

/* This is an aesthetic decoder for log messages; must match ee_aes_mode_t */
static const char *aes_cipher_mode_text[] = { "ecb", "ctr", "ccm", "gcm" };

uint32_t
ee_aes(ee_aes_mode_t  mode,
       ee_aes_func_t  func,
       const uint8_t *p_key,
       uint32_t       keylen,
       const uint8_t *p_iv,
       const uint32_t count,
       void          *p_message_list, /* see ee_aes.h for details */
       uint32_t       iter)
{
    void       *p_context;
    uint8_t    *p_in;
    uint8_t    *p_out;
    uint8_t    *p_tag;
    uint32_t   *p32;
    uint8_t    *p8;
    uint32_t    len;
    uint32_t    t0   = 0;
    uint32_t    t1   = 0;
    uint16_t    bits = keylen * 8;
    const char *m    = aes_cipher_mode_text[mode];
    ee_status_t ret;
    uint32_t    x;

    if (th_aes_create(&p_context, mode) != EE_STATUS_OK) {
        th_printf("e-aes%d_%s-[Failed to create context]\r\n", bits, m);
        return 0;
    }
    th_printf("m-aes%d_%s-iter[%d]\r\n", bits, m, iter);
    th_printf("m-aes%d_%s-count[%d]\r\n", bits, m, count);
    if (func == EE_AES_ENC) {
        th_printf("m-aes%d_%s-encrypt-start\r\n", bits, m);
        t0 = th_timestamp();
        th_pre();
        while (iter-- > 0) {
            ret = EE_STATUS_OK;
            if (th_aes_init(p_context, p_key, keylen, p_iv, func, mode)
                != EE_STATUS_OK) {
                th_post();
                th_printf("e-aes%d_%s-[Failed to initialize]\r\n", bits, m);
                goto exit;
            }
            /* Work through the list of messages for this context */
            p32 = (uint32_t *)p_message_list;
            /* Perform multiple en/decrypts in the same context */
            for (x = 0; x < count; ++x) {
                /* Set up the data pointers */
                len  = *p32++;
                p8   = (uint8_t *)p32;
                p_in = p8;
                p8 += len;
                p_out = p8;
                p8 += len;
                p_tag = p8;
                p8 += EE_AES_TAGLEN;
                p32 = (uint32_t *)p8;

                switch (mode) {
                case EE_AES_ECB:
                    if (len % EE_AES_BLOCKLEN != 0) {
                        th_post();
                        th_printf("e-aes%d_%s-[non mod-16]\r\n", bits, m);
                        goto exit;
                    }
                    ret = th_aes_ecb_encrypt(p_context, p_in, len, p_out);
                    break;
                case EE_AES_CTR:
                    ret = th_aes_ctr_encrypt(p_context, p_in, len, p_out);
                    break;
                case EE_AES_CCM:
                    ret = th_aes_ccm_encrypt(p_context,
                                             p_in,
                                             len,
                                             p_out,
                                             p_tag,
                                             EE_AES_TAGLEN,
                                             p_iv,
                                             EE_AES_AEAD_IVLEN);
                    break;
                case EE_AES_GCM:
                    ret = th_aes_gcm_encrypt(p_context,
                                             p_in,
                                             len,
                                             p_out,
                                             p_tag,
                                             EE_AES_TAGLEN,
                                             p_iv,
                                             EE_AES_AEAD_IVLEN);
                    break;
                default:
                    th_post();
                    th_printf("e-aes%d_%s-[Invalid AES enum: %d]\r\n",
                              bits,
                              m,
                              mode);
                    goto exit;
                }
            }
            th_aes_deinit(p_context);
            if (ret != EE_STATUS_OK) {
                goto err_enc_exit;
            }
        }
        th_post();
        t1 = th_timestamp();
        th_printf("m-aes%d_%s-encrypt-finish\r\n", bits, m);
    } else {
        th_printf("m-aes%d_%s-decrypt-start\r\n", bits, m);
        t0 = th_timestamp();
        th_pre();
        while (iter-- > 0) {
            ret = EE_STATUS_OK;
            if (th_aes_init(p_context, p_key, keylen, p_iv, func, mode)
                != EE_STATUS_OK) {
                th_post();
                th_printf("e-aes%d_%s-[Failed to initialize]\r\n", bits, m);
                goto exit;
            }
            /* Work through the list of messages for this context */
            p32 = (uint32_t *)p_message_list;
            /* Performple en/decrypts in the same context */
            for (x = 0; x < count; ++x) {
                /* Set up the data pointers */
                len  = *p32++;
                p8   = (uint8_t *)p32;
                p_in = p8;
                p8 += len;
                p_out = p8;
                p8 += len;
                p_tag = p8;
                p8 += EE_AES_TAGLEN;
                p32 = (uint32_t *)p8;

                switch (mode) {
                case EE_AES_ECB:
                    if (len % EE_AES_BLOCKLEN != 0) {
                        th_post();
                        th_printf("e-aes%d_%s-[non mod-16]\r\n", bits, m);
                        goto exit;
                    }
                    ret = th_aes_ecb_decrypt(p_context, p_in, len, p_out);
                    break;
                case EE_AES_CTR:
                    ret = th_aes_ctr_decrypt(p_context, p_in, len, p_out);
                    break;
                case EE_AES_CCM:
                    ret = th_aes_ccm_decrypt(p_context,
                                             p_in,
                                             len,
                                             p_out,
                                             p_tag,
                                             EE_AES_TAGLEN,
                                             p_iv,
                                             EE_AES_AEAD_IVLEN);
                    break;
                case EE_AES_GCM:
                    ret = th_aes_gcm_decrypt(p_context,
                                             p_in,
                                             len,
                                             p_out,
                                             p_tag,
                                             EE_AES_TAGLEN,
                                             p_iv,
                                             EE_AES_AEAD_IVLEN);
                    break;
                default:
                    th_post();
                    th_printf("e-aes%d_%s-[Invalid AES enum: %d]\r\n",
                              bits,
                              m,
                              mode);
                    goto exit;
                }
            }
            th_aes_deinit(p_context);
            if (ret != EE_STATUS_OK) {
                goto err_dec_exit;
            }
        }
        th_post();
        t1 = th_timestamp();
        th_printf("m-aes%d_%s-decrypt-finish\r\n", bits, m);
    }
    goto exit;
err_enc_exit:
    th_post();
    th_printf("e-aes%d_%s-[Failed to encrypt]\r\n", bits, m);
    goto exit;
err_dec_exit:
    th_post();
    th_printf("e-aes%d_%s-[Failed to decrypt]\r\n", bits, m);
    goto exit;
exit:
    th_aes_destroy(p_context);
    return t1 - t0;
}
