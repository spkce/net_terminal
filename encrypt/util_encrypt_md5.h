/**@file    util_encrypt_md5.h
 * @note    Hangzhou Hikvision Automotive Technology Co., Ltd. All Right Reserved.
 * @brief   md5加解密模块
 *
 * @author  whq
 * @date    2018-05-14
 * @version V1.0
 *
 * @note History:
 * @note whq 2018-05-14 移植对接DVR的SDK的MD5模块
 */

#ifndef _UTIL_ENCRYPT_MD5_H_
#define _UTIL_ENCRYPT_MD5_H_

/**
 * Function:    MD5_string \n
 * Description: encrypt data with md5 \n
 *
 * \param[in]  *in  -input string
 * \param[in]  in_len   -bytes of input string
 * \param[out] *out -output string
 * \return  N/A
 */
void MD5_string(unsigned char *in, int in_len, unsigned char *out);

/**
 * Function:    string_to_print \n
 * Description: print the string after encrypt by md5 \n
 *
 * \param[in]  *src -input string
 * \param[in]  len  -bytes of input string
 * \param[out] *out -output string
 * \return  N/A
 */
void string_to_print(unsigned char *src, int len, char *out);

/**
 * Function:	hamc_encrypt \n
 * Description: encrypt the data with HMAC\n
 *
 * \param[in]  *in	-input string
 * \param[in]  in_len	-bytes of input string
 * \param[in] *key -the key string of encrypt
 * \param[in] key_len -bytes of key string
 * \param[out] key_len -the target output string after encrypt
 * \return	N/A
 */
void hamc_encrypt(unsigned char *in, int in_len, unsigned char *key, int key_len, unsigned char *digest);

#endif /*_UTIL_ENCRYPT_MD5_H_*/
