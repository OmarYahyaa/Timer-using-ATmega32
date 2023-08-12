/*
 * HKEYPAD_program.c
 *
 *  Created on: Jul 30, 2023
 *      Author: OMAR YAHYA
 */

#include <STD_TYPES.h>
#include <ERROR_STATES.h>
#include <avr/delay.h>
#include <MDIO_interface.h>
#include <HKEYPAD_private.h>
#include <HKEYPAD_config.h>
#include <HKEYPAD_interface.h>

ErrorState_t HKEYPAD_enInit(void) {
	ErrorState_t Local_enState = SUCCESS;
	/** Set Pin Direction for Rows as Input **/
	MDIO_enSetPinDirection(HKEYPAD_R1, INPUT);
	MDIO_enSetPinDirection(HKEYPAD_R2, INPUT);
	MDIO_enSetPinDirection(HKEYPAD_R3, INPUT);
	MDIO_enSetPinDirection(HKEYPAD_R4, INPUT);
	/** Activation Pull-Up Resistor **/
	MDIO_enSetPinValue(HKEYPAD_R1, HIGH);
	MDIO_enSetPinValue(HKEYPAD_R2, HIGH);
	MDIO_enSetPinValue(HKEYPAD_R3, HIGH);
	MDIO_enSetPinValue(HKEYPAD_R4, HIGH);
	/** Set Pin Direction for Columns as Output **/
	MDIO_enSetPinDirection(HKEYPAD_C1, OUTPUT);
	MDIO_enSetPinDirection(HKEYPAD_C2, OUTPUT);
	MDIO_enSetPinDirection(HKEYPAD_C3, OUTPUT);
	MDIO_enSetPinDirection(HKEYPAD_C4, OUTPUT);
	/** Set Pin Value for Columns Initially High **/
	MDIO_enSetPinValue(HKEYPAD_C1, HIGH);
	MDIO_enSetPinValue(HKEYPAD_C2, HIGH);
	MDIO_enSetPinValue(HKEYPAD_C3, HIGH);
	MDIO_enSetPinValue(HKEYPAD_C4, HIGH);
	return Local_enState;
}

ErrorState_t HKEYPAD_enGetPressedKey(u8 *ptrKey) {
	ErrorState_t Local_enState = SUCCESS;
	if (NULL != ptrKey) {
		u8 static Local_u8Keys[HKEYPAD_ROW_SIZE][HKEYPAD_COLUMN_SIZE] =
		HKEYPAD_KEYS;
		u8 static Local_u8Rows[] = HKEYPAD_ROWS;
		u8 static Local_u8Columns[] = HKEYPAD_COLUMNS;
		u8 Local_u8RowCounter;
		u8 Local_u8ColumnCounter;
		u8 Local_u8Flag = 0; // To finish looping if key pressed
		u8 Local_u8KeyState;
		u8 Local_u8PressedKey = HKEYPAD_NO_PRESSED_KEY;
		for (Local_u8ColumnCounter = 0;
				(Local_u8ColumnCounter < HKEYPAD_COLUMN_SIZE)
						&& (Local_u8Flag == 0); Local_u8ColumnCounter++) {
			/** Activate Current Column **/
			MDIO_enSetPinValue(Local_u8Columns[Local_u8ColumnCounter],
			HKEYPAD_KEY_PRESSED);
			for (Local_u8RowCounter = 0;
					(Local_u8RowCounter < HKEYPAD_ROW_SIZE)
							&& (Local_u8Flag == 0); Local_u8RowCounter++) {
				/** Read the Current Row **/
				MDIO_enGetPinValue(Local_u8Rows[Local_u8RowCounter],
						&Local_u8KeyState);
				if (Local_u8KeyState == HKEYPAD_KEY_PRESSED) {
					/** Long Press Elimination **/
					while (Local_u8KeyState == HKEYPAD_KEY_PRESSED) {
						MDIO_enGetPinValue(Local_u8Rows[Local_u8RowCounter],
								&Local_u8KeyState);
					} // while Key is Pressed
					Local_u8PressedKey =
							Local_u8Keys[Local_u8RowCounter][Local_u8ColumnCounter];
					Local_u8Flag = 1;
				} // if Key Pressed
			} // for --> Looping on Rows
			/** Deactivate Current Column **/
			MDIO_enSetPinValue(Local_u8Columns[Local_u8ColumnCounter], HIGH);
		} // for --> Looping on Columns
		*ptrKey = Local_u8PressedKey;
	} else {
		Local_enState = NULL_POINTER_ERR;
	}
	return Local_enState;
}
