/** @file sys_selftest.h
*   @brief System Memory Header File
*   @date 15.Mar.2012
*   @version 03.01.00
*   
*   This file contains:
*   - Efuse Self Test Functions
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#ifndef __sys_selftest_H__
#define __sys_selftest_H__

#include "sys_common.h"
#include "sys_core.h"
#include "system.h"
#include "sys_vim.h"
#include "adc.h"
#include "can.h"
#include "mibspi.h"
#include "het.h"
#include "htu.h"
#include "esm.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

#define flash1bitError	(*(volatile uint32_t *) 0xF00803F0)
#define flash2bitError	(*(volatile uint32_t *) 0xF00803F8)

#define tcramA1bitError	(*(volatile uint32_t *)(0x08400000))
#define tcramA2bitError (*(volatile uint32_t *)(0x08400010))

#define tcramB1bitError	(*(volatile uint32_t *)(0x08400008))
#define tcramB2bitError (*(volatile uint32_t *)(0x08400018))

#define tcramA1bit		(*(volatile uint32_t *)0x08000000)
#define tcramA2bit		(*(volatile uint32_t *)0x08000010)

#define tcramB1bit		(*(volatile uint32_t *)0x08000008)
#define tcramB2bit		(*(volatile uint32_t *)0x08000018)

#define flashBadECC		(*(volatile uint32_t *)0x20080000)

#define CCMSR 			(*(volatile uint32_t *)0xFFFFF600U)
#define CCMKEYR			(*(volatile uint32_t *)0xFFFFF604U)

#define DMA_PARCR		(*(volatile uint32_t *)0xFFFFF1A8U)
#define DMA_PARADDR		(*(volatile uint32_t *)0xFFFFF1ACU)

#define DMARAMLOC		(*(volatile uint32_t *)0xFFF80000U)
#define DMARAMPARLOC	(*(volatile uint32_t *)0xFFF80A00U)

#ifndef __PBIST_H__
#define __PBIST_H__

/** @enum pbistPort
*   @brief Alias names for pbist Port number
*
*   This enumeration is used to provide alias names for the pbist Port number
*     - PBIST_PORT0
*     - PBIST_PORT1
*/
enum pbistPort
{
    PBIST_PORT0 = 0, /**< Alias for PBIST Port 0 */
    PBIST_PORT1 = 1  /**< Alias for PBIST Port 1 */
};
/** @enum pbistAlgo
*   @brief Alias names for pbist Algorithm
*
*   This enumeration is used to provide alias names for the pbist Algorithm
*     - PBIST_TripleReadSlow 
*     - PBIST_TripleReadFast 
*     - PBIST_March13N_DP    
*     - PBIST_March13N_SP    
*     - PBIST_DOWN1a_DP      
*     - PBIST_DOWN1a_SP      
*     - PBIST_MapColumn_DP   
*     - PBIST_MapColumn_SP   
*     - PBIST_Precharge_DP   
*     - PBIST_Precharge_SP   
*     - PBIST_DTXN2a_DP      
*     - PBIST_DTXN2a_SP      
*     - PBIST_PMOSOpen_DP    
*     - PBIST_PMOSOpen_SP    
*     - PBIST_PPMOSOpenSlice1_DP
*     - PBIST_PPMOSOpenSlice1_SP
*     - PBIST_PPMOSOpenSlice2_DP
*     - PBIST_PPMOSOpenSlice2_SP

*/
enum pbistAlgo
{
    PBIST_TripleReadSlow     = 0x00000001,
    PBIST_TripleReadFast     = 0x00000002,
    PBIST_March13N_DP        = 0x00000004,
	PBIST_March13N_SP        = 0x00000008,
    PBIST_DOWN1a_DP          = 0x00000010,
	PBIST_DOWN1a_SP          = 0x00000020,
    PBIST_MapColumn_DP       = 0x00000040,
	PBIST_MapColumn_SP       = 0x00000080,
    PBIST_Precharge_DP       = 0x00000100,
	PBIST_Precharge_SP       = 0x00000200,
    PBIST_DTXN2a_DP          = 0x00000400,
	PBIST_DTXN2a_SP          = 0x00000800,
	PBIST_PMOSOpen_DP        = 0x00001000,
    PBIST_PMOSOpen_SP        = 0x00002000,
	PBIST_PPMOSOpenSlice1_DP = 0x00004000,
    PBIST_PPMOSOpenSlice1_SP = 0x00008000,
	PBIST_PPMOSOpenSlice2_DP = 0x00010000,
    PBIST_PPMOSOpenSlice2_SP = 0x00020000
};

/* PBIST General Definitions */

/** @struct pbistBase
*   @brief PBIST Base Register Definition
*
*   This structure is used to access the PBIST module registers.
*/
/** @typedef pbistBASE_t
*   @brief PBIST Register Frame Type Definition
*
*   This type is used to access the PBIST Registers.
*/
typedef volatile struct pbistBase
{
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1)) /* 0x0160: RAM Configuration Register    */
    uint32_t RLS    : 2U;   /* 0x0160: RAM Latency Select         */
    uint32_t PLS    : 4U;   /* 0x0160: Pipeline Latency Select    */
    uint32_t SMS    : 2U;   /* 0x0160: Sense Margin Select Register  */
    uint32_t DWR    : 8U;   /* 0x0160: Data Width Register        */
    uint32_t RDS    : 8U;   /* 0x0160: Return Data Select         */
    uint32_t RGS    : 8U;   /* 0x0160: RAM Group Select           */
#else
    uint32_t RGS    : 8U;   /* 0x0160: RAM Group Select           */
    uint32_t RDS    : 8U;   /* 0x0160: Return Data Select         */
    uint32_t DWR    : 8U;   /* 0x0160: Data Width Register        */
    uint32_t SMS    : 2U;   /* 0x0160: Sense Margin Select Register  */
    uint32_t PLS    : 4U;   /* 0x0160: Pipeline Latency Select    */
    uint32_t RLS    : 2U;   /* 0x0160: RAM Latency Select         */
#endif

    uint32_t DLR;			/* 0x0164: Datalogger Register */
    uint32_t : 32U;			/* 0x0168 */
	uint32_t : 32U;			/* 0x016C */
	uint32_t : 32U;			/* 0x0170 */
	uint32_t : 32U;			/* 0x0174 */
	uint32_t : 32U;			/* 0x0178 */
	uint32_t : 32U;			/* 0x017C */
    uint32_t PACT;			/* 0x0180: PBIST Activate Register */
    uint32_t PBISTID;		/* 0x0184: PBIST ID Register */
    uint32_t OVER;			/* 0x0188: Override Register */
    uint32_t : 32U;			/* 0x018C */
    uint32_t FSRF0;			/* 0x0190: Fail Status Fail Register 0 */
	uint32_t FSRF1;			/* 0x0194: Fail Status Fail Register 1 */
    uint32_t FSRC0;			/* 0x0198: Fail Status Count Register 0 */
    uint32_t FSRC1;			/* 0x019C: Fail Status Count Register 1 */
    uint32_t FSRA0;			/* 0x01A0: Fail Status Address 0 Register */
    uint32_t FSRA1;			/* 0x01A4: Fail Status Address 1 Register */
    uint32_t FSRDL0;		/* 0x01A8: Fail Status Data Register 0 */
    uint32_t : 32U;			/* 0x01AC */
    uint32_t FSRDL1;		/* 0x01B0: Fail Status Data Register 1 */
    uint32_t : 32U;			/* 0x01B4 */
    uint32_t : 32U;			/* 0x01B8 */
    uint32_t : 32U;			/* 0x01BC */
    uint32_t ROM;			/* 0x01C0: ROM Mask Register */
    uint32_t ALGO;			/* 0x01C4: Algorithm Mask Register */
    uint32_t RINFOL;		/* 0x01C8: RAM Info Mask Lower Register */
    uint32_t RINFOU;		/* 0x01CC: RAM Info Mask Upper Register */
} pbistBASE_t;

#define pbistREG   ((pbistBASE_t *)0xFFFFE560U)

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** @fn void memoryPort0TestFailNotification(uint32_t groupSelect, uint32_t dataSelect, uint32_t address, uint32_t data)
*   @brief Memory Port 0 test fail notification
*   @param[in] groupSelect Failing Ram group select:
*   @param[in] dataSelect Failing Ram data select:
*   @param[in] address Failing Ram offset:
*   @param[in] data Failing data at address:
*
*   @note This function has to be provide by the user.
*/
void memoryPort0TestFailNotification(uint32_t groupSelect, uint32_t dataSelect, uint32_t address, uint32_t data);

/** @fn void memoryPort1TestFailNotification(uint32_t groupSelect, uint32_t dataSelect, uint32_t address, uint32_t data)
*   @brief Memory Port 1 test fail notification
*   @param[in] groupSelect Failing Ram group select:
*   @param[in] dataSelect Failing Ram data select:
*   @param[in] address Failing Ram offset:
*   @param[in] data Failing data at address:
*
*   @note This function has to be provide by the user.
*/
void memoryPort1TestFailNotification(uint32_t groupSelect, uint32_t dataSelect, uint32_t address, uint32_t data);

#endif

#ifndef __STC_H__
#define __STC_H__

/* STC General Definitions */

/* STC Test Intervals supported in the Device */
#define STC_INTERVAL 24
#define STC_MAX_TIMEOUT 0xFFFFFFFF

/** @struct stcBase
*   @brief STC Base Register Definition
*
*   This structure is used to access the STC module registers.
*/
/** @typedef stcBASE_t
*   @brief STC Register Frame Type Definition
*
*   This type is used to access the STC Registers.
*/
typedef volatile struct stcBase
{
    uint32_t STCGCR0;		/**< 0x0000: STC Control Register 0	*/
    uint32_t STCGCR1;		/**< 0x0004: STC Control Register 1 */
    uint32_t STCTPR;		/**< 0x0008: STC Self-Test Run Timeout Counter Preload Register	*/
    uint32_t STCCADDR;		/**< 0x000C: STC Self-Test Current ROM Address Register */
    uint32_t STCCICR;		/**< 0x0010: STC Self-Test Current Interval Count Register */
    uint32_t STCGSTAT;		/**< 0x0014: STC Self-Test Global Status Register */
	uint32_t STCFSTAT;		/**< 0x0018: STC Self-Test Fail Status Register */
    uint32_t CPU1_CURMISR3;	/**< 0x001C: STC CPU1 Current MISR Register */
    uint32_t CPU1_CURMISR2;	/**< 0x0020: STC CPU1 Current MISR Register */
    uint32_t CPU1_CURMISR1;	/**< 0x0024: STC CPU1 Current MISR Register */
    uint32_t CPU1_CURMISR0;	/**< 0x0028: STC CPU1 Current MISR Register */
    uint32_t CPU2_CURMISR3;	/**< 0x002C: STC CPU1 Current MISR Register */
    uint32_t CPU2_CURMISR2;	/**< 0x0030: STC CPU1 Current MISR Register */
    uint32_t CPU2_CURMISR1;	/**< 0x0034: STC CPU1 Current MISR Register */
    uint32_t CPU2_CURMISR0;	/**< 0x0038: STC CPU1 Current MISR Register */
    uint32_t STCSCSCR;		/**< 0x003C: STC Signature Compare Self-Check Register */
} stcBASE_t;

#define stcREG   ((stcBASE_t *)0xFFFFE600U)

#endif

#ifndef __EFC_H__
#define __EFC_H__

typedef volatile struct efcBase
{
	uint32_t INSTRUCTION;    			/* 0x0	INSTRUCTION AN DUMPWORD REGISTER	*/
	uint32_t ADDRESS;			    	/* 0x4 ADDRESS REGISTER    					*/
	uint32_t DATA_UPPER;			    /* 0x8 DATA UPPER REGISTER    				*/
	uint32_t DATA_LOWER;				/* 0xc DATA LOWER REGISTER    				*/
	uint32_t SYSTEM_CONFIG;				/* 0x10 SYSTEM CONFIG REGISTER    			*/
	uint32_t SYSTEM_STATUS;				/* 0x14 SYSTEM STATUS REGISTER    			*/
	uint32_t ACCUMULATOR;				/* 0x18 ACCUMULATOR REGISTER    			*/
	uint32_t BOUNDARY;			    	/* 0x1C BOUNDARY REGISTER 					*/
	uint32_t KEY_FLAG;			    	/* 0x20 KEY FLAG REGISTER    				*/
	uint32_t KEY;			        	/* 0x24	KEY REGISTER 						*/
	uint32_t : 32;				        /* 0x28	RESERVED 							*/
	uint32_t PINS;				        /* 0x2C  PINS REGISTER						*/
	uint32_t CRA;				        /* 0x30  CRA								*/
	uint32_t READ;				        /* 0x34 READ REGISTER						*/
	uint32_t PROGRAMME;				    /* 0x38 PROGRAMME REGISTER					*/
	uint32_t ERROR;				        /* 0x3C	ERROR STATUS REGISTER				*/
	uint32_t SINGLE_BIT;				/* 0x40	SINGLE BIT ERROR 					*/
	uint32_t TWO_BIT_ERROR;				/* 0x44	DOUBLE BIT ERROR 					*/
	uint32_t SELF_TEST_CYCLES;			/* 0x48	SELF TEST CYCLEX					*/
	uint32_t SELF_TEST_SIGN;			/* 0x4C SELF TEST SIGNATURE					*/
} efcBASE_t;

#define efcREG   ((efcBASE_t *)0xFFF8C000U)

#define INPUT_ENABLE         0x0000000F
#define INPUT_DISABLE        0x00000000

#define SYS_WS_READ_STATES   0x00000000


#define SYS_REPAIR_EN_0      0x00000000
#define SYS_REPAIR_EN_3      0x00000100
#define SYS_REPAIR_EN_5      0x00000200

#define SYS_DEID_AUTOLOAD_EN 0x00000400
#define SYS_DEID_AUTOLOAD_EN 0x00000400

#define EFC_FDI_EN            0x00000800
#define EFC_FDI_DIS           0x00000000

#define SYS_ECC_OVERRIDE_EN   0x00001000
#define SYS_ECC_OVERRIDE_DIS  0x00000000

#define SYS_ECC_SELF_TEST_EN  0x00002000
#define SYS_ECC_SELF_TEST_DIS 0x00000000

#define OUTPUT_ENABLE         0x0003C000
#define OUTPUT_DISABLE        0x00000000

/*********** OUTPUT **************/

#define EFC_AUTOLOAD_ERROR_EN    0x00040000
#define EFC_INSTRUCTION_ERROR_EN 0x00080000
#define EFC_INSTRUCTION_INFO_EN  0x00100000
#define EFC_SELF_TEST_ERROR_EN   0x00200000


#define EFC_AUTOLOAD_ERROR_DIS    0x00000000
#define EFC_INSTRUCTION_ERROR_DIS 0x00000000
#define EFC_INSTRUCTION_INFO_DIS  0x00000000
#define EFC_SELF_TEST_ERROR_DIS   0x00000000

#define DISABLE_READ_ROW0         0x00800000

/********************************************************************/

#define SYS_REPAIR_0         0x00000010
#define SYS_REPAIR_3         0x00000010
#define SYS_REPAIR_5         0x00000020

#define SYS_DEID_AUTOLOAD    0x00000040
#define SYS_FCLRZ            0x00000080
#define EFC_READY            0x00000100
#define SYS_ECC_OVERRIDE     0x00000200
#define EFC_AUTOLOAD_ERROR   0x00000400
#define EFC_INSTRUCTION_ERROR 0x00000800
#define EFC_INSTRUCTION_INFO  0x00001000
#define SYS_ECC_SELF_TEST    0x00002000
#define EFC_SELF_TEST_ERROR  0x00004000
#define EFC_SELF_TEST_DONE   0x00008000

/**************   0x3C error status register ******************************************************/

#define TIME_OUT 0x01
#define AUTOLOAD_NO_FUSEROM_DATA      0x02 
#define AUTOLOAD_SIGN_FAIL            0x03
#define AUTOLOAD_PROG_INTERRUPT       0x04
#define AUTOLOAD_TWO_BIT_ERR          0x05
#define PROGRAME_WR_P_SET             0x06
#define PROGRAME_MNY_DATA_ITERTN      0x07
#define PROGRAME_MNY_CNTR_ITERTN      0x08
#define UN_PROGRAME_BIT_SET           0x09
#define REDUNDANT_REPAIR_ROW          0x0A
#define PROGRAME_MNY_CRA_ITERTN       0x0B
#define PROGRAME_SAME_DATA            0x0C
#define PROGRAME_CMP_SKIP			  0x0D
#define PROGRAME_ABORT                0x0E
#define PROGRAME_INCORRECT_KEY		  0x0F
#define FUSEROM_LASTROW_STUCK		  0x10
#define AUTOLOAD_SINGLE_BIT_ERR		  0x15
#define DUMPWORD_TWO_BIT_ERR	      0x16
#define DUMPWORD_ONE_BIT_ERR          0x17
#define SELF_TEST_ERROR               0x18

#define INSTRUCTION_DONE              0x20

/**************   Efuse Instruction set ******************************************************/

#define TEST_UNPROGRAME_ROM  0x01000000
#define PROGRAME_CRA         0x02000000  
#define DUMP_WORD            0x04000000
#define LOAD_FUSE_SCAN_CHAIN 0x05000000
#define PROGRAME_DATA        0x07000000
#define RUN_AUTOLOAD_8       0x08000000
#define RUN_AUTOLOAD_A       0x0A000000

#endif

/* safety Init Interface Functions */
void ccmSelfCheck(void);
void ccmFail(uint32_t);

void stcSelfCheck(void);
void stcSelfCheckFail(void);
void cpuSelfTest(uint32_t no_of_intervals, uint32_t max_timeout, boolean_t restart_test);
void cpuSelfTestFail(void);

void _memoryInit_(uint32_t);

void pbistSelfCheck(void);
void pbistRun(uint32_t, uint32_t);
void pbistStop(void);
void pbistSelfCheckFail(void);
boolean_t pbistIsTestCompleted(void);
boolean_t pbistIsTestPassed(void);
boolean_t pbistPortTestStatus(uint32_t port);

void efcCheck(void);
void efcSelfTest(void);
boolean_t efcStuckZeroTest(void);
boolean_t checkefcSelfTest(void);
void efcClass1Error(void);
void efcClass2Error(void);

void fmcBus2Check(void);
void fmcECCcheck(void);
void fmcClass1Error(void);
void fmcClass2Error(void);

void checkB0RAMECC(void);
void checkB1RAMECC(void);
void tcramClass1Error(void);
void tcramClass2Error(void);

void checkFlashECC(void);
void flashClass1Error(void);
void flashClass2Error(void);

void vimParityCheck(void);
void dmaParityCheck(void);
void adc1ParityCheck(void);
void adc2ParityCheck(void);
void het1ParityCheck(void);
void htu1ParityCheck(void);
void het2ParityCheck(void);
void htu2ParityCheck(void);
void can1ParityCheck(void);
void can2ParityCheck(void);
void can3ParityCheck(void);
void mibspi1ParityCheck(void);
void mibspi3ParityCheck(void);
void mibspi5ParityCheck(void);

/* USER CODE BEGIN (2) */
/* USER CODE END */

#endif
