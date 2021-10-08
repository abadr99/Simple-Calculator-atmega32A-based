/** @file Math.h
*
* @brief This file is for all math operations.
* @layer Service
* @author Abdelrhman Badr
* @last update 27-sep-21
*/


#ifndef _MATH_H_
#define _MATH_H_

#define SET_BIT(Register,Bit)		((Register) |= (1<<Bit))
#define CLEAR_BIT(Register,Bit)		((Register) &= (~(1<<Bit)))
#define GET_BIT(Register,Bit)		(((Register) & (1<<(Bit)))>>(Bit))
#define TOGGLE_BIT(Register,Bit)	((Register) ^= (1<<(Bit)))

#endif /*end of _MATH_H_*/
