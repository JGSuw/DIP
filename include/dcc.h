/** @file dcc.h
*   @brief DCC Driver Definition File
*   @date 15.Mar.2012
*   @version 03.01.00
*   
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */


#ifndef __DCC_H__
#define __DCC_H__

#include "sys_common.h"

/* DCC General Definitions */

/** @def dcc1CNT0_CLKSRC_HFLPO
*   @brief Alias name for DCC1 Counter 0 Clock Source HFLPO
*
*   This is an alias name for the Clock Source HFLPO for DCC1 Counter 0.
*
*   @note This value should be used for API argument @a cnt0_Clock_Source
*/
#define dcc1CNT0_CLKSRC_HFLPO 0x00000005U

/** @def dcc1CNT0_CLKSRC_TCK
*   @brief Alias name for DCC1 Counter 0 Clock Source TCK
*
*   This is an alias name for the Clock Source TCK for DCC1 Counter 0.
*
*   @note This value should be used for API argument @a cnt0_Clock_Source
*/
#define dcc1CNT0_CLKSRC_TCK 0x0000000AU

/** @def dcc1CNT0_CLKSRC_OSCIN
*   @brief Alias name for DCC1 Counter 0 Clock Source OSCIN
*
*   This is an alias name for the Clock Source OSCIN for DCC1 Counter 0.
*
*   @note This value should be used for API argument @a cnt0_Clock_Source
*/
#define dcc1CNT0_CLKSRC_OSCIN 0x0000000FU

/** @def dcc1CNT1_CLKSRC_PLL1
*   @brief Alias name for DCC1 Counter 1 Clock Source PLL1
*
*   This is an alias name for the Clock Source PLL for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_PLL1 0x0000A0000U

/** @def dcc1CNT1_CLKSRC_PLL2
*   @brief Alias name for DCC1 Counter 1 Clock Source PLL2
*
*   This is an alias name for the Clock Source OSCIN for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_PLL2 0x0000A0001U

/** @def dcc1CNT1_CLKSRC_LFLPO
*   @brief Alias name for DCC1 Counter 1 Clock Source LFLPO
*
*   This is an alias name for the Clock Source LFLPO for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_LFLPO 0x0000A0002U

/** @def dcc1CNT1_CLKSRC_HFLPO
*   @brief Alias name for DCC1 Counter 1 Clock Source HFLPO
*
*   This is an alias name for the Clock Source HFLPO for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_HFLPO 0x0000A0003U

/** @def dcc1CNT1_CLKSRC_EXTCLKIN1
*   @brief Alias name for DCC1 Counter 1 Clock Source EXTCLKIN1
*
*   This is an alias name for the Clock Source EXTCLKIN1 for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_EXTCLKIN1 0x0000A0005U

/** @def dcc1CNT1_CLKSRC_EXTCLKIN2
*   @brief Alias name for DCC1 Counter 1 Clock Source EXTCLKIN2
*
*   This is an alias name for the Clock Source EXTCLKIN2 for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_EXTCLKIN2 0x0000A0006U

/** @def dcc1CNT1_CLKSRC_VCLK
*   @brief Alias name for DCC1 Counter 1 Clock Source VCLK
*
*   This is an alias name for the Clock Source VCLK for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_VCLK 0x0000A0008U

/** @def dcc1CNT1_CLKSRC_N2HET1_31
*   @brief Alias name for DCC1 Counter 1 Clock Source N2HET1_31
*
*   This is an alias name for the Clock Source N2HET1_31 for DCC1 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc1CNT1_CLKSRC_N2HET1_31 0x00005000FU

/** @def dcc2CNT0_CLKSRC_TCK
*   @brief Alias name for DCC2 Counter 0 Clock Source TCK
*
*   This is an alias name for the Clock Source TCK for DCC2 Counter 0.
*
*   @note This value should be used for API argument @a cnt0_Clock_Source
*/
#define dcc2CNT0_CLKSRC_TCK 0x0000000AU

/** @def dcc1CNT0_CLKSRC_OSCIN
*   @brief Alias name for DCC1 Counter 0 Clock Source OSCIN
*
*   This is an alias name for the Clock Source OSCIN for DCC2 Counter 0.
*
*   @note This value should be used for API argument @a cnt0_Clock_Source
*/
#define dcc2CNT0_CLKSRC_OSCIN 0x0000000FU

/** @def dcc2CNT1_CLKSRC_VCLK
*   @brief Alias name for DCC2 Counter 1 Clock Source VCLK
*
*   This is an alias name for the Clock Source VCLK for DCC2 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc2CNT1_CLKSRC_VCLK 0x0000A0008U

/** @def dcc2CNT1_CLKSRC_N2HET1_0
*   @brief Alias name for DCC2 Counter 1 Clock Source N2HET2_0
*
*   This is an alias name for the Clock Source N2HET2_0 for DCC2 Counter 1.
*
*   @note This value should be used for API argument @a cnt1_Clock_Source
*/
#define dcc2CNT1_CLKSRC_N2HET1_0 0x00005000FU

/** @def dccNOTIFICATION_DONE
*   @brief Alias name for DCC Done notification
*
*   This is an alias name for the DCC Done notification.
*
*   @note This value should be used for API argument @a notification
*/
#define dccNOTIFICATION_DONE 0x0000A000U

/** @def dccNOTIFICATION_ERROR
*   @brief Alias name for DCC Error notification
*
*   This is an alias name for the DCC Error notification.
*
*   @note This value should be used for API argument @a notification
*/
#define dccNOTIFICATION_ERROR 0x000000A0U


/** @enum dcc1clocksource
*   @brief Alias names for dcc clock sources
*
*   This enumeration is used to provide alias names for the clock sources:
*/
enum dcc1clocksource
{
    DCC1_CNT0_HF_LPO	= 0x5,	/**< Alias for DCC1 CNT 0 CLOCK SOURCE 0*/
	DCC1_CNT0_TCK		= 0xA,	/**< Alias for DCC1 CNT 0 CLOCK SOURCE 1*/
	DCC1_CNT0_OSCIN		= 0xF,	/**< Alias for DCC1 CNT 0 CLOCK SOURCE 2*/

    DCC1_CNT1_PLL1		= 0x0,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 0*/
    DCC1_CNT1_PLL2		= 0x1,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 1*/
	DCC1_CNT1_LF_LPO	= 0x2,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 2*/
	DCC1_CNT1_HF_LPO	= 0x3,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 3*/
	DCC1_CNT1_EXTCLKIN1 = 0x5,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 4*/
	DCC1_CNT1_EXTCLKIN2 = 0x6,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 6*/
	DCC1_CNT1_VCLK		= 0x8,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 8*/
	DCC1_CNT1_N2HET1_31	= 0xA	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 9*/
};

/** @enum dcc2clocksource
*   @brief Alias names for dcc clock sources
*
*   This enumeration is used to provide alias names for the clock sources:
*/
enum dcc2clocksource
{
    DCC2_CNT0_OSCIN		= 0xF,	/**< Alias for DCC1 CNT 0 CLOCK SOURCE 0*/
    DCC2_CNT0_TCK		= 0xA,	/**< Alias for DCC1 CNT 0 CLOCK SOURCE 2*/

   	DCC2_CNT1_VCLK		= 0x8,	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 8*/
	DCC2_CNT1_N2HET2_0	= 0xA	/**< Alias for DCC1 CNT 1 CLOCK SOURCE 9*/
};

/** @struct dccBase
*   @brief DCC Base Register Definition
*
*   This structure is used to access the DCC module registers.
*/
/** @typedef dccBASE_t
*   @brief DCC Register Frame Type Definition
*
*   This type is used to access the DCC Registers.
*/
typedef volatile struct dccBase
{
    uint32_t GCTRL;      	/**< 0x0000: DCC Control Register		*/
    uint32_t REV;      		/**< 0x0004: DCC Revision Id Register 	*/
    uint32_t CNT0SEED;    	/**< 0x0008: DCC Counter0 Seed Register	*/
    uint32_t VALID0SEED;    /**< 0x000C: DCC Valid0 Seed Register 	*/
    uint32_t CNT1SEED;		/**< 0x0010: DCC Counter1 Seed Register 	*/
    uint32_t STAT; 			/**< 0x0014: DCC Status Register 		*/
    uint32_t CNT0;    		/**< 0x0018: DCC Counter0 Value Register 	*/
    uint32_t VALID0;    	/**< 0x001C: DCC Valid0 Value Register 	*/
    uint32_t CNT1;      	/**< 0x0020: DCC Counter1 Value Register	*/
    uint32_t CLKSRC1;   	/**< 0x0024: DCC Counter1 Clock Source Selection Register 	*/
    uint32_t CLKSRC0;   	/**< 0x0028: DCC Counter0 Clock Source Selection Register 	*/
} dccBASE_t;


/** @def dccREG1
*   @brief DCC1 Register Frame Pointer
*
*   This pointer is used by the DCC driver to access the dcc2 module registers.
*/
#define dccREG1   ((dccBASE_t *)0xFFFFEC00U)


/** @def dccREG2
*   @brief DCC2 Register Frame Pointer
*
*   This pointer is used by the DCC driver to access the dcc2 module registers.
*/
#define dccREG2   ((dccBASE_t *)0xFFFFF400U)


/* DCC Interface Functions */
void dccInit(void);
void dccSetCounter0Seed(dccBASE_t  *dcc, uint32_t cnt0seed);
void dccSetTolerance(dccBASE_t  *dcc, uint32_t valid0seed);
void dccSetCounter1Seed(dccBASE_t  *dcc, uint32_t cnt1seed);
void dccSetSeed(dccBASE_t  *dcc, uint32_t cnt0seed, uint32_t valid0seed, uint32_t cn1seed);
void dccSelectClockSource(dccBASE_t  *dcc, uint32_t cnt0_Clock_Source, uint32_t cnt1_Clock_Source);
void dccEnable(dccBASE_t  *dcc);
void dccDisable(dccBASE_t  *dcc);
uint32_t dccGetErrStatus(dccBASE_t  *dcc);

void dccEnableNotification(dccBASE_t  *dcc, uint32_t notification);
void dccDisableNotification(dccBASE_t  *dcc, uint32_t notification);

/** @fn void dccNotification(dccBASE_t  *dcc,uint32_t flags)
*   @brief Interrupt callback
*   @param[in] dcc   - dcc module base address
*   @param[in] flags - status flags
*
* This is a callback function provided by the application.  It is call when
* a dcc is complete or detected error.
*/
void dccNotification(dccBASE_t  *dcc,uint32_t flags);

#endif
