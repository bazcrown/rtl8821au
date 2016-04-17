
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

#ifndef __HAL8812PWRSEQ_H__
#define __HAL8812PWRSEQ_H__

#include "HalPwrSeqCmd.h"

/* 
	Check document WB-110628-DZ-RTL8195 (Jaguar) Power Architecture-R04.pdf
	There are 6 HW Power States:
	0: POFF--Power Off
	1: PDN--Power Down
	2: CARDEMU--Card Emulation
	3: ACT--Active Mode
	4: LPS--Low Power State
	5: SUS--Suspend

	The transision from different states are defined below
	TRANS_CARDEMU_TO_ACT
	TRANS_ACT_TO_CARDEMU
	TRANS_CARDEMU_TO_SUS
	TRANS_SUS_TO_CARDEMU
	TRANS_CARDEMU_TO_PDN
	TRANS_ACT_TO_LPS
	TRANS_LPS_TO_ACT	

	TRANS_END
*/
#define	RTL8812_TRANS_CARDEMU_TO_ACT_STEPS	15
#define	RTL8812_TRANS_ACT_TO_CARDEMU_STEPS	15
#define	RTL8812_TRANS_CARDEMU_TO_SUS_STEPS	15
#define	RTL8812_TRANS_SUS_TO_CARDEMU_STEPS	15
#define	RTL8812_TRANS_CARDEMU_TO_PDN_STEPS	15
#define	RTL8812_TRANS_PDN_TO_CARDEMU_STEPS	15
#define	RTL8812_TRANS_ACT_TO_LPS_STEPS	15
#define	RTL8812_TRANS_LPS_TO_ACT_STEPS	15	
#define	RTL8812_TRANS_END_STEPS	1


#define RTL8812_TRANS_CARDEMU_TO_ACT 														\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(2), 0},/* disable SW LPS 0x04[10]=0*/	\
	{0x0006, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, BIT(1), BIT(1)},/* wait till 0x04[17] = 1    power ready*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(7), 0},/* disable HWPDN 0x04[15]=0*/ \
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(3), 0},/* disable WL suspend*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(0), BIT(0)},/* polling until return 0*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, BIT(0), 0},/**/

#define RTL8812_TRANS_ACT_TO_CARDEMU													\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0c00, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x04}, /* 0xc00[7:0] = 4	turn off 3-wire */	\
	{0x0e00, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x04}, /* 0xe00[7:0] = 4	turn off 3-wire */	\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(0), 0}, /* 0x2[0] = 0	 RESET BB, CLOSE RF */	\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_DELAY, 0, PWRSEQ_DELAY_US},/*Delay 1us*/	\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(1), 0},  /* Whole BB is reset*/			\
	/*{0x001F, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0},//0x1F[7:0] = 0 turn off RF*/	\
	/*{0x004E, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(7), 0},//0x4C[23] = 0x4E[7] = 0, switch DPDT_SEL_P output from register 0x65[2] */	\
	{0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x28}, /* 0x07[7:0] = 0x28 sps pwm mode */	\
	{0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x02, 0},/*0x8[1] = 0 ANA clk =500k */	\
	/*{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(0)|BIT(1), 0}, //  0x02[1:0] = 0	reset BB */	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(1), BIT(1)}, /*0x04[9] = 1 turn off MAC by HW state machine*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, BIT(1), 0}, /*wait till 0x04[9] = 0 polling until return 0 to disable*/	

#define RTL8812_TRANS_CARDEMU_TO_SUS													\
	/* format */								\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0042, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xF0, 0xcc},\
	{0x0042, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xF0, 0xEC},\
	{0x0043, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x07},/* gpio11 input mode, gpio10~8 output mode */	\
	{0x0045, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x00},/* gpio 0~7 output same value as input ?? */	\
	{0x0046, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0xff},/* gpio0~7 output mode */	\
	{0x0047, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0},/* 0x47[7:0] = 00 gpio mode */	\
	{0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0},/* suspend option all off */	\
	{0x0014, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x80, BIT(7)},/*0x14[7] = 1 turn on ZCD */	\
	{0x0015, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x01, BIT(0)},/* 0x15[0] =1 trun on ZCD */	\
	{0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x10, BIT(4)},/*0x23[4] = 1 hpon LDO sleep mode */	\
	{0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x02, 0},/*0x8[1] = 0 ANA clk =500k */	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(3), BIT(3)}, /*0x04[11] = 2b'11 enable WL suspend for PCIe*/	

#define RTL8812_TRANS_SUS_TO_CARDEMU													\
	/* format */								\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(3), 0}, /*0x04[11] = 2b'01enable WL suspend*/   \
	{0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x10, 0},/*0x23[4] = 0 hpon LDO sleep mode leave */	\
	{0x0015, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x01, 0},/* 0x15[0] =0 trun off ZCD */	\
	{0x0014, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x80, 0},/*0x14[7] = 0 turn off ZCD */	\
	{0x0046, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x00},/* gpio0~7 input mode */	\
	{0x0043, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x00},/* gpio11 input mode, gpio10~8 input mode */

#define RTL8812_TRANS_CARDEMU_TO_CARDDIS													\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	/**{0x0194, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(0), 0}, //0x194[0]=0 , disable 32K clock*/	\
	/**{0x0093, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x94}, //0x93=0x94 , 90[30] =0 enable 500k ANA clock .switch clock from 12M to 500K , 90 [26] =0 disable EEprom loader clock*/	\
	{0x0003, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(2), 0}, /*0x03[2] = 0, reset 8051*/	\
	{0x0080, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x05}, /*0x80=05h if reload fw, fill the default value of host_CPU handshake field*/	\
	{0x0042, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xF0, 0xcc},\
	{0x0042, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xF0, 0xEC},\
	{0x0043, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x07},/* gpio11 input mode, gpio10~8 output mode */	\
	{0x0045, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x00},/* gpio 0~7 output same value as input ?? */	\
	{0x0046, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0xff},/* gpio0~7 output mode */	\
	{0x0047, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0},/* 0x47[7:0] = 00 gpio mode */	\
	{0x0014, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x80, BIT(7)},/*0x14[7] = 1 turn on ZCD */	\
	{0x0015, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x01, BIT(0)},/* 0x15[0] =1 trun on ZCD */	\
	{0x0012, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x01, 0},/*0x12[0] = 0 force PFM mode */	\
	{0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x10, BIT(4)},/*0x23[4] = 1 hpon LDO sleep mode */	\
	{0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x02, 0},/*0x8[1] = 0 ANA clk =500k */	\
	{0x0007, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x20}, /*0x07=0x20 , SOP option to disable BG/MB*/	\
	{0x001f, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(1), 0}, /*0x01f[1]=0 , disable RFC_0  control  REG_RF_CTRL_8812 */	\
	{0x0076, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(1), 0}, /*0x076[1]=0 , disable RFC_1  control REG_OPT_CTRL_8812 +2 */	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(3), BIT(3)}, /*0x04[11] = 2b'01 enable WL suspend*/	

#define RTL8812_TRANS_CARDDIS_TO_CARDEMU													\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/                       \
	{0x0012, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(0), BIT(0)},/*0x12[0] = 1 force PWM mode */	\
	{0x0014, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x80, 0},/*0x14[7] = 0 turn off ZCD */	\
	{0x0015, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x01, 0},/* 0x15[0] =0 trun off ZCD */	\
	{0x0023, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0x10, 0},/*0x23[4] = 0 hpon LDO leave sleep mode */	\
	{0x0046, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x00},/* gpio0~7 input mode */	\
	{0x0043, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x00},/* gpio11 input mode, gpio10~8 input mode */ \
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(2), 0}, /*0x04[10] = 0, enable SW LPS PCIE only*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(3), 0}, /*0x04[11] = 2b'01enable WL suspend*/	\
	{0x0003, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(2), BIT(2)}, /*0x03[2] = 1, enable 8051*/	\
	{0x0301, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0},/*PCIe DMA start*/


#define RTL8812_TRANS_CARDEMU_TO_PDN												\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(7), BIT(7)},/* 0x04[15] = 1*/

#define RTL8812_TRANS_PDN_TO_CARDEMU												\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/	\
	{0x0005, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(7), 0},/* 0x04[15] = 0*/

#define RTL8812_TRANS_ACT_TO_LPS														\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/								\
	{0x0301, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0xFF},/*PCIe DMA stop*/	\
	{0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x7F},/*Tx Pause*/		\
	{0x05F8, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, 0xFF, 0},/*Should be zero if no packet is transmitting*/	\
	{0x05F9, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, 0xFF, 0},/*Should be zero if no packet is transmitting*/	\
	{0x05FA, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, 0xFF, 0},/*Should be zero if no packet is transmitting*/	\
	{0x05FB, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, 0xFF, 0},/*Should be zero if no packet is transmitting*/	\
	{0x0c00, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x04}, /* 0xc00[7:0] = 4	turn off 3-wire */	\
	{0x0e00, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x04}, /* 0xe00[7:0] = 4	turn off 3-wire */	\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(0), 0},/*CCK and OFDM are disabled,and clock are gated,and RF closed*/	\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_DELAY, 0, PWRSEQ_DELAY_US},/*Delay 1us*/	\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(1), 0},  /* Whole BB is reset*/			\
	{0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x03},/*Reset MAC TRX*/			\
	{0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(1), 0},/*check if removed later*/		\
	{0x0553, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(5), BIT(5)},/*Respond TxOK to scheduler*/	


#define RTL8812_TRANS_LPS_TO_ACT															\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/	\
	{0x0080, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_SDIO_MSK,PWR_BASEADDR_SDIO,PWR_CMD_WRITE, 0xFF, 0x84}, /*SDIO RPWM*/	\
	{0xFE58, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_USB_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x84}, /*USB RPWM*/	\
	{0x0361, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_PCI_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0x84}, /*PCIe RPWM*/	\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_DELAY, 0, PWRSEQ_DELAY_MS}, /*Delay*/	\
	{0x0008, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(4), 0}, /*.	0x08[4] = 0		 switch TSF to 40M*/	\
	{0x0109, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_POLLING, BIT(7), 0}, /*Polling 0x109[7]=0  TSF in 40M*/			\
	{0x0029, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(6)|BIT(7), 0}, /*.	0x29[7:6] = 2b'00	 enable BB clock*/	\
	{0x0101, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(1), BIT(1)}, /*.	0x101[1] = 1*/					\
	{0x0100, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0xFF}, /*.	0x100[7:0] = 0xFF	 enable WMAC TRX*/	\
	{0x0002, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, BIT(1)|BIT(0), BIT(1)|BIT(0)}, /*.	0x02[1:0] = 2b'11	 enable BB macro*/	\
	{0x0522, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,PWR_BASEADDR_MAC,PWR_CMD_WRITE, 0xFF, 0}, /*.	0x522 = 0*/
 
#define RTL8812_TRANS_END																\
	/* format */																\
	/* { offset, cut_msk, fab_msk|interface_msk, base|cmd, msk, value }, // comments here*/		\
	{0xFFFF, PWR_CUT_ALL_MSK, PWR_FAB_ALL_MSK, PWR_INTF_ALL_MSK,0,PWR_CMD_END, 0, 0}, //


extern struct wlan_pwr_cfg rtl8812_power_on_flow[RTL8812_TRANS_CARDEMU_TO_ACT_STEPS+RTL8812_TRANS_END_STEPS];
extern struct wlan_pwr_cfg rtl8812_radio_off_flow[RTL8812_TRANS_ACT_TO_CARDEMU_STEPS+RTL8812_TRANS_END_STEPS];
extern struct wlan_pwr_cfg rtl8812_card_disable_flow[RTL8812_TRANS_ACT_TO_CARDEMU_STEPS+RTL8812_TRANS_CARDEMU_TO_PDN_STEPS+RTL8812_TRANS_END_STEPS];
extern struct wlan_pwr_cfg rtl8812_card_enable_flow[RTL8812_TRANS_ACT_TO_CARDEMU_STEPS+RTL8812_TRANS_CARDEMU_TO_PDN_STEPS+RTL8812_TRANS_END_STEPS];
extern struct wlan_pwr_cfg rtl8812_suspend_flow[RTL8812_TRANS_ACT_TO_CARDEMU_STEPS+RTL8812_TRANS_CARDEMU_TO_SUS_STEPS+RTL8812_TRANS_END_STEPS];
extern struct wlan_pwr_cfg rtl8812_resume_flow[RTL8812_TRANS_ACT_TO_CARDEMU_STEPS+RTL8812_TRANS_CARDEMU_TO_SUS_STEPS+RTL8812_TRANS_END_STEPS];
extern struct wlan_pwr_cfg rtl8812_hwpdn_flow[RTL8812_TRANS_ACT_TO_CARDEMU_STEPS+RTL8812_TRANS_CARDEMU_TO_PDN_STEPS+RTL8812_TRANS_END_STEPS];
extern struct wlan_pwr_cfg rtl8812_enter_lps_flow[RTL8812_TRANS_ACT_TO_LPS_STEPS+RTL8812_TRANS_END_STEPS];
extern struct wlan_pwr_cfg rtl8812_leave_lps_flow[RTL8812_TRANS_LPS_TO_ACT_STEPS+RTL8812_TRANS_END_STEPS];

#endif //__HAL8812PWRSEQ_H__

