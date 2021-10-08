/*
 * CLCD_config.h
 *
 *  Created on: May 1, 2021
 *      Author: Abdelrhman Badr
 */

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_


#define CLCD_8BitMode	    (1)
#define CLCD_4BitMode_Upper	(0)
#define CLCD_4BitMode_Lower	(2)
#define CLCD_2Lines		    (1)
#define CLCD_1Lines		    (0)
#define CLCD_5X8		    (0)
#define CLCD_5X10		    (1)

/****************************/

/*Configuration of the LCD connection*/
#define CLCD_PORT		(PORTD)
#define CLCD_RS_PORT	(PORTD)
#define CLCD_RS_PIN		(PIN0)
#define CLCD_RW_PORT	(PORTD)
#define CLCD_RW_PIN		(PIN1)
#define CLCD_EN_PORT	(PORTD)
#define CLCD_EN_PIN		(PIN2)

/*LCD Modes*/
/*you have two modes: CLCD_8BitMode	&& CLCD_4BitMode*/
#define CLCD_DATA_MODE				(CLCD_4BitMode_Upper)
#define CLCD_NUMBER_OF_LINES		(CLCD_2Lines)
#define CLCD_FONT					(CLCD_5X8)
#define CLCD_INCREMENT_DECREMENT	(CLCD_Increment)
#endif /* CLCD_CONFIG_H_ */
