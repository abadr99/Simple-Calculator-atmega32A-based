/*
 * Calculator.c
 *
 *  Created on: Oct 4, 2021
 *      Author: Abdelrhman Badr
 */

/*Include Services files*/
#include "Std_DataType.h"
#include "Math.h"
#include "Atmega32A.h"
#include "Error.h"
#include "util/delay.h"

/*Incude MCAL files*/
#include "DIO.h"

/*Include HAL files*/
#include "CLCD.h"
#include "KeyPad.h"

/*Include App files*/
#include "Calculator.h"

void Calculator_Initiate(void)
{
	CLCD_Setup();
	KeyPad_Setup();
}

void Calculator_CheckError(float32_t MathExpressionArr[] , bool *SyntxError , bool *MathError , uint8_t MathExpressionLastIndex)
{
	uint8_t i;
	*SyntxError = false;
	*MathError = false;

	/*Check for first element*/
	if(MathExpressionArr[0] == '*' || MathExpressionArr[0] == '/')
	{
		*SyntxError = true;
	}
	/*check for last element*/
	else if (MathExpressionArr[MathExpressionLastIndex] == '*' || MathExpressionArr[MathExpressionLastIndex] == '/' || MathExpressionArr[MathExpressionLastIndex] == '+' || MathExpressionArr[MathExpressionLastIndex] == '-')
	{
		*SyntxError = true;
	}
	else
	{
		for(i = 1 ; i < MathExpressionLastIndex - 1 ; i++)
		{
			if((MathExpressionArr[i] == '+') && (MathExpressionArr[i+1] == '*'))
			{
				*SyntxError = true;
				break;
			}
			else if((MathExpressionArr[i] == '-') && (MathExpressionArr[i+1] == '*'))
			{
				*SyntxError = true;
				break;
			}
			else if((MathExpressionArr[i] == '-') && (MathExpressionArr[i+1] == '/'))
			{
				*SyntxError = true;
				break;
			}
			else if((MathExpressionArr[i] == '-') && (MathExpressionArr[i+1] == '*'))
			{
				*SyntxError = true;
				break;
			}
			else if ((MathExpressionArr[i] == '/') && (MathExpressionArr[i+1] == 0))
			{
				*MathError = true;
			}
		}
	}
}

void Calculator_Evaluate(float32_t FirstNumber , uint8_t Operator , float32_t SecondNumber , float32_t *Result)
{
	switch (Operator)
	{
	case '+': *Result = FirstNumber + SecondNumber; break;
	case '-': *Result = FirstNumber - SecondNumber; break;
	case '*': *Result = FirstNumber * SecondNumber; break;
	case '/': *Result = (float32_t)FirstNumber / SecondNumber; break;
	default : break;
	}
}

uint8_t Calculator_PriorityCheck(uint8_t Operand)
{
	uint8_t ReturnVal;
	switch(Operand)
	{
	case '+':
	case '-':
		ReturnVal = 1;
		break;
	case '*':
	case '/':
		ReturnVal = 2;
		break;
	default:
		ReturnVal = 0;
		break;
	}
	return ReturnVal;
}
