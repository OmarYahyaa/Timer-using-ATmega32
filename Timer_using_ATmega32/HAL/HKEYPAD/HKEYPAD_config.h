/*
 * HKEYPAD_config.h
 *
 *  Created on: Jul 30, 2023
 *      Author: OMAR YAHYA
 */

#ifndef HKEYPAD_HKEYPAD_CONFIG_H_
#define HKEYPAD_HKEYPAD_CONFIG_H_

/**
 * Configure Pins for Keypad
 */

/** Rows **/
#define HKEYPAD_R1    PD0
#define HKEYPAD_R2    PD1
#define HKEYPAD_R3    PD2
#define HKEYPAD_R4    PD3
/** Columns **/
#define HKEYPAD_C1    PD4
#define HKEYPAD_C2    PD5
#define HKEYPAD_C3    PD6
#define HKEYPAD_C4    PD7

/**
 * Configure Keypad Keys (Key Mapping)
 */

#define ASSIGNMENT1 1
#define ASSIGNMENT2 2

#define HKEYPAD_KEYS    {{7,8,9,'R'},{4,5,6,'L'},{1,2,3,'E'},{'C',0,'=','S'}}

#endif /* HKEYPAD_HKEYPAD_CONFIG_H_ */
