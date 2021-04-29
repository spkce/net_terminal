#ifndef _ENCRYPT_DES_H
#define _ENCRYPT_DES_H

/************************************************************************
  Function:    	// des_encrypt
  Description:	// 将字符串做des加密
  Input:        // input:待加密的源字符串，output：加密后密文的输出地址，
				   srckey：加密密钥
  Output:      	// output：密文将输出在output内
  Return:		// NULL
************************************************************************/
void des_encrypt(char *input, char *output, char *srckey);


/*******************************************************************
  Function:    	// des_decrypt
  Description:	// 将des加密后的密文解密
  Input:        // srcStrLen:源字符串长度，encStr：密文，
				   srcStr：解密后源字符串输出地址；srckey：加密密钥
  Output:      	// srcStr：输出解密后的源字符串
  Return:		// NULL
*******************************************************************/
void des_decrypt(int srcStrLen, char *encStr, char *srcStr, char *srckey);

unsigned char getQuickCRC8(unsigned char *pBuffer, unsigned int ucLen);


#endif


