

/*
 * Filename: swc_clock.c
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_types.h"
#include "swc_clock.h"



/* USER CODE START SWC_CLOCK_INCLUDE */
#include "statemachine.h"
#include "statemachine_cfg.h"
#include "sc_state_type.h"
#include "sc_clock_type.h"
#include "sc_events_type.h"
/* USER CODE END SWC_CLOCK_INCLUDE */


#include "sp_common.h"

/* USER CODE START SWC_CLOCK_USERDEFINITIONS */
/** ---------------------------------- Actions -------------------------------------- **/

/**
 *  Reset Car Statemachine
 */
static void CLOCK__requestReset();

/**
 * Will change the TFT display font when in editing mode
 */
static void CLOCK__setEditFonts();

/**
 * increase the value of the minute or hour widget by 1
 */
static void CLOCK__incrementWidget();

/**
 * Will request the list of available features
 */
static void CLOCK__setDisplayFonts();
/* USER CODE END SWC_CLOCK_USERDEFINITIONS */



/*
* component: swc_clock
* cycletime: 50
* description: Runnable for the input of the clock
* events: ev_1ms|ev_event_onData
* name: CLOCK_input_run
* shortname: input
* signalIN: so_event|so_clock|so_state
* signalOUT: so_event|so_clock|so_state
* task: tsk_io
*/
void CLOCK_input_run(RTE_event ev){
	
	/* USER CODE START CLOCK_input_run */

    SC_STATE_data_t state = SC_STATE_INIT_DATA;
    SC_EVENTS_data_t event = SC_EVENTS_INIT_DATA;
    
    STATE_initState(CLOCK_Connection_StateActions, CLOCK_Connection_StateActions_size, &state);
    
    //Store to-state
    RTE_SC_STATE_set(&SO_STATE_signal, state);
    
    
    //Get fromstate and event
   state = RTE_SC_STATE_get(&SO_STATE_signal);
   event = RTE_SC_EVENTS_get(&SO_EVENT_signal);
    
    
    //Call the state machine
    RC_t result = STATE_processEvent(   CLOCK_Connection_Transitions, CLOCK_Connection_Transitions_size,
                                        CLOCK_Connection_StateActions, CLOCK_Connection_StateActions_size,
                                        event.m_ev, &state);
    


    switch(event.m_ev) //set the events accordinly to the recieved event
    {
        
        case EV_NONE:
        event.m_ev = EV_NONE;
        break;
        
        case EV_KEYLEFT:
        event.m_ev = EV_KEYLEFT;
        break;
        
        case EV_KEYRIGHTLONGPRESS:
        event.m_ev = EV_KEYRIGHTLONGPRESS;
        break;
        
        case EV_KEYRIGHT:
        event.m_ev = EV_KEYRIGHT;
        break;
        
        case EV_250MS:
        event.m_ev = EV_250MS;
        break;
        
        case EV_1MIN:
        event.m_ev = EV_1MIN;
        break;
    }
    
    
    RTE_SC_EVENTS_set(&SO_EVENT_signal,event);
    /* USER CODE END CLOCK_input_run */
}

/*
* component: swc_clock
* cycletime: 0
* description: Runnable
* events: ev_1ms|ev_event_onData
* name: CLOCK_control_run
* shortname: control
* signalIN: so_event|so_clock|so_state
* signalOUT: so_event|so_clock|so_state
* task: tsk_control
*/
void CLOCK_control_run(RTE_event ev){
	
	/* USER CODE START CLOCK_control_run */
    
    /* USER CODE END CLOCK_control_run */
}

/*
* component: swc_clock
* cycletime: 250
* description: Runnable
* events: ev_1ms|ev_event_onData
* name: CLOCK_display_run
* shortname: display
* signalIN: so_event|so_clock|so_state
* signalOUT: so_event|so_clock|so_state
* task: tsk_io
*/
void CLOCK_display_run(RTE_event ev){
	
	/* USER CODE START CLOCK_display_run */

    /* USER CODE END CLOCK_display_run */
}

/* USER CODE START SWC_CLOCK_FUNCTIONS */
/** --------------------------------- State Actions  ---------------------------------- **/

/**
 *  Reset Car Statemachine
 */
static void CLOCK_requestReset()
{

    SC_EVENTS_data_t ev = SC_EVENTS_INIT_DATA;
    ev.m_ev = EV_NONE;
    RTE_SC_EVENTS_set(&SO_EVENT_signal, ev);
}

static void CLOCK__setEditFonts()
{

    SC_EVENTS_data_t ev = SC_EVENTS_INIT_DATA;
    ev.m_ev = EV_KEYLEFT;
    RTE_SC_EVENTS_set(&SO_EVENT_signal, ev);
}

static void CLOCK__incrementWidget()
{

    SC_EVENTS_data_t ev = SC_EVENTS_INIT_DATA;
    ev.m_ev = EV_KEYRIGHT;
    RTE_SC_EVENTS_set(&SO_EVENT_signal, ev);
}

static void CLOCK__setDisplayFonts()
{

    SC_EVENTS_data_t ev = SC_EVENTS_INIT_DATA;
    ev.m_ev = EV_KEYLEFT;
    RTE_SC_EVENTS_set(&SO_EVENT_signal, ev);
}



//============================================== WIDGET =====================================

/**  ===== CLOCK_W_ISDISPLAYING ====   */
static const STATE_stateInnerTransitionTable_t STATE_CLOCK_W_ISDISPLAYING_Transitions = {
/*    Event                 ToState                 	 Guard                       Action                       */
    { EV_KEYLEFT,           CLOCK_W_ISEDITING,           0,                          CLOCK__setEditFonts		}, 
};

/**  ===== CLOCK_W_ISEDITING ====   */
static const STATE_stateInnerTransitionTable_t STATE_CLOCK_W_ISEDITING_Transitions = {
/*    Event                 	ToState                 		Guard                       	Action                       */
    { EV_KEYRIGHT,              CLOCK_W_ISEDITING,                	0,                          CLOCK__incrementWidget	}, 
    { EV_KEYRIGHTLONGPRESS,		CLOCK_W_ISAUTOINCREMENT,            0,                          0						}, 
    { EV_KEYLEFT,				CLOCK_W_ISDISPLAYING,           	0,                          CLOCK__setDisplayFonts	}, 
};

/**  ===== CLOCK_W_ISAUTOINCREMENT ====   */
static const STATE_stateInnerTransitionTable_t STATE_CLOCK_W_ISAUTOINCREMENT_Transitions = {
/*    Event                 ToState                 				Guard                       Action                       */
    { EV_KEYRIGHT,          CLOCK_W_ISDISPLAYING,             		0,                          CLOCK__incrementWidget	},
    { EV_250MS,             CLOCK_W_ISAUTOINCREMENT,                0,                          CLOCK__incrementWidget	}, 
};


static const STATE_stateOuterTransitionTable_t CLOCK_Widget_Transitions = {
/*    fromState         			 Pointer to table                            			 Size of table [Elements]    */
    { CLOCK_W_ISDISPLAYING,          &STATE_CLOCK_W_ISDISPLAYING_Transitions,                sizeof(STATE_CLOCK_W_ISDISPLAYING_Transitions)/sizeof(STATE_stateInnerTransition_t)    	  },
    { CLOCK_W_ISEDITING,     		 &STATE_CLOCK_W_ISEDITING_Transitions,           		 sizeof(STATE_CLOCK_W_ISEDITING_Transitions)/sizeof(STATE_stateInnerTransition_t)     		  },
    { CLOCK_W_ISAUTOINCREMENT,       &STATE_CLOCK_W_ISAUTOINCREMENT_Transitions,             sizeof(STATE_CLOCK_W_ISAUTOINCREMENT_Transitions)/sizeof(STATE_stateInnerTransition_t) 	  },
};
static const uint16_t CLOCK_Widget_Transitions_Size = sizeof(CLOCK_Widget_Transitions)/sizeof(STATE_stateOuterTransitionTable_t);



//============================================== Container =====================================

/**  ===== CLOCK_C_ISDISPLAYING ====   */
static const STATE_stateInnerTransitionTable_t ISDISPLAYING_Transitions[] = {
/*    Event                 ToState                 	 	  Guard                       Action                       */
    { EV_KEYLEFT,           CLOCK_C_ISEDITINGHOURS,           0,                          CLOCK__dispatch_KL_Hours		},
	{ EV_1MIN,           	CLOCK_C_ISDISPLAYING,             0,                          CLOCK__increment1Minute		},
};

/**  ===== CLOCK_C_ISEDITINGHOURS ====   */
static const STATE_stateInnerTransitionTable_t ISEDITINGHOURS_Transitions = {
/*    Event                 	ToState                 		Guard                       	Action                       */
    { EV_KEYLEFT,				CLOCK_C_ISEDITINGMINUTES,           0,                          CLOCK__dispatch_KL_HoursMin	}, 
    { EV_KEYRIGHT,              CLOCK_C_ISEDITINGHOURS,             0,                          CLOCK__dispatch_KR_Hours	}, 
    { EV_KEYRIGHTLONGPRESS,		CLOCK_C_ISEDITINGHOURS,             0,                          CLOCK__dispatch_KRLP_Hours	},
    { EV_250MS,					CLOCK_C_ISEDITINGHOURS,           	0,                          CLOCK__dispatch_250MS_Hours	}, 	
};

/**  ===== CLOCK_C_ISEDITINGMINUTES ====   */
static const STATE_stateInnerTransitionTable_t ISEDITINGMINUTES_Transitions = {
/*    Event                 	ToState                 		Guard                       	Action                       */
    { EV_KEYLEFT,				CLOCK_C_ISDISPLAYING,   	        0,                          CLOCK__dispatch_KL_Min		}, 
    { EV_KEYRIGHT,              CLOCK_C_ISEDITINGMINUTES,           0,                          CLOCK__dispatch_KR_Min		}, 
    { EV_KEYRIGHTLONGPRESS,		CLOCK_C_ISEDITINGMINUTES,           0,                          CLOCK__dispatch_KRLP_Min	},
    { EV_250MS,					CLOCK_C_ISEDITINGMINUTES,         	0,                          CLOCK__dispatch_250MS_Min	}, 	
};


static const STATE_stateOuterTransitionTable_t CLOCK_Container_Transitions = {
/*    fromState         				 Pointer to table                            				 Size of table [Elements]    */
    { ISDISPLAYING,          	 &STATE_CLOCK_C_ISDISPLAYING_Transitions,                	 sizeof(ISDISPLAYING_Transitions)/sizeof(STATE_stateInnerTransition_t)    	  },
    { ISEDITINGHOURS,     		 &STATE_CLOCK_C_ISEDITINGHOURS_Transitions,           		 sizeof(ISEDITING_Transitions)/sizeof(STATE_stateInnerTransition_t)     		  },
    { ISEDITINGMINUTES,      	 &STATE_CLOCK_C_ISEDITINGMINUTES_Transitions,             	 sizeof(ISAUTOINCREMENT_Transitions)/sizeof(STATE_stateInnerTransition_t) 	  },
};
static const uint16_t CLOCK_Container_Transitions_Size = sizeof(CLOCK_Container_Transitions)/sizeof(STATE_stateOuterTransitionTable_t);




/** ---------------------------------- Action ------------------------------------------- **/

static const STATE_stateActionTable_t CLOCK_Connection_StateActions = {
/*  fromState           Entry                           Exit    */
  { ISDISPLAYING,       CLOCK__setDisplayFonts,        0   }
};
static const uint16_t CONTROL_Connection_StateActions_size = sizeof(CLOCK_Connection_StateActions)/sizeof(STATE_stateAction_t);


/**
**
** General Dispatcher, saving the states
**
**/

static void CLOCK__dispatch_wrapper(STATE_event_t ev, CLOCK_active_widget_t widget)
{
	
	//Read the state object (container);
    
	SC_CLOCK_data_t clock = RTE_SC_CLOCK_get(&SO_CLOCK_signal);
	
	//Set the active widget to the hour widget
	clock.m_clock.m_activeWidget = widget;
	
	//Write the changed widget back to the clock object
	RTE_SC_CLOCK_set(&SO_CLOCK_signal,clock);
	
	//And fire it to the container state machine
	//The widget state machine will be called by the container actions
	//We need a local copy of the widget state as the widget object is also changed by the widget actions
	
	if (widget == CLOCK_HOURWIDGET)
	{
		
		SC_STATE_data_t localState = clock.m_clock.m_hours.m_state;
		STATE_processEvent(&Clock_Widget_Transitions, CLOCK_Widget_Transitions_Size, 0, ev, &localState);
		
		//Re-read the state object in order to get the changed by the child
		clock = RTE_SC_CLOCK_get(&SO_CLOCK_signal);
		clock.m_clock.m_hours.m_state = localState;
		
		//Write the changed state back to the clock object
		RTE_SC_CLOCK_set(&SO_CLOCK_signal, clock);
	}
	else if (CLOCK_MINWDIGET == widget)
	{
		CLOCK_state_t localState = clock.m_minutes.m_state;
		STATE_processEvent(&Clock_Widget_Transitions, CLOCK_Widget_Transitions_Size, 0, ev, &localState);
		
		//Re-read the state object in order to get the changed by the child
		clock = RTE_SC_CLOCK_get(&SO_CLOCK_signal);
		clock.m_clock.m_minutes.m_state = localState;
		
		//Write the changed state back to the clock object
		RTE_SC_CLOCK_set(&SO_CLOCK_signal, clock);
	}

}

static void CLOCK__dispatch_KL_HoursMin()
{
    
CLOCK__dispatch_wrapper(EV_KEYLEFT, CLOCK_HOURWIDGET);    
CLOCK__dispatch_wrapper(EV_KEYLEFT, CLOCK_MINWIDGET); 

}

static void CLOCK__dispatch_KR_Hours()
{
    
CLOCK__dispatch_wrapper(EV_KEYRIGHT, CLOCK_HOURWIDGET);    

}

static void CLOCK__dispatch_KRLP_Hours()
{
    
CLOCK__dispatch_wrapper(EV_KEYRIGHTLONGPRESS, CLOCK_HOURWIDGET);    

}

static void CLOCK__dispatch_250MS_Hours()
{
    
CLOCK__dispatch_wrapper(EV_250MS, CLOCK_HOURWIDGET);    

}

static void CLOCK__dispatch_KL_Min()
{
  
CLOCK__dispatch_wrapper(EV_KEYLEFT, CLOCK_MINWIDGET); 

}

static void CLOCK__dispatch_KR_Min()
{
    
CLOCK__dispatch_wrapper(EV_KEYRIGHT, CLOCK_MINWIDGET);    

}

static void CLOCK__dispatch_KRLP_Min()
{
    
CLOCK__dispatch_wrapper(EV_KEYRIGHTLONGPRESS, CLOCK_MINWIDGET);    

}

static void CLOCK__dispatch_250MS_Min()
{
    
CLOCK__dispatch_wrapper(EV_250MS, CLOCK_MINWIDGET);    

}
/* USER CODE END SWC_CLOCK_FUNCTIONS */
