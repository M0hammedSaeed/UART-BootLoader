/**************************************************************************************
 *  [File Name]	 : main.c
 *  [Author]	 : Mohamed Saeed
 **************************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "UART_interface.h"
#include "FPEC_interface.h"


/* Constants */
#define APP_START_PAGE      4
#define END_MC_PAGE         64

/* Global Variables */
u8 Global_u8ReceiveFlag;
u8 Global_u8ReceiveBuffer[50];
u8 Global_u8ReceiveCounter;
u8 Global_u8FirstRecordFlag = 1;

typedef void (*Function_t)(void);
Function_t addr_to_call = NULL_PTR;

/* ProtoTypes */
void BL_voidEraseAppArea(void);
void voidJumpToApp(void);
void Parser_voidParseRecord(u8 *Copy_u8BufData);

int main(void)
{
	MUART_Config_t uart1_config = {MUART_1, MUART_BaudRate_9600, MUART_Data8Bits, MUART_NoParity,
								   MUART_1StopBits, MUART_ParityCheckDisabled};

	/* Initialize Clock System to HSI 8MHz */
	MRCC_voidInitSysClock();

	/* Enable the clock for Peripherals */
	MRCC_voidEnableClock(MRCC_APB2, USART1_PERIPHERAL);	/* USART1 */
	MRCC_voidEnableClock(MRCC_APB2, GPIOA_PERIPHERAL);	/* Port A */
	MRCC_voidEnableClock(MRCC_AHB, FLITF_PERIPHERAL);	/* FPEC   */

	/* Initialize pins for UART module */
	MGPIO_voidSetPinMode(MGPIO_PORTA, MGPIO_PIN9, MGPIO_OUTPUT_AFPP_2MHZ);	/* TX AFPP */
	MGPIO_voidSetPinMode(MGPIO_PORTA, MGPIO_PIN10, MGPIO_INPUT_FLOATING);	/* RX Input Floating */

	MUART_voidInit(&uart1_config);	/* Initialize the UART */
	MSTK_voidInit();	/* Initialize the SysTick */

	MSTK_voidSetSingleInterval(15000000, voidJumpToApp);

	while(1)
	{
		Global_u8ReceiveFlag = MUART_voidReceiveByteConditional(MUART_1, (&Global_u8ReceiveBuffer[Global_u8ReceiveCounter]));

		if(Global_u8ReceiveFlag)
		{
			/* Stop timer till processing the data */
			MSTK_voidStopInterval();

			/* '\n' indicate the end of the record */
			if(Global_u8ReceiveBuffer[Global_u8ReceiveCounter] == '\n')
			{
				/* With the coming of the first record will erase the Application section */
				if(Global_u8FirstRecordFlag)
				{
					BL_voidEraseAppArea();
					Global_u8FirstRecordFlag = 0;
				}
				else{}

				/* Parse Record */
				Parser_voidParseRecord(Global_u8ReceiveBuffer);
				/* Inform the burning Application the record has come to send the next */
				MUART_voidSendArrSynch("ok", 2, MUART_1);
				/* Initialize the index for the new record */
				Global_u8ReceiveCounter = 0;
			}
			else
			{
				Global_u8ReceiveCounter++;
			}

			MSTK_voidSetSingleInterval(15000000, voidJumpToApp);
		}
		else{}
	}
	return 0;
}

/* To Erase the Application section before burning the new Application */
void BL_voidEraseAppArea(void)
{
	for (u8 i = APP_START_PAGE ;i < END_MC_PAGE ;i++)
	{
		MFPEC_voidErasePage(i);
	}
}

/* This function will be called when timeout happens to jump to the APP section */
void voidJumpToApp(void)
{
	#define SCB_VTOR   *((volatile u32*)0xE000ED08) /* Vector table offset register */

	/* Relocate the vector table */
	SCB_VTOR = 0x08001000;

	/* Jump to application */
	addr_to_call = *(Function_t*)(0x08001004);
	addr_to_call();
}
