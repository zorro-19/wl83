
#ifndef OPENSSL_AES128_CBC_H
#define OPENSSL_AES128_CBC_H

# include <stddef.h>


# ifdef  __cplusplus
extern "C" {
# endif


# define AES_ENCRYPT     1
# define AES_DECRYPT     0

/*
 * Because array size can't be a const in C, the following two are macros.
 * Both sizes are in bytes.
 */
# define AES_MAXNR 14
# define AES_BLOCK_SIZE 16

/* This should be a hidden type, but EVP requires that the size be known */
struct aes_key_st {
    unsigned int rd_key[4 * (AES_MAXNR + 1)];
    int rounds;
};
typedef struct aes_key_st AES_KEY;

typedef unsigned int u32;
typedef unsigned char u8;

#define GETU32(pt) (((u32)(pt)[0] << 24) ^ ((u32)(pt)[1] << 16) ^ ((u32)(pt)[2] <<  8) ^ ((u32)(pt)[3]))
#define PUTU32(ct, st) { (ct)[0] = (u8)((st) >> 24); (ct)[1] = (u8)((st) >> 16); (ct)[2] = (u8)((st) >>  8); (ct)[3] = (u8)(st); }



int AES_set_encrypt_key(const unsigned char *userKey, const int bits,
                        AES_KEY *key);

int AES_set_decrypt_key(const unsigned char *userKey, const int bits,
                        AES_KEY *key);

void AES_cbc_encrypt(const unsigned char *in, unsigned char *out,
                     size_t length, const AES_KEY *key,
                     unsigned char *ivec, const int enc);

typedef void (*block128_f)(const unsigned char in[16],
                           unsigned char out[16], const void *key);


# ifdef  __cplusplus
}
# endif

#endif
