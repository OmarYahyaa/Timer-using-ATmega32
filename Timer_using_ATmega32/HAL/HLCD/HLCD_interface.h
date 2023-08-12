/*
 * HLCD_interface.h
 *
 *  Created on: Jul 26, 2023
 *      Author: OMAR YAHYA
 */

#ifndef HLCD_HLCD_INTERFACE_H_
#define HLCD_HLCD_INTERFACE_H_

ErrorState_t HLCD_enInit(void);
ErrorState_t HLCD_enSendCommand(u8 copy_u8Command);
ErrorState_t HLCD_enSendData(u8 copy_u8Data);
ErrorState_t HLCD_enSendString(const char *ptrString);
ErrorState_t HLCD_enSendIntegerNumber(s32 copy_u32Num);
ErrorState_t HLCD_enGoToXY(u8 copy_u8X, u8 copy_u8Y);
ErrorState_t HLCD_enClearDisplay(void);
ErrorState_t HLCD_enClearCharachter(u8 copy_u8X, u8 copy_u8Y,u8 copy_u8Length);
/** Add the Custom Pattern before you Show anything on LCD **/
ErrorState_t HLCD_enSendCustomPattern(u8 *ptrPattern, u8 copy_u8PatternNum);
ErrorState_t HLCD_enDisplayCustomPattern(u8 copy_s8PatternNum);

#endif /* HLCD_HLCD_INTERFACE_H_ */
