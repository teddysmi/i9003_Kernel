/**
 * Copyright (C) 2010-2011, Samsung Electronics, Co., Ltd. All Rights Reserved.
 *  Written by System S/W Group, Open OS S/W R&D Team,
 *  Mobile Communication Division.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/**
 * Project Name : OMAP-Samsung Linux Kernel for Android
 *
 * Project Description :
 *
 * Comments : tabstop = 8, shiftwidth = 8, noexpandtab
 */

/**
 * File Name : mux_adam_rev_r00.c
 *
 * File Description :
 *
 * Author : System Platform 2
 * Dept : System S/W Group (Open OS S/W R&D Team)
 * Created : 08/Feb/2011
 * Version : Baby-Raccoon
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/ctype.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <asm/system.h>
#include <plat/control.h>
#include <plat/mux.h>
#include <plat/gpio.h>
#include <linux/interrupt.h>

#include "mux.h"

/* FIXME: tricky!!! */
static unsigned int output_gpio[][3] = {
	{OMAP_GPIO_FM_SCL,		1, (unsigned int)"OMAP_GPIO_FM_SCL"},
	{OMAP_GPIO_FM_SDA,		1, (unsigned int)"OMAP_GPIO_FM_SDA"},
	{OMAP_GPIO_SYS_DRM_MSECURE,	1, (unsigned int)"OMAP_GPIO_SYS_DRM_MSECURE"},
	/*{OMAP_GPIO_PS_HOLD_PU,		0, (unsigned int)"OMAP_GPIO_PS_HOLD_PU" },*/
	{OMAP_GPIO_CON_CP_SEL,		0, (unsigned int)"OMAP_GPIO_CON_CP_SEL"},
	{OMAP_GPIO_ALS_EN,		0, (unsigned int)"OMAP_GPIO_ALS_EN"},
	{OMAP_GPIO_GPS_EN,		0, (unsigned int)"OMAP_GPIO_GPS_EN"},
	{OMAP_GPIO_GPS_CNTL,		0, (unsigned int)"OMAP_GPIO_GPS_CNTL"},
	{OMAP_GPIO_SENSOR_SCL,		1, (unsigned int)"OMAP_GPIO_SENSOR_SCL"},
	{OMAP_GPIO_SENSOR_SDA,		1, (unsigned int)"OMAP_GPIO_SENSOR_SDA"},
	{OMAP_GPIO_GPS_NRST,		1, (unsigned int)"OMAP_GPIO_GPS_NRST"},
	{OMAP_GPIO_FUEL_SDA,		1, (unsigned int)"OMAP_GPIO_FUEL_SDA"},
	{OMAP_GPIO_MIC_SEL,		1, (unsigned int)"OMAP_GPIO_MIC_SEL"},
	{OMAP_GPIO_CP_RST,		1, (unsigned int)"OMAP_GPIO_CP_RST"},
	{OMAP_GPIO_PCM_SEL,		0, (unsigned int)"OMAP_GPIO_PCM_SEL"},
	{OMAP_GPIO_JIG_ON18,		0, (unsigned int)"OMAP_GPIO_JIG_ON18"},
	{OMAP_GPIO_FUEL_SCL,		1, (unsigned int)"OMAP_GPIO_FUEL_SCL"},
	{OMAP_GPIO_LCD_EN_SET,		1, (unsigned int)"OMAP_GPIO_LCD_EN_SET"},
	{OMAP_GPIO_BT_NRST,		0, (unsigned int)"OMAP_GPIO_BT_NRST"},
	{OMAP_GPIO_5M_CAM_NRST,		0, (unsigned int)"OMAP_GPIO_5M_CAM_NRST"},
	{OMAP_GPIO_CAM_CIF_NSTBY,	0, (unsigned int)"OMAP_GPIO_CAM_CIF_NSTBY"},
	{OMAP_GPIO_EAR_MICBIAS_EN,	0, (unsigned int)"OMAP_GPIO_EAR_MICBIAS_EN"},
	{OMAP_GPIO_PDA_ACTIVE,		1, (unsigned int)"OMAP_GPIO_PDA_ACTIVE"},
	/*{OMAP_GPIO_UART_SEL,		1, (unsigned int)"OMAP_GPIO_UART_SEL" },*/
	{OMAP_GPIO_RESET_REQ_N,		0, (unsigned int)"OMAP_GPIO_RESET_REQ_N"},
	{OMAP_GPIO_VIBTONE_EN,		0, (unsigned int)"OMAP_GPIO_VIBTONE_EN"},
	{OMAP_GPIO_TOUCH_EN,		0, (unsigned int)"OMAP_GPIO_TOUCH_EN"},
	{OMAP_GPIO_CAM_CIF_NRST,	0, (unsigned int)"OMAP_GPIO_CAM_CIF_NRST"},
	{OMAP_GPIO_FM_nRST,		0, (unsigned int)"OMAP_GPIO_FM_nRST"},
	{OMAP_GPIO_CHG_EN,		0, (unsigned int)"OMAP_GPIO_CHG_EN"},
	{OMAP_GPIO_LED_EN1,		0, (unsigned int)"OMAP_GPIO_LED_EN1"},
	{OMAP_GPIO_MASSMEMORY_EN,	0, (unsigned int)"OMAP_GPIO_MASSMEMORY_EN"},
	{OMAP_GPIO_WLAN_EN,		0, (unsigned int)"OMAP_GPIO_WLAN_EN"},
	{OMAP_GPIO_CP_VBUS_EN,		0, (unsigned int)"OMAP_GPIO_CP_VBUS_EN"},
	{OMAP_GPIO_LED_EN2,		0, (unsigned int)"OMAP_GPIO_LED_EN2"},
	{OMAP_GPIO_CP_ON,		0, (unsigned int)"OMAP_GPIO_CP_ON"},
	{OMAP_GPIO_AP_I2C_SCL,		1, (unsigned int)"OMAP_GPIO_AP_I2C_SCL"},
	/*{OMAP_GPIO_MLCD_RST,		0, (unsigned int)"OMAP_GPIO_MLCD_RST" },*/
	{OMAP_GPIO_AMP_SHDN,		1, (unsigned int)"OMAP_GPIO_AMP_SHDN"},
	{OMAP_GPIO_MSENSE_NRST,		0, (unsigned int)"OMAP_GPIO_MSENSE_NRST"},
	{OMAP_GPIO_CAM_EN1,		0, (unsigned int)"OMAP_GPIO_CAM_EN1"},
	{OMAP_GPIO_CAM_5M_NSTBY,	0, (unsigned int)"OMAP_GPIO_CAM_5M_NSTBY"},
	{OMAP_GPIO_AP_I2C_SDA,		1, (unsigned int)"OMAP_GPIO_AP_I2C_SDA"},
	{OMAP_GPIO_CAM_EN2,		0, (unsigned int)"OMAP_GPIO_CAM_EN2"},
};

unsigned int omap34xx_output_gpio_size = ARRAY_SIZE(output_gpio);
EXPORT_SYMBOL(omap34xx_output_gpio_size);
unsigned int (*omap34xx_output_gpio_ptr)[3] = output_gpio;
EXPORT_SYMBOL(omap34xx_output_gpio_ptr);

static unsigned int wakeup_gpio[] = {
	OMAP_GPIO_JACK_NINT,
	OMAP_GPIO_FUEL_INT_N,
	OMAP_GPIO_CHG_ING_N,
	OMAP_GPIO_T_FLASH_DETECT,
	OMAP_GPIO_KEY_PWRON,
	OMAP_GPIO_KEY_HOME,
	OMAP_GPIO_TA_NCONNECTED,
	OMAP_GPIO_DET_3_5,
	OMAP_GPIO_EAR_SEND_END,
};

unsigned int omap34xx_wakeup_gpio_size = ARRAY_SIZE(wakeup_gpio);
EXPORT_SYMBOL(omap34xx_wakeup_gpio_size);
unsigned int *omap34xx_wakeup_gpio_ptr = wakeup_gpio;
EXPORT_SYMBOL(omap34xx_wakeup_gpio_ptr);

static struct omap_board_mux board_mux[] __initdata = { 
/*
 *		Name, reg-offset,
 *		mux-mode | [active-mode | off-mode]
 */

	// 0 
	OMAP3_MUX(SDRC_D0, OMAP_PIN_INPUT),
	// 1 
	OMAP3_MUX(SDRC_D1, OMAP_PIN_INPUT),
	// 2 
	OMAP3_MUX(SDRC_D2, OMAP_PIN_INPUT),
	// 3 
	OMAP3_MUX(SDRC_D3, OMAP_PIN_INPUT),
	// 4 
	OMAP3_MUX(SDRC_D4, OMAP_PIN_INPUT),
	// 5 
	OMAP3_MUX(SDRC_D5, OMAP_PIN_INPUT),
	// 6 
	OMAP3_MUX(SDRC_D6, OMAP_PIN_INPUT),
	// 7 
	OMAP3_MUX(SDRC_D7, OMAP_PIN_INPUT),
	// 8 
	OMAP3_MUX(SDRC_D8, OMAP_PIN_INPUT),
	// 9 
	OMAP3_MUX(SDRC_D9, OMAP_PIN_INPUT),
	// 10
	OMAP3_MUX(SDRC_D10, OMAP_PIN_INPUT),
	// 11 
	OMAP3_MUX(SDRC_D11, OMAP_PIN_INPUT),
	// 12 
	OMAP3_MUX(SDRC_D12, OMAP_PIN_INPUT),
	// 13 
	OMAP3_MUX(SDRC_D13, OMAP_PIN_INPUT),
	// 14 
	OMAP3_MUX(SDRC_D14, OMAP_PIN_INPUT),
	// 15 
	OMAP3_MUX(SDRC_D15, OMAP_PIN_INPUT),
	// 16 
	OMAP3_MUX(SDRC_D16, OMAP_PIN_INPUT),
	// 17 
	OMAP3_MUX(SDRC_D17, OMAP_PIN_INPUT),
	// 18 
	OMAP3_MUX(SDRC_D18, OMAP_PIN_INPUT),
	// 19 
	OMAP3_MUX(SDRC_D19, OMAP_PIN_INPUT),
	// 20 
	OMAP3_MUX(SDRC_D20, OMAP_PIN_INPUT),
	// 21 
	OMAP3_MUX(SDRC_D21, OMAP_PIN_INPUT),
	// 22 
	OMAP3_MUX(SDRC_D22, OMAP_PIN_INPUT),
	// 23 
	OMAP3_MUX(SDRC_D23, OMAP_PIN_INPUT),
	// 24 
	OMAP3_MUX(SDRC_D24, OMAP_PIN_INPUT),
	// 25 
	OMAP3_MUX(SDRC_D25, OMAP_PIN_INPUT),
	// 26 
	OMAP3_MUX(SDRC_D26, OMAP_PIN_INPUT),
	// 27 
	OMAP3_MUX(SDRC_D27, OMAP_PIN_INPUT),
	// 28 
	OMAP3_MUX(SDRC_D28, OMAP_PIN_INPUT),
	// 29 
	OMAP3_MUX(SDRC_D29, OMAP_PIN_INPUT),
	// 30 
	OMAP3_MUX(SDRC_D30, OMAP_PIN_INPUT),
	// 31 
	OMAP3_MUX(SDRC_D31, OMAP_PIN_INPUT),
	// 32 
	OMAP3_MUX(SDRC_CKE0, OMAP_MUX_MODE0),
	// 33 
	OMAP3_MUX(SDRC_CKE1, OMAP_MUX_MODE0),
	// 34 
	OMAP3_MUX(SDRC_CLK, OMAP_PIN_INPUT),
	// 35 
	OMAP3_MUX(SDRC_DQS0, OMAP_PIN_INPUT),
	// 36 
	OMAP3_MUX(SDRC_DQS1, OMAP_PIN_INPUT),
	// 37 
	OMAP3_MUX(SDRC_DQS2, OMAP_PIN_INPUT),
	// 38 
	OMAP3_MUX(SDRC_DQS3, OMAP_PIN_INPUT),

	// GPMC PIN MUX CONFIGURATION - GPMC_A1-GPMC_A10 ARE SUPPOSED TO BE OUTPUT ONLY LINES AS
	// THEY ARE MEANT FOR ADDRESS ONLY. ON THE OTHER HAND D0-D15 ARE MUXED WITH ADDRESS AND ALSO
	// THEY ARE DATA LINES AND SO CAN BE BIRECTIONAL.CHIPSELECTS ARE OUTPUT ONLY AND PULLUP IN OMAP
	// WILL NOT BE ACTIVATED EVEN IF REGISTER IS PROGRAMMED. BUT STILL JUST PULLING THEM UP.
	// WAIT2 AND WAIT3 ARE ACTIVE LOW INTERRUPT SIGNALS AND SO PULLING THEM UP. PULLING UP 
	// WAIT0 AND WAIT1 ALSO.

	// 39 (N4, L, GPMC_A1, INT_TEMP_POP)
	OMAP3_MUX(GPMC_A1, OMAP_MUX_MODE7 | OMAP_PIN_INPUT_PULLDOWN),
	// 40 (M4, L, GPIO_35, GPS_EN)
	OMAP3_MUX(GPMC_A2, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 41 (G3, L, GPIO_36, GPS_CNTL
	OMAP3_MUX(GPMC_A3, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 42 (G4, L, GPIO_37, SENSOR_SCL, O[H], OFF[H])
	OMAP3_MUX(GPMC_A4, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLUP),
	// 43 (F3, L, GPIO_38, SENSOR_SDA, O[H], OFF[H])
	OMAP3_MUX(GPMC_A5, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLUP),
	// 44 (E2, H, GPIO_39, GPS_nRST, I[?], OFF[?])
	OMAP3_MUX(GPMC_A6, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 45 (E3, H, GPIO_40, FM_INT, I[Z])
	OMAP3_MUX(GPMC_A7, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 46 (E4, H, GPIO_41, FUEL_SDA, O[H], OFF[H])
	OMAP3_MUX(GPMC_A8, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLUP),
	// 47 (L3, H, GPIO_42, MIC_SEL, O[H], OFF[?])
	OMAP3_MUX(GPMC_A9, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 48 (D4, H, GPIO_43, CP_RST, I[H], I[H])
	OMAP3_MUX(GPMC_A10, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 49 
	OMAP3_MUX(GPMC_D0, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 50 GPMC_D0(I/O)
	OMAP3_MUX(GPMC_D1, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 51 GPMC_D1(I/O)
	OMAP3_MUX(GPMC_D2, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 52 GPMC_D2(I/O)
	OMAP3_MUX(GPMC_D3, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 53 GPMC_D3(I/O)
	OMAP3_MUX(GPMC_D4, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 54 GPMC_D4(I/O)
	OMAP3_MUX(GPMC_D5, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 55 GPMC_D5(I/O)
	OMAP3_MUX(GPMC_D6, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 56 GPMC_D6(I/O)
	OMAP3_MUX(GPMC_D7, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 57 (N2, H, GPMC_D8, GPMC_D8, I/O)
	OMAP3_MUX(GPMC_D8, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	// 58 (P1, H, GPMC_D9, GPMC_D9, I/O)
	OMAP3_MUX(GPMC_D9, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	// 59 (R1, H, GPMC_D10, GPMC_D10, I/O)
	OMAP3_MUX(GPMC_D10, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 60 (U2, H, GPMC_D11, GPMC_D11, I/O)
	OMAP3_MUX(GPMC_D11, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 61 (V3, H, GPMC_D12, GPMC_D12, I/O)
	OMAP3_MUX(GPMC_D12, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 62 (W1, H, GPMC_D13, GPMC_D13, I/O)
	OMAP3_MUX(GPMC_D13, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 63 (Y2, H, GPMC_D14, GPMC_D14, I/O)
	OMAP3_MUX(GPMC_D14, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 64 (Y1, H, GPMC_D15, GPMC_D15, I/O)
	OMAP3_MUX(GPMC_D15, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 65 (G4)
	OMAP3_MUX(GPMC_NCS0, OMAP_MUX_MODE0),
	// 66 (C2, H, GPIO_52, PCM_SEL)
	OMAP3_MUX(GPMC_NCS1, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 67 (V8, H, GPIO_53, PS_OUT, I[H], OFF[H]) 
	OMAP3_MUX(GPMC_NCS2, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP),
	// 68 (U8, H, GPIO_54, IF_CON_SENSE18, I[L], OFF[L])
	OMAP3_MUX(GPMC_NCS3, OMAP_MUX_MODE4 | OMAP_PIN_INPUT),
	// 69 (B3, H, GPIO_55, FUEL_SCL, O)
	OMAP3_MUX(GPMC_NCS4, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLUP),
	// 70 (R8, H, GPT10_PWM_EVT, VIBTONE_PWM)
	OMAP3_MUX(GPMC_NCS5, OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLDOWN),
	// 71 (P8, H, GPIO_57, BOOT_MODE, [O])
	OMAP3_MUX(GPMC_NCS6, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 72 (N8, L, GPIO_58, LED_PWM , O[L], OFF[L])
	OMAP3_MUX(GPMC_NCS7, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 73 (T4, L, GPIO_59, GPMC_CLK, O[L], OFF[L])
	OMAP3_MUX(GPMC_CLK, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 74
	OMAP3_MUX(GPMC_NADV_ALE, OMAP_MUX_MODE0),
	// 75
	OMAP3_MUX(GPMC_NOE, OMAP_MUX_MODE0),
	// 76
	OMAP3_MUX(GPMC_NWE, OMAP_MUX_MODE0),
	// 77 (G3, L, SAFE_MODE, N/C, O)
	OMAP3_MUX(GPMC_NBE0_CLE, OMAP_MUX_MODE7 | OMAP_PIN_INPUT_PULLDOWN),
	// 78 (U3, L, GPIO_63, LCD_ID2, I)
	OMAP3_MUX(GPMC_NBE1, OMAP_MUX_MODE4 | OMAP_PIN_INPUT),
	// 79 (H1, L, GPIO_62, LCD_ID1, I)
	OMAP3_MUX(GPMC_NWP, OMAP_MUX_MODE4 | OMAP_PIN_INPUT),
	// 80 
	OMAP3_MUX(GPMC_WAIT0, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	// 81 (L8, H, GPIO_63, BT_nSHUTDOWN, O[L], OFF[L])
	OMAP3_MUX(GPMC_WAIT1, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	/* Skip uart settitng because it already set up in bootloader */
	/* 
	   // 82 (K8, H, GPIO_64, UART4_TX)
	   OMAP3_MUX(GPMC_WAIT2,  OMAP_MUX_MODE2 | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 83 (J8, H, GPIO_65, UART4_RX)
	   OMAP3_MUX(GPMC_WAIT3,        OMAP_MUX_MODE2 | OMAP_PIN_INPUT | OMAP_PIN_OFF_WAKEUPENABLE),
	 */

	// DSS PIN MUX CONFIGURATION
	// D0-D23 ARE ALL OUTPUT LINES AND SO NO NEED OF A PU/PD
	// HSYNC AND VSYNC ARE ALSO OUTPUT LINES.
	// DSS D18-21 ARE NOT USED FOR DISPLAY. THEY ARE MUXED TO GPIO FUNCTION.
	// DSS DAT LINES CONFIGURED FOR OUTPUT ONLY BASED ON THE FUNC.SPEC.
	// THE PINOUT_POP SHEET HOWEVER MENTIONS THEM AS I/O. CHECK...

	/* Skip dss settitng because it already set up in bootloader */
	/* 
	   // 84 (D28, H, DSS_PCLK, DISPLAY_MCLK, O)
	   OMAP3_MUX(DSS_PCLK,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 85 (D26, H, DSS_HSYNC, DISPLAY_HSYNC, O)
	   OMAP3_MUX(DSS_HSYNC,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 86 (D27, H, DSS_VSYNC, DISPLAY_VSYNC, O)
	   OMAP3_MUX(DSS_VSYNC,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 87 (E27, L, DSS_ACBIAS, DISPLAY_CE, O)
	   OMAP3_MUX(DSS_ACBIAS,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 88 (AG22, L, DSS_DATA0, LCD_D0, O)
	   OMAP3_MUX(DSS_DATA0,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 89 (AH22, L, DSS_DATA1, LCD_D1, O)
	   OMAP3_MUX(DSS_DATA1,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 90 (AG23, L, DSS_DATA2, LCD_D2, O)
	   OMAP3_MUX(DSS_DATA2,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 91 (AH23, L, DSS_DATA3, LCD_D3, O)
	   OMAP3_MUX(DSS_DATA3,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 92 (AG24, L, DSS_DATA4, LCD_D4, O)
	   OMAP3_MUX(DSS_DATA4,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 93 (AH24, L, DSS_DATA5, LCD_D5, O)
	   OMAP3_MUX(DSS_DATA5,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 94 (E26, L, DSS_DATA6, LCD_D6, O)
	   OMAP3_MUX(DSS_DATA6,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 95 (F28, L, DSS_DATA7, LCD_D7, O)
	   OMAP3_MUX(DSS_DATA7,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 96 (F27, L, DSS_DATA8, LCD_D8, O)
	   OMAP3_MUX(DSS_DATA8,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 97 (G26, L, DSS_DATA9, LCD_D9, O)
	   OMAP3_MUX(DSS_DATA9,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 98 (AD28, L, DSS_DATA10, LCD_D10, O)
	   OMAP3_MUX(DSS_DATA10,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 99 (AD27, L, DSS_DATA11, LCD_D11, O)
	   OMAP3_MUX(DSS_DATA11,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 100 (AB28, L, DSS_DATA12, LCD_D12, O)
	   OMAP3_MUX(DSS_DATA12,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 101 (AB27, L, DSS_DATA13, LCD_D13, O)
	   OMAP3_MUX(DSS_DATA13,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 102 (AA28, L, DSS_DATA14, LCD_D14, O)
	   OMAP3_MUX(DSS_DATA14,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 103 (AA27, L, DSS_DATA15, LCD_D15, O)
	   OMAP3_MUX(DSS_DATA15,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 104 (G25, L, DSS_DATA16, LCD_D16, O)
	   OMAP3_MUX(DSS_DATA16,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 105 (H27, L, DSS_DATA17, LCD_D17, O)
	   OMAP3_MUX(DSS_DATA17,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 106 (H26, L, DSS_DATA18, LCD_D18, O)
	   OMAP3_MUX(DSS_DATA18,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 107 (H25, L, DSS_DATA19, LCD_D19, O)
	   OMAP3_MUX(DSS_DATA19,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 108 (E28, L, DSS_DATA20, LCD_D20, O)
	   OMAP3_MUX(DSS_DATA20,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 109 (J26, L, DSS_DATA21, LCD_D21, O)
	   OMAP3_MUX(DSS_DATA21,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 110 (AC27, L, DSS_DATA22, LCD_D22, O)     
	   OMAP3_MUX(DSS_DATA22,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	   // 111 (AC28, L, DSS_DATA23, LCD_D23, O)
	   OMAP3_MUX(DSS_DATA23,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_OUTPUT_LOW),
	 */

	// CAMERA PIN MUX CONFIGURATION
	// CAM_FLD AND CAM_WEN ARE NOT USED IN CAMERA FUNCTION. THEY MIGHT BE USED FOR GPIO FUNCTION.
	// CAM_SHUTTER AND CAM_GLOBAL_RESET ARE BEING DRAWN FOR CAMERA FROM MCBSP1 SIGNALS.
	// ADDING THE MUX FOR THESE TWO PINS UNDER MCBSP1.
	// CAM_STROBE IS AN OUTPUT SIGNAL. REST ALL ARE EITHER I OR I/O.
	// CAM_HS AND CAM_VS ARE ACTIVE LOW SIGNALS FOR SENSOR MT9T012.
	// PCLK IS INPUT SIGNAL AND FOR NOW CONFIGURED AS PU.
	// CSIA CONFIGURED FOR I/O.

	// 112 (A24, L, CAM_HS, PIXEL_HSYNC, O)
	OMAP3_MUX(CAM_HS, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 113 (A23, L, CAM_VS, PIXEL_VSYNC, O)
	OMAP3_MUX(CAM_VS, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 114 (C25, L, CAM_XLCKA, PIXEL_MCLK, O)
	OMAP3_MUX(CAM_XCLKA, OMAP_MUX_MODE0),
	// 115 (C27, L, CAM_PCLK, PIXEL_PCLK, O)
	OMAP3_MUX(CAM_PCLK, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 116 (C23, L, GPIO_98, 5M_CAM_nRST, O[L], OFF[L])
	OMAP3_MUX(CAM_FLD, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 117 (AF16, L, GPIO_99, WLAN_IRQ) 
	OMAP3_MUX(CAM_D0, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 118 (AF15, L, SAFE_MODE, N/C) - 09/17
	OMAP3_MUX(CAM_D1, OMAP_MUX_MODE7 | OMAP_PIN_INPUT_PULLDOWN),
	// 119 (B24, L, GPIO_101, CIF_STBY, O[L], OFF[L])
	OMAP3_MUX(CAM_D2, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 120 (C24, L, GPIO_102, EAR_MICBIAS_EN, O[L], OFF[L])
	OMAP3_MUX(CAM_D3, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 121 (D24, L, CAM_D4, CAM_D0, I/O)
	OMAP3_MUX(CAM_D4, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 122 (A25, L, CAM_D5, CAM_D1, I/O)
	OMAP3_MUX(CAM_D5, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 123 (K28, L, CAM_D6, CAM_D2, I/O)
	OMAP3_MUX(CAM_D6, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 124 (L28, L, CAM_D7, CAM_D3, I/O)
	OMAP3_MUX(CAM_D7, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 125 (K27, L, CAM_D8, CAM_D4, I/O)
	OMAP3_MUX(CAM_D8, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 126 (L27, L, CAM_D9, CAM_D5, I/O)
	OMAP3_MUX(CAM_D9, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 127 (B25, L, CAM_D10, CAM_D6, I/O)
	OMAP3_MUX(CAM_D10, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 128 (C26, L, CAM_D11, CAM_D7, I/O)
	OMAP3_MUX(CAM_D11, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 129 (B26, L, GPIO_111, PDA_ACTIVE)
	OMAP3_MUX(CAM_XCLKB, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 130 (B20, L, GPIO_167, CP_ON, O[L], OFF[L])
	OMAP3_MUX(CAM_WEN, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	/* Skip dss settitng because it already set up in bootloader */
	/*
	   // 131 (D25, L, GPIO_126, UART_SEL, O[L], OFF[L])
	   OMAP3_MUX(CAM_STROBE,  OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	 */
	// 132 (AF18, L, GPIO_112, DET_3.5, I[U], OFF[U])
	OMAP3_MUX(CSI2_DX0, OMAP_MUX_MODE4 | OMAP_PIN_INPUT | OMAP_WAKEUP_EN),
	// 133 (AF17, L, GPIO_113, EAR_KEY, I[Z], OFF[L])
	OMAP3_MUX(CSI2_DY0, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP | OMAP_WAKEUP_EN),
	// 134 (AG18, L, GPIO_114, COMPASS_INT, I[L], OFF[L])
	OMAP3_MUX(CSI2_DX1, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 135 (AH18, L, GPIO_115, ACC_INT, I[L], OFF[L])
	OMAP3_MUX(CSI2_DY1, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),

	// MCBSP2 PIN MUX CONFIGURATION - USED FOR AUDIO
	// EXCEPT THE DX (TRANSMIT) LINE, EVERYTHING ELSE HAS TO BE INPUT ENABLED.
	// PU/PD DOES NOT MATTER FOR FUNCTIONALITY.

	// 136 (P21, L, MCBSP2_FSX, I2S_SYNC, I/O),
	OMAP3_MUX(MCBSP2_FSX, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 137 (N21, L, MCBSP2_CLKX, I2S_CLK, I/O)
	OMAP3_MUX(MCBSP2_CLKX, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 138 (R21, L, MCBSP2_DR, I2S_DIN, I)
	OMAP3_MUX(MCBSP2_DR, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 139 (M21, L, MCBSP2_DX, I2S_DOUT, O)
	OMAP3_MUX(MCBSP2_DX, OMAP_MUX_MODE0),

	// MMC1&2 PIN MUX CONFIG
	// MMC2 DAT4-7 LINES ARE USED FOR MMC2_DDIR0, MMC2_DDIR1, MMC2_CDIR AND MMC2_CLKI
	// EXCEPT FOR CLKOUT AND DIR LINES, EVERYTHING ELSE IS EITHER I OR I/O
	// NOT FULLY SURE OF MMC2_CLKIN (MUXED WITH MMC2_DAT7) LINE PU/PD VALUE.

	// 140 (N28, L, MMC1_CLK, TF_CLK, O)
	OMAP3_MUX(SDMMC1_CLK, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 141 (M27, L, MMC1_CMD, TF_CMD, I/O)
	OMAP3_MUX(SDMMC1_CMD, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 142 (N27, L, MMC1_DAT0, TF_DAT0, I/O)
	OMAP3_MUX(SDMMC1_DAT0, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 143 (N26, L, MMC1_DAT1, TF_DAT1, I/O)
	OMAP3_MUX(SDMMC1_DAT1, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 144 (N25, L, MMC1_DAT2, TF_DAT2, I/O)
	OMAP3_MUX(SDMMC1_DAT2, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 145 (P28, L, MMC1_DAT3, TF_DAT3, I/O)
	OMAP3_MUX(SDMMC1_DAT3, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),

	// 146 (K23, L, SAFE_MODE, N/C)
	OMAP3_MUX(SDMMC1_DAT4, OMAP_MUX_MODE7 | OMAP_PIN_INPUT_PULLDOWN),
	// 147 (P26, L, GPIO_127, SAFE_MODE, N/C)
	OMAP3_MUX(GPIO127, OMAP_MUX_MODE7 | OMAP_PIN_INPUT_PULLDOWN),
	// 148 (R27, L, GPIO_128, SAFE_MODE, N/C)
	OMAP3_MUX(GPIO128, OMAP_MUX_MODE7 | OMAP_PIN_INPUT_PULLDOWN),
	// 149 (R25, L, SAFE_MODE, N/C)
	OMAP3_MUX(SDMMC1_DAT7, OMAP_MUX_MODE7 | OMAP_PIN_INPUT_PULLDOWN),

	// 150 (AE2, L, NAND_CLK, O[L], OFF[L])
	OMAP3_MUX(SDMMC2_CLK, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 151 (AG5, H, NAND_CMD, O[L], OFF[L])
	OMAP3_MUX(SDMMC2_CMD, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),

	// 152 (AH5, H, MMC2_DAT0, MOVI_DAT0)
	OMAP3_MUX(SDMMC2_DAT0, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 153 (AH4, H, MMC2_DAT1, MOVI_DAT1)
	OMAP3_MUX(SDMMC2_DAT1, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 154 (AG4, H, MMC2_DAT2, MOVI_DAT2)
	OMAP3_MUX(SDMMC2_DAT2, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 155 (AF4, H, MMC2_DAT3, MOVI_DAT3)
	OMAP3_MUX(SDMMC2_DAT3, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 156 (AE4, H, MMC2_DAT4)
	OMAP3_MUX(SDMMC2_DAT4, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 157 (AH3, H, MMC2_DAT5)
	OMAP3_MUX(SDMMC2_DAT5, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 158 (AF3, H, MMC2_DAT6)
	OMAP3_MUX(SDMMC2_DAT6, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 159 (AE3, H, MMC2_DAT7)
	OMAP3_MUX(SDMMC2_DAT7, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLDOWN),

	// MCBSP2 PIN MUXING
	// EXCEPT THE DX (TRANSMIT) LINE, EVERYTHING ELSE HAS TO BE INPUT ENABLED.
	// PU/PD DOES NOT MATTER FOR FUNCTIONALITY.

	// 160 (AF6, L, GPIO_140, RESET_REQ_N, O[L], OFF[L])
	OMAP3_MUX(MCBSP3_DX, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 161 (AE6, L, GPIO_141, VIBTONE_EN, O[L], OFF[L])
	OMAP3_MUX(MCBSP3_DR, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 162 (AF5, L, GPIO_142, TOUCH_INT, I[L], OFF[L])
	OMAP3_MUX(MCBSP3_CLKX, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP),
	// 163 (AE5, L, GPIO_143, TOUCH_EN, O[L], OFF[L])
	OMAP3_MUX(MCBSP3_FSX, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),

	// UART2 PIN MUX CONFIGURATION.
	// CTS IS AN ACTIVE LOW INPUT SIGNAL AND SO IT SHOULD BE PULLED UP.

	// 164 (AB26, H, UART2_CTS, BT_CTS, I)
	OMAP3_MUX(UART2_CTS, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),
	// 165 (AB25, H, UART2_RTS, BT_RTS, O)
	OMAP3_MUX(UART2_RTS, OMAP_MUX_MODE0),
	// 166 (AA25, H, UART2_TX, BT_TXD, O)
	OMAP3_MUX(UART2_TX, OMAP_MUX_MODE0),
	// 167 (AD25, H, UART2_RX, BT_RXD, I)
	OMAP3_MUX(UART2_RX, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),

	// UART1 PIN CONFIGURATION - ON THE BOARD, THESE PINS ACTUALLY WERE GETTING
	// CONNECTED TO SSI. BUT NOW SOME HW MODS ARE BEING DONE AND ON NEW BOARDS
	// THESE LINES WILL BE CONNECTED TO DB9 AND SO MUST BE MUXED TO UART1.

	// 168 (AA8, L, MIPI_TX_DATA, O)
	OMAP3_MUX(UART1_TX, OMAP_MUX_MODE1 | OMAP_PIN_OUTPUT),
	// 169 (AA9, MIPI_TX_FLG, O)
	OMAP3_MUX(UART1_RTS, OMAP_MUX_MODE1 | OMAP_PIN_OUTPUT),
	// 170 (W8, MIPI_TX_RDY, I)
	OMAP3_MUX(UART1_CTS, OMAP_MUX_MODE1 | OMAP_PIN_INPUT_PULLDOWN),
	// 171 (Y8, L, GPIO_151, CAM_VGA_nRST, O[L], OFF[L])
	OMAP3_MUX(UART1_RX, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),

	// MCBSP4 AND MCBSP1 PIN CONFIGURATION
	// ALL MCBSP4 SIGNALS ARE CONNECTED TO SSI.

	// 172 (AE1, L, MIPI_RX_DATA, I)
	OMAP3_MUX(MCBSP4_CLKX, OMAP_MUX_MODE1 | OMAP_PIN_INPUT_PULLDOWN),
	// 173 (AD1, L, MIPI_RX_FLG, I)
	OMAP3_MUX(MCBSP4_DR, OMAP_MUX_MODE1 | OMAP_PIN_INPUT_PULLDOWN),
	// 174 (AD2, L, MIPI_RX_RDY, O)
	OMAP3_MUX(MCBSP4_DX, OMAP_MUX_MODE1 | OMAP_PIN_OUTPUT),
	// 175 (M8, L, MIPI_WAKE, O)
	OMAP3_MUX(MCBSP4_FSX, OMAP_MUX_MODE1 | OMAP_PIN_OUTPUT),

	// MCBSP1_FSR IS USED IN CAM_GLOBAL_RESET FUNCTION.
	// MCBSP1_CLKX IS USED IN CAM_SHUTTER FUNCTION.
	// MCBSP1_DX TO BE USED IN GPIO_158 FUNCTION.

	// 176 (Y21, L, MCBSP1_CLKR, FM_RST, I[L])
	OMAP3_MUX(MCBSP1_CLKR, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 177 (AA21, L, GPIO_161, CHG_EN, O[L], OFF[L])
	OMAP3_MUX(MCBSP1_FSR, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 178 (N18, L, GPIO_158, OMAP_GPIO_LED_EN1, O[L])
	OMAP3_MUX(MCBSP1_DX, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 179 (U21, L, GPIO_159 MASSMEMORY_EN O[L])
	OMAP3_MUX(MCBSP1_DR, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 180 (T21, L, GPIO_160, WLAN_EN, O[L], OFF[L])
	OMAP3_MUX(MCBSP_CLKS, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 181 (K26, L, GPIO_161, CP_VBUS_EN, I/O)
	OMAP3_MUX(MCBSP1_FSX, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 182 (W21, H, GOIO_162, OMAP_GPIO_LED_EN2, O[L])
	OMAP3_MUX(MCBSP1_CLKX, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),

	// UART3 PIN MUX CONFIGURATION.
	// 183 (H18, H, GPS_UART_CTS)
	OMAP3_MUX(UART3_CTS_RCTX, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),
	// 184 (H19, H, GPS_UART_RTS)
	OMAP3_MUX(UART3_RTS_SD, OMAP_MUX_MODE0),
	// 185 (H20, H, UART3_RX, AP_UART_RXD1)
	OMAP3_MUX(UART3_RX_IRRX, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),
	// 186 (H21, H, UART3_TX, AP_UART_TXD1)
	OMAP3_MUX(UART3_TX_IRTX, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),

	// HSUSB SIGNALS
	// 187 (T28, L, HSUSB0_CLK, USB0HS_CLK, I)
	OMAP3_MUX(HSUSB0_CLK, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 188 (T25, H, HSUSB0_STP, USB0HS_STP, O)
	OMAP3_MUX(HSUSB0_STP, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLUP),
	// 189 (R28, L, HSUSB0_DIR, USB0HS_DIR, I)
	OMAP3_MUX(HSUSB0_DIR, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLUP),
	// 190 (T26, L, HSUSB0_NXT, USB0HS_NXT, I)
	OMAP3_MUX(HSUSB0_NXT, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 191 (T27, L, HSUSB0_DATA0, USB0HS_DATA0, I/O)
	OMAP3_MUX(HSUSB0_DATA0, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 192 (U28, L, HSUSB0_DATA1, USB0HS_DATA1, I/O)
	OMAP3_MUX(HSUSB0_DATA1, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 193 (U27, L, HSUSB0_DATA2, USB0HS_DATA2, I/O)
	OMAP3_MUX(HSUSB0_DATA2, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 194 (U26, L, HSUSB0_DATA3, USB0HS_DATA3, I/O)
	OMAP3_MUX(HSUSB0_DATA3, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 195 (U25, L, HSUSB0_DATA4, USB0HS_DATA4, I/O)
	OMAP3_MUX(HSUSB0_DATA4, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 196 (V28, L, HSUSB0_DATA5, USB0HS_DATA5, I/O)
	OMAP3_MUX(HSUSB0_DATA5, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 197 (V27, L, HSUSB0_DAT6, USB0HS_DATA6, I/O)
	OMAP3_MUX(HSUSB0_DATA6, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 198 (V26, L, HSUSB0_DAT7, USB0HS_DATA7, I/O)
	OMAP3_MUX(HSUSB0_DATA7, OMAP_MUX_MODE0 | OMAP_PIN_INPUT | OMAP_PIN_OFF_INPUT_PULLDOWN),

	// I2C PIN MUX CONFIGURATION
	// 199 (K21, I2C1_SCL, PWR_SCL, I/O)
	OMAP3_MUX(I2C1_SCL, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	// 200 (J21, I2C1_SDA, PWR_SDA, I/O)
	OMAP3_MUX(I2C1_SDA, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	// 201 (AF15, H, I2C2_SCL, SCL, I/O)
	OMAP3_MUX(I2C2_SCL, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	// 202 (AE15, H, I2C2_SDA, SDA, I/O)
	OMAP3_MUX(I2C2_SDA, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	// 203 (AF14, H, I2C3_SCL, TOUCH_I2C_SCL, I/O)
	OMAP3_MUX(I2C3_SCL, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	// 204 (AG14, H, I2C3_SDA, TOUCH_I2C_SDA, I/O)
	OMAP3_MUX(I2C3_SDA, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),

	// HDQ CONFIGURATION
	// 205 (J25, H, GPIO_170, MLCD_RST, O[H], OFF[L])
	OMAP3_MUX(HDQ_SIO, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP),

	// MCSPI1 AND MCSPI2 PIN CONFIGURATION
	// FOR ALL SPI, SPI_CS0 IS I/O AND OTHER SPI CS ARE PURE OUT.
	// CLK AND SIMO/SOMI LINES ARE I/O.
	// 206 (AB3, L, MCSPI1_CLK, DISPLAY_CLK, O)
	OMAP3_MUX(MCSPI1_CLK, OMAP_MUX_MODE0),
	// 207 (AB4, L, MCSPI1_SIMO, DISLPAY_SI, I)
	OMAP3_MUX(MCSPI1_SIMO, OMAP_MUX_MODE0),
	// 208 (AA4, H, GPIO_173, LCD_SDO, DISLPAY_SO, O)
	OMAP3_MUX(MCSPI1_SOMI, OMAP_MUX_MODE0 | OMAP_PIN_OFF_INPUT_PULLDOWN),
	// 209 (AC2, H, MCSPI1_CS0, DISPLAY_CS, O)
	OMAP3_MUX(MCSPI1_CS0, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	// 210 (AC3, H, MCSPI1_CS1, WLAN_CMD, O)
	OMAP3_MUX(MCSPI1_CS1, OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLUP),
	// 211 (AB1, H, MCSPI1_CS2, WLAN_CLK, O)
	OMAP3_MUX(MCSPI1_CS2, OMAP_MUX_MODE3 | OMAP_PIN_INPUT_PULLUP),
	// 212 (AB2, H, GPIO_177, AMP_SHDN) 
	OMAP3_MUX(MCSPI1_CS3, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),

	// 213 (H9, L, GPIO_178, HW_REV0)
	OMAP3_MUX(MCSPI2_CLK, OMAP_MUX_MODE4 | OMAP_PIN_INPUT),
	// 214 (J10, L, GPIO_179, MSENSE_nRST)
	OMAP3_MUX(MCSPI2_SIMO, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 215 (H10, L, GPIO_180, CAM_EN1)
	OMAP3_MUX(MCSPI2_SOMI, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 216 (H11, H, GPIO_181, CAM_5M_nSTBY)
	OMAP3_MUX(MCSPI2_CS0, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN),
	// 217 (J11, L, GPIO_182, HW_REV1)
	OMAP3_MUX(MCSPI2_CS1, OMAP_MUX_MODE4 | OMAP_PIN_INPUT),

	// SYS_NIRQ CAN BE USED IN SYS_NIRQ FUNCTION AS WELL AS GPIO AS T2 INTERRUPT IS CONNECTED HERE.
	// 218 (AF26, H, GPIO_0, SYS_NIRQ0, I)
	OMAP3_MUX(SYS_NIRQ, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP | OMAP_WAKEUP_EN),

	// GPIO_186 (CAMSENSOR_EN2)
	OMAP3_MUX(SYS_CLKOUT2, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),

	// SYS_CLKOUT2 IS GOING TO BBIO_29 AND SO MUXING IT IN GPIO FUNCTION.
	// 219 (AE22, L, SAFE_MODE, N/C)
	/* OMAP3_MUX("AE22_SYS_CLKOUT2", 0x01E2, OMAP_MUX_MODE7) */

	// WAKEUP DOMAIN PADS

	// 283 I2C_SR_SCL
	OMAP3_MUX(I2C4_SCL, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	// 284 I2C_SR_SDA
	OMAP3_MUX(I2C4_SDA, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	// 285 SYS_32K DOES NOT HAVE ANY PU/PD. OR MODE. ONLY I/O OR JUST O.
	OMAP3_MUX(SYS_32K, OMAP_PIN_INPUT),
	// 286 (AF25, 0, SYS_CLKREQ, SYS_CLKREQ, I)
	OMAP3_MUX(SYS_CLKREQ, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 287 (AF24, 0, SYS_NRESWARM, NWARM_RESETOUT, I)
	OMAP3_MUX(SYS_NRESWARM, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),

	// SYS_BOOT SIGNALS DO NOT HAVE ANY PU/PD FUNCTIONALITY.
	// 288 (AH26, Z, SYS_BOOT0, SYS_BOOT0, I[Z])
	OMAP3_MUX(SYS_BOOT0, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),
	// 289 (AG26, Z, SYS_BOOT1, SYS_BOOT1, I[Z])
	OMAP3_MUX(SYS_BOOT1, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),
	// 290 (AE14, Z, SYS_BOOT2, SYS_BOOT2, I[Z])
	OMAP3_MUX(SYS_BOOT2, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),
	// 291 (AF18, Z, SYS_BOOT3, SYS_BOOT3, I[Z])
	OMAP3_MUX(SYS_BOOT3, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),
	// 292 (AF19, Z, SYS_BOOT4, SYS_BOOT4, I[Z])
	OMAP3_MUX(SYS_BOOT4, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),
	// 293 (AE21, Z, SYS_BOOT5, SYS_BOOT5, I[Z])
	OMAP3_MUX(SYS_BOOT5, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),
	// 294 (AF21, Z, SYS_BOOT6, SYS_BOOT6, I[Z])
	OMAP3_MUX(SYS_BOOT6, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),

	// 295 (AF22, 0, SYS_OFF_MODE, SYS_OFF_MODE, O) 
	OMAP3_MUX(SYS_OFF_MODE, OMAP_MUX_MODE0),

	// 296 (AG25, L, GPIO_10, USBSW_Nint, I[H], OFF[H])
	OMAP3_MUX(SYS_CLKOUT1, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP),

	// 297 
	OMAP3_MUX(JTAG_NTRST, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 298
	OMAP3_MUX(JTAG_TCK, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 299
	OMAP3_MUX(JTAG_TMS_TMSC, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLDOWN),
	// 300
	OMAP3_MUX(JTAG_TDI, OMAP_MUX_MODE0 | OMAP_PIN_INPUT),

	// 301 (AA11, H, SAFE_MODE, GPIO_11, N/C)
	OMAP3_MUX(JTAG_EMU0, OMAP_MUX_MODE7 | OMAP_PIN_INPUT_PULLDOWN),
	// 302 (W10, H, SAFE_MODE, N/C) - 09/17
	OMAP3_MUX(JTAG_EMU1, OMAP_MUX_MODE7 | OMAP_PIN_INPUT_PULLDOWN),

	//FOR NORMAL EXECUTION
	// ETK_D8 SIGNAL WAS MUXED FOR MSECURE FUNCTIONALITY AND IS OK ON NON GP DEVICES.
	// HOWEVER ON GP DEVICES, THE MSECURE LINE IS NOT DRIVEN HIGH BY OMAP AND SO WE
	// NEED TO MUX IT IN GPIO MODE AND DRIVE IT HIGH.

	// 303 (AF10, H, GPIO_12, FUEL_INT_N, I[H], OFF[H])
	OMAP3_MUX(ETK_CLK, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP | OMAP_WAKEUP_EN),
	// 304 (AE10, H, GPIO_13, NAND_INT, I[H], OFF[H])
	OMAP3_MUX(ETK_CTL, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP),
	// 305 (AF11, H, GPIO_14,  FM_SCL, I[H]) // 10/15 gatz92jeon
	OMAP3_MUX(ETK_D0, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLUP),
	// 306 (AG12, H, GPIO_15, FM_SDA, I[H]) // 10/15 gatz92jeon
	OMAP3_MUX(ETK_D1, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLUP),
	// 307 (AH12, H, GPIO_16, CHG_ING_N, I[H], OFF[H])
	OMAP3_MUX(ETK_D2, OMAP_MUX_MODE4 | OMAP_PIN_INPUT | OMAP_WAKEUP_EN),	//EXTERNAL PULL-UP

	// 308 (AE13, H, MMC3_DATA3, WLAN_D(3), IO)
	OMAP3_MUX(ETK_D3, OMAP_MUX_MODE2 | OMAP_PIN_INPUT_PULLUP),
	// 309 (AE11, L, MMC3_DATA0, WLAN_D(0), IO)
	OMAP3_MUX(ETK_D4, OMAP_MUX_MODE2 | OMAP_PIN_INPUT_PULLUP),
	// 310 (AH9, L, MMC3_DATA1, WLAN_D(1), IO)
	OMAP3_MUX(ETK_D5, OMAP_MUX_MODE2 | OMAP_PIN_INPUT_PULLUP),
	// 311 (AF13, L, MMC3_DATA(2), WLAN_D(2), IO)
	OMAP3_MUX(ETK_D6, OMAP_MUX_MODE2 | OMAP_PIN_INPUT_PULLUP),
	// 312 (AH14, L, GPIO_21, PHONE_ACTIVE, I[L], OFF[H])
	OMAP3_MUX(ETK_D7, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN | OMAP_PIN_OFF_INPUT_PULLUP),
	// 313 (AF9, L, GPIO_22, SYS_DRM_MSECURE, O[H], OFF[H])
	OMAP3_MUX(ETK_D8, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 314 (AG9, L, GPIO_23, TF_DETECT, I[H], OFF[H])
	OMAP3_MUX(ETK_D9, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP | OMAP_WAKEUP_EN),	//EXTERNAL PULL-UP
	// 315 (AE7, L, GPIO_24, KEY_PWRON, I[L], OFF[L])
	OMAP3_MUX(ETK_D10,
			  OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLDOWN | OMAP_WAKEUP_EN),
	/* Skip ps_hold settitng because it already set up in bootloader */
	/*
	   // 316 (AF7, L, GPIO_25, PS_HOLD_PU, O[H], OFF[H])
	   OMAP3_MUX(ETK_D11, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP),
	 */
	// 317 (AG7, L, GPIO_26, KEY_HOME)
	OMAP3_MUX(ETK_D12, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP),
	// 318 (AC5, L, GPIO_27, CON_CP_BOOT)
	OMAP3_MUX(ETK_D13, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP),
	// 319 (AG8, L, GPIO_28, ALS_EN, O[L], OFF[L])
	OMAP3_MUX(ETK_D14, OMAP_MUX_MODE4 | OMAP_PIN_OUTPUT),
	// 320 (AH8, L, GPIO_29, TA_NCONNECTED, I[H], OFF[H])
	OMAP3_MUX(ETK_D15, OMAP_MUX_MODE4 | OMAP_PIN_INPUT_PULLUP | OMAP_PIN_OFF_INPUT_PULLUP),	// Brian: NC

	// 321
	//OMAP3_MUX("_D2D_SWAKEUP", 0x0A4C,  OMAP_MUX_MODE0 | OMAP_PIN_INPUT)
	{.reg_offset = OMAP_MUX_TERMINATOR},
};

unsigned int omap34xx_mux_size = ARRAY_SIZE(board_mux);
EXPORT_SYMBOL(omap34xx_mux_size);
struct omap_board_mux *omap34xx_mux_ptr = board_mux;
EXPORT_SYMBOL(omap34xx_mux_ptr);
