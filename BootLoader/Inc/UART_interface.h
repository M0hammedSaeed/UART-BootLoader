/**************************************************************************************
 *  [File Name]	 : UART_interface.h
 *	[Version]	 : V01
 *  [Author]	 : Mohamed Saeed
 **************************************************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

typedef enum
{
	MUART_1,
	MUART_2,
	MUART_3
}MUART_Num_t;

typedef enum
{
	MUART_BaudRate_2400 	= 2400,
	MUART_BaudRate_9600 	= 9600,
	MUART_BaudRate_19200 	= 19200,
	MUART_BaudRate_57600 	= 57600,
	MUART_BaudRate_115200 	= 115200,
	MUART_BaudRate_230400 	= 230400,
	MUART_BaudRate_460800 	= 460800,
	MUART_BaudRate_921600 	= 921600,
	MUART_BaudRate_2250000 	= 2250000,
	MUART_BaudRate_4500000 	= 4500000
}MUART_BaudRate_t;

typedef enum
{
	MUART_NoParity   = 0,
	MUART_EvenParity = 0,
	MUART_OddParity
}MUART_Parity_t;

typedef enum
{
	MUART_Data8Bits,
	MUART_Data9Bits
}MUART_DataLength_t;

typedef enum
{
	MUART_1StopBits,
	MUART_2StopBits
}MUART_StopBits_t;

typedef enum
{
	MUART_ParityCheckEnabled,
	MUART_ParityCheckDisabled
}MUART_ParityCheck_t;

typedef struct
{
	MUART_Num_t 	 	UART_Number;
	MUART_BaudRate_t 	UART_BaudRate;
	MUART_DataLength_t	UART_DataLength;
	MUART_Parity_t	    UART_Parity;
	MUART_StopBits_t	UART_StopBits;
	MUART_ParityCheck_t UART_ParityCheck;
}MUART_Config_t;


void MUART_voidInit(MUART_Config_t *Copy_ConfigPtr);

void MUART_voidTransmitByteSynch(u8	Local_u8Byte, MUART_Num_t Copy_UARTNumber);
u8 MUART_voidReceiveByteSynch(MUART_Num_t Copy_UARTNumber);
u8 MUART_voidReceiveByteConditional(MUART_Num_t Copy_UARTNumber, u8 *Copy_u8Data);

void MUART_voidSendArrSynch(u8 *Copy_u8PtrTXArr, u8 Copy_u8ArrSize, MUART_Num_t Copy_UARTNumber);
void MUART_voidReceiveArrSynch(u8 *Copy_u8PtrRXArr, u8 Copy_u8ArrSize, MUART_Num_t Copy_UARTNumber);

void MUART_voidSendNumber(s32 Copy_s32Number, MUART_Num_t Copy_UARTNumber);

#endif /* UART_INTERFACE_H_ */
