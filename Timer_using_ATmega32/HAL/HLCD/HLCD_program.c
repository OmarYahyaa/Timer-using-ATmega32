/*
 * HLCD_program.c
 *
 *  Created on: Jul 26, 2023
 *      Author: OMAR YAHYA
 */

#include <STD_TYPES.h>
#include <ERROR_STATES.h>
#include <BIT_MATH.h>
#include <avr/delay.h>
#include <MDIO_interface.h>
#include <HLCD_private.h>
#include <HLCD_config.h>
#include <HLCD_interface.h>

static void HLCD_voidNLatch(u8 copy_u8Byte) {
#if((HLCD_DATA == HLCD_DATA_PORT) && (HLCD_MODE!=HLCD_4BIT_MODE))
	MDIO_enSetPortValue(HLCD_D_PORT, HLCD_DATA_PORT);
#elif(HLCD_DATA == HLCD_DATA_PINS)
	u8 Local_u8Counter = 0;
#if(HLCD_MODE==HLCD_8BIT_MODE)
	u8 Local_u8Condition = 8;
	u8 Local_u8LCD_Pins_arr[] = { HLCD_D0_PIN, HLCD_D1_PIN, HLCD_D2_PIN,
	HLCD_D3_PIN, HLCD_D4_PIN, HLCD_D5_PIN, HLCD_D6_PIN, HLCD_D7_PIN };
	for (Local_u8Counter = 0; Local_u8Counter < Local_u8Condition;
			Local_u8Counter++) {
		MDIO_enSetPinValue(Local_u8LCD_Pins_arr[Local_u8Counter],
				GET_BIT(copy_u8Byte, Local_u8Counter));
	} // for
#elif(HLCD_MODE==HLCD_4BIT_MODE)
	u8 Local_u8Condition = 4;
	u8 Local_u8LCD_Pins_arr[] = { HLCD_D4_PIN, HLCD_D5_PIN, HLCD_D6_PIN,
	HLCD_D7_PIN };
	/** Send Upper 4 Bits **/
	for (Local_u8Counter = 0; Local_u8Counter < Local_u8Condition;
			Local_u8Counter++) {
		MDIO_enSetPinValue(Local_u8LCD_Pins_arr[Local_u8Counter],
				GET_BIT(copy_u8Byte, Local_u8Counter + 4));
	} // for
	/** Enable Pulse **/
	MDIO_enSetPinValue(HLCD_EN_PIN, HIGH);
	_delay_ms(2);
	MDIO_enSetPinValue(HLCD_EN_PIN, LOW);
	/** Send Lower 4 Bits **/
	for (Local_u8Counter = 0; Local_u8Counter < Local_u8Condition;
			Local_u8Counter++) {
		MDIO_enSetPinValue(Local_u8LCD_Pins_arr[Local_u8Counter],
				GET_BIT(copy_u8Byte, Local_u8Counter));
	} // for
#endif
#endif
	/** Enable Pulse **/
	MDIO_enSetPinValue(HLCD_EN_PIN, HIGH);
	// It should be 230ns
	// Increased it to not make delay after each Send Command
	_delay_ms(2);
	MDIO_enSetPinValue(HLCD_EN_PIN, LOW);
}

ErrorState_t HLCD_enInit(void) {
	ErrorState_t Local_enState = SUCCESS;
	/** Set Pins Direction **/
	MDIO_enSetPinDirection(HLCD_RS_PIN, OUTPUT);
	MDIO_enSetPinDirection(HLCD_RW_PIN, OUTPUT);
	MDIO_enSetPinDirection(HLCD_EN_PIN, OUTPUT);
#if(HLCD_DATA == HLCD_DATA_PINS)
#if(HLCD_MODE != HLCD_4BIT_MODE)
	MDIO_enSetPinDirection(HLCD_D0_PIN, OUTPUT);
	MDIO_enSetPinDirection(HLCD_D1_PIN, OUTPUT);
	MDIO_enSetPinDirection(HLCD_D2_PIN, OUTPUT);
	MDIO_enSetPinDirection(HLCD_D3_PIN, OUTPUT);
#endif
	MDIO_enSetPinDirection(HLCD_D4_PIN, OUTPUT);
	MDIO_enSetPinDirection(HLCD_D5_PIN, OUTPUT);
	MDIO_enSetPinDirection(HLCD_D6_PIN, OUTPUT);
	MDIO_enSetPinDirection(HLCD_D7_PIN, OUTPUT);
#elif((HLCD_DATA == HLCD_DATA_PORT) && (HLCD_MODE!=HLCD_4BIT_MODE))
	MDIO_enSetPortDirection(HLCD_D_PORT, PORT_OUTPUT);
#endif
#if(HLCD_MODE != HLCD_4BIT_MODE)
	/*************** 8-bit Mode Initialization Steps ***************/
	/** Delay More than 30ms **/
	_delay_ms(35);
	/** Function Set Command **/
	HLCD_enSendCommand(HLCD_CMD_FUNCTION_SET_2LINES_5X8_8BIT);
	/** Display Control Command **/
	HLCD_enSendCommand(HLCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	/** Display Clear Command **/
	HLCD_enSendCommand(HLCD_CMD_CLEAR_DISPLAY);
	/** Entry Mode Set **/
	HLCD_enSendCommand(HLCD_CMD_ENTRY_MODE_SET_INC_NO_SHIFT);
	/*************** 8-bit Mode Initialization Steps ***************/
#else
	/*************** 4-bit Mode Initialization Steps ***************/
	/** Delay More than 30ms **/
	_delay_ms(35);
	/** Function Set Command **/
	/// Step 1 --> Send 0010

	/**
	 * Note: We Send this Pattern to Distinguish between 4-Bit and 8-Bit Mode
	 */

#if(HLCD_DATA!=HLCD_DATA_PORT)
	MDIO_enSetPinValue(HLCD_D4_PIN, 0);
	MDIO_enSetPinValue(HLCD_D5_PIN, 1);
	MDIO_enSetPinValue(HLCD_D6_PIN, 0);
	MDIO_enSetPinValue(HLCD_D7_PIN, 0);
#endif
	/// Step 2 --> Enable Pulse
	MDIO_enSetPinValue(HLCD_EN_PIN, HIGH);
	_delay_ms(2);
	MDIO_enSetPinValue(HLCD_EN_PIN, LOW);
	/// Step 3 --> Send Command
	HLCD_enSendCommand(HLCD_CMD_FUNCTION_SET_2LINES_5X8_4BIT);
	/** Display Control Command **/
	HLCD_enSendCommand(HLCD_CMD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	/** Display Clear Command **/
	HLCD_enSendCommand(HLCD_CMD_CLEAR_DISPLAY);
	/** Entry Mode Set **/
	HLCD_enSendCommand(HLCD_CMD_ENTRY_MODE_SET_INC_NO_SHIFT);
	/*************** 4-bit Mode Initialization Steps ***************/
#endif

	/**
	 * Note: Delay after each Send Command is included in Send Command Function.
	 */

	return Local_enState;
}

ErrorState_t HLCD_enSendCommand(u8 copy_u8Command) {
	ErrorState_t Local_enState = SUCCESS;
	/** Set RS to High for Sending Command **/
	MDIO_enSetPinValue(HLCD_RS_PIN, LOW);
	/** Set RW to Low for Writing **/
	MDIO_enSetPinValue(HLCD_RW_PIN, LOW);
	/** Send Command to Data Pins (4-Bit or 8-Bit Mode) **/
	HLCD_voidNLatch(copy_u8Command);
	return Local_enState;
}

ErrorState_t HLCD_enSendData(u8 copy_u8Data) {
	ErrorState_t Local_enState = SUCCESS;
	/** Set RS to High for Sending Data **/
	MDIO_enSetPinValue(HLCD_RS_PIN, HIGH);
	/** Set RW to Low for Writing **/
	MDIO_enSetPinValue(HLCD_RW_PIN, LOW);
	/** Send Data to Data Pins (4-Bit or 8-Bit Mode) **/
	HLCD_voidNLatch(copy_u8Data);
	return Local_enState;
}

ErrorState_t HLCD_enSendString(const char *ptrString) {
	ErrorState_t Local_enState = SUCCESS;
	if (NULL != ptrString) {
		s8 Local_s8Counter1 = 0; // Count the String Characters
		s8 Local_s8Counter2 = 0; // Count Position of Y
		s8 Local_s8Counter3 = 0; // Inner Counter to Clear LCD when it FUll
		u8 Local_u8InitialX = 0;
		while (ptrString[Local_s8Counter1] != '\0') {
			/** This part to handle overflow of the row and entire LCD **/
			if (Local_s8Counter2 == 16) {
				TOGG_BIT(Local_u8InitialX, 0);
				HLCD_enGoToXY(Local_u8InitialX, 0);
				Local_s8Counter2 = 0;
				Local_s8Counter3++;
			} // if Local_s8Counter2 == 16
			if (Local_s8Counter3 == 2) {
				_delay_ms(HLCD_OVERFLOW_DELAY);
				HLCD_enClearDisplay();
				_delay_ms(HLCD_OVERFLOW_DELAY);
				Local_s8Counter3 = 0;
			} // if Local_s8Counter3 == 2
			/** This part to handle overflow of the row and entire LCD **/
			_delay_ms(HLCD_WRITING_DELAY);
			HLCD_enSendData(ptrString[Local_s8Counter1]);
			Local_s8Counter1++;
			Local_s8Counter2++;
		} // while
	} else {
		Local_enState = NULL_POINTER_ERR;
	} // else
	return Local_enState;
}

ErrorState_t HLCD_enSendIntegerNumber(s32 copy_s32Num) {
	ErrorState_t Local_enState = SUCCESS;
	u8 Local_u8Numbers[10];
	s8 Local_s8Counter = 0;
	if (0 == copy_s32Num) {
		HLCD_enSendData('0');
	} else {
		if (0 > copy_s32Num) {
			HLCD_enSendData('-');
			copy_s32Num *= -1;
		} // if 0 > copy_s32Num
		while (copy_s32Num > 0) {
			Local_u8Numbers[Local_s8Counter] = copy_s32Num % 10;
			copy_s32Num /= 10;
			Local_s8Counter++;
		} // while
		Local_s8Counter--;
		for (; Local_s8Counter >= 0; Local_s8Counter--) {
			HLCD_enSendData(Local_u8Numbers[Local_s8Counter] + '0');
		} // for
	} // else copy_s32Num != 0
	return Local_enState;
}

ErrorState_t HLCD_enGoToXY(u8 copy_u8X, u8 copy_u8Y) {
	ErrorState_t Local_enState = SUCCESS;
	/** Calculating Address **/
	u8 Local_u8Address;
	if (((copy_u8X >= 0) && (copy_u8X <= 2))
			&& ((copy_u8Y >= 0) && (copy_u8Y <= 15))) {
		if (0 == copy_u8X) {
			/** Location for First Line **/
			Local_u8Address = copy_u8Y;
		} else if ((1 == copy_u8X)) {
			/** Location for Second Line **/
			Local_u8Address = HLCD_SECOND_ROW_INITIAL_ADDRESS + copy_u8Y;
		}
	} else {
		Local_enState = OUT_OF_RANGE_ERR;
	}
	/** Set DDRAM Address then Send Command **/
	HLCD_enSendCommand(SET_BIT(Local_u8Address, 7));
	return Local_enState;
}

ErrorState_t HLCD_enClearDisplay(void) {
	ErrorState_t Local_enState = SUCCESS;
	HLCD_enSendCommand(HLCD_CMD_CLEAR_DISPLAY);
	return Local_enState;
}

ErrorState_t HLCD_enClearCharachter(u8 copy_u8X, u8 copy_u8Y, u8 copy_u8Length) {
	ErrorState_t Local_enState = SUCCESS;
	u8 Local_u8Iterrator;
	HLCD_enGoToXY(copy_u8X, copy_u8Y);
	for (Local_u8Iterrator = 0; Local_u8Iterrator < copy_u8Length;
			Local_u8Iterrator++) {
		HLCD_enSendData(' ');
	}
	return Local_enState;
}

ErrorState_t HLCD_enSendCustomPattern(u8 *ptrPattern, u8 copy_u8PatternNum) {
	ErrorState_t Local_enState = SUCCESS;
	if (NULL != ptrPattern) {
		/** Calculating Initial CGRAM Address **/

		/**
		 *  Notes :
		 *  	- Pattern Number - 1 as it Starts from 0 to 7
		 *  	- Multiplied by 8 as each Pattern is 8 Rows
		 */

		u8 Local_u8Address = (copy_u8PatternNum - 1) * 8;
		u8 Local_u8Counter = 0;
		/** Set CGRAM Address then Sending Command **/
		HLCD_enSendCommand(SET_BIT(Local_u8Address, 6));
		/** Write Pattern in CGRAM **/
		for (Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++) {
			HLCD_enSendData(ptrPattern[Local_u8Counter]);
		}
		/** Go Back to the DDRAM **/
		HLCD_enGoToXY(0, 0);
	} else {
		Local_enState = NULL_POINTER_ERR;
	}
	return Local_enState;
}

ErrorState_t HLCD_enDisplayCustomPattern(u8 copy_u8PatternNum) {
	ErrorState_t Local_enState = SUCCESS;
	HLCD_enSendData(copy_u8PatternNum - 1);
	return Local_enState;
}

