/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
//
#include "project.h"
#include "global.h"
#include "button.h"
#include "tft.h"
#include "sp_common.h"

//#include "seven.h"
//#include "led.h"
//#include "joystick.h"


ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //Set systick period to 1 ms. Enable the INT and start it
    EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
    EE_systick_enable_int();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */    
    
    for(;;)
        StartOS(OSDEFAULTAPPMODE);
}

/****************************************************************************
* Task Definitions
*****************************************************************************/

TASK(tsk_init)
{
    //Init MCAL Drivers
    
    //LED_Init();
    //JOYSTICK_Init();
    //SEVEN_Init();
    UART_LOG_Start();
    TFT_init();
    
    //Reconfigure ISRs with OS parameters
    //This line MUST be called after the hardware driver initialization!
    EE_system_init();
    
    //Start Systick
    //Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();
    
    //Initialize clock signal
    SC_CLOCK_data_t myClock = SC_CLOCK_INIT_DATA;
    RTE_SC_CLOCK_set(&SO_CLOCK_DISPLAY_signal, myClock);
    
    TFT_setBacklight(100);
    TFT_setTextSize(1);
    TFT_setColors(BLACK, WHITE);
    TFT_print("1112296 - EAA LAB 2\n");
    
    //Start the cyclic alarms 
    SetRelAlarm(alrm_cyclic, 1, 1);
    SetRelAlarm(alrm_250ms, 300, 250);
    SetRelAlarm(alrm_1s, 1000, 1000);

    //Activate all extended and background task
    
    ActivateTask(tsk_control);
    
    ActivateTask(tsk_background);
    
    UART_LOG_PutString("1112296 - EAA LAB 2 \n");
    
    TerminateTask();
}

TASK(tsk_background)
{
    while(1)
    {
        __asm("nop");
    }
}
    
/* [] END OF FILE */
