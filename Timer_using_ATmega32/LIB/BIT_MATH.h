/*
 * BIT_MATH.h
 *
 *  Created on: Jul 15, 2023
 *      Author: OMAR YAHYA
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(reg,bit)  reg |=  (1<<(bit))
#define CLR_BIT(reg,bit)  reg &= ~(1<<(bit))
#define TOGG_BIT(reg,bit) reg ^=  (1<<(bit))
#define TOGG_REG(reg)	  (reg= ~(reg))
#define GET_BIT(reg,bit)  (reg>>(bit)) & 1

#endif /* BIT_MATH_H_ */
