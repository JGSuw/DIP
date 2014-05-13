/*-----------------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:        arm_fir_lattice_init_q31.c      
*      
* Description:  Q31 FIR lattice filter initialization function.      
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
 * @addtogroup FIR_Lattice      
 * @{      
 */     
     
  /**      
   * @brief Initialization function for the Q31 FIR lattice filter.      
   * @param[in] *S points to an instance of the Q31 FIR lattice structure.      
   * @param[in] numStages  number of filter stages.      
   * @param[in] *pCoeffs points to the coefficient buffer.  The array is of length numStages.      
   * @param[in] *pState points to the state buffer.   The array is of length numStages.      
   * @return none.      
   */     
     
void arm_fir_lattice_init_q31(     
  arm_fir_lattice_instance_q31 * S,     
  uint16_t numStages,     
  q31_t * pCoeffs,     
  q31_t * pState)     
{     
  /* Assign filter taps */     
  S->numStages = numStages;     
     
  /* Assign coefficient pointer */     
  S->pCoeffs = pCoeffs;     
     
  /* Clear state buffer and size is always numStages */     
  memset(pState, 0, (numStages) * sizeof(q31_t));     
     
  /* Assign state pointer */     
  S->pState = pState;     
     
}     
     
/**      
 * @} end of FIR_Lattice group      
 */     
