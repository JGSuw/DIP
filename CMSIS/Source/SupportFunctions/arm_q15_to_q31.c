/* ----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_q15_to_q31.c      
*      
* Description:	Converts the elements of the Q15 vector to Q31 vector.    
*      
* Target Processor:          Cortex-R4/R5
*
* Version 1.0.0 2011/03/08
*     Alpha release.
*
* Version 1.0.1 2011/09/30
*     Beta release.
*
* Version 2.0.0 2011/12/15
*     Final release. 
* 
* ---------------------------------------------------------------------------- */     
#include "arm_math.h"     
     
/**      
 * @ingroup groupSupport      
 */     
     
/**      
 * @addtogroup q15_to_x      
 * @{      
 */     
     
/**      
 * @brief Converts the elements of the Q15 vector to Q31 vector.       
 * @param[in]       *pSrc points to the Q15 input vector      
 * @param[out]      *pDst points to the Q31 output vector     
 * @param[in]       blockSize length of the input vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * \par Description:      
 *      
 * The equation used for the conversion process is:     
 *     
 * <pre>      
 * 	pDst[n] = (q31_t) pSrc[n] << 16;   0 <= n < blockSize.      
 * </pre>      
 *     
 */     
     
     
void arm_q15_to_q31(     
  q15_t * pSrc,     
  q31_t * pDst,     
  uint32_t blockSize)     
{     
  q15_t *pIn = pSrc;                             /* Src pointer */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t out1, out2, out3, out4;  
  q31_t in1, in2, in3, in4;    
  
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (q31_t)A << 16 */     
    /* convert from q15 to q31 and then store the results in the destination buffer */     
	/* read two samples at a time */  
	in1 = _SIMD32_OFFSET(pIn);  
	in2 = _SIMD32_OFFSET(pIn + 2);  
	in3 = _SIMD32_OFFSET(pIn + 4);  
	in4 = _SIMD32_OFFSET(pIn + 6);  
	  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* extract lower 16 bits to 32 bit result */  
	out1 = in1 << 16u;  
	/* extract upper 16 bits to 32 bit result */  
	out2 = in1 & 0xFFFF0000;  
  
#else  
  
	/* extract upper 16 bits to 32 bit result */  
	out1 = in1 & 0xFFFF0000;  
	/* extract lower 16 bits to 32 bit result */  
	out2 = in1 << 16u;  
  
#endif	 	//	#ifndef ARM_MATH_BIG_ENDIAN	   
  
	/* store result to destination */  
	pDst[0] = out1;  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* extract lower 16 bits to 32 bit result */  
	out3 = in2 << 16u;  
  
	/* store result to destination */  
	pDst[1] = out2;  
  
	/* extract upper 16 bits to 32 bit result */  
	out4 = in2 & 0xFFFF0000;  
  
#else  
  
	/* extract upper 16 bits to 32 bit result */  
	out3 = in2 & 0xFFFF0000;  
  
	/* store result to destination */  
	pDst[1] = out2;  
  
	/* extract lower 16 bits to 32 bit result */  
	out4 = in2 << 16u;  
  
#endif	 	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	pDst[2] = out3;  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* extract lower 16 bits to 32 bit result */  
	out1 = in3 << 16u;  
  
	/* store result to destination */  
	pDst[3] = out4;  
  
	/* extract upper 16 bits to 32 bit result */  
	out2 = in3 & 0xFFFF0000;  
  
#else  
  
	/* extract upper 16 bits to 32 bit result */  
	out1 = in3 & 0xFFFF0000;  
  
	/* store result to destination */  
	pDst[3] = out4;  
  
	/* extract lower 16 bits to 32 bit result */  
	out2 = in3 << 16u;  
  
#endif	 	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* store result to destination */  
	pDst[4] = out1;  
  
	/* extract upper 16 bits to 32 bit result */  
	out3 = in4 & 0xFFFF0000;  
  
	pDst[5] = out2;  
  
	/* extract lower 16 bits to 32 bit result */  
	out4 = in4 << 16u;  
  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* store result to destination */  
	pDst[7] = out3;  
  
	/* increment input pointer */  
	pIn += 8u;  
  
	/* store result to destination */  
	pDst[6] = out4;  
  
#else  
  
	/* store result to destination */  
	pDst[6] = out3;  
  
	/* increment input pointer */  
	pIn += 8u;  
  
	/* store result to destination */  
	pDst[7] = out4;  
  
#endif	 	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* increment destination pointer */  
	pDst += 8u;  
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = (q31_t)A << 16 */     
    /* convert from q15 to q31 and then store the results in the destination buffer */     
    *pDst++ = (q31_t) * pIn++ << 16;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
}     
     
/**      
 * @} end of q15_to_x group      
 */     
