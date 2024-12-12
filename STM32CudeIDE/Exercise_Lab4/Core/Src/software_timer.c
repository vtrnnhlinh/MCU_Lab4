/*
 * software_timer.c
 *
 *  Created on: Nov 25, 2024
 *      Author: ADMIN
 */

int timer1_flag = 0;
int timer2_flag = 0;

int counter1 = 0;
int counter2 = 0;

void timerRun()
{
	if(counter1 > 0)
	{
		counter1--;
		if(counter1 == 0) timer1_flag = 1;
	}
	if(counter2 > 0)
	{
		counter2--;
		if(counter2 == 0) timer2_flag = 1;
	}
}
