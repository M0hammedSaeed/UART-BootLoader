/**************************************************************************************
 *  [File Name]	 : FPEC_interface.h
 *	[Version]	 : V01
 *  [Author]	 : Mohamed Saeed
 **************************************************************************************/

#ifndef FPEC_INTERFACE_H_
#define FPEC_INTERFACE_H_

/*
 * MFPEC_voidWriteHalfWord --> write half word at specific location
 * I/P: (u32) the address, (u16) data
 */
void MFPEC_voidWriteHalfWord(u32 Copy_u32Address, u16 Copy_u16Data);

/*
 * MFPEC_voidWriteArea --> write half word at specific area
 * I/P: (u32) the address, (u16) pointer to data, (u16) Length of data
 */
void MFPEC_voidWriteArea(u32 Copy_u32Address, u16 *Copy_u16Data, u16 Copy_u16Length);

/*
 * MFPEC_voidErasePage --> Erase a page
 * I/P: (u8) page number
 */
void MFPEC_voidErasePage(u8 Copy_u8PageNumber);

/* MFPEC_voidMassErase --> Erase a the whole user pages */
void MFPEC_voidMassErase(void);

#endif /* FPEC_INTERFACE_H_ */
