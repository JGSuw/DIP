/** @file sys_pmu.h
*   @brief System Pmu Header File
*   @date 15.Mar.2012
*   @version 03.01.00
*   
*   This file contains:
*   - Pmu Interface Functions
*   .
*   which are relevant for the performance monitor unit driver.
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#ifndef __SYS_PMU_H__
#define __SYS_PMU_H__

#include "sys_common.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */

/** @def pmuCOUNTER0
*   @brief pmu event counter 0
*
*   Alias for pmu event counter 0
*/
#define pmuCOUNTER0 0x00000001U

/** @def pmuCOUNTER1
*   @brief pmu event counter 1
*
*   Alias for pmu event counter 1
*/
#define pmuCOUNTER1 0x00000002U

/** @def pmuCOUNTER2
*   @brief pmu event counter 2
*
*   Alias for pmu event counter 2
*/
#define pmuCOUNTER2 0x00000004U

/** @def pmuCYCLE_COUNTER
*   @brief pmu cycle counter
*
*   Alias for pmu event counter
*/
#define pmuCYCLE_COUNTER 0x80000000U

/** @enum pmuEvent
*   @brief pmu event
*
*   Alias for pmu event counter increment source
*/
enum pmuEvent
{
    PMU_INST_CACHE_MISS                     = 0x01,
    PMU_DATA_CACHE_MISS                     = 0x03,
    PMU_DATA_CACHE_ACCESS                   = 0x04,
    PMU_DATA_READ_ARCH_EXECUTED             = 0x06,
    PMU_DATA_WRITE_ARCH_EXECUTED            = 0x07,
    PMU_INST_ARCH_EXECUTED                  = 0x08,
    PMU_EXCEPTION_TAKEN                     = 0x09,
    PMU_EXCEPTION_RETURN_ARCH_EXECUTED      = 0x0A,
    PMU_CHANGE_TO_CONTEXT_ID_EXECUTED       = 0x0B,
    PMU_SW_CHANGE_OF_PC_ARCH_EXECUTED       = 0x0C,
    PMU_BRANCH_IMM_INST_ARCH_EXECUTED       = 0x0D,
    PMU_PROC_RETURN_ARCH_EXECUTED           = 0x0E,
    PMU_UNALIGNED_ACCESS_ARCH_EXECUTED      = 0x0F,
    PMU_BRANCH_MISSPREDICTED                = 0x10,
    PMU_CYCLE_COUNT                         = 0x11,
    PMU_PREDICTABLE_BRANCHES                = 0x12,
    PMU_INST_BUFFER_STALL                   = 0x40,
    PMU_DATA_DEPENDENCY_INST_STALL          = 0x41,
    PMU_DATA_CACHE_WRITE_BACK               = 0x42,
    PMU_EXT_MEMORY_REQUEST                  = 0x43,
    PMU_LSU_BUSY_STALL                      = 0x44,
    PMU_FORCED_DRAIN_OFSTORE_BUFFER         = 0x45,
    PMU_FIQ_DISABLED_CYCLE_COUNT            = 0x46,
    PMU_IRQ_DISABLED_CYCLE_COUNT            = 0x47,
    PMU_ETMEXTOUT_0                         = 0x48,
    PMU_ETMEXTOUT_1                         = 0x49,
    PMU_INST_CACHE_TAG_ECC_ERROR            = 0x4A,
    PMU_INST_CACHE_DATA_ECC_ERROR           = 0x4B,
    PMU_DATA_CACHE_TAG_ECC_ERROR            = 0x4C,
    PMU_DATA_CACHE_DATA_ECC_ERROR           = 0x4D,
    PMU_TCM_FATAL_ECC_ERROR_PREFETCH        = 0x4E,
    PMU_TCM_FATAL_ECC_ERROR_LOAD_STORE      = 0x4F,
    PMU_STORE_BUFFER_MERGE                  = 0x50,
    PMU_LSU_STALL_STORE_BUFFER_FULL         = 0x51,
    PMU_LSU_STALL_STORE_QUEUE_FULL          = 0x52,
    PMU_INTEGER_DIV_EXECUTED                = 0x53,
    PMU_STALL_INTEGER_DIV                   = 0x54,
    PMU_PLD_INST_LINE_FILL                  = 0x55,
    PMU_PLD_INST_NO_LINE_FILL               = 0x56,
    PMU_NON_CACHEABLE_ACCESS_AXI_MASTER     = 0x57,
    PMU_INST_CACHE_ACCESS                   = 0x58,
    PMU_DOUBLE_DATA_CACHE_ISSUE             = 0x59,
    PMU_DUAL_ISSUE_CASE_A                   = 0x5A,
    PMU_DUAL_ISSUE_CASE_B1_B2_F2_F2D        = 0x5B,
    PMU_DUAL_ISSUE_OTHER                    = 0x5C,
    PMU_DP_FLOAT_INST_EXCECUTED             = 0x5D,
    PMU_DUAL_ISSUED_PAIR_INST_ARCH_EXECUTED = 0x5E,
    PMU_DATA_CACHE_DATA_FATAL_ECC_ERROR     = 0x60,
    PMU_DATA_CACHE_TAG_FATAL_ECC_ERROR      = 0x61,
    PMU_PROCESSOR_LIVE_LOCK                 = 0x62,
    PMU_ATCM_MULTI_BIT_ECC_ERROR            = 0x64,
    PMU_B0TCM_MULTI_BIT_ECC_ERROR           = 0x65,
    PMU_B1TCM_MULTI_BIT_ECC_ERROR           = 0x66,
    PMU_ATCM_SINGLE_BIT_ECC_ERROR           = 0x67,
    PMU_B0TCM_SINGLE_BIT_ECC_ERROR          = 0x68,
    PMU_B1TCM_SINGLE_BIT_ECC_ERROR          = 0x69,
    PMU_TCM_COR_ECC_ERROR_LOAD_STORE        = 0x6A,
    PMU_TCM_COR_ECC_ERROR_PREFETCH          = 0x6B,
    PMU_TCM_FATAL_ECC_ERROR_AXI_SLAVE       = 0x6C,
    PMU_TCM_COR_ECC_ERROR_AXI_SLAVE         = 0x6D
};

/** @fn void _pmuInit_(void)
*   @brief Initialize Performance Monitor Unit
*/
void _pmuInit_(void);

/** @fn void _pmuEnableCountersGlobal_(void)
*   @brief Enable and reset cycle counter and all 3 event counters
*/
void _pmuEnableCountersGlobal_(void);

/** @fn void _pmuDisableCountersGlobal_(void)
*   @brief Disable cycle counter and all 3 event counters
*/
void _pmuDisableCountersGlobal_(void);

/** @fn void _pmuResetCycleCounter_(void)
*   @brief Reset cycle counter
*/
void _pmuResetCycleCounter_(void);

/** @fn void _pmuResetEventCounters_(void)
*   @brief Reset event counters 0-2
*/
void _pmuResetEventCounters_(void);

/** @fn void _pmuResetCounters_(void)
*   @brief Reset cycle counter and event counters 0-2
*/
void _pmuResetCounters_(void);

/** @fn void _pmuStartCounters_(uint32_t counters)
*   @brief Starts selected counters
*   @param[in] counters - Counter mask
*/
void _pmuStartCounters_(uint32_t counters);

/** @fn void _pmuStopCounters_(uint32_t counters)
*   @brief Stops selected counters
*   @param[in] counters - Counter mask
*/
void _pmuStopCounters_(uint32_t counters);

/** @fn void _pmuSetCountEvent_(uint32_t counter, uint32_t event)
*   @brief Set event counter count event
*   @param[in] counter - Counter select 0..2
*   @param[in] event   - Count event
*/
void _pmuSetCountEvent_(uint32_t counter, uint32_t event);

/** @fn uint32_t _pmuGetCycleCount_(void)
*   @brief Returns current cycle counter value
*
*   @return cycle count.
*/
uint32_t _pmuGetCycleCount_(void);

/** @fn uint32_t _pmuGetEventCount_(uint32_t counter)
*   @brief Returns current event counter value
*   @param[in] counter - Counter select 0..2
*
*   @return event counter count.
*/
uint32_t _pmuGetEventCount_(uint32_t counter);

/** @fn uint32_t _pmuGetOverflow_(void)
*   @brief Returns current overflow register and clear flags
*
*   @return overflow flags.
*/
uint32_t _pmuGetOverflow_(void);


#endif
