/** @file notification.c 
*   @brief User Notification Definition File
*   @date 15.Jun.2012
*   @version 03.01.02
*
*   This file  defines  empty  notification  routines to avoid
*   linker errors, Driver expects user to define the notification. 
*   The user needs to either remove this file and use their custom 
*   notification function or place their code sequence in this file 
*   between the provided USER CODE BEGIN and USER CODE END.
*
*/

/* Include Files */

#include "esm.h"
#include "sys_selftest.h"
#include "gio.h"
#include "rti.h"
#include "eqep.h"
/* USER CODE BEGIN (0) */
/* USER CODE END */

void esmGroup1Notification(uint32_t channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (1) */
/* USER CODE END */
}

/* USER CODE BEGIN (2) */
/* USER CODE END */

void esmGroup2Notification(uint32_t channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (3) */
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */

void memoryPort0TestFailNotification(uint32_t groupSelect, uint32_t dataSelect, uint32_t address, uint32_t data)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (5) */
/* USER CODE END */
}

/* USER CODE BEGIN (6) */
/* USER CODE END */

void memoryPort1TestFailNotification(uint32_t groupSelect, uint32_t dataSelect, uint32_t address, uint32_t data)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (7) */
/* USER CODE END */
}

/* USER CODE BEGIN (8) */
/* USER CODE END */
void rtiNotification(uint32_t notification)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (9) */
/* USER CODE END */
}

/* USER CODE BEGIN (10) */
/* USER CODE END */
void gioNotification(uint32_t bit)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (19) */
/* USER CODE END */
}

/* USER CODE BEGIN (20) */
/* USER CODE END */




/* USER CODE BEGIN (43) */
/* USER CODE END */


/* USER CODE BEGIN (47) */
/* USER CODE END */

void eqepNotification(eqepBASE_t *node,uint16_t flags)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (48) */
/* USER CODE END */
}
/* USER CODE BEGIN (49) */
/* USER CODE END */

/* USER CODE BEGIN (50) */
/* USER CODE END */


/* USER CODE BEGIN (53) */
/* USER CODE END */
