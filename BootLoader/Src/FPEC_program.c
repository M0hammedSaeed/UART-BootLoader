/**************************************************************************************
 *  [File Name]	 : FPEC_program.c
 *	[Version]	 : V01
 *  [Author]	 : Mohamed Saeed
 **************************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "FPEC_interface.h"
#include "FPEC_private.h"
#include "FPEC_config.h"

void MFPEC_voidWriteHalfWord(u32 Copy_u32Address, u16 Copy_u16Data)
{
	/* Wait if read or write operation is under execution */
	while(GET_BIT(MFPEC->FLASH_SR, BSY));

	/* Check on the lock bit */
	if(GET_BIT(MFPEC->FLASH_CR, LOCK))
	{
		/* if FPEC locked perform a lock sequence */
		MFPEC->FLASH_KEYR = FPEC_KEY1;
		MFPEC->FLASH_KEYR = FPEC_KEY2;
	}

	/* Enable program */
	SET_BIT(MFPEC->FLASH_CR, PG);

	/* Write byte at the desired place */
	 (*(u16 *)Copy_u32Address) = Copy_u16Data;

	/* Wait till the write is done */
	while(GET_BIT(MFPEC->FLASH_SR, BSY));

	/* Disable PG */
	CLR_BIT(MFPEC->FLASH_CR, PG);
}

void MFPEC_voidWriteArea(u32 Copy_u32Address, u16 *Copy_u16Data, u16 Copy_u16Length)
{
	/* Wait if read or write operation is under execution */
	while(GET_BIT(MFPEC->FLASH_SR, BSY));

	/* Check on the lock bit */
	if(GET_BIT(MFPEC->FLASH_CR, LOCK))
	{
		/* if FPEC locked perform a lock sequence */
		MFPEC->FLASH_KEYR = FPEC_KEY1;
		MFPEC->FLASH_KEYR = FPEC_KEY2;
	}

	for (u8 i = 0 ;i <Copy_u16Length ;i++)
	{
		/* Enable program */
		SET_BIT(MFPEC->FLASH_CR, PG);

		/* Write byte at the desired place */
		(*(u16 *)Copy_u32Address) = Copy_u16Data[i];

		/* Shift to the next address */
		Copy_u32Address += 2;

		/* Wait till the write is done */
		while(GET_BIT(MFPEC->FLASH_SR, BSY));
	}

	/* Disable PG */
	CLR_BIT(MFPEC->FLASH_CR, PG);
}

void MFPEC_voidErasePage(u8 Copy_u8PageNumber)
{
	/* Check on the lock bit */
	if(GET_BIT(MFPEC->FLASH_CR, LOCK))
	{
		/* if FPEC locked perform a lock sequence */
		MFPEC->FLASH_KEYR = FPEC_KEY1;
		MFPEC->FLASH_KEYR = FPEC_KEY2;
	}

	/* Enable erase for page */
	SET_BIT(MFPEC->FLASH_CR, PER);

	/* Set Address for page */
	MFPEC->FLASH_AR = MFPEC_FLASH_START_ADDRESS + (u32)(Copy_u8PageNumber * 1024);

	/* Start erase */
	SET_BIT(MFPEC->FLASH_CR, STRT);

	/* Wait till the erase is done */
	while(GET_BIT(MFPEC->FLASH_SR, BSY));

	/* Disable erase for page */
	CLR_BIT(MFPEC->FLASH_CR, PER);
}

void MFPEC_voidMassErase(void)
{
	/* Check on the lock bit */
	if(GET_BIT(MFPEC->FLASH_CR, LOCK))
	{
		/* if FPEC locked perform a lock sequence */
		MFPEC->FLASH_KEYR = FPEC_KEY1;
		MFPEC->FLASH_KEYR = FPEC_KEY2;
	}

	/* Enable erase for page */
	SET_BIT(MFPEC->FLASH_CR, MER);

	/* Start erase */
	SET_BIT(MFPEC->FLASH_CR, STRT);

	/* Wait till the erase is done */
	while(GET_BIT(MFPEC->FLASH_SR, BSY));
}
