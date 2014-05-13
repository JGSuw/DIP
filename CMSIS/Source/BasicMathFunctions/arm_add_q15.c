/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_add_q15.c      
*      
* Description:	Q15 vector addition      
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
* -------------------------------------------------------------------- */     
#include "arm_math.h"     
     
/**      
 * @ingroup groupMath      
 */     
     
/**      
 * @addtogroup BasicAdd      
 * @{      
 */     
     
/**      
 * @brief Q15 vector addition.      
 * @param[in]       *pSrcA points to the first input vector      
 * @param[in]       *pSrcB points to the second input vector      
 * @param[out]      *pDst points to the output vector      
 * @param[in]       blockSize number of samples in each vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q15 range [0x8000 0x7FFF] will be saturated.      
 */     
     
void arm_add_q15(     
  q15_t * pSrcA,     
  q15_t * pSrcB,     
  q15_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t inA1, inA2;		 						 /* temporary input variables */  
  q31_t inB1, inB2;								 /* temporary input variabels */  
  q31_t out1, out2, out3, out4;					 /* temporary output variables */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A + B */     
    /* Add and then store the results in the destination buffer. */     
	/* read two samples at a time from sourceA buffer */  
	inA1 = _SIMD32_OFFSET(pSrcA);  
	/* read two samples at a time from sourceB buffer */  
	inB1 = _SIMD32_OFFSET(pSrcB);  
	/* read two samples at a time from sourceA buffer */  
	inA2 = _SIMD32_OFFSET(pSrcA + 2);  
  
	/* add, saturate and store two samples to destination at a time*/  
	out1 = __QADD16(inA1, inB1);  
  
	/* read two samples at a time from sourceB buffer */  
	inB2 = _SIMD32_OFFSET(pSrcB + 2);  
  
	/* store two output samples at a time to destination */  
	_SIMD32_OFFSET(pDst) = out1;  
  
	/* add, saturate and store two samples to destination at a time*/  
	out2 = __QADD16(inA2, inB2);     
  
	/* read two samples at a time from sourceA buffer */  
	inA1 = _SIMD32_OFFSET(pSrcA + 4);  
	/* read two samples at a time from sourceB buffer */  
	inB1 = _SIMD32_OFFSET(pSrcB + 4);  
	/* read two samples at a time from sourceA buffer */  
	inA2 = _SIMD32_OFFSET(pSrcA + 6);  
  
	/* add, saturate and store two samples to destination at a time*/  
	out3 = __QADD16(inA1, inB1);  
  
	/* read two samples at a time from sourceB buffer */  
	inB2 = _SIMD32_OFFSET(pSrcB + 6);  
  
	/* increment sourceA pointer by 8 */  
	pSrcA += 8u;  
  
	/* store two output samples at a time to destination */  
	_SIMD32_OFFSET(pDst + 2) = out2;  
  
	/* add, saturate and store two samples to destination at a time*/  
	out4 = __QADD16(inA2, inB2);  
  
	/* store two output samples at a time to destination */  
	_SIMD32_OFFSET(pDst + 4) = out3;  
  
	/* increment sourceB pointer by 8 */  
	pSrcB += 8u;  
  
	/* store two output samples at a time to destination */  
	_SIMD32_OFFSET(pDst + 6) = out4;  
  
	/* increment destination pointer by 8 */  
	pDst += 8u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A + B */     
    /* Add and then store the results in the destination buffer. */     
    *pDst++ = (q15_t) __QADD16(*pSrcA++, *pSrcB++);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
}     
     
/**      
 * @} end of BasicAdd group      
 */     
