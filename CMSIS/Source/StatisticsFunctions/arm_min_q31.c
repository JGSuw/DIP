/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:		arm_min_q31.c      
*      
* Description:	Minimum value of a Q31 vector.      
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
 * @addtogroup Min      
 * @{      
 */     
     
     
/**      
 * @brief Minimum value of a Q31 vector.      
 * @param[in]       *pSrc points to the input vector      
 * @param[in]       blockSize length of the input vector      
 * @param[out]      *pResult minimum value returned here      
 * @param[out]      *pIndex index of minimum value returned here      
 * @return none.      
 *      
 */     
     
void arm_min_q31(     
  q31_t * pSrc,     
  uint32_t blockSize,     
  q31_t * pResult,     
  uint32_t * pIndex)     
{     
  q31_t minVal1, minVal2, minVal3, minVal4, out;                             /* Temporary variables to store the output value. */     
  uint32_t blkCnt, count, outIndex;              /* loop counter */     
     
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
    /* Initialize minVal to the next consecutive values one by one */     
    minVal1 = *pSrc++;     
    minVal2 = *pSrc++;     
    minVal3 = *pSrc++;     
    minVal4 = *pSrc++;     
     
    /* compare for the minimum value */     
    if(out > minVal1)     
    {     
      /* Update the minimum value and its index */     
      out = minVal1;     
      outIndex = count + 1u;     
    }     
     
    /* compare for the minimum value */     
    if(out > minVal2)     
    {     
      /* Update the minimum value and its index */     
      out = minVal2;     
      outIndex = count + 2u;     
    }     
     
    /* compare for the minimum value */     
    if(out > minVal3)     
    {     
      /* Update the minimum value and its index */     
      out = minVal3;     
      outIndex = count + 3u;     
    }     
  
    /* compare for the minimum value */     
    if(out > minVal4)     
    {     
      /* Update the minimum value and its index */     
      out = minVal4;     
      outIndex = count + 4u;     
    }     
  
   	count += 4u;  
  
    blkCnt--;     
  };     
  
  /* if (blockSize - 1u) is not multiple of 4 */  
  blkCnt = (blockSize - 1u) % 4u;     
     
  while(blkCnt > 0u)     
  {     
    /* Initialize minVal to the next consecutive values one by one */     
    minVal1 = *pSrc++;     
     
    /* compare for the minimum value */     
    if(out > minVal1)     
    {     
      /* Update the minimum value and its index */     
      out = minVal1;     
      outIndex = blockSize - blkCnt;     
    }     
     
    blkCnt--;     
  };     
     
  /* Store the minimum value and its index into destination pointers */     
  *pResult = out;     
  *pIndex = outIndex;     
}     
     
/**      
 * @} end of Min group      
 */     
