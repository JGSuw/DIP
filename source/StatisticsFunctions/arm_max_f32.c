/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_max_f32.c      
*      
* Description:	Maximum value of a floating-point vector.      
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
 * @ingroup groupStats      
 */     
     
/**      
 * @defgroup Max Maximum      
 *      
 * Computes the maximum value of an array of data.       
 * The function returns both the maximum value and its position within the array.       
 * There are separate functions for floating-point, Q31, Q15, and Q7 data types.      
 */     
     
/**      
 * @addtogroup Max      
 * @{      
 */     
     
     
/**      
 * @brief Maximum value of a floating-point vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult maximum value returned here      
 * @param[out]      *pIndex index of maximum value returned here      
 * @return none.      
 */     
     
void arm_max_f32(     
  float32_t * pSrc,     
  uint32_t blockSize,     
  float32_t * pResult,     
  uint32_t * pIndex)     
{     
  float32_t maxVal1, maxVal2, out;                         /* Temporary variables to store the output value. */     
  uint32_t blkCnt, outIndex, count;              /* loop counter */     
     
  /* Initialise the count value. */     
  count = 0u;  
  /* Initialise the index value to zero. */     
  outIndex = 0u;     
  /* Load first input value that act as reference value for comparision */     
  out = *pSrc++;     
     
  /* Loop unrolling */     
  
  blkCnt = (blockSize - 1u) >> 2u;     
     
  while(blkCnt > 0u)     
  {     
    /* Initialize maxVal to the next consecutive values one by one */     
    maxVal1 = pSrc[0];     
     
	maxVal2 = pSrc[1];    
    
    /* compare for the maximum value */     
    if(out < maxVal1)     
    {     
      /* Update the maximum value and its index */     
      out = maxVal1;     
      outIndex = count + 1u;     
    }     
     
    maxVal1 = pSrc[2];     
	   
    /* compare for the maximum value */     
    if(out < maxVal2)     
    {     
      /* Update the maximum value and its index */     
      out = maxVal2;     
      outIndex = count + 2u;     
    }     
     
	maxVal2 = pSrc[3];     
  
    /* compare for the maximum value */     
    if(out < maxVal1)     
    {     
      /* Update the maximum value and its index */     
      out = maxVal1;     
      outIndex = count + 3u;     
    }     
  
    /* compare for the maximum value */     
    if(out < maxVal2)     
    {     
      /* Update the maximum value and its index */     
      out = maxVal2;     
      outIndex = count + 4u;     
    }     
  
   	count += 4u;  
  
	pSrc += 4u;  
  
	/* Decrement the loop counter */    
    blkCnt--;        
  }   
  
  /* if (blockSize - 1u) is not multiple of 4 */  
  blkCnt = (blockSize - 1u) % 4u;     
     
  while(blkCnt > 0u)     
  {     
    /* Initialize maxVal to the next consecutive values one by one */     
    maxVal1 = *pSrc++;     
     
    /* compare for the maximum value */     
    if(out < maxVal1)     
    {     
      /* Update the maximum value and it's index */     
      out = maxVal1;     
      outIndex = blockSize - blkCnt;     
    }     
  
  
	/* Decrement the loop counter */    
    blkCnt--;     
     
  }     
     
  /* Store the maximum value and it's index into destination pointers */     
  *pResult = out;     
  *pIndex = outIndex;     
}     
     
/**      
 * @} end of Max group      
 */     
