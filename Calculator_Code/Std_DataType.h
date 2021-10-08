/** @file Std_DataType.h
*
* @brief This file is used to define standarded data types in AVR (unsigned and signed) integers and floats.
* @layer Service
* @note	THIS FILE MUST BE INCLUDED IN ALL SOURCE FILES
* @author Abdelrhman Badr
* @last update 27-sep-21
*/

#ifndef  STD_DATATYPES_H_
#define STD_DATATYPES_H_

/*unsigned datatypes*/
typedef unsigned char 		uint8_t;
typedef unsigned short 		uint16_t;
typedef unsigned long 		uint32_t;
typedef unsigned long long 	uint64_t;

/*signed datatypes*/
typedef signed char 		 int8_t;
typedef signed short 		 int16_t;
typedef signed long 		 int32_t;
typedef signed long long     int64_t;

/*float datatypes*/
typedef float 	float32_t;
typedef double 	float64_t;

/*bool*/
typedef enum
{
	false,true,
}bool;
#endif /* STD_DATATYPES_H_ */
