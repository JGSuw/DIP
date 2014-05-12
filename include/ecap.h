/** @file ecap.h
*   @brief ECAP Driver Header File
*   @date 17.July.2012
*   @version 03.02.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the ECAP driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#ifndef __ECAP_H__
#define __ECAP_H__

// **************************************************************************
// the includes

#include "sys_common.h"


//!
//! \defgroup ECAP

//!
//! \ingroup ECAP
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines

//! \brief Defines the base address of the capture (CAP) A registers
//!
#define CAPA_BASE_ADDR              (0x00006A00)




//! \brief Defines the location of the FREE/SOFT bits in the ECCTL1 register
//!
#define CAP_ECCTL1_FREESOFT_BITS   (3 << 14)

//! \brief Defines the location of the PRESCALE bits in the ECCTL1 register
//!
#define CAP_ECCTL1_PRESCALE_BITS   (31 << 9)

//! \brief Defines the location of the CAPLDEN bits in the ECCTL1 register
//!
#define CAP_ECCTL1_CAPLDEN_BITS   (1 << 8)

//! \brief Defines the location of the CTRRST4 bits in the ECCTL1 register
//!
#define CAP_ECCTL1_CTRRST4_BITS   (1 << 7)

//! \brief Defines the location of the CAP4POL bits in the ECCTL1 register
//!
#define CAP_ECCTL1_CAP4POL_BITS   (1 << 6)

//! \brief Defines the location of the CTRRST3 bits in the ECCTL1 register
//!
#define CAP_ECCTL1_CTRRST3_BITS   (1 << 5)

//! \brief Defines the location of the CAP3POL bits in the ECCTL1 register
//!
#define CAP_ECCTL1_CAP3POL_BITS   (1 << 4)

//! \brief Defines the location of the CTRRST2 bits in the ECCTL1 register
//!
#define CAP_ECCTL1_CTRRST2_BITS   (1 << 3)

//! \brief Defines the location of the CAP2POL bits in the ECCTL1 register
//!
#define CAP_ECCTL1_CAP2POL_BITS   (1 << 2)

//! \brief Defines the location of the CTRRST1 bits in the ECCTL1 register
//!
#define CAP_ECCTL1_CTRRST1_BITS   (1 << 1)

//! \brief Defines the location of the CAP1POL bits in the ECCTL1 register
//!
#define CAP_ECCTL1_CAP1POL_BITS   (1 << 0)


//! \brief Defines the location of the APWMPOL bits in the ECCTL2 register
//!
#define CAP_ECCTL2_APWMPOL_BITS   (1 << 10)

//! \brief Defines the location of the CAP/APWM bits in the ECCTL2 register
//!
#define CAP_ECCTL2_CAPAPWM_BITS   (1 << 9)

//! \brief Defines the location of the SWSYNC bits in the ECCTL2 register
//!
#define CAP_ECCTL2_SWSYNC_BITS    (1 << 8)

//! \brief Defines the location of the SYNCO_SEL bits in the ECCTL2 register
//!
#define CAP_ECCTL2_SYNCOSEL_BITS  (3 << 6)

//! \brief Defines the location of the SYNCI_EN bits in the ECCTL2 register
//!
#define CAP_ECCTL2_SYNCIEN_BITS   (1 << 5)

//! \brief Defines the location of the TSCTRSTOP bits in the ECCTL2 register
//!
#define CAP_ECCTL2_TSCTRSTOP_BITS (1 << 4)

//! \brief Defines the location of the REARM bits in the ECCTL2 register
//!
#define CAP_ECCTL2_REARM_BITS     (1 << 3)

//! \brief Defines the location of the STOP_WRAP bits in the ECCTL2 register
//!
#define CAP_ECCTL2_STOP_WRAP_BITS (3 << 1)

//! \brief Defines the location of the CONT/ONESHOT bits in the ECCTL2 register
//!
#define CAP_ECCTL2_CONTONESHOT_BITS (1 << 0)


//! \brief Defines the location of the CTR=COMP bits in the ECCxxx register
//!
#define CAP_ECCxxx_CTRCOMP_BITS  (1 << 7)

//! \brief Defines the location of the CTR=PRD bits in the ECCxxx register
//!
#define CAP_ECCxxx_CTRPRD_BITS   (1 << 6)

//! \brief Defines the location of the CTROVF bits in the ECCxxx register
//!
#define CAP_ECCxxx_CTROVF_BITS   (1 << 5)

//! \brief Defines the location of the CEVT4 bits in the ECCxxx register
//!
#define CAP_ECCxxx_CEVT4_BITS    (1 << 4)

//! \brief Defines the location of the CEVT4 bits in the ECCxxx register
//!
#define CAP_ECCxxx_CEVT3_BITS    (1 << 3)

//! \brief Defines the location of the CEVT4 bits in the ECCxxx register
//!
#define CAP_ECCxxx_CEVT2_BITS    (1 << 2)

//! \brief Defines the location of the CEVT4 bits in the ECCxxx register
//!
#define CAP_ECCxxx_CEVT1_BITS    (1 << 1)

//! \brief Defines the location of the INT bits in the ECCxxx register
//!
#define CAP_ECCxxx_INT_BITS      (1 << 0)




// **************************************************************************
// the typedefs

//! \brief Enumeration to define the capture (CAP) interrupts
//!
typedef enum
{
    CAP_Int_Type_CTR_CMP = (1 << 7),     //!< Denotes CTR = CMP interrupt
    CAP_Int_Type_CTR_PRD = (1 << 6),     //!< Denotes CTR = PRD interrupt
    CAP_Int_Type_CTR_OVF = (1 << 5),     //!< Denotes CTROVF interrupt
    CAP_Int_Type_CEVT4 = (1 << 4),       //!< Denotes CEVT4 interrupt
    CAP_Int_Type_CEVT3 = (1 << 3),       //!< Denotes CEVT3 interrupt
    CAP_Int_Type_CEVT2 = (1 << 2),       //!< Denotes CEVT2 interrupt
    CAP_Int_Type_CEVT1 = (1 << 1),       //!< Denotes CEVT1 interrupt
    CAP_Int_Type_Global = (1 << 0),      //!< Denotes Capture global interrupt
    CAP_Int_Type_All = 0x00FF            //!< Denotes All interrupts
} CAP_Int_Type_e;

//! \brief Enumeration to define the capture (CAP) prescaler values
//!
typedef enum
{
    CAP_Prescale_By_1 = (0 << 9),    //!< Divide by 1
    CAP_Prescale_By_2 = (1 << 9),    //!< Divide by 2
    CAP_Prescale_By_4 = (2 << 9),    //!< Divide by 4
    CAP_Prescale_By_6 = (3 << 9),    //!< Divide by 6
    CAP_Prescale_By_8 = (4 << 9),    //!< Divide by 8
    CAP_Prescale_By_10 = (5 << 9),   //!< Divide by 10
    CAP_Prescale_By_12 = (6 << 9),   //!< Divide by 12
    CAP_Prescale_By_14 = (7 << 9),   //!< Divide by 14
    CAP_Prescale_By_16 = (8 << 9),   //!< Divide by 16
    CAP_Prescale_By_18 = (9 << 9),   //!< Divide by 18
    CAP_Prescale_By_20 = (10 << 9),  //!< Divide by 20
    CAP_Prescale_By_22 = (11 << 9),  //!< Divide by 22
    CAP_Prescale_By_24 = (12 << 9),  //!< Divide by 24
    CAP_Prescale_By_26 = (13 << 9),  //!< Divide by 26
    CAP_Prescale_By_28 = (14 << 9),  //!< Divide by 28
    CAP_Prescale_By_30 = (15 << 9),  //!< Divide by 30
    CAP_Prescale_By_32 = (16 << 9),  //!< Divide by 32
    CAP_Prescale_By_34 = (17 << 9),  //!< Divide by 34
    CAP_Prescale_By_36 = (18 << 9),  //!< Divide by 36
    CAP_Prescale_By_38 = (19 << 9),  //!< Divide by 38
    CAP_Prescale_By_40 = (20 << 9),  //!< Divide by 40
    CAP_Prescale_By_42 = (21 << 9),  //!< Divide by 42
    CAP_Prescale_By_44 = (22 << 9),  //!< Divide by 44
    CAP_Prescale_By_46 = (23 << 9),  //!< Divide by 46
    CAP_Prescale_By_48 = (24 << 9),  //!< Divide by 48
    CAP_Prescale_By_50 = (25 << 9),  //!< Divide by 50
    CAP_Prescale_By_52 = (26 << 9),  //!< Divide by 52
    CAP_Prescale_By_54 = (27 << 9),  //!< Divide by 54
    CAP_Prescale_By_56 = (28 << 9),  //!< Divide by 56
    CAP_Prescale_By_58 = (29 << 9),  //!< Divide by 58
    CAP_Prescale_By_60 = (30 << 9),  //!< Divide by 60
    CAP_Prescale_By_62 = (31 << 9)   //!< Divide by 62
} CAP_Prescale_e;

//! \brief Enumeration to define the pulse width modulation (PWM) run modes
//!
typedef enum
{
    CAP_RunMode_HardStop = (0 << 14),
    CAP_RunMode_SoftStopAfterCycle = (1 << 14),
    CAP_RunMode_FreeRun = (2 << 14)
} CAP_RunMode_e;

//! \brief Enumeration to define the capture (CAP) Stop/Wrap modes
//!
typedef enum
{
    CAP_Stop_Wrap_CEVT1 = (0 << 1),     //!< Stop/Wrap after Capture Event 1
    CAP_Stop_Wrap_CEVT2 = (1 << 1),     //!< Stop/Wrap after Capture Event 2
    CAP_Stop_Wrap_CEVT3 = (2 << 1),     //!< Stop/Wrap after Capture Event 3
    CAP_Stop_Wrap_CEVT4 = (3 << 1)      //!< Stop/Wrap after Capture Event 4
} CAP_Stop_Wrap_e;

//! \brief Enumeration to define the capture (CAP) events
//!
typedef enum
{
    CAP_Event_1 = 0,     //!< Capture Event 1
    CAP_Event_2,         //!< Capture Event 2
    CAP_Event_3,         //!< Capture Event 3
    CAP_Event_4          //!< Capture Event 4
} CAP_Event_e;

//! \brief Enumeration to define the capture (CAP) event polarities
//!
typedef enum
{
    CAP_Polarity_Rising = 0,     //!< Rising Edge Triggered
    CAP_Polarity_Falling         //!< Falling Edge Triggered
} CAP_Polarity_e;


//! \brief Enumeration to define the capture (CAP) event resets
//!
typedef enum
{
    CAP_Reset_Disable = 0,     //!< Disable counter reset on capture event
    CAP_Reset_Enable           //!< Enable counter reset on capture event
} CAP_Reset_e;

//! \brief Enumeration to define the Sync Out options
//!
typedef enum
{
    CAP_SyncOut_SyncIn = (0 << 6),     //!< Sync In used for Sync Out
    CAP_SyncOut_CTRPRD = (1 << 6),     //!< CTR = PRD used for Sync Out
    CAP_SyncOut_Disable = (2 << 6)    //!< Disables Sync Out
} CAP_SyncOut_e;

//! \brief Enumeration to define the Polarity
//!
typedef enum
{
  RISING_EDGE=0,
  FALLING_EDGE=1
} CAP_Polarity;

//! \brief Enumeration to define the Mode of operation
//!
typedef enum
{
 CONTINUOUS=0,
 ONE_SHOT=1
} CAP_Mode;

//! \brief Enumeration to define the capture events
//!
typedef enum
{
 CAPTURE_EVENT1=0,
 CAPTURE_EVENT2=1,
 CAPTURE_EVENT3=2,
 CAPTURE_EVENT4=3
} CAP_Event ;

//! \brief Defines the capture (CAP) object
//!
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1)) 

typedef struct _ecapBASE_t_
 {

   uint32_t              TSCTR;    /**<  0x0000 Time stamp counter Register*/
   uint32_t              CTRPHS;  /**<  0x0004 Counter phase Register*/ 
   uint32_t              CAP1;      /**<  0x0008 Capture 1 Register*/
   uint32_t              CAP2;      /**<  0x000C Capture 2 Register*/
   uint32_t              CAP3;      /**<  0x0010 Capture 3 Register*/
   uint32_t              CAP4;      /**<  0x0014 Capture 4 Register*/
   uint16_t              rsvd1[8];  /**<  0x0018 Reserved*/
   uint16_t              ECCTL1;   /**<  0x0028 Capture Control Reg 1 Register*/
   uint16_t              ECCTL2;   /**<  0x002A Capture Control Reg 2 Register*/
   uint16_t              ECEINT;    /**<  0x002C Interrupt enable Register*/
   uint16_t              ECFLG;     /**<  0x002E Interrupt flags Register*/ 
   uint16_t              ECCLR;     /**<  0x0030 Interrupt clear Register*/
   uint16_t              ECFRC;     /**<  0x0032 Interrupt force Register*/
   uint16_t              rsvd2[6];  /**<  0x0034 Reserved*/

}ecapBASE_t;

#else

typedef struct _ecapBASE_t_
 {

   uint32_t              TSCTR;    /**<  0x0000 Time stamp counter Register*/
   uint32_t              CTRPHS;  /**<  0x0004 Counter phase Register*/ 
   uint32_t              CAP1;      /**<  0x0008 Capture 1 Register*/
   uint32_t              CAP2;      /**<  0x000C Capture 2 Register*/
   uint32_t              CAP3;      /**<  0x0010 Capture 3 Register*/
   uint32_t              CAP4;      /**<  0x0014 Capture 4 Register*/
   uint16_t              rsvd1[8];  /**<  0x0018 Reserved*/
   uint16_t              ECCTL2;   /**<  0x002A Capture Control Reg 2 Register*/
   uint16_t              ECCTL1;   /**<  0x0028 Capture Control Reg 1 Register*/
   uint16_t              ECFLG;     /**<  0x002E Interrupt flags Register*/ 
   uint16_t              ECEINT;    /**<  0x002C Interrupt enable Register*/
   uint16_t              ECFRC;     /**<  0x0032 Interrupt force Register*/
   uint16_t              ECCLR;     /**<  0x0030 Interrupt clear Register*/
   uint16_t              rsvd2[6];  /**<  0x0034 Reserved*/

}ecapBASE_t;

#endif
/** @def ecapREG1
*   @brief ECAP1 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP1 registers.
*/
#define ecapREG1 ((ecapBASE_t *)0xFCF79300U)

/** @def ecapREG2
*   @brief ECAP2 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP2 registers.
*/
#define ecapREG2 ((ecapBASE_t *)0xFCF79400U)

/** @def ecapREG3
*   @brief ECAP3 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP3 registers.
*/
#define ecapREG3 ((ecapBASE_t *)0xFCF79500U)

/** @def ecapREG4
*   @brief ECAP4 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP4 registers.
*/
#define ecapREG4 ((ecapBASE_t *)0xFCF79600U)

/** @def ecapREG5
*   @brief ECAP5 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP5 registers.
*/
#define ecapREG5 ((ecapBASE_t *)0xFCF79700U)

/** @def ecapREG6
*   @brief ECAP6 Register Frame Pointer
*
*   This pointer is used by the ECAP driver to access the ECAP6 registers.
*/
#define ecapREG6 ((ecapBASE_t *)0xFCF79800U)




// **************************************************************************
// the globals


// **************************************************************************
// the function prototypes

//! \brief     Initializes the ETPWM module
void CAP_init(void);

//! \brief     Sets capture peripheral up for capture mode
//! \param[in] ecap  The capture (CAP) object handle
void CAP_setModeCap(ecapBASE_t *ecap);

//! \brief     Sets capture peripheral up for APWM mode
//! \param[in] ecap  The capture (CAP) object handle
void CAP_setModeApwm(ecapBASE_t *ecap);

//! \brief     Clears capture (CAP) interrupt flag
//! \param[in] ecap  The capture (CAP) object handle
//! \param[in] intType  The capture interrupt to be cleared
inline void CAP_clearInt(ecapBASE_t *ecap, const CAP_Int_Type_e intType)
{ 
      
    ecap->ECCLR |= intType;
    
    return;
}

//! \brief     Disables loading of CAP1-4 on capture event
//! \param[in] ecap  The capture (CAP) object handle
void CAP_disableCaptureLoad(ecapBASE_t *ecap);

//! \brief     Disables capture (CAP) interrupt source
//! \param[in] ecap  The capture (CAP) object handle
//! \param[in] intType  The capture interrupt type to be disabled
void CAP_disableInt(ecapBASE_t *ecap, const CAP_Int_Type_e intType);

//! \brief     Disables counter synchronization
//! \param[in] ecap  The capture (CAP) object handle
void CAP_disableSyncIn(ecapBASE_t *ecap);

//! \brief     Disables Time Stamp counter from running
//! \param[in] ecap  The capture (CAP) object handle
void CAP_disableTimestampCounter(ecapBASE_t *ecap);

//! \brief     Enables loading of CAP1-4 on capture event
//! \param[in] ecap  The capture (CAP) object handle
void CAP_enableCaptureLoad(ecapBASE_t *ecap);

//! \brief     Enables capture (CAP) interrupt source
//! \param[in] ecap  The capture (CAP) object handle
//! \param[in] intType  The capture interrupt type to be enabled
void CAP_enableInt(ecapBASE_t *ecap, const CAP_Int_Type_e intType);

//! \brief     Enables counter synchronization
//! \param[in] ecap  The capture (CAP) object handle
void CAP_enableSyncIn(ecapBASE_t *ecap);

//! \brief     Enables Time Stamp counter to running
//! \param[in] ecap  The capture (CAP) object handle
void CAP_enableTimestampCounter(ecapBASE_t *ecap);

//! \brief     Gets the CAP1 register value
//! \param[in] ecap  The capture (CAP) object handle
inline uint32_t CAP_getCap1(ecapBASE_t *ecap)
{
    
        return (ecap->CAP1);
} // end of CAP_getCap1() function

//! \brief     Gets the CAP2 register value
//! \param[in] ecap  The capture (CAP) object handle
inline uint32_t CAP_getCap2(ecapBASE_t *ecap)
{
    
      return (ecap->CAP2);
} // end of CAP_getCap2() function

//! \brief     Gets the CAP3 register value
//! \param[in] ecap  The capture (CAP) object handle
inline uint32_t CAP_getCap3(ecapBASE_t *ecap)
{
        
    return (ecap->CAP3);
} // end of CAP_getCap3() function

//! \brief     Gets the CAP4 register value
//! \param[in] ecap  The capture (CAP) object handle
inline uint32_t CAP_getCap4(ecapBASE_t *ecap)
{
      
    return (ecap->CAP4);
} // end of CAP_getCap4() function

//! \brief     (Re-)Arm the capture module
//! \param[in] ecap  The capture (CAP) object handle
inline void CAP_rearm(ecapBASE_t *ecap)
{
    
     ecap->ECCTL2 |= CAP_ECCTL2_REARM_BITS;
    
    return;
} // end of CAP_rearm() function

//! \brief     Sets the capture event polarity
//! \param[in] ecap  The capture (CAP) object handle
//! \param[in] event  The event to configure
//! \param[in] polarity  The polarity to configure the event for
void CAP_setCapEvtPolarity(ecapBASE_t *ecap, const CAP_Event_e event, const CAP_Polarity_e polarity);

//! \brief     Sets the capture event counter reset configuration
//! \param[in] ecap  The capture (CAP) object handle
//! \param[in] event  The event to configure
//! \param[in] reset  Whether the event should reset the counter or not
void CAP_setCapEvtReset(ecapBASE_t *ecap, const CAP_Event_e event, const CAP_Reset_e reset);

//! \brief     Sets up for continuous Capture
//! \param[in] ecap  The capture (CAP) object handle
void CAP_setCapContinuous(ecapBASE_t *ecap);

//! \brief     Sets up for one-shot Capture
//! \param[in] ecap  The capture (CAP) object handle
void CAP_setCapOneShot(ecapBASE_t *ecap);

//! \brief     Sets the APWM period
//! \param[in] ecap  The capture (CAP) object handle
//! \param[in] period  The APWM period
inline void CAP_setApwmPeriod(ecapBASE_t *ecap, const uint32_t period)
{
        
    ecap->CAP1 = period;
    
    return;
} // end of CAP_setApwmPeriod() function

//! \brief     Sets the APWM compare value
//! \param[in] ecap  The capture (CAP) object handle
//! \param[in] compare  The APWM compare value
inline void CAP_setApwmCompare(ecapBASE_t *ecap, const uint32_t compare)
{
    
    ecap->CAP2 = compare;
    
    return;
} // end of CAP_setApwmCompare() function

//! \brief     Set the stop/wrap mode
//! \param[in] ecap  The capture (CAP) object handle
//! \param[in] stopWrap  The stop/wrap mode to set
void CAP_setStopWrap(ecapBASE_t *ecap, const CAP_Stop_Wrap_e stopWrap);

//! \brief     Set the sync out mode
//! \param[in] ecap  The capture (CAP) object handle
//! \param[in] syncOut  The sync out mode to set
void CAP_setSyncOut(ecapBASE_t *ecap, const CAP_SyncOut_e syncOut);

//! \brief Interrupt callback
//! \param[in] ecap		Handle to CAP object
//! \param[in] flags			Copy of  interrupt flags
void 	ecapNotification(ecapBASE_t *ecap,uint16_t flags);



#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup

#endif // end of _CAP_H_ definition

