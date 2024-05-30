/**************************************************************************************
 *  [File Name]	 : UART_program.c
 *	[Version]	 : V01
 *  [Author]	 : Mohamed Saeed
 **************************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"


/* Array of Addresses which has type of Struct to addresses MUART_t*/
static volatile MUART_t* const MUART[3] = { MUART1 , MUART2 , MUART3 };


void MUART_voidInit(MUART_Config_t *Copy_ConfigPtr)
{
	u8 Local_u8UARTNum = Copy_ConfigPtr->UART_Number;

	/* Calculating the value of BRR corresponding to the BaudRate */
	u32 Local_u32Mantissa = CLOCK_FREQ / (16 * (Copy_ConfigPtr -> UART_BaudRate));
	u32 Local_u32Fraction = (( (CLOCK_FREQ * 100) / (16 * (Copy_ConfigPtr->UART_BaudRate) )) % 100) * 16;

	if(Local_u32Fraction > 1500)
	{
		Local_u32Mantissa += 1;
		Local_u32Fraction = 0;
	}
	MUART[Local_u8UARTNum]->BRR	= (Local_u32Mantissa << 4) | (Local_u32Fraction / 100);


	/* Enabling the TX and RX */
	SET_BIT(MUART[Local_u8UARTNum]->CR1, MUART_TE);
	SET_BIT(MUART[Local_u8UARTNum]->CR1, MUART_RE);

	/* Parity Check Enable */
	if(Copy_ConfigPtr->UART_ParityCheck == MUART_ParityCheckEnabled)
	{
		SET_BIT(MUART[Local_u8UARTNum]->CR1, MUART_PCE);
	}
	else
	{
		CLR_BIT(MUART[Local_u8UARTNum]->CR1, MUART_PCE);
	}
	/* Even or Odd Parity */
	if(Copy_ConfigPtr->UART_Parity == MUART_EvenParity )
	{
		CLR_BIT(MUART[Local_u8UARTNum]->CR1, MUART_PS);
	}
	else if(Copy_ConfigPtr->UART_Parity == MUART_OddParity)
	{
		SET_BIT(MUART[Local_u8UARTNum]->CR1, MUART_PS);
	}
	else
	{
		CLR_BIT(MUART[Local_u8UARTNum]->CR1, MUART_PS);
	}

	/* Data length */
	if(Copy_ConfigPtr->UART_DataLength == MUART_Data8Bits)
	{
		CLR_BIT(MUART[Local_u8UARTNum]->CR1, MUART_M);
	}
	else if(Copy_ConfigPtr->UART_DataLength == MUART_Data9Bits)
	{
		SET_BIT(MUART[Local_u8UARTNum]->CR1, MUART_M);
	}


	/*Number of Stop bits*/
	if(Copy_ConfigPtr->UART_StopBits == MUART_1StopBits)
	{
		CLR_BIT(MUART[Local_u8UARTNum]->CR2, MUART_STOP1);
		CLR_BIT(MUART[Local_u8UARTNum]->CR2, MUART_STOP0);
	}
	else if(Copy_ConfigPtr->UART_StopBits == MUART_2StopBits)
	{
		SET_BIT(MUART[Local_u8UARTNum]->CR2, MUART_STOP1);
		CLR_BIT(MUART[Local_u8UARTNum]->CR2, MUART_STOP0);
	}

	/* Enable the UART */
	SET_BIT(MUART[Local_u8UARTNum]->CR1, MUART_UE);
	/* Clear the status register */
	MUART[Local_u8UARTNum]->SR = 0x00;
}


void MUART_voidTransmitByteSynch(u8	Local_u8Byte, MUART_Num_t Copy_UARTNumber)
{
	/* Send the Byte to the Data Register */
	MUART[Copy_UARTNumber]->DR = Local_u8Byte;

	/* Wait until the transmission complete */
	while(GET_BIT(MUART[Copy_UARTNumber]->SR, MUART_TC) == 0);

	/* Clear the transmission Complete flag */
	CLR_BIT(MUART[Copy_UARTNumber]->SR, MUART_TC);

}

u8 MUART_voidReceiveByteSynch(MUART_Num_t Copy_UARTNumber)
{
	u8 Local_u8Byte;

	/* Wait until the Receive not empty flag is raised */
	while(GET_BIT(MUART[Copy_UARTNumber]->SR, MUART_RXNE) == 0);

	/* Get the received data */
	Local_u8Byte = MUART[Copy_UARTNumber]->DR;

	/* Clear the Receive not empty flag */
	CLR_BIT(MUART[Copy_UARTNumber]->SR, MUART_RXNE);

	return Local_u8Byte;
}

u8 MUART_voidReceiveByteConditional(MUART_Num_t Copy_UARTNumber, u8 *Copy_u8Data)
{
	u8 Local_u8Error = 1;

	/* Check the Receive not empty flag is raised */
	if(GET_BIT(MUART[Copy_UARTNumber]->SR, MUART_RXNE) == 1)
	{
		/* Get the received data */
		*Copy_u8Data = MUART[Copy_UARTNumber]->DR;
	}
	else
	{
		Local_u8Error = 0;
	}

	/* Clear the Receive not empty flag */
	CLR_BIT(MUART[Copy_UARTNumber]->SR, MUART_RXNE);

	return Local_u8Error;
}

void MUART_voidSendArrSynch(u8 *Copy_u8PtrTXArr, u8 Copy_u8ArrSize, MUART_Num_t Copy_UARTNumber)
{
	u16 Local_u16Iterator = 0;

	while(Local_u16Iterator < Copy_u8ArrSize)
	{
		MUART_voidTransmitByteSynch(Copy_u8PtrTXArr[Local_u16Iterator], Copy_UARTNumber);
		Local_u16Iterator++;
	}
}

void MUART_voidReceiveArrSynch(u8 *Copy_u8PtrRXArr, u8 Copy_u8ArrSize, MUART_Num_t Copy_UARTNumber)
{
	u16 Local_u16Iterator = 0;

	while(Local_u16Iterator < Copy_u8ArrSize)
	{
		Copy_u8PtrRXArr[Local_u16Iterator] = MUART_voidReceiveByteSynch(Copy_UARTNumber);
		Local_u16Iterator++;
	}

	Copy_u8PtrRXArr[Local_u16Iterator] = '\0';
}

void MUART_voidSendNumber(s32 Copy_s32Number, MUART_Num_t Copy_UARTNumber)
{
	u8 Local_u8Counter = 0, Local_u8SentNumber;
	u32 Local_u32divisible = 1;

	if(Copy_s32Number < 0)
	{
		MUART_voidTransmitByteSynch('-', Copy_UARTNumber);
		Copy_s32Number  *= -1;
	}

	u32 Local_u32temp = Copy_s32Number;

	if(Copy_s32Number == 0)
	{
		MUART_voidTransmitByteSynch('0', Copy_UARTNumber);
	}
	else
	{
		/* getting the number of the digits */
		while(Local_u32temp != 0)
		{
			Local_u8Counter++;
			Local_u32temp = Local_u32temp / 10;

		}

		/* getting the divisible to get each number separately */
		while(Local_u8Counter > 1)
		{
			Local_u8Counter--;
			Local_u32divisible *= 10;
		}

		/* getting each number and send it to the UART */
		while(Local_u32divisible != 0)
		{
			Local_u8SentNumber = Copy_s32Number / Local_u32divisible;
			MUART_voidTransmitByteSynch(Local_u8SentNumber + '0', Copy_UARTNumber);
			Copy_s32Number -= (Local_u8SentNumber * Local_u32divisible);
			Local_u32divisible = Local_u32divisible / 10;
		}
	}
}
