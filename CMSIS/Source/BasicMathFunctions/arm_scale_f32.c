/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_scale_f32.c      
*      
* Description:	Multiplies a floating-point vector by a scalar.      
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
 * @defgroup scale Vector Scale      
 *      
 * Multiply a vector by a scalar value.  For floating-point data, the algorithm used is:      
 *      
 * <pre>      
 *     pDst[n] = pSrc[n] * scale,   0 <= n < blockSize.      
 * </pre>      
 *      
 * In the fixed-point Q7, Q15, and Q31 functions, <code>scale</code> is represented by      
 * a fractional multiplication <code>scaleFract</code> and an arithmetic shift <code>shift</code>.      
 * The shift allows the gain of the scaling operation to exceed 1.0.      
 * The algorithm used with fixed-point data is:      
 *      
 * <pre>      
 *     pDst[n] = (pSrc[n] * scaleFract) << shift,   0 <= n < blockSize.      
 * </pre>      
 *      
 * The overall scale factor applied to the fixed-point data is      
 * <pre>      
 *     scale = scaleFract * 2^shift.      
 * </pre>      
 */     
     
/**      
 * @addtogroup scale      
 * @{      
 */     
     
/**      
 * @brief Multiplies a floating-point vector by a scalar.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       scale scale factor to be applied      
 * @param[out]      *pDst points to the output vector      
 * @param[in]       blockSize number of samples in the vector      
 * @return none.      
 */     
     
     
void arm_scale_f32(     
  float32_t * pSrc,     
  float32_t scale,     
  float32_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  float32_t in1, in2, in3, in4;	  				 /* temporary variabels */  
  float32_t in5, in6, in7, in8;					 /* temporary variabels */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
    /* C = A * scale */     
    /* Scale the input and then store the results in the destination buffer. */     
	/* read input samples from source */  
	in1 = *pSrc;  
	in2 = *(pSrc + 1);  
  
	/* multiply with scaling factor */  
    in1 = in1 * scale;     
  
	/* read input sample from source */  
	in3 = *(pSrc + 2);  
  
	/* multiply with scaling factor */  
    in2 = in2 * scale;     
  
	/* read input sample from source */  
	in4 = *(pSrc + 3);  
  
	/* multiply with scaling factor */  
    in3 = in3 * scale;     
  
	/* read input sample from source */  
	in5 = *(pSrc + 4);  
  
	/* multiply with scaling factor */  
    in4 = in4 * scale;     
  
	/* read input sample from source */  
	in6 = *(pSrc + 5);  
  
	/* multiply with scaling factor */  
    in5 = in5 * scale;     
  
	/* read input sample from source */  
	in7 = *(pSrc + 6);  
  
	/* multiply with scaling factor */  
    in6 = in6 * scale;     
  
	/* read input sample from source */  
	in8 = *(pSrc + 7);  
  
	/* multiply with scaling factor */  
    in7 = in7 * scale;     
  
	/* store the result to destination */  
	*pDst = in1;  
  
	/* multiply with scaling factor */  
    in8 = in8 * scale;     
  
	/* store the result to destination */  
	*(pDst + 1) = in2;  
	*(pDst + 2) = in3;  
	*(pDst + 3) = in4;  
	*(pDst + 4) = in5;  
	*(pDst + 5) = in6;  
  
	/* increment source pointer by 8 to process next samples */  
	pSrc += 8u;  
  
	/* store the result to destination */  
	*(pDst + 6) = in7;  
	*(pDst + 7) = in8;  
  
	/* increment destination by 8 */  
	pDst += 8u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = A * scale */     
    /* Scale the input and then store the result in the destination buffer. */     
    *pDst++ = (*pSrc++) * scale;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of scale group      
 */     
