/*
 * main.c
 *
 *  Created on: Oct 4, 2021
 *      Author: Abdelrhman Badr
 */

/*Include Services files*/
#include "Std_DataType.h"
#include "Math.h"
#include "Atmega32A.h"
#include "Error.h"
#include "Stack.h"
#include "util/delay.h"

/*Incude MCAL files*/
#include "DIO.h"

/*Include HAL files*/
#include "CLCD.h"
#include "KeyPad.h"

/*Include App files*/
#include "Calculator.h"


void main (void)
{
	/*Initiate calculator*/
	Calculator_Initiate();

	uint8_t CastVariable; /*This temp variable is used to cast array elemnts to uint8_t before passing it*/
	float32_t MathExpressionArr[16] = {32761};
	uint8_t MathExpressionLastIndex = 0;
	uint8_t PressedNumber = KEYPAD_NOT_PRESSED;
	float32_t Number = 0;
	float32_t FirstOperand = 0;
	float32_t SecondOperand = 0;
	uint8_t Operator = 0;
	uint8_t i = 0;
	float32_t Result = 0;
	bool SyntaxErrorFlag = false;
	bool MathErrorFlag   = false;

	Stack8_t  OperatorStack ;
	Stack16_t OperandStack  ;
	uint8_t StackSize = 0;
	Stack8_Initiate(&OperatorStack);
	Stack16_Initiate(&OperandStack);

	while(1)
	{
		/*Get the math expression*/
		while(1)
		{
			do
			{
				KeyPad_GetValue(&PressedNumber);
			}
			while(PressedNumber == KEYPAD_NOT_PRESSED);

			if(PressedNumber != KEYPAD_NOT_PRESSED && PressedNumber != 'O')
			{
				if(PressedNumber == '+' || PressedNumber == '-' || PressedNumber == '*' || PressedNumber == '/' || PressedNumber == '=')
				{
					/*Insert number to MathExpressionArr*/
					MathExpressionArr[MathExpressionLastIndex] = Number;
					MathExpressionLastIndex ++;
					Number = 0;
					MathExpressionArr[MathExpressionLastIndex] = PressedNumber;
					MathExpressionLastIndex ++;
					if(PressedNumber == '=')
					{
						MathExpressionLastIndex -= 2;
						break;
					}
				}
				else if((PressedNumber >= '0') || (PressedNumber <= '9'))
				{
					Number = (PressedNumber - '0') + (Number * 10);
				}
				CLCD_PrintChar(PressedNumber);
				/*Handle one press*/
				while(PressedNumber != KEYPAD_NOT_PRESSED)
				{
					KeyPad_GetValue(&PressedNumber);
				}
			}
			KeyPad_GetValue(&PressedNumber);
		}

		/*Error checking*/
		CastVariable = (uint8_t)MathExpressionLastIndex;
		Calculator_CheckError(MathExpressionArr,&SyntaxErrorFlag,&MathErrorFlag,CastVariable);
		if(SyntaxErrorFlag == false && MathErrorFlag == false)
		{
			/*Negative numbers*/
			if(MathExpressionArr[0] == '-')
			{
				MathExpressionArr[1] *= -1;
			}
			else
			{
				for(i = 1 ; i < MathExpressionLastIndex; i++)
				{
					if((MathExpressionArr[i] == '*') || (MathExpressionArr[i] == '/') || (MathExpressionArr[i] == '+'))
					{
						if(MathExpressionArr[i + 1] == '-')
						{
							MathExpressionArr[i + 2] *= -1;
							MathExpressionArr[i + 1] = 32761;
							i += 3;
						}
					}
				}
				/*Get the result*/
				for(i = 0 ; i <= MathExpressionLastIndex ; i++)
				{
					/*check the scanned element is within range*/
					if(MathExpressionArr[i] <= MAX_VAL)
					{
						/*Check if the scanned element is operator*/
						if(((uint8_t)MathExpressionArr[i] == '+') || ((uint8_t)MathExpressionArr[i] == '-') || ((uint8_t)MathExpressionArr[i] == '*') || ((uint8_t)MathExpressionArr[i] == '/'))
						{
							Stack8_Size(&OperatorStack,&StackSize);
							if(StackSize == 0)
							{
								CastVariable = (uint8_t)MathExpressionArr[i];
								Stack8_Push(&OperatorStack,&CastVariable);
							}
							else if(Calculator_PriorityCheck(MathExpressionArr[i]) > Calculator_PriorityCheck(Stack8_Top(&OperatorStack)))
							{
								CastVariable = (uint8_t)MathExpressionArr[i];
								Stack8_Push(&OperatorStack,&CastVariable);
							}
							else if(Calculator_PriorityCheck((uint8_t)MathExpressionArr[i]) <= Calculator_PriorityCheck((uint8_t)Stack8_Top(&OperatorStack)))
							{
								do
								{
									Stack16_Pop(&OperandStack,&SecondOperand);
									Stack16_Pop(&OperandStack,&FirstOperand);
									Stack8_Pop(&OperatorStack,&Operator);
									Calculator_Evaluate(FirstOperand,Operator,SecondOperand,&Result);
									CLCD_SetCursor(0,1);
									Stack16_Push(&OperandStack,&Result);
									Stack16_Size(&OperandStack,&StackSize);
								}while(StackSize != 1);
								CastVariable = (uint8_t)MathExpressionArr[i];
								Stack8_Push(&OperatorStack,&CastVariable);
							}
						}
						else /*Operand*/
						{
							Stack16_Push(&OperandStack,&MathExpressionArr[i]);
						}
					}
				}
				Stack8_Size(&OperatorStack,&StackSize);
				while(StackSize != 0)
				{
					Stack16_Pop(&OperandStack,&SecondOperand);
					Stack16_Pop(&OperandStack,&FirstOperand);
					Stack8_Pop(&OperatorStack,&Operator);
					Calculator_Evaluate(FirstOperand,Operator,SecondOperand,&Result);
					Stack16_Push(&OperandStack,&Result);
					Stack8_Size(&OperatorStack,&StackSize);
				}
				CLCD_SetCursor(0,1);
				CLCD_PrintString("Result = ");
				CLCD_PrintFloat(Result);
			}
		}
		else /*case of error*/
		{
			if(SyntaxErrorFlag == true)
			{
				CLCD_SetCursor(0,1);
				CLCD_PrintString("SYNTAX ERROR");
			}
			else if(MathErrorFlag == true)
			{
				CLCD_SetCursor(0,1);
				CLCD_PrintString("MATH ERROR");
			}
		}

		do
		{
			KeyPad_GetValue(&PressedNumber);
		}while(PressedNumber != 'O');

		MathExpressionLastIndex = 0;
		PressedNumber = KEYPAD_NOT_PRESSED;
		Number = 0;
		FirstOperand = 0;
		SecondOperand = 0;
		Operator = 0;
		Result = 0;
		SyntaxErrorFlag = false;
		MathErrorFlag   = false;
		Stack8_Initiate(&OperatorStack);
		Stack16_Initiate(&OperandStack);
		StackSize = 0;
		CLCD_SetCursor(0,0);
		CLCD_PrintString("																	");
		CLCD_SetCursor(0,1);
		CLCD_PrintString("																	");
		CLCD_SetCursor(0,0);

	}
}
