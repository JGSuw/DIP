/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_mat_scale_f32.c      
*      
* Description:	Multiplies a floating-point matrix by a scalar.      
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
 * @defgroup MatrixScale Matrix Scale      
 *      
 * Multiplies a matrix by a scalar.  This is accomplished by multiplying each element in the      
 * matrix by the scalar.  For example:      
 * \image html MatrixScale.gif "Matrix Scaling of a 3 x 3 matrix"      
 *      
 * The function checks to make sure that the input and output matrices are of the same size.      
 *      
 * In the fixed-point Q15 and Q31 functions, <code>scale</code> is represented by      
 * a fractional multiplication <code>scaleFract</code> and an arithmetic shift <code>shift</code>.      
 * The shift allows the gain of the scaling operation to exceed 1.0.      
 * The overall scale factor applied to the fixed-point data is      
 * <pre>      
 *     scale = scaleFract * 2^shift.      
 * </pre>      
 */     
     
/**      
 * @addtogroup MatrixScale      
 * @{      
 */     
     
/**      
 * @brief Floating-point matrix scaling.      
 * @param[in]       *pSrc points to input matrix structure      
 * @param[in]       scale scale factor to be applied       
 * @param[out]      *pDst points to output matrix structure      
 * @return     		The function returns either <code>ARM_MATH_SIZE_MISMATCH</code>       
 * or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.      
 *      
 */     
     
arm_status arm_mat_scale_f32(     
  const arm_matrix_instance_f32 * pSrc,     
  float32_t scale,     
  arm_matrix_instance_f32 * pDst)     
{     
  float32_t *pIn = pSrc->pData;                  /* input data matrix pointer */     
  float32_t *pOut = pDst->pData;                 /* output data matrix pointer */     
  float32_t in1, in2, in3, in4;  
  float32_t in5, in6, in7, in8;  
  float32_t out1, out2, out3, out4;				 /* temporary variables */   
  float32_t out5, out6, out7, out8;  
  uint32_t numSamples;                           /* total number of elements in the matrix */     
  uint32_t blkCnt;                               /* loop counters */     
  arm_status status;                             /* status of matrix scaling     */     
     
#ifdef ARM_MATH_MATRIX_CHECK     
  /* Check for matrix mismatch condition */     
  if((pSrc->numRows != pDst->numRows) || (pSrc->numCols != pDst->numCols))     
  {     
    /* Set status as ARM_MATH_SIZE_MISMATCH */     
    status = ARM_MATH_SIZE_MISMATCH;     
  }     
  else     
#endif     
  {     
    /* Total number of samples in the input matrix */     
    numSamples = (uint32_t) pSrc->numRows * pSrc->numCols;     
     
    /* Loop Unrolling */     
    blkCnt = numSamples >> 3u;     
     
    /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
     ** a second loop below computes the remaining 1 to 7 samples. */     
    while(blkCnt > 0u)     
    {     
      /* C(m,n) = A(m,n) * scale */     
      /* Scaling and results are stored in the destination buffer. */    
	  in1 = pIn[0];  
	  in2 = pIn[1];  
	  in3 = pIn[2];  
	  in4 = pIn[3];  
  
	  out1 = in1 * scale;  
	  out2 = in2 * scale;  
	  out3 = in3 * scale;  
	  out4 = in4 * scale;  
  
	  in5 = pIn[4];  
	  in6 = pIn[5];  
	  in7 = pIn[6];  
	  in8 = pIn[7];  
  
	  pOut[0] = out1;  
	  pOut[1] = out2;  
	  pOut[2] = out3;  
	  pOut[3] = out4;  
  
	  out5 = in5 * scale;  
	  out6 = in6 * scale;  
	  out7 = in7 * scale;  
	  out8 = in8 * scale;  
  
	  pOut[4] = out5;  
	  pOut[5] = out6;  
	  pOut[6] = out7;  
	  pOut[7] = out8;  
	    
	  pIn += 8u;  
	  pOut += 8u;  
  
      /* Decrement the numSamples loop counter */     
      blkCnt--;     
    }     
     
    /* If the numSamples is not a multiple of 8, compute any remaining output samples here.      
     ** No loop unrolling is used. */     
    blkCnt = numSamples % 0x8u;     
     
    while(blkCnt > 0u)     
    {     
      /* C(m,n) = A(m,n) * scale */     
      /* The results are stored in the destination buffer. */     
      *pOut++ = (*pIn++) * scale;     
     
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
 * @} end of MatrixScale group      
 */     
