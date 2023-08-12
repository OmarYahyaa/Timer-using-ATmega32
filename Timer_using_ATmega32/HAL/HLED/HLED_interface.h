/*
 * HLED_interface.h
 *
 *  Created on: Jul 18, 2023
 *      Author: OMAR YAHYA
 */

#ifndef HLED_HLED_INTERFACE_H_
#define HLED_HLED_INTERFACE_H_

typedef enum {
	SOURCE = 0, SINK = 1
} Led_Connection_t;

typedef struct {
	Pin_t LED_Pin;
	Led_Connection_t LED_Connection;
} Led_t;

ErrorState_t HLED_enInit(Led_t *PtrLed);
ErrorState_t HLED_enEnable(Led_t *PtrLed);
ErrorState_t HLED_enDisable(Led_t *PtrLed);
ErrorState_t HLED_enToggle(Led_t *PtrLed);

#endif /* HLED_HLED_INTERFACE_H_ */
