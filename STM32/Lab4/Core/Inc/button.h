/*
 * button.h
 *  Created on: Dec 1, 2024
 *      Author: vtrnn
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "scheduler.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

#define NUM_OF_BUTTONS 3			// Number of Buttons to use

int isButtonPressed(int index);

void getKeyInput();

#endif /* INC_BUTTON_H_ */
