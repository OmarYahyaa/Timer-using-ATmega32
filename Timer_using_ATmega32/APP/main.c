/*
 * main.c
 *
 *  Created on: Jul 30, 2023
 *      Author: OMAR YAHYA
 */

#include <STD_TYPES.h>
#include <ERROR_STATES.h>
#include <avr/delay.h>
#include <MDIO_interface.h>
#include <HKEYPAD_interface.h>
#include <HLCD_interface.h>
#include <HLED_interface.h>

#define LCD_FIRST_ROW     0
#define LCD_SECOND_ROW    1

#define HOURS_NUM1_POS    0
#define HOURS_NUM2_POS    1
#define MINUTES_NUM1_POS  3
#define MINUTES_NUM2_POS  4
#define SECONDS_NUM1_POS  6
#define SECONDS_NUM2_POS  7

#define HOURS_SECTION     0
#define MINUTES_SECTION   1
#define SECONDS_SECTION   2

void main(void) {
	u8 arrowPattern[]  = { 0x04, 0x0E, 0x1F, 0x0E, 0x0E, 0x0E, 0x0E, 0x00 };
	u8 personPattern[] = { 0x0E, 0x0E, 0x04, 0x1F, 0x04, 0x0E, 0x11, 0x00 };
	u8 pressedKey;
	u8 hoursNum1     = 0;
	u8 hoursNum2     = 0;
	u8 minutesNum1   = 0;
	u8 minutesNum2   = 0;
	u8 secondsNum1   = 0;
	u8 secondsNum2   = 0;
	s8 arrowPosition = 0;
	u8 enterCounter  = 0;
	Led_t led1 = { PC7, SOURCE };
	HLCD_enInit();
	HKEYPAD_enInit();
	HLED_enInit(&led1);
	HLCD_enSendCustomPattern(arrowPattern, 1);
	HLCD_enSendCustomPattern(personPattern, 2);
	HLCD_enSendString("00:00:00");
	HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
	HLCD_enDisplayCustomPattern(1);
	while (1) {
		HKEYPAD_enGetPressedKey(&pressedKey);
		switch (pressedKey) {
		case 0 ... 9:
			if ((pressedKey >= 6)
					&& (((enterCounter == MINUTES_SECTION)
							&& (arrowPosition == MINUTES_NUM1_POS))
							|| ((enterCounter == SECONDS_SECTION)
									&& (arrowPosition == SECONDS_NUM1_POS)))) {
				// No Action as the largest value in minutes and seconds is 59
			} else {
				HLCD_enGoToXY(LCD_FIRST_ROW, arrowPosition);
				HLCD_enSendIntegerNumber(pressedKey);
				switch (arrowPosition) {
				case HOURS_NUM1_POS:
					hoursNum1   = pressedKey;
					break;
				case HOURS_NUM2_POS:
					hoursNum2   = pressedKey;
					break;
				case MINUTES_NUM1_POS:
					minutesNum1 = pressedKey;
					break;
				case MINUTES_NUM2_POS:
					minutesNum2 = pressedKey;
					break;
				case SECONDS_NUM1_POS:
					secondsNum1 = pressedKey;
					break;
				case SECONDS_NUM2_POS:
					secondsNum2 = pressedKey;
					break;
				} // switch
			} // else
			break;
		case 'R': // Right
			/** Handling the boundaries for (Hours - Minutes - Seconds) **/
			if ((enterCounter == HOURS_SECTION) && ((arrowPosition + 1) == 2)) {
				HLCD_enClearCharachter(LCD_SECOND_ROW, arrowPosition, 1);
				arrowPosition = 0;
				HLCD_enGoToXY(1, arrowPosition);
				HLCD_enDisplayCustomPattern(1);
			} else if (enterCounter == MINUTES_SECTION
					&& ((arrowPosition + 1) == 5)) {
				HLCD_enClearCharachter(1, arrowPosition, 1);
				arrowPosition = 3;
				HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
				HLCD_enDisplayCustomPattern(1);
			} else if (enterCounter == SECONDS_SECTION
					&& ((arrowPosition + 1) == 8)) {
				HLCD_enClearCharachter(LCD_SECOND_ROW, arrowPosition, 1);
				arrowPosition = 6;
				HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
				HLCD_enDisplayCustomPattern(1);
			/** Handling the boundaries for (Hours - Minutes - Seconds) **/
			} else {
				HLCD_enClearCharachter(LCD_SECOND_ROW, arrowPosition, 1);
				arrowPosition++;
				HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
				HLCD_enDisplayCustomPattern(1);
			}
			break;
		case 'L': // Left
			/** Handling the boundaries for (Hours - Minutes - Seconds) **/
			if ((enterCounter == HOURS_SECTION)
					&& ((arrowPosition - 1) == -1)) {
				HLCD_enClearCharachter(LCD_SECOND_ROW, arrowPosition, 1);
				arrowPosition = 1;
				HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
				HLCD_enDisplayCustomPattern(1);
			} else if (enterCounter == MINUTES_SECTION
					&& ((arrowPosition - 1) == 2)) {
				HLCD_enClearCharachter(LCD_SECOND_ROW, arrowPosition, 1);
				arrowPosition = 4;
				HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
				HLCD_enDisplayCustomPattern(1);
			} else if (enterCounter == SECONDS_SECTION
					&& ((arrowPosition - 1) == 5)) {
				HLCD_enClearCharachter(LCD_SECOND_ROW, arrowPosition, 1);
				arrowPosition = 7;
				HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
				HLCD_enDisplayCustomPattern(1);
			/** Handling the boundaries for (Hours - Minutes - Seconds) **/
			} else {
				HLCD_enClearCharachter(LCD_SECOND_ROW, arrowPosition, 1);
				arrowPosition--;
				HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
				HLCD_enDisplayCustomPattern(1);
			}
			break;
		case 'E': // Enter
			enterCounter++;
			if (enterCounter == MINUTES_SECTION) {
				HLCD_enClearCharachter(LCD_SECOND_ROW, arrowPosition, 1);
				arrowPosition = 3;
				HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
				HLCD_enDisplayCustomPattern(1);
			} else if (enterCounter == SECONDS_SECTION) {
				HLCD_enClearCharachter(LCD_SECOND_ROW, arrowPosition, 1);
				arrowPosition = 6;
				HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
				HLCD_enDisplayCustomPattern(1);
			} else {
				enterCounter = HOURS_SECTION;
				HLCD_enClearCharachter(LCD_SECOND_ROW, arrowPosition, 1);
				arrowPosition = 0;
				HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
				HLCD_enDisplayCustomPattern(1);
			}
			break;
		case 'C': // Clear + Long Press for Stop Timer
			enterCounter = HOURS_SECTION;
			HLCD_enClearDisplay();
			HLCD_enSendString("00:00:00");
			arrowPosition = 0;
			HLCD_enGoToXY(LCD_SECOND_ROW, arrowPosition);
			HLCD_enDisplayCustomPattern(1);
			HLED_enDisable(&led1);
			hoursNum1   = 0;
			hoursNum2   = 0;
			minutesNum1 = 0;
			minutesNum2 = 0;
			secondsNum1 = 0;
			secondsNum2 = 0;
			break;
		case 'S': // Start
			/** Handling not to Take Action if Timer is not Set **/
			if (hoursNum1 == 0 && hoursNum2 == 0 && minutesNum1 == 0
					&& minutesNum2 == 0 && secondsNum1 == 0
					&& secondsNum2 == 0) {
				// No Action
			} else {
				enterCounter = 0;
				/** Clear Arrow **/
				HLCD_enClearCharachter(LCD_SECOND_ROW, arrowPosition, 1);
				while (1) {
					/***** Exiting From Loop when C Pressed *****/
					HKEYPAD_enGetPressedKey(&pressedKey);
					if (pressedKey == 'C') {
						break;
					}
					/***** Exiting From Loop when C Pressed *****/
					// 750 --> 1 Second
					_delay_ms(100);
					if (secondsNum1 == 0 && secondsNum2 == 0) {
						if (minutesNum1 == 0 && minutesNum2 == 0) {
							if (hoursNum1 == 0 && hoursNum2 == 0) {
								/***** Timer Finish Action ****/
								HLCD_enGoToXY(LCD_SECOND_ROW, 0);
								HLCD_enDisplayCustomPattern(2);
								HLCD_enSendString("   Its Time");
								HLCD_enGoToXY(LCD_SECOND_ROW, 15);
								HLCD_enDisplayCustomPattern(2);
								HLED_enEnable(&led1);
								break;
								/***** Timer Finish Action ****/
							} else if (hoursNum2 == 0) {
								hoursNum1--;
								HLCD_enGoToXY(LCD_FIRST_ROW, 0);
								HLCD_enSendIntegerNumber(hoursNum1);
								hoursNum2 = 9;
								HLCD_enGoToXY(LCD_FIRST_ROW, 1);
								HLCD_enSendIntegerNumber(hoursNum2);
								/***** Return Minutes to 59 ****/
								minutesNum1 = 5;
								minutesNum2 = 9;
								HLCD_enGoToXY(LCD_FIRST_ROW, 4);
								HLCD_enSendIntegerNumber(minutesNum2);
								HLCD_enGoToXY(LCD_FIRST_ROW, 3);
								HLCD_enSendIntegerNumber(minutesNum1);
								/***** Return Minutes to 59 ****/

								/***** Return Seconds to 59 ****/
								secondsNum1 = 5;
								secondsNum2 = 9;
								HLCD_enGoToXY(LCD_FIRST_ROW, 7);
								HLCD_enSendIntegerNumber(secondsNum2);
								HLCD_enGoToXY(LCD_FIRST_ROW, 6);
								HLCD_enSendIntegerNumber(secondsNum1);
								/***** Return Seconds to 59 ****/
							} else {
								hoursNum2--;
								HLCD_enGoToXY(LCD_FIRST_ROW, 1);
								HLCD_enSendIntegerNumber(hoursNum2);
								/***** Return Minutes to 59 ****/
								minutesNum1 = 5;
								minutesNum2 = 9;
								HLCD_enGoToXY(LCD_FIRST_ROW, 4);
								HLCD_enSendIntegerNumber(minutesNum2);
								HLCD_enGoToXY(LCD_FIRST_ROW, 3);
								HLCD_enSendIntegerNumber(minutesNum1);
								/***** Return Minutes to 59 ****/

								/***** Return Seconds to 59 ****/
								secondsNum1 = 5;
								secondsNum2 = 9;
								HLCD_enGoToXY(LCD_FIRST_ROW, 7);
								HLCD_enSendIntegerNumber(secondsNum2);
								HLCD_enGoToXY(LCD_FIRST_ROW, 6);
								HLCD_enSendIntegerNumber(secondsNum1);
								/***** Return Seconds to 59 ****/
							}
						} else if (minutesNum2 == 0) {
							minutesNum1--;
							HLCD_enGoToXY(LCD_FIRST_ROW, 3);
							HLCD_enSendIntegerNumber(minutesNum1);
							minutesNum2 = 9;
							HLCD_enGoToXY(LCD_FIRST_ROW, 4);
							HLCD_enSendIntegerNumber(minutesNum2);
							/***** Return Seconds to 59 ****/
							secondsNum1 = 5;
							secondsNum2 = 9;
							HLCD_enGoToXY(LCD_FIRST_ROW, 7);
							HLCD_enSendIntegerNumber(secondsNum2);
							HLCD_enGoToXY(LCD_FIRST_ROW, 6);
							HLCD_enSendIntegerNumber(secondsNum1);
							/***** Return Seconds to 59 ****/
						} else {
							minutesNum2--;
							HLCD_enGoToXY(LCD_FIRST_ROW, 4);
							HLCD_enSendIntegerNumber(minutesNum2);
							/***** Return Seconds to 59 ****/
							secondsNum1 = 5;
							secondsNum2 = 9;
							HLCD_enGoToXY(LCD_FIRST_ROW, 7);
							HLCD_enSendIntegerNumber(secondsNum2);
							HLCD_enGoToXY(LCD_FIRST_ROW, 6);
							HLCD_enSendIntegerNumber(secondsNum1);
							/***** Return Seconds to 59 ****/
						}
					} else if (secondsNum2 == 0) {
						secondsNum1--;
						HLCD_enGoToXY(LCD_FIRST_ROW, 6);
						HLCD_enSendIntegerNumber(secondsNum1);
						secondsNum2 = 9;
						HLCD_enGoToXY(LCD_FIRST_ROW, 7);
						HLCD_enSendIntegerNumber(secondsNum2);
					} else {
						secondsNum2--;
						HLCD_enGoToXY(LCD_FIRST_ROW, 7);
						HLCD_enSendIntegerNumber(secondsNum2);
					}
				} // while
			} // else --> Timer is Set
			break;
		default:
			break;
		} // switch
	} // Super Loop
} // main
