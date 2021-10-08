/*
 * CLCD.c
 *
 *  Created on: Oct 2, 2021
 *      Author: Abdelrhman
 */
#include "Std_DataType.h"
#include "Math.h"
#include "Atmega32A.h"
#include "Error.h"
#include "DIO.h"
#include "CLCD_Private.h"
#include "CLCD_Config.h"
#include "CLCD.h"
#include "util/delay.h"

static void CLCD_SendEnablePulse(void)
{
	DIO_WritePin(CLCD_EN_PORT,CLCD_EN_PIN,DIO_LOW_PIN);
	_delay_us(1);
	DIO_WritePin(CLCD_EN_PORT,CLCD_EN_PIN,DIO_HIGH_PIN);
	_delay_us(1);
	DIO_WritePin(CLCD_EN_PORT,CLCD_EN_PIN,DIO_LOW_PIN);
}

static void CLCD_SendLSB(uint8_t DataModeConnection , uint8_t Data)
{
	switch(DataModeConnection)
	{
		case UPPER_DATA_CONNECTION:
							DIO_WritePin(CLCD_PORT,PIN7,GET_BIT(Data,3));
							DIO_WritePin(CLCD_PORT,PIN6,GET_BIT(Data,2));
							DIO_WritePin(CLCD_PORT,PIN5,GET_BIT(Data,1));
							DIO_WritePin(CLCD_PORT,PIN4,GET_BIT(Data,0));
							break;
		case LOWER_DATA_CONNECTION:
							DIO_WritePin(CLCD_PORT,PIN3,GET_BIT(Data,3));
							DIO_WritePin(CLCD_PORT,PIN2,GET_BIT(Data,2));
							DIO_WritePin(CLCD_PORT,PIN1,GET_BIT(Data,1));
							DIO_WritePin(CLCD_PORT,PIN0,GET_BIT(Data,0));
							break;
		default: break;
	}
}

static void CLCD_SendMSB(uint8_t DataModeConnection, uint8_t Data)
{
	switch(DataModeConnection)
	{
		case UPPER_DATA_CONNECTION:
							DIO_WritePin(CLCD_PORT,PIN7,GET_BIT(Data,7));
							DIO_WritePin(CLCD_PORT,PIN6,GET_BIT(Data,6));
							DIO_WritePin(CLCD_PORT,PIN5,GET_BIT(Data,5));
							DIO_WritePin(CLCD_PORT,PIN4,GET_BIT(Data,4));
							break;
		case LOWER_DATA_CONNECTION:
							DIO_WritePin(CLCD_PORT,PIN3,GET_BIT(Data,7));
							DIO_WritePin(CLCD_PORT,PIN2,GET_BIT(Data,6));
							DIO_WritePin(CLCD_PORT,PIN1,GET_BIT(Data,5));
							DIO_WritePin(CLCD_PORT,PIN0,GET_BIT(Data,4));
							break;
		default: break;
	}
}

static void InitiateLCDControlPins(void)
{
	DIO_SetPinDirection(CLCD_RS_PORT,CLCD_RS_PIN,DIO_OUTPUT_PIN);
	DIO_SetPinDirection(CLCD_RW_PORT,CLCD_RW_PIN,DIO_OUTPUT_PIN);
	DIO_SetPinDirection(CLCD_EN_PORT,CLCD_EN_PIN,DIO_OUTPUT_PIN);
}

static void InitiateLCDDataPins(void)
{
	#if (CLCD_DATA_MODE == CLCD_8BitMode)
		DIO_SetPortDirection(CLCD_PORT,DIO_OUTPUT_PORT);
	#elif (CLCD_DATA_MODE == CLCD_4BitMode_Upper)
		DIO_SetPinDirection(CLCD_PORT,PIN7,DIO_OUTPUT_PIN);
		DIO_SetPinDirection(CLCD_PORT,PIN6,DIO_OUTPUT_PIN);
		DIO_SetPinDirection(CLCD_PORT,PIN5,DIO_OUTPUT_PIN);
		DIO_SetPinDirection(CLCD_PORT,PIN4,DIO_OUTPUT_PIN);
	#elif (CLCD_DATA_MODE == CLCD_4BitMode_Lower)
		DIO_SetPinDirection(CLCD_PORT,PIN3,DIO_OUTPUT_PIN);
		DIO_SetPinDirection(CLCD_PORT,PIN2,DIO_OUTPUT_PIN);
		DIO_SetPinDirection(CLCD_PORT,PIN1,DIO_OUTPUT_PIN);
		DIO_SetPinDirection(CLCD_PORT,PIN0,DIO_OUTPUT_PIN);
	#endif /*CLCD_DATA_MODE*/
}

static void CLCD_SendInstruction(uint8_t Instruction)
{
	#if  (CLCD_DATA_MODE == CLCD_8BitMode)

		/*set the RS and RW to zero*/
		DIO_WritePin(CLCD_RS_PORT,CLCD_RS_PIN,DIO_LOW_PIN);
		DIO_WritePin(CLCD_RW_PORT,CLCD_RW_PIN,DIO_LOW_PIN);

		/*Send the instruction*/
		/*The only important thing is the data should be available on the databus before generating the High-to-Low pulse on EN pin.*/
		DIO_WritePort(CLCD_PORT,Instruction);
		/*set enable pulse __||||__  */
		CLCD_SendEnablePulse();

	#elif (CLCD_DATA_MODE == CLCD_4BitMode_Upper)
		/*set the RS and RW to zero*/
		DIO_WritePin(CLCD_RS_PORT,CLCD_RS_PIN,DIO_LOW_PIN);
		DIO_WritePin(CLCD_RW_PORT,CLCD_RW_PIN,DIO_LOW_PIN);
		/*Send the instruction*/
		/*Send the 4 MSB*/
		CLCD_SendMSB(UPPER_DATA_CONNECTION , Instruction);

		/*set enable pulse __||||__  */
		CLCD_SendEnablePulse();

		/*Send the 4 LSB*/
		CLCD_SendLSB(UPPER_DATA_CONNECTION , Instruction);

		/*set enable pulse __||||__  */
		CLCD_SendEnablePulse();

	#elif (CLCD_DATA_MODE == CLCD_4BitMode_Lower)

		/*set the RS and RW to zero*/
		DIO_WritePin(CLCD_RS_PORT,CLCD_RS_PIN,DIO_LOW_PIN);
		DIO_WritePin(CLCD_RW_PORT,CLCD_RW_PIN,DIO_LOW_PIN);
		/*Send the instruction*/
		/*Send the 4 MSB*/
		CLCD_SendMSB(LOWER_DATA_CONNECTION , Instruction);

		/*set enable pulse __||||__  */
		CLCD_SendEnablePulse();

		/*Send the 4 LSB*/
		CLCD_SendLSB(LOWER_DATA_CONNECTION , Instruction);
		/*set enable pulse __||||__  */
		CLCD_SendEnablePulse();

	#endif/*CLCD_DATAMODE*/
}
static void CLCD_SendData(uint8_t Data)
{
	#if (CLCD_DATA_MODE == CLCD_8BitMode)

		 /*set the RS to one and RW to zero*/
		 DIO_WritePin(CLCD_RS_PORT,CLCD_RS_PIN,DIO_HIGH_PIN);
		 DIO_WritePin(CLCD_RW_PORT,CLCD_RW_PIN,DIO_LOW_PIN);

		 /*Send the data*/
		 /*The only important thing is the data should be available on the databus before generating the High-to-Low pulse on EN pin.*/
		 DIO_WritePort(CLCD_PORT,Data);
		 /*set enable pulse __||||__  */
		 CLCD_SendEnablePulse();

	#elif (CLCD_DATA_MODE == CLCD_4BitMode_Upper)
		 /*set the RS to one and RW to zero*/
		 DIO_WritePin(CLCD_RS_PORT,CLCD_RS_PIN,DIO_HIGH_PIN);
		 DIO_WritePin(CLCD_RW_PORT,CLCD_RW_PIN,DIO_LOW_PIN);

	    /*Send the data*/

	     /*Send the 4 MSB*/
	     CLCD_SendMSB(UPPER_DATA_CONNECTION,Data);

	     /*set enable pulse __||||__  */
	     CLCD_SendEnablePulse();

	     /*Send the 4 LSB*/
	     CLCD_SendLSB(UPPER_DATA_CONNECTION,Data);

	     /*set enable pulse __||||__  */
	     CLCD_SendEnablePulse();

	#elif (CLCD_DATA_MODE == CLCD_4BitMode_Lower)

		 /*set the RS to one and RW to zero*/
		 DIO_WritePin(CLCD_RS_PORT,CLCD_RS_PIN,DIO_HIGH_PIN);
		 DIO_WritePin(CLCD_RW_PORT,CLCD_RW_PIN,DIO_LOW_PIN);

		/*Send the instruction*/
		/*Send the 4 MSB*/
		CLCD_SendMSB(LOWER_DATA_CONNECTION,Data);

		/*set enable pulse __||||__  */
		CLCD_SendEnablePulse();

		/*Send the 4 LSB*/
		CLCD_SendLSB(LOWER_DATA_CONNECTION,Data);

		/*set enable pulse __||||__  */
		CLCD_SendEnablePulse();
	#endif/*_dataBitMode*/
}
void CLCD_Setup(void)
{
	/*Error handling*/
	#if (CLCD_PORT > PORTD) || (CLCD_RS_PORT > PORTD) || (CLCD_RW_PORT > PORTD) || (CLCD_EN_PORT > PORTD)
		#error "Error CLCD Port"
	#endif /*CLCD_PORT*/

	#if (CLCD_RS_PIN > PIN7) || (CLCD_RW_PIN > PIN7) || (CLCD_EN_PIN > PIN7)
		#error "Error CLCD Pin"
	#endif /*CLCD_PIN*/

	#if (CLCD_DATA_MODE != CLCD_8BitMode)
		#if(CLCD_DATA_MODE != CLCD_4BitMode_Lower)
			#if(CLCD_DATA_MODE != CLCD_4BitMode_Upper)
				#error "Error in CLCD_DATA_MODE"
			#endif
		#endif
	#endif /*CLCD_DATA_MODE*/

	#if (CLCD_NUMBER_OF_LINES != CLCD_2Lines)
		#if(CLCD_NUMBER_OF_LINES != CLCD_1Lines)
			#error "Error in CCLCD_NUMBER_OF_LINES"
		#endif
	#endif /*CLCD_NUMBER_OF_LINES*/

	#if (CLCD_FONT != CLCD_5X8)
		#if(CLCD_FONT != CLCD_5X10)
			#error "Error in CLCD_FONT"
		#endif
	#endif /*CLCD_NUMBER_OF_LINES*/

	#if (CLCD_INCREMENT_DECREMENT != CLCD_Increment)
		#if(CLCD_INCREMENT_DECREMENT != CLCD_Decrement)
			#error "Error in CLCD_INCREMENT_DECREMENT"
		#endif
	#endif /*CLCD_NUMBER_OF_LINES*/

	/*Set directions of pins*/
	InitiateLCDControlPins();

	#if (CLCD_DATA_MODE == CLCD_8BitMode)

		InitiateLCDDataPins();

		/*Wait for more than 30mS after VDD rises to 4.5Volt*/
		_delay_ms(40);

		/*send function set and wait for excution time*/
		CLCD_SendInstruction(CLCD_FUNCTION_SET | (CLCD_DATA_MODE << 4) | (CLCD_NUMBER_OF_LINES <<3) | (CLCD_FONT << 2));
		_delay_us(50);

		/*send display on/off instruction*/
		/*With initial states blink and cursor are off ,, display are on*/
		CLCD_SendInstruction(CLCD_DISPLAY_CONTROL | (CLCD_BlinkOff) | (CLCD_CursorOff << 1) |(CLCD_DisplayOn << 2));
		_delay_us(50);

		/*send clear display instruction*/
		CLCD_SendInstruction(CLCD_CLEAR_DISPLAY);
		_delay_ms(3);

		/*send entry mode set function*/
		/*CLCD_SendInstruction(CLCD_ENTRY_MODE_SET);*/

	#elif (CLCD_DATA_MODE == CLCD_4BitMode_Upper)
		InitiateLCDDataPins();
	#elif (CLCD_DATA_MODE == CLCD_4BitMode_Lower)
		InitiateLCDDataPins();
	#endif /*CLCD_DATA_MODE*/

	#if (CLCD_DATA_MODE == CLCD_4BitMode_Lower )|| (CLCD_DATA_MODE == CLCD_4BitMode_Upper)

		/*Wait for more than 30mS after VDD rises to 4.5Volt*/
		_delay_ms(40);
		/*send function set and wait for excution time*/
		/*Sets to 4-bit operation.In this case, operation is handled as 8 bits by initialization,and only this instruction
		  completes with one write.*/
		CLCD_SendInstruction(0x02);
		_delay_us(50);
		CLCD_SendInstruction(CLCD_FUNCTION_SET | (CLCD_4BITMODE << 4) | (CLCD_NUMBER_OF_LINES <<3) | (CLCD_FONT << 2));
		_delay_us(50);
		/*send display on/off instruction*/
		/*With initial states blink and cursor are off ,, display are on*/
		CLCD_SendInstruction(CLCD_DISPLAY_CONTROL | (CLCD_BlinkOff) | (CLCD_CursorOff << 1) |(CLCD_DisplayOn << 2));
		_delay_us(50);
		/*send clear display instruction*/
		CLCD_SendInstruction(CLCD_CLEAR_DISPLAY);
		_delay_ms(3);
		/*send entry mode set function*/
		/*CLCD_SendInstruction(CLCD_ENTRY_MODE_SET);*/
	#endif
}

void CLCD_PrintString(char *str)
{
	uint8_t iterator;
	for(iterator = 0 ; str[iterator] != '\0'; iterator++)
	{
		CLCD_SendData(str[iterator]);
	}
}
void CLCD_SetCursor(uint8_t x_position , uint8_t y_position)
{
	if(y_position == 0)
	{
		CLCD_SendInstruction(CLCD_DDRAM_ADDRESS + x_position);
		_delay_us(50);
	}
	else if (y_position == 1)
	{
		CLCD_SendInstruction(CLCD_DDRAM_ADDRESS + x_position + 0X40);
		_delay_us(50);
	}
}
void CLCD_BlinkCursor(void)
{
	CLCD_SendInstruction( CLCD_DISPLAY_CONTROL | (CLCD_BlinkOn) | (CLCD_DisplayOn << 2));
	_delay_us(50);
}

void CLCD_NoBlinkCursor(void)
{
	CLCD_SendInstruction(CLCD_DISPLAY_CONTROL | (CLCD_BlinkOff) | (CLCD_DisplayOn << 2));
	_delay_us(50);
}

void CLCD_TurnOnCursor(void)
{
	CLCD_SendInstruction(CLCD_DISPLAY_CONTROL | (CLCD_CursorOn << 1) | (CLCD_DisplayOn << 2));
	_delay_us(50);
}

void CLCD_TurnOffCursor(void)
{
	CLCD_SendInstruction(CLCD_DISPLAY_CONTROL | (CLCD_CursorOff << 1) | (CLCD_DisplayOn << 2));
	_delay_us(50);
}
void CLCD_TurnOnDisplay(void)
{
	CLCD_SendInstruction(CLCD_DISPLAY_CONTROL | (CLCD_DisplayOn << 2));
	_delay_us(50);
}

void CLCD_TurnOffDisplay(void)
{
	CLCD_SendInstruction(CLCD_DISPLAY_CONTROL | (CLCD_DisplayOff << 2));
	_delay_us(50);
}

void CLCD_ShiftCursorRight(void)
{
	CLCD_SendInstruction(CLCD_CURSOR_OR_DISPLAY_SHIFT | (CLCD_SC_CURSOR << 3) | ( CLCD_RL_RIGHT << 2));
	_delay_us(50);
}

void CLCD_ShiftCursorLeft(void)
{
	CLCD_SendInstruction(CLCD_CURSOR_OR_DISPLAY_SHIFT | (CLCD_SC_CURSOR << 3) | ( CLCD_RL_LEFT << 2));
	_delay_us(50);
}
void CLCD_ShiftDisplayLeft(void)
{
	CLCD_SendInstruction(CLCD_CURSOR_OR_DISPLAY_SHIFT | (CLCD_SC_DISPLAY << 3) | ( CLCD_RL_LEFT << 2));
	_delay_us(50);
}

void CLCD_ShiftDisplayRight(void)
{
	CLCD_SendInstruction(CLCD_CURSOR_OR_DISPLAY_SHIFT | (CLCD_SC_DISPLAY << 3) | ( CLCD_RL_RIGHT << 2));
	_delay_us(50);
}

void CLCD_PrintChar(char Ch)
{
	CLCD_SendData(Ch);
}
void CLCD_PrintNumber(int16_t Number)
{
	uint8_t NumberDigitsArray[16];
	uint8_t NumberDigitArrayIndex = 0;
	uint8_t i;
	if(Number < 0)
	{
		Number *= -1; /*change to positive number*/
		CLCD_PrintChar('-'); /*Print negative sign*/
	}
	while(Number != 0)
	{
		NumberDigitsArray[NumberDigitArrayIndex] = Number % 10;
		NumberDigitArrayIndex++;
		Number /= 10;
	}

	if(NumberDigitArrayIndex == 0)
	{
		CLCD_PrintChar(0 + '0');
	}
	else
	{
		for(i = NumberDigitArrayIndex ; i > 0 ; i--)
		{
			CLCD_PrintChar(NumberDigitsArray[i - 1] + '0');
		}
	}
}

void CLCD_StoreSpecialCharater(uint8_t PixelsArray[] , uint8_t Location)
{
	uint8_t PixelsArrayIterator = 0;
	Location *= 8;
	/*Send the CGRAM instruction*/
	CLCD_SendInstruction(CLCD_CGRAM_ADDRESS + Location);
	for(PixelsArrayIterator = 0 ; PixelsArrayIterator < 7 ; PixelsArrayIterator++)
	{
		CLCD_SendData(PixelsArray[PixelsArrayIterator]);
	}
	/*make the adress counter point to DDRAM*/
	CLCD_SendInstruction(CLCD_DDRAM_ADDRESS);

}

void CLCD_PrintSpecialCharacter(uint8_t Location)
{
	CLCD_SendData(Location);
}

void CLCD_ClearCLCD(void)
{
	CLCD_SendInstruction(CLCD_CLEAR_DISPLAY);
}

void CLCD_PrintFloat(float32_t Number)
{
	uint16_t IntegerPart = (uint32_t)Number;
	uint8_t DecimalPart = (uint8_t)((Number - IntegerPart)*100);
	CLCD_PrintNumber(IntegerPart);
	CLCD_PrintChar('.');
	CLCD_PrintNumber(DecimalPart);

}
