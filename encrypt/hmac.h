/*******************************************************************************
       Copyright: 2007-2008 Hangzhou Hikvision Digital Technology Co.,Ltd
        Filename:  hmac.h
     Description:  head file of HMAC algorithm 
         Version:  1.0
         Created:  01/08/2008 01 CST
          Author:  xmq <xiemq@hikvision.com>
******************************************************************************/

#ifndef _HMAC_H
#define _HMAC_H

#ifdef  __cplusplus
extern "C" {
#endif
#define KEY_IOPAD_SIZE      64
#define MD5_DIGEST_SIZE     16
#define SHA1_DIGEST_SIZE    20

void encryptHMAC(unsigned char *in, int in_len,     /* input string */
                unsigned char *key, int key_len,    /* input key */
                unsigned char digest[16]);          /* result */

void hmac_sha1(const char *msg, int msg_len, char *digest, const char *key, int key_len);


#ifdef  __cplusplus
}
#endif
#endif	/* _HMAC_H */


