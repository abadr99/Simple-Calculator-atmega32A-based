/*
 * Calculator.h
 *
 *  Created on: Oct 4, 2021
 *      Author: Abdelrhman Badr
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#define MAX_VAL	(32760)
#define MIN_VAL	(-32760)


void Calculator_Initiate(void);
void Calculator_CheckError(float32_t MathExpressionArr[] , bool *SyntxError , bool *MathError , uint8_t MathExpressionLastIndex);
void Calculator_Evaluate(float32_t FirstNumber , uint8_t Operator , float32_t SecondNumber , float32_t *Result);
uint8_t Calculator_PriorityCheck(uint8_t Operand);
#endif /* CALCULATOR_H_ */
