/** @file Error.h
*
* @brief This file is for all error operations.
* @layer Service
* @author Abdelrhman Badr
* @last update 27-sep-21
*/


#ifndef _Error_H_
#define _Error_H_

/*This dataType is used for error handling*/
typedef enum
{
	NoError,
	FunctionParameterError,
	OverFlowError
}Error_t;

/*Write in this macro the function that will be exceuted if the error executed */
#define ErrorFunction()		{}

#endif /*end of _Error_H_*/
