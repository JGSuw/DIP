/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_dot_prod_f32.c      
*      
* Description:	Floating-point dot product.      
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
 * @defgroup dot_prod Vector Dot Product      
 *      
 * Computes the dot product of two vectors.      
 * The vectors are multiplied element-by-element and then summed.      
 * There are separate functions for floating-point, Q7, Q15, and Q31 data types.      
 */     
     
/**      
 * @addtogroup dot_prod      
 * @{      
 */     
     
/**      
 * @brief Dot product of floating-point vectors.      
 * @param[in]       *pSrcA points to the first input vector      
 * @param[in]       *pSrcB points to the second input vector      
 * @param[in]       blockSize number of samples in each vector      
 * @param[out]      *result output result returned here      
 * @return none.      
 */     
     
     
void arm_dot_prod_f32(     
  float32_t * pSrcA,     
  float32_t * pSrcB,     
  uint32_t blockSize,     
  float32_t * result)     
{     
  float32_t sum1 = 0.0f;  
  float32_t sum2 = 0.0f, sum3 = 0.0f, sum4 = 0.0f;			             /* Temporary result storage */     
  float32_t inA1, inA2, inB1, inB2;  
  float32_t inA3, inA4, inB3, inB4;  
  uint32_t blkCnt;                               /* loop counter */     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */     
    /* Calculate dot product and then store the result in a temporary buffer */     
  
	/* read input from sourceA */  
	inA1 = *pSrcA;  
	/* read input from sourceB */  
	inB1 = *pSrcB;  
	/* read input from sourceA */  
	inA2 = *(pSrcA + 1);  
	/* read input from sourceB */  
	inB2 = *(pSrcB + 1);  
  
	/* multiply and accumulate */  
	sum1 += inA1 * inB1;  
  
	/* read input from sourceA */  
	inA3 = *(pSrcA + 2);  
	/* read input from sourceB */  
	inB3 = *(pSrcB + 2);  
  
	/* multiply and accumulate */  
	sum2 += inA2 * inB2;  
  
	/* read input from sourceA */  
	inA4 = *(pSrcA + 3);  
	/* read input from sourceB */  
	inB4 = *(pSrcB + 3);  
  
	/* multiply and accumulate */  
	sum3 += inA3 * inB3;  
  
	/* read input from sourceA */  
	inA1 = *(pSrcA + 4);  
	/* read input from sourceB */  
	inB1 = *(pSrcB + 4);  
  
	/* multiply and accumulate */  
	sum4 += inA4 * inB4;  
  
	/* read input from sourceA */  
	inA2 = *(pSrcA + 5);  
	/* read input from sourceB */  
	inB2 = *(pSrcB + 5);  
  
	/* multiply and accumulate */  
	sum1 += inA1 * inB1;  
  
	/* read input from sourceA */  
	inA3 = *(pSrcA + 6);  
	/* read input from sourceB */  
	inB3 = *(pSrcB + 6);  
  
	/* multiply and accumulate */  
	sum2 += inA2 * inB2;  
  
	/* read input from sourceA */  
	inA4 = *(pSrcA + 7);  
	/* read input from sourceB */  
	inB4 = *(pSrcB + 7);  
  
	/* multiply and accumulate */  
	sum3 += inA3 * inB3;  
  
	/* increment sourceA pointer by 8 */  
	pSrcA += 8u;  
	/* increment sourceB pointer by 8 */  
	pSrcB += 8u;  
	  
	/* multiply and accumulate */  
	sum4 += inA4 * inB4;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }   
  /* add accumulators */    
  sum1 = sum1 + sum2 + sum3 + sum4;   
  
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
  
  while(blkCnt > 0u)     
  {     
    /* C = A[0]* B[0] + A[1]* B[1] + A[2]* B[2] + .....+ A[blockSize-1]* B[blockSize-1] */     
    /* Calculate dot product and then store the result in a temporary buffer. */     
	inA1 = *pSrcA++;  
	inB1 = *pSrcB++;  
    sum1 += (inA1 * inB1);  
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* Store the result back in the destination buffer */     
  *result = sum1;     
}     
     
/**      
 * @} end of dot_prod group      
 */     
