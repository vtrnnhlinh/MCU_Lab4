/*
 * scheduler.h
 *
 *  Created on: Nov 25, 2024
 *      Author: ADMIN
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_
#include <stdint.h>
#include "main.h"
#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0

typedef struct
{
	//Pointer to the task
	void(*pTask)(void);

	uint32_t Delay;

	uint32_t Period;

	uint8_t RunMe;

	uint32_t TaskID;
}sTask;

void SCH_Init (void);
unsigned char SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Delete_Task(const unsigned char TASK_INDEX);

#endif /* INC_SCHEDULER_H_ */
