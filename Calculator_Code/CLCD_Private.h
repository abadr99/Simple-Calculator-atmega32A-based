/*
 * CLCD_Private.h
 *
 *  Created on: Oct 2, 2021
 *      Author: Abdelrhman
 */

#ifndef CLCD_PRIVATE_H_
#define CLCD_PRIVATE_H_

/*Define modes of data connection*/
#define UPPER_DATA_CONNECTION	(1)
#define LOWER_DATA_CONNECTION	(2)

/*Private functions prototype*/
static void CLCD_SendEnablePulse(void);
static void CLCD_SendLSB(uint8_t DataModeConnection , uint8_t Data);
static void CLCD_SendMSB(uint8_t DataModeConnection, uint8_t Data);
static void CLCD_SendInstruction(uint8_t Instruction);
static void CLCD_SendData(uint8_t Data);
static void InitiateLCDDataPins(void);
static void InitiateLCDControlPins(void);

/*CLCD instructions*/
#define CLCD_CLEAR_DISPLAY		        (0X01)
#define CLCD_RETURN_HOME		        (0X02)
#define CLCD_ENTRY_MODE_SET		        (0X04)
#define CLCD_DISPLAY_CONTROL	        (0X08)
#define CLCD_CURSOR_OR_DISPLAY_SHIFT	(0X10)
#define CLCD_FUNCTION_SET				(0X20)
#define CLCD_DDRAM_ADDRESS				(0X80)
#define CLCD_CGRAM_ADDRESS				(0X40)
#define CLCD_CursorOff	    (0)
#define CLCD_CursorOn	    (1)
#define CLCD_BlinkOff	    (0)
#define CLCD_BlinkOn	    (1)
#define CLCD_Increment	    (1)
#define CLCD_Decrement	    (0)
#define CLCD_Shift		    (1)
#define CLCD_NoShift		(0)
#define CLCD_DisplayOn	    (1)
#define CLCD_DisplayOff	    (0)
#define CLCD_ShiftToRight	(1)
#define CLCD_ShiftToLeft 	(1)
#define CLCD_DisplayShift	(1)
#define CLCD_CursorMove		(0)
#define CLCD_SC_CURSOR		(0)
#define CLCD_SC_DISPLAY		(1)
#define CLCD_RL_LEFT		(0)
#define CLCD_RL_RIGHT		(1)
#define CLCD_4BITMODE		(0)


#endif /* CLCD_PRIVATE_H_ */
