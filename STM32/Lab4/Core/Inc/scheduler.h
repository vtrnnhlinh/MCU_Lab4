/*
 * schedule.h
 *
 *  Created on: Dec 1, 2024
 *      Author: vtrnn
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

#define SCH_MAX_TASKS	40

extern int TIME_CYCLE;	// Time cycle

typedef struct{
	void (*pTask)(void);
	uint32_t 	Delay;	// Time of the first time operation
	uint32_t 	Period;	// Time of the next time operation
	uint8_t 	RunMe;	// Number of times to perform the operation

	uint32_t 	TaskID;	// Location of task
}sTasks;

void SCH_Init(void);
uint32_t SCH_Add_Task ( void (*pFunction)() ,
					uint32_t DELAY,
					uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);

#endif /* INC_SCHEDULER_H_ */
