/** @file pinmux.h 
*   @brief PINMUX Driver Implementation File
*   @date 15.Mar.2012
*   @version 03.01.00
*
*/

/* (c) Texas Instruments 2009-2012, All rights reserved. */

#include "sys_common.h"

#ifndef __PINMUX_H__
#define __PINMUX_H__

#define PINMUX_BALL_A4_SHIFT    0
#define PINMUX_BALL_A5_SHIFT    8
#define PINMUX_BALL_A11_SHIFT   8
#define PINMUX_BALL_A14_SHIFT   0
#define PINMUX_BALL_B2_SHIFT    24
#define PINMUX_BALL_B3_SHIFT    8
#define PINMUX_BALL_B4_SHIFT    16
#define PINMUX_BALL_B5_SHIFT    24
#define PINMUX_BALL_B11_SHIFT   8
#define PINMUX_BALL_B12_SHIFT   0
#define PINMUX_BALL_C1_SHIFT    0
#define PINMUX_BALL_C2_SHIFT    0
#define PINMUX_BALL_C3_SHIFT    16
#define PINMUX_BALL_C4_SHIFT    16
#define PINMUX_BALL_C5_SHIFT    8
#define PINMUX_BALL_C6_SHIFT    0
#define PINMUX_BALL_D3_SHIFT    0
#define PINMUX_BALL_D4_SHIFT    0
#define PINMUX_BALL_D5_SHIFT    0
#define PINMUX_BALL_D16_SHIFT   24
#define PINMUX_BALL_D17_SHIFT   16
#define PINMUX_BALL_D19_SHIFT   0
#define PINMUX_BALL_E1_SHIFT    16
#define PINMUX_BALL_E3_SHIFT    8
#define PINMUX_BALL_E18_SHIFT   0
#define PINMUX_BALL_E19_SHIFT   0
#define PINMUX_BALL_F3_SHIFT    16
#define PINMUX_BALL_G3_SHIFT    8
#define PINMUX_BALL_G19_SHIFT   16
#define PINMUX_BALL_H3_SHIFT    16
#define PINMUX_BALL_H18_SHIFT   24
#define PINMUX_BALL_H19_SHIFT   16
#define PINMUX_BALL_J1_SHIFT    8
#define PINMUX_BALL_J3_SHIFT    24
#define PINMUX_BALL_J18_SHIFT   0
#define PINMUX_BALL_J19_SHIFT   8
#define PINMUX_BALL_K2_SHIFT    8
#define PINMUX_BALL_K17_SHIFT   0
#define PINMUX_BALL_K18_SHIFT   0
#define PINMUX_BALL_K19_SHIFT   8
#define PINMUX_BALL_M1_SHIFT    0
#define PINMUX_BALL_M2_SHIFT    24
#define PINMUX_BALL_N1_SHIFT    16
#define PINMUX_BALL_N2_SHIFT    0
#define PINMUX_BALL_N17_SHIFT   16
#define PINMUX_BALL_N19_SHIFT   0
#define PINMUX_BALL_P1_SHIFT    24
#define PINMUX_BALL_P2_SHIFT    16
#define PINMUX_BALL_R2_SHIFT    24
#define PINMUX_BALL_T1_SHIFT    0
#define PINMUX_BALL_U1_SHIFT    24
#define PINMUX_BALL_V2_SHIFT    16
#define PINMUX_BALL_V5_SHIFT    8
#define PINMUX_BALL_V6_SHIFT    16
#define PINMUX_BALL_V7_SHIFT    16
#define PINMUX_BALL_V8_SHIFT    8
#define PINMUX_BALL_V9_SHIFT    24
#define PINMUX_BALL_V10_SHIFT   16
#define PINMUX_BALL_W3_SHIFT    16
#define PINMUX_BALL_W5_SHIFT    8
#define PINMUX_BALL_W8_SHIFT    16
#define PINMUX_BALL_W9_SHIFT    8
#define PINMUX_BALL_W10_SHIFT   0

#define PINMUX_GATE_EMIF_CLK_SHIFT              8
#define PINMUX_GIOB_DISABLE_HET2_SHIFT          16
#define PINMUX_ALT_ADC_TRIGGER_SHIFT            0
#define PINMUX_ETHERNET_SHIFT                   24
#define PINMUX_ETPWM1_SHIFT                      0
#define PINMUX_ETPWM2_SHIFT                      8
#define PINMUX_ETPWM3_SHIFT                      16
#define PINMUX_ETPWM4_SHIFT                      24
#define PINMUX_ETPWM5_SHIFT                      0
#define PINMUX_ETPWM6_SHIFT                      8
#define PINMUX_ETPWM7_SHIFT                      16
#define PINMUX_ETPWM_TIME_BASE_SYNC_SHIFT         24
#define PINMUX_ETPWM_TBCLK_SYNC_SHIFT            0
#define PINMUX_TZ1_SHIFT                        16
#define PINMUX_TZ2_SHIFT                        24
#define PINMUX_TZ3_SHIFT                        0
#define PINMUX_EPWM1SYNCI_SHIFT                 8


#define PINMUX_BALL_A4_MASK             (~(0xFF << PINMUX_BALL_A4_SHIFT))
#define PINMUX_BALL_A5_MASK             (~(0xFF << PINMUX_BALL_A5_SHIFT))
#define PINMUX_BALL_A11_MASK            (~(0xFF << PINMUX_BALL_A11_SHIFT))
#define PINMUX_BALL_A14_MASK            (~(0xFF << PINMUX_BALL_A14_SHIFT))
#define PINMUX_BALL_B2_MASK             (~(0xFF << PINMUX_BALL_B2_SHIFT))
#define PINMUX_BALL_B3_MASK             (~(0xFF << PINMUX_BALL_B3_SHIFT))
#define PINMUX_BALL_B4_MASK             (~(0xFF << PINMUX_BALL_B4_SHIFT))
#define PINMUX_BALL_B5_MASK             (~(0xFF << PINMUX_BALL_B5_SHIFT))
#define PINMUX_BALL_B11_MASK            (~(0xFF << PINMUX_BALL_B11_SHIFT))
#define PINMUX_BALL_B12_MASK            (~(0xFF << PINMUX_BALL_B12_SHIFT))
#define PINMUX_BALL_C1_MASK             (~(0xFF << PINMUX_BALL_C1_SHIFT))
#define PINMUX_BALL_C2_MASK             (~(0xFF << PINMUX_BALL_C2_SHIFT))
#define PINMUX_BALL_C3_MASK             (~(0xFF << PINMUX_BALL_C3_SHIFT))
#define PINMUX_BALL_C4_MASK             (~(0xFF << PINMUX_BALL_C4_SHIFT))
#define PINMUX_BALL_C5_MASK             (~(0xFF << PINMUX_BALL_C5_SHIFT))
#define PINMUX_BALL_C6_MASK             (~(0xFF << PINMUX_BALL_C6_SHIFT))
#define PINMUX_BALL_D3_MASK             (~(0xFF << PINMUX_BALL_D3_SHIFT))
#define PINMUX_BALL_D4_MASK             (~(0xFF << PINMUX_BALL_D4_SHIFT))
#define PINMUX_BALL_D5_MASK             (~(0xFF << PINMUX_BALL_D5_SHIFT))
#define PINMUX_BALL_D16_MASK            (~(0xFF << PINMUX_BALL_D16_SHIFT))
#define PINMUX_BALL_D17_MASK            (~(0xFF << PINMUX_BALL_D17_SHIFT))
#define PINMUX_BALL_D19_MASK            (~(0xFF << PINMUX_BALL_D19_SHIFT))
#define PINMUX_BALL_E1_MASK             (~(0xFF << PINMUX_BALL_E1_SHIFT))
#define PINMUX_BALL_E3_MASK             (~(0xFF << PINMUX_BALL_E3_SHIFT))
#define PINMUX_BALL_E18_MASK            (~(0xFF << PINMUX_BALL_E18_SHIFT))
#define PINMUX_BALL_E19_MASK            (~(0xFF << PINMUX_BALL_E19_SHIFT))
#define PINMUX_BALL_F3_MASK             (~(0xFF << PINMUX_BALL_F3_SHIFT))
#define PINMUX_BALL_G3_MASK             (~(0xFF << PINMUX_BALL_G3_SHIFT))
#define PINMUX_BALL_G19_MASK            (~(0xFF << PINMUX_BALL_G19_SHIFT))
#define PINMUX_BALL_H3_MASK             (~(0xFF << PINMUX_BALL_H3_SHIFT))
#define PINMUX_BALL_H18_MASK            (~(0xFF << PINMUX_BALL_H18_SHIFT))
#define PINMUX_BALL_H19_MASK            (~(0xFF << PINMUX_BALL_H19_SHIFT))
#define PINMUX_BALL_J1_MASK             (~(0xFF << PINMUX_BALL_J1_SHIFT))
#define PINMUX_BALL_J3_MASK             (~(0xFF << PINMUX_BALL_J3_SHIFT))
#define PINMUX_BALL_J18_MASK            (~(0xFF << PINMUX_BALL_J18_SHIFT))
#define PINMUX_BALL_J19_MASK            (~(0xFF << PINMUX_BALL_J19_SHIFT))
#define PINMUX_BALL_K2_MASK             (~(0xFF << PINMUX_BALL_K2_SHIFT))
#define PINMUX_BALL_K17_MASK            (~(0xFF << PINMUX_BALL_K17_SHIFT))
#define PINMUX_BALL_K18_MASK            (~(0xFF << PINMUX_BALL_K18_SHIFT))
#define PINMUX_BALL_K19_MASK            (~(0xFF << PINMUX_BALL_K19_SHIFT))
#define PINMUX_BALL_M1_MASK             (~(0xFF << PINMUX_BALL_M1_SHIFT))
#define PINMUX_BALL_M2_MASK             (~(0xFF << PINMUX_BALL_M2_SHIFT))
#define PINMUX_BALL_N1_MASK             (~(0xFF << PINMUX_BALL_N1_SHIFT))
#define PINMUX_BALL_N2_MASK             (~(0xFF << PINMUX_BALL_N2_SHIFT))
#define PINMUX_BALL_N17_MASK            (~(0xFF << PINMUX_BALL_N17_SHIFT))
#define PINMUX_BALL_N19_MASK            (~(0xFF << PINMUX_BALL_N19_SHIFT))
#define PINMUX_BALL_P1_MASK             (~(0xFF << PINMUX_BALL_P1_SHIFT))
#define PINMUX_BALL_P2_MASK             (~(0xFF << PINMUX_BALL_P2_SHIFT))
#define PINMUX_BALL_R2_MASK             (~(0xFF << PINMUX_BALL_R2_SHIFT))
#define PINMUX_BALL_T1_MASK             (~(0xFF << PINMUX_BALL_T1_SHIFT))
#define PINMUX_BALL_T12_MASK            (~(0xFF << PINMUX_BALL_T12_SHIFT))
#define PINMUX_BALL_U1_MASK             (~(0xFF << PINMUX_BALL_U1_SHIFT))
#define PINMUX_BALL_V2_MASK             (~(0xFF << PINMUX_BALL_V2_SHIFT))
#define PINMUX_BALL_V5_MASK             (~(0xFF << PINMUX_BALL_V5_SHIFT))
#define PINMUX_BALL_V6_MASK             (~(0xFF << PINMUX_BALL_V6_SHIFT))
#define PINMUX_BALL_V7_MASK             (~(0xFF << PINMUX_BALL_V7_SHIFT))
#define PINMUX_BALL_V8_MASK             (~(0xFF << PINMUX_BALL_V8_SHIFT))
#define PINMUX_BALL_V9_MASK             (~(0xFF << PINMUX_BALL_V9_SHIFT))
#define PINMUX_BALL_V10_MASK            (~(0xFF << PINMUX_BALL_V10_SHIFT))
#define PINMUX_BALL_W3_MASK             (~(0xFF << PINMUX_BALL_W3_SHIFT))
#define PINMUX_BALL_W5_MASK             (~(0xFF << PINMUX_BALL_W5_SHIFT))
#define PINMUX_BALL_W8_MASK             (~(0xFF << PINMUX_BALL_W8_SHIFT))
#define PINMUX_BALL_W9_MASK             (~(0xFF << PINMUX_BALL_W9_SHIFT))
#define PINMUX_BALL_W10_MASK            (~(0xFF << PINMUX_BALL_W10_SHIFT))

#define PINMUX_GATE_EMIF_CLK_MASK               (~(0xFF << PINMUX_GATE_EMIF_CLK_SHIFT))
#define PINMUX_GIOB_DISABLE_HET2_MASK           (~(0xFF << PINMUX_GIOB_DISABLE_HET2_SHIFT))
#define PINMUX_ALT_ADC_TRIGGER_MASK             (~(0xFF << PINMUX_ALT_ADC_TRIGGER_SHIFT))
#define PINMUX_ETHERNET_MASK                    (~(0xFF << PINMUX_ETHERNET_SHIFT))

#define PINMUX_ETPWM1_MASK                      (~(0xFF << PINMUX_ETPWM1_SHIFT))
#define PINMUX_ETPWM2_MASK                      (~(0xFF << PINMUX_ETPWM2_SHIFT))
#define PINMUX_ETPWM3_MASK                      (~(0xFF << PINMUX_ETPWM3_SHIFT))
#define PINMUX_ETPWM4_MASK                      (~(0xFF << PINMUX_ETPWM4_SHIFT))
#define PINMUX_ETPWM5_MASK                      (~(0xFF << PINMUX_ETPWM5_SHIFT))
#define PINMUX_ETPWM6_MASK                      (~(0xFF << PINMUX_ETPWM6_SHIFT))
#define PINMUX_ETPWM7_MASK                      (~(0xFF << PINMUX_ETPWM7_SHIFT))
#define PINMUX_ETPWM_TIME_BASE_SYNC_MASK        (~(0xFF << PINMUX_ETPWM_TIME_BASE_SYNC_SHIFT))
#define PINMUX_ETPWM_TBCLK_SYNC_MASK           (~(0xFF << PINMUX_ETPWM_TBCLK_SYNC_SHIFT))
#define PINMUX_TZ1_MASK                        (~(0xFF << PINMUX_TZ1_SHIFT))
#define PINMUX_TZ2_MASK                        (~(0xFF << PINMUX_TZ2_SHIFT))
#define PINMUX_TZ3_MASK                        (~(0xFF << PINMUX_TZ3_SHIFT))
#define PINMUX_EPWM1SYNCI_MASK                 (~(0xFF << PINMUX_EPWM1SYNCI_SHIFT))



#define PINMUX_BALL_A4_HET1_16                                  (0x1 <<  PINMUX_BALL_A4_SHIFT)
#define PINMUX_BALL_A4_ETPWM1SYNCI                      	    (0x2 <<  PINMUX_BALL_A4_SHIFT)
#define PINMUX_BALL_A4_ETPWM1SYNCO                              (0x4 <<  PINMUX_BALL_A4_SHIFT)

#define PINMUX_BALL_A5_GIOA_0                                   (0x1 <<  PINMUX_BALL_A5_SHIFT)
#define PINMUX_BALL_A5_OHCI_PRT_RcvDpls_1                       (0x2 <<  PINMUX_BALL_A5_SHIFT)
#define PINMUX_BALL_A5_W2FC_RXDPI                               (0x4 <<  PINMUX_BALL_A5_SHIFT)

#define PINMUX_BALL_A11_HET1_14                                 (0x1 <<  PINMUX_BALL_A11_SHIFT)
#define PINMUX_BALL_A11_OHCI_RCFG_txSe0_0                       (0x2 <<  PINMUX_BALL_A11_SHIFT)

#define PINMUX_BALL_A14_HET1_26                                 (0x1 <<  PINMUX_BALL_A14_SHIFT)
#define PINMUX_BALL_A14_MII_RXD_1                               (0x2 <<  PINMUX_BALL_A14_SHIFT)
#define PINMUX_BALL_A14_RMII_RXD_1                              (0x4 <<  PINMUX_BALL_A14_SHIFT)

#define PINMUX_BALL_B2_MIBSPI3NCS_2                             (0x1 <<  PINMUX_BALL_B2_SHIFT)
#define PINMUX_BALL_B2_I2C_SDA                                  (0x2 <<  PINMUX_BALL_B2_SHIFT)
#define PINMUX_BALL_B2_HET1_27                                  (0x4 <<  PINMUX_BALL_B2_SHIFT)
#define PINMUX_BALL_B2_nTZ2                                     (0x8 <<  PINMUX_BALL_B2_SHIFT)

#define PINMUX_BALL_B3_HET1_22                                  (0x1 <<  PINMUX_BALL_B3_SHIFT)
#define PINMUX_BALL_B3_OHCI_RCFG_txSe0_1                        (0x2 <<  PINMUX_BALL_B3_SHIFT)
#define PINMUX_BALL_B3_W2FC_SE0O                                (0x4 <<  PINMUX_BALL_B3_SHIFT)

#define PINMUX_BALL_B4_HET1_12                                  (0x1 <<  PINMUX_BALL_B4_SHIFT)
#define PINMUX_BALL_B4_MII_CRS                                  (0x2 <<  PINMUX_BALL_B4_SHIFT)
#define PINMUX_BALL_B4_RMII_CRS_DV                              (0x4 <<  PINMUX_BALL_B4_SHIFT)

#define PINMUX_BALL_B5_GIOA_5                                   (0x1 <<  PINMUX_BALL_B5_SHIFT)
#define PINMUX_BALL_B5_EXTCLKIN                                 (0x2 <<  PINMUX_BALL_B5_SHIFT)
#define PINMUX_BALL_B5_ETPWM1A                                  (0x4 <<  PINMUX_BALL_B5_SHIFT)

#define PINMUX_BALL_B11_HET1_30                                 (0x1 <<  PINMUX_BALL_B11_SHIFT)
#define PINMUX_BALL_B11_MII_RX_DV                               (0x2 <<  PINMUX_BALL_B11_SHIFT)
#define PINMUX_BALL_B11_OHCI_RCFG_speed_0                       (0x4 <<  PINMUX_BALL_B11_SHIFT)
#define PINMUX_BALL_B11_EQEP2S		                      (0x8 <<  PINMUX_BALL_B11_SHIFT)

#define PINMUX_BALL_B12_HET1_04                                 (0x1 <<  PINMUX_BALL_B12_SHIFT)
#define PINMUX_BALL_B12_ETPWM4B                                 (0x2 <<  PINMUX_BALL_B12_SHIFT)

#define PINMUX_BALL_C1_GIOA_2                                   (0x1 <<  PINMUX_BALL_C1_SHIFT)
#define PINMUX_BALL_C1_OHCI_RCFG_txdPls_1                       (0x2 <<  PINMUX_BALL_C1_SHIFT)
#define PINMUX_BALL_C1_W2FC_TXDO                                (0x4 <<  PINMUX_BALL_C1_SHIFT)
#define PINMUX_BALL_C1_HET2_0                                   (0x8 <<  PINMUX_BALL_C1_SHIFT)
#define PINMUX_BALL_C1_EQEP2I                                   (0x10 <<  PINMUX_BALL_C1_SHIFT)


#define PINMUX_BALL_C2_GIOA_1                                   (0x1 <<  PINMUX_BALL_C2_SHIFT)
#define PINMUX_BALL_C2_OHCI_PRT_RcvDmns_1                       (0x2 <<  PINMUX_BALL_C2_SHIFT)
#define PINMUX_BALL_C2_W2FC_RXDMI                               (0x4 <<  PINMUX_BALL_C2_SHIFT)

#define PINMUX_BALL_C3_MIBSPI3NCS_3                             (0x1 <<  PINMUX_BALL_C3_SHIFT)
#define PINMUX_BALL_C3_I2C_SCL                                  (0x2 <<  PINMUX_BALL_C3_SHIFT)
#define PINMUX_BALL_C3_HET1_29                                  (0x4 <<  PINMUX_BALL_C3_SHIFT)
#define PINMUX_BALL_C3_nTZ1                                     (0x8 <<  PINMUX_BALL_C3_SHIFT)

#define PINMUX_BALL_C4_EMIF_ADDR_6                              (0x1 <<  PINMUX_BALL_C4_SHIFT)
#define PINMUX_BALL_C4_HET2_11                                  (0x4 <<  PINMUX_BALL_C4_SHIFT)

#define PINMUX_BALL_C5_EMIF_ADDR_7                              (0x1 <<  PINMUX_BALL_C5_SHIFT)
#define PINMUX_BALL_C5_HET2_13                                  (0x4 <<  PINMUX_BALL_C5_SHIFT)

#define PINMUX_BALL_C6_EMIF_ADDR_8                              (0x1 <<  PINMUX_BALL_C6_SHIFT)
#define PINMUX_BALL_C6_HET2_15                                  (0x4 <<  PINMUX_BALL_C6_SHIFT)


#define PINMUX_BALL_D3_SPI2NENA                                 (0x1 <<  PINMUX_BALL_D3_SHIFT)
#define PINMUX_BALL_D3_SPI2NCS_1                                (0x2 <<  PINMUX_BALL_D3_SHIFT)

#define PINMUX_BALL_D4_EMIF_ADDR_0                              (0x1 <<  PINMUX_BALL_D4_SHIFT)
#define PINMUX_BALL_D4_HET2_1                                   (0x2 <<  PINMUX_BALL_D4_SHIFT)

#define PINMUX_BALL_D5_EMIF_ADDR_1                              (0x1 <<  PINMUX_BALL_D5_SHIFT)
#define PINMUX_BALL_D5_HET2_3                                   (0x2 <<  PINMUX_BALL_D5_SHIFT)

#define PINMUX_BALL_D16_EMIF_BA_1                               (0x1 <<  PINMUX_BALL_D16_SHIFT)
#define PINMUX_BALL_D16_HET2_5                                  (0x2 <<  PINMUX_BALL_D16_SHIFT)

#define PINMUX_BALL_D17_EMIF_nWE                                (0x1 <<  PINMUX_BALL_D17_SHIFT)
#define PINMUX_BALL_D17_EMIF_RNW                                (0x2 <<  PINMUX_BALL_D17_SHIFT)

#define PINMUX_BALL_D19_HET1_10                                 (0x1 <<  PINMUX_BALL_D19_SHIFT)
#define PINMUX_BALL_D19_MII_TX_CLK                              (0x2 <<  PINMUX_BALL_D19_SHIFT)
#define PINMUX_BALL_D19_OHCI_RCFG_txEnL_0                       (0x4 <<  PINMUX_BALL_D19_SHIFT)
#define PINMUX_BALL_D19_MII_TX_AVCLK4                           (0x8 <<  PINMUX_BALL_D19_SHIFT)
#define PINMUX_BALL_D19_nTZ3                                    (0x10 <<  PINMUX_BALL_D19_SHIFT)

#define PINMUX_BALL_E1_GIOA_3                                   (0x1 <<  PINMUX_BALL_E1_SHIFT)
#define PINMUX_BALL_E1_HET2_02                                   (0x2 <<  PINMUX_BALL_E1_SHIFT)

#define PINMUX_BALL_E3_HET1_11                                  (0x1 <<  PINMUX_BALL_E3_SHIFT)
#define PINMUX_BALL_E3_MIBSPI3NCS_4                             (0x2 <<  PINMUX_BALL_E3_SHIFT)
#define PINMUX_BALL_E3_HET2_18                                  (0x4 <<  PINMUX_BALL_E3_SHIFT)
#define PINMUX_BALL_E3_OHCI_PRT_OvrCurrent_1                    (0x8 <<  PINMUX_BALL_E3_SHIFT)
#define PINMUX_BALL_E3_W2FC_VBUSI                               (0x10 <<  PINMUX_BALL_E3_SHIFT)
#define PINMUX_BALL_E3_ETPWM1SYNCO                              (0x20 <<  PINMUX_BALL_E3_SHIFT)

#define PINMUX_BALL_E18_HET1_08                                 (0x1 <<  PINMUX_BALL_E18_SHIFT)
#define PINMUX_BALL_E18_MIBSPI1SIMO_1                           (0x2 <<  PINMUX_BALL_E18_SHIFT)
#define PINMUX_BALL_E18_MII_TXD_3                               (0x4 <<  PINMUX_BALL_E18_SHIFT)
#define PINMUX_BALL_E18_OHCI_PRT_OvrCurrent_0                   (0x8 <<  PINMUX_BALL_E18_SHIFT)

#define PINMUX_BALL_E19_MIBSPI5NCS_0                            (0x1 <<  PINMUX_BALL_E19_SHIFT)
#define PINMUX_BALL_E19_ETPWM4A                                 (0x4 <<  PINMUX_BALL_E19_SHIFT)

#define PINMUX_BALL_F3_MIBSPI1NCS_1                             (0x1 <<  PINMUX_BALL_F3_SHIFT)
#define PINMUX_BALL_F3_HET1_17                                  (0x2 <<  PINMUX_BALL_F3_SHIFT)
#define PINMUX_BALL_F3_MII_COL                                  (0x4 <<  PINMUX_BALL_F3_SHIFT)
#define PINMUX_BALL_F3_OHCI_RCFG_suspend_0                      (0x8 <<  PINMUX_BALL_F3_SHIFT)
#define PINMUX_BALL_F3_EQEP1S                                   (0x10 <<  PINMUX_BALL_F3_SHIFT)

#define PINMUX_BALL_G3_MIBSPI1NCS_2                             (0x1 <<  PINMUX_BALL_G3_SHIFT)
#define PINMUX_BALL_G3_HET1_19                                  (0x2 <<  PINMUX_BALL_G3_SHIFT)
#define PINMUX_BALL_G3_MDIO                                     (0x4 <<  PINMUX_BALL_G3_SHIFT)

#define PINMUX_BALL_G19_MIBSPI1NENA                             (0x1 <<  PINMUX_BALL_G19_SHIFT)
#define PINMUX_BALL_G19_HET1_23                                 (0x2 <<  PINMUX_BALL_G19_SHIFT)
#define PINMUX_BALL_G19_MII_RXD_2                               (0x4 <<  PINMUX_BALL_G19_SHIFT)
#define PINMUX_BALL_G19_OHCI_PRT_RcvDpls_0                      (0x8 <<  PINMUX_BALL_G19_SHIFT)
#define PINMUX_BALL_G19_ECAP4                                       (0x10 <<  PINMUX_BALL_G19_SHIFT)


#define PINMUX_BALL_H3_GIOA_6                                   (0x1 <<  PINMUX_BALL_H3_SHIFT)
#define PINMUX_BALL_H3_HET2_04                                   (0x2 <<  PINMUX_BALL_H3_SHIFT)
#define PINMUX_BALL_H3_ETPWM1B                                  (0x4 <<  PINMUX_BALL_H3_SHIFT)

#define PINMUX_BALL_H18_MIBSPI5NENA                             (0x1 <<  PINMUX_BALL_H18_SHIFT)
#define PINMUX_BALL_H18_MII_RXD_3                               (0x4 <<  PINMUX_BALL_H18_SHIFT)
#define PINMUX_BALL_H18_OHCI_PRT_RcvDmns_0                      (0x8 <<  PINMUX_BALL_H18_SHIFT)
#define PINMUX_BALL_H18_MIBSPI5SOMI_1                           (0x10 <<  PINMUX_BALL_H18_SHIFT)
#define PINMUX_BALL_H18_ECAP5                                   (0x20 <<  PINMUX_BALL_H18_SHIFT)

#define PINMUX_BALL_H19_MIBSPI5CLK                              (0x1 <<  PINMUX_BALL_H19_SHIFT)
#define PINMUX_BALL_H19_MII_TXEN                                (0x4 <<  PINMUX_BALL_H19_SHIFT)
#define PINMUX_BALL_H19_RMII_TXEN                               (0x8 <<  PINMUX_BALL_H19_SHIFT)

#define PINMUX_BALL_J1_HET1_18                                  (0x1 <<  PINMUX_BALL_J1_SHIFT)
#define PINMUX_BALL_J1_ETPWM6A                                  (0x2 <<  PINMUX_BALL_J1_SHIFT)

#define PINMUX_BALL_J3_MIBSPI1NCS_3                             (0x1 <<  PINMUX_BALL_J3_SHIFT)
#define PINMUX_BALL_J3_HET1_21                                  (0x2 <<  PINMUX_BALL_J3_SHIFT)

#define PINMUX_BALL_J18_MIBSPI5SOMI_0                           (0x1 <<  PINMUX_BALL_J18_SHIFT)
#define PINMUX_BALL_J18_MII_TXD_0                               (0x4 <<  PINMUX_BALL_J18_SHIFT)
#define PINMUX_BALL_J18_RMII_TXD_0                              (0x8 <<  PINMUX_BALL_J18_SHIFT)

#define PINMUX_BALL_J19_MIBSPI5SIMO_0                           (0x1 <<  PINMUX_BALL_J19_SHIFT)
#define PINMUX_BALL_J19_MII_TXD_1                               (0x4 <<  PINMUX_BALL_J19_SHIFT)
#define PINMUX_BALL_J19_RMII_TXD_1                              (0x8 <<  PINMUX_BALL_J19_SHIFT)
#define PINMUX_BALL_J19_MIBSPI5SOMI_2                           (0x10 <<  PINMUX_BALL_J19_SHIFT)

#define PINMUX_BALL_K2_GIOB_1                                   (0x1 <<  PINMUX_BALL_K2_SHIFT)
#define PINMUX_BALL_K2_OHCI_RCFG_PrtPower_0                     (0x2 <<  PINMUX_BALL_K2_SHIFT)

#define PINMUX_BALL_K17_EMIF_nCS_3                              (0x1 <<  PINMUX_BALL_K17_SHIFT)
#define PINMUX_BALL_K17_HET2_09                                 (0x4 <<  PINMUX_BALL_K17_SHIFT)

#define PINMUX_BALL_K18_HET1_0                                  (0x1 <<  PINMUX_BALL_K18_SHIFT)
#define PINMUX_BALL_K18_SPI4CLK                                 (0x2 <<  PINMUX_BALL_K18_SHIFT)
#define PINMUX_BALL_K18_ETPWM2B                                 (0x4 <<  PINMUX_BALL_K18_SHIFT)

#define PINMUX_BALL_K19_HET1_28                                 (0x1 <<  PINMUX_BALL_K19_SHIFT)
#define PINMUX_BALL_K19_MII_RXCLK                               (0x2 <<  PINMUX_BALL_K19_SHIFT)
#define PINMUX_BALL_K19_RMII_REFCLK                             (0x4 <<  PINMUX_BALL_K19_SHIFT)
#define PINMUX_BALL_K19_MII_RX_AVCLK4                           (0x8 <<  PINMUX_BALL_K19_SHIFT)

#define PINMUX_BALL_M1_GIOA_7                                   (0x1 <<  PINMUX_BALL_M1_SHIFT)
#define PINMUX_BALL_M1_HET2_06                                  (0x2 <<  PINMUX_BALL_M1_SHIFT)
#define PINMUX_BALL_M1_ETPWM2A                                  (0x4 <<  PINMUX_BALL_M1_SHIFT)

#define PINMUX_BALL_M2_GIOB_0                                   (0x1 <<  PINMUX_BALL_M2_SHIFT)
#define PINMUX_BALL_M2_OHCI_RCFG_txDpls_0                       (0x2 <<  PINMUX_BALL_M2_SHIFT)

#define PINMUX_BALL_N1_HET1_15                                  (0x1 <<  PINMUX_BALL_N1_SHIFT)
#define PINMUX_BALL_N1_MIBSPI1NCS_4                             (0x2 <<  PINMUX_BALL_N1_SHIFT)
#define PINMUX_BALL_N1_ECAP1                                    (0x4 <<  PINMUX_BALL_N1_SHIFT)

#define PINMUX_BALL_N2_HET1_13                                  (0x1 <<  PINMUX_BALL_N2_SHIFT)
#define PINMUX_BALL_N2_SCITX                                    (0x2 <<  PINMUX_BALL_N2_SHIFT)
#define PINMUX_BALL_N2_ETPWM5B                                  (0x4 <<  PINMUX_BALL_N2_SHIFT)

#define PINMUX_BALL_N17_EMIF_nCS_0                              (0x1 <<  PINMUX_BALL_N17_SHIFT)
#define PINMUX_BALL_N17_HET2_07                                 (0x4 <<  PINMUX_BALL_N17_SHIFT)

#define PINMUX_BALL_N19_AD1EVT                                  (0x1 <<  PINMUX_BALL_N19_SHIFT)
#define PINMUX_BALL_N19_MII_RX_ER                               (0x2 <<  PINMUX_BALL_N19_SHIFT)
#define PINMUX_BALL_N19_RMII_RX_ER                              (0x4 <<  PINMUX_BALL_N19_SHIFT)

#define PINMUX_BALL_P1_HET1_24                                  (0x1 <<  PINMUX_BALL_P1_SHIFT)
#define PINMUX_BALL_P1_MIBSPI1NCS_5                             (0x2 <<  PINMUX_BALL_P1_SHIFT)
#define PINMUX_BALL_P1_MII_RXD_0                                (0x4 <<  PINMUX_BALL_P1_SHIFT)
#define PINMUX_BALL_P1_RMII_RXD_0                               (0x8 <<  PINMUX_BALL_P1_SHIFT)

#define PINMUX_BALL_P2_HET1_20                                  (0x1 <<  PINMUX_BALL_P2_SHIFT)
#define PINMUX_BALL_P2_ETPWM6B	                            (0x2 <<  PINMUX_BALL_P2_SHIFT)

#define PINMUX_BALL_R2_MIBSPI1NCS_0                             (0x1 <<  PINMUX_BALL_R2_SHIFT)
#define PINMUX_BALL_R2_MIBSPI1SOMI_1                            (0x2 <<  PINMUX_BALL_R2_SHIFT)
#define PINMUX_BALL_R2_MII_TXD_2                                (0x4 <<  PINMUX_BALL_R2_SHIFT)
#define PINMUX_BALL_R2_OHCI_PRT_RcvData_0                       (0x8 <<  PINMUX_BALL_R2_SHIFT)
#define PINMUX_BALL_R2_ECAP6                                    (0x10 <<  PINMUX_BALL_R2_SHIFT)

#define PINMUX_BALL_T1_HET1_07                                  (0x1 <<  PINMUX_BALL_T1_SHIFT)
#define PINMUX_BALL_T1_OHCI_RCFG_PrtPower_1                     (0x2 <<  PINMUX_BALL_T1_SHIFT)
#define PINMUX_BALL_T1_W2FC_GZO                                 (0x4 <<  PINMUX_BALL_T1_SHIFT)
#define PINMUX_BALL_T1_HET2_14                                  (0x8 <<  PINMUX_BALL_T1_SHIFT)
#define PINMUX_BALL_T1_ETPWM7B                                  (0x10 <<  PINMUX_BALL_T1_SHIFT)


#define PINMUX_BALL_U1_HET1_03                                  (0x1 <<  PINMUX_BALL_U1_SHIFT)
#define PINMUX_BALL_U1_SPI4NCS_0                                (0x2 <<  PINMUX_BALL_U1_SHIFT)
#define PINMUX_BALL_U1_OHCI_RCFG_speed_1                        (0x4 <<  PINMUX_BALL_U1_SHIFT)
#define PINMUX_BALL_U1_W2FC_PUENON                              (0x8 <<  PINMUX_BALL_U1_SHIFT)
#define PINMUX_BALL_U1_HET2_10                                  (0x10 <<  PINMUX_BALL_U1_SHIFT)
#define PINMUX_BALL_U1_EQEP2B                                   (0x20 <<  PINMUX_BALL_U1_SHIFT)

#define PINMUX_BALL_V2_HET1_01                                  (0x1 <<  PINMUX_BALL_V2_SHIFT)
#define PINMUX_BALL_V2_SPI4NENA                                 (0x2 <<  PINMUX_BALL_V2_SHIFT)
#define PINMUX_BALL_V2_OHCI_RCFG_txEnL_1                        (0x4 <<  PINMUX_BALL_V2_SHIFT)
#define PINMUX_BALL_V2_W2FC_PUENO                               (0x8 <<  PINMUX_BALL_V2_SHIFT)
#define PINMUX_BALL_V2_HET2_08                                  (0x10 <<  PINMUX_BALL_V2_SHIFT)
#define PINMUX_BALL_V2_EQEP2A                                   (0x20 <<  PINMUX_BALL_V2_SHIFT)

#define PINMUX_BALL_V5_MIBSPI3NCS_1                             (0x1 <<  PINMUX_BALL_V5_SHIFT)
#define PINMUX_BALL_V5_HET1_25                                  (0x2 <<  PINMUX_BALL_V5_SHIFT)
#define PINMUX_BALL_V5_MDCLK                                    (0x4 <<  PINMUX_BALL_V5_SHIFT)

#define PINMUX_BALL_V6_HET1_05                                  (0x1 <<  PINMUX_BALL_V6_SHIFT)
#define PINMUX_BALL_V6_SPI4SOMI                                 (0x2 <<  PINMUX_BALL_V6_SHIFT)
#define PINMUX_BALL_V6_HET2_12                                  (0x4 <<  PINMUX_BALL_V6_SHIFT)
#define PINMUX_BALL_V6_ETPWM3B                                  (0x8 <<  PINMUX_BALL_V6_SHIFT)

#define PINMUX_BALL_V7_HET1_09                                  (0x1 <<  PINMUX_BALL_V7_SHIFT)
#define PINMUX_BALL_V7_HET2_16                                  (0x2 <<  PINMUX_BALL_V7_SHIFT)
#define PINMUX_BALL_V7_OHCI_RCFG_suspend_1                      (0x4 <<  PINMUX_BALL_V7_SHIFT)
#define PINMUX_BALL_V7_W2FC_SUSPENDO                            (0x8 <<  PINMUX_BALL_V7_SHIFT)
#define PINMUX_BALL_V7_ETPWM7A                                  (0x10 <<  PINMUX_BALL_V7_SHIFT)

#define PINMUX_BALL_V8_MIBSPI3SOMI                              (0x1 <<  PINMUX_BALL_V8_SHIFT)
#define PINMUX_BALL_V8_AWM_EXT_ENA                              (0x2 <<  PINMUX_BALL_V8_SHIFT)
#define PINMUX_BALL_V8_ECAP2                                    (0x4 <<  PINMUX_BALL_V8_SHIFT)

#define PINMUX_BALL_V9_MIBSPI3CLK                               (0x1 <<  PINMUX_BALL_V9_SHIFT)
#define PINMUX_BALL_V9_AWM_EXT_SEL_1                            (0x2 <<  PINMUX_BALL_V9_SHIFT)
#define PINMUX_BALL_V9_EQEP1A                                   (0x4 <<  PINMUX_BALL_V9_SHIFT)

#define PINMUX_BALL_V10_MIBSPI3NCS_0                            (0x1 <<  PINMUX_BALL_V10_SHIFT)
#define PINMUX_BALL_V10_AD2EVT                                  (0x2 <<  PINMUX_BALL_V10_SHIFT)
#define PINMUX_BALL_V10_GIOB_2                                  (0x4 <<  PINMUX_BALL_V10_SHIFT)
#define PINMUX_BALL_V10_EQEP1I                                  (0x8 <<  PINMUX_BALL_V10_SHIFT)

#define PINMUX_BALL_W3_HET1_06                                  (0x1 <<  PINMUX_BALL_W3_SHIFT)
#define PINMUX_BALL_W3_SCIRX                                    (0x2 <<  PINMUX_BALL_W3_SHIFT)
#define PINMUX_BALL_W3_ETPWM5A                                  (0x4 <<  PINMUX_BALL_W3_SHIFT)

#define PINMUX_BALL_W5_HET1_02                                  (0x1 <<  PINMUX_BALL_W5_SHIFT)
#define PINMUX_BALL_W5_SPI4SIMO                                 (0x2 <<  PINMUX_BALL_W5_SHIFT)
#define PINMUX_BALL_W5_ETPWM3A                                  (0x4 <<  PINMUX_BALL_W5_SHIFT)

#define PINMUX_BALL_W8_MIBSPI3SIMO                              (0x1 <<  PINMUX_BALL_W8_SHIFT)
#define PINMUX_BALL_W8_AWM_EXT_SEL_0                            (0x2 <<  PINMUX_BALL_W8_SHIFT)
#define PINMUX_BALL_W8_ECAP3                                    (0x4 <<  PINMUX_BALL_W8_SHIFT)

#define PINMUX_BALL_W9_MIBSPI3NENA                              (0x1 <<  PINMUX_BALL_W9_SHIFT)
#define PINMUX_BALL_W9_MIBSPI3NCS_5                             (0x2 <<  PINMUX_BALL_W9_SHIFT)
#define PINMUX_BALL_W9_HET1_31                                  (0x4 <<  PINMUX_BALL_W9_SHIFT)
#define PINMUX_BALL_W9_EQEP1B                                   (0x8 <<  PINMUX_BALL_W9_SHIFT)

#define PINMUX_BALL_W10_GIOB_3                                  (0x1 <<  PINMUX_BALL_W10_SHIFT)
#define PINMUX_BALL_W10_OHCI_PRT_RcvData_1                      (0x2 <<  PINMUX_BALL_W10_SHIFT)
#define PINMUX_BALL_W10_W2FC_RXDI                               (0x4 <<  PINMUX_BALL_W10_SHIFT)

#define PINMUX_GATE_EMIF_CLK                                    (0x0 <<  PINMUX_GATE_EMIF_CLK_SHIFT)      /**/ 
#define PINMUX_GIOB_DISABLE_HET2                                (0x1 <<  PINMUX_GIOB_DISABLE_HET2_SHIFT)
#define PINMUX_ALT_ADC_TRIGGER_1                                (0x1 <<  PINMUX_ALT_ADC_TRIGGER_SHIFT)
#define PINMUX_ALT_ADC_TRIGGER_2                                (0x2 <<  PINMUX_ALT_ADC_TRIGGER_SHIFT)
#define PINMUX_ETHERNET_MII                                     (0x0 <<  PINMUX_ETHERNET_SHIFT)
#define PINMUX_ETHERNET_RMII                                    (0x1 <<  PINMUX_ETHERNET_SHIFT)

#define PINMUX_ETPWM1_EQEPERR12                                   (0x1 <<  PINMUX_ETPWM1_SHIFT)
#define PINMUX_ETPWM1_EQEPERR1                                    (0x2 <<  PINMUX_ETPWM1_SHIFT)
#define PINMUX_ETPWM1_EQEPERR2                                    (0x4 <<  PINMUX_ETPWM1_SHIFT)
#define PINMUX_ETPWM2_EQEPERR12                                   (0x1 <<  PINMUX_ETPWM2_SHIFT)
#define PINMUX_ETPWM2_EQEPERR1                                    (0x2 <<  PINMUX_ETPWM2_SHIFT)
#define PINMUX_ETPWM2_EQEPERR2                                    (0x4 <<  PINMUX_ETPWM2_SHIFT)
#define PINMUX_ETPWM3_EQEPERR12                                   (0x1 <<  PINMUX_ETPWM3_SHIFT)
#define PINMUX_ETPWM3_EQEPERR1                                    (0x2 <<  PINMUX_ETPWM3_SHIFT)
#define PINMUX_ETPWM3_EQEPERR2                                    (0x4 <<  PINMUX_ETPWM3_SHIFT)
#define PINMUX_ETPWM4_EQEPERR12                                   (0x1 <<  PINMUX_ETPWM4_SHIFT)
#define PINMUX_ETPWM4_EQEPERR1                                    (0x2 <<  PINMUX_ETPWM4_SHIFT)
#define PINMUX_ETPWM4_EQEPERR2                                    (0x4 <<  PINMUX_ETPWM4_SHIFT)
#define PINMUX_ETPWM5_EQEPERR12                                   (0x1 <<  PINMUX_ETPWM5_SHIFT)
#define PINMUX_ETPWM5_EQEPERR1                                    (0x2 <<  PINMUX_ETPWM5_SHIFT)
#define PINMUX_ETPWM5_EQEPERR2                                    (0x4 <<  PINMUX_ETPWM5_SHIFT)
#define PINMUX_ETPWM6_EQEPERR12                                   (0x1 <<  PINMUX_ETPWM6_SHIFT)
#define PINMUX_ETPWM6_EQEPERR1                                    (0x2 <<  PINMUX_ETPWM6_SHIFT)
#define PINMUX_ETPWM6_EQEPERR2                                    (0x4 <<  PINMUX_ETPWM6_SHIFT)
#define PINMUX_ETPWM7_EQEPERR12                                   (0x1 <<  PINMUX_ETPWM7_SHIFT)
#define PINMUX_ETPWM7_EQEPERR1                                    (0x2 <<  PINMUX_ETPWM7_SHIFT)
#define PINMUX_ETPWM7_EQEPERR2                                    (0x4 <<  PINMUX_ETPWM7_SHIFT)
#define PINMUX_ETPWM_TIME_BASE_SYNC                        (0x2 <<  PINMUX_ETPWM_TIME_BASE_SYNC_SHIFT)
#define PINMUX_ETPWM_TBCLK_SYNC                            (0x2 <<  PINMUX_ETPWM_TBCLK_SYNC_SHIFT)
#define PINMUX_TZ1_ASYNC                                          (0x1 <<  PINMUX_TZ1_SHIFT)
#define PINMUX_TZ1_SYNC                                           (0x2 <<  PINMUX_TZ1_SHIFT)
#define PINMUX_TZ1_FILTERED                                       (0x4 <<  PINMUX_TZ1_SHIFT)
#define PINMUX_TZ2_ASYNC                                          (0x1 <<  PINMUX_TZ2_SHIFT)
#define PINMUX_TZ2_SYNC                                           (0x2 <<  PINMUX_TZ2_SHIFT)
#define PINMUX_TZ2_FILTERED                                       (0x4 <<  PINMUX_TZ2_SHIFT)
#define PINMUX_TZ3_ASYNC                                          (0x1 <<  PINMUX_TZ3_SHIFT)
#define PINMUX_TZ3_SYNC                                           (0x2 <<  PINMUX_TZ3_SHIFT)
#define PINMUX_TZ3_FILTERED                                       (0x4 <<  PINMUX_TZ3_SHIFT)
#define PINMUX_EPWM1SYNCI_ASYNC                                   (0x1 <<  PINMUX_EPWM1SYNCI_SHIFT)
#define PINMUX_EPWM1SYNCI_SYNC                                    (0x2 <<  PINMUX_EPWM1SYNCI_SHIFT)
#define PINMUX_EPWM1SYNCI_FILTERED                                (0x4 <<  PINMUX_EPWM1SYNCI_SHIFT)



/** @struct pinMuxKicker
*   @brief Pin Muxing Kicker Register Definition
*
*   This structure is used to access the Pin Muxing Kicker registers.
*/
typedef volatile struct pinMuxKicker
{
    uint32_t KICKER0;       /* kicker 0 register */
    uint32_t KICKER1;       /* kicker 1 register */
} pinMuxKICKER_t;

/** @struct pinMuxBase
*   @brief PINMUX Register Definition
*
*   This structure is used to access the PINMUX module egisters.
*/
/** @typedef pinMuxBASE_t
*   @brief PINMUX Register Frame Type Definition
*
*   This type is used to access the PINMUX Registers.
*/
typedef volatile struct pinMuxBase
{
    uint32_t PINMUX0;           /**< 0xEB10 Pin Mux 0 register*/
    uint32_t PINMUX1;           /**< 0xEB14 Pin Mux 1 register*/
    uint32_t PINMUX2;           /**< 0xEB18 Pin Mux 2 register*/
    uint32_t PINMUX3;           /**< 0xEB1C Pin Mux 3 register*/
    uint32_t PINMUX4;           /**< 0xEB20 Pin Mux 4 register*/
    uint32_t PINMUX5;           /**< 0xEB24 Pin Mux 5 register*/
    uint32_t PINMUX6;           /**< 0xEB28 Pin Mux 6 register*/
    uint32_t PINMUX7;           /**< 0xEB2C Pin Mux 7 register*/
    uint32_t PINMUX8;           /**< 0xEB30 Pin Mux 8 register*/
    uint32_t PINMUX9;           /**< 0xEB34 Pin Mux 9 register*/
    uint32_t PINMUX10;          /**< 0xEB38 Pin Mux 10 register*/
    uint32_t PINMUX11;          /**< 0xEB3C Pin Mux 11 register*/
    uint32_t PINMUX12;          /**< 0xEB40 Pin Mux 12 register*/
    uint32_t PINMUX13;          /**< 0xEB44 Pin Mux 13 register*/
    uint32_t PINMUX14;          /**< 0xEB48 Pin Mux 14 register*/
    uint32_t PINMUX15;          /**< 0xEB4C Pin Mux 15 register*/
    uint32_t PINMUX16;          /**< 0xEB50 Pin Mux 16 register*/
    uint32_t PINMUX17;          /**< 0xEB54 Pin Mux 17 register*/
    uint32_t PINMUX18;          /**< 0xEB58 Pin Mux 18 register*/
    uint32_t PINMUX19;          /**< 0xEB5C Pin Mux 19 register*/
    uint32_t PINMUX20;          /**< 0xEB60 Pin Mux 20 register*/
    uint32_t PINMUX21;          /**< 0xEB64 Pin Mux 21 register*/
    uint32_t PINMUX22;          /**< 0xEB68 Pin Mux 22 register*/
    uint32_t PINMUX23;          /**< 0xEB6C Pin Mux 23 register*/
    uint32_t PINMUX24;          /**< 0xEB70 Pin Mux 24 register*/
    uint32_t PINMUX25;          /**< 0xEB74 Pin Mux 25 register*/
    uint32_t PINMUX26;          /**< 0xEB78 Pin Mux 26 register*/
    uint32_t PINMUX27;          /**< 0xEB7C Pin Mux 27 register*/
    uint32_t PINMUX28;          /**< 0xEB80 Pin Mux 28 register*/
    uint32_t PINMUX29;          /**< 0xEB84 Pin Mux 29 register*/
    uint32_t PINMUX30;          /**< 0xEB88 Pin Mux 30 register*/
    uint32_t PINMUX31;          /**< 0xEB8C Pin Mux 31 register*/
    uint32_t PINMUX32;          /**< 0xEB90 Pin Mux 32 register*/
    uint32_t PINMUX33;          /**< 0xEB94 Pin Mux 33 register*/
    uint32_t PINMUX34;          /**< 0xEB98 Pin Mux 34 register*/
    uint32_t PINMUX35;          /**< 0xEB9C Pin Mux 35 register*/
    uint32_t PINMUX36;          /**< 0xEBA0 Pin Mux 36 register*/
    uint32_t PINMUX37;          /**< 0xEBA4 Pin Mux 37 register*/
    uint32_t PINMUX38;          /**< 0xEBA8 Pin Mux 38 register*/
    uint32_t PINMUX39;          /**< 0xEBAC Pin Mux 39 register*/
    uint32_t PINMUX40;          /**< 0xEBB0 Pin Mux 40 register*/
    uint32_t PINMUX41;          /**< 0xEBB4 Pin Mux 41 register*/
    uint32_t PINMUX42;          /**< 0xEBB8 Pin Mux 42 register*/
    uint32_t PINMUX43;          /**< 0xEBBC Pin Mux 43 register*/
    uint32_t PINMUX44;          /**< 0xEBC0 Pin Mux 44 register*/
    uint32_t PINMUX45;          /**< 0xEBC4 Pin Mux 45 register*/
    uint32_t PINMUX46;          /**< 0xEBC8 Pin Mux 46 register*/
    uint32_t PINMUX47;          /**< 0xEBCC Pin Mux 47 register*/

}pinMuxBASE_t;

        
/** @def kickerReg
*       @brief Pin Muxing Kicker Register Frame Pointer
*
*               This pointer is used to enable and disable muxing accross the device.
*/      
#define kickerReg ((pinMuxKICKER_t *) 0xFFFFEA38)

/** @def pinMuxReg
*       @brief Pin Muxing Control Register Frame Pointer
*
*               This pointer is used to set the muxing registers accross the device.
*/      
#define pinMuxReg ((pinMuxBASE_t *) 0xFFFFEB10)

/** @fn void muxInit(void)
*   @brief Initializes the PINMUX Driver
*
*   This function initializes the PINMUX module and configures the selected 
*   pinmux settings as per the user selection in the GUI
*/
void muxInit(void);

#endif
