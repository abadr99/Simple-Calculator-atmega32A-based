/*
 * Stack.h
 *
 *  Created on: Oct 5, 2021
 *      Author: Abdelrhman
 */

#ifndef STACK_H_
#define STACK_H_


#define MAX_STACK	(16)

typedef struct
{
	uint8_t Top;
	uint8_t Size;
	uint8_t StackArr[MAX_STACK];
}Stack8_t;

typedef struct
{
	uint8_t Top;
	uint8_t Size;
	float32_t StackArr[MAX_STACK];
}Stack16_t;

void Stack8_Initiate(Stack8_t *Stack);
void Stack8_Push(Stack8_t *Stack , uint8_t *PushedElement);
void Stack8_Pop(Stack8_t *Stack , uint8_t *PopedElement);
uint8_t Stack8_Top(Stack8_t *Stack);
void Stack8_Size(Stack8_t *Stack , uint8_t *Size);

void Stack16_Initiate(Stack16_t *Stack);
void Stack16_Push(Stack16_t *Stack,float32_t *PushedElement);
void Stack16_Pop(Stack16_t *Stack, float32_t *PopedElement);
void Stack16_Top(Stack8_t *Stack , float32_t *TopElement);
void Stack16_Size(Stack16_t *Stack , uint8_t *Size);

#endif /* STACK_H_ */
