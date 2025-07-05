/*****************************************************************************
 * osal_mbedtls.h
 *
 *
 *
 ****************************************************************************/
/*
 * wiki
 * ====
 */
#ifndef OSAL_MBEDTLS_H_INCLUDE
#define OSAL_MBEDTLS_H_INCLUDE
/*****************************************************************************
 * @addtogroup osal_mbedtls
 * @{
 */
/*****************************************************************************
 * Included Files
 ****************************************************************************/

#if !defined(OSAL_API_H_INCLUDE)
#error "Only 'osal/osal_api.h' can be included directly."
#endif

/*****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define OSAL_MBEDTLS_AES
#define OSAL_MBEDTLS_BASE64
#define OSAL_MBEDTLS_MD5

/*****************************************************************************
 * Public Types
 ****************************************************************************/

/*****************************************************************************
 * Public Data
 ****************************************************************************/

/*****************************************************************************
 * Inline Functions
 ****************************************************************************/

/****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef OSAL_MBEDTLS_AES
int osal_mbedtls_aes_crypt_cbc(bool           isencrypt,
                               const uint8_t *key,
                               uint32_t       keybits,
                               uint8_t        iv[16],
                               size_t         length,
                               const uint8_t *input,
                               uint8_t       *output);

int osal_mbedtls_aes_encrypt_cbc(const uint8_t *key,
                                 uint32_t       keybits,
                                 uint8_t        iv[16],
                                 size_t         length,
                                 const uint8_t *input,
                                 uint8_t       *output);

int osal_mbedtls_aes_decrypt_cbc(const uint8_t *key,
                                 uint32_t       keybits,
                                 uint8_t        iv[16],
                                 size_t         length,
                                 const uint8_t *input,
                                 uint8_t       *output);
#endif /* OSAL_MBEDTLS_AES */

#ifdef OSAL_MBEDTLS_BASE64
int osal_mbedtls_base64_encode(uint8_t       *dst,
                               size_t         dlen,
                               size_t        *olen,
                               const uint8_t *src,
                               size_t         slen);
int osal_mbedtls_base64_decode(uint8_t       *dst,
                               size_t         dlen,
                               size_t        *olen,
                               const uint8_t *src,
                               size_t         slen);
#endif /* OSAL_MBEDTLS_BASE64 */

#ifdef OSAL_MBEDTLS_MD5
int osal_mbedtls_md5(const uint8_t *input, size_t ilen, uint8_t output[16]);
int osal_mbedtls_md5str(const uint8_t *input,
                        size_t         ilen,
                        char           outstr[32 + 1]);
#endif /* OSAL_MBEDTLS_MD5 */

/****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************
 * @} (end addtogroup osal_mbedtls)
 */
/****************************************************************************/
#endif /* OSAL_MBEDTLS_H_INCLUDE */
/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
