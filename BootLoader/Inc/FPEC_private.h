/**************************************************************************************
 *  [File Name]	 : FPEC_private.h
 *	[Version]	 : V01
 *  [Author]	 : Mohamed Saeed
 **************************************************************************************/

#ifndef FPEC_PRIVATE_H_
#define FPEC_PRIVATE_H_

/* Register defintions */
typedef struct
{
	volatile u32 FLASH_ACR;
	volatile u32 FLASH_KEYR;
	volatile u32 FLASH_OPTKEYR;
	volatile u32 FLASH_SR;
	volatile u32 FLASH_CR;
	volatile u32 FLASH_AR;
	volatile u32 RESERVED;
	volatile u32 FLASH_OBR;
	volatile u32 FLASH_WRPR;
}MFPEC_t;

#define MFPEC    	((volatile MFPEC_t *)0x40022000)

/* Register bits */

/* FLASH_SR */
#define    BSY       0
#define    PGERR     2
#define    WRPRTERR  4
#define    EOP       5

/* FLASH_CR */
#define    PG        0
#define    PER       1
#define    MER       2
#define    OPTPG     4
#define    OPTER     5
#define    STRT      6
#define    LOCK      7
#define    OPTWRE    9
#define    ERRIE     10
#define    EOPIE     12

/* Lock keys */
#define    FPEC_KEY1    0x45670123
#define    FPEC_KEY2    0xCDEF89AB
#define    RDPRT_key    0x00A5

#endif /* FPEC_PRIVATE_H_ */
