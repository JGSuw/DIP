/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_negate_f32.c      
*      
* Description:	Negates floating-point vectors.      
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
 * @defgroup negate Vector Negate      
 *      
 * Negates the elements of a vector.      
 *      
 * <pre>      
 *     pDst[n] = -pSrc[n],   0 <= n < blockSize.      
 * </pre>      
 */     
     
/**      
 * @addtogroup negate      
 * @{      
 */     
     
/**      
 * @brief  Negates the elements of a floating-point vector.      
 * @param[in]  *pSrc points to the input vector      
 * @param[out]  *pDst points to the output vector      
 * @param[in]  blockSize number of samples in the vector      
 * @return none.      
 */     
     
void arm_negate_f32(     
  float32_t * pSrc,     
  float32_t * pDst,     
  uint32_t blockSize)     
{     
  uint32_t blkCnt;                               /* loop counter */     
  float32_t in1, in2, in3, in4;	 				 /* temporary variables */  
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {     
	  /* read inputs from source */  
	  in1 = *pSrc;  
	  in2 = *(pSrc + 1);  
	  in3 = *(pSrc + 2);  
	  in4 = *(pSrc + 3);  
  
	  /* negate the input */  
	  in1 = -in1;  
	  in2 = -in2;  
	  in3 = -in3;  
	  in4 = -in4;  
  
	  /* store the result to destination */  
	  *pDst = in1;  
	  *(pDst + 1) = in2;  
	  *(pDst + 2) = in3;  
	  *(pDst + 3) = in4;  
  
	  /* read inputs from source */  
	  in1 = *(pSrc + 4);  
	  in2 = *(pSrc + 5);  
	  in3 = *(pSrc + 6);  
	  in4 = *(pSrc + 7);  
  
	  /* negate the input */  
	  in1 = -in1;  
	  in2 = -in2;  
	  in3 = -in3;  
	  in4 = -in4;  
  
	  /* store the result to destination */  
	  *(pDst + 4) = in1;  
	  *(pDst + 5) = in2;  
	  *(pDst + 6) = in3;  
	  *(pDst + 7) = in4;  
  
	  /* increment sourec by 8 to process next samples */  
	  pSrc += 8u;  
	  /* increment destination by 8 to process next samples */  
	  pDst += 8u;  
  
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = -A */     
    /* Negate and then store the results in the destination buffer. */     
    *pDst++ = -*pSrc++;     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
}     
     
/**      
 * @} end of negate group      
 */     
