/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_mat_scale_q15.c      
*      
* Description:	Multiplies a Q15 matrix by a scalar.      
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
 * @brief Q15 matrix scaling.      
 * @param[in]       *pSrc points to input matrix      
 * @param[in]       scaleFract fractional portion of the scale factor      
 * @param[in]       shift number of bits to shift the result by      
 * @param[out]      *pDst points to output matrix structure      
 * @return     		The function returns either      
 * <code>ARM_MATH_SIZE_MISMATCH</code> or <code>ARM_MATH_SUCCESS</code> based on the outcome of size checking.      
 *      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 * @details      
 * <b>Scaling and Overflow Behavior:</b>      
 * \par      
 * The input data <code>*pSrc</code> and <code>scaleFract</code> are in 1.15 format.      
 * These are multiplied to yield a 2.30 intermediate result and this is shifted with saturation to 1.15 format.      
 */     
     
arm_status arm_mat_scale_q15(     
  const arm_matrix_instance_q15 * pSrc,     
  q15_t scaleFract,     
  int32_t shift,     
  arm_matrix_instance_q15 * pDst)     
{     
  q15_t *pIn = pSrc->pData;                      /* input data matrix pointer */     
  q15_t *pOut = pDst->pData;                     /* output data matrix pointer */     
  uint32_t numSamples;                           /* total number of elements in the matrix */     
  int32_t totShift = 15 - shift;                 /* total shift to apply after scaling */     
  uint32_t blkCnt;                               /* loop counters */     
  arm_status status;                             /* status of matrix scaling     */     
  q15_t in1, in2, in3, in4;  
  q31_t out1, out2, out3 ,out4;   
  q31_t inA1, inA2;  
  
#ifdef ARM_MATH_MATRIX_CHECK     
  /* Check for matrix mismatch */     
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
      /* Scale, saturate and then store the results in the destination buffer. */     
    /* Reading 2 inputs from memory */     
    inA1 = _SIMD32_OFFSET(pIn);     
    inA2 = _SIMD32_OFFSET(pIn + 2);   
	    
    /* C = A * scale */     
    /* Scale the inputs and then store the 2 results in the destination buffer      
     * in single cycle by packing the outputs */     
 	out1 = (q31_t)((q15_t)(inA1 >> 16) * scaleFract);  
	out2 = (q31_t)((q15_t)inA1 * scaleFract);  
	out3 = (q31_t)((q15_t)(inA2 >> 16) * scaleFract);  
	out4 = (q31_t)((q15_t)inA2 * scaleFract);  
  
	out1 = out1 >> totShift;  
    inA1 = _SIMD32_OFFSET(pIn + 4);     
	out2 = out2 >> totShift;  
    inA2 = _SIMD32_OFFSET(pIn + 6);   
	out3 = out3 >> totShift;  
	out4 = out4 >> totShift;  
  
#ifdef CCS  
	in1 = (q15_t)(__SSATA(out1, 0, 16));  
	in2 = (q15_t)(__SSATA(out2, 0, 16));  
	in3 = (q15_t)(__SSATA(out3, 0, 16));  
	in4 = (q15_t)(__SSATA(out4, 0, 16));  
#else  
	in1 = (q15_t)(__SSAT(out1, 16));  
	in2 = (q15_t)(__SSAT(out2, 16));  
	in3 = (q15_t)(__SSAT(out3, 16));  
	in4 = (q15_t)(__SSAT(out4, 16));  
#endif  
  
//#ifndef ARM_MATH_BIG_ENDIAN  
// 	*__SIMD32(pDst)++ = __PKHBT(in1, in2,16);  
// 	*__SIMD32(pDst)++ = __PKHBT(in3, in4,16);  
//#else  
 	_SIMD32_OFFSET(pOut) = __PKHBT(in2, in1,16);  
 	_SIMD32_OFFSET(pOut + 2) = __PKHBT(in4, in3,16);  
//#endif  
   /* Reading 2 inputs from memory */     
	    
    /* C = A * scale */     
    /* Scale the inputs and then store the 2 results in the destination buffer      
     * in single cycle by packing the outputs */     
 	out1 = (q31_t)((q15_t)(inA1 >> 16) * scaleFract);  
	out2 = (q31_t)((q15_t)inA1 * scaleFract);  
	out3 = (q31_t)((q15_t)(inA2 >> 16) * scaleFract);  
	out4 = (q31_t)((q15_t)inA2 * scaleFract);  
  
	out1 = out1 >> totShift;  
	out2 = out2 >> totShift;  
	out3 = out3 >> totShift;  
	out4 = out4 >> totShift;  
  
#ifdef CCS  
	in1 = (q15_t)(__SSATA(out1, 0, 16));  
	in2 = (q15_t)(__SSATA(out2, 0, 16));  
	in3 = (q15_t)(__SSATA(out3, 0, 16));  
	in4 = (q15_t)(__SSATA(out4, 0, 16));  
#else  
	in1 = (q15_t)(__SSAT(out1, 16));  
	in2 = (q15_t)(__SSAT(out2, 16));  
	in3 = (q15_t)(__SSAT(out3, 16));  
	in4 = (q15_t)(__SSAT(out4, 16));  
#endif  
  
//#ifndef ARM_MATH_BIG_ENDIAN  
// 	*__SIMD32(pDst)++ = __PKHBT(in1, in2,16);  
// 	*__SIMD32(pDst)++ = __PKHBT(in3, in4,16);  
//#else  
 	_SIMD32_OFFSET(pOut + 4) = __PKHBT(in2, in1,16);  
 	_SIMD32_OFFSET(pOut + 6) = __PKHBT(in4, in3,16);  
//#endif  
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
#ifdef CCS	     
      *pOut++ =     
        (q15_t) (__SSATA(((q31_t) (*pIn++) * scaleFract) >> totShift, 0, 16));     
#else   
      *pOut++ =     
        (q15_t) (__SSAT(((q31_t) (*pIn++) * scaleFract) >> totShift, 16));     
#endif	//	#ifdef CCS   
		   
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
