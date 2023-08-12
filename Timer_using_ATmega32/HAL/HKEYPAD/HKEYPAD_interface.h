/*
 * HKEYPAD_interface.h
 *
 *  Created on: Jul 30, 2023
 *      Author: OMAR YAHYA
 */

#ifndef HKEYPAD_HKEYPAD_INTERFACE_H_
#define HKEYPAD_HKEYPAD_INTERFACE_H_

ErrorState_t HKEYPAD_enInit(void);
ErrorState_t HKEYPAD_enGetPressedKey(u8 *ptrKey);

#endif /* HKEYPAD_HKEYPAD_INTERFACE_H_ */
