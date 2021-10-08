/*
 * KeyPad_Congif.h
 *
 *  Created on: Sep 29, 2021
 *      Author: Abdelrhman
 */

#ifndef KEYPAD_CONGIF_H_
#define KEYPAD_CONGIF_H_

/*Define KeyPad type*/
#define KEYPAD_TYPE		(KeyPad_4x4)



#if KEYPAD_TYPE == KeyPad_4x4

/*Define keypad characters*/
#define KEYPAD_CHARACTERS	{{'7','8','9','/'},\
							 {'4','5','6','*'},\
							 {'1','2','3','-'},\
							 {'O','0','=','+'}}

/*Define keypad connected pins*/
#define KEYPAD_PORT		(PORTA)

#define KEYPAD_COL0		(PIN0)
#define KEYPAD_COL1		(PIN1)
#define KEYPAD_COL2		(PIN2)
#define KEYPAD_COL3		(PIN3)

#define KEYPAD_ROW0		(PIN4)
#define KEYPAD_ROW1		(PIN5)
#define KEYPAD_ROW2		(PIN6)
#define KEYPAD_ROW3		(PIN7)



#elif KEYPDA_TYPE == KeyPad_4x3

#endif /*KEYPDA_TYPE*/

#endif /* KEYPAD_CONGIF_H_ */
