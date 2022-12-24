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
#include "clock_type.h"
//#include "logging.h"
#include "sp_common.h"

/*////////////////////////////////////////////////////////
                     PROTOTYPES
*/////////////////////////////////////////////////////////

//DISPATCHER
static void CLOCK_dispatch_KL_Hours();
static void CLOCK_increment1Minute();
static void CLOCK_dispatch_KL_HoursMin();
static void CLOCK_dispatch_KR_Hours();
static void CLOCK_dispatch_KRLP_Hours();
static void CLOCK_dispatch_250MS_Hours();
static void CLOCK_dispatch_KL_Min();
static void CLOCK_dispatch_KR_Min();
static void CLOCK_dispatch_KRLP_Min();
static void CLOCK_dispatch_250MS_Min();

//WIDGET
static void CLOCK_setEditFonts();
static void CLOCK_incrementWidget();
static void CLOCK_setDisplayFonts();
static void CLOCK_updateTime();

//DISPATCH WRAPPER
static void CLOCK_dispatch_wrapper(EVENT_enum_t ev, CLOCK_active_widget_t widget);


/*////////////////////////////////////////////////////////
                     ACTIIONS
*/////////////////////////////////////////////////////////

///////////////////////DISPATCHER///////////////////////

//CLOCK_dispatch_KL_Hours
static void CLOCK_dispatch_KL_Hours()
{
    UART_LOG_PutString("Dispatch KL Hours \n");
    
    CLOCK_dispatch_wrapper(EV_KEYLEFT, CLOCK_hour_widget);
}

//CLOCK_increment1Minute
static void CLOCK_increment1Minute()
{
    UART_LOG_PutString("Increment 1 Minute \n");
    
    CLOCK_dispatch_wrapper(EV_1MIN, CLOCK_hour_widget);
    
    CLOCK_dispatch_wrapper(EV_1MIN, CLOCK_minute_widget);
}

//CLOCK_dispatch_KL_HoursMin
static void CLOCK_dispatch_KL_HoursMin()
{
    UART_LOG_PutString("Dispatch KL Hours Min \n");
    
    CLOCK_dispatch_wrapper(EV_KEYLEFT, CLOCK_hour_widget);
    
    CLOCK_dispatch_wrapper(EV_KEYLEFT, CLOCK_minute_widget);
}

//CLOCK_dispatch_KR_Hours
static void CLOCK_dispatch_KR_Hours()
{
    UART_LOG_PutString("Dispatch KR Hours \n");
    
    CLOCK_dispatch_wrapper(EV_KEYRIGHT, CLOCK_hour_widget);
}

//CLOCK_dispatch_KRLP_Hours
static void CLOCK_dispatch_KRLP_Hours()
{
    UART_LOG_PutString("Dispatch KRLP Hours \n");
    
    CLOCK_dispatch_wrapper(EV_KEYRIGHTLONGPRESS, CLOCK_hour_widget);
}

//CLOCK_dispatch_250MS_Hours
static void CLOCK_dispatch_250MS_Hours()
{
    UART_LOG_PutString("Dispatch 250MS Hours \n");
    
    CLOCK_dispatch_wrapper(EV_250MS, CLOCK_hour_widget);
}

//CLOCK_dispatch_KL_Min
static void CLOCK_dispatch_KL_Min()
{
    UART_LOG_PutString("Dispatch KL Min \n");
    
    CLOCK_dispatch_wrapper(EV_KEYLEFT, CLOCK_minute_widget);
}

//CLOCK_dispatch_KR_Min
static void CLOCK_dispatch_KR_Min()
{
    UART_LOG_PutString("Dispatch KR Min \n");
    
    CLOCK_dispatch_wrapper(EV_KEYRIGHT, CLOCK_minute_widget);
}

//CLOCK_dispatch_KRLP_Min
static void CLOCK_dispatch_KRLP_Min()
{
    UART_LOG_PutString("Dispatch KRLP Min \n");
    
    CLOCK_dispatch_wrapper(EV_KEYRIGHTLONGPRESS, CLOCK_minute_widget);
}

//CLOCK_dispatch_250MS_Min
static void CLOCK_dispatch_250MS_Min()
{
    UART_LOG_PutString("Dispatch 250MS Min \n");
    
    CLOCK_dispatch_wrapper(EV_250MS, CLOCK_minute_widget);
}

///////////////////////WIDGET///////////////////////

//CLOCK_setEditFonts
//Chooses which of the editing widgets is active.
static void CLOCK_setEditFonts()
{
    UART_LOG_PutString("Set Edit Fonts \n");
    
    SC_CLOCK_data_t localClock = RTE_SC_CLOCK_get(&SO_CLOCK_signal);
    
    if(CLOCK_hour_widget == localClock.m_activeWidget) {
        
        localClock.m_hours.m_fontEditing = TRUE;
        
        localClock.m_minutes.m_fontEditing = FALSE;
    }
    else if (CLOCK_minute_widget == localClock.m_activeWidget){
        
        localClock.m_hours.m_fontEditing = FALSE;
        
        localClock.m_minutes.m_fontEditing = TRUE;
    }
    else
    {
        //Intended to do nothing.
    }
    
    RTE_SC_CLOCK_set(&SO_CLOCK_signal, localClock);
}

//CLOCK_setDisplayFonts
//Sets that none of the editing widgets is active.
static void CLOCK_setDisplayFonts()
{
    UART_LOG_PutString("Set Display Fonts \n");
    
    SC_CLOCK_data_t localClock = RTE_SC_CLOCK_get(&SO_CLOCK_signal);
    
    localClock.m_hours.m_fontEditing = FALSE;
    
    localClock.m_minutes.m_fontEditing = FALSE;
    
    
    RTE_SC_CLOCK_set(&SO_CLOCK_signal, localClock);
}

//CLOCK_incrementWidget
//Increments the widget until it reaches its maximum value, then resets it to zero.
static void CLOCK_incrementWidget()
{
    UART_LOG_PutString("Increment Widget \n");
    
    SC_CLOCK_data_t localClock = RTE_SC_CLOCK_get(&SO_CLOCK_signal);
    
    if(CLOCK_minute_widget == localClock.m_activeWidget)
    {
        if(localClock.m_minutes.m_maxValue > localClock.m_minutes.m_currentValue)
        {
            localClock.m_minutes.m_currentValue++;   
        }
        else
        {
            localClock.m_minutes.m_currentValue = 0; 
        }
    }
    else if(CLOCK_hour_widget == localClock.m_activeWidget)
    {
        if(localClock.m_hours.m_maxValue > localClock.m_hours.m_currentValue)
        {
            localClock.m_hours.m_currentValue++;   
        }
        else
        {
            localClock.m_hours.m_currentValue = 0; 
        }
    }
    else
    {
        //Intended to do nothing.
    }
    
    RTE_SC_CLOCK_set(&SO_CLOCK_signal, localClock);
}

//CLOCK_updateTime
static void CLOCK_updateTime()
{
    UART_LOG_PutString("Update Time \n");
    
    SC_CLOCK_data_t localClock = RTE_SC_CLOCK_get(&SO_CLOCK_signal);
    
    if(CLOCK_hour_widget == localClock.m_activeWidget && localClock.m_minutes.m_currentValue == localClock.m_minutes.m_maxValue) 
    {
        if(localClock.m_hours.m_currentValue < localClock.m_hours.m_maxValue) 
        {
            localClock.m_hours.m_currentValue++;
        }
        else 
        {
            localClock.m_hours.m_currentValue = 0;
        }
    }
    else if (CLOCK_minute_widget == localClock.m_activeWidget)
    {
        if(localClock.m_minutes.m_currentValue < localClock.m_minutes.m_maxValue) 
        {
            localClock.m_minutes.m_currentValue++;
        }
        else 
        {
            localClock.m_minutes.m_currentValue = 0;
        }
    }
    else
    {
        //Intended to do nothing
    }
    
    RTE_SC_CLOCK_set(&SO_CLOCK_signal, localClock);
}

/*////////////////////////////////////////////////////////
                     TABLES
*/////////////////////////////////////////////////////////

///////////////////////CONTAINER///////////////////////

//STATE_CLOCK_C_ISDISPLAYING_Transitions
const STATE_stateInnerTransition_t STATE_CLOCK_C_ISDISPLAYING_Transitions[] = {
/*           Event                        ToState             Guard       Action */
	{ EVENT(EV_KEYLEFT), 		STATE(CLOCK_C_ISEDITINGHOURS),	0,  	CLOCK_dispatch_KL_Hours },
	{ EVENT(EV_1MIN), 		    STATE(CLOCK_C_ISDISPLAYING), 	0, 	    CLOCK_increment1Minute  }, 
};
    
//STATE_CLOCK_C_ISEDITINGHOURS_Transitions
const STATE_stateInnerTransitionTable_t STATE_CLOCK_C_ISEDITINGHOURS_Transitions = {
/*          Event                            ToState                  Guard       Action */
	{ EVENT(EV_KEYLEFT), 		    STATE(CLOCK_C_ISEDITINGMINUTES),    0,  	CLOCK_dispatch_KL_HoursMin },
	{ EVENT(EV_KEYRIGHT), 		    STATE(CLOCK_C_ISEDITINGHOURS), 	    0, 	    CLOCK_dispatch_KR_Hours    }, 
    { EVENT(EV_KEYRIGHTLONGPRESS),  STATE(CLOCK_C_ISEDITINGHOURS),  	0, 	    CLOCK_dispatch_KRLP_Hours  }, 
    { EVENT(EV_250MS), 		        STATE(CLOCK_C_ISEDITINGHOURS),  	0, 	    CLOCK_dispatch_250MS_Hours }, 
};

//STATE_CLOCK_C_ISEDITINGMINUTES_Transitions
const STATE_stateInnerTransitionTable_t STATE_CLOCK_C_ISEDITINGMINUTES_Transitions = {
/*         Event                                 ToState             Guard           Action */
	{ EVENT(EV_KEYLEFT), 		    STATE(CLOCK_C_ISDISPLAYING),        0,  	CLOCK_dispatch_KL_Min    },
	{ EVENT(EV_KEYRIGHT), 		    STATE(CLOCK_C_ISEDITINGMINUTES), 	0, 	    CLOCK_dispatch_KR_Min    }, 
    { EVENT(EV_KEYRIGHTLONGPRESS),  STATE(CLOCK_C_ISEDITINGMINUTES),  	0, 	    CLOCK_dispatch_KRLP_Min  }, 
    { EVENT(EV_250MS), 		        STATE(CLOCK_C_ISEDITINGMINUTES),  	0, 	    CLOCK_dispatch_250MS_Min }, 
};

const STATE_stateOuterTransitionTable_t CLOCK_Container_Transitions = {
/*         fromState                PointerToTable                        Size of table [Elements] */
	{ STATE(CLOCK_C_ISDISPLAYING),      &STATE_CLOCK_C_ISDISPLAYING_Transitions,      sizeof(STATE_CLOCK_C_ISDISPLAYING_Transitions)/sizeof(STATE_stateInnerTransition_t)     },
	{ STATE(CLOCK_C_ISEDITINGHOURS),    &STATE_CLOCK_C_ISEDITINGHOURS_Transitions,    sizeof(STATE_CLOCK_C_ISEDITINGHOURS_Transitions)/sizeof(STATE_stateInnerTransition_t)   }, 
    { STATE(CLOCK_C_ISEDITINGMINUTES),  &STATE_CLOCK_C_ISEDITINGMINUTES_Transitions,  sizeof(STATE_CLOCK_C_ISEDITINGMINUTES_Transitions)/sizeof(STATE_stateInnerTransition_t) },
};

//Action Table
static const STATE_stateAction_t CLOCK_StateActions[] = {
    /*  fromState                               Entry           Exit*/
    { STATE(CLOCK_C_ISDISPLAYING),              0,              0   }
};


//const uint16_t CLOCK_Container_Transitions_Size = sizeof(CLOCK_Container_Transitions)/sizeof(STATE_stateOuterTransition_t);
    

///////////////////////WIDGET///////////////////////

//STATE_CLOCK_W_ISDISPLAYING_Transitions
const STATE_stateInnerTransitionTable_t STATE_CLOCK_W_ISDISPLAYING_Transitions = {
/*           Event                 ToState                Guard       Action */
	{ EVENT(EV_KEYLEFT),    STATE(CLOCK_W_ISEDITING),   	0,  	CLOCK_setEditFonts},
   	{ EVENT(EV_1MIN),       STATE(CLOCK_W_ISDISPLAYING),	0,  	CLOCK_updateTime},
};

//STATE_CLOCK_W_ISEDITING_Transitions
const STATE_stateInnerTransitionTable_t STATE_CLOCK_W_ISEDITING_Transitions = {
/*           Event                      ToState                  Guard       Action */
	{ EVENT(EV_KEYRIGHT),           STATE(CLOCK_W_ISEDITING),   	0,  	CLOCK_incrementWidget},
    { EVENT(EV_KEYRIGHTLONGPRESS),  STATE(CLOCK_W_ISAUTOINCREMENT),	0,  	0                    },
    { EVENT(EV_KEYLEFT),            STATE(CLOCK_W_ISDISPLAYING),	0,  	CLOCK_setDisplayFonts},
};

//STATE_CLOCK_W_ISAUTOINCREMENT_Transitions
const STATE_stateInnerTransitionTable_t STATE_CLOCK_W_ISAUTOINCREMENT_Transitions = {
/*           Event                ToState                    Guard       Action */
	{ EVENT(EV_KEYRIGHT),   STATE(CLOCK_W_ISEDITING),       	0,  	CLOCK_incrementWidget},
    { EVENT(EV_250MS),      STATE(CLOCK_W_ISAUTOINCREMENT), 	0,  	CLOCK_incrementWidget},
    { EVENT(EV_KEYLEFT),     STATE(CLOCK_W_ISDISPLAYING),   	0,  	CLOCK_setDisplayFonts},
};

//CLOCK_Widget_Transitions
const STATE_stateOuterTransitionTable_t CLOCK_Widget_Transitions = {
/*         fromState                          PointerToTable                          Size of table [Elements] */
	{ STATE(CLOCK_W_ISDISPLAYING),     &STATE_CLOCK_W_ISDISPLAYING_Transitions,      sizeof(STATE_CLOCK_W_ISDISPLAYING_Transitions)/sizeof(STATE_stateInnerTransition_t)    },
	{ STATE(CLOCK_W_ISEDITING),        &STATE_CLOCK_W_ISEDITING_Transitions,         sizeof(STATE_CLOCK_W_ISEDITING_Transitions)/sizeof(STATE_stateInnerTransition_t)       }, 
    { STATE(CLOCK_W_ISAUTOINCREMENT),  &STATE_CLOCK_W_ISAUTOINCREMENT_Transitions,   sizeof(STATE_CLOCK_W_ISAUTOINCREMENT_Transitions)/sizeof(STATE_stateInnerTransition_t) },
};

/*////////////////////////////////////////////////////////
                     STATE MACHINE OBJECTS
*/////////////////////////////////////////////////////////

//Hour Widget
STATE_t CLOCK_hourWidget = {
                                &CLOCK_Widget_Transitions,
                                sizeof(CLOCK_Widget_Transitions)/sizeof(STATE_stateOuterTransition_t),
                                &CLOCK_StateActions,
                                sizeof(CLOCK_StateActions)/sizeof(STATE_stateAction_t),
                                STATE(CLOCK_W_ISDISPLAYING)
};

//Minute Widget
STATE_t CLOCK_minuteWidget = {
                                &CLOCK_Widget_Transitions,
                                sizeof(CLOCK_Widget_Transitions)/sizeof(STATE_stateOuterTransition_t),
                                &CLOCK_StateActions,
                                sizeof(CLOCK_StateActions)/sizeof(STATE_stateAction_t),
                                STATE(CLOCK_W_ISDISPLAYING)
};

//Object of the State Machine
STATE_t CLOCK_fsm = {
                        &CLOCK_Container_Transitions,
                        sizeof(CLOCK_Container_Transitions)/sizeof(STATE_stateOuterTransition_t),
                        &CLOCK_StateActions,
                        sizeof(CLOCK_StateActions)/sizeof(STATE_stateAction_t),
                        STATE(CLOCK_C_ISDISPLAYING)
};


/*////////////////////////////////////////////////////////
                     DISPATCH WRAPPER
*/////////////////////////////////////////////////////////
static void CLOCK_dispatch_wrapper(EVENT_enum_t ev, CLOCK_active_widget_t widget)
{
    SC_CLOCK_data_t clock = RTE_SC_CLOCK_get(&SO_CLOCK_signal);
    
    clock.m_activeWidget = widget;
    
    RTE_SC_CLOCK_set(&SO_CLOCK_signal, clock);
    
    if(CLOCK_hour_widget == widget)
    {
        //CLOCK_state_t localState = clock.m_hours.m_state;
        STATE_processEvent(&CLOCK_hourWidget, ev);
    }
    else if(CLOCK_minute_widget == widget)
    {
        STATE_processEvent(&CLOCK_minuteWidget, ev);   
    }
    else
    {
        //Intended to do nothing.   
    }
    
}

/* [] END OF FILE */
