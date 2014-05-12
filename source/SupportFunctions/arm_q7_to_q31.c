/* ----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_q7_to_q31.c      
*      
* Description:	Converts the elements of the Q7 vector to Q31 vector.    
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
 * @addtogroup q7_to_x      
 * @{      
 */     
     
/**      
 * @brief Converts the elements of the Q7 vector to Q31 vector.      
 * @param[in]       *pSrc points to the Q7 input vector      
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
 * 	pDst[n] = (q31_t) pSrc[n] << 24;   0 <= n < blockSize.     
 * </pre>       
 *     
 */     
     
     
void arm_q7_to_q31(     
  q7_t * pSrc,     
  q31_t * pDst,     
  uint32_t blockSize)     
{     
  q7_t *pIn = pSrc;                              /* Src pointer */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t out1, out2, out3, out4;  
  q31_t input1, input2;  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (q31_t) A << 24 */     
    /* convert from q7 to q31 and then store the results in the destination buffer */     
  
	/* read 4 samples at a time */  
	input1 = *__SIMD32(pIn)++;  
	input2 = *__SIMD32(pIn)++;  
  
	/* extract q7_t value and convert it to q31_t value */  
	out1 = (input1 >> 24) << 24;  
	out2 = (input1 >> 16) << 24;  
	out3 = (input1 >> 8) << 24;  
	out4 = (input1 << 24);  
  
	/* store result samples to destination */  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	pDst[3] = out1;  
	pDst[2] = out2;  
	pDst[1] = out3;  
	pDst[0] = out4;  
  
#else  
  
	pDst[0] = out1;  
	pDst[1] = out2;  
	pDst[2] = out3;  
	pDst[3] = out4;  
  
#endif	 	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* extract q7_t value and convert it to q31_t value */  
	out1 = (input2 >> 24) << 24;  
	out2 = (input2 >> 16) << 24;  
	out3 = (input2 >> 8) << 24;  
	out4 = (input2 << 24);  
  
	/* store result samples to destination */  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	pDst[7] = out1;  
	pDst[6] = out2;  
	pDst[5] = out3;  
	pDst[4] = out4;  
  
#else  
  
	pDst[4] = out1;  
	pDst[5] = out2;  
	pDst[6] = out3;  
	pDst[7] = out4;  
  
#endif	 	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	pDst += 8u;  
    
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = (q31_t) A << 24 */     
    /* convert from q7 to q31 and then store the results in the destination buffer */     
    *pDst++ = (q31_t) * pIn++ << 24;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
}     
     
/**      
 * @} end of q7_to_x group      
 */     
