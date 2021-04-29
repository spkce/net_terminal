#include<string.h>
#include "des.h"

int IP[]={
			58, 50, 42, 34, 26, 18, 10, 2,  60, 52, 44, 36, 28, 20, 12, 4,    /*initial change*/
           62, 54, 46, 38, 30, 22, 14, 6,  64, 56, 48, 40, 32, 24, 16, 8,
           57, 49, 41, 33, 25, 17, 9,  1,  59, 51, 43, 35, 27, 19, 11, 3,
           61, 53, 45, 37, 29, 21, 13, 5,  63, 55, 47, 39, 31, 23, 15, 7
};
int IP_1[]={
			40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,    /*opp initial change*/
           38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
           36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
           34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
 };
int S_BOX[8][4][16]={{                                                                              /*S-diagram array*/
                 {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                 {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
                 {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                 {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
                 },
                {
                 {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
                 {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
                 {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
                 {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
                },
                {
                 {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
                 {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
                 {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
                 {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
                },
                {
                 {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
                 {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
                 {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
                 {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
                },
                {
                 {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
                 {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
                 {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
                 {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
                },
                {
                 {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
                 {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
                 {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
                 {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
                },
                {
                 {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
                 {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
                 {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
                 {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
                },
                {
                 {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
                 {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
                 {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
                 {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
                }
};
int E[48]={ 
			  32, 1, 2, 3, 4, 5,                                                               /*Expand array*/
               4, 5, 6, 7, 8, 9,
               8, 9,10,11,12,13,
              12,13,14,15,16,17,
              16,17,18,19,20,21,
              20,21,22,23,24,25,
              24,25,26,27,28,29,
              28,29,30,31,32, 1
 };
int P[32]={
		   16, 7,20,21,                                                                /*P-change*/
           29,12,28,17,
            1,15,23,26,
            5,18,31,10,
            2, 8,24,14,
           32,27, 3, 9,
           19,13,30, 6,
           22,11, 4,25
 };
int PC1[56]={
			57,49,41,33,25,17,9,                                                /*PC-1 in keyBuild*/
             1,58,50,42,34,26,18,
             10,2,59,51,43,35,27,
             19,11,3,60,52,44,36,
             63,55,47,39,31,33,15,
             7,62,54,46,38,30,22,
             14,6,61,53,45,37,29,
             21,13,5,28,20,12,4
 };
int PC2[48]={
			14,17,11,24, 1, 5,                                                     /*PC-2 in keyBuild*/
             3,28,15, 6,21,10,
            23,19,12, 4,26, 8,
            16, 7,27,20,13, 2,
            41,52,31,37,47,55,
            30,40,51,45,33,48,
            44,49,39,56,34,53,
            46,42,50,36,29,32
 };
int MOVE_LEFT[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

void encrypt(int L[17][32],int R[17][32],int key[16][48],int mi_wen[64],int mode);/* 加密函数 */
void F(int R[32],int key[48],int temp[32]); /* 对数据进行F转换 */
void S(int temp_1[48],int temp_2[32]);		/* 将数据输入S盒进行处理 */
void replace(int aaa[],int bbb[],int num,int ccc[]);

void er_jin_zhi_8(int shi[8],int er[64]);	/* 将八位十进制数字转化为六十四位二进制数字 */
void shi_jin_zhi_8(int er[64],int shi[8]);	/* 将六十四位二进制数字转化为八位十进制数字 */

void er_jin_zhi_16(int shi[8],int er[64]);
void shi_jin_zhi_16(int er[64],int shi[8]);

void key_build(int key_2[64],int key[16][48]);

#define ENCRYPT_MODE	1
#define DECRYPT_MODE	2

/************************************************************************
  Function:    	// des_encrypt
  Description:	// 将字符串做des加密
  Input:        // input:待加密的源字符串，output：加密后密文的输出地址，
				   srckey：加密密钥
  Output:      	// output：密文将输出在output内
  Return:		// NULL
************************************************************************/
void des_encrypt(char *input, char *output, char *srckey)
{
	int i, j;
	int size_of_data;
	int count;									  /* 加密的轮数 */
	int key_10[8], key_2[64], key[16][48];		  /* 分别存储原始密码（八位十进制数字），二进制密码，十六个子密钥 */
	int data_10_8[8], data_2[64], data_10_16[16]; /* 分别存储原始数据，二进制数据，密文 */
	int L[17][32], R[17][32]; 
	int mi_wen[64], tmpbuf[64];

	for(i=0; i<8; i++)
	{
		key_10[i] = srckey[i];
	}
	size_of_data = strlen(input);

	er_jin_zhi_8(key_10, key_2);
	key_build(key_2, key);
	/* 16组子密钥已经产生 */

	count = ( (size_of_data-1) / 8) + 1;	/* 确定加密的轮数 */
	
	for(i=count; i>0; i--)					/* 开始正式加密! */
	{
		for( j=0 ; j<8 ; j++ )				/* 读取数据块，一次八个字符 */
		{
			data_10_8[j] = input[8*(count-i)+j];
		}
		
		er_jin_zhi_8(data_10_8, data_2);	/* 将字符的ASCII值转化为二进制形式 */
		
		replace(L[0],data_2, 32, IP);		/* 对明文进行初始置换--IP置换 */
		replace(R[0],data_2, 32, IP+32);
		
		encrypt(L, R, key, mi_wen, ENCRYPT_MODE);	/* 进行加密 */
		
		replace(tmpbuf, mi_wen, 64, IP_1);			/* 对密文进行IP_1置换 */
		
		shi_jin_zhi_16(tmpbuf, data_10_16);			/* 将密文转化为十进制 */
		
		for( j=0 ; j<16 ; j++ )						/* 将密文存入output */
		{
			output[(count-i)*16+j] = (char)data_10_16[j];
		}
	}

/*	printf("encrypted str(len:%d):%s\n",strlen(output),output);*/
	return;
}

/*******************************************************************
  Function:    	// des_decrypt
  Description:	// 将des加密后的密文解密
  Input:        // srcStrLen:源字符串长度，encStr：密文，
				   srcStr：解密后源字符串输出地址；srckey：加密密钥
  Output:      	// srcStr：输出解密后的源字符串
  Return:		// NULL
*******************************************************************/
void des_decrypt(int srcStrLen, char *encStr, char *srcStr, char *srckey)
{
	int i, j;
	int size_of_data;
	int count;									  /* 加密的轮数 */
	int key_10[8], key_2[64], key[16][48];		  /* 分别存储原始密码（八位十进制数字），二进制密码，十六个子密钥 */
	int data_10_8[8], data_2[64], data_10_16[16]; /* 分别存储原始数据，二进制数据，密文 */
	int L[17][32], R[17][32]; 
	int mi_wen[64], tmpbuf[64];

	for(i=0; i<8; i++)
	{
		key_10[i] = srckey[i];
	}
	size_of_data = srcStrLen;

	er_jin_zhi_8(key_10, key_2);
	key_build(key_2, key);
	/* 16组子密钥已经产生 */

	count = ( (size_of_data-1) / 8 ) + 1;		/* 确定加密或解密的轮数 */
	
	for(i=count; i>0; i--)						/* 开始正式加密解密 ! */
	{
		for( j=0 ; j<16 ; j++ )					/* 读取数据块，一次十六个字符 */
		{
			data_10_16[j] = encStr[(count-i)*16+j]; 
		}
		
		er_jin_zhi_16(data_10_16, data_2);		/* 将字符的ASCII值转化为二进制形式 */
		
		replace(L[0],data_2, 32, IP);			/* 对明/密文进行初始置换--IP置换 */
		replace(R[0],data_2, 32, IP+32);
		
		encrypt(L,R,key, mi_wen, DECRYPT_MODE);	/* 进行解密 */
		
		replace(tmpbuf, mi_wen, 64, IP_1);		/* 对明文进行IP_1置换 */
		
		shi_jin_zhi_8(tmpbuf, data_10_8);		/* 将明文转化为十进制 */
		
		for( j=0 ; j<8 ; j++ )					/* 将明文存入srcStr */
		{
			srcStr[(count-i)*8+j] = (char)data_10_8[j];
		}
	}

/*	printf("source str:%s\n",srcStr);*/
	return;
}

/* 加密函数 */
void encrypt(int L[17][32],int R[17][32],int key[16][48],int mi_wen[64],int mode)
{
	int i,j;
	int temp[32];
	
	for(i=1;i<=16;i++)
	{
		if(mode == ENCRYPT_MODE)
			F(R[i-1],key[i-1],temp);
		else
			F(R[i-1],key[16-i],temp);

		for(j=0;j<32;j++)
		{
			L[i][j]=R[i-1][j];
			R[i][j]=(L[i-1][j] + temp[j])%2;
		}
	}

	for(i=0;i<32;i++)
	{
		mi_wen[i]=R[16][i];
	}
	for(i=32;i<64;i++)
	{
		mi_wen[i]=L[16][i-32];
	}
}

/* 对数据进行F转换 */
void F(int R[32],int key[48],int temp[32])
{
	int i;
	int temp_1[48],temp_2[32];
	replace(temp_1,R,48,E);
	for(i=0;i<48;i++)
	{
		temp_1[i]=(temp_1[i]+key[i])%2;
	}

	S(temp_1,temp_2);
	replace(temp,temp_2,32,P);
}

/* 将数据输入S盒进行处理 */
void S(int temp_1[48],int temp_2[32])
{
	int a,i,j,k;
	for(i=0;i<8;i++)
	{
		j=temp_1[i*6]*2+temp_1[i*6+5];
		k=temp_1[i*6+1]*8 + temp_1[i*6+2]*4 + temp_1[i*6+3]*2 + temp_1[i*6+4];
		a=S_BOX[i][j][k];
	
		for(j=3;j>=0;j--)	/* 此时的j已经完成了他的使命，所以可以挪为他用 */
		{
			temp_2[i*4+j]=a%2;
			a/=2;
		}
	}
}

/* 矩阵转换函数.根据ccc矩阵的位序信息，改变bbb矩阵内数字的位置，保存在aaa矩阵中 */
void replace(int aaa[],int bbb[],int num,int ccc[])
{
	int i;
	for(i=0;i<num;i++)
	{
		aaa[i]=bbb[ccc[i]-1];
	}
}

/* 
   将十进制数据转换成二进制（十六个十进制数为一组）
   这个函数只有在解密时才用得到，那是将密文切成16个字符的字符块，然后转换成二进制，
   由于本DES使用的表是64-95的，所以要先还原成正常的数
*/
void er_jin_zhi_16(int shi[16],int er[64])
{
	int i,j;
	for(i=0;i<16;i++)
	{	
		if( i%2==0 )
			shi[i]-=64;
		else
			shi[i]-=(64+16);
 		for( j=3 ; j>=0 ; j-- )
		{      	
			er[i*4+j]=shi[i]%2;
			shi[i]/=2;
		}
	}
}

/* 将十进制数据转换成二进制（八个十进制数为一组）*/
void er_jin_zhi_8(int shi[8],int er[64])
{
	int i,j;
	for(i=0; i<8 ;i++)
	{	
 		for( j=7 ; j>=0 ; j-- )
		{      	
			er[i*8+j]=shi[i]%2;
			shi[i]/=2;
		}
	}
}

/* 将六十四位二进制数据转换成十六位十进制 */
void shi_jin_zhi_16(int er[64],int shi[16]) 
{
	int i;
	for( i=0 ; i<16 ; i++ )
	{
		if( i%2==0 )
		{
			shi[i]= er[i*4]*8 + er[i*4+1]*4 + er[i*4+2]*2 + er[i*4+3]*1 +64;
		}
		else
		{
			shi[i]= er[i*4]*8 + er[i*4+1]*4 + er[i*4+2]*2 + er[i*4+3]*1 + 64 + 16;/*这里规定第偶数次将 四位二进制数串 转化为 十进制数串 时要加16，这是为了区分不同的表*/
		}
	}
}

/* 将六十四位二进制数据转换成八位十进制 */
void shi_jin_zhi_8(int er[64],int shi[8]) 
{
	int i;
	for( i=0 ; i<8 ; i++ )
		shi[i]=er[i*8]*128 + er[i*8+1]*64 + er[i*8+2]*32 + er[i*8+3]*16 + er[i*8+4]*8 + er[i*8+5]*4 + er[i*8+6]*2 + er[i*8+7]*1;
}

/* 根据所给的密钥产生子密钥 */
void key_build(int key_2[64],int key[16][48])
{
	int i,j;
	int c[17][28],d[17][28],temp[56];
	
	replace(c[0],key_2,28,PC1);		/* 此处之所以没有用temp做中转站，是为了提高速度。*/
	replace(d[0],key_2,28,PC1+28);	/* 此处稍复杂*/

	for(i=1;i<=16;i++)				/* 数据左移 */
	{
		if(MOVE_LEFT[i-1]==1)
		{
			for(j=0;j<27;j++)
			{
				c[i][j]=c[i-1][j+1];
				d[i][j]=d[i-1][j+1];
			}			
			c[i][27]=c[i-1][0];
			d[i][27]=d[i-1][0];
		}
		else
		{
			for(j=0;j<26;j++)
			{
				c[i][j]=c[i-1][j+2];
				d[i][j]=d[i-1][j+2];
			}			
			c[i][26]=c[i-1][0];
			d[i][26]=d[i-1][0];
			c[i][27]=c[i-1][1];
			d[i][27]=d[i-1][1];
		}

		for(j=0;j<28;j++)
			temp[j]=c[i][j];
		for(j=28;j<56;j++)
			temp[j]=d[i][j-28];
	
		replace(key[i-1],temp,48,PC2);
	}
}

unsigned char getQuickCRC8(unsigned char *pBuffer, unsigned int ucLen)
{
	unsigned int k;
	unsigned char crc;
	unsigned char temp;
	unsigned char CCITT_CRC8_DATA[256] = 
	{
		0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83,
		0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
		0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e,
		0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
		0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0,
		0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
		0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d,
		0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
		0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5,
		0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
		0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58,
		0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
		0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6,
		0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
		0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b,
		0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
		0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f,
		0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
		0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92,
		0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
		0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c,
		0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
		0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1,
		0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
		0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49,
		0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
		0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4,
		0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
		0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a,
		0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
		0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7,
		0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35
	};

	crc = 0;

	for(k = 0; k < ucLen; k++)
	{
		temp = pBuffer[k] ^ crc;
		crc = CCITT_CRC8_DATA[temp];
	}

	return crc;
}

