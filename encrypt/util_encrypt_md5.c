/* MD5C.C - RSA Data Security, Inc., MD5 message-digest algorithm
 */

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
 */
#include <stdio.h>
#include <string.h>
//#include "md5.h"
//#include "util_encrypt.h" 

/* Constants for MD5Transform routine.
 */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

/* F, G, H and I are basic MD5 functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
 */
#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (unsigned int)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (unsigned int)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (unsigned int)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (unsigned int)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }

typedef struct
{
    unsigned int state[4];           /* state (ABCD) */
    unsigned int count[2];           /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64]; /* input buffer */
} MD5_CTX;


static void MD5_transform(unsigned int state[4], unsigned char block[64]);
static void MD5_encode(unsigned char *output, unsigned int*input, unsigned int len);
static void MD5_decode(unsigned int *output, unsigned char *input, unsigned int len);
static void MD5_memcpy(unsigned char *output, unsigned char *input, unsigned int len);
static void MD5_memset(unsigned char *output, int value, unsigned int len);

static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/**
 * Function:    MD5_init \n
 * Description: MD5 initialization. Begins an MD5 operation, writing a new context. \n
 *
 * \param[in]  *context -object to initialization
 * \param[out] N/A
 * \return  N/A
 */
void MD5_init(MD5_CTX *context)
{
    context->count[0] = context->count[1] = 0;

    /* Load magic initialization constants. */
    context->state[0] = 0x67452301;
    context->state[1] = 0xefcdab89;
    context->state[2] = 0x98badcfe;
    context->state[3] = 0x10325476;

    return;
}

/**
 * Function:    MD5_update \n
 * Description: MD5 block update operation. Continues an MD5 message-digest \n
                operation, processing another message block, and updating the \n
                context. \n
 *
 * \param[in]  *input -input string
 * \param[in]  inputLen -length of input string 
 * \param[out] *context -output data after update
 * \return  N/A
 */
void MD5_update(MD5_CTX *context, unsigned char *input, unsigned int inputLen)
{
    unsigned int i = 0;
    unsigned int index = 0;
    unsigned int partLen = 0;

    /* Compute number of bytes mod 64 */
    index = (unsigned int) ((context->count[0] >> 3) & 0x3F);

    /* Update number of bits */
    if((context->count[0] += (inputLen << 3)) < (inputLen << 3))
    {
        context->count[1]++;
    }
    context->count[1] += (inputLen >> 29);

    partLen = 64 - index;

    /* Transform as many times as possible. */
    if (inputLen >= partLen)
    {
        MD5_memcpy((unsigned char *) & context->buffer[index], input, partLen);
        MD5_transform(context->state, context->buffer);

        for (i = partLen; i + 63 < inputLen; i += 64)
        {
            MD5_transform(context->state, &input[i]);
        }

        index = 0;
    }
    else
    {
        i = 0;
    }

    /* Buffer remaining input */
    MD5_memcpy((unsigned char *) & context->buffer[index], (unsigned char *) & input[i], inputLen - i);

    return;
}

/**
 * Function:    MD5_final \n
 * Description: MD5 finalization. Ends an MD5 message-digest operation, \n
                writing the message digest and zeroizing the context.\n
 *
 * \param[in]  *context -input data after update
 * \param[out] digest[16] -output data after encrypt by md5
 * \return  N/A
 */
void MD5_final(unsigned char digest[16], MD5_CTX *context)
{
    unsigned char bits[8] = {0};
    unsigned int index = 0;
    unsigned int padLen = 0;

    /* Save number of bits */
    MD5_encode (bits, context->count, 8);

    /* Pad out to 56 mod 64. */
    index = (unsigned int) ((context->count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    MD5_update (context, PADDING, padLen);

    /* Append length (before padding) */
    MD5_update (context, bits, 8);

    /* Store state in digest */
    MD5_encode (digest, context->state, 16);

    /* Zeroize sensitive information. */
    MD5_memset ((unsigned char *) context, 0, sizeof (*context));

    return;
}


/**
 * Function:    MD5_string \n
 * Description: encrypt data with md5 \n
 *
 * \param[in]  *in  -input string
 * \param[in]  in_len   -bytes of input string
 * \param[out] *out -output string
 * \return  N/A
 */
void MD5_string(unsigned char *in, int in_len, unsigned char *out)
{
    MD5_CTX ctx;

    if(NULL == out)
    {
        return;
    }
    else
    {
        MD5_init(&ctx);
        MD5_update(&ctx, in, in_len);
        MD5_final(out, &ctx);
    }

    return;
}



/**
 * Function:    string_to_print \n
 * Description: print the string after encrypt by md5 \n
 *
 * \param[in]  *src -input string
 * \param[in]  len  -bytes of input string
 * \param[out] *out -output string
 * \return  N/A
 */
void string_to_print(unsigned char *src, int len, char *out)
{
    int     i;
    int     msb = 0, lsb = 0;
    char    temp[2*len + 1];
    const char tab[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                        '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    if((NULL == src) || (NULL == out))
    {
        return;
    }   
    else
    {
        for(i = 0; i < len; i++)
        {
            lsb =(*(src + i)) & 0xf;
            msb =((*(src + i)) & 0xf0) >> 4;
            temp[2*i] = tab[msb];
            temp[2*i+1] = tab[lsb];
        }
        temp[2*i] = '\0';
        memcpy(out, temp, 2*len+1);
    }

    return;
}


/**
 * Function:    MD5_transform \n
 * Description: MD5 basic transformation. Transforms state based on block.\n
 *
 * \param[in]  block[64] 
 * \param[out] state[4]
 * \return  N/A
 */
static void MD5_transform(unsigned int state[4], unsigned char block[64])
{
    unsigned int a = state[0], b = state[1], c = state[2], d = state[3], x[16];

    MD5_decode (x, block, 64);

    /* Round 1 */
    FF (a, b, c, d, x[0], S11, 0xd76aa478);       /* 1 */
    FF (d, a, b, c, x[1], S12, 0xe8c7b756);       /* 2 */
    FF (c, d, a, b, x[2], S13, 0x242070db);       /* 3 */
    FF (b, c, d, a, x[3], S14, 0xc1bdceee);       /* 4 */
    FF (a, b, c, d, x[4], S11, 0xf57c0faf);       /* 5 */
    FF (d, a, b, c, x[5], S12, 0x4787c62a);       /* 6 */
    FF (c, d, a, b, x[6], S13, 0xa8304613);       /* 7 */
    FF (b, c, d, a, x[7], S14, 0xfd469501);       /* 8 */
    FF (a, b, c, d, x[8], S11, 0x698098d8);       /* 9 */
    FF (d, a, b, c, x[9], S12, 0x8b44f7af);       /* 10 */
    FF (c, d, a, b, x[10], S13, 0xffff5bb1);      /* 11 */
    FF (b, c, d, a, x[11], S14, 0x895cd7be);      /* 12 */
    FF (a, b, c, d, x[12], S11, 0x6b901122);      /* 13 */
    FF (d, a, b, c, x[13], S12, 0xfd987193);      /* 14 */
    FF (c, d, a, b, x[14], S13, 0xa679438e);      /* 15 */
    FF (b, c, d, a, x[15], S14, 0x49b40821);      /* 16 */

    /* Round 2 */
    GG (a, b, c, d, x[1], S21, 0xf61e2562);       /* 17 */
    GG (d, a, b, c, x[6], S22, 0xc040b340);       /* 18 */
    GG (c, d, a, b, x[11], S23, 0x265e5a51);      /* 19 */
    GG (b, c, d, a, x[0], S24, 0xe9b6c7aa);       /* 20 */
    GG (a, b, c, d, x[5], S21, 0xd62f105d);       /* 21 */
    GG (d, a, b, c, x[10], S22, 0x2441453);       /* 22 */
    GG (c, d, a, b, x[15], S23, 0xd8a1e681);      /* 23 */
    GG (b, c, d, a, x[4], S24, 0xe7d3fbc8);       /* 24 */
    GG (a, b, c, d, x[9], S21, 0x21e1cde6);       /* 25 */
    GG (d, a, b, c, x[14], S22, 0xc33707d6);      /* 26 */
    GG (c, d, a, b, x[3], S23, 0xf4d50d87);       /* 27 */
    GG (b, c, d, a, x[8], S24, 0x455a14ed);       /* 28 */
    GG (a, b, c, d, x[13], S21, 0xa9e3e905);      /* 29 */
    GG (d, a, b, c, x[2], S22, 0xfcefa3f8);       /* 30 */
    GG (c, d, a, b, x[7], S23, 0x676f02d9);       /* 31 */
    GG (b, c, d, a, x[12], S24, 0x8d2a4c8a);      /* 32 */

    /* Round 3 */
    HH (a, b, c, d, x[5], S31, 0xfffa3942);       /* 33 */
    HH (d, a, b, c, x[8], S32, 0x8771f681);       /* 34 */
    HH (c, d, a, b, x[11], S33, 0x6d9d6122);      /* 35 */
    HH (b, c, d, a, x[14], S34, 0xfde5380c);      /* 36 */
    HH (a, b, c, d, x[1], S31, 0xa4beea44);       /* 37 */
    HH (d, a, b, c, x[4], S32, 0x4bdecfa9);       /* 38 */
    HH (c, d, a, b, x[7], S33, 0xf6bb4b60);       /* 39 */
    HH (b, c, d, a, x[10], S34, 0xbebfbc70);      /* 40 */
    HH (a, b, c, d, x[13], S31, 0x289b7ec6);      /* 41 */
    HH (d, a, b, c, x[0], S32, 0xeaa127fa);       /* 42 */
    HH (c, d, a, b, x[3], S33, 0xd4ef3085);       /* 43 */
    HH (b, c, d, a, x[6], S34, 0x4881d05);        /* 44 */
    HH (a, b, c, d, x[9], S31, 0xd9d4d039);       /* 45 */
    HH (d, a, b, c, x[12], S32, 0xe6db99e5);      /* 46 */
    HH (c, d, a, b, x[15], S33, 0x1fa27cf8);      /* 47 */
    HH (b, c, d, a, x[2], S34, 0xc4ac5665);       /* 48 */

    /* Round 4 */
    II (a, b, c, d, x[0], S41, 0xf4292244);       /* 49 */
    II (d, a, b, c, x[7], S42, 0x432aff97);       /* 50 */
    II (c, d, a, b, x[14], S43, 0xab9423a7);      /* 51 */
    II (b, c, d, a, x[5], S44, 0xfc93a039);       /* 52 */
    II (a, b, c, d, x[12], S41, 0x655b59c3);      /* 53 */
    II (d, a, b, c, x[3], S42, 0x8f0ccc92);       /* 54 */
    II (c, d, a, b, x[10], S43, 0xffeff47d);      /* 55 */
    II (b, c, d, a, x[1], S44, 0x85845dd1);       /* 56 */
    II (a, b, c, d, x[8], S41, 0x6fa87e4f);       /* 57 */
    II (d, a, b, c, x[15], S42, 0xfe2ce6e0);      /* 58 */
    II (c, d, a, b, x[6], S43, 0xa3014314);       /* 59 */
    II (b, c, d, a, x[13], S44, 0x4e0811a1);      /* 60 */
    II (a, b, c, d, x[4], S41, 0xf7537e82);       /* 61 */
    II (d, a, b, c, x[11], S42, 0xbd3af235);      /* 62 */
    II (c, d, a, b, x[2], S43, 0x2ad7d2bb);       /* 63 */
    II (b, c, d, a, x[9], S44, 0xeb86d391);       /* 64 */

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;

    /* Zeroize sensitive information.
    */
    MD5_memset((unsigned char *) x, 0, sizeof (x));

    return;
}

/**
 * Function:    MD5_encode \n
 * Description: Encodes input (unsigned int) into output (unsigned char). \n
                Assumes len is a multiple of 4.\n
 *
 * \param[in]  *input   -input data
 * \param[in]  len  -length of input data
 * \param[out] *output  -output data
 * \return  N/A
 */
static void MD5_encode(unsigned char *output, unsigned int*input, unsigned int len)
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
    {
        output[j] = (unsigned char) (input[i] & 0xff);
        output[j + 1] = (unsigned char) ((input[i] >> 8) & 0xff);
        output[j + 2] = (unsigned char) ((input[i] >> 16) & 0xff);
        output[j + 3] = (unsigned char) ((input[i] >> 24) & 0xff);
    }

    return;
}

/**
 * Function:    MD5_encode \n
 * Description: Decodes input (unsigned char) into output (unsigned int). \n
                Assumes len is a multiple of 4.\n
 *
 * \param[in]  *input   -input data
 * \param[in]  len  -length of input data
 * \param[out] *output  -output data
 * \return  N/A
 */
static void MD5_decode(unsigned int *output, unsigned char *input, unsigned int len)
{
    unsigned int i, j;

    for (i = 0, j = 0; j < len; i++, j += 4)
    {
        output[i] = ((unsigned int) input[j]) | (((unsigned int) input[j + 1]) << 8) |
            (((unsigned int) input[j + 2]) << 16) | (((unsigned int) input[j + 3]) << 24);
    }

    return;
}

/**
 * Function:    MD5_memcpy \n
 * Description: Replace "for loop" with standard memcpy if possible.\n
 *
 * \param[in]  input    -input data
 * \param[in]  len  -length of input data
 * \param[out] output   -output data
 * \return  N/A
 */
static void MD5_memcpy(unsigned char *output, unsigned char *input, unsigned int len)
{
    unsigned int i;

    for (i = 0; i < len; i++)
    {
        output[i] = input[i];
    }

    return;
}

/**
 * Function:    MD5_memset \n
 * Description: Replace "for loop" with standard memset if possible.\n
 *
 * \param[in]  value    -value to be set
 * \param[in]  len  -bytes of need set
 * \param[out] output   -output data
 * \return  N/A
 */
static void MD5_memset(unsigned char *output, int value, unsigned int len)
{
    unsigned int i;

    for (i = 0; i < len; i++)
    {
        ((char *) output)[i] = (char) value;
    }

    return;
}



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
void hamc_encrypt(unsigned char *in, int in_len, unsigned char *key, int key_len, unsigned char *digest)
{
    MD5_CTX context;
    unsigned char k_ipad[65] = {0};    /* inner padding - key XORd with ipad*/
    unsigned char k_opad[65] = {0};    /* outer padding - key XORd with opad*/
    unsigned char tk[16] = {0};
    int i = 0;
	MD5_CTX 	 tctx;

	if(NULL==in || NULL==key || NULL==digest)
	{
		return;
	}
	else
	{
    	/* if key is longer than 64 bytes reset it to key=MD5(key) */
	    if(key_len > 64)
	    {
	        MD5_init(&tctx);
	        MD5_update(&tctx, key, key_len);
	        MD5_final(tk, &tctx);

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
	    memcpy( k_ipad, key,key_len);
	    memcpy( k_opad, key,key_len);
		
	    /* XOR key with ipad and opad values */
	    for(i=0; i<64; i++)
	    {
	        k_ipad[i] ^= 0x36;
	        k_opad[i] ^= 0x5c;
	    }

	    /*
	    * perform inner MD5
	    */
	    MD5_init(&context);                     /* init context for 1st pass */
	    MD5_update(&context, k_ipad, 64);       /* start with inner pad */
	    MD5_update(&context, in, in_len);   /* then text of datagram */
	    MD5_final(digest, &context);            /* finish up 1st pass */
		
	    /* 
	    * perform outer MD5
	    */
	    MD5_init(&context);                     /* init context for 2nd pass */
	    MD5_update(&context, k_opad, 64);       /* start with outer pad */
	    MD5_update(&context, digest, 16);       /* then results of 1st hash */
	    MD5_final(digest, &context);            /* finish up 2nd pass */
	}

	return;
}


