#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rsa_app.h"

//#include "openssl/aes.h"
#include "openssl/bio.h"
#include "openssl/err.h"
#include "openssl/rsa.h"
#include "openssl/evp.h"
#include "openssl/x509.h"
#include "openssl/pem.h"
#include "openssl/bn.h"
#include "openssl/rand.h"
#include "openssl/crypto.h"


/** @fn    Function   : app_rsa_encode
 *  @brief Description: RSA加密程序
 *  @param [in]chPublicKey: base64编码的公钥字符串
 *  @param [in]str: 需要加密的字符串
 *  @param [in]pub_en: 经过RSA加密的字符串，base64格式
 *  @return <0:error  0:success
 */
int app_rsa_encode(const char *chPublicKey, char *str, unsigned char *pub_en) //chPublicKey为base64编码的公钥字符串
{
    BIO *bio = NULL;
    RSA *pub_key = NULL;
    //int rsa_len;
    int rsaENLen = 0;
    char errBuf[512] = {0};
    unsigned char p_en[300] = {0};

    if ((bio = BIO_new_mem_buf(chPublicKey, -1)) == NULL) //从字符串读取RSA公钥
    {
        printf("BIO_new_mem_buf failed!\n");
        return -1;
    }

    pub_key = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL); //从bio结构中得到rsa结构    Get RSA struct from bio
    if (!pub_key)
    {
        //ERR_load_crypto_strings();
        ERR_error_string_n(ERR_get_error(), errBuf, sizeof(errBuf));
        printf("load public key failed, reason: ");
        printf("%s", errBuf);
        printf("\r\n");
        BIO_free_all(bio);
        return -1;
    }
    else
    {
        //rsa_len = RSA_size(pub_key); //获取RSA的长度
        ERR_clear_error();
        //printf("++++++RSA length: %d \r\n", rsa_len);
        rsaENLen = RSA_public_encrypt(strlen(str), (unsigned char *)str, (unsigned char *)p_en, pub_key, RSA_PKCS1_PADDING);
        if (rsaENLen <= 0)
        {
            //ERR_load_crypto_strings();
            ERR_error_string_n(ERR_get_error(), errBuf, sizeof(errBuf));
            printf("RSA_public_encrypt failed, reason:");
            printf("%s", errBuf);
            printf("\r\n");
            RSA_free(pub_key);
            BIO_free_all(bio);
            return -1;
        }
        EVP_EncodeBlock((unsigned char *)pub_en, (unsigned char *)p_en, rsaENLen);   //base编码
        RSA_free(pub_key);
        BIO_free_all(bio);
        return 0;
    }
}
