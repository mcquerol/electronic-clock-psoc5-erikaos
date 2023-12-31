

/*
 * Filename: tsk_io.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "tsk_io.h"



/* USER CODE START TSK_IO_INCLUDE */
#include "sp_common.h"

/* USER CODE END TSK_IO_INCLUDE */

#include "swc_clock.h"



/* USER CODE START TSK_IO_USERDEFINITIONS */

/* USER CODE END TSK_IO_USERDEFINITIONS */

/*******************************************************************************
 * Runnable Tables from Activation Engine
 *******************************************************************************/

/* Cyclic Table */

const RTE_cyclicTable_t RTE_cyclicActivationTable_tsk_io[] = {
	{ CLOCK_input_run, 50 },	//Runnable
	{ CLOCK_display_run, 250 },	//Runnable
};
const uint16_t RTE_cyclicActivation_tsk_io_size = sizeof (RTE_cyclicActivationTable_tsk_io) / sizeof(RTE_cyclicTable_t); 


/*******************************************************************************
 * Task Body
 *******************************************************************************/


/*
* description: Task for the input and output sides
* events: ev_1ms
* mode: Cyclic
* name: tsk_io
* shortname: io
* signalpoolsRO: sp_common
* signalpoolsRW: sp_common
* tickEvent: ev_1ms
* timertickperiod: 1
*/
TASK(tsk_io)
{
	/* ticktime of the task */
	static uint32_t ticktime = 0;

	/* USER CODE START TSK_IO_TASKBOBY_PRE */

	/* USER CODE END TSK_IO_TASKBODY_PRE */
    
    //Process all cyclic runnables which are due
    RTE_ProcessCyclicTable(RTE_cyclicActivationTable_tsk_io, RTE_cyclicActivation_tsk_io_size, ticktime);
	
	/* USER CODE START TSK_IO_TASKBODY_POST */

	/* USER CODE END TSK_IO_TASKBODY_POST */

	ticktime += 1;
	if (ticktime > 0xFFFFFF00) ticktime = 0;
    
}


/*******************************************************************************
 * Interrupt Service Routines
 *******************************************************************************/

ISR2(isr_Button)
{
    SC_BUTTON_data_t myButton = SC_BUTTON_INIT_DATA;
    SC_EVENT_data_t myEvent   = SC_EVENT_INIT_DATA;
    
    SC_BUTTON_driverIn(&myButton);
    
    if(TRUE == myButton.buttonRightPressed)
    {
        myEvent.m_ev = EV_KEYRIGHT;
        RTE_SC_EVENT_set(&SO_EVENT_signal, myEvent);
    }
    else if(TRUE == myButton.buttonLeftPressed)
    {
        myEvent.m_ev = EV_KEYLEFT;
        RTE_SC_EVENT_set(&SO_EVENT_signal, myEvent);
    }
    else
    {
        //Intended To Do Nothing.
    }    
    
}

/* USER CODE START TSK_IO_ISR */

/* USER CODE END TSK_IO_ISR */

