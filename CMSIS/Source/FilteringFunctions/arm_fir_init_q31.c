/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_fir_init_q31.c      
*      
* Description:	Q31 FIR filter initialization function.      
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
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup FIR      
 * @{      
 */     
     
/**      
 * @details      
 *      
 * @param[in,out] *S points to an instance of the Q31 FIR filter structure.      
 * @param[in] 	  numTaps  Number of filter coefficients in the filter.      
 * @param[in] 	  *pCoeffs points to the filter coefficients buffer.      
 * @param[in] 	  *pState points to the state buffer.      
 * @param[in] 	  blockSize number of samples that are processed per call.      
 * @return        none.      
 *      
 * <b>Description:</b>      
 * \par      
 * <code>pCoeffs</code> points to the array of filter coefficients stored in time reversed order:      
 * <pre>      
 *    {b[numTaps-1], b[numTaps-2], b[N-2], ..., b[1], b[0]}      
 * </pre>      
 * \par      
 * <code>pState</code> points to the array of state variables.      
 * <code>pState</code> is of length <code>numTaps+blockSize-1</code> samples, where <code>blockSize</code> is the number of input samples processed by each call to <code>arm_fir_q31()</code>.      
 */     
     
void arm_fir_init_q31(     
  arm_fir_instance_q31 * S,     
  uint16_t numTaps,     
  q31_t * pCoeffs,     
  q31_t * pState,     
  uint32_t blockSize)     
{     
  /* Assign filter taps */     
  S->numTaps = numTaps;     
     
  /* Assign coefficient pointer */     
  S->pCoeffs = pCoeffs;     
     
  /* Clear state buffer and state array size is (blockSize + numTaps - 1) */     
  memset(pState, 0, (blockSize + ((uint32_t) numTaps - 1u)) * sizeof(q31_t));     
     
  /* Assign state pointer */     
  S->pState = pState;     
     
}     
     
/**      
 * @} end of FIR group      
 */     
