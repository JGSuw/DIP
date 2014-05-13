/* ----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_q31_to_q15.c      
*      
* Description:	Converts the elements of the Q31 vector to Q15 vector.      
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
 * @addtogroup q31_to_x      
 * @{      
 */     
     
/**      
 * @brief Converts the elements of the Q31 vector to Q15 vector.      
 * @param[in]       *pSrc points to the Q31 input vector      
 * @param[out]      *pDst points to the Q15 output vector     
 * @param[in]       blockSize length of the input vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
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
 * 	pDst[n] = (q15_t) pSrc[n] >> 16;   0 <= n < blockSize.      
 * </pre>      
 *     
 */     
     
     
void arm_q31_to_q15(     
  q31_t * pSrc,     
  q15_t * pDst,     
  uint32_t blockSize)     
{     
  q31_t *pIn = pSrc;                             /* Src pointer */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2, in3, in4;  
//  q15_t out1, out2, out3, out4;  
  q31_t out1, out2, out3, out4;  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (q15_t) A >> 16 */     
    /* convert from q31 to q15 and then store the results in the destination buffer */     
	/* read input samples */  
	in1 = pIn[0];  
	in2 = pIn[1];  
	in3 = pIn[2];  
	in4 = pIn[3];  
  
	/* pack two higher 16-bit values from two 32-bit values */  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	out1 = __PKHTB(in2, in1, 16);  
	out2 = __PKHTB(in4, in3, 16);  
  
#else  
  
	out1 = __PKHTB(in1, in2, 16);  
	out2 = __PKHTB(in3, in4, 16);  
  
#endif		//	#ifdef ARM_MATH_BIG_ENDIAN  
  
	/* read input samples */  
	in1 = pIn[4];  
	in2 = pIn[5];  
	in3 = pIn[6];  
	in4 = pIn[7];  
  
	/* pack two higher 16-bit values from two 32-bit values */  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	out3 = __PKHTB(in2, in1, 16);  
	out4 = __PKHTB(in4, in3, 16);  
  
#else  
  
	out3 = __PKHTB(in1, in2, 16);  
	out4 = __PKHTB(in3, in4, 16);  
  
#endif		//	#ifdef ARM_MATH_BIG_ENDIAN  
  
	/* store two samples at a time to destination */  
	_SIMD32_OFFSET(pDst) = out1;  
	_SIMD32_OFFSET(pDst + 2) = out2;  
	_SIMD32_OFFSET(pDst + 4) = out3;  
	_SIMD32_OFFSET(pDst + 6) = out4;  
  
	/* incremnet source pointer */  
	pIn += 8u;  
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
    /* C = (q15_t) A >> 16 */     
    /* convert from q31 to q15 and then store the results in the destination buffer */     
    *pDst++ = (q15_t) (*pIn++ >> 16);     
     
    blkCnt--;     
  }     
     
}     
   												    
    /* Decrement the loop counter */     
/**      
 * @} end of q31_to_x group      
 */     
