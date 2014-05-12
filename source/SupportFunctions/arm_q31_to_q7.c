/* ----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_q31_to_q7.c      
*      
* Description:	Converts the elements of the Q31 vector to Q7 vector.      
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
 * @ingroup groupSupport      
 */     
     
/**      
 * @addtogroup q31_to_x      
 * @{      
 */     
     
/**      
 * @brief Converts the elements of the Q31 vector to Q7 vector.      
 * @param[in]       *pSrc points to the Q31 input vector      
 * @param[out]      *pDst points to the Q7 output vector     
 * @param[in]       blockSize length of the input vector      
 * @return none.      
 *  
 * \par Conditions for optimum performance  
 *  Input and output buffers should be aligned by 32-bit  
 *  
 *      
 * \par Description:      
 *      
 * The equation used for the conversion process is:      
 *     
 * <pre>      
 * 	pDst[n] = (q7_t) pSrc[n] >> 24;   0 <= n < blockSize.       
 * </pre>      
 *     
 */     
     
     
void arm_q31_to_q7(     
  q31_t * pSrc,     
  q7_t * pDst,     
  uint32_t blockSize)     
{     
  q31_t *pIn = pSrc;                             /* Src pointer */     
  uint32_t blkCnt;                               /* loop counter */     
  q31_t in1, in2, in3, in4; 
  q31_t in5, in6, in7, in8; 
  q7_t out1, out2, out3, out4;
     
  /*loop Unrolling */     
  blkCnt = blockSize >> 3u;     
     
  /* First part of the processing with loop unrolling.  Compute 8 outputs at a time.      
   ** a second loop below computes the remaining 1 to 7 samples. */     
  while(blkCnt > 0u)     
  {   			     
    /* C = (q7_t) A >> 24 */     
    /* convert from q31 to q7 and then store the results in the destination buffer */     
	/* read input samples */  
	in1 = pIn[0];  
	in2 = pIn[1];  
	out1 = (q7_t)(in1 >> 24); 
	in3 = pIn[2];  
	out2 = (q7_t)(in2 >> 24); 
	in4 = pIn[3]; 
	
	out3 = (q7_t)(in3 >> 24); 
	out4 = (q7_t)(in4 >> 24); 
 
  	*__SIMD32(pDst)++ = __PACKq7(out1, out2, out3, out4);

	in5 = pIn[4];  
	in6 = pIn[5];  
	out1 = (q7_t)(in5 >> 24); 
	in7 = pIn[6];  
	out2 = (q7_t)(in6 >> 24); 
	in8 = pIn[7]; 
	
	out3 = (q7_t)(in7 >> 24); 
	out4 = (q7_t)(in8 >> 24); 

  	*__SIMD32(pDst)++ = __PACKq7(out1, out2, out3, out4);

	/* update pointer to process next samples */
	pIn += 8u;

    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
  /* If the blockSize is not a multiple of 8, compute any remaining output samples here.      
   ** No loop unrolling is used. */     
  blkCnt = blockSize % 0x8u;     
     
  while(blkCnt > 0u)     
  {     
    /* C = (q7_t) A >> 24 */     
    /* convert from q31 to q7 and then store the results in the destination buffer */     
    *pDst++ = (q7_t) (*pIn++ >> 24);     
     
    /* Decrement the loop counter */     
    blkCnt--;     
  }     
     
}     
     
/**      
 * @} end of q31_to_x group      
 */     
