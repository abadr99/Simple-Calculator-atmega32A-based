/*
 * KeyPad.c
 *
 *  Created on: Sep 29, 2021
 *      Author: Abdelrhman Badr
 */

#include "Std_DataType.h"
#include "Math.h"
#include "Atmega32A.h"
#include "Error.h"
#include "DIO.h"
#include "KeyPad_Congif.h"
#include "KeyPad.h"
#include "util/delay.h"

void KeyPad_Setup(void)
{
	#if KEYPAD_TYPE == KeyPad_4x4
		/*Error handling*/
		#if KEYPAD_PORT > PORTD
			#error "KEYPAD_PORT in KeyPad_Config.h is not defined correctly"
		#elif (KEYPAD_COL0 > PIN7) || (KEYPAD_COL1 > PIN7) || (KEYPAD_COL2 > PIN7) || (KEYPAD_COL3 > PIN7)|| (KEYPAD_ROW0 > PIN7) || (KEYPAD_ROW1 > PIN7) || (KEYPAD_ROW2 > PIN7) || (KEYPAD_ROW3> PIN7)
			#error "One of keypad pin in KeyPad_Config.h is not defined correctly"
		#endif /*Error handling*/

		/*Set keypad rows as input*/
		DIO_SetPinDirection(KEYPAD_PORT,KEYPAD_ROW0,DIO_INPUT_PULLUP_PIN);
		DIO_SetPinDirection(KEYPAD_PORT,KEYPAD_ROW1,DIO_INPUT_PULLUP_PIN);
		DIO_SetPinDirection(KEYPAD_PORT,KEYPAD_ROW2,DIO_INPUT_PULLUP_PIN);
		DIO_SetPinDirection(KEYPAD_PORT,KEYPAD_ROW3,DIO_INPUT_PULLUP_PIN);
		/*Set keypad col as output*/
		DIO_SetPinDirection(KEYPAD_PORT,KEYPAD_COL0,DIO_OUTPUT_PIN);
		DIO_SetPinDirection(KEYPAD_PORT,KEYPAD_COL1,DIO_OUTPUT_PIN);
		DIO_SetPinDirection(KEYPAD_PORT,KEYPAD_COL2,DIO_OUTPUT_PIN);
		DIO_SetPinDirection(KEYPAD_PORT,KEYPAD_COL3,DIO_OUTPUT_PIN);
		/*Set keypad rows as high initial state*/
		DIO_WritePin(KEYPAD_PORT,KEYPAD_COL0,DIO_HIGH_PIN);
		DIO_WritePin(KEYPAD_PORT,KEYPAD_COL1,DIO_HIGH_PIN);
		DIO_WritePin(KEYPAD_PORT,KEYPAD_COL2,DIO_HIGH_PIN);
		DIO_WritePin(KEYPAD_PORT,KEYPAD_COL3,DIO_HIGH_PIN);
	#endif /*KEYPAD_TYPE*/
}
void KeyPad_GetValue(uint8_t *ReturnedValue)
{
	*ReturnedValue = KEYPAD_NOT_PRESSED;
	#if KEYPAD_TYPE == KeyPad_4x4
		uint8_t KeyPad_Arr[4][4] = KEYPAD_CHARACTERS;
		const uint8_t Col_Arr[4] = {KEYPAD_COL0,KEYPAD_COL1,KEYPAD_COL2,KEYPAD_COL3};
		const uint8_t Row_Arr[4] = {KEYPAD_ROW0,KEYPAD_ROW1,KEYPAD_ROW2,KEYPAD_ROW3};
		uint8_t ColIterator = 0;
		uint8_t RowIterator = 0;
		uint8_t RowVal = DIO_HIGH_PIN;
		for(ColIterator = 0 ; ColIterator < 4 ; ColIterator++)
		{
			/*Drive a high signal for required col*/
			DIO_WritePin(KEYPAD_PORT,Col_Arr[ColIterator],DIO_LOW_PIN);
			/*Check if the high signal dirved to row*/
			for(RowIterator = 0 ; RowIterator < 4 ; RowIterator++)
			{
				DIO_ReadPin(KEYPAD_PORT,Row_Arr[RowIterator],&RowVal);
				if(RowVal == DIO_LOW_PIN)
				{
					*ReturnedValue = KeyPad_Arr[RowIterator][ColIterator];
					DIO_ReadPin(KEYPAD_PORT,Row_Arr[RowIterator],&RowVal);
					break;
				}
			}
			DIO_WritePin(KEYPAD_PORT,Col_Arr[ColIterator],DIO_HIGH_PIN);
		}
	#endif /*KEYPAD_TYPE*/
}




