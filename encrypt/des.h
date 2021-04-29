#ifndef _ENCRYPT_DES_H
#define _ENCRYPT_DES_H

/************************************************************************
  Function:    	// des_encrypt
  Description:	// ���ַ�����des����
  Input:        // input:�����ܵ�Դ�ַ�����output�����ܺ����ĵ������ַ��
				   srckey��������Կ
  Output:      	// output�����Ľ������output��
  Return:		// NULL
************************************************************************/
void des_encrypt(char *input, char *output, char *srckey);


/*******************************************************************
  Function:    	// des_decrypt
  Description:	// ��des���ܺ�����Ľ���
  Input:        // srcStrLen:Դ�ַ������ȣ�encStr�����ģ�
				   srcStr�����ܺ�Դ�ַ��������ַ��srckey��������Կ
  Output:      	// srcStr��������ܺ��Դ�ַ���
  Return:		// NULL
*******************************************************************/
void des_decrypt(int srcStrLen, char *encStr, char *srcStr, char *srckey);

unsigned char getQuickCRC8(unsigned char *pBuffer, unsigned int ucLen);


#endif


