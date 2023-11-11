/*
 * Stack.c
 *
 *  Created on: Oct 5, 2021
 *      Author: Abdelrhman
 */

#include "Std_DataType.h"
#include "Stack.h"
// 8-bit stack
void Stack8_Initiate(Stack8_t *Stack)
{
	Stack->Top = 0;
	Stack->Size = 0;
}
void Stack8_Push(Stack8_t *Stack , uint8_t *PushedElement)
{
	Stack->StackArr[Stack->Top] = *PushedElement;
	Stack->Top ++;
	Stack->Size ++;
}
void Stack8_Pop(Stack8_t *Stack , uint8_t *PopedElement)
{
	Stack->Top --;
	*PopedElement = Stack->StackArr[Stack->Top];
	Stack->Size --;
}

uint8_t Stack8_Top(Stack8_t *Stack)
{
	return Stack->StackArr[(Stack->Top) - 1];
}
void Stack8_Size(Stack8_t *Stack , uint8_t *StackSize)
{
	*StackSize = Stack->Size;
}


void Stack16_Initiate(Stack16_t *Stack)
{
	Stack->Top = 0;
	Stack->Size = 0;
}

void Stack16_Push(Stack16_t *Stack,float32_t *PushedElement)
{
	Stack->StackArr[Stack->Top] = *PushedElement;
	Stack->Top ++;
	Stack->Size ++;
}
void Stack16_Pop(Stack16_t *Stack, float32_t *PopedElement)
{
	Stack->Top --;
	*PopedElement = Stack->StackArr[Stack->Top];
	Stack->Size --;
}
void Stack16_Top(Stack8_t *Stack , float32_t *TopElement)
{
	*TopElement = Stack->StackArr[(Stack->Top) - 1];
}
void Stack16_Size(Stack16_t *Stack , uint8_t *StackSize)
{
	*StackSize = Stack->Size;
}

