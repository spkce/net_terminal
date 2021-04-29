/*******************************************************************************
    Copyright: 2007-2008 Hangzhou Hikvision Digital Technology Co.,Ltd.
     Filename:  cryptomisc.c
  Description:  magic and des encrypt algorithm functions 
      Version:  1.0
      Created:  01/03/2008 00 CST
       Author:
 ******************************************************************************/
#include <stdio.h>
#include <string.h>

#include "d3des.h"
#include "cryptomisc.h"
                                                
/* global variables */
unsigned char PrivateKey[16]={0x6a,0x68,0xa3,0x61,0xbf,0x6e,0xb5,0x67,0xcd,0x7a,0xfe,0x68,0xca,0x6f,0xde,0x75};


/*******************************************************************************
 *         Name: encryptMagic 
 *  Description: ʹ��ħ���ֶ������ַ������м��� 
 * 
 *       Mode   Type         Name         Description
 * -----------------------------------------------------------------------------
 *        in:   char *      in          �����ܵ�ԭʼ�ַ��� 
 *              int         in_len      ����ԭʼ�ַ������� 
 *    in-out:   ��
 *       out:   char *      out         ���ܺ���ַ���
 *    return:   int                     �ɹ�����0��ʧ�ܷ���-1
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 01/03/2008 00 CST
 *  Revision: none
 ******************************************************************************/
int encryptMagic(char *in, char *out, int in_len)
{
    int            ix;
    unsigned long  magic;
    unsigned long  passwdInt = 0;
	
    if(NULL == out)
    {
        return -1;
    }

    magic     = 0x686b7773;
    out[0] = 0;

    if(in_len == 0)
    {
        return -1;
    }
	
    for (ix = 0; ix < in_len; ix++)
    {
        passwdInt += (in[ix]) * (ix+1) ^ (ix+1);
    }
	
    sprintf (out, "%lu", (long) (passwdInt * magic));
	
    /* make encrypted passwd printable */
    for (ix = 0; ix < (int)(strlen (out)); ix++)
    {
        if (out[ix] < '3')
        {
            out[ix] = out[ix] + 'B';
        }
        else if (out[ix] < '5')
        {
            out[ix] = out[ix] + '/';
        }
        else if (out[ix] < '7')
        {
            out[ix] = out[ix] + '>';
        }
        else if (out[ix] < '9')
        {
            out[ix] = out[ix] + '!';
        }
    }
	
    return 0;
}


/*******************************************************************************
 *         Name: encryptDes 
 *  Description: ʹ��DES�㷨���ַ������м���
 * 
 *       Mode   Type         Name           Description
 * -----------------------------------------------------------------------------
 *        in:   char *      pInput          ����ԭʼ�ַ���
 *              int         iInputMaxLen    �����ַ�������󳤶� 
 *              int         iInputLen       �����ַ�����ʵ�ʳ��� 
 *              int         iOutputMaxLen   ����������󳤶�
 *    in-out:   ��
 *       out:   char *      pOutput         ���ܺ���ַ���
 *              int *       iOutputLen      ʵ���������ĳ��� 
 *    return:   int                         �ɹ�����0��ʧ�ܷ���-1 
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 01/03/2008 00 CST
 *  Revision: none
 ******************************************************************************/
int encryptDes(char *pInput, int iInputMaxLen, int iInputLen, char *pOutput, int iOutputMaxLen, int *iOutputLen)
{
	int iBlock;
	int iFill;
	int i;
	int iLeft;
	
	*iOutputLen = 0;
	
	iLeft = iInputLen % 16;
	
	if (iLeft == 0)
	{
		iBlock = iInputLen/16;
	}
	else
	{
		iBlock = (iInputLen-iLeft)/16+1;
	}

	if (iBlock == 0)
	{
		iBlock += 1;
	}
	
	iFill = iBlock * 16;
	
	if (iInputMaxLen < iFill)
	{
		return -1;
	}
	
	if (iOutputMaxLen < iFill)
	{
		return -1;
	}

	if (iFill > iInputLen)
	{
		memset(pInput+iInputLen, 0, (unsigned)(iFill - iInputLen));
	}
	
	des2key((unsigned char*)PrivateKey,EN0);
	
	for (i=0; i<iBlock; i++)
	{
		D2des((unsigned char*)pInput+i*16, (unsigned char*)pOutput+i*16);
	}
	
	*iOutputLen = iFill;
	
	return 0;
}


/*******************************************************************************
 *         Name: decryptDes 
 *  Description: ��ʹ��DES�㷨���ܺ���ַ������н��� 
 * 
 *       Mode   Type         Name           Description
 * -----------------------------------------------------------------------------
 *        in:   char *      pInput          �����ַ��� 
 *              int         iInputLen       �����ַ�������
 *              int         iOutputMaxLen   ����ַ�����󳤶� 
 *    in-out:   �� 
 *       out:   char *      pOutput         ���ܺ�õ��Ľ��
 *              int *       iOutputLen      ���ܺ���ַ�������
 *    return:   int                         �ɹ�����0��ʧ�ܷ���-1 
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 01/03/2008 00 CST
 *  Revision: none
 ******************************************************************************/
int decryptDes(char *pInput, int iInputLen, char *pOutput, int iOutputMaxLen, int *iOutputLen)
{
	int iBlock;
	int i;
	
	if (iInputLen%16 != 0)
	{
		return -1;
	}
	
	if (iOutputMaxLen < iInputLen)
	{
		return -1;
	}
	
	iBlock = iInputLen/16;
	
	des2key((unsigned char*)PrivateKey,DE1);
	
	for (i=0; i<iBlock; i++)
	{
		D2des((unsigned char*)pInput+i*16,(unsigned char*)pOutput+i*16);
	}
	
	*iOutputLen = iInputLen;
	
	return 0;
}

#if 0
/*******************************************************************************
 *         Name: RSA_GeneratePEMKeys 
 *  Description:  
 * 
 *       Mode   Type         Name         Description
 * -----------------------------------------------------------------------------
 *        in:  
 *    in-out:  
 *       out:  
 *    return:  
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 01/03/2008 00 CST
 *  Revision: none
 ******************************************************************************/
int RSA_GeneratePEMKeys(R_RSA_PUBLIC_KEY *publicKey, R_RSA_PRIVATE_KEY *privateKey, R_RSA_PROTO_KEY *protoKey)
{
	int status;
	static unsigned char seedByte = 0;
	unsigned int bytesNeeded;
	static R_RANDOM_STRUCT randomStruct;
	
	R_RandomInit(&randomStruct);
	
	/* Initialize with all zero seed bytes, which will not yield an actual
			 random number output. */
	R_RandomCreate(&randomStruct);
	
	while (1)
    {
		R_GetRandomBytesNeeded(&bytesNeeded, &randomStruct);
		if(bytesNeeded == 0)
        {
			break;
        }
		
		R_RandomUpdate(&randomStruct, &seedByte, 1);
	}

	status = R_GeneratePEMKeys(publicKey, privateKey, protoKey, &randomStruct);
	if(status) 
	{
		return -1;
	}
	return 0;
}
#endif


