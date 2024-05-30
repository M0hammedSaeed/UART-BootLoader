/*******************************************************************************
 *
 *  [File Name]  : BIT_MATH.h
 *
 *  [version]	 : V01
 *
 *  [Author]	 : Mohamed Saeed
 *
 *******************************************************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/* [Description]: Write one at specific bit in register */
#define SET_BIT(REG,BIT)		(REG |= (1<<BIT))

/* [Description]: Write zero at specific bit in register */
#define CLR_BIT(REG,BIT)		(REG &= ~(1<<BIT))

/* [Description]: Change the value at specific bit in register */
#define TOG_BIT(REG,BIT)		(REG ^= (1<<BIT))

/* [Description]: Get the value at specific bit in register */
#define GET_BIT(REG,BIT)        ((REG >> BIT) & 0X01)

/* [Description]: Check if a specific bit is one or zero
 * [Return]     : One (True) if the already bit is set(1)
 * 				  Zero (False) if the bit is clear(0)
 */
#define BIT_IS_SET(REG,BIT)		(REG & (1<<BIT))

/* [Description]: Check if a specific bit is one or zero
 * [Return]     : One (True) if the already bit is clear(0)
 * 				  Zero (False) if the bit is set(1)
 */
#define BIT_IS_CLEAR(REG,BIT)	(!(REG & (1<<BIT)))

/* [Description]: Rotate Right the register value with specific number is rotate
 * [Example]    : Rotate Right bit number 2
 *
 *			Register 	    ==>	|0|0|1|0|0|1|1|0|
 *			After Rotate	==> |1|0|0|0|1|0|0|1|
 */
#define ROR(REG,NUM)			(REG = (REG>>NUM) | (REG<<(8-NUM))

/* [Description]: Rotate Left the register value with specific number is rotate
 * [Example]    : Rotate Left bit number 2
 *
 *			Register 	    ==>	|0|0|1|0|0|1|1|0|
 *			After Rotate	==> |1|0|0|1|1|0|0|0|
 */
#define ROL(REG,NUM)			(REG = (REG<<NUM) | (REG>>(8-NUM))

#endif /* BIT_MATH_H_ */
