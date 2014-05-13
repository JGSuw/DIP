//*----------------------------------------------------------------------------*/
/* sys_link.cmd                                                               */
/*                                                                            */
/* (c) Texas Instruments 2009-2010, All rights reserved.                      */
/*                                                                            */


/* USER CODE BEGIN (0) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */

--retain="*(.intvecs)"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */

MEMORY
{
    VECTORS (RX) : origin=0x00000000 length=0x00000100 fill=0xFFFFFFFF
    EMIF_1  (RX) : origin=0x60000000 length=0x00000100
    FLASH   (RX) : origin=0x00000100 length=0x0003FF00 fill=0xFFFFFFFF
    EMIF_2  (RX) : origin=0x60000100 length=0x00003F00
    STACKS  (RW) : origin=0x08000000 length=0x00001500
    RAM     (RW) : origin=0x08001500 length=0x00018000



/* USER CODE BEGIN (1) */
/* USER CODE END */
}

SECTIONS
{
    .intvecs : {} > VECTORS 
	.text	 : {} > FLASH   
    .const   : {} > FLASH   
    .cinit   : {} > FLASH   
    .pinit   : {} > FLASH   
    .bss     : {} > RAM
    .data    : {} > RAM

/* USER CODE BEGIN (2) */
    .sysmem : {} > RAM
/* USER CODE END */
}


/*----------------------------------------------------------------------------*/

