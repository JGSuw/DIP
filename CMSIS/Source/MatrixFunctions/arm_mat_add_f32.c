/* ----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_mat_add_f32.c      
*      
* Description:	Floating-point matrix addition      
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
* -------------------------------------------------------------------------- */     
     
#include "arm_math.h"     
     
/**      
 * @ingroup groupMatrix      
 */     
     
/**      
 * @defgroup MatrixAdd Matrix Addition      
 *      
 * Adds two matrices.      
 * \image html MatrixAddition.gif "Addition of two 3 x 3 matrices"      
 *      
 * The functions check to make sure that      
 * <code>pSrcA</code>, <code>pSrcB</code>, and <code>pDst</code> have the same      
 * number of rows and columns.      
 */     
     
/**      
 * @addtogroup MatrixAdd      
 * @{      
 */     
     
     
/**      
 * @brief Floating-point matrix addition.      
 * @param[in]       *pSrcA points to the first input matrix structure      
 * @param[in]       *pSrcB points to the second input matrix structure      
 * @param[out]      *pDst points to output matrix structure      
 * @return     		The function returns either      
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.      
 */     
     
arm_status arm_mat_add_f32(     
  const arm_matrix_instance_f32 * pSrcA,     
  const arm_matrix_instance_f32 * pSrcB,     
  arm_matrix_instance_f32 * pDst)     
{     
  float32_t *pIn1 = pSrcA->pData;                /* input data matrix pointer A  */     
  float32_t *pIn2 = pSrcB->pData;                /* input data matrix pointer B  */     
  float32_t *pOut = pDst->pData;                 /* output data matrix pointer   */     
  float32_t inA1, inA2, inB1, inB2, out1, out2;  /* temporary variables */   
  uint32_t numSamples;                           /* total number of elements in the matrix  */     
  uint32_t blkCnt;                               /* loop counters */     
  arm_status status;                             /* status of matrix addition */     
     
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
     
    /* Loop unrolling */     
    blkCnt = numSamples >> 3u;   
     
    /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.    
     ** a second loop below computes the remaining 1 to 7 samples. */   
    while(blkCnt > 0u)     
    {     
      /* C(m,n) = A(m,n) + B(m,n) */     
      /* Add and then store the results in the destination buffer. */   
	  /* Read values from source A */   
	  inA1 = pIn1[0];  
  
	  /* Read values from source B */   
	  inB1 = pIn2[0];  
  
	  /* Read values from source A */   
	  inA2 = pIn1[1];  
  
	  /* out = sourceA + sourceB */  
	  out1 = inA1 + inB1;  
  
	  /* Read values from source B */   
	  inB2 = pIn2[1];  
  
	  /* Read values from source A */   
	  inA1 = pIn1[2];  
  
	  /* out = sourceA + sourceB */  
	  out2 = inA2 + inB2;  
  
	  /* Read values from source B */   
	  inB1 = pIn2[2];    
  
	  /* Store result in destination */   
	  pOut[0] = out1;  
	  pOut[1] = out2;  
  
	  /* Read values from source A */   
	  inA2 = pIn1[3];  
  
	  /* Read values from source B */   
	  inB2 = pIn2[3];  
    
	  /* out = sourceA + sourceB */  
	  out1 = inA1 + inB1;  
  
	  /* Read values from source A */   
	  inA1 = pIn1[4];  
  
	  /* out = sourceA + sourceB */  
	  out2 = inA2 + inB2;  
	    
	  /* Read values from source B */   
	  inB1 = pIn2[4];  
  
	  /* Store result in destination */   
	  pOut[2] = out1;  
  
	  /* Read values from source A */   
	  inA2 = pIn1[5];  
  
	  /* out = sourceA + sourceB */  
	  out1 = inA1 + inB1;  
  
	  /* Read values from source B */   
	  inB2 = pIn2[5];  
  
	  /* Store result in destination */   
	  pOut[3] = out2;  
  
	  /* Read values from source A */   
	  inA1 = pIn1[6];  
  
	  /* out = sourceA + sourceB */  
	  out2 = inA2 + inB2;  
  
	  /* Read values from source A */   
	  inA2 = pIn1[7];  
	    
	  /* Read values from source B */   
	  inB1 = pIn2[6];  
	  inB2 = pIn2[7];  
  
	  /* Store result in destination */   
	  pOut[4] = out1;  
  
	  /* out = sourceA + sourceB */  
	  out1 = inA1 + inB1;  
  
	  /* Store result in destination */   
	  pOut[5] = out2;  
  
	  /* out = sourceA + sourceB */  
	  out2 = inA2 + inB2;  
  
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
      /* C(m,n) = A(m,n) + B(m,n) */     
      /* Add and then store the results in the destination buffer. */     
      *pOut++ = (*pIn1++) + (*pIn2++);     
     
      /* Decrement the loop counter */     
      blkCnt--;     
    }     
     
    /* set status as ARM_MATH_SUCCESS */     
    status = ARM_MATH_SUCCESS;     
     
  }     
     
  /* Return to application */     
  return (status);     
}     
     
/**      
 * @} end of MatrixAdd group      
 */     
