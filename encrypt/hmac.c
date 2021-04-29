/*******************************************************************************
    Copyright: 2007-2008 Hangzhou Hikvision Digital Technology Co.,Ltd.
     Filename:  hmac.c
  Description:  implement of HMAC algorithm 
      Version:  1.0
      Created:  01/08/2008 01 CST
       Author:  xmq <xiemq@hikvision.com>
 ******************************************************************************/
#include <string.h>

#include "md5.h"
#include "hmac.h"
#include "ipc_sha1.h"

/*******************************************************************************
 *         Name: encryptHMAC 
 *  Description: 使用HMAC加密算法对数据进行加密 
 * 
 *       Mode   Type                Name         Description
 * -----------------------------------------------------------------------------
 *        in:   unsigned char *     in          原始输入数据
 *              int                 in_len      输入数据长度
 *              unsigned char *     key         加密使用的密钥
 *              int                 ken_len     密钥的长度
 *    in-out:   无 
 *       out:   unsigned char *     digest      加密后的结果输出
 *    return:   void
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 01/08/2008 01 CST
 *  Revision: none
 ******************************************************************************/
void
encryptHMAC(unsigned char *in, int in_len, unsigned char *key, int key_len, 
        unsigned char *digest)
{
    MD5_CTX context;
    unsigned char k_ipad[65];    /* inner padding - key XORd with ipad*/
    unsigned char k_opad[65];    /* outer padding - key XORd with opad*/
    unsigned char tk[16] = {0};
    int i;
	
    /* if key is longer than 64 bytes reset it to key=MD5(key) */
    if(key_len > 64)
    {
        MD5_CTX      tctx;

        MD5Init(&tctx);
        MD5Update(&tctx, key, (unsigned)key_len);
        MD5Final(tk, &tctx);

        key = tk;
        key_len = 16;
    }
	
	/*
	* the HMAC_MD5 transform looks like:
	*
	* MD5(K XOR opad, MD5(K XOR ipad, text))
	*
	* where K is an n byte key
	* ipad is the byte 0x36 repeated 64 times
    * opad is the byte 0x5c repeated 64 times
    * and text is the data being protected
	*/
	
    /* start out by storing key in pads */
    memset( k_ipad,0, sizeof(k_ipad));
    memset( k_opad,0, sizeof(k_opad));
    memcpy( k_ipad, key,(unsigned)key_len);
    memcpy( k_opad, key,(unsigned)key_len);
	
    /* XOR key with ipad and opad values */
    for(i=0; i<64; i++)
    {
        k_ipad[i] ^= 0x36;
        k_opad[i] ^= 0x5c;
    }

    /*
    * perform inner MD5
    */
    MD5Init(&context);                     /* init context for 1st pass */
    MD5Update(&context, k_ipad, 64);       /* start with inner pad */
    MD5Update(&context, in, (unsigned)in_len);   /* then text of datagram */
    MD5Final(digest, &context);            /* finish up 1st pass */
	
    /* 
    * perform outer MD5
    */
    MD5Init(&context);                     /* init context for 2nd pass */
    MD5Update(&context, k_opad, 64);       /* start with outer pad */
    MD5Update(&context, digest, 16);       /* then results of 1st hash */
    MD5Final(digest, &context);            /* finish up 2nd pass */
}

char hmac_hb2hex(unsigned char hb)
{    
    hb = hb & 0xF;    
    return (char)(hb < 10 ? '0' + hb : hb - 10 + 'A');
}

void hmac_sha1(const char *msg, int msg_len, char *digest, const char *key, int key_len)
{
	if((NULL == msg) || (NULL == digest) || (NULL == key)) 
	{
		//log_err("parameter is Null,failed!");
		return;
	}

	if(key_len > KEY_IOPAD_SIZE) 
	{
		//log_err("key_len > size(%d) of array",KEY_IOPAD_SIZE);
		return;
	}

	sha1_context context;
	unsigned char k_ipad[KEY_IOPAD_SIZE];    /* inner padding - key XORd with ipad  */
	unsigned char k_opad[KEY_IOPAD_SIZE];    /* outer padding - key XORd with opad */
	unsigned char out[SHA1_DIGEST_SIZE];
	int i;

	/* start out by storing key in pads */
	memset(k_ipad, 0, sizeof(k_ipad));
	memset(k_opad, 0, sizeof(k_opad));
	memcpy(k_ipad, key, key_len);
	memcpy(k_opad, key, key_len);

	/* XOR key with ipad and opad values */
	for (i = 0; i < KEY_IOPAD_SIZE; i++) 
	{
		k_ipad[i] ^= 0x36;
		k_opad[i] ^= 0x5c;
	}

	/* perform inner SHA */
	sha1_init(&context);                                      /* init context for 1st pass */
	sha1_starts(&context);                                    /* setup context for 1st pass */
	sha1_update(&context, k_ipad, KEY_IOPAD_SIZE);            /* start with inner pad */
	sha1_update(&context, (unsigned char *) msg, msg_len);    /* then text of datagram */
	sha1_finish(&context, out);                               /* finish up 1st pass */

	/* perform outer SHA */
	sha1_init(&context);                              /* init context for 2nd pass */
	sha1_starts(&context);                            /* setup context for 2nd pass */
	sha1_update(&context, k_opad, KEY_IOPAD_SIZE);    /* start with outer pad */
	sha1_update(&context, out, SHA1_DIGEST_SIZE);     /* then results of 1st hash */
	sha1_finish(&context, out);                       /* finish up 2nd pass */

	for (i = 0; i < SHA1_DIGEST_SIZE; ++i) 
	{
		digest[i * 2] = hmac_hb2hex(out[i] >> 4);
		digest[i * 2 + 1] = hmac_hb2hex(out[i]);
	}
}



