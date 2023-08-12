/*
 * MDIO_program.c
 *
 *  Created on: Jul 15, 2023
 *      Author: OMAR YAHYA
 */

#include <STD_TYPES.h>
#include <BIT_MATH.h>
#include <ERROR_STATES.h>
#include <MDIO_register.h>
#include <MDIO_private.h>
#include <MDIO_config.h>
#include <MDIO_interface.h>

ErrorState_t MDIO_enSetPinDirection(Pin_t copy_enPin,Direction_t copy_enDirection) {
	ErrorState_t Local_enState = SUCCESS;
	u8 Local_u8Port = copy_enPin / 10;
	u8 Local_u8Pin  = copy_enPin % 10;
	switch (Local_u8Port) {
	case PORTA:
		if (OUTPUT == copy_enDirection) {
			SET_BIT(REG_DDRA, Local_u8Pin);
		} else if (INPUT == copy_enDirection) {
			CLR_BIT(REG_DDRA, Local_u8Pin);
		} else {
			Local_enState = OUT_OF_RANGE_ERR;
		}
		break;
	case PORTB:
		if (OUTPUT == copy_enDirection) {
			SET_BIT(REG_DDRB, Local_u8Pin);
		} else if (INPUT == copy_enDirection) {
			CLR_BIT(REG_DDRB, Local_u8Pin);
		} else {
			Local_enState = OUT_OF_RANGE_ERR;
		}
		break;
	case PORTC:
		if (OUTPUT == copy_enDirection) {
			SET_BIT(REG_DDRC, Local_u8Pin);
		} else if (INPUT == copy_enDirection) {
			CLR_BIT(REG_DDRC, Local_u8Pin);
		} else {
			Local_enState = OUT_OF_RANGE_ERR;
		}
		break;
	case PORTD:
		if (OUTPUT == copy_enDirection) {
			SET_BIT(REG_DDRD, Local_u8Pin);
		} else if (INPUT == copy_enDirection) {
			CLR_BIT(REG_DDRD, Local_u8Pin);
		} else {
			Local_enState = OUT_OF_RANGE_ERR;
		}
		break;
	default:
		Local_enState = OUT_OF_RANGE_ERR;
		break;
	} // switch
	return Local_enState;
}

ErrorState_t MDIO_enSetPortDirection(Port_t copy_enPort, u8 copy_u8Value) {
	ErrorState_t Local_enState = SUCCESS;
	if ((0 > copy_u8Value) || (255 < copy_u8Value)) {
		Local_enState = OUT_OF_RANGE_ERR;
	} else {
		switch (copy_enPort) {
		case PORTA: // PORTA
			REG_DDRA = copy_u8Value;
			break;
		case PORTB: // PORTB
			REG_DDRB = copy_u8Value;
			break;
		case PORTC: // PORTC
			REG_DDRC = copy_u8Value;
			break;
		case PORTD: // PORTD
			REG_DDRD = copy_u8Value;
			break;
		default:
			Local_enState = OUT_OF_RANGE_ERR;
			break;
		} // switch
	} // else
	return Local_enState;
}

ErrorState_t MDIO_enSetPinValue(Pin_t copy_enPin, Value_t copy_enValue) {
	ErrorState_t Local_enState = SUCCESS;
	u8 Local_u8Port = copy_enPin / 10;
	u8 Local_u8Pin  = copy_enPin % 10;
	switch (Local_u8Port) {
	case PORTA:
		if (HIGH == copy_enValue) {
			SET_BIT(REG_PORTA, Local_u8Pin);
		} else if (LOW == copy_enValue) {
			CLR_BIT(REG_PORTA, Local_u8Pin);
		} else {
			Local_enState = OUT_OF_RANGE_ERR;
		}
		break;
	case PORTB:
		if (HIGH == copy_enValue) {
			SET_BIT(REG_PORTB, Local_u8Pin);
		} else if (LOW == copy_enValue) {
			CLR_BIT(REG_PORTB, Local_u8Pin);
		} else {
			Local_enState = OUT_OF_RANGE_ERR;
		}
		break;
	case PORTC:
		if (HIGH == copy_enValue) {
			SET_BIT(REG_PORTC, Local_u8Pin);
		} else if (LOW == copy_enValue) {
			CLR_BIT(REG_PORTC, Local_u8Pin);
		} else {
			Local_enState = OUT_OF_RANGE_ERR;
		}
		break;
	case PORTD:
		if (HIGH == copy_enValue) {
			SET_BIT(REG_PORTD, Local_u8Pin);
		} else if (LOW == copy_enValue) {
			CLR_BIT(REG_PORTD, Local_u8Pin);
		} else {
			Local_enState = OUT_OF_RANGE_ERR;
		}
		break;
	default:
		Local_enState = OUT_OF_RANGE_ERR;
		break;
	} // switch
	return Local_enState;
}

ErrorState_t MDIO_enSetPortValue(Port_t copy_enPort, u8 copy_u8Value) {
	ErrorState_t Local_enState = SUCCESS;
	if ((0 > copy_u8Value) || (255 < copy_u8Value)) {
		Local_enState = OUT_OF_RANGE_ERR;
	} else {
		switch (copy_enPort) {
		case PORTA:
			REG_PORTA = copy_u8Value;
			break;
		case PORTB:
			REG_PORTB = copy_u8Value;
			break;
		case PORTC:
			REG_PORTC = copy_u8Value;
			break;
		case PORTD:
			REG_PORTD = copy_u8Value;
			break;
		default:
			Local_enState = OUT_OF_RANGE_ERR;
			break;
		} // switch
	} // else
	return Local_enState;
}

ErrorState_t MDIO_enGetPinValue(Pin_t copy_enPin, Value_t *ptrPinValue) {
	ErrorState_t Local_enState = SUCCESS;
	u8 Local_u8Port = copy_enPin / 10;
	u8 Local_u8Pin = copy_enPin % 10;
	if (NULL != ptrPinValue) {
		switch (Local_u8Port) {
		case PORTA:
			*ptrPinValue = GET_BIT(REG_PINA, Local_u8Pin);
			break;
		case PORTB:
			*ptrPinValue = GET_BIT(REG_PINB, Local_u8Pin);
			break;
		case PORTC:
			*ptrPinValue = GET_BIT(REG_PINC, Local_u8Pin);
			break;
		case PORTD:
			*ptrPinValue = GET_BIT(REG_PIND, Local_u8Pin);
			break;
		default:
			Local_enState = OUT_OF_RANGE_ERR;
			break;
		} // switch
	} // if
	else {
		Local_enState = NULL_POINTER_ERR;
	}
	return Local_enState;
}

ErrorState_t MDIO_enGetPortValue(Port_t copy_enPort, u8 *ptrPortValue) {
	ErrorState_t Local_enState = SUCCESS;
	if (NULL != ptrPortValue) {
		switch (copy_enPort) {
		case PORTA:
			*ptrPortValue = REG_PINA;
			break;
		case PORTB:
			*ptrPortValue = REG_PINB;
			break;
		case PORTC:
			*ptrPortValue = REG_PINC;
			break;
		case PORTD:
			*ptrPortValue = REG_PIND;
			break;
		default:
			Local_enState = OUT_OF_RANGE_ERR;
			break;
		} // switch
	} // if
	else {
		Local_enState = NULL_POINTER_ERR;
	}
	return Local_enState;
}

ErrorState_t MDIO_enTogglePinValue(Pin_t copy_enPin) {
	ErrorState_t Local_enState = SUCCESS;
	u8 Local_u8Port = copy_enPin / 10;
	u8 Local_u8Pin = copy_enPin % 10;
	switch (Local_u8Port) {
	case PORTA:
		TOGG_BIT(REG_PORTA, Local_u8Pin);
		break;
	case PORTB:
		TOGG_BIT(REG_PORTB, Local_u8Pin);
		break;
	case PORTC:
		TOGG_BIT(REG_PORTC, Local_u8Pin);
		break;
	case PORTD:
		TOGG_BIT(REG_PORTD, Local_u8Pin);
		break;
	default:
		Local_enState = OUT_OF_RANGE_ERR;
		break;
	} // switch
	return Local_enState;
}

ErrorState_t MDIO_enTogglePortValue(Port_t copy_enPort) {
	ErrorState_t Local_enState = SUCCESS;
	switch (copy_enPort) {
	case PORTA:
		TOGG_REG(REG_PORTA);
		break;
	case PORTB:
		TOGG_REG(REG_PORTB);
		break;
	case PORTC:
		TOGG_REG(REG_PORTC);
		break;
	case PORTD:
		TOGG_REG(REG_PORTD);
		break;
	default:
		Local_enState = OUT_OF_RANGE_ERR;
		break;
	} // switch
	return Local_enState;
}


