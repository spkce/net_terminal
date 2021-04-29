#ifndef _HIK_AES_H_
#define _HIK_AES_H_

//#define Nr 4			// number of rounds in encryption

#ifdef __cplusplus
extern "C" {
#endif


/** @fn	int __stdcall AES_encrypt(unsigned char *pInput, int iInputMaxLen, int iInputLen, unsigned char *pOutput, int iOutputMaxLen, int *iOutputLen, unsigned char* pKey)
 *  @brief
 *  @param (in)	unsigned char * pInput    
 *  @param (in)	int iInputMaxLen    
 *  @param (in)	int iInputLen    
 *  @param (in)	unsigned char * pOutput    
 *  @param (in)	int iOutputMaxLen    
 *  @param (in)	int * iOutputLen    
 *  @param (in)	unsigned char * pKey    
 *  @return	int __stdcall
 */
int aes_encrypt(unsigned char *pInput, int iInputMaxLen, int iInputLen, unsigned char *pOutput, int iOutputMaxLen, int *iOutputLen, unsigned char* pKey);

/** @fn	int __stdcall AES_decrypt(char *pInput, int iInputLen, char *pOutput, int iOutputMaxLen, int *iOutputLen, unsigned char* pKey)
 *  @brief
 *  @param (in)	char * pInput			  
 *  @param (in)	int iInputLen    
 *  @param (in)	char * pOutput    
 *  @param (in)	int iOutputMaxLen    
 *  @param (in)	int * iOutputLen    
 *  @param (in)	unsigned char * pKey    
 *  @return	int __stdcall
 */
int aes_decrypt(char *pInput, int iInputLen, char *pOutput, int iOutputMaxLen, int *iOutputLen, unsigned char* pKey);

#ifdef __cplusplus
}
#endif

#endif

