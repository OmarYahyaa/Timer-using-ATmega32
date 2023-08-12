/*
 * HLCD_private.h
 *
 *  Created on: Jul 26, 2023
 *      Author: OMAR YAHYA
 */

#ifndef HLCD_HLCD_PRIVATE_H_
#define HLCD_HLCD_PRIVATE_H_

static void HLCD_voidNLatch(u8 copy_u8Byte);

#define HLCD_DATA_PINS                       		  0
#define HLCD_DATA_PORT                       		  1

#define HLCD_8BIT_MODE 						 		  0
#define HLCD_4BIT_MODE 						 		  1

/** LCD Instructions **/
#define HLCD_CMD_FUNCTION_SET_2LINES_5X8_8BIT     0b00111000
#define HLCD_CMD_FUNCTION_SET_2LINES_5X11_8BIT    0b00111100
#define HLCD_CMD_FUNCTION_SET_2LINES_5X8_4BIT     0b00101000
#define HLCD_CMD_FUNCTION_SET_2LINES_5X11_4BIT    0b00101100
#define HLCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF  0b00001100
#define HLCD_CMD_CLEAR_DISPLAY                    0b00000001
#define HLCD_CMD_ENTRY_MODE_SET_INC_NO_SHIFT      0b00000110

#define HLCD_SECOND_ROW_INITIAL_ADDRESS 		     0x40

#endif /* HLCD_HLCD_PRIVATE_H_ */
