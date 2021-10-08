/** @file DIO.h
*
* @brief .
* @layer MCAL
* @author Abdelrhman Badr
* @last update 27-sep-21
*/

#ifndef _DIO_H_
#define _DIO_H_

/*Define direction of pins*/
#define DIO_OUTPUT_PIN			(1)
#define DIO_INPUT_PIN			(2)
#define DIO_INPUT_PULLUP_PIN	(3)

/*Define direction of ports*/
#define DIO_OUTPUT_PORT	(0XFF)
#define DIO_INPUT_PORT	(0X00)

/*Define pin voltage levels*/
#define DIO_HIGH_PIN	(1)
#define DIO_LOW_PIN		(0)

/*Define port values*/
#define DIO_HIGH_PORT	(0XFF)
#define DIO_LOW_PORT	(0X00)

/*
*@brief				   This function is used to set tha data direction of the pin input, output
*@para				   1) Port --> PORTA, PORTB, PORTC, PORTD
*@para				   2) Pin number --> PIN0, PIN1, ..., PIN7
*@para				   3) Direction --> DIO_OUTPUT_PIN, DIO_INPUT_PIN
*@return Error state : 1) FunctionParameterError -->  if the passed parameter is wrong
*@return 			   2) NoError --> if the function executed successfully
*/
Error_t DIO_SetPinDirection(uint8_t Port ,uint8_t PinNumber , uint8_t Direction);

/*
*@brief				   This function is used to set tha data direction of the port input, output, value indicate for direction
*@para				   1) Port --> PORTA, PORTB, PORTC, PORTD
*@return Error state : 1) FunctionParameterError -->  if the passed parameter is wrong
*@return 			   2) NoError --> if the function executed successfully
*/
Error_t DIO_SetPortDirection(uint8_t Port , uint8_t Direction);

/*
*@brief				   This function is used to set the pin output voltage level (High/Low)
*@para				   1) Port --> PORTA, PORTB, PORTC, PORTD
*@para				   2) Pin number --> PIN0, PIN1, ..., PIN7
*@para				   3) VoltageLevel --> DIO_HIGH_PIN, DIO_LOW_PIN
*@return Error state : 1) FunctionParameterError -->  if the passed parameter is wrong
*@return 			   2) NoError --> if the function executed successfully
*/
Error_t DIO_WritePin(uint8_t Port , uint8_t PinNumber ,uint8_t VoltageLevel);
/*
*@brief				   This function is used to set the port output voltage val
*@para				   1) Port --> PORTA, PORTB, PORTC, PORTD
*@para				   3) VoltageLevel --> DIO_HIGH_Port (All pins will be high), DIO_LOW_PIN(All pins will be low),Value(for mixed values)
*@return Error state : 1) FunctionParameterError -->  if the passed parameter is wrong
*@return 			   2) NoError --> if the function executed successfully
*@return 			   3) OverFlowError --> if the passed port value is larger than 255
*/
Error_t DIO_WritePort(uint8_t Port , uint8_t PortVal);

/*
*@brief				   This function is used to get the pin input voltage value
*@para				   1) Port --> PORTA, PORTB, PORTC, PORTD
*@para				   2) Pin number --> PIN0, PIN1, ..., PIN7
*@para				   3) Address of the variable that input pin reading will be assigned to
*@return Error state : 1) FunctionParameterError -->  if the passed parameter is wrong
*@return 			   2) NoError --> if the function executed successfully
*/
Error_t DIO_ReadPin(uint8_t Port , uint8_t PinNumber , uint8_t * PinVal);

/*
*@brief				   This function is used to get the port input voltage value
*@para				   1) Port --> PORTA, PORTB, PORTC, PORTD
*@para				   2) Address of the variable to assign the result
*@return Error state : 1) FunctionParameterError -->  if the passed parameter is wrong
*@return 			   2) NoError --> if the function executed successfully
*/
Error_t DIO_ReadPort(uint8_t Port  , uint8_t * PortVal);

#endif /*_DIO_H_*/
