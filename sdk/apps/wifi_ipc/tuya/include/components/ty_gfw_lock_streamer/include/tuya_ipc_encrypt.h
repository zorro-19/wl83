#ifndef TUYA_IPC_ENCRYPT_H
#define TUYA_IPC_ENCRYPT_H

#include <string.h>

#include "tuya_cloud_error_code.h"
#include "tuya_cloud_types.h"
#include "aes_inf.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef OPERATE_RET(*AES_HW_CB)(IN BYTE_T *pdata_in,  IN UINT_T data_len,
                                OUT BYTE_T *pdata_out,  OUT UINT_T *pdata_out_len,
                                IN BYTE_T *pkey, IN BYTE_T *piv);

/***********************************************************
*  Function: OpensslAES_CBC128_encrypt
*  Input:
  IN CONST BYTE *pdata_in,    \\需要加密数据的BUFFER地址
  IN CONST UINT data_len,     \\需要加密数据总长度
  IN UINT out_buffer_len,     \\加密BUFFER的长度
  IN CONST BYTE *pkey         \\加密的密钥
  IN BYTE *piv                \\加密向量
  Output:
  OUT BYTE *pdata_out,        \\加密BUFFER地址
  OUT UINT *pdata_out_len,    \\加密后数据的长度
*  Return: OPERATE_RET
***********************************************************/
OPERATE_RET OpensslAES_CBC128_encrypt(IN CONST BYTE_T *pdata_in,  IN CONST UINT_T data_len,
                                      OUT BYTE_T *pdata_out,  OUT UINT_T *pdata_out_len,
                                      IN CONST BYTE_T *pkey, IN BYTE_T *piv);

/***********************************************************
*  Function: OpensslAES_CBC128_decrypt
*  Input:
  IN CONST BYTE *pdata_in,    \\需要解密数据的BUFFER地址
  IN CONST UINT data_len,     \\需要解密数据总长度
  IN UINT out_buffer_len,     \\解密BUFFER的长度
  IN CONST BYTE *pkey         \\解密的密钥
  IN BYTE *piv                \\解密向量
  Output:
  OUT BYTE *pdata_out,        \\解密BUFFER地址
  OUT UINT *pdata_out_len,    \\解密后数据的长度
*  Return: OPERATE_RET
***********************************************************/
OPERATE_RET OpensslAES_CBC128_decrypt(IN CONST BYTE_T *pdata_in,  IN CONST UINT_T data_len,
                                      OUT BYTE_T *pdata_out,  OUT UINT_T *pdata_out_len,
                                      IN CONST BYTE_T *pkey, IN BYTE_T *piv);


typedef struct {
    BOOL_T        inited;
    BOOL_T        encryptKeyUpdated;
    CHAR_T        encryptKey[AES128_ENCRYPT_KEY_LEN + 4];

    OPERATE_RET(*UpdateEncryptInfo)(VOID);
    OPERATE_RET(*Encrypt)(IN BYTE_T *data, IN UINT_T size, INOUT BYTE_T *encryptedDate, OUT UINT_T *encryptedSize, OUT BYTE_T *iv);
    OPERATE_RET(*Decrypt)(IN BYTE_T *data, IN UINT_T size, INOUT CHAR_T *decryptedDate, OUT UINT_T *decryptedSize, IN BYTE_T *iv);
    OPERATE_RET(*EncryptWithKeyIv)(IN CONST BYTE_T *pdata_in,  IN CONST UINT_T data_len,
                                   OUT BYTE_T *pdata_out,  OUT UINT_T *pdata_out_len,
                                   IN CONST BYTE_T *pkey, IN BYTE_T *piv);
    OPERATE_RET(*CheckAndUpdateEncKey)(IN CONST BYTE_T *cloudKeyMd5);
} ENCRYPTOR_S;

ENCRYPTOR_S *GetEncryptorInstance(VOID);


int tuya_ipc_encrypt_init();

OPERATE_RET tuya_ipc_set_aes_hw_cb(AES_HW_CB encrypt_hw_cb, AES_HW_CB decrypt_hw_cb);


#ifdef __cplusplus
}
#endif

#endif //

