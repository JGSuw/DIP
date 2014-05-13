/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_mat_scale_q31.c      
*      
* Description:	Multiplies a Q31 matrix by a scalar.      
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
 * @addtogroup MatrixScale      
 * @{      
 */     
     
/**      
 * @brief Q31 matrix scaling.      
 * @param[in]       *pSrc points to input matrix      
 * @param[in]       scaleFract fractional portion of the scale factor      
 * @param[in]       shift number of bits to shift the result by      
 * @param[out]      *pDst points to output matrix structure      
 * @return     		The function returns either      
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.      
 *      
 * @details      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The input data <code>*pSrc</code> and <code>scaleFract</code> are in 1.31 format.      
 * These are multiplied to yield a 2.62 intermediate result and this is shifted with saturation to 1.31 format.      
 */     
     
arm_status arm_mat_scale_q31(     
  const arm_matrix_instance_q31 * pSrc,     
  q31_t scaleFract,     
  int32_t shift,     
  arm_matrix_instance_q31 * pDst)     
{     
  q31_t *pIn = pSrc->pData;                      /* input data matrix pointer */     
  q31_t *pOut = pDst->pData;                     /* output data matrix pointer */     
  uint32_t numSamples;                           /* total number of elements in the matrix */     
  int32_t totShift = shift+1;                    /* shift to apply after scaling */     
  uint32_t blkCnt;                               /* loop counters  */     
  arm_status status;                             /* status of matrix scaling      */     
  q31_t in1, in2, in3, in4;  
  q31_t out1, out2, out3, out4;   
  
   
#ifdef ARM_MATH_MATRIX_CHECK     
  /* Check for matrix mismatch  */     
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
      /* C(m,n) = A(m,n) * k */     
	  /* Read values from input */   
	  in1 = *pIn;   
	  in2 = *(pIn + 1);   
	  in3 = *(pIn + 2);   
	  in4 = *(pIn + 3);   
   
      /* multiply input with scaler value */   
	  in1 = ((q63_t) in1 * scaleFract) >> 32;   
      in2 = ((q63_t) in2 * scaleFract) >> 32;    
	  in3 = ((q63_t) in3 * scaleFract) >> 32;   
      in4 = ((q63_t) in4 * scaleFract) >> 32;    
	     
	  /* apply shifting */   
	  out1 = in1 << totShift;   
	  out2 = in2 << totShift;   
  
      /* saturate the results. */     
	  if(in1 != (out1 >> totShift))   
	  out1 = 0x7FFFFFFF ^(in1 >> 31);   
	     
	  if(in2 != (out2 >> totShift))   
	  out2 = 0x7FFFFFFF ^(in2 >> 31);   
	     
	  out3 = in3 << totShift;   
	  out4 = in4 << totShift;   
	     
	  *pOut = out1;   
	  *(pOut + 1) = out2;   
  
	  if(in3 != (out3 >> totShift))   
	  out3 = 0x7FFFFFFF ^(in3 >> 31);   
	     
	  in1 = *(pIn + 4);   
	  in2 = *(pIn + 5);   
  
	  if(in4 != (out4 >> totShift))   
	  out4 = 0x7FFFFFFF ^(in4 >> 31);   
	     
	  /* Store result destination */   
	  *(pOut + 2) = out3;   
	  *(pOut + 3) = out4;   
  
	  in3 = *(pIn + 6);   
	  in4 = *(pIn + 7);   
   
      /* multiply input with scaler value */   
	  in1 = ((q63_t) in1 * scaleFract) >> 32;   
      in2 = ((q63_t) in2 * scaleFract) >> 32;    
	  in3 = ((q63_t) in3 * scaleFract) >> 32;   
      in4 = ((q63_t) in4 * scaleFract) >> 32;    
	     
	  /* apply shifting */   
	  out1 = in1 << totShift;   
	  out2 = in2 << totShift;   
  
      /* saturate the results. */     
	  if(in1 != (out1 >> totShift))   
	  out1 = 0x7FFFFFFF ^(in1 >> 31);   
	     
	  if(in2 != (out2 >> totShift))   
	  out2 = 0x7FFFFFFF ^(in2 >> 31);   
	     
	  *(pOut + 4) = out1;   
	  out3 = in3 << totShift;   
	  *(pOut + 5) = out2;   
	  out4 = in4 << totShift;   
  
	  if(in3 != (out3 >> totShift))   
	  out3 = 0x7FFFFFFF ^(in3 >> 31);   
	     
	  if(in4 != (out4 >> totShift))   
	  out4 = 0x7FFFFFFF ^(in4 >> 31);   
	     
	  /* Store result destination */   
	  *(pOut + 6) = out3;   
	  *(pOut + 7) = out4;   
  
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
      /* C(m,n) = A(m,n) * k */     
      /* Scale, saturate and then store the results in the destination buffer. */     
      in1 = *pIn++;   
   
	  in2 = ((q63_t)in1  * scaleFract) >> 32;     
   
      out1 = in2 << totShift;   
   
	  if(in2 != (out1 >> totShift))   
	  out1 = 0x7FFFFFFF ^(in2 >> 31);   
   
	  *pOut++ = out1;     
     
      /* Decrement the numSamples loop counter */     
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
