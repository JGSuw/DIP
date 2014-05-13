/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_add_q31.c      
*      
* Description:	Q31 vector addition.      
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
 * @brief Q31 vector addition.      
 * @param[in]       *pSrcA points to the first input vector      
 * @param[in]       *pSrcB points to the second input vector      
 * @param[out]      *pDst points to the output vector      
 * @param[in]       blockSize number of samples in each vector      
 * @return none.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q31 range[0x80000000 0x7FFFFFFF] will be saturated.      
 */     
     
void arm_add_q31(     
  q31_t * pSrcA,     
  q31_t * pSrcB,     
  q31_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t inA1, inA2, inA3, inA4;	  				 /* temporary input variables */  
  q31_t inB1, inB2, inB3, inB4;					 /* temporary input variables */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A + B */     
    /* Add and then store the results in the destination buffer. */     
	/* read input from soruceA */  
	inA1 = *pSrcA;  
	/* read input from soruceB */  
	inB1 = *pSrcB;  
	/* read input from soruceA */  
	inA2 = *(pSrcA + 1);  
	/* read input from soruceB */  
	inB2 = *(pSrcB + 1);  
  
	/* add, saturate and store result to destination */  
	*pDst = __QADD(inA1, inB1);  
  
	/* read input from soruceA */  
	inA3 = *(pSrcA + 2);  
	/* read input from soruceB */  
	inB3 = *(pSrcB + 2);  
  
	/* add, saturate and store result to destination */  
	*(pDst + 1) = __QADD(inA2, inB2);  
  
	/* read input from soruceA */  
	inA4 = *(pSrcA + 3);  
	/* read input from soruceB */  
	inB4 = *(pSrcB + 3);  
  
	/* add, saturate and store result to destination */  
	*(pDst + 2) = __QADD(inA3, inB3);  
  
	/* read input from soruceA */  
	inA1 = *(pSrcA + 4);  
	/* read input from soruceB */  
	inB1 = *(pSrcB + 4);  
  
	/* add, saturate and store result to destination */  
	*(pDst + 3) = __QADD(inA4, inB4);  
  
	/* read input from soruceA */  
	inA2 = *(pSrcA + 5);  
	/* read input from soruceB */  
	inB2 = *(pSrcB + 5);  
  
	/* add, saturate and store result to destination */  
	*(pDst + 4) = __QADD(inA1, inB1);  
  
	/* read input from soruceA */  
	inA3 = *(pSrcA + 6);  
	/* read input from soruceB */  
	inB3 = *(pSrcB + 6);  
  
	/* add, saturate and store result to destination */  
	*(pDst + 5) = __QADD(inA2, inB2);  
  
	/* read input from soruceA */  
	inA4 = *(pSrcA + 7);  
  
	/* add, saturate and store result to destination */  
	*(pDst + 6) = __QADD(inA3, inB3);  
  
	/* increment sourceA pointer by 8 */  
	pSrcA += 8u;  
  
	/* read input from soruceB */  
	inB4 = *(pSrcB + 7);  
  
	/* increment sourceB pointer by 8 */  
	pSrcB += 8u;  
  
	/* add, saturate and store result to destination */  
	*(pDst + 7) = __QADD(inA4, inB4);  
  
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
	inA1 = *pSrcA++;  
	inB1 = *pSrcB++;  
	     
    *pDst++ = __QADD(inA1, inB1);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of BasicAdd group      
 */     
