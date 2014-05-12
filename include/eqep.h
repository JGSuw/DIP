/** @file eqep.h
*   @brief EQEP Driver Header File
*   @date 15.Aug.2012
*   @version 03.02.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the EQEP driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#ifndef __QEP_H__
#define __QEP_H__

// **************************************************************************
// the includes

#include "sys_common.h"

//!
//! \defgroup EQEP

//!
//! \ingroup EQEP
//@{

#ifdef __cplusplus
extern "C" {
#endif

// **************************************************************************
// the defines

#define QEP_BASE_ADDR                        (0x00006B00) //!<base address of QEP

// QDECCTL Register
#define QEP_QDECCTL_QSRC					 (3  << 14)		//!<position counter source selection
#define QEP_QDECCTL_SOEN					 (1  << 13)		//!<sync output enable
#define QEP_QDECCTL_SPSEL					 (1  << 12)		//!<sync output pin selection
#define QEP_QDECCTL_XCR						 (1  << 11)		//!<external clock rate
#define QEP_QDECCTL_SWAP					 (1  << 10)		//!<swap quadrature clock inputs
#define QEP_QDECCTL_IGATE					 (1  <<  9)		//!<index pulse gating option
#define QEP_QDECCTL_QAP						 (1  <<  8)		//!<QEPA input polarity
#define QEP_QDECCTL_QBP						 (1  <<  7)		//!<QEPB input polarity
#define QEP_QDECCTL_QIP						 (1  <<  6)		//!<QEPI input polarity
#define QEP_QDECCTL_QSP						 (1  <<  5)		//!<QEPS input polarity

// QEPCTL Register
#define QEP_QEPCTL_FREESOFT					 ( 3 << 14)		//!<emulation control bit
#define QEP_QEPCTL_PCRM						 ( 3 << 12)		//!<emulation control bit
#define QEP_QEPCTL_SEI						 ( 3 << 10)		//!<strobe event initialization of position counter
#define QEP_QEPCTL_IEI						 ( 3 <<  8)		//!<index event initialization of position counter
#define QEP_QEPCTL_SWI						 ( 1 <<  7)		//!<software initialization of position counter
#define QEP_QEPCTL_SEL						 ( 1 <<  6)		//!<strobe event latch of position counter
#define QEP_QEPCTL_IEL						 ( 3 <<  4)		//!<index event latch of position counter (software index marker)
#define QEP_QEPCTL_QPEN						 ( 1 <<  3)		//!<quad position counter enable/software reset
#define QEP_QEPCTL_QCLM						 ( 1 <<  2)		//!<QEP capture latch mode
#define QEP_QEPCTL_UTE						 ( 1 <<  1)		//!<QEP unit timer enable
#define QEP_QEPCTL_WDE						 ( 1 <<  0)		//!<watchdog timer enable

// QPOSCTL Register
#define QEP_QPOSCTL_PCSHDW					 (   1 << 15)	//!<position compare shadow enable
#define QEP_QPOSCTL_PCLOAD					 (   1 << 14)	//!<position compare shadow load mode
#define QEP_QPOSCTL_PCPOL					 (   1 << 13)	//!<load when QPOSCNT = QPOSCMP
#define QEP_QPOSCTL_PCE						 (   1 << 12)	//!<position compare enable/disable
#define QEP_QPOSCTL_PCSPW					 (4095 <<  0)	//!<selection position compare sync output pulse width

// QCAPCTL Register
#define QEP_QCAPCTL_CEN						 (   1 << 15)	//!<enable QEP capture
#define QEP_QCAPCTL_CCPS					 (   7 <<  4)	//!<qep capture timer clock prescaler
#define QEP_QCAPCTL_UPPS					 (  15 <<  0)	//!<unit position event prescaler

// QEINT Register
#define QEP_QEINT_UTO						 (   1 << 11)	//!<unit timeout interrupt enable
#define QEP_QEINT_IEL						 (   1 << 10)	//!<index event latch interrupt enable
#define QEP_QEINT_SEL						 (   1 <<  9)	//!<strobe event latch	interrupt enable
#define QEP_QEINT_PCM						 (   1 <<  8)	//!<position compare match interrupt enable	
#define QEP_QEINT_PCR						 (   1 <<  7)	//!<position compare ready interrupt enable 
#define QEP_QEINT_PCO						 (   1 <<  6)	//!<position counter overflow interrupt enable
#define QEP_QEINT_PCU						 (   1 <<  5)	//!<position counter underflow interrupt enable
#define QEP_QEINT_WTO						 (   1 <<  4)	//!<watchdog time out interrupt enable
#define QEP_QEINT_QDC						 (   1 <<  3)	//!<quadrature direction change interrupt enable
#define QEP_QEINT_QPE						 (   1 <<  2)	//!<quadrature phase error interrupt enable
#define QEP_QEINT_PCE						 (   1 <<  1)	//!<position counter error interrupt enable
																
// QFLG Register
#define QEP_QFLG_UTO						 (   1 << 11)	//!<unit timeout interrupt flag
#define QEP_QFLG_IEL						 (   1 << 10)	//!<index event latch interrupt flag
#define QEP_QFLG_SEL						 (   1 <<  9)	//!<strobe event latch	interrupt flag
#define QEP_QFLG_PCM						 (   1 <<  8)	//!<position compare match interrupt flag
#define QEP_QFLG_PCR						 (   1 <<  7)	//!<position compare ready interrupt flag
#define QEP_QFLG_PCO						 (   1 <<  6)	//!<position counter overflow interrupt flag
#define QEP_QFLG_PCU						 (   1 <<  5)	//!<position counter underflow interrupt flag
#define QEP_QFLG_WTO						 (   1 <<  4)	//!<watchdog time out interrupt flag
#define QEP_QFLG_QDC						 (   1 <<  3)	//!<quadrature direction change interrupt flag
#define QEP_QFLG_QPE						 (   1 <<  2)	//!<quadrature phase error interrupt flag
#define QEP_QFLG_PCE						 (   1 <<  1)	//!<position counter error interrupt flag

// QCLR Register
#define QEP_QCLR_UTO						 (   1 << 11)	//!<clear unit timeout interrupt flag
#define QEP_QCLR_IEL						 (   1 << 10)	//!<clear index event latch interrupt flag
#define QEP_QCLR_SEL						 (   1 <<  9)	//!<clear strobe event latch interrupt flag
#define QEP_QCLR_PCM						 (   1 <<  8)	//!<clear position compare match interrupt flag
#define QEP_QCLR_PCR						 (   1 <<  7)	//!<clear position compare ready interrupt flag
#define QEP_QCLR_PCO						 (   1 <<  6)	//!<clear position counter overflow interrupt flag
#define QEP_QCLR_PCU						 (   1 <<  5)	//!<clear position counter underflow interrupt flag
#define QEP_QCLR_WTO						 (   1 <<  4)	//!<clear watchdog time out interrupt flag
#define QEP_QCLR_QDC						 (   1 <<  3)	//!<clear quadrature direction change interrupt flag
#define QEP_QCLR_QPE						 (   1 <<  2)	//!<clear quadrature phase error interrupt flag
#define QEP_QCLR_PCE						 (   1 <<  1)	//!<clear position counter error interrupt flag

// QFRC Register
#define QEP_QFRC_UTO						 (   1 << 11)	//!<force unit timeout interrupt 
#define QEP_QFRC_IEL						 (   1 << 10)	//!<force index event latch interrupt 
#define QEP_QFRC_SEL						 (   1 <<  9)	//!<force strobe event latch interrupt 
#define QEP_QFRC_PCM						 (   1 <<  8)	//!<force position compare match interrupt 
#define QEP_QFRC_PCR						 (   1 <<  7)	//!<force position compare ready interrupt 
#define QEP_QFRC_PCO						 (   1 <<  6)	//!<force position counter overflow interrupt 
#define QEP_QFRC_PCU						 (   1 <<  5)	//!<force position counter underflow interrupt 
#define QEP_QFRC_WTO						 (   1 <<  4)	//!<force watchdog time out interrupt 
#define QEP_QFRC_QDC						 (   1 <<  3)	//!<force quadrature direction change interrupt 
#define QEP_QFRC_QPE						 (   1 <<  2)	//!<force quadrature phase error interrupt 
#define QEP_QFRC_PCE						 (   1 <<  1)	//!<force position counter error interrupt 

// QEPSTS Register
#define QEP_QEPSTS_UPEVNT					(   1 << 7)		//!<unit position event flag
#define QEP_QEPSTS_FDF						(   1 << 6)		//!<direction on the first index marker
#define QEP_QEPSTS_QDF						(   1 << 5)		//!<quadrature direction flag
#define QEP_QEPSTS_QDLF						(   1 << 4)		//!<direction latch flag
#define QEP_QEPSTS_COEF						(   1 << 3)		//!<capture overflow error flag
#define QEP_QEPSTS_CDEF						(   1 << 2)		//!<capture direction error flag
#define QEP_QEPSTS_FIMF						(   1 << 1)		//!<first index marker flag
#define QEP_QEPSTS_PCEF						(   1 << 0)		//!<position counter error flag

// PC mode 
#define QEP_QUADRATURE_COUNT                 0x00
#define QEP_DIRECTION_COUNT                  0x01
#define QEP_UP_COUNT                         0x02
#define QEP_DOWN_COUNT                       0x03

// External Clock Rate 
#define QEP_RESOLUTION_2x                    0x00
#define QEP_RESOLUTION_1x                    0x01

// Direction
#define QEP_CLOCKWISE                        0x01
#define QEP_COUNTERCLOCKWISE                 0x01

// Edge 
#define QEP_RISING_EDGE                      0x00
#define QEP_FALLING_EDGE                     0x01
#define QEP_DIRECTON_DEPENDENT               0x01

// Index event latch of position counter 
#define QEP_LATCH_RISING_EDGE                0x01
#define QEP_LATCH_FALLING_EDGE               0x02
#define QEP_LATCH_SW_INDEX_MARKER            0x03

// Position counter reset mode
#define QEP_INDEX_EVENT                      0x00
#define QEP_MAX_POSITION                     0x01
#define QEP_FIRST_INDEX_EVENT                0x02
#define QEP_UNITTIME_EVENT                   0x03

// eQEP capture timer clock prescaler and Unit position event prescaler
#define QEP_PS_1                             0x00
#define QEP_PS_2                             0x01
#define QEP_PS_4                             0x02
#define QEP_PS_8                             0x03
#define QEP_PS_16                            0x04
#define QEP_PS_32                            0x05
#define QEP_PS_64                            0x06
#define QEP_PS_128                           0x07
#define QEP_PS_256                           0x08
#define QEP_PS_512                           0x09
#define QEP_PS_1024                          0x0A
#define QEP_PS_2048                          0x0B

// eQEP capture latch mode
#define QEP_ON_POSITION_COUNTER_READ         0x00
#define QEP_ON_UNIT_TIMOUT_EVENT             0x01

// Sync output pin selection
#define QEP_INDEX_PIN                        0x00
#define QEP_STROBE_PIN                       0x01

// Position-compare shadow load mode
#define QEP_QPOSCNT_EQ_0                     0x00
#define QEP_QPOSCNT_EQ_QPSCMP                0x01

// Polarity of sync output
#define QEP_ACTIVE_HIGH                      0x00
#define QEP_ACTIVE_LOW                       0x01

// **************************************************************************
// the typedefs

//! \brief QEP counting mode
//!
typedef enum
{
	QEP_Qsrc_Quad_Count_Mode=(0 << 14),						//!<quadrature count mode
	QEP_Qsrc_Dir_Count_Mode=(1 << 14),						//!<direction count mode
	QEP_Qsrc_Up_Count_Mode=(2 << 14),						//!<up count mode for frequency measurement (QCLK=XCLK, QDIR=1)
	QEP_Qsrc_Down_Count_Mode=(3 << 14)						//!<down count mode for frequency measurement (QCLK=XCLK, QDIR=0)
} QEP_Qsrc_e;

//! \brief Sync output pin selection
//!
typedef enum
{	
	QEP_Spsel_Index_Pin_Sync_Output=(0 << 12),				//!<index pin for sync output
	QEP_Spsel_Strobe_Pin_Sync_Output=(1 << 12)				//!<strobe pin for sync output
} QEP_Spsel_e;

//! \brief External clock rate
//!
typedef enum
{
	QEP_Xcr_2x_Res=(0 << 11),								//!<2x resolution: count the rising/falling edge
	QEP_Xcr_1x_Res=(1 << 11)								//!<1x resolution: count the rising edge only
} QEP_Xcr_e;

//! \brief Swap A/B channels
//!
typedef enum
{
	QEP_Swap_Not_Swapped=(0 << 10),							//!<quad inputs not swapped
	QEP_Swap_Swapped=(1 << 10)								//!<quad inputs swapped
} QEP_Swap_e;

//! \brief Index gating
//!
typedef enum
{
	QEP_Igate_Disable=(0 << 9),								//!<disable gating of index pulse
	QEP_Igate_Enable=(1 << 9)								//!<enable gating of index pulse
} QEP_Igate_e;

//! \brief Channel A polarity
//!
typedef enum
{
	QEP_Qap_No_Effect=(0 << 8),								//!<no effect
	QEP_Qap_Inverted=(1 << 8)								//!<negates QEPA input
} QEP_Qap_e;

//! \brief Channel B polarity
//!
typedef enum
{
	QEP_Qbp_No_Effect=(0 << 7),								//!<no effect
	QEP_Qbp_Inverted=(1 << 7)								//!<negates QEPB input
} QEP_Qbp_e;

//! \brief Index polarity
//
typedef enum
{
	QEP_Qip_No_Effect=(0 << 6),								//!<no effect
	QEP_Qip_Inverted=(1 << 6)								//!<negates QEPI input
} QEP_Qip_e;

//! \brief Channel S polarity
//!
typedef enum
{
	QEP_Qsp_No_Effect=(0 << 5),								//!<no effect
	QEP_Qsp_Inverted=(1 << 5)								//!<negates QEPS input
} QEP_Qsp_e;

//! \brief Emulation control bits
//!
typedef enum
{
	QEPCTL_Freesoft_Immediate_Halt=(0 << 14),				//!<position, watchdog, unit timer, capture timer stops immediately
	QEPCTL_Freesoft_Rollover_Halt=(1 << 14),				//!<position, watchdog, unit timer continues until rollover, capture counts until next unit period event
	QEPCTL_Freesoft_Unaffected_Halt=(2 << 14)				//!<position, watchdog, unit timer, capture timer unaffected by emu suspend
} QEPCTL_Freesoft_e;

//! \brief Position counter reset mode
//!
typedef enum
{
	QEPCTL_Pcrm_Index_Reset=(0 << 12),						//!<position counter reset on index event
	QEPCTL_Pcrm_Max_Reset=(1 << 12),						//!<position counter reset on max position
	QEPCTL_Pcrm_First_Index_Reset=(2 << 12),				//!<position counter reset on first index event
	QEPCTL_Pcrm_Unit_Time_Reset=(3 << 12)					//!<position counter reset on unit time event
} QEPCTL_Pcrm_e;

//! \brief Strobe event initialization of position counter
//!
typedef enum
{
	QEPCTL_Sei_Nothing=(0 << 10),							//!<does nothing
	QEPCTL_Sei_Rising_Edge_Init=(2 << 10),					//!<initializes on rising edge of QEPS signal
	QEPCTL_Sei_Rising_Falling_Edge_Init=(3 << 10)			//!<initializes on rising/falling edge of QEPS signal
} QEPCTL_Sei_e;

//! \brief Index event initialization of position counter
//!
typedef enum
{
	QEPCTL_Iei_Nothing=(0 << 8),							//!<does nothing
	QEPCTL_Iei_Rising_Edge_Init=(2 << 8),					//!<initializes on rising edge of QEPI signal
	QEPCTL_Iei_Rising_Falling_Edge_Init=(3 << 8)			//!<initializes on falling edge of QEPS signal
} QEPCTL_Iei_e;

//! \brief Software initialization of position counter
//!
typedef enum
{
	QEPCTL_Swi_Nothing=(0 << 7),							//!<does nothing
	QEPCTL_Swi_Auto_Init_Counter=(1 << 7)					//!<init position counter (QPOSCNT=QPOSINIT)
} QEPCTL_Swi_e;

//! \brief Strobe event latch of position counter
//!
typedef enum
{
	QEPCTL_Sel_Rising_Edge=(0 << 6),						//!<Position counter latched on rising edge of QEPS strobe (QPOSSLAT = POSCCNT)
	QEPCTL_Sel_Rising_Falling_Edge=(1 << 6)					//!<Clockwise: position counter latched on rising edge, counter clockwise: latched on falling edge
} QEPCTL_Sel_e;
	
//! \brief Index event latch of position counter (software index marker)
//!
typedef enum
{
	QEPCTL_Iel_Rising_Edge=(1 << 4),						//!<latches position counter on rising edge of index signal
	QEPCTL_Iel_Falling_Edge=(2 << 4),						//!<ditto on falling edge of index signal
	QEPCTL_Iel_Software_Index_Marker=(3 << 4)				//!<software index marker.  See data sheet.
} QEPCTL_Iel_e;

//! \brief QEP capture latch mode
//!
typedef enum
{
	QEPCTL_Qclm_Latch_on_CPU_Read=(0 << 2),					//!<latch on position counter read by cpu
	QEPCTL_Qclm_Latch_on_Unit_Timeout=(1 << 2)				//!<latch on unit time out
} QEPCTL_Qclm_e;

//! \brief Position compare shadow enable
//!
typedef enum
{
	QPOSCTL_Pcshdw_Load_Immediate=(0 << 15),				//!<shadow disabled, load immediate
	QPOSCTL_Pcshdw_Shadow_Enabled=(1 << 15)					//!<shadow enabled
} QPOSCTL_Pcshdw_e;

//! \brief Position compare shadow load mode
//!
typedef enum
{
	QPOSCTL_Pcload_Load_Posn_Count_Zero=(0 << 14),			//!<load on qposcnt = 0
	QPOSCTL_Pcload_Load_Posn_Count_Equal_Compare=(1 << 14)	//!<load when qposcnt = qposcmp
} QPOSCTL_Pcload_e;

//! \brief Polarity of sync output
//!
typedef enum
{
	QPOSCTL_Pcpol_Active_High=(0 << 13),					//!<active high pulse output
	QPOSCTL_Pcpol_Active_Low=(1 << 13)						//!<active low pulse output
} QPOSCTL_Pcpol_e;

//! \brief QEP capture timer clock prescaler
//!
typedef enum
{
	QCAPCTL_Ccps_Capture_Div_1=(0 << 4),					//!<capclk = sysclkout/1
	QCAPCTL_Ccps_Capture_Div_2=(1 << 4),					//!<capclk = sysclkout/2
	QCAPCTL_Ccps_Capture_Div_4=(2 << 4),					//!<capclk = sysclkout/4
	QCAPCTL_Ccps_Capture_Div_8=(3 << 4),					//!<capclk = sysclkout/8
	QCAPCTL_Ccps_Capture_Div_16=(4 << 4),					//!<capclk = sysclkout/16
	QCAPCTL_Ccps_Capture_Div_32=(5 << 4),					//!<capclk = sysclkout/32
	QCAPCTL_Ccps_Capture_Div_64=(6 << 4),					//!<capclk = sysclkout/64
	QCAPCTL_Ccps_Capture_Div_128=(7 << 4)					//!<capclk = sysclkout/128
} QCAPCTL_Ccps_e;

//! \brief Unit position event prescaler
//!
typedef enum
{
	QCAPCTL_Upps_Div_1_Prescale=(0 << 0),					//!<upevnt = qclk/1
	QCAPCTL_Upps_Div_2_Prescale=(1 << 0),					//!<upevnt = qclk/2
	QCAPCTL_Upps_Div_4_Prescale=(2 << 0),					//!<upevnt = qclk/4
	QCAPCTL_Upps_Div_8_Prescale=(3 << 0),					//!<upevnt = qclk/8
	QCAPCTL_Upps_Div_16_Prescale=(4 << 0),					//!<upevnt = qclk/16
	QCAPCTL_Upps_Div_32_Prescale=(5 << 0),					//!<upevnt = qclk/32
	QCAPCTL_Upps_Div_64_Prescale=(6 << 0),					//!<upevnt = qclk/64
	QCAPCTL_Upps_Div_128_Prescale=(7 << 0),					//!<upevnt = qclk/128
	QCAPCTL_Upps_Div_256_Prescale=(8 << 0),					//!<upevnt = qclk/256
	QCAPCTL_Upps_Div_512_Prescale=(9 << 0),					//!<upevnt = qclk/512
	QCAPCTL_Upps_Div_1024_Prescale=(10 << 0),				//!<upevnt = qclk/1024
	QCAPCTL_Upps_Div_2048_Prescale=(11 << 0)				//!<upevnt = qclk/2048
} QCAPCTL_Upps_e;

//! \brief QEP interrupt enable flags
typedef enum
{
	QEINT_Uto=(1 << 11),									//!<unit time out interrupt enable
	QEINT_Iel=(1 << 10),									//!<index event latch interrupt enable
	QEINT_Sel=(1 << 9),										//!<strobe event latch interrupt enable
	QEINT_Pcm=(1 << 8),										//!<position compare match interrupt enable
	QEINT_Pcr=(1 << 7),										//!<position compare ready interrupt enable 
	QEINT_Pco=(1 << 6),										//!<position compare overflow interrupt enable
	QEINT_Pcu=(1 << 5),										//!<position compare underflow interrupt enable
	QEINT_Wto=(1 << 4),										//!<position compare watchdog time out interrupt enable
	QEINT_Qdc=(1 << 3),										//!<quadrature direction change interrupt enable
	QEINT_Qpe=(1 << 2),										//!<quadrature phase error interrupt enable
	QEINT_Pce=(1 << 1)										//!<position counter interrupt enable
} QEINT_e;

//! \brief Defines the QEP object
//!

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1)) 

typedef struct _eqepBASE_t_
{
  uint32_t      QPOSCNT;       //!< 0x0000 eQEP Position Counter
  uint32_t      QPOSINIT;      //!< 0x0004 eQEP Initialization Position Count
  uint32_t      QPOSMAX;       //!< 0x0008 eQEP Maximum Position Count
  uint32_t      QPOSCMP;       //!< 0x000C eQEP Position Compare
  uint32_t      QPOSILAT;      //!< 0x0010 eQEP Index Position Latch
  uint32_t      QPOSSLAT;      //!< 0x0014 eQEP Strobe Position Latch
  uint32_t      QPOSLAT;       //!< 0x0018 eQEP Position Latch
  uint32_t      QUTMR;         //!< 0x001C eQEP Unit Timer
  uint32_t      QUPRD;         //!< 0x0020 eQEP Unit Period
  uint16_t		QWDTMR;		   //!< 0x0024 eQEP Watchdog Timer
  uint16_t		QWDPRD;		   //!< 0x0026 eQEP Watchdog Period
  uint16_t		QDECCTL;	   //!< 0x0028 eQEP Decoder Control
  uint16_t		QEPCTL;		   //!< 0x002A eQEP Control
  uint16_t		QCAPCTL;	   //!< 0x002C eQEP Capture Control
  uint16_t		QPOSCTL;	   //!< 0x002E eQEP Position Compare Control
  uint16_t		QEINT;		   //!< 0x0030 eQEP Interrupt Enable Register
  uint16_t		QFLG;		   //!< 0x0032 eQEP Interrupt Flag Register
  uint16_t		QCLR;		   //!< 0x0034 eQEP Interrupt Clear Register
  uint16_t		QFRC;		   //!< 0x0036 eQEP Interrupt Force Register
  uint16_t		QEPSTS;		   //!< 0x0038 eQEP Status Register
  uint16_t		QCTMR;		   //!< 0x003A eQEP Capture Timer
  uint16_t		QCPRD;		   //!< 0x003C eQEP Capture Period
  uint16_t		QCTMRLAT;	   //!< 0x003E eQEP Capture Timer Latch
  uint16_t		QCPRDLAT;	   //!< 0x0040 eQEP Capture Period Latch
  uint16_t		rsvd_1;	       //!< 0x0042 Reserved
} eqepBASE_t;

#else

typedef struct _eqepBASE_t_
{
  uint32_t      QPOSCNT;       //!< 0x0000 eQEP Position Counter
  uint32_t      QPOSINIT;      //!< 0x0004 eQEP Initialization Position Count
  uint32_t      QPOSMAX;       //!< 0x0008 eQEP Maximum Position Count
  uint32_t      QPOSCMP;       //!< 0x000C eQEP Position Compare
  uint32_t      QPOSILAT;      //!< 0x0010 eQEP Index Position Latch
  uint32_t      QPOSSLAT;      //!< 0x0014 eQEP Strobe Position Latch
  uint32_t      QPOSLAT;       //!< 0x0018 eQEP Position Latch
  uint32_t      QUTMR;         //!< 0x001C eQEP Unit Timer
  uint32_t      QUPRD;         //!< 0x0020 eQEP Unit Period
  uint16_t		QWDPRD;		   //!< 0x0026 eQEP Watchdog Period
  uint16_t		QWDTMR;		   //!< 0x0024 eQEP Watchdog Timer
  uint16_t		QEPCTL;		   //!< 0x002A eQEP Control
  uint16_t		QDECCTL;	   //!< 0x0028 eQEP Decoder Control
  uint16_t		QPOSCTL;	   //!< 0x002E eQEP Position Compare Control
  uint16_t		QCAPCTL;	   //!< 0x002C eQEP Capture Control
  uint16_t		QFLG;		   //!< 0x0032 eQEP Interrupt Flag Register
  uint16_t		QEINT;		   //!< 0x0030 eQEP Interrupt Enable Register
  uint16_t		QFRC;		   //!< 0x0036 eQEP Interrupt Force Register
  uint16_t		QCLR;		   //!< 0x0034 eQEP Interrupt Clear Register
  uint16_t		QCTMR;		   //!< 0x003A eQEP Capture Timer
  uint16_t		QEPSTS;		   //!< 0x0038 eQEP Status Register
  uint16_t		QCTMRLAT;	   //!< 0x003E eQEP Capture Timer Latch
  uint16_t		QCPRD;		   //!< 0x003C eQEP Capture Period
  uint16_t		rsvd_1;	       //!< 0x0042 Reserved
  uint16_t		QCPRDLAT;	   //!< 0x0040 eQEP Capture Period Latch
} eqepBASE_t;

#endif

/** @def eqepREG1
*   @brief eQEP1 Register Frame Pointer
*
*   This pointer is used by the eQEP driver to access the eQEP1 registers.
*/
#define eqepREG1 ((eqepBASE_t *)0xFCF79900U)

/** @def eqepREG2
*   @brief eQEP2 Register Frame Pointer
*
*   This pointer is used by the eQEP driver to access the eQEP2 registers.
*/
#define eqepREG2 ((eqepBASE_t *)0xFCF79A00U)

// **************************************************************************
// the globals


// **************************************************************************
// the function prototypes

//! \brief Initialize QEP module
void QEPInit(void);

//! \brief Clears all QEP interrupt flags
//! \param[in] eqep		Handle to QEP object
void QEP_clear_all_interrupt_flags (eqepBASE_t *eqep);

//! \brief Clears a single interrupt flag
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEINT			Interrupt flag
void QEP_clear_interrupt_flag (eqepBASE_t *eqep, const QEINT_e QEINT);

//! \brief Clears the position counter
//! \param[in] eqep		Handle to QEP object
void QEP_clear_posn_counter (eqepBASE_t *eqep);

//! \brief Disables all interrupts
//! \param[in] eqep		Handle to QEP object
void QEP_disable_all_interrupts (eqepBASE_t *eqep);

//! \brief Disable capture
//! \param[in] eqep		Handle to QEP object
void QEP_disable_capture (eqepBASE_t *eqep);

//! \brief Disable gating of index pulse
//! \param[in] eqep		Handle to QEP object
void QEP_disable_gate_index (eqepBASE_t *eqep);

//! \brief Disable individual interrupt
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEINT			Individual interrupts
void QEP_disable_interrupt (eqepBASE_t *eqep, const QEINT_e QEINT);

//! \brief Disable position compare
//! \param[in] eqep		Handle to QEP object
void QEP_disable_posn_compare (eqepBASE_t *eqep);

//! \brief Disable position compare shadowing
//! \param[in] eqep		Handle to QEP object
void QEP_disable_posn_compare_shadow (eqepBASE_t *eqep);

//! \brief Disable output sync pulse
//! \param[in] eqep		Handle to QEP object
void QEP_disable_sync_out (eqepBASE_t *eqep);

//! \brief Disable unit timer
//! \param[in] eqep		Handle to QEP object
void QEP_disable_unit_timer (eqepBASE_t *eqep);

//! \brief Disable watchdog timer
//! \param[in] eqep		Handle to QEP object
void QEP_disable_watchdog (eqepBASE_t *eqep);

//! \brief Enable capture
//! \param[in] eqep		Handle to QEP object
void QEP_enable_capture (eqepBASE_t *eqep);

//! \brief Enable counter
//! \param[in] eqep		Handle to QEP object
void QEP_enable_counter (eqepBASE_t *eqep);

//! \brief Enable gating of index pulse
//! \param[in] eqep		Handle to QEP object
void QEP_enable_gate_index (eqepBASE_t *eqep);

//! \brief Enable individual interrupt
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEINT			Individual interrupts
void QEP_enable_interrupt (eqepBASE_t *eqep, const QEINT_e QEINT);

//! \brief Enable position compare
//! \param[in] eqep		Handle to QEP object
void QEP_enable_posn_compare (eqepBASE_t *eqep);

//! \brief Enable position compare shadowing
//! \param[in] eqep		Handle to QEP object
void QEP_enable_posn_compare_shadow (eqepBASE_t *eqep);

//! \brief Enable output sync pulse
//! \param[in] eqep		Handle to QEP object
void QEP_enable_sync_out (eqepBASE_t *eqep);

//! \brief Enable unit timer
//! \param[in] eqep		Handle to QEP object
void QEP_enable_unit_timer (eqepBASE_t *eqep);

//! \brief Enable watchdog timer
//! \param[in] eqep		Handle to QEP object
void QEP_enable_watchdog (eqepBASE_t *eqep);

//! \brief Manually force QEP interrupt
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEINT			Individual interrupt
void QEP_force_interrupt (eqepBASE_t *eqep, const QEINT_e QEINT);


//! \brief Reads capture period latch
//! \param[in] eqep		Handle to QEP object
//! \return						Counter value
uint16_t QEP_read_capture_period_latch (eqepBASE_t *eqep);

//! \brief Reads timer latch
//! \param[in] eqep		Handle to QEP object
//! \return						Timer value
uint16_t QEP_read_capture_timer_latch (eqepBASE_t *eqep);

//! \brief Reads interrupt flag value
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEINT			Which interrupt to interrogate
//! \return						Interrupt flag value
uint16_t QEP_read_interrupt_flag (eqepBASE_t *eqep, const QEINT_e QEINT);

//! \brief Reads position compare register
//! \param[in] eqep		Handle to QEP object
//! \return						Counter value
uint32_t QEP_read_posn_compare (eqepBASE_t *eqep);

//! \brief Reads position counter
//! \param[in] eqep		Handle to QEP object
//! \return						Counter value
uint32_t QEP_read_posn_count (eqepBASE_t *eqep);

//! \brief Reads position counter value index pulse latch register
//! \param[in] eqep		Handle to QEP object
//! \return						Counter value
uint32_t QEP_read_posn_index_latch (eqepBASE_t *eqep);

//! \brief Reads position counter value
//! \param[in] eqep		Handle to QEP object
//! \return						Counter value
uint32_t QEP_read_posn_latch (eqepBASE_t *eqep);

//! \brief Reads position strobe latch
//! \param[in] eqep		Handle to QEP object
//! \return						Counter value
uint32_t QEP_read_posn_strobe_latch (eqepBASE_t *eqep);

//! \brief Reads status register
//! \param[in] eqep		Handle to QEP object
//! \return						Status register value
uint16_t QEP_read_status (eqepBASE_t *eqep);

//! \brief Resets counter
//! \param[in] eqep		Handle to QEP object
void QEP_reset_counter (eqepBASE_t *eqep);

//! \brief Sets capture latch mode
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEPCTL_Qclm		capture latch mode
void QEP_set_capture_latch_mode (eqepBASE_t *eqep, const QEPCTL_Qclm_e QEPCTL_Qclm);

//! \brief Sets capture period
//! \param[in] eqep		Handle to QEP object
//! \param[in] period			Capture period
void QEP_set_capture_period (eqepBASE_t *eqep, const uint16_t period);

//! \brief Sets capture pre-scaler
//! \param[in] eqep		Handle to QEP object
//! \param[in] QCAPCTL_Ccps		Capture pre-scaler 
void QEP_set_capture_prescale (eqepBASE_t *eqep, const QCAPCTL_Ccps_e QCAPCTL_Ccps);

//! \brief Sets emulation control
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEPCTL_Freesoft	Emulation control bits
void QEP_set_emu_control (eqepBASE_t *eqep, const QEPCTL_Freesoft_e QEPCTL_Freesoft);

//! \brief Sets external clock rate
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEP_Xcr			External clock rate
void QEP_set_ext_clock_rate (eqepBASE_t *eqep, const QEP_Xcr_e QEP_Xcr);

//! \brief Sets the event which initializes the counter register
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEPCTL_Iei		Index event
void QEP_set_index_event_init (eqepBASE_t *eqep, const QEPCTL_Iei_e QEPCTL_Iei);

//! \brief Sets the index event which latches the position counter 
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEPCTL_Iel		Latch event
void QEP_set_index_event_latch (eqepBASE_t *eqep, const QEPCTL_Iel_e QEPCTL_Iel);

//! \brief Sets index polarity
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEP_Qip			Index polarity
void QEP_set_index_polarity (eqepBASE_t *eqep, const QEP_Qip_e QEP_Qip);

//! \brief Sets max position count
//! \param[in] eqep		Handle to QEP object
//! \param[in] max_count		Maximum counter value
void QEP_set_max_posn_count (eqepBASE_t *eqep, const uint32_t max_count);

//! \brief Sets output pulse width when a match occur
//! \param[in] eqep		Handle to QEP object
//! \param[in] pulse_width		Pulse width value
void QEP_set_posn_compare_pulse_width (eqepBASE_t *eqep, const uint16_t pulse_width);

//! \brief Sets position compare shadow load mode
//! \param[in] eqep		Handle to QEP object
//! \param[in] QPOSCTL_Pcload	PC load event	
void QEP_set_posn_compare_shadow_load (eqepBASE_t *eqep, const QPOSCTL_Pcload_e QPOSCTL_Pcload);

//! \brief Sets position counter reset mode
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEPCTL_Pcrm		Position counter reset mode
void QEP_set_posn_count_reset_mode (eqepBASE_t *eqep, const QEPCTL_Pcrm_e QEPCTL_Pcrm);

//! \brief Sets initial position counter value
//! \param[in] eqep		Handle to QEP object
//! \param[in] init_count		initial counter value
void QEP_set_posn_init_count (eqepBASE_t *eqep, const uint32_t init_count);

//! \brief Selects whether index or strobe pin is used for sync output
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEP_SPsel		Selected pin
void QEP_set_select_sync_pin (eqepBASE_t *eqep, const QEP_Spsel_e QEP_SPsel);

//! \brief Determines if software initialization of position counter enabled 
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEPCTL_Swi		Enable/disable position counter initialization
void QEP_set_soft_init (eqepBASE_t *eqep, const QEPCTL_Swi_e QEPCTL_Swi);

//! \brief Determines strobe initialization of position counter 
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEPCTL_Sei		Strobe initialization of position counter (disabled, rising edge of QEPI) or rising/falling depending on direction
void QEP_set_strobe_event_init (eqepBASE_t *eqep, const QEPCTL_Sei_e QEPCTL_Sei);

//! \brief Sets up strobe latch of position counter 
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEPCTL_Sel		Sets strobe latch of position counter
void QEP_set_strobe_event_latch (eqepBASE_t *eqep, const QEPCTL_Sel_e QEPCTL_Sel);

//! \brief Sets up strobe polarity 
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEP_Qsp			Strobe polarity
void QEP_set_strobe_polarity (eqepBASE_t *eqep, const QEP_Qsp_e QEP_Qsp);

//! \brief Sets up swapping of A/B channels
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEP_Swap			Swap/don't swap A/B channels
void QEP_set_swap_quad_inputs (eqepBASE_t *eqep, QEP_Swap_e QEP_Swap);

//! \brief Sets synch output compare polarity
//! \param[in] eqep		Handle to QEP object
//! \param[in] QPOSCTL_Pcpol	Polarity of sync output
void QEP_set_synch_output_compare_polarity (eqepBASE_t *eqep, const QPOSCTL_Pcpol_e QPOSCTL_Pcpol);

//! \brief Sets unit timer period
//! \param[in] eqep		Handle to QEP object
//! \param[in] unit_period		Unit period
void QEP_set_unit_period (eqepBASE_t *eqep, const uint16_t unit_period);

//! \brief Sets unit timer prescaling
//! \param[in] eqep		Handle to QEP object
//! \param[in] QCAPCTL_Upps		Unit timer prescaling
void QEP_set_unit_posn_prescale (eqepBASE_t *eqep, const QCAPCTL_Upps_e QCAPCTL_Upps);

//! \brief Sets watchdog period
//! \param[in] eqep		Handle to QEP object
//! \param[in] watchdog_period	Watchdog period
void QEP_set_watchdog_period (eqepBASE_t *eqep, const uint16_t watchdog_period);

//! \brief Sets A polarity
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEP_Qap			Channel A polarity
void QEP_set_A_polarity (eqepBASE_t *eqep, const QEP_Qap_e QEP_Qap);

//! \brief Sets B polarity
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEP_Qbp			Channel B polarity
void QEP_set_B_polarity (eqepBASE_t *eqep, const QEP_Qbp_e QEP_Qbp);

//! \brief QEP counting mode
//! \param[in] eqep		Handle to QEP object
//! \param[in] QEP_Qsrc			Sets QEP counting mode	
void QEP_set_QEP_source (eqepBASE_t *eqep, const QEP_Qsrc_e QEP_Qsrc);

//! \brief Writes a value to the position compare register
//! \param[in] eqep		Handle to QEP object
//! \param[in] posn				Position compare register value
void QEP_write_posn_compare (eqepBASE_t *eqep, const uint32_t posn);

//! \brief Interrupt callback
//! \param[in] eqep		Handle to QEP object
//! \param[in] flags			Copy of  interrupt flags
void 	eqepNotification(eqepBASE_t *eqep,uint16_t flags);

#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif // end of _QEP_H_ definition

