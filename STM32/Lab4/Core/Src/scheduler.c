/*
 * scheduler.c
 *
 *  Created on: Dec 1, 2024
 *      Author: vtrnn
 */

#include "scheduler.h"

int TIME_CYCLE; // Time cycle

// Define array list of task and variable count number of tasks
sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;


// Delete Task
uint8_t SCH_Delete_Task(uint32_t taskID) {
	// If no task in array or taskID invalid, return -1
	if (current_index_task == 0 || taskID < 0 || taskID >= SCH_MAX_TASKS) {
		return -1;
	}
	for (int i = taskID; i < SCH_MAX_TASKS-1; i++) {
		// Move task from index i+1 -> i
		SCH_tasks_G[i].pTask = SCH_tasks_G[i+1].pTask;
		SCH_tasks_G[i].Delay = SCH_tasks_G[i+1].Delay;
		SCH_tasks_G[i].Period = SCH_tasks_G[i+1].Period;
		SCH_tasks_G[i].RunMe = SCH_tasks_G[i+1].RunMe;
	}
	// Reset SCH_tasks_G[SCH_MAX_TASKS-1]
	SCH_tasks_G[SCH_MAX_TASKS-1].pTask = 0x0000;
	SCH_tasks_G[SCH_MAX_TASKS-1].Delay = 0;
	SCH_tasks_G[SCH_MAX_TASKS-1].Period = 0;
	SCH_tasks_G[SCH_MAX_TASKS-1].RunMe = 0;
	current_index_task--;
	return taskID;
}


// Initialize SCH_task
void SCH_Init(void) {
	while (current_index_task != 0) {
		SCH_Delete_Task(0);
	}
}


// Add task to the end of array SCH_task_G
// Has the same role as setTimer() of software timer
uint32_t SCH_Add_Task(void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
	if(current_index_task < SCH_MAX_TASKS) {
		// Initialize new task
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY/TIME_CYCLE;
		SCH_tasks_G[current_index_task].Period =  PERIOD/TIME_CYCLE;
		SCH_tasks_G[current_index_task].RunMe = 0;
		// Add to the end of array
		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		// Update current_index_task
		current_index_task++;
		return SCH_tasks_G[current_index_task].TaskID;
	}
	return -1;
}


// Update timer of each task
// Has the same role as timerRun() of software timer
void SCH_Update(void) {
	for(int i = 0; i < current_index_task; i++) {
		if(SCH_tasks_G[i].Delay > 0) {
			// Decrease 1 cycle
			SCH_tasks_G[i].Delay--;
		}
		else {
			// At the first time operation, time = Delay (input user)
			// At later times, time = Period;
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe += 1;
		}
	}
}


// Check RunMe each task
// Has the same role as check flag of software timer
void SCH_Dispatch_Tasks(void) {
	for(int i = 0; i < current_index_task; i++) {
		if(SCH_tasks_G[i].RunMe > 0) {
			SCH_tasks_G[i].RunMe--;		// Reset / reduce RunMe flag
			(*SCH_tasks_G[i].pTask)();	// Run the task
			// Periodic tasks will automatically run again
			// If this is a "one shot" task, remove it from the array
			if (SCH_tasks_G[i].Period == 0) {
				SCH_Delete_Task(i);
				i--;
			}
		}
	}
}

