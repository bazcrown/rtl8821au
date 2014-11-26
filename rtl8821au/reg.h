#ifndef __RTL8821AU_REG_H__
#define __RTL8821AU_REG_H__


// TX AGC 
#define RTXAGC_A_CCK11_CCK1				0xc20
#define RTXAGC_A_OFDM18_OFDM6				0xc24
#define RTXAGC_A_OFDM54_OFDM24				0xc28
#define RTXAGC_A_MCS03_MCS00				0xc2c
#define RTXAGC_A_MCS07_MCS04				0xc30
#define RTXAGC_A_MCS11_MCS08				0xc34
#define RTXAGC_A_MCS15_MCS12				0xc38

#define rTxAGC_A_Nss1Index3_Nss1Index0_JAguar	0xc3c
#define rTxAGC_A_Nss1Index7_Nss1Index4_JAguar	0xc40
#define rTxAGC_A_Nss2Index1_Nss1Index8_JAguar	0xc44
#define rTxAGC_A_Nss2Index5_Nss2Index2_JAguar	0xc48
#define rTxAGC_A_Nss2Index9_Nss2Index6_JAguar	0xc4c


#define RTXAGC_B_CCK11_CCK1				0xe20
#define RTXAGC_B_OFDM18_OFDM6				0xe24
#define RTXAGC_B_OFDM54_OFDM24				0xe28
#define RTXAGC_B_MCS03_MCS00				0xe2c
#define RTXAGC_B_MCS07_MCS04				0xe30
#define RTXAGC_B_MCS11_MCS08				0xe34
#define RTXAGC_B_MCS15_MCS12				0xe38

#define rTxAGC_B_Nss1Index3_Nss1Index0_JAguar		0xe3c
#define rTxAGC_B_Nss1Index7_Nss1Index4_JAguar		0xe40
#define rTxAGC_B_Nss2Index1_Nss1Index8_JAguar		0xe44
#define rTxAGC_B_Nss2Index5_Nss2Index2_JAguar		0xe48
#define rTxAGC_B_Nss2Index9_Nss2Index6_JAguar		0xe4c
#define bTxAGC_byte0_Jaguar							0xff
#define bTxAGC_byte1_Jaguar							0xff00
#define bTxAGC_byte2_Jaguar							0xff0000
#define bTxAGC_byte3_Jaguar							0xff000000

#endif