/*
 * KeyPad.h
 *
 *  Created on: Sep 29, 2021
 *      Author: Abdelrhman
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*Define keypad value when not pressed*/
#define KEYPAD_NOT_PRESSED	(0xFF)

/*
*@ breif : This function used to setup microcontroller to deal with keypad
*@ Para  : void
*@ Return: void
*/
void KeyPad_Setup(void);
/*
*@ breif : This function used to get the pressed key
*@ Para  : address of the variable that will indicate for pressed key
			<<<< This variable must be initialized wih  KEYPAD_NOT_PRESSED >>>>
*@ Return: void
*/
void KeyPad_GetValue(uint8_t *ReturnedValue);

#endif /* KEYPAD_H_ */
