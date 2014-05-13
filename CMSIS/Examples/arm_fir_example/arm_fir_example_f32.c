/* ----------------------------------------------------------------------     
* Copyright (C) 2011 ARM Limited. All rights reserved. 
*     
* $Date:        15. December 2011   
* $Revision: 	V2.0.0  
*     
* Project:      Cortex-R4 DSP Library 
 * Title:	        arm_fir_example_f32.c		  
 *  
 * Description:	Example code demonstrating how an FIR filter can be used
 *               as a low pass filter.
 * 
* Target Processor:          Cortex-R4
*
* Version 2.0.0 2011/12/15
*     Final release. 
* 
* ---------------------------------------------------------------------------- */ 
 
/** 
 * @ingroup groupExamples 
 */ 
 
/**    
 * @defgroup FIRLPF FIR Lowpass Filter Example
 * 
 * \par Description: 
 * \par
 * Removes high frequency signal components from the input using an FIR lowpass filter.
 * The example demonstrates how to configure an FIR filter and then pass data through
 * it in a block-by-block fashion.
 * \image html FIRLPF_signalflow.gif 
 * 
 * \par Algorithm:
 * \par
 * The input signal is a sum of two sine waves:  1 kHz and 15 kHz.
 * This is processed by an FIR lowpass filter with cutoff frequency 6 kHz.
 * The lowpass filter eliminates the 15 kHz signal leaving only the 1 kHz sine wave at the output.
 * \par
 * The lowpass filter was designed using MATLAB with a sample rate of 48 kHz and 
 * a length of 29 points.
 * The MATLAB code to generate the filter coefficients is shown below:
 * <pre>
 *     h = fir1(28, 6/24);
 * </pre>
 * The first argument is the "order" of the filter and is always one less than the desired length.
 * The second argument is the normalized cutoff frequency.  This is in the range 0 (DC) to 1.0 (Nyquist).
 * A 6 kHz cutoff with a Nyquist frequency of 24 kHz lies at a normalized frequency of 6/24 = 0.25.
 * The FIR filter function requires the coefficients to be in time reversed order.
 * <pre>
 *     fliplr(h)
 * </pre>
 * The resulting filter coefficients and are shown below.  
 * Note that the filter is symmetric (a property of linear phase FIR filters)
 * and the point of symmetry is sample 14.  Thus the filter will have a delay of
 * 14 samples for all frequencies.
 * \par
 * \image html FIRLPF_coeffs.gif 
 * \par
 * The frequency response of the filter is shown next.  
 * The passband gain of the filter is 1.0 and it reaches 0.5 at the cutoff frequency 6 kHz.
 * \par
 * \image html FIRLPF_response.gif 
 * \par
 * The input signal is shown below.
 * The left hand side shows the signal in the time domain while the right hand side is a frequency domain representation.
 * The two sine wave components can be clearly seen.
 * \par
 * \image html FIRLPF_input.gif 
 * \par
 * The output of the filter is shown below.  The 15 kHz component has been eliminated.
 * \par
 * \image html FIRLPF_output.gif 
 *
 * \par Variables Description:
 * \par
 * \li \c testInput_f32_1kHz_15kHz points to the input data
 * \li \c refOutput points to the reference output data
 * \li \c testOutput points to the test output data
 * \li \c firStateF32 points to state buffer
 * \li \c firCoeffs32 points to coefficient buffer
 * \li \c blockSize number of samples processed at a time
 * \li \c numBlocks number of frames 
 *
 * \par Cortex-R DSP Software Library Functions Used:
 * \par
 * - arm_fir_init_f32()
 * - arm_fir_f32() 
 * 
 * <b> Refer  </b> 
 * \link arm_fir_example_f32.c \endlink
 * 
 */ 
 
 
/** \example arm_fir_example_f32.c 
 */  
 
/* ---------------------------------------------------------------------- 
** Include Files  
** ------------------------------------------------------------------- */ 

#include "arm_math.h" 
#include "math_helper.h" 
 
/* ---------------------------------------------------------------------- 
** Macro Defines  
** ------------------------------------------------------------------- */ 

#define TEST_LENGTH_SAMPLES 320 
#define SNR_THRESHOLD_F32	140.0f 
#define BLOCK_SIZE			32 
#define NUM_TAPS			29 
 
/* ------------------------------------------------------------------- 
 * The input signal and reference output (computed with MATLAB)
 * are defined externally in arm_fir_lpf_data.c.
 * ------------------------------------------------------------------- */ 

extern float32_t testInput_f32_1kHz_15kHz[TEST_LENGTH_SAMPLES]; 
extern float32_t refOutput[TEST_LENGTH_SAMPLES]; 

/* ------------------------------------------------------------------- 
 * External definition for Performance Monitor
 * ------------------------------------------------------------------- */ 

extern unsigned int Enable_Performance_Monitor(int);
extern unsigned int Performance_Monitor_Start(int);
extern unsigned int Performance_Monitor_Stop(int);
extern unsigned int Performance_Monitor_Read_Counter0(int);
extern unsigned int Performance_Monitor_Read_Counter1(int);
extern unsigned int Performance_Monitor_Read_Counter2(int);
extern unsigned int Performance_Monitor_Read_CycleCount(int); 
/* ------------------------------------------------------------------- 
 * Declare Test output buffer 
 * ------------------------------------------------------------------- */ 

static float32_t testOutput[TEST_LENGTH_SAMPLES]; 
 
/* ------------------------------------------------------------------- 
 * Declare State buffer of size (numTaps + blockSize - 1) 
 * ------------------------------------------------------------------- */ 

static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1]; 
 
/* ---------------------------------------------------------------------- 
** FIR Coefficients buffer generated using fir1() MATLAB function. 
** fir1(28, 6/24)
** ------------------------------------------------------------------- */ 
 
const float32_t firCoeffs32[NUM_TAPS] = { 
-0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f, 
-0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f, 
+0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f, 
+0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f 
}; 
 
/* ------------------------------------------------------------------ 
 * Global variables for FIR LPF Example 
 * ------------------------------------------------------------------- */ 

uint32_t blockSize = BLOCK_SIZE; 
uint32_t numBlocks = TEST_LENGTH_SAMPLES/BLOCK_SIZE; 
 
float32_t  snr; 
/* ------------------------------------------------------------------ 
 * Global variables for Performance Monitor 
 * ------------------------------------------------------------------- */ 
unsigned int PMU_counter0_result[10];
unsigned int PMU_counter1_result[10];
unsigned int PMU_counter2_result[10];
unsigned int PMU_cycle_count[10];

/* ---------------------------------------------------------------------- 
 * FIR LPF Example 
 * ------------------------------------------------------------------- */ 
 
int32_t main(void) 
{ 
  uint32_t i; 
  arm_fir_instance_f32 S; 
  arm_status status; 
  float32_t  *inputF32, *outputF32; 
 
  /* Initialize input and output buffer pointers */ 
  inputF32 = &testInput_f32_1kHz_15kHz[0];	 
  outputF32 = &testOutput[0]; 

  /* Call FIR init function to initialize the instance structure. */
  arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], blockSize); 
 
  /* ---------------------------------------------------------------------- 
  ** Call the FIR process function for every blockSize samples  
  ** ------------------------------------------------------------------- */ 

  for(i=0; i < numBlocks; i++)  
    {	 
      Enable_Performance_Monitor(0);  								// Init PMU
      Performance_Monitor_Start(0);								// start PMU counters
      arm_fir_f32(&S, inputF32 + (i * blockSize), outputF32 + (i * blockSize), blockSize);  
      Performance_Monitor_Stop(0);     								// stop PMU counters
      PMU_counter0_result[i] = Performance_Monitor_Read_Counter0(0);
      PMU_counter1_result[i] = Performance_Monitor_Read_Counter1(0);
      PMU_counter2_result[i] = Performance_Monitor_Read_Counter2(0);
      PMU_cycle_count[i]     = Performance_Monitor_Read_CycleCount(0);
    } 
 
  /* ---------------------------------------------------------------------- 
  ** Compare the generated output against the reference output computed
  ** in MATLAB.
  ** ------------------------------------------------------------------- */ 

  snr = arm_snr_f32(&refOutput[0], &testOutput[0], TEST_LENGTH_SAMPLES); 
 
  if (snr < SNR_THRESHOLD_F32) 
    { 
      status = ARM_MATH_TEST_FAILURE; 
    } 
  else
    {
      status = ARM_MATH_SUCCESS; 
    }
	 
  /* ---------------------------------------------------------------------- 
  ** Loop here if the signal does not match the reference output.
  ** ------------------------------------------------------------------- */ 
	 
  if( status != ARM_MATH_SUCCESS) 
    { 
      while(1); 
    } 
} 
 
/** \endlink */ 
 
 
 
