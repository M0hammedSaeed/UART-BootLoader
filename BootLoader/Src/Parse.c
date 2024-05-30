/**************************************************************************************
 *  [File Name]	 : Parse.c
 *  [Author]	 : Mohamed Saeed
 **************************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "FPEC_interface.h"

u32 Global_u32Address = 0x08000000 ;

u8 AsciToHex(u8 Copy_u8Asci)
{
	u8 Local_u8Result;

	if((Copy_u8Asci >= 48) && (Copy_u8Asci <= 57))	/* From 0 to 9 */
	{
		Local_u8Result = Copy_u8Asci - 48;
	}
	else if((Copy_u8Asci >= 65) && (Copy_u8Asci <= 70))	/* From A to F */
	{
		Local_u8Result = Copy_u8Asci - 55;
	}
	else{}

	return Local_u8Result;
}

void ParseData(u8* Copy_u8BufData)
{
	/* Get character count */
	u8 Local_u8HighDigit = AsciToHex(Copy_u8BufData[1]);
	u8 Local_u8LowDigit  = AsciToHex(Copy_u8BufData[2]);
	u8 Local_u8CharCount = Local_u8LowDigit | (Local_u8HighDigit <<4);

	/* Get Address */
	u32 Local_u32Address = 0;
	u8 Digit0 = AsciToHex(Copy_u8BufData[6]);
	u8 Digit1 = AsciToHex(Copy_u8BufData[5]);
	u8 Digit2 = AsciToHex(Copy_u8BufData[4]);
	u8 Digit3 = AsciToHex(Copy_u8BufData[3]);
	Local_u32Address = Digit0 | (Digit1 << 4) | (Digit2 << 8) | (Digit3 << 12);
	Local_u32Address = Local_u32Address | Global_u32Address ;

	/* Get Data */
	u16 Local_u16DataBuffer[20];
	for (u8 i = 0; i < (Local_u8CharCount/2); i++)
	{
		Digit0 = AsciToHex(Copy_u8BufData[9+ i*4]);
		Digit1 = AsciToHex(Copy_u8BufData[10+ i*4]);
		Digit2 = AsciToHex(Copy_u8BufData[11+ i*4]);
		Digit3 = AsciToHex(Copy_u8BufData[12+ i*4]);
		Local_u16DataBuffer[i] = Digit1 | (Digit0 << 4) | (Digit2 << 12) | (Digit3 << 8);
	}

	/* Write data to flash */
	MFPEC_voidWriteArea(Local_u32Address, Local_u16DataBuffer, (Local_u8CharCount/2));
}

void ParseUpperAddress(u8 *Copy_u8BufData)
{
	/* Get Address */
	u32 Local_u32Address;
	u8 Digit0 = AsciToHex(Copy_u8BufData[12]);
	u8 Digit1 = AsciToHex(Copy_u8BufData[11]);
	u8 Digit2 = AsciToHex(Copy_u8BufData[10]);
	u8 Digit3 = AsciToHex(Copy_u8BufData[9]);
	Local_u32Address = Digit0 | (Digit1 << 4) | (Digit2 << 8) | (Digit3 << 12);
	Global_u32Address = (Local_u32Address << 16);
}

void Parser_voidParseRecord(u8 *Copy_u8BufData)
{
	switch(Copy_u8BufData[8])
	{
	case '0': ParseData(Copy_u8BufData); break;
	case '4': ParseUpperAddress(Copy_u8BufData); break;
	}
}
