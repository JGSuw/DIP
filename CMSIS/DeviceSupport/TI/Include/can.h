/** @file can.h
*   @brief CAN Driver Header File
*   @date 15.January.2012
*   @version 03.00.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the CAN driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#include "sys_common.h"

#ifndef __CAN_H__
#define __CAN_H__

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* CAN General Definitions */

/** @def CANLEVEL_ACTIVE
*   @brief Alias name for CAN error operation level active (Error couter 0-95)  
*/
#define CANLEVEL_ACTIVE 0x00U

/** @def CANLEVEL_WARNING
*   @brief Alias name for CAN error operation level warning (Error couter 96-127)  
*/
#define CANLEVEL_WARNING 0x40U

/** @def CANLEVEL_PASSIVE
*   @brief Alias name for CAN error operation level passive (Error couter 128-255)  
*/
#define CANLEVEL_PASSIVE 0x20U

/** @def CANLEVEL_BUS_OFF
*   @brief Alias name for CAN error operation level bus off (Error couter 256)  
*/
#define CANLEVEL_BUS_OFF 0x80U

/** @def CANERROR_NO
*   @brief Alias name for no CAN error occured 
*/
#define CANERROR_OK 0U

/** @def CANERROR_STUFF
*   @brief Alias name for CAN stuff error an RX message 
*/
#define CANERROR_STUFF 1U

/** @def CANERROR_FORMAT
*   @brief Alias name for CAN form/format error an RX message 
*/
#define CANERROR_FORMAT 2U

/** @def CANERROR_ACKNOWLEDGE
*   @brief Alias name for CAN TX message wasn't acknowledged  
*/
#define CANERROR_ACKNOWLEDGE 3U

/** @def CANERROR_BIT1
*   @brief Alias name for CAN TX message sendig recessive level but monitoring dominant  
*/
#define CANERROR_BIT1 4U

/** @def CANERROR_BIT0
*   @brief Alias name for CAN TX message sendig dominant level but monitoring recessive  
*/
#define CANERROR_BIT0 5U

/** @def CANERROR_CRC
*   @brief Alias name for CAN RX message received wrong CRC  
*/
#define CANERROR_CRC 6U

/** @def CANERROR_NO
*   @brief Alias name for CAN no message has send or received sinced last call of CANGetLastError  
*/
#define CANERROR_NO 7U

/** @def CANMESSAGE_BOX1
*   @brief Alias name for CAN message box 1
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX1 1U

/** @def CANMESSAGE_BOX2
*   @brief Alias name for CAN message box 2
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX2 2U

/** @def CANMESSAGE_BOX3
*   @brief Alias name for CAN message box 3
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX3 3U

/** @def CANMESSAGE_BOX4
*   @brief Alias name for CAN message box 4
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX4 4U

/** @def CANMESSAGE_BOX5
*   @brief Alias name for CAN message box 5
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX5 5U

/** @def CANMESSAGE_BOX6
*   @brief Alias name for CAN message box 6
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX6 6U

/** @def CANMESSAGE_BOX7
*   @brief Alias name for CAN message box 7
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX7 7U

/** @def CANMESSAGE_BOX8
*   @brief Alias name for CAN message box 8
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX8 8U

/** @def CANMESSAGE_BOX9
*   @brief Alias name for CAN message box 9
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX9 9U

/** @def CANMESSAGE_BOX10
*   @brief Alias name for CAN message box 10
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX10 10U

/** @def CANMESSAGE_BOX11
*   @brief Alias name for CAN message box 11
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX11 11U

/** @def CANMESSAGE_BOX12
*   @brief Alias name for CAN message box 12
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX12 12U

/** @def CANMESSAGE_BOX13
*   @brief Alias name for CAN message box 13
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX13 13U

/** @def CANMESSAGE_BOX14
*   @brief Alias name for CAN message box 14
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX14 14U

/** @def CANMESSAGE_BOX15
*   @brief Alias name for CAN message box 15
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX15 15U

/** @def CANMESSAGE_BOX16
*   @brief Alias name for CAN message box 16
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX16 16U

/** @def CANMESSAGE_BOX17
*   @brief Alias name for CAN message box 17
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX17 17U

/** @def CANMESSAGE_BOX18
*   @brief Alias name for CAN message box 18
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX18 18U

/** @def CANMESSAGE_BOX19
*   @brief Alias name for CAN message box 19
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX19 19U

/** @def CANMESSAGE_BOX20
*   @brief Alias name for CAN message box 20
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX20 20U

/** @def CANMESSAGE_BOX21
*   @brief Alias name for CAN message box 21
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX21 21U

/** @def CANMESSAGE_BOX22
*   @brief Alias name for CAN message box 22
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX22 22U

/** @def CANMESSAGE_BOX23
*   @brief Alias name for CAN message box 23
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX23 23U

/** @def CANMESSAGE_BOX24
*   @brief Alias name for CAN message box 24
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX24 24U

/** @def CANMESSAGE_BOX25
*   @brief Alias name for CAN message box 25
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX25 25U

/** @def CANMESSAGE_BOX26
*   @brief Alias name for CAN message box 26
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX26 26U

/** @def CANMESSAGE_BOX27
*   @brief Alias name for CAN message box 27
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX27 27U

/** @def CANMESSAGE_BOX28
*   @brief Alias name for CAN message box 28
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX28 28U

/** @def CANMESSAGE_BOX29
*   @brief Alias name for CAN message box 29
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX29 29U

/** @def CANMESSAGE_BOX30
*   @brief Alias name for CAN message box 30
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX30 30U

/** @def CANMESSAGE_BOX31
*   @brief Alias name for CAN message box 31
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX31 31U

/** @def CANMESSAGE_BOX32
*   @brief Alias name for CAN message box 32
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX32 32U

/** @def CANMESSAGE_BOX33
*   @brief Alias name for CAN message box 33
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX33 33U

/** @def CANMESSAGE_BOX34
*   @brief Alias name for CAN message box 34
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX34 34U

/** @def CANMESSAGE_BOX35
*   @brief Alias name for CAN message box 35
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX35 35U

/** @def CANMESSAGE_BOX36
*   @brief Alias name for CAN message box 36
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX36 36U

/** @def CANMESSAGE_BOX37
*   @brief Alias name for CAN message box 37
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX37 37U

/** @def CANMESSAGE_BOX38
*   @brief Alias name for CAN message box 38
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX38 38U

/** @def CANMESSAGE_BOX39
*   @brief Alias name for CAN message box 39
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX39 39U

/** @def CANMESSAGE_BOX40
*   @brief Alias name for CAN message box 40
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX40 40U

/** @def CANMESSAGE_BOX41
*   @brief Alias name for CAN message box 41
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX41 41U

/** @def CANMESSAGE_BOX42
*   @brief Alias name for CAN message box 42
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX42 42U

/** @def CANMESSAGE_BOX43
*   @brief Alias name for CAN message box 43
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX43 43U

/** @def CANMESSAGE_BOX44
*   @brief Alias name for CAN message box 44
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX44 44U

/** @def CANMESSAGE_BOX45
*   @brief Alias name for CAN message box 45
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX45 45U

/** @def CANMESSAGE_BOX46
*   @brief Alias name for CAN message box 46
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX46 46U

/** @def CANMESSAGE_BOX47
*   @brief Alias name for CAN message box 47
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX47 47U

/** @def CANMESSAGE_BOX48
*   @brief Alias name for CAN message box 48
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX48 48U

/** @def CANMESSAGE_BOX49
*   @brief Alias name for CAN message box 49
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX49 49U

/** @def CANMESSAGE_BOX50
*   @brief Alias name for CAN message box 50
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX50 50U

/** @def CANMESSAGE_BOX51
*   @brief Alias name for CAN message box 51
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX51 51U

/** @def CANMESSAGE_BOX52
*   @brief Alias name for CAN message box 52
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX52 52U

/** @def CANMESSAGE_BOX53
*   @brief Alias name for CAN message box 53
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX53 53U

/** @def CANMESSAGE_BOX54
*   @brief Alias name for CAN message box 54
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX54 54U

/** @def CANMESSAGE_BOX55
*   @brief Alias name for CAN message box 55
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX55 55U

/** @def CANMESSAGE_BOX56
*   @brief Alias name for CAN message box 56
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX56 56U

/** @def CANMESSAGE_BOX57
*   @brief Alias name for CAN message box 57
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX57 57U

/** @def CANMESSAGE_BOX58
*   @brief Alias name for CAN message box 58
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX58 58U

/** @def CANMESSAGE_BOX59
*   @brief Alias name for CAN message box 59
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX59 59U

/** @def CANMESSAGE_BOX60
*   @brief Alias name for CAN message box 60
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX60 60U

/** @def CANMESSAGE_BOX61
*   @brief Alias name for CAN message box 61
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX61 61U

/** @def CANMESSAGE_BOX62
*   @brief Alias name for CAN message box 62
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX62 62U

/** @def CANMESSAGE_BOX63
*   @brief Alias name for CAN message box 63
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX63 63U

/** @def CANMESSAGE_BOX64
*   @brief Alias name for CAN message box 64
*
*   @note This value should be used for API argument @a messageBox
*/
#define CANMESSAGE_BOX64 64U

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @struct CANBase
*   @brief CAN Register Frame Definition
*
*   This type is used to access the CAN Registers.
*/
/** @typedef canBASE_t
*   @brief CAN Register Frame Type Definition
*
*   This type is used to access the CAN Registers.
*/
typedef volatile struct CANBase
{
    uint32_t      CTL;          /**< 0x0000: Control Register                       */
    uint32_t      ES;           /**< 0x0004: Error and Status Register              */
    uint32_t      EERC;         /**< 0x0008: Error Counter Register                 */
    uint32_t      BTR;          /**< 0x000C: Bit Timing Register                    */
    uint32_t      INT;          /**< 0x0010: Interrupt Register                     */
    uint32_t      TEST;         /**< 0x0014: Test Register                          */
    uint32_t      : 32U;        /**< 0x0018: Reserved                               */
    uint32_t      PERR;         /**< 0x001C: Parity/SECDED Error Code Register      */
    uint32_t      REL;          /**< 0x0020: Core Release Register                  */
    uint32_t      ECCDIAG;      /**< 0x0024: ECC Diagnostic Register                */
    uint32_t      ECCDIADSTAT;  /**< 0x0028: ECC Diagnostic Status Register         */
    uint32_t      : 32U;        /**< 0x002C: Reserved                               */
    uint32_t      : 32U;        /**< 0x0030: Reserved                               */
    uint32_t      : 32U;        /**< 0x0034: Reserved                               */
    uint32_t      : 32U;        /**< 0x0038: Reserved                               */
    uint32_t      : 32U;        /**< 0x003C: Reserved                               */
    uint32_t      : 32U;        /**< 0x0040: Reserved                               */
    uint32_t      : 32U;        /**< 0x0044: Reserved                               */
    uint32_t      : 32U;        /**< 0x0048: Reserved                               */
    uint32_t      : 32U;        /**< 0x004C: Reserved                               */
    uint32_t      : 32U;        /**< 0x0050: Reserved                               */
    uint32_t      : 32U;        /**< 0x0054: Reserved                               */
    uint32_t      : 32U;        /**< 0x0058: Reserved                               */
    uint32_t      : 32U;        /**< 0x005C: Reserved                               */
    uint32_t      : 32U;        /**< 0x0060: Reserved                               */
    uint32_t      : 32U;        /**< 0x0064: Reserved                               */
    uint32_t      : 32U;        /**< 0x0068: Reserved                               */
    uint32_t      : 32U;        /**< 0x006C: Reserved                               */
    uint32_t      : 32U;        /**< 0x0070: Reserved                               */
    uint32_t      : 32U;        /**< 0x0074: Reserved                               */
    uint32_t      : 32U;        /**< 0x0078: Reserved                               */
    uint32_t      : 32U;        /**< 0x007C: Reserved                               */
    uint32_t      ABOTR;        /**< 0x0080: Auto Bus On Time Register              */
    uint32_t      TXRQX;        /**< 0x0084: Transmission Request X Register        */
    uint32_t      TXRQx[4U];    /**< 0x0088-0x0094: Transmission Request Registers  */
    uint32_t      NWDATX;       /**< 0x0098: New Data X Register                    */
    uint32_t      NWDATx[4U];   /**< 0x009C-0x00A8: New Data Registers              */
    uint32_t      INTPNDX;      /**< 0x00AC: Interrupt Pending X Register           */
    uint32_t      INTPNDx[4U];  /**< 0x00B0-0x00BC: Interrupt Pending Registers     */
    uint32_t      MSGVALX;      /**< 0x00C0: Message Valid X Register               */
    uint32_t      MSGVALx[4U];  /**< 0x00C4-0x00D0: Message Valid Registers         */
    uint32_t      : 32U;        /**< 0x00D4: Reserved                               */
    uint32_t      INTMUXx[4U];  /**< 0x00D8-0x00E4: Interrupt Multiplexer Registers */
    uint32_t      : 32U;        /**< 0x00E8: Reserved                               */
    uint32_t      : 32U;        /**< 0x00EC: Reserved                               */
    uint32_t      : 32U;        /**< 0x00F0: Reserved                               */
    uint32_t      : 32U;        /**< 0x00F4: Reserved                               */
    uint32_t      : 32U;        /**< 0x00F8: Reserved                               */
    uint32_t      : 32U;        /**< 0x00FC: Reserved                               */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint8_t IF1NO;              /**< 0x0100: IF1 Command Register, Msg Number       */
    uint8_t IF1STAT;            /**< 0x0100: IF1 Command Register, Status           */
    uint8_t IF1CMD;             /**< 0x0100: IF1 Command Register, Command          */
    uint32_t      : 8U;         /**< 0x0100: IF1 Command Register, Reserved         */
#else
    uint32_t      : 8U;         /**< 0x0100: IF1 Command Register, Reserved         */
    uint8_t IF1CMD;             /**< 0x0100: IF1 Command Register, Command          */
    uint8_t IF1STAT;            /**< 0x0100: IF1 Command Register, Status           */
    uint8_t IF1NO;              /**< 0x0100: IF1 Command Register, Msg Number       */
#endif
    uint32_t      IF1MSK;       /**< 0x0104: IF1 Mask Register                      */
    uint32_t      IF1ARB;       /**< 0x0108: IF1 Arbitration Register               */
    uint32_t      IF1MCTL;      /**< 0x010C: IF1 Message Control Register           */
    uint8_t IF1DATx[8U];        /**< 0x0110-0x0114: IF1 Data A and B Registers      */
    uint32_t      : 32U;        /**< 0x0118: Reserved                               */
    uint32_t      : 32U;        /**< 0x011C: Reserved                               */
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
    uint8_t IF2NO;              /**< 0x0120: IF2 Command Register, Msg No           */
    uint8_t IF2STAT;            /**< 0x0120: IF2 Command Register, Status           */
    uint8_t IF2CMD;             /**< 0x0120: IF2 Command Register, Command          */
    uint32_t      : 8U;         /**< 0x0120: IF2 Command Register, Reserved         */
#else
    uint32_t      : 8U;         /**< 0x0120: IF2 Command Register, Reserved         */
    uint8_t IF2CMD;             /**< 0x0120: IF2 Command Register, Command          */
    uint8_t IF2STAT;            /**< 0x0120: IF2 Command Register, Status           */
    uint8_t IF2NO;              /**< 0x0120: IF2 Command Register, Msg Number       */
#endif
    uint32_t      IF2MSK;       /**< 0x0124: IF2 Mask Register                      */
    uint32_t      IF2ARB;       /**< 0x0128: IF2 Arbitration Register               */
    uint32_t      IF2MCTL;      /**< 0x012C: IF2 Message Control Register           */
    uint8_t IF2DATx[8U];        /**< 0x0130-0x0134: IF2 Data A and B Registers      */
    uint32_t      : 32U;        /**< 0x0138: Reserved                               */
    uint32_t      : 32U;        /**< 0x013C: Reserved                               */
    uint32_t      IF3OBS;       /**< 0x0140: IF3 Observation Register               */
    uint32_t      IF3MSK;       /**< 0x0144: IF3 Mask Register                      */
    uint32_t      IF3ARB;       /**< 0x0148: IF3 Arbitration Register               */
    uint32_t      IF3MCTL;      /**< 0x014C: IF3 Message Control Register           */
    uint8_t IF3DATx[8U];        /**< 0x0150-0x0154: IF3 Data A and B Registers      */
    uint32_t      : 32U;        /**< 0x0158: Reserved                               */
    uint32_t      : 32U;        /**< 0x015C: Reserved                               */
    uint32_t      IF3UEy[4U];   /**< 0x0160-0x016C: IF3 Update Enable Registers     */
    uint32_t      : 32U;        /**< 0x0170: Reserved                               */
    uint32_t      : 32U;        /**< 0x0174: Reserved                               */
    uint32_t      : 32U;        /**< 0x0178: Reserved                               */
    uint32_t      : 32U;        /**< 0x017C: Reserved                               */
    uint32_t      : 32U;        /**< 0x0180: Reserved                               */
    uint32_t      : 32U;        /**< 0x0184: Reserved                               */
    uint32_t      : 32U;        /**< 0x0188: Reserved                               */
    uint32_t      : 32U;        /**< 0x018C: Reserved                               */
    uint32_t      : 32U;        /**< 0x0190: Reserved                               */
    uint32_t      : 32U;        /**< 0x0194: Reserved                               */
    uint32_t      : 32U;        /**< 0x0198: Reserved                               */
    uint32_t      : 32U;        /**< 0x019C: Reserved                               */
    uint32_t      : 32U;        /**< 0x01A0: Reserved                               */
    uint32_t      : 32U;        /**< 0x01A4: Reserved                               */
    uint32_t      : 32U;        /**< 0x01A8: Reserved                               */
    uint32_t      : 32U;        /**< 0x01AC: Reserved                               */
    uint32_t      : 32U;        /**< 0x01B0: Reserved                               */
    uint32_t      : 32U;        /**< 0x01B4: Reserved                               */
    uint32_t      : 32U;        /**< 0x01B8: Reserved                               */
    uint32_t      : 32U;        /**< 0x01BC: Reserved                               */
    uint32_t      : 32U;        /**< 0x01C0: Reserved                               */
    uint32_t      : 32U;        /**< 0x01C4: Reserved                               */
    uint32_t      : 32U;        /**< 0x01C8: Reserved                               */
    uint32_t      : 32U;        /**< 0x01CC: Reserved                               */
    uint32_t      : 32U;        /**< 0x01D0: Reserved                               */
    uint32_t      : 32U;        /**< 0x01D4: Reserved                               */
    uint32_t      : 32U;        /**< 0x01D8: Reserved                               */
    uint32_t      : 32U;        /**< 0x01DC: Reserved                               */
    uint32_t      TIOC;         /**< 0x01E0: TX IO Control Register                 */
    uint32_t      RIOC;         /**< 0x01E4: RX IO Control Register                 */
} canBASE_t;


/** @def canREG1
*   @brief CAN1 Register Frame Pointer
*
*   This pointer is used by the CAN driver to access the CAN1 registers.
*/
#define canREG1 ((canBASE_t *)0xFFF7DC00U)

/** @def canREG2
*   @brief CAN2 Register Frame Pointer
*
*   This pointer is used by the CAN driver to access the CAN2 registers.
*/
#define canREG2 ((canBASE_t *)0xFFF7DE00U)

/** @def canREG3
*   @brief CAN3 Register Frame Pointer
*
*   This pointer is used by the CAN driver to access the CAN3 registers.
*/
#define canREG3 ((canBASE_t *)0xFFF7E000U)

/* USER CODE BEGIN (2) */
/* USER CODE END */


/* CAN Interface Functions */

void     canInit(void);
uint32_t canTransmit(canBASE_t *node, uint32_t messageBox, const uint8_t *data);
uint32_t canGetData(canBASE_t *node, uint32_t messageBox, uint8_t * const data);
uint32_t canIsTxMessagePending(canBASE_t *node, uint32_t messageBox);
uint32_t canIsRxMessageArrived(canBASE_t *node, uint32_t messageBox);
uint32_t canIsMessageBoxValid(canBASE_t *node, uint32_t messageBox);
uint32_t canGetLastError(canBASE_t *node);
uint32_t canGetErrorLevel(canBASE_t *node);
void     canEnableErrorNotification(canBASE_t *node);
void     canDisableErrorNotification(canBASE_t *node);

/** @fn void canErrorNotification(canBASE_t *node, uint32_t notification)
*   @brief Error notification
*   @param[in] node Pointer to CAN node:
*              - canREG1: CAN1 node pointer
*              - canREG2: CAN2 node pointer
*              - canREG3: CAN3 node pointer
*   @param[in] notification Error notification code:
*           - CANLEVEL_WARNING (0x40): When RX- or TX error counter are between 96 and 127     
*           - CANLEVEL_BUS_OFF (0x80): When RX- or TX error counter are above 255     
*
*   @note This function has to be provide by the user.
*/
void canErrorNotification(canBASE_t *node, uint32_t notification);

/** @fn void canMessageNotification(canBASE_t *node, uint32_t messageBox)
*   @brief Message notification
*   @param[in] node Pointer to CAN node:
*              - canREG1: CAN1 node pointer
*              - canREG2: CAN2 node pointer
*              - canREG3: CAN3 node pointer
*   @param[in] messageBox Message box number of CAN node:
*              - CANMESSAGE_BOX1: CAN message box 1
*              - CANMESSAGE_BOXn: CAN message box n [n: 1-64]
*              - CANMESSAGE_BOX64: CAN message box 64
*
*   @note This function has to be provide by the user.
*/
void canMessageNotification(canBASE_t *node, uint32_t messageBox);

/* USER CODE BEGIN (3) */
/* USER CODE END */


#endif
