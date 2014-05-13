/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_negate_q7.c      
*      
* Description:	Negates Q7 vectors.      
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
 * @addtogroup negate      
 * @{      
 */     
     
/**      
 * @brief  Negates the elements of a Q7 vector.      
 * @param[in]  *pSrc points to the input vector      
 * @param[out]  *pDst points to the output vector      
 * @param[in]  blockSize number of samples in the vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * The Q7 value -1 (0x80) will be saturated to the maximum allowable positive value 0x7F.      
 */     
     
void arm_negate_q7(     
  q7_t * pSrc,     
  q7_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q7_t in;                                      /* Input value1 */     
  q31_t in1, in2, in3, in4;  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 4u;     
     
  /* First part of the processing with loop unrolling.  Compute 16 outputs at a time.      
   ** a second loop below computes the remaining 1 to 15 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = -A */     
    /* Read four inputs at a time */     
	 in1 = _SIMD32_OFFSET(pSrc);  
	 in2 = _SIMD32_OFFSET(pSrc + 4);  
  
	 /* negate four samples at a time */	   
	 in1 = __QSUB8(0, in1);  
  
    /* Read four inputs at a time */     
	 in3 = _SIMD32_OFFSET(pSrc + 8);  
  
	 /* negate four samples at a time */	   
	 in2 = __QSUB8(0, in2);  
  
    /* Read four inputs at a time */     
	 in4 = _SIMD32_OFFSET(pSrc + 12);  
  
	 /* store the result to destination four samples at a time */  
	 _SIMD32_OFFSET(pDst) = in1;  
  
	 /* negate four samples at a time */	   
	 in3 = __QSUB8(0, in3);  
  
	 /* store the result to destination four samples at a time */  
	 _SIMD32_OFFSET(pDst + 4) = in2;  
  
	 /* negate four samples at a time */	   
	 in4 = __QSUB8(0, in4);  
  
	 /* store the result to destination four samples at a time */  
	 _SIMD32_OFFSET(pDst + 8) = in3;  
	   
	 /* increment source pointer by 16 to process next samples */  
	 pSrc += 16u;  
	   
	 /* store the result to destination 4 samples at a time */  
	 _SIMD32_OFFSET(pDst + 12) = in4;  
	   
	 /* increment destination pointer by 16 */  
	 pDst += 16u;  
  
	/* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 16, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x10u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = -A */     
	in = *pSrc++;  
  
    *pDst++ = __QSUB8(0, in);  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of negate group      
 */     
