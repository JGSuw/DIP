/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_negate_q15.c      
*      
* Description:	Negates Q15 vectors.      
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
 * @brief  Negates the elements of a Q15 vector.      
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
 * The Q15 value -1 (0x8000) will be saturated to the maximum allowable positive value 0x7FFF.      
 */     
     
void arm_negate_q15(     
  q15_t * pSrc,     
  q15_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  q15_t in;		                                 /* Temporary variables */     
  q31_t in1, in2, in3, in4;	 					 /* Temporary variables */  
     
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = -A */     
    /* Read two inputs at a time */     
	in1 = _SIMD32_OFFSET(pSrc);  
	in2 = _SIMD32_OFFSET(pSrc + 2);  
  
	/* negate two samples at a time */  
	in1 = __QSUB16(0, in1);  
  
    /* Read two inputs at a time */     
	in3 = _SIMD32_OFFSET(pSrc + 4);  
  
	/* negate two samples at a time */  
	in2 = __QSUB16(0, in2);  
  
    /* Read two inputs at a time */     
	in4 = _SIMD32_OFFSET(pSrc + 6);  
  
	/* store the result to destination 2 samples at a time */  
	_SIMD32_OFFSET(pDst) = in1;  
  
	/* negate two samples at a time */  
	in3 = __QSUB16(0, in3);  
  
	/* store the result to destination 2 samples at a time */  
	_SIMD32_OFFSET(pDst + 2) = in2;  
  
	/* negate two samples at a time */  
	in4 = __QSUB16(0, in4);  
  
	/* store the result to destination 2 samples at a time */  
	_SIMD32_OFFSET(pDst + 4) = in3;  
  
	/* increment source pointer by 8 to process next samples */  
	pSrc += 8u;  
  
	/* store the result to destination 2 samples at a time */  
	_SIMD32_OFFSET(pDst + 6) = in4;  
  
	/* increment destination pointer by 8 */  
	pDst += 8u;  
   
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = -A */     
    /* Negate and then store the result in the destination buffer. */    
	in = *pSrc++;  
  
	*pDst++ = __QSUB16(0, in);  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of negate group      
 */     
