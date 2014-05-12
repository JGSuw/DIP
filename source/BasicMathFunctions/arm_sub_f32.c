/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_sub_f32.c      
*      
* Description:	Floating-point vector subtraction.      
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
 * @ingroup groupMath      
 */     
     
/**      
 * @defgroup BasicSub Vector Subtraction      
 *      
 * Element-by-element subtraction of two vectors.      
 *      
 * <pre>      
 *     pDst[n] = pSrcA[n] - pSrcB[n],   0 <= n < blockSize.      
 * </pre>      
 *      
 * There are separate functions for floating-point, Q7, Q15, and Q31 data types.      
 */     
     
/**      
 * @addtogroup BasicSub      
 * @{      
 */     
     
     
/**      
 * @brief Floating-point vector subtraction.      
 * @param[in]       *pSrcA points to the first input vector      
 * @param[in]       *pSrcB points to the second input vector      
 * @param[out]      *pDst points to the output vector      
 * @param[in]       blockSize number of samples in each vector      
 * @return none.      
 */     
     
void arm_sub_f32(     
  float32_t * pSrcA,     
  float32_t * pSrcB,     
  float32_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  float32_t inA1, inA2, inA3, inA4;	   			 /* temporary variables */  
  float32_t inB1, inB2, inB3, inB4;				 /* temporary variables */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A - B */     
    /* Subtract and then store the results in the destination buffer. */     
	/* Read 4 input samples from sourceA and sourceB */  
	inA1 = *pSrcA;  
	inB1 = *pSrcB;  
	inA2 = *(pSrcA + 1);  
	inB2 = *(pSrcB + 1);  
	inA3 = *(pSrcA + 2);  
	inB3 = *(pSrcB + 2);  
	inA4 = *(pSrcA + 3);  
	inB4 = *(pSrcB + 3);  
  
	/* dst = srcA - srcB */  
	/* subtract and store the result */  
	*pDst = inA1 - inB1;  
	*(pDst + 1) = inA2 - inB2;  
	*(pDst + 2) = inA3 - inB3;  
	*(pDst + 3) = inA4 - inB4;  
  
	/* Read 4 input samples from sourceA and sourceB */  
	inA1 = *(pSrcA + 4);  
	inB1 = *(pSrcB + 4);  
	inA2 = *(pSrcA + 5);  
	inB2 = *(pSrcB + 5);  
	inA3 = *(pSrcA + 6);  
	inB3 = *(pSrcB + 6);  
	inA4 = *(pSrcA + 7);  
	inB4 = *(pSrcB + 7);  
  
	/* dst = srcA - srcB */  
	/* subtract and store the result */  
	*(pDst + 4) = inA1 - inB1;  
	*(pDst + 5) = inA2 - inB2;  
	*(pDst + 6) = inA3 - inB3;  
	*(pDst + 7) = inA4 - inB4;  
  
	/* Update pointers to process next sampels */  
	pSrcA += 8u;  
	pSrcB += 8u;  
	pDst += 8u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A - B */     
    /* Subtract and then store the results in the destination buffer. */     
	inA1 = *pSrcA++;  
	inB1 = *pSrcB++;  
  
    *pDst++ = inA1 - inB1;  
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of BasicSub group      
 */     
