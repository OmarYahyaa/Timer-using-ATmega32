/*
 * MDIO_interface.h
 *
 *  Created on: Jul 15, 2023
 *      Author: OMAR YAHYA
 */

#ifndef MDIO_MDIO_INTERFACE_H_
#define MDIO_MDIO_INTERFACE_H_

#include <STD_TYPES.h>
#include <ERROR_STATES.h>

typedef enum {
/// PORTA
	PA0 = 10,
	PA1 = 11,
	PA2 = 12,
	PA3 = 13,
	PA4 = 14,
	PA5 = 15,
	PA6 = 16,
	PA7 = 17,
/// PORTB
	PB0 = 20,
	PB1 = 21,
	PB2 = 22,
	PB3 = 23,
	PB4 = 24,
	PB5 = 25,
	PB6 = 26,
	PB7 = 27,
///PORTC
	PC0 = 30,
	PC1 = 31,
	PC2 = 32,
	PC3 = 33,
	PC4 = 34,
	PC5 = 35,
	PC6 = 36,
	PC7 = 37,
///PORTD
	PD0 = 40,
	PD1 = 41,
	PD2 = 42,
	PD3 = 43,
	PD4 = 44,
	PD5 = 45,
	PD6 = 46,
	PD7 = 47
} Pin_t;

typedef enum {
	PORTA = 1, PORTB = 2, PORTC = 3, PORTD = 4
} Port_t;

typedef enum {
	PORT_OUTPUT = 0xFF, PORT_INPUT = 0x00
} PortDirection_t;

typedef enum {
	PORT_HIGH = 0xFF, PORT_LOW = 0x00
} PortValue_t;

typedef enum {
	INPUT = 0, OUTPUT = 1
} Direction_t;

typedef enum {
	LOW = 0, HIGH = 1
} Value_t;

ErrorState_t MDIO_enSetPinDirection(Pin_t copy_enPin,Direction_t copy_enDirection);
ErrorState_t MDIO_enSetPortDirection(Port_t copy_enPort, u8 copy_u8Value);
ErrorState_t MDIO_enSetPinValue(Pin_t copy_enPin, Value_t copy_enValue);
ErrorState_t MDIO_enSetPortValue(Port_t copy_enPort, u8 copy_u8Value);
ErrorState_t MDIO_enGetPinValue(Pin_t copy_enPin, Value_t *ptrPinValue);
ErrorState_t MDIO_enGetPortValue(Port_t copy_enPort, u8 *ptrPortValue);
ErrorState_t MDIO_enTogglePinValue(Pin_t copy_enPin);
ErrorState_t MDIO_enTogglePortValue(Port_t copy_enPort);

#endif /* MDIO_MDIO_INTERFACE_H_ */
