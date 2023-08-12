/*
 * HLCD_config.h
 *
 *  Created on: Jul 26, 2023
 *      Author: OMAR YAHYA
 */

#ifndef HLCD_HLCD_CONFIG_H_
#define HLCD_HLCD_CONFIG_H_

/**
 *  Choose LCD Data Connection:
 *  	HLCD_DATA_PINS
 *		HLCD_DATA_PORT
 */

#define HLCD_DATA HLCD_DATA_PINS

/**
 *  Choose LCD Mode:
 *  	HLCD_8BIT_MODE
 *		HLCD_4BIT_MODE
 */

#define HLCD_MODE HLCD_4BIT_MODE

#define HLCD_RS_PIN PC0
#define HLCD_RW_PIN PC1
#define HLCD_EN_PIN PC2

#define HLCD_WRITING_DELAY  0
#define HLCD_OVERFLOW_DELAY 500

#if((HLCD_DATA == HLCD_DATA_PORT) && (HLCD_MODE != HLCD_4BIT_MODE))
#define HLCD_D_PORT PORTA
#elif(HLCD_DATA == HLCD_DATA_PINS)
#if(HLCD_MODE != HLCD_4BIT_MODE)
#define HLCD_D0_PIN PA0
#define HLCD_D1_PIN PA1
#define HLCD_D2_PIN PA2
#define HLCD_D3_PIN PA3
#endif
#define HLCD_D4_PIN PC3
#define HLCD_D5_PIN PC4
#define HLCD_D6_PIN PC5
#define HLCD_D7_PIN PC6
#else
#error ("Wrong LCD Configuration !!")
#endif

/**
 *  Note : 4-Bit Mode Can't Work with HLCD_DATA_PORT
 */

#endif /* HLCD_HLCD_CONFIG_H_ */
