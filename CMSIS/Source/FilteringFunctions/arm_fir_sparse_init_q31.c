/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_fir_sparse_init_q31.c      
*      
* Description:	Q31 sparse FIR filter initialization function.     
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
* ---------------------------------------------------------------------------*/     
#include "arm_math.h"     
     
/**      
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup FIR_Sparse      
 * @{      
 */     
     
/**     
 * @brief  Initialization function for the Q31 sparse FIR filter.     
 * @param[in,out] *S         points to an instance of the Q31 sparse FIR structure.     
 * @param[in]     numTaps    number of nonzero coefficients in the filter.     
 * @param[in]     *pCoeffs   points to the array of filter coefficients.     
 * @param[in]     *pState    points to the state buffer.     
 * @param[in]     *pTapDelay points to the array of offset times.     
 * @param[in]     maxDelay   maximum offset time supported.     
 * @param[in]     blockSize  number of samples that will be processed per block.     
 * @return none     
 *      
 * <b>Description:</b>      
 * \par      
 * <code>pCoeffs</code> holds the filter coefficients and has length <code>numTaps</code>.      
 * <code>pState</code> holds the filter's state variables and must be of length      
 * <code>maxDelay + blockSize</code>, where <code>maxDelay</code>      
 * is the maximum number of delay line values.      
 * <code>blockSize</code> is the number of words processed by <code>arm_fir_sparse_q31()</code> function.      
 */     
     
void arm_fir_sparse_init_q31(     
  arm_fir_sparse_instance_q31 * S,     
  uint16_t numTaps,     
  q31_t * pCoeffs,     
  q31_t * pState,     
  int32_t * pTapDelay,     
  uint16_t maxDelay,     
  uint32_t blockSize)     
{     
  /* Assign filter taps */     
  S->numTaps = numTaps;     
     
  /* Assign coefficient pointer */     
  S->pCoeffs = pCoeffs;     
     
  /* Assign TapDelay pointer */     
  S->pTapDelay = pTapDelay;     
     
  /* Assign MaxDelay */     
  S->maxDelay = maxDelay;     
     
  /* reset the stateIndex to 0 */     
  S->stateIndex = 0u;     
     
  /* Clear state buffer and size is always maxDelay + blockSize */     
  memset(pState, 0, (maxDelay + blockSize) * sizeof(q31_t));     
     
  /* Assign state pointer */     
  S->pState = pState;     
     
}     
     
/**      
 * @} end of FIR_Sparse group      
 */     
