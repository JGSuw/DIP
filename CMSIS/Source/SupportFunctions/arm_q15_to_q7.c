/* ----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_q15_to_q7.c      
*      
* Description:	Converts the elements of the Q15 vector to Q7 vector.    
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
 * @brief Converts the elements of the Q15 vector to Q7 vector.       
 * @param[in]       *pSrc points to the Q15 input vector      
 * @param[out]      *pDst points to the Q7 output vector     
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
 * 	pDst[n] = (q7_t) pSrc[n] >> 8;   0 <= n < blockSize.      
 * </pre>     
 *     
 */     
     
     
void arm_q15_to_q7(     
  q15_t * pSrc,     
  q7_t * pDst,     
  uint32_t blockSize)     
{     
  q15_t *pIn = pSrc;                             /* Src pointer */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2, in3, in4;  
  q31_t out1, out2, out3, out4;  
  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = (q7_t) A >> 8 */     
    /* convert from q15 to q7 and then store the results in the destination buffer */  
	/* read two input sampeles at a time */     
	in1 = _SIMD32_OFFSET(pIn);  
	in2 = _SIMD32_OFFSET(pIn + 2);  
	in3 = _SIMD32_OFFSET(pIn + 4);  
	in4 = _SIMD32_OFFSET(pIn + 6);  
  
	/* pack two q15_t values */  
#ifndef ARM_MATH_BIG_ENDIAN  
  
	out1 = __PKHTB(in2, in1, 16);  
	out2 = __PKHBT(in2, in1, 16);  
	out3 = __PKHTB(in4, in3, 16);  
	out4 = __PKHBT(in4, in3, 16);  
  
#else  
  
	out1 = __PKHTB(in1, in2, 16);  
	out2 = __PKHBT(in1, in2, 16);  
	out3 = __PKHTB(in3, in4, 16);  
	out4 = __PKHBT(in3, in4, 16);  
  
#endif	 	//	#ifndef ARM_MATH_BIG_ENDIAN  
  
	/* rotate packed value by 24 */  
	out2 = ((uint32_t)out2 << 8) | ((uint32_t)out2 >> 24);  
	  
	/* anding with 0xff00ff00 to get two 8 bit values */  
	out1 = out1 & 0xFF00FF00;  
	/* anding with 0x00ff00ff to get two 8 bit values */  
	out2 = out2 & 0x00FF00FF;  
  
	/* rotate packed value by 24 */  
	out4 = ((uint32_t)out4 << 8) | ((uint32_t)out4 >> 24);  
	  
	/* anding with 0xff00ff00 to get two 8 bit values */  
	out3 = out3 & 0xFF00FF00;  
	/* anding with 0x00ff00ff to get two 8 bit values */  
	out4 = out4 & 0x00FF00FF;  
  
	/* oring two values(contains two 8 bit values) to get four packed 8 bit values */  
	out2 = out1 | out2;  
	out4 = out3 | out4;  
  
	/* store result to destination */  
	_SIMD32_OFFSET(pDst) = out2;  
	/* incremnet input pointer */  
	pIn += 8u;  
	/* store result to destination */  
	_SIMD32_OFFSET(pDst + 4) = out4;  
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
    /* C = (q7_t) A >> 8 */     
    /* convert from q15 to q7 and then store the results in the destination buffer */     
    *pDst++ = (q7_t) (*pIn++ >> 8);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
}     
     
/**      
 * @} end of q15_to_x group      
 */     
