/** @file CRC.h
*   @brief CRC Driver Header File
*   @date 15.Mar.2012
*   @version 03.01.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the CRC driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#include "sys_common.h"

#ifndef __CRC_H__
#define __CRC_H__

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* CRC General Definitions */

/** @def CRCLEVEL_ACTIVE
*   @brief Alias name for CRC error operation level active 
*/
#define CRCLEVEL_ACTIVE 0x00U


/** @def CRC_AUTO
*   @brief Alias name for CRC auto mode
*/
#define CRC_AUTO 0x00000001


/** @def CRC_SEMI_CPU
*   @brief Alias name for semi cpu mode setting
*/
#define CRC_SEMI_CPU 0x00000002


/** @def CRC_FULL_CPU
*   @brief Alias name for CRC cpu full mode
*/
#define CRC_FULL_CPU 0x00000003


/** @def CRC_CH4_TO
*   @brief Alias name for channel1 time out interrupt flag
*/
#define CRC_CH4_TO 0x10000000

/** @def CRC_CH4_UR
*   @brief Alias name for channel1 underrun interrupt flag
*/
#define CRC_CH4_UR 0x08000000

/** @def CRC_CH4_OR
*   @brief Alias name for channel1 overrun interrupt flag
*/
#define CRC_CH4_OR 0x04000000

/** @def CRC_CH4_FAIL
*   @brief Alias name for channel1 crc fail interrupt flag
*/
#define CRC_CH4_FAIL 0x02000000

/** @def CRC_CH4_CC
*   @brief Alias name for channel1 compression complete interrupt flag
*/
#define CRC_CH4_CC 0x01000000

/** @def CRC_CH3_TO
*   @brief Alias name for channel2 time out interrupt flag
*/
#define CRC_CH3_TO 0x00100000

/** @def CRC_CH3_UR
*   @brief Alias name for channel2 underrun interrupt flag
*/
#define CRC_CH3_UR 0x00080000

/** @def CRC_CH3_OR
*   @brief Alias name for channel2 overrun interrupt flag
*/
#define CRC_CH3_OR 0x00040000

/** @def CRC_CH3_FAIL
*   @brief Alias name for channel2 crc fail interrupt flag
*/
#define CRC_CH3_FAIL 0x00020000

/** @def CRC_CH3_CC
*   @brief Alias name for channel2 compression complete interrupt flag
*/
#define CRC_CH3_CC 0x00010000

/** @def CRC_CH2_TO
*   @brief Alias name for channel3 time out interrupt flag
*/
#define CRC_CH2_TO 0x00001000

/** @def CRC_CH2_UR
*   @brief Alias name for channel3 underrun interrupt flag
*/
#define CRC_CH2_UR 0x00000800

/** @def CRC_CH2_OR
*   @brief Alias name for channel3 overrun interrupt flag  
*/
#define CRC_CH2_OR 0x00000400

/** @def CRC_CH2_FAIL
*   @brief Alias name for channel3 crc fail interrupt flag 
*/
#define CRC_CH2_FAIL 0x00000200

/** @def CRC_CH2_CC
*   @brief Alias name for channel3 compression complete interrupt flag  
*/
#define CRC_CH2_CC 0x00000100

/** @def CRC_CH1_TO
*   @brief Alias name for channel4 time out interrupt flag 
*/
#define CRC_CH1_TO 0x00000010

/** @def CRC_CH1_UR
*   @brief Alias name for channel4 underrun interrupt flag
*/
#define CRC_CH1_UR 0x00000008


/** @def CRC_CH1_OR
*   @brief Alias name for channel4 overrun interrupt flag  
*/
#define CRC_CH1_OR 0x00000004

/** @def CRC_CH1_FAIL
*   @brief Alias name for channel4 crc fail interrupt flag  
*/
#define CRC_CH1_FAIL 0x00000002

/** @def CRC_CH1_CC
*   @brief Alias name for channel4 compression complete interrupt flag    
*/
#define CRC_CH1_CC 0x00000001



/** @struct crcModConfig
*   @brief CRC configuration for different modes
*
*   This type is used to pass crc mode configuration details
*/
/** @typedef crcModConfig_t
*   @brief CRC Data Type Definition
*/
typedef struct crcModConfig
{
    uint32_t mode;     /**< Mode of operation        */
    uint32_t crc_channel;     /**< CRC channel-0,1       */
    uint32_t * src_data_pat;  /**< Pattern data */
    uint32_t data_length;  /**< Pattern data length.Number of 64 bit size word*/
} crcModConfig_t;

/** @struct crcConfig
*   @brief CRC configuration for different modes
*
*   This type is used to pass crc configuration
*/
/** @typedef crcConfig_t
*   @brief CRC Data Type Definition
*/
typedef struct crcConfig
{
    uint32_t crc_channel;     /**< CRC channel-0,1         */
    uint32_t mode;     /**< Mode of operation        */
    uint32_t pcount;     /**< Pattern count*/
    uint32_t scount;     /**< Sector count  */
    uint32_t wdg_preload;  /**< Watchdog period */
    uint32_t block_preload;  /**< Block period*/

} crcConfig_t;


/** @struct crcBase
*   @brief CRC Register Frame Definition
*
*   This type is used to access the CRC Registers.
*/
/** @typedef crcBASE_t
*   @brief CRC Register Frame Type Definition
*
*   This type is used to access the CRC Registers.
*/
typedef volatile struct crcBase
{
    uint32_t      CTRL0;                 /**< 0x0000: Global Control Register 0 >**/
    uint32_t      : 32U;                /**< 0x0004: reserved >**/
    uint32_t      CTRL1;                /**< 0x0008: Global Control Register 1 >**/
    uint32_t      : 32U;                /**< 0x000C: reserved >**/    
    uint32_t      CTRL2;                /**< 0x0010: Global Control Register 2 >**/
    uint32_t      : 32U;                /**< 0x0014: reserved >**/        
    uint32_t      INTS;                 /**< 0x0018: Interrupt Enable Set Register >**/
    uint32_t      : 32U;                /**< 0x001C: reserved >**/        
    uint32_t      INTR;                 /**< 0x0020: Interrupt Enable Reset Register >**/
    uint32_t      : 32U;                /**< 0x0024: reserved >**/    
    uint32_t      STATUS;               /**< 0x0028: Interrupt Status Register >**/
    uint32_t      : 32U;                /**< 0x002C: reserved >**/    
    uint32_t      INT_OFFSET_REG;       /**< 0x0030: Interrupt Offset >**/
    uint32_t      : 32U;                /**< 0x0034: reserved >**/    
    uint32_t      BUSY;                 /**< 0x0038: CRC Busy Register >**/
    uint32_t      : 32U;                /**< 0x003C: reserved >**/    
    uint32_t      PCOUNT_REG1;          /**< 0x0040: Pattern Counter Preload Register1 >**/
    uint32_t      SCOUNT_REG1;          /**< 0x0044: Sector Counter Preload Register1 >**/
    uint32_t      CURSEC_REG1;          /**< 0x0048: Current Sector Register 1 >**/
    uint32_t      WDTOPLD1;             /**< 0x004C: Channel 1 Watchdog Timeout Preload Register A >**/
    uint32_t      BCTOPLD1;             /**< 0x0050: Channel 1 Block Complete Timeout Preload Register B >**/
    uint32_t      : 32U;                /**< 0x0054: reserved >**/
    uint32_t      : 32U;                /**< 0x0058: reserved >**/
    uint32_t      : 32U;                /**< 0x005C: reserved >**/
    uint32_t      PSA_SIGREGL1;         /**< 0x0060: Channel 1 PSA signature low register >**/
    uint32_t      PSA_SIGREGH1;         /**< 0x0064: Channel 1 PSA signature high register >**/
    uint32_t      REGL1;                /**< 0x0068: Channel 1 CRC value low register >**/
    uint32_t      REGH1;                /**< 0x006C: Channel 1 CRC value high register >**/
    uint32_t      PSA_SECSIGREGL1;      /**< 0x0070: Channel 1 PSA sector signature low register >**/
    uint32_t      PSA_SECSIGREGH1;      /**< 0x0074: Channel 1 PSA sector signature high register >**/
    uint32_t      RAW_DATAREGL1;        /**< 0x0078: Channel 1 Raw Data Low Register >**/
    uint32_t      RAW_DATAREGH1;        /**< 0x007C: Channel 1 Raw Data High Register >**/
    uint32_t      PCOUNT_REG2;          /**< 0x0080: CRC Pattern Counter Preload Register2 >**/
    uint32_t      SCOUNT_REG2;          /**< 0x0084: Sector Counter Preload Register2 >**/
    uint32_t      CURSEC_REG2;          /**< 0x0088: Current Sector Register 2>**/
    uint32_t      WDTOPLD2;             /**< 0x008C: Channel 2 Watchdog Timeout Preload Register A >**/
    uint32_t      BCTOPLD2;             /**< 0x0090: Channel 2 Block Complete Timeout Preload Register B >**/
    uint32_t      : 32U;                /**< 0x0094: reserved >**/
    uint32_t      : 32U;                /**< 0x0098: reserved >**/
    uint32_t      : 32U;                /**< 0x009C: reserved >**/    
    uint32_t      PSA_SIGREGL2;         /**< 0x00A0: Channel 2 PSA signature low register >**/
    uint32_t      PSA_SIGREGH2;         /**< 0x00A8: Channel 2 PSA signature high register >**/
    uint32_t      REGL2;                /**< 0x00AC: Channel 2 CRC value low register >**/
    uint32_t      REGH2;                /**< 0x00AC: Channel 2 CRC value high register >**/
    uint32_t      PSA_SECSIGREGL2;      /**< 0x00B0: Channel 2 PSA sector signature low register >**/
    uint32_t      PSA_SECSIGREGH2;      /**< 0x00B4: Channel 2 PSA sector signature high register >**/
    uint32_t      RAW_DATAREGL2;        /**< 0x00B8: Channel 2 Raw Data Low Register >**/
    uint32_t      RAW_DATAREGH2;        /**< 0x00BC: Channel 2 Raw Data High Register >**/
}crcBASE_t;
 
/** @def crcREG
*   @brief CRC Register Frame Pointer
*
*   This pointer is used by the CRC driver to access the CRC registers.
*/
#define crcREG ((crcBASE_t *)0xFE000000U)

/* USER CODE BEGIN (1) */
/* USER CODE END */

/* CRC Interface Functions */
void crcInit(void);
void crcSendPowerDown(crcBASE_t *crc);
void crcSignGen(crcBASE_t *crc,crcModConfig_t *param);
void crcSetConfig(crcBASE_t *crc,crcConfig_t *param);
uint64_t crcGetSectorSig(crcBASE_t *crc,uint32_t channel);
uint32_t crcGetFailedSector(crcBASE_t *crc,uint32_t channel);
uint32_t crcGetIntrPend(crcBASE_t *crc,uint32_t channel);
void crcChannelReset(crcBASE_t *crc,uint32_t channel);
void crcEnableNotification(crcBASE_t *crc, uint32_t flags);
void crcDisableNotification(crcBASE_t *crc, uint32_t flags);

/** @fn void crcNotification(crcBASE_t *crc, uint32_t flags)
*   @brief Interrupt callback
*   @param[in] crc   - crc module base address
*   @param[in] flags - copy of error interrupt flags
*
* This is a callback that is provided by the application and is called upon
* an interrupt.  The parameter passed to the callback is a copy of the 
* interrupt flag register.
*/
void crcNotification(crcBASE_t *crc, uint32_t flags);



/* USER CODE BEGIN (2) */
/* USER CODE END */

#endif
