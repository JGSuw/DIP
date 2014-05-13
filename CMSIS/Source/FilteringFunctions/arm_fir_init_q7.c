/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_fir_init_q7.c      
*      
* Description:  Q7 FIR filter initialization function.      
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
* ------------------------------------------------------------------- */     
     
#include "arm_math.h"     
     
/**      
 * @ingroup groupFilters      
 */     
     
/**      
 * @addtogroup FIR      
 * @{      
 */     
/**      
 * @param[in,out] *S points to an instance of the Q7 FIR filter structure.      
 * @param[in] 	  numTaps  Number of filter coefficients in the filter.      
 * @param[in] 	  *pCoeffs points to the filter coefficients buffer.      
 * @param[in]     *pState points to the state buffer.      
 * @param[in]     blockSize number of samples that are processed per call.      
 * @return     	  none      
 *      
 * <b>Description:</b>      
 * \par      
 * <code>pCoeffs</code> points to the array of filter coefficients stored in time reversed order:      
 * <pre>      
 *    {b[numTaps-1], b[numTaps-2], b[N-2], ..., b[1], b[0]}      
 * </pre>      
 * \par      
 * <code>pState</code> points to the array of state variables.      
 * <code>pState</code> is of length <code>numTaps+blockSize</code> samples, where <code>blockSize</code> is the number of input samples processed by each call to <code>arm_fir_q7()</code>.      
 */     
     
void arm_fir_init_q7(     
  arm_fir_instance_q7 * S,     
  uint16_t numTaps,     
  q7_t * pCoeffs,     
  q7_t * pState,     
  uint32_t blockSize)     
{     
     
  /* Assign filter taps */     
  S->numTaps = numTaps;     
     
  /* Assign coefficient pointer */     
  S->pCoeffs = pCoeffs;     
     
  /* Clear the state buffer.  The size is always (blockSize + numTaps) */     
  memset(pState, 0, (numTaps + (blockSize)) * sizeof(q7_t));     
     
  /* Assign state pointer */     
  S->pState = pState;     
     
}     
     
/**      
 * @} end of FIR group      
 */     
