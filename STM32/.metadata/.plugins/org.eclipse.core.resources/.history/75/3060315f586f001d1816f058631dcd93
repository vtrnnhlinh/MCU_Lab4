/*
 * button.c
 *
 *  Created on: Nov 29, 2022
 *      Author: dell
 */

#include "button.h"

// Khoi tao cac bien de xu li chong rung, xu li tin hieu, xu li nut nhan o hai che do (nhan thuong va nhan giu)
int KeyReg0[NUM_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg1[NUM_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg2[NUM_OF_BUTTONS] = {NORMAL_STATE};
int KeyReg3[NUM_OF_BUTTONS] = {NORMAL_STATE};

// Khoi tao cac flag cho tung button: button_flag (nhan thuong) va buttonlong_flag (nhan giu)
int button_flag[NUM_OF_BUTTONS] = {0};
int buttonlong_flag[NUM_OF_BUTTONS] = {0};

// Khoi tao cac bien dem chu ki de xac dinh hai su kien co the xay ra cua nut nhan
int TimeOutForKeyPress[NUM_OF_BUTTONS] = {0};

int isButtonPressed(int index) {
	if (button_flag[index] == 1) {
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index){
	button_flag[index] = 1;
}

void getKeyInput() {
	for (int i = 0; i < NUM_OF_BUTTONS; i++) {
		KeyReg0[i] = KeyReg1[i];	// Xu li chong rung
		KeyReg1[i] = KeyReg2[i];

		// Doc cac tin hieu tu cac nut nhan
		if (i == 0) {
			KeyReg2[i] = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);
		}

		// Xu li tin hieu
		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg3[i] != KeyReg2[i]){
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg2[i] == PRESSED_STATE){
					subKeyProcess(i);	// Kich timer_flag[i] = 1;
					if (buttonlong_flag[i] == 0) {
						TimeOutForKeyPress[i] = 2000 / TIME_CYCLE; 	// Set thoi gian 2s (dieu kien cho su kien longkeyPress dien ra)
					}
					else {
						TimeOutForKeyPress[i] = 1000 / TIME_CYCLE;	// Set thoi gian 1s (dieu kien cho nhung lan bien "counter" se tang gia tri (chi su dung cho button INC va DEC))
					}
				}
			} else {
				TimeOutForKeyPress[i]--;
				// Neu sau khoang thoi gian TimeOutForKeyPress lan dau tien (3s) ma van con nhan giu button, thi buttonlong_flag[i] se bang 1, nguoc lai se bang 0
				if (TimeOutForKeyPress[i] == 0){
					KeyReg3[i] = NORMAL_STATE;
					buttonlong_flag[i] = 1;
				}
			}
		}
		else {
			buttonlong_flag[i] = 0;
		}
	}
}



