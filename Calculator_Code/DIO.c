/** @file Dio.c
*
* @brief This source file is used for DIO function impelementation.
* @layer MCAL
* @author Abdelrhman Badr
* @last update 27-sep-21
*/

#include "Math.h"
#include "Std_DataType.h"
#include "Atmega32A.h"
#include "Error.h"
#include "DIO_Private.h"
#include "DIO.h"


Error_t DIO_SetPinDirection(uint8_t Port ,uint8_t PinNumber , uint8_t Direction)
{
	Error_t ReturnError = NoError;
	if(PinNumber > DIO_MAX_NUMBER_OF_PIN)
	{
		ReturnError = FunctionParameterError;
	}
	else
	{
		if(Direction == DIO_OUTPUT_PIN)
		{
			switch(Port)
			{
			case PORTA : SET_BIT(DDRA_REG,PinNumber); break;
			case PORTB : SET_BIT(DDRB_REG,PinNumber); break;
			case PORTC : SET_BIT(DDRC_REG,PinNumber); break;
			case PORTD : SET_BIT(DDRD_REG,PinNumber); break;
			default : ReturnError = FunctionParameterError; break;
			}
		}
		else if (Direction == DIO_INPUT_PIN)
		{
			switch(Port)
			{

			case PORTA : CLEAR_BIT(DDRA_REG,PinNumber); CLEAR_BIT(PORTA_REG,PinNumber); break;
			case PORTB : CLEAR_BIT(DDRB_REG,PinNumber); CLEAR_BIT(PORTB_REG,PinNumber); break;
			case PORTC : CLEAR_BIT(DDRC_REG,PinNumber); CLEAR_BIT(PORTC_REG,PinNumber); break;
			case PORTD : CLEAR_BIT(DDRD_REG,PinNumber); CLEAR_BIT(PORTD_REG,PinNumber); break;
			}
		}
		else if (Direction == DIO_INPUT_PULLUP_PIN)
		{
			switch(Port)
			{

			case PORTA : CLEAR_BIT(DDRA_REG,PinNumber); SET_BIT(PORTA_REG,PinNumber); break;
			case PORTB : CLEAR_BIT(DDRB_REG,PinNumber); SET_BIT(PORTB_REG,PinNumber); break;
			case PORTC : CLEAR_BIT(DDRC_REG,PinNumber); SET_BIT(PORTC_REG,PinNumber); break;
			case PORTD : CLEAR_BIT(DDRD_REG,PinNumber); SET_BIT(PORTD_REG,PinNumber); break;
			}
		}
		else
		{
			ReturnError = FunctionParameterError;
		}
	}

	return ReturnError;
}

Error_t DIO_SetPortDirection(uint8_t Port , uint8_t Direction)
{
	Error_t ReturnError = NoError;
	if(Direction == DIO_OUTPUT_PORT)
	{
		switch(Port)
		{
		case PORTA: DDRA_REG = DIO_OUTPUT_PORT; break;
		case PORTB: DDRB_REG = DIO_OUTPUT_PORT; break;
		case PORTC: DDRC_REG = DIO_OUTPUT_PORT; break;
		case PORTD: DDRD_REG = DIO_OUTPUT_PORT; break;
		default : ReturnError = FunctionParameterError; break;
		}
	}
	else if (Direction == DIO_INPUT_PORT)
	{
		switch(Port)
		{
		case PORTA: DDRA_REG = DIO_INPUT_PORT; break;
		case PORTB: DDRB_REG = DIO_INPUT_PORT; break;
		case PORTC: DDRC_REG = DIO_INPUT_PORT; break;
		case PORTD: DDRD_REG = DIO_INPUT_PORT; break;
		default : ReturnError = FunctionParameterError; break;
		}
	}

	else
	{
		ReturnError = FunctionParameterError;
	}
	return ReturnError;
}

Error_t DIO_WritePin(uint8_t Port , uint8_t PinNumber ,uint8_t VoltageLevel)
{
	Error_t ReturnError = NoError;

	if(PinNumber > DIO_MAX_NUMBER_OF_PIN)
	{
		ReturnError = FunctionParameterError;
	}
	else
	{
		if(VoltageLevel == DIO_HIGH_PIN)
		{
			switch(Port)
			{
			case PORTA: SET_BIT(PORTA_REG,PinNumber); break;
			case PORTB: SET_BIT(PORTB_REG,PinNumber); break;
			case PORTC: SET_BIT(PORTC_REG,PinNumber); break;
			case PORTD: SET_BIT(PORTD_REG,PinNumber); break;
			default : ReturnError = FunctionParameterError; break;
			}

		}
		else if (VoltageLevel == DIO_LOW_PIN)
		{
			switch(Port)
			{
			case PORTA: CLEAR_BIT(PORTA_REG,PinNumber); break;
			case PORTB: CLEAR_BIT(PORTB_REG,PinNumber); break;
			case PORTC: CLEAR_BIT(PORTC_REG,PinNumber); break;
			case PORTD: CLEAR_BIT(PORTD_REG,PinNumber); break;
			default : ReturnError = FunctionParameterError; break;
			}

		}
		else
		{
			ReturnError = FunctionParameterError;
		}
	}
	return ReturnError;
}
Error_t DIO_WritePort(uint8_t Port , uint8_t PortVal)
{
	Error_t ReturnError = NoError;
	if((uint16_t)PortVal > DIO_MAX_NUMBER_PORT_VAL)
	{
		ReturnError = OverFlowError;
	}
	else
	{
		switch(Port)
		{
		case PORTA:PORTA_REG = PortVal; break;
		case PORTB:PORTB_REG = PortVal; break;
		case PORTC:PORTC_REG = PortVal; break;
		case PORTD:PORTD_REG = PortVal; break;
		default : ReturnError = FunctionParameterError; break;
		}
	}
	return ReturnError;
}

Error_t DIO_ReadPin(uint8_t Port , uint8_t PinNumber , uint8_t * PinVal)
{
	Error_t ReturnError = NoError;
	if(PinNumber > DIO_MAX_NUMBER_OF_PIN)
	{
		ReturnError = FunctionParameterError;
	}
	else
	{
		switch(Port)
		{
		case PORTA: *PinVal = GET_BIT(PINA_REG,PinNumber); break;
		case PORTB: *PinVal = GET_BIT(PINB_REG,PinNumber); break;
		case PORTC: *PinVal = GET_BIT(PINC_REG,PinNumber); break;
		case PORTD: *PinVal = GET_BIT(PIND_REG,PinNumber); break;
		default : ReturnError = FunctionParameterError; break;
		}
	}

	return ReturnError;
}

Error_t DIO_ReadPort(uint8_t Port  , uint8_t * PortVal)
{
	Error_t ReturnError = NoError;
	switch(Port)
	{
	case PORTA: *PortVal = PINA_REG; break;
	case PORTB: *PortVal = PINB_REG; break;
	case PORTC: *PortVal = PINC_REG; break;
	case PORTD: *PortVal = PIND_REG; break;
	default : ReturnError = FunctionParameterError; break;
	}
	return ReturnError;
}
