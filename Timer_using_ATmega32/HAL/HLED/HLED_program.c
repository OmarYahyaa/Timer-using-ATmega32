/*
 * HLED_program.c
 *
 *  Created on: Jul 18, 2023
 *      Author: OMAR YAHYA
 */

#include <STD_TYPES.h>
#include <ERROR_STATES.h>
#include <MDIO_interface.h>
#include <HLED_private.h>
#include <HLED_config.h>
#include <HLED_interface.h>

ErrorState_t HLED_enInit(Led_t *PtrLed) {
	ErrorState_t Local_enState = SUCCESS;
	if (PtrLed != NULL) {
		MDIO_enSetPinDirection(PtrLed->LED_Pin, OUTPUT);
		switch (PtrLed->LED_Connection) {
		case SOURCE:
			MDIO_enSetPinValue(PtrLed->LED_Pin, LOW);
			break;
		case SINK:
			MDIO_enSetPinValue(PtrLed->LED_Pin, HIGH);
			break;
		default:
			Local_enState = OUT_OF_RANGE_ERR;
			break;
		}
	} // if --> PtrLed != NULL
	else {
		Local_enState = NULL_POINTER_ERR;
	}
	return Local_enState;
}

ErrorState_t HLED_enEnable(Led_t *PtrLed) {
	ErrorState_t Local_enState = SUCCESS;
	if (PtrLed != NULL) {
		switch (PtrLed->LED_Connection) {
		case SOURCE:
			MDIO_enSetPinValue(PtrLed->LED_Pin, HIGH);
			break;
		case SINK:
			MDIO_enSetPinValue(PtrLed->LED_Pin, LOW);
			break;
		default:
			Local_enState = OUT_OF_RANGE_ERR;
			break;
		}
	} // if --> PtrLed != NULL
	else {
		Local_enState = NULL_POINTER_ERR;
	}

	return Local_enState;
}

ErrorState_t HLED_enDisable(Led_t *PtrLed) {
	ErrorState_t Local_enState = SUCCESS;
	if (PtrLed != NULL) {
		switch (PtrLed->LED_Connection) {
		case SOURCE:
			MDIO_enSetPinValue(PtrLed->LED_Pin, LOW);
			break;
		case SINK:
			MDIO_enSetPinValue(PtrLed->LED_Pin, HIGH);
			break;
		default:
			Local_enState = OUT_OF_RANGE_ERR;
			break;
		}
	} // if --> PtrLed != NULL
	else {
		Local_enState = NULL_POINTER_ERR;
	}

	return Local_enState;
}

ErrorState_t HLED_enToggle(Led_t *PtrLed) {
	ErrorState_t Local_enState = SUCCESS;
	if (PtrLed != NULL) {
		MDIO_enTogglePinValue(PtrLed->LED_Pin);
		return Local_enState;
	} else {
		Local_enState = NULL_POINTER_ERR;
	}
	return Local_enState;
}
