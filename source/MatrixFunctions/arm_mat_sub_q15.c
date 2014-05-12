/* ----------------------------------------------------------------------    
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*    
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*    
* Project:      Cortex-R DSP Library 
* Title:	    arm_mat_sub_q15.c    
*    
* Description:	Q15 Matrix subtraction    
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
 * @ingroup groupMatrix    
 */   
   
/**    
 * @addtogroup MatrixSub    
 * @{    
 */   
   
/**    
 * @brief Q15 matrix subtraction.    
 * @param[in]       *pSrcA points to the first input matrix structure    
 * @param[in]       *pSrcB points to the second input matrix structure    
 * @param[out]      *pDst points to output matrix structure    
 * @return     		The function returns either    
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.    
 *    
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 * <b>Scaling and Overflow Behavior:</b>    
 * \par    
 * The function uses saturating arithmetic.    
 * Results outside of the allowable Q15 range [0x8000 0x7FFF] will be saturated.    
 */   
   
arm_status arm_mat_sub_q15(   
  const arm_matrix_instance_q15 * pSrcA,   
  const arm_matrix_instance_q15 * pSrcB,   
  arm_matrix_instance_q15 * pDst)   
{   
  q15_t *pInA = pSrcA->pData;                    /* input data matrix pointer A */   
  q15_t *pInB = pSrcB->pData;                    /* input data matrix pointer B */   
  q15_t *pOut = pDst->pData;                     /* output data matrix pointer */   
  q31_t inA1, inA2, inB1, inB2;					 /* temporary variables */   
  q31_t out1, out2, out3, out4;					 /* temporary variables */  
  uint32_t numSamples;                           /* total number of elements in the matrix */   
  uint32_t blkCnt;                               /* loop counters  */   
  arm_status status;                             /* status of matrix subtraction  */   
   
   
#ifdef ARM_MATH_MATRIX_CHECK   
  /* Check for matrix mismatch condition */   
  if((pSrcA->numRows != pSrcB->numRows) ||   
     (pSrcA->numCols != pSrcB->numCols) ||   
     (pSrcA->numRows != pDst->numRows) || (pSrcA->numCols != pDst->numCols))   
  {   
    /* Set status as ARM_MATH_SIZE_MISMATCH */   
    status = ARM_MATH_SIZE_MISMATCH;   
  }   
  else   
#endif   
  {   
    /* Total number of samples in the input matrix */   
    numSamples = (uint32_t) pSrcA->numRows * pSrcA->numCols;   
   
    /* Apply loop unrolling */   
    blkCnt = numSamples >> 3u;   
   
    /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.    
     ** a second loop below computes the remaining 1 to 7 samples. */   
    while(blkCnt > 0u)   
    {   
      /* C(m,n) = A(m,n) - B(m,n) */   
      /* Subtract, Saturate and then store the results in the destination buffer. */   
		/* Read two values from source A */   
		inA1 = _SIMD32_OFFSET(pInA);  
	  
	    /* Read two values from source B */   
		inB1 = _SIMD32_OFFSET(pInB);  
	  
		/* Read two values from source A */   
		inA2 = _SIMD32_OFFSET(pInA + 2);  
	  
		/* out = sourceA - sourceB  two at a time */   
		out1 = __QSUB16(inA1, inB1);  
	  
	    /* Read two values from source B */   
		inB2 = _SIMD32_OFFSET(pInB + 2);  
	  
		/* store result to destination buffer */   
		_SIMD32_OFFSET(pOut) = out1;  
	  
		/* out = sourceA - sourceB  two at a time */   
		out2 = __QSUB16(inA2, inB2);     
	  
		/* Read two values from source A */   
		inA1 = _SIMD32_OFFSET(pInA + 4);  
	  
	    /* Read two values from source B */   
		inB1 = _SIMD32_OFFSET(pInB + 4);  
	  
		/* Read two values from source A */   
		inA2 = _SIMD32_OFFSET(pInA + 6);  
	  
		/* out = sourceA - sourceB  two at a time */   
		out3 = __QSUB16(inA1, inB1);  
	  
	    /* Read two values from source B */   
		inB2 = _SIMD32_OFFSET(pInB + 6);  
	  
		/* Increment SourceA pointer */  
		pInA += 8u;  
	  
		/* store result to destination buffer */   
		_SIMD32_OFFSET(pOut + 2) = out2;  
	  
		/* out = sourceA - sourceB  two at a time */   
		out4 = __QSUB16(inA2, inB2);  
	  
		/* store result to destination buffer */   
		_SIMD32_OFFSET(pOut + 4) = out3;  
	  
		/* Incremnet SourceB Pointer */  
		pInB += 8u;  
	  
		/* store result to destination buffer */   
		_SIMD32_OFFSET(pOut + 6) = out4;  
	  
		/* Increment destination pointer */  
		pOut += 8u;  
  
      /* Decrement the loop counter */   
      blkCnt--;   
    }   
   
    /* If the blockSize is not a multiple of 8, compute any remaining output samples here.    
     ** No loop unrolling is used. */   
    blkCnt = numSamples % 0x8u;   
   
    while(blkCnt > 0u)   
    {   
      /* C(m,n) = A(m,n) - B(m,n) */   
      /* Subtract and then store the results in the destination buffer. */   
      *pOut++ = (q15_t) __QSUB16(*pInA++, *pInB++);   
   
      /* Decrement the loop counter */   
      blkCnt--;   
    }   
   
    /* Set status as ARM_MATH_SUCCESS */   
    status = ARM_MATH_SUCCESS;   
  }   
   
  /* Return to application */   
  return (status);   
}   
   
/**    
 * @} end of MatrixSub group    
 */   
