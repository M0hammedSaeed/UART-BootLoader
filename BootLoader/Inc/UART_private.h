/**************************************************************************************
 *  [File Name]	 : UART_private.h
 *	[Version]	 : V01
 *  [Author]	 : Mohamed Saeed
 **************************************************************************************/

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_


#define MUART1_BASE_ADDRESS		0x40013800
#define MUART2_BASE_ADDRESS    	0x40004400
#define MUART3_BASE_ADDRESS		0x40004800

typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}MUART_t;

#define MUART1 	((volatile MUART_t *)(MUART1_BASE_ADDRESS))
#define MUART2 	((volatile MUART_t *)(MUART2_BASE_ADDRESS))
#define MUART3 	((volatile MUART_t *)(MUART3_BASE_ADDRESS))

/* SR */
#define  MUART_TXE 		7
#define  MUART_TC 		6
#define  MUART_RXNE 	5
#define  MUART_IDLE 	4
#define  MUART_ORE 		3
#define  MUART_NE 		2
#define  MUART_FE 		1
#define  MUART_PE 		0
/* CR1 */
#define MUART_UE		13
#define MUART_M			12
#define MUART_WAKE		11
#define MUART_PCE		10
#define MUART_PS		9
#define MUART_PEIE		8
#define MUART_TXEIE		7
#define MUART_TCIE		6
#define MUART_RXNEIE	5
#define MUART_IDLEIE	4
#define MUART_TE		3
#define MUART_RE		2
#define MUART_RWU		1
#define MUART_SBK		0
/* CR2 */
#define MUART_STOP1		13
#define MUART_STOP0		12
#define MUART_CLKEN		11
#define MUART_CPOL		10
#define MUART_CPHA		9

#endif /* UART_PRIVATE_H_ */
