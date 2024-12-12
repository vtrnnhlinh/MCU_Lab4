/*
 * scheduler.c
 *
 *  Created on: Nov 25, 2024
 *      Author: ADMIN
 */


#include "scheduler.h"
#define TICK 10
sTask SCH_tasks_G[SCH_MAX_TASKS];
//khai bao them 1 bien de xem vi tri nao con trong
//uint8_t current_index_task = 0;
void SCH_Init(void)
{
	unsigned char i;
	for(i=0; i < SCH_MAX_TASKS; i++)
	{
		 SCH_Delete_Task(i);
	}
}

unsigned char SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD)
{
	 	unsigned char Index = 0;
	    // First find a gap in the array (if there is one)
	    while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
	    {
	       Index++;
	    }
	    // Have we reached the end of the list?
	    if (Index == SCH_MAX_TASKS)
	    {
	        return SCH_MAX_TASKS;
	    }
	    // If we're here, there is a space in the task array
	    SCH_tasks_G[Index].pTask = pFunction;
	    SCH_tasks_G[Index].Delay = DELAY/TICK;
	    SCH_tasks_G[Index].Period = PERIOD/TICK;
	    SCH_tasks_G[Index].RunMe = 0;
	    //Save this task in system
	    SCH_tasks_G[Index].TaskID = Index;
	    // return position of task (to allow later deletion)
	    return Index;
}

//this function calculates when a task is due to run and sets a flag
void SCH_Update(void)
{
	unsigned char Index;
	// NOTE: calculations are in *TICKS* ( not milliseconds )
	for ( Index = 0; Index < SCH_MAX_TASKS; Index++)
	{
		// Check if there is a task at this location
		if ( SCH_tasks_G[Index] . pTask)
		{
			if ( SCH_tasks_G[Index] . Delay == 0)
			{
				// The task is due to run
				// Inc . the ’RunMe’ flag
				SCH_tasks_G[Index] .RunMe += 1;
				if ( SCH_tasks_G[Index] . Period > 0 )
				{
					// Schedule periodic tasks to run again
					SCH_tasks_G[Index] . Delay = SCH_tasks_G[Index] . Period ;
				}
			}
			else
			{
				// Not yet ready to run : just decrement the delay
				SCH_tasks_G[Index].Delay --;
			}
		}
	}
}

//This function execute the tasks
void SCH_Dispatch_Tasks(void)
{
    unsigned char Index;
    // Dispatches (runs) the next task (if one is ready)
    for (Index = 0; Index < SCH_MAX_TASKS; Index++)
    {
        if (SCH_tasks_G[Index].RunMe > 0)
        {
            (*SCH_tasks_G[Index].pTask)(); // Run the task
            //SCH_tasks_G[Index].RunMe -= 1; // Reset / reduce RunMe flag
            SCH_tasks_G[Index].RunMe --;
            // Periodic tasks will automatically run again

            // - if this is a 'one shot' task, remove it from the array
            if (SCH_tasks_G[Index].Period == 0)
            {
                SCH_Delete_Task(Index);
            }
        }
    }
}

void SCH_Delete_Task(const unsigned char TASK_INDEX)
{
    SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
    SCH_tasks_G[TASK_INDEX].Delay = 0;
    SCH_tasks_G[TASK_INDEX].Period = 0;
    SCH_tasks_G[TASK_INDEX].RunMe = 0;
}
