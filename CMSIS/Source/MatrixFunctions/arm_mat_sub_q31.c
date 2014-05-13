/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_mat_sub_q31.c      
*      
* Description:	Q31 matrix subtraction      
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
 * @brief Q31 matrix subtraction.      
 * @param[in]       *pSrcA points to the first input matrix structure      
 * @param[in]       *pSrcB points to the second input matrix structure      
 * @param[out]      *pDst points to output matrix structure      
 * @return     		The function returns either      
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.      
 *      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The function uses saturating arithmetic.      
 * Results outside of the allowable Q31 range [0x80000000 0x7FFFFFFF] will be saturated.      
 */     
     
     
arm_status arm_mat_sub_q31(     
  const arm_matrix_instance_q31 * pSrcA,     
  const arm_matrix_instance_q31 * pSrcB,     
  arm_matrix_instance_q31 * pDst)     
{     
  q31_t *pIn1 = pSrcA->pData;                    /* input data matrix pointer A */     
  q31_t *pIn2 = pSrcB->pData;                    /* input data matrix pointer B */     
  q31_t *pOut = pDst->pData;                     /* output data matrix pointer */   
  q31_t inA1, inA2, inB1, inB2;					 /* temporary variables */   
  q31_t out1, out2;								 /* temporary variables */ 	  
  uint32_t numSamples;                           /* total number of elements in the matrix  */   
  uint32_t blkCnt;                               /* loop counters */     
  arm_status status;                             /* status of matrix subtraction */     
     
     
#ifdef ARM_MATH_MATRIX_CHECK     
  /* Check for matrix mismatch condition  */     
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
     
    /* Loop Unrolling */     
    blkCnt = numSamples >> 3u;     
     
    /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
     ** a second loop below computes the remaining 1 to 7 samples. */     
    while(blkCnt > 0u)     
    {     
      /* C(m,n) = A(m,n) - B(m,n) */     
      /* Subtract, saturate and then store the results in the destination buffer. */     
	  /* Read values from source A */   
	  inA1 = pIn1[0];  
  
	  /* Read values from source B */   
	  inB1 = pIn2[0];  
  
	  /* Read values from source A */   
	  inA2 = pIn1[1];  
  
	  /* Subtract and saturate */  
	  out1 = __QSUB(inA1, inB1);  
  
	  /* Read values from source B */   
	  inB2 = pIn2[1];  
  
	  /* Read values from source A */   
	  inA1 = pIn1[2];  
  
	  /* Subtract and saturate */  
	  out2 = __QSUB(inA2, inB2);  
  
	  /* Read values from source B */   
	  inB1 = pIn2[2];    
  
	  /* Store result in destination */   
	  pOut[0] = out1;  
	  pOut[1] = out2;  
  
	  /* Read values from source A */   
	  inA2 = pIn1[3];  
  
	  /* Read values from source B */   
	  inB2 = pIn2[3];  
    
	  /* Subtract and saturate */  
	  out1 = __QSUB(inA1, inB1);  
  
	  /* Read values from source A */   
	  inA1 = pIn1[4];  
  
	  /* Subtract and saturate */  
	  out2 = __QSUB(inA2, inB2);  
	    
	  /* Read values from source B */   
	  inB1 = pIn2[4];  
  
	  /* Store result in destination */   
	  pOut[2] = out1;  
  
	  /* Read values from source A */   
	  inA2 = pIn1[5];  
  
	  /* Subtract and saturate */  
	  out1 = __QSUB(inA1, inB1);  
  
	  /* Read values from source B */   
	  inB2 = pIn2[5];  
  
	  /* Store result in destination */   
	  pOut[3] = out2;  
  
	  /* Read values from source A */   
	  inA1 = pIn1[6];  
  
	  /* Subtract and saturate */  
	  out2 = __QSUB(inA2, inB2);  
  
	  /* Read values from source A */   
	  inA2 = pIn1[7];  
	    
	  /* Read values from source B */   
	  inB1 = pIn2[6];  
	  inB2 = pIn2[7];  
  
	  /* Store result in destination */   
	  pOut[4] = out1;  
  
	  /* Subtract and saturate */  
	  out1 = __QSUB(inA1, inB1);  
  
	  /* Store result in destination */   
	  pOut[5] = out2;  
  
	  /* Subtract and saturate */  
	  out2 = __QSUB(inA2, inB2);  
  
	  /* Store result in destination */   
	  pOut[6] = out1;  
  
	  /* Increment Soruce A pointer */  
	  pIn1 += 8u;  
  
	  pOut[7] = out2;  
  
	  /* Increment Soruce B pointer */  
	  pIn2 += 8u;  
  
	  /* Increment Destination pointer */  
	  pOut += 8u;   
   
      /* Decrement the loop counter */   
      blkCnt--;   
    }     
     
    /* If the numSamples is not a multiple of 8, compute any remaining output samples here.      
     ** No loop unrolling is used. */     
    blkCnt = numSamples % 0x8u;     
     
    while(blkCnt > 0u)     
    {     
      /* C(m,n) = A(m,n) - B(m,n) */     
      /* Subtract, saturate and then store the results in the destination buffer. */     
	  inA1 = *pIn1++;   
	  inB1 = *pIn2++;   
   
      inA1 = __QSUB(inA1, inB1);   
   
	  *pOut++ = inA1;   
     
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
