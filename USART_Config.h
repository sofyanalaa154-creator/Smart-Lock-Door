/**********************************************************************/
/*****************		Author: Alaa		    ***********************/
/*****************		Layer:	MCAL			***********************/
/*****************		SWC:	USART			***********************/
/*****************		Version:1.00			***********************/
/**********************************************************************/
#ifndef USART_CONFIG_H
#define USART_CONFIG_H

#define F_CPU 16000000UL

/* Configuration Macros */
#define SYNC             0
#define ASYNC            1

#define DATA_FRAME_5BITS 5
#define DATA_FRAME_6BITS 6
#define DATA_FRAME_7BITS 7
#define DATA_FRAME_8BITS 8

#define STOP_1BIT        1
#define STOP_2BITS       2

#define NO_PARITY        0
#define EVEN             2
#define ODD              3

/* Driver Settings */
#define USART_MODE      ASYNC
#define DATA_FRAME      DATA_FRAME_8BITS
#define NO_OF_STOP_BIT  STOP_1BIT
#define NO_OF_PARITY    NO_PARITY
#define BAUD_RATE       9600

#endif
