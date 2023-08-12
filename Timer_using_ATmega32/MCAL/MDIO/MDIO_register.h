/*
 * MDIO_register.h
 *
 *  Created on: Jul 15, 2023
 *      Author: OMAR YAHYA
 */

#ifndef MDIO_MDIO_REGISTER_H_
#define MDIO_MDIO_REGISTER_H_

#define REG_DDRA  *((volatile u8 *)0x3A)
#define REG_PORTA *((volatile u8 *)0x3B)
#define REG_PINA  *((volatile u8 *)0x39)

#define REG_DDRB  *((volatile u8 *)0x37)
#define REG_PORTB *((volatile u8 *)0x38)
#define REG_PINB  *((volatile u8 *)0x36)

#define REG_DDRC  *((volatile u8 *)0x34)
#define REG_PORTC *((volatile u8 *)0x35)
#define REG_PINC  *((volatile u8 *)0x33)

#define REG_DDRD  *((volatile u8 *)0x31)
#define REG_PORTD *((volatile u8 *)0x32)
#define REG_PIND  *((volatile u8 *)0x30)

#endif /* MDIO_MDIO_REGISTER_H_ */
