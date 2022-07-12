/**
* \file main
* \author Peter Fromm
* \date 5.12.2019
*
* \brief Demonstrator for critical regions
*
* this file contains a state machine implementation of a rection game using ERIKA OS
* some noise is expected on startup which can result in buggy UART messages
* the SSDs are sometimes glitchy but maybe depends n the board
*/

#include "project.h"
#include "global.h"

#include "led.h"
#include "button.h"
#include "tft.h"

#include "tsk_io.h"
#include "tsk_control.h"
#include "ringbuffer.h"
#include "statemachine.h"

#include "sc_events_type.h"
#include "swc_clock.h"

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

/**
* This funtion will activate all tasks / events which are called in a 1ms context
* Alternatively, we would have to create an own alarm for each
**/
void callback_1ms()
{
    SetEvent(tsk_io,ev_1ms);
    SetEvent(tsk_control,ev_1ms);
    
    
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
   
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
    ShutdownOS(0);
    while(1)
    {
    }
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

/** TASK tsk_init
 * initializes the UART, LEDs and SSD
 * it also activates the extended tasks and displays a
 * welcome message to the user through UART
 * this task is automatically started when the OS is started in the main function
 */
TASK(tsk_init)
{
    
    //Init MCAL Drivers
    UART_LOG_Start();
    LED_Init();
    TFT_init();
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
    
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
    
    //Start alarm
    SetRelAlarm(alarm_1ms,1,1);
    
    ActivateTask(tsk_control);
    ActivateTask(tsk_io);
    
    //TODO INIT STATE MACHINE AND RINGBUFFER
    
    //Activate all extended and the background task
    ActivateTask(tsk_background);
    
    TerminateTask();
    
}

/** TASK tsk_background
 * low priority task with a nop command
 */
TASK(tsk_background)
{
    while(1)
    {
        //do something with low prioroty
        __asm("nop");
    }
}

ISR2(isr_button)
{
    
    SetEvent(tsk_io,ev_event_onData);
    
}
/* [] END OF FILE */