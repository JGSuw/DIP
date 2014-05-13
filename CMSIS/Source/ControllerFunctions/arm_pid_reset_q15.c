/* ----------------------------------------------------------------------      
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*      
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*      
* Project:      Cortex-R DSP Library 
* Title:	    arm_pid_reset_q15.c      
*      
* Description:	Q15 PID Control reset function     
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
 * @addtogroup PID      
 * @{      
 */     
     
/**      
* @brief  Reset function for the Q15 PID Control.     
* @param[in] *S		Instance pointer of PID control data structure.     
* @return none.      
* \par Description:     
* The function resets the state buffer to zeros.      
*/     
void arm_pid_reset_q15(     
  arm_pid_instance_q15 * S)     
{     
  /* Reset state to zero, The size will be always 3 samples */     
  memset(S->state, 0, 3u * sizeof(q15_t));      
}     
     
/**      
 * @} end of PID group      
 */     
