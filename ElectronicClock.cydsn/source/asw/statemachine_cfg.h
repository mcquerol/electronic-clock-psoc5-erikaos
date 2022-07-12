/**
* \file statemachine_cfg.h
* \author P. Fromm
* \date 23.6.20
*
* \brief generic statemachine implementation, based on 2 Layer lookup table
*
* detailed description what the file does
*
* \note <notes>
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 1.0; 23.06.2020; P. Fromm
*            - Initial version
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
**/


 
#ifndef STATEMACHINE_CFG_H
#define STATEMACHINE_CFG_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
#include "global.h"
    
   
#include "sc_events_type.h"
#include "sc_state_type.h"

/** ----------------------------- Event and State definitions --------------------------------------- **/    

// We will use the event definition from the event signal.
// Strictly spoken, the state machine events are only a subset, 
// but we want to avoid multiple similar definitions.
typedef EVENT_enum_t STATE_event_t;
    
// Same argument for the states
typedef SC_STATE_data_t STATE_state_t;

//Initial state of the state machine
#define STATE_INITIALSTATE SC_STATE_INIT_DATA




#endif /* STATEMACHINE_CFG_H */
