/*
 * Copyright (C) 2009 Nokia
 * Copyright (C) 2009 Texas Instruments
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define OMAP3_CONTROL_PADCONF_MUX_PBASE				0x48002030LU

#define OMAP3_MUX(mode0, mux_value)					\
{									\
	.reg_offset	= (OMAP3_CONTROL_PADCONF_##mode0##_OFFSET),	\
	.value		= (mux_value),					\
}

/*
 * OMAP3 CONTROL_PADCONF* register offsets for pin-muxing
 *
 * Extracted from the TRM.  Add 0x48002030 to these values to get the
 * absolute addresses.  The name in the macro is the mode-0 name of
 * the pin.  NOTE: These registers are 16-bits wide.
 *
 * Note that 34XX TRM uses MMC instead of SDMMC and SAD2D instead
 * of CHASSIS for some registers. For the defines, we follow the
 * 36XX naming, and use SDMMC and CHASSIS.
 */
#define OMAP3_CONTROL_PADCONF_SDRC_D0_OFFSET			0x000
#define OMAP3_CONTROL_PADCONF_SDRC_D1_OFFSET			0x002
#define OMAP3_CONTROL_PADCONF_SDRC_D2_OFFSET			0x004
#define OMAP3_CONTROL_PADCONF_SDRC_D3_OFFSET			0x006
#define OMAP3_CONTROL_PADCONF_SDRC_D4_OFFSET			0x008
#define OMAP3_CONTROL_PADCONF_SDRC_D5_OFFSET			0x00a
#define OMAP3_CONTROL_PADCONF_SDRC_D6_OFFSET			0x00c
#define OMAP3_CONTROL_PADCONF_SDRC_D7_OFFSET			0x00e
#define OMAP3_CONTROL_PADCONF_SDRC_D8_OFFSET			0x010
#define OMAP3_CONTROL_PADCONF_SDRC_D9_OFFSET			0x012
#define OMAP3_CONTROL_PADCONF_SDRC_D10_OFFSET			0x014
#define OMAP3_CONTROL_PADCONF_SDRC_D11_OFFSET			0x016
#define OMAP3_CONTROL_PADCONF_SDRC_D12_OFFSET			0x018
#define OMAP3_CONTROL_PADCONF_SDRC_D13_OFFSET			0x01a
#define OMAP3_CONTROL_PADCONF_SDRC_D14_OFFSET			0x01c
#define OMAP3_CONTROL_PADCONF_SDRC_D15_OFFSET			0x01e
#define OMAP3_CONTROL_PADCONF_SDRC_D16_OFFSET			0x020
#define OMAP3_CONTROL_PADCONF_SDRC_D17_OFFSET			0x022
#define OMAP3_CONTROL_PADCONF_SDRC_D18_OFFSET			0x024
#define OMAP3_CONTROL_PADCONF_SDRC_D19_OFFSET			0x026
#define OMAP3_CONTROL_PADCONF_SDRC_D20_OFFSET			0x028
#define OMAP3_CONTROL_PADCONF_SDRC_D21_OFFSET			0x02a
#define OMAP3_CONTROL_PADCONF_SDRC_D22_OFFSET			0x02c
#define OMAP3_CONTROL_PADCONF_SDRC_D23_OFFSET			0x02e
#define OMAP3_CONTROL_PADCONF_SDRC_D24_OFFSET			0x030
#define OMAP3_CONTROL_PADCONF_SDRC_D25_OFFSET			0x032
#define OMAP3_CONTROL_PADCONF_SDRC_D26_OFFSET			0x034
#define OMAP3_CONTROL_PADCONF_SDRC_D27_OFFSET			0x036
#define OMAP3_CONTROL_PADCONF_SDRC_D28_OFFSET			0x038
#define OMAP3_CONTROL_PADCONF_SDRC_D29_OFFSET			0x03a
#define OMAP3_CONTROL_PADCONF_SDRC_D30_OFFSET			0x03c
#define OMAP3_CONTROL_PADCONF_SDRC_D31_OFFSET			0x03e
#define OMAP3_CONTROL_PADCONF_SDRC_CLK_OFFSET			0x040
#define OMAP3_CONTROL_PADCONF_SDRC_DQS0_OFFSET			0x042
#define OMAP3_CONTROL_PADCONF_SDRC_DQS1_OFFSET			0x044
#define OMAP3_CONTROL_PADCONF_SDRC_DQS2_OFFSET			0x046
#define OMAP3_CONTROL_PADCONF_SDRC_DQS3_OFFSET			0x048
#define OMAP3_CONTROL_PADCONF_GPMC_A1_OFFSET			0x04a
#define OMAP3_CONTROL_PADCONF_GPMC_A2_OFFSET			0x04c
#define OMAP3_CONTROL_PADCONF_GPMC_A3_OFFSET			0x04e
#define OMAP3_CONTROL_PADCONF_GPMC_A4_OFFSET			0x050
#define OMAP3_CONTROL_PADCONF_GPMC_A5_OFFSET			0x052
#define OMAP3_CONTROL_PADCONF_GPMC_A6_OFFSET			0x054
#define OMAP3_CONTROL_PADCONF_GPMC_A7_OFFSET			0x056
#define OMAP3_CONTROL_PADCONF_GPMC_A8_OFFSET			0x058
#define OMAP3_CONTROL_PADCONF_GPMC_A9_OFFSET			0x05a
#define OMAP3_CONTROL_PADCONF_GPMC_A10_OFFSET			0x05c
#define OMAP3_CONTROL_PADCONF_GPMC_D0_OFFSET			0x05e
#define OMAP3_CONTROL_PADCONF_GPMC_D1_OFFSET			0x060
#define OMAP3_CONTROL_PADCONF_GPMC_D2_OFFSET			0x062
#define OMAP3_CONTROL_PADCONF_GPMC_D3_OFFSET			0x064
#define OMAP3_CONTROL_PADCONF_GPMC_D4_OFFSET			0x066
#define OMAP3_CONTROL_PADCONF_GPMC_D5_OFFSET			0x068
#define OMAP3_CONTROL_PADCONF_GPMC_D6_OFFSET			0x06a
#define OMAP3_CONTROL_PADCONF_GPMC_D7_OFFSET			0x06c
#define OMAP3_CONTROL_PADCONF_GPMC_D8_OFFSET			0x06e
#define OMAP3_CONTROL_PADCONF_GPMC_D9_OFFSET			0x070
#define OMAP3_CONTROL_PADCONF_GPMC_D10_OFFSET			0x072
#define OMAP3_CONTROL_PADCONF_GPMC_D11_OFFSET			0x074
#define OMAP3_CONTROL_PADCONF_GPMC_D12_OFFSET			0x076
#define OMAP3_CONTROL_PADCONF_GPMC_D13_OFFSET			0x078
#define OMAP3_CONTROL_PADCONF_GPMC_D14_OFFSET			0x07a
#define OMAP3_CONTROL_PADCONF_GPMC_D15_OFFSET			0x07c
#define OMAP3_CONTROL_PADCONF_GPMC_NCS0_OFFSET			0x07e
#define OMAP3_CONTROL_PADCONF_GPMC_NCS1_OFFSET			0x080
#define OMAP3_CONTROL_PADCONF_GPMC_NCS2_OFFSET			0x082
#define OMAP3_CONTROL_PADCONF_GPMC_NCS3_OFFSET			0x084
#define OMAP3_CONTROL_PADCONF_GPMC_NCS4_OFFSET			0x086
#define OMAP3_CONTROL_PADCONF_GPMC_NCS5_OFFSET			0x088
#define OMAP3_CONTROL_PADCONF_GPMC_NCS6_OFFSET			0x08a
#define OMAP3_CONTROL_PADCONF_GPMC_NCS7_OFFSET			0x08c
#define OMAP3_CONTROL_PADCONF_GPMC_CLK_OFFSET			0x08e
#define OMAP3_CONTROL_PADCONF_GPMC_NADV_ALE_OFFSET		0x090
#define OMAP3_CONTROL_PADCONF_GPMC_NOE_OFFSET			0x092
#define OMAP3_CONTROL_PADCONF_GPMC_NWE_OFFSET			0x094
#define OMAP3_CONTROL_PADCONF_GPMC_NBE0_CLE_OFFSET		0x096
#define OMAP3_CONTROL_PADCONF_GPMC_NBE1_OFFSET			0x098
#define OMAP3_CONTROL_PADCONF_GPMC_NWP_OFFSET			0x09a
#define OMAP3_CONTROL_PADCONF_GPMC_WAIT0_OFFSET			0x09c
#define OMAP3_CONTROL_PADCONF_GPMC_WAIT1_OFFSET			0x09e
#define OMAP3_CONTROL_PADCONF_GPMC_WAIT2_OFFSET			0x0a0
#define OMAP3_CONTROL_PADCONF_GPMC_WAIT3_OFFSET			0x0a2
#define OMAP3_CONTROL_PADCONF_DSS_PCLK_OFFSET			0x0a4
#define OMAP3_CONTROL_PADCONF_DSS_HSYNC_OFFSET			0x0a6
#define OMAP3_CONTROL_PADCONF_DSS_VSYNC_OFFSET			0x0a8
#define OMAP3_CONTROL_PADCONF_DSS_ACBIAS_OFFSET			0x0aa
#define OMAP3_CONTROL_PADCONF_DSS_DATA0_OFFSET			0x0ac
#define OMAP3_CONTROL_PADCONF_DSS_DATA1_OFFSET			0x0ae
#define OMAP3_CONTROL_PADCONF_DSS_DATA2_OFFSET			0x0b0
#define OMAP3_CONTROL_PADCONF_DSS_DATA3_OFFSET			0x0b2
#define OMAP3_CONTROL_PADCONF_DSS_DATA4_OFFSET			0x0b4
#define OMAP3_CONTROL_PADCONF_DSS_DATA5_OFFSET			0x0b6
#define OMAP3_CONTROL_PADCONF_DSS_DATA6_OFFSET			0x0b8
#define OMAP3_CONTROL_PADCONF_DSS_DATA7_OFFSET			0x0ba
#define OMAP3_CONTROL_PADCONF_DSS_DATA8_OFFSET			0x0bc
#define OMAP3_CONTROL_PADCONF_DSS_DATA9_OFFSET			0x0be
#define OMAP3_CONTROL_PADCONF_DSS_DATA10_OFFSET			0x0c0
#define OMAP3_CONTROL_PADCONF_DSS_DATA11_OFFSET			0x0c2
#define OMAP3_CONTROL_PADCONF_DSS_DATA12_OFFSET			0x0c4
#define OMAP3_CONTROL_PADCONF_DSS_DATA13_OFFSET			0x0c6
#define OMAP3_CONTROL_PADCONF_DSS_DATA14_OFFSET			0x0c8
#define OMAP3_CONTROL_PADCONF_DSS_DATA15_OFFSET			0x0ca
#define OMAP3_CONTROL_PADCONF_DSS_DATA16_OFFSET			0x0cc
#define OMAP3_CONTROL_PADCONF_DSS_DATA17_OFFSET			0x0ce
#define OMAP3_CONTROL_PADCONF_DSS_DATA18_OFFSET			0x0d0
#define OMAP3_CONTROL_PADCONF_DSS_DATA19_OFFSET			0x0d2
#define OMAP3_CONTROL_PADCONF_DSS_DATA20_OFFSET			0x0d4
#define OMAP3_CONTROL_PADCONF_DSS_DATA21_OFFSET			0x0d6
#define OMAP3_CONTROL_PADCONF_DSS_DATA22_OFFSET			0x0d8
#define OMAP3_CONTROL_PADCONF_DSS_DATA23_OFFSET			0x0da
#define OMAP3_CONTROL_PADCONF_CAM_HS_OFFSET			0x0dc
#define OMAP3_CONTROL_PADCONF_CAM_VS_OFFSET			0x0de
#define OMAP3_CONTROL_PADCONF_CAM_XCLKA_OFFSET			0x0e0
#define OMAP3_CONTROL_PADCONF_CAM_PCLK_OFFSET			0x0e2
#define OMAP3_CONTROL_PADCONF_CAM_FLD_OFFSET			0x0e4
#define OMAP3_CONTROL_PADCONF_CAM_D0_OFFSET			0x0e6
#define OMAP3_CONTROL_PADCONF_CAM_D1_OFFSET			0x0e8
#define OMAP3_CONTROL_PADCONF_CAM_D2_OFFSET			0x0ea
#define OMAP3_CONTROL_PADCONF_CAM_D3_OFFSET			0x0ec
#define OMAP3_CONTROL_PADCONF_CAM_D4_OFFSET			0x0ee
#define OMAP3_CONTROL_PADCONF_CAM_D5_OFFSET			0x0f0
#define OMAP3_CONTROL_PADCONF_CAM_D6_OFFSET			0x0f2
#define OMAP3_CONTROL_PADCONF_CAM_D7_OFFSET			0x0f4
#define OMAP3_CONTROL_PADCONF_CAM_D8_OFFSET			0x0f6
#define OMAP3_CONTROL_PADCONF_CAM_D9_OFFSET			0x0f8
#define OMAP3_CONTROL_PADCONF_CAM_D10_OFFSET			0x0fa
#define OMAP3_CONTROL_PADCONF_CAM_D11_OFFSET			0x0fc
#define OMAP3_CONTROL_PADCONF_CAM_XCLKB_OFFSET			0x0fe
#define OMAP3_CONTROL_PADCONF_CAM_WEN_OFFSET			0x100
#define OMAP3_CONTROL_PADCONF_CAM_STROBE_OFFSET			0x102
#define OMAP3_CONTROL_PADCONF_CSI2_DX0_OFFSET			0x104
#define OMAP3_CONTROL_PADCONF_CSI2_DY0_OFFSET			0x106
#define OMAP3_CONTROL_PADCONF_CSI2_DX1_OFFSET			0x108
#define OMAP3_CONTROL_PADCONF_CSI2_DY1_OFFSET			0x10a
#define OMAP3_CONTROL_PADCONF_MCBSP2_FSX_OFFSET			0x10c
#define OMAP3_CONTROL_PADCONF_MCBSP2_CLKX_OFFSET		0x10e
#define OMAP3_CONTROL_PADCONF_MCBSP2_DR_OFFSET			0x110
#define OMAP3_CONTROL_PADCONF_MCBSP2_DX_OFFSET			0x112
#define OMAP3_CONTROL_PADCONF_SDMMC1_CLK_OFFSET			0x114
#define OMAP3_CONTROL_PADCONF_SDMMC1_CMD_OFFSET			0x116
#define OMAP3_CONTROL_PADCONF_SDMMC1_DAT0_OFFSET		0x118
#define OMAP3_CONTROL_PADCONF_SDMMC1_DAT1_OFFSET		0x11a
#define OMAP3_CONTROL_PADCONF_SDMMC1_DAT2_OFFSET		0x11c
#define OMAP3_CONTROL_PADCONF_SDMMC1_DAT3_OFFSET		0x11e

/* SDMMC1_DAT4 - DAT7 are SIM_IO SIM_CLK SIM_PWRCTRL and SIM_RST on 36xx */
#define OMAP3_CONTROL_PADCONF_SDMMC1_DAT4_OFFSET		0x120
#define OMAP3_CONTROL_PADCONF_SDMMC1_DAT5_OFFSET		0x122
#define OMAP3_CONTROL_PADCONF_SDMMC1_DAT6_OFFSET		0x124
#define OMAP3_CONTROL_PADCONF_SDMMC1_DAT7_OFFSET		0x126

#define OMAP3_CONTROL_PADCONF_SDMMC2_CLK_OFFSET			0x128
#define OMAP3_CONTROL_PADCONF_SDMMC2_CMD_OFFSET			0x12a
#define OMAP3_CONTROL_PADCONF_SDMMC2_DAT0_OFFSET		0x12c
#define OMAP3_CONTROL_PADCONF_SDMMC2_DAT1_OFFSET		0x12e
#define OMAP3_CONTROL_PADCONF_SDMMC2_DAT2_OFFSET		0x130
#define OMAP3_CONTROL_PADCONF_SDMMC2_DAT3_OFFSET		0x132
#define OMAP3_CONTROL_PADCONF_SDMMC2_DAT4_OFFSET		0x134
#define OMAP3_CONTROL_PADCONF_SDMMC2_DAT5_OFFSET		0x136
#define OMAP3_CONTROL_PADCONF_SDMMC2_DAT6_OFFSET		0x138
#define OMAP3_CONTROL_PADCONF_SDMMC2_DAT7_OFFSET		0x13a
#define OMAP3_CONTROL_PADCONF_MCBSP3_DX_OFFSET			0x13c
#define OMAP3_CONTROL_PADCONF_MCBSP3_DR_OFFSET			0x13e
#define OMAP3_CONTROL_PADCONF_MCBSP3_CLKX_OFFSET		0x140
#define OMAP3_CONTROL_PADCONF_MCBSP3_FSX_OFFSET			0x142
#define OMAP3_CONTROL_PADCONF_UART2_CTS_OFFSET			0x144
#define OMAP3_CONTROL_PADCONF_UART2_RTS_OFFSET			0x146
#define OMAP3_CONTROL_PADCONF_UART2_TX_OFFSET			0x148
#define OMAP3_CONTROL_PADCONF_UART2_RX_OFFSET			0x14a
#define OMAP3_CONTROL_PADCONF_UART1_TX_OFFSET			0x14c
#define OMAP3_CONTROL_PADCONF_UART1_RTS_OFFSET			0x14e
#define OMAP3_CONTROL_PADCONF_UART1_CTS_OFFSET			0x150
#define OMAP3_CONTROL_PADCONF_UART1_RX_OFFSET			0x152
#define OMAP3_CONTROL_PADCONF_MCBSP4_CLKX_OFFSET		0x154
#define OMAP3_CONTROL_PADCONF_MCBSP4_DR_OFFSET			0x156
#define OMAP3_CONTROL_PADCONF_MCBSP4_DX_OFFSET			0x158
#define OMAP3_CONTROL_PADCONF_MCBSP4_FSX_OFFSET			0x15a
#define OMAP3_CONTROL_PADCONF_MCBSP1_CLKR_OFFSET		0x15c
#define OMAP3_CONTROL_PADCONF_MCBSP1_FSR_OFFSET			0x15e
#define OMAP3_CONTROL_PADCONF_MCBSP1_DX_OFFSET			0x160
#define OMAP3_CONTROL_PADCONF_MCBSP1_DR_OFFSET			0x162
#define OMAP3_CONTROL_PADCONF_MCBSP_CLKS_OFFSET			0x164
#define OMAP3_CONTROL_PADCONF_MCBSP1_FSX_OFFSET			0x166
#define OMAP3_CONTROL_PADCONF_MCBSP1_CLKX_OFFSET		0x168
#define OMAP3_CONTROL_PADCONF_UART3_CTS_RCTX_OFFSET		0x16a
#define OMAP3_CONTROL_PADCONF_UART3_RTS_SD_OFFSET		0x16c
#define OMAP3_CONTROL_PADCONF_UART3_RX_IRRX_OFFSET		0x16e
#define OMAP3_CONTROL_PADCONF_UART3_TX_IRTX_OFFSET		0x170
#define OMAP3_CONTROL_PADCONF_HSUSB0_CLK_OFFSET			0x172
#define OMAP3_CONTROL_PADCONF_HSUSB0_STP_OFFSET			0x174
#define OMAP3_CONTROL_PADCONF_HSUSB0_DIR_OFFSET			0x176
#define OMAP3_CONTROL_PADCONF_HSUSB0_NXT_OFFSET			0x178
#define OMAP3_CONTROL_PADCONF_HSUSB0_DATA0_OFFSET		0x17a
#define OMAP3_CONTROL_PADCONF_HSUSB0_DATA1_OFFSET		0x17c
#define OMAP3_CONTROL_PADCONF_HSUSB0_DATA2_OFFSET		0x17e
#define OMAP3_CONTROL_PADCONF_HSUSB0_DATA3_OFFSET		0x180
#define OMAP3_CONTROL_PADCONF_HSUSB0_DATA4_OFFSET		0x182
#define OMAP3_CONTROL_PADCONF_HSUSB0_DATA5_OFFSET		0x184
#define OMAP3_CONTROL_PADCONF_HSUSB0_DATA6_OFFSET		0x186
#define OMAP3_CONTROL_PADCONF_HSUSB0_DATA7_OFFSET		0x188
#define OMAP3_CONTROL_PADCONF_I2C1_SCL_OFFSET			0x18a
#define OMAP3_CONTROL_PADCONF_I2C1_SDA_OFFSET			0x18c
#define OMAP3_CONTROL_PADCONF_I2C2_SCL_OFFSET			0x18e
#define OMAP3_CONTROL_PADCONF_I2C2_SDA_OFFSET			0x190
#define OMAP3_CONTROL_PADCONF_I2C3_SCL_OFFSET			0x192
#define OMAP3_CONTROL_PADCONF_I2C3_SDA_OFFSET			0x194
#define OMAP3_CONTROL_PADCONF_HDQ_SIO_OFFSET			0x196
#define OMAP3_CONTROL_PADCONF_MCSPI1_CLK_OFFSET			0x198
#define OMAP3_CONTROL_PADCONF_MCSPI1_SIMO_OFFSET		0x19a
#define OMAP3_CONTROL_PADCONF_MCSPI1_SOMI_OFFSET		0x19c
#define OMAP3_CONTROL_PADCONF_MCSPI1_CS0_OFFSET			0x19e
#define OMAP3_CONTROL_PADCONF_MCSPI1_CS1_OFFSET			0x1a0
#define OMAP3_CONTROL_PADCONF_MCSPI1_CS2_OFFSET			0x1a2
#define OMAP3_CONTROL_PADCONF_MCSPI1_CS3_OFFSET			0x1a4
#define OMAP3_CONTROL_PADCONF_MCSPI2_CLK_OFFSET			0x1a6
#define OMAP3_CONTROL_PADCONF_MCSPI2_SIMO_OFFSET		0x1a8
#define OMAP3_CONTROL_PADCONF_MCSPI2_SOMI_OFFSET		0x1aa
#define OMAP3_CONTROL_PADCONF_MCSPI2_CS0_OFFSET			0x1ac
#define OMAP3_CONTROL_PADCONF_MCSPI2_CS1_OFFSET			0x1ae
#define OMAP3_CONTROL_PADCONF_SYS_NIRQ_OFFSET			0x1b0
#define OMAP3_CONTROL_PADCONF_SYS_CLKOUT2_OFFSET		0x1b2
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD0_OFFSET		0x1b4
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD1_OFFSET		0x1b6
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD2_OFFSET		0x1b8
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD3_OFFSET		0x1ba
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD4_OFFSET		0x1bc
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD5_OFFSET		0x1be
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD6_OFFSET		0x1c0
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD7_OFFSET		0x1c2
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD8_OFFSET		0x1c4
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD9_OFFSET		0x1c6
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD10_OFFSET		0x1c8
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD11_OFFSET		0x1ca
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD12_OFFSET		0x1cc
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD13_OFFSET		0x1ce
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD14_OFFSET		0x1d0
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD15_OFFSET		0x1d2
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD16_OFFSET		0x1d4
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD17_OFFSET		0x1d6
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD18_OFFSET		0x1d8
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD19_OFFSET		0x1da
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD20_OFFSET		0x1dc
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD21_OFFSET		0x1de
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD22_OFFSET		0x1e0
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD23_OFFSET		0x1e2
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD24_OFFSET		0x1e4
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD25_OFFSET		0x1e6
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD26_OFFSET		0x1e8
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD27_OFFSET		0x1ea
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD28_OFFSET		0x1ec
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD29_OFFSET		0x1ee
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD30_OFFSET		0x1f0
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD31_OFFSET		0x1f2
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD32_OFFSET		0x1f4
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD33_OFFSET		0x1f6
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD34_OFFSET		0x1f8
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD35_OFFSET		0x1fa
#define OMAP3_CONTROL_PADCONF_SAD2D_MCAD36_OFFSET		0x1fc

/* Note that 34xx TRM has SAD2D instead of CHASSIS for these */
#define OMAP3_CONTROL_PADCONF_CHASSIS_CLK26MI_OFFSET		0x1fe
#define OMAP3_CONTROL_PADCONF_CHASSIS_NRESPWRON_OFFSET		0x200
#define OMAP3_CONTROL_PADCONF_CHASSIS_NRESWARW_OFFSET		0x202
#define OMAP3_CONTROL_PADCONF_CHASSIS_NIRQ_OFFSET		0x204
#define OMAP3_CONTROL_PADCONF_CHASSIS_FIQ_OFFSET		0x206
#define OMAP3_CONTROL_PADCONF_CHASSIS_ARMIRQ_OFFSET		0x208
#define OMAP3_CONTROL_PADCONF_CHASSIS_IVAIRQ_OFFSET		0x20a
#define OMAP3_CONTROL_PADCONF_CHASSIS_DMAREQ0_OFFSET		0x20c
#define OMAP3_CONTROL_PADCONF_CHASSIS_DMAREQ1_OFFSET		0x20e
#define OMAP3_CONTROL_PADCONF_CHASSIS_DMAREQ2_OFFSET		0x210
#define OMAP3_CONTROL_PADCONF_CHASSIS_DMAREQ3_OFFSET		0x212
#define OMAP3_CONTROL_PADCONF_CHASSIS_NTRST_OFFSET		0x214
#define OMAP3_CONTROL_PADCONF_CHASSIS_TDI_OFFSET		0x216
#define OMAP3_CONTROL_PADCONF_CHASSIS_TDO_OFFSET		0x218
#define OMAP3_CONTROL_PADCONF_CHASSIS_TMS_OFFSET		0x21a
#define OMAP3_CONTROL_PADCONF_CHASSIS_TCK_OFFSET		0x21c
#define OMAP3_CONTROL_PADCONF_CHASSIS_RTCK_OFFSET		0x21e
#define OMAP3_CONTROL_PADCONF_CHASSIS_MSTDBY_OFFSET		0x220
#define OMAP3_CONTROL_PADCONF_CHASSIS_IDLEREQ_OFFSET		0x222
#define OMAP3_CONTROL_PADCONF_CHASSIS_IDLEACK_OFFSET		0x224

#define OMAP3_CONTROL_PADCONF_SAD2D_MWRITE_OFFSET		0x226
#define OMAP3_CONTROL_PADCONF_SAD2D_SWRITE_OFFSET		0x228
#define OMAP3_CONTROL_PADCONF_SAD2D_MREAD_OFFSET		0x22a
#define OMAP3_CONTROL_PADCONF_SAD2D_SREAD_OFFSET		0x22c
#define OMAP3_CONTROL_PADCONF_SAD2D_MBUSFLAG_OFFSET		0x22e
#define OMAP3_CONTROL_PADCONF_SAD2D_SBUSFLAG_OFFSET		0x230
#define OMAP3_CONTROL_PADCONF_SDRC_CKE0_OFFSET			0x232
#define OMAP3_CONTROL_PADCONF_SDRC_CKE1_OFFSET			0x234

/* 36xx only */
#define OMAP3_CONTROL_PADCONF_GPMC_A11_OFFSET			0x236
#define OMAP3_CONTROL_PADCONF_SDRC_BA0_OFFSET			0x570
#define OMAP3_CONTROL_PADCONF_SDRC_BA1_OFFSET			0x572
#define OMAP3_CONTROL_PADCONF_SDRC_A0_OFFSET			0x574
#define OMAP3_CONTROL_PADCONF_SDRC_A1_OFFSET			0x576
#define OMAP3_CONTROL_PADCONF_SDRC_A2_OFFSET			0x578
#define OMAP3_CONTROL_PADCONF_SDRC_A3_OFFSET			0x57a
#define OMAP3_CONTROL_PADCONF_SDRC_A4_OFFSET			0x57c
#define OMAP3_CONTROL_PADCONF_SDRC_A5_OFFSET			0x57e
#define OMAP3_CONTROL_PADCONF_SDRC_A6_OFFSET			0x580
#define OMAP3_CONTROL_PADCONF_SDRC_A7_OFFSET			0x582
#define OMAP3_CONTROL_PADCONF_SDRC_A8_OFFSET			0x584
#define OMAP3_CONTROL_PADCONF_SDRC_A9_OFFSET			0x586
#define OMAP3_CONTROL_PADCONF_SDRC_A10_OFFSET			0x588
#define OMAP3_CONTROL_PADCONF_SDRC_A11_OFFSET			0x58a
#define OMAP3_CONTROL_PADCONF_SDRC_A12_OFFSET			0x58c
#define OMAP3_CONTROL_PADCONF_SDRC_A13_OFFSET			0x58e
#define OMAP3_CONTROL_PADCONF_SDRC_A14_OFFSET			0x590
#define OMAP3_CONTROL_PADCONF_SDRC_NCS0_OFFSET			0x592
#define OMAP3_CONTROL_PADCONF_SDRC_NCS1_OFFSET			0x594
#define OMAP3_CONTROL_PADCONF_SDRC_NCLK_OFFSET			0x596
#define OMAP3_CONTROL_PADCONF_SDRC_NRAS_OFFSET			0x598
#define OMAP3_CONTROL_PADCONF_SDRC_NCAS_OFFSET			0x59a
#define OMAP3_CONTROL_PADCONF_SDRC_NWE_OFFSET			0x59c
#define OMAP3_CONTROL_PADCONF_SDRC_DM0_OFFSET			0x59e
#define OMAP3_CONTROL_PADCONF_SDRC_DM1_OFFSET			0x5a0
#define OMAP3_CONTROL_PADCONF_SDRC_DM2_OFFSET			0x5a2
#define OMAP3_CONTROL_PADCONF_SDRC_DM3_OFFSET			0x5a4

/* 36xx only, these are SDMMC1_DAT4 - DAT7 on 34xx */
#define OMAP3_CONTROL_PADCONF_SIM_IO_OFFSET			0x120
#define OMAP3_CONTROL_PADCONF_SIM_CLK_OFFSET			0x122
#define OMAP3_CONTROL_PADCONF_SIM_PWRCTRL_OFFSET		0x124
#define OMAP3_CONTROL_PADCONF_SIM_RST_OFFSET			0x126

#define OMAP3_CONTROL_PADCONF_ETK_CLK_OFFSET			0x5a8
#define OMAP3_CONTROL_PADCONF_ETK_CTL_OFFSET			0x5aa
#define OMAP3_CONTROL_PADCONF_ETK_D0_OFFSET			0x5ac
#define OMAP3_CONTROL_PADCONF_ETK_D1_OFFSET			0x5ae
#define OMAP3_CONTROL_PADCONF_ETK_D2_OFFSET			0x5b0
#define OMAP3_CONTROL_PADCONF_ETK_D3_OFFSET			0x5b2
#define OMAP3_CONTROL_PADCONF_ETK_D4_OFFSET			0x5b4
#define OMAP3_CONTROL_PADCONF_ETK_D5_OFFSET			0x5b6
#define OMAP3_CONTROL_PADCONF_ETK_D6_OFFSET			0x5b8
#define OMAP3_CONTROL_PADCONF_ETK_D7_OFFSET			0x5ba
#define OMAP3_CONTROL_PADCONF_ETK_D8_OFFSET			0x5bc
#define OMAP3_CONTROL_PADCONF_ETK_D9_OFFSET			0x5be
#define OMAP3_CONTROL_PADCONF_ETK_D10_OFFSET			0x5c0
#define OMAP3_CONTROL_PADCONF_ETK_D11_OFFSET			0x5c2
#define OMAP3_CONTROL_PADCONF_ETK_D12_OFFSET			0x5c4
#define OMAP3_CONTROL_PADCONF_ETK_D13_OFFSET			0x5c6
#define OMAP3_CONTROL_PADCONF_ETK_D14_OFFSET			0x5c8
#define OMAP3_CONTROL_PADCONF_ETK_D15_OFFSET			0x5ca
#define OMAP3_CONTROL_PADCONF_I2C4_SCL_OFFSET			0x9d0
#define OMAP3_CONTROL_PADCONF_I2C4_SDA_OFFSET			0x9d2
#define OMAP3_CONTROL_PADCONF_SYS_32K_OFFSET			0x9d4
#define OMAP3_CONTROL_PADCONF_SYS_CLKREQ_OFFSET			0x9d6
#define OMAP3_CONTROL_PADCONF_SYS_NRESWARM_OFFSET		0x9d8
#define OMAP3_CONTROL_PADCONF_SYS_BOOT0_OFFSET			0x9da
#define OMAP3_CONTROL_PADCONF_SYS_BOOT1_OFFSET			0x9dc
#define OMAP3_CONTROL_PADCONF_SYS_BOOT2_OFFSET			0x9de
#define OMAP3_CONTROL_PADCONF_SYS_BOOT3_OFFSET			0x9e0
#define OMAP3_CONTROL_PADCONF_SYS_BOOT4_OFFSET			0x9e2
#define OMAP3_CONTROL_PADCONF_SYS_BOOT5_OFFSET			0x9e4
#define OMAP3_CONTROL_PADCONF_SYS_BOOT6_OFFSET			0x9e6
#define OMAP3_CONTROL_PADCONF_SYS_OFF_MODE_OFFSET		0x9e8
#define OMAP3_CONTROL_PADCONF_SYS_CLKOUT1_OFFSET		0x9ea
#define OMAP3_CONTROL_PADCONF_JTAG_NTRST_OFFSET			0x9ec
#define OMAP3_CONTROL_PADCONF_JTAG_TCK_OFFSET			0x9ee
#define OMAP3_CONTROL_PADCONF_JTAG_TMS_TMSC_OFFSET		0x9f0
#define OMAP3_CONTROL_PADCONF_JTAG_TDI_OFFSET			0x9f2
#define OMAP3_CONTROL_PADCONF_JTAG_EMU0_OFFSET			0x9f4
#define OMAP3_CONTROL_PADCONF_JTAG_EMU1_OFFSET			0x9f6
#define OMAP3_CONTROL_PADCONF_SAD2D_SWAKEUP_OFFSET		0xa1c
#define OMAP3_CONTROL_PADCONF_JTAG_RTCK_OFFSET			0xa1e
#define OMAP3_CONTROL_PADCONF_JTAG_TDO_OFFSET			0xa20
#define OMAP3_CONTROL_PADCONF_GPIO127_OFFSET			0xa24
#define OMAP3_CONTROL_PADCONF_GPIO128_OFFSET			0xa28

#define OMAP3_CONTROL_PADCONF_MUX_SIZE				\
		(OMAP3_CONTROL_PADCONF_JTAG_TDO_OFFSET + 0x2)
