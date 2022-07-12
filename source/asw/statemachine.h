/**
* \file statemachine.h
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
* \copyright Copyright �2016
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


 
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
#include "global.h"
#include "statemachine_cfg.h"

/**
 * function pointer used for actions
 */
typedef void (*STATE_ActionPtr_t)();

/**
 * function pointer used for guards
 */
typedef boolean_t (*STATE_GuardPtr_t)();

   

/**
 * State Transition (Inner table)
 */
typedef struct
{
    STATE_event_t       event;                          /**< \brief The event firing the transition */
    STATE_state_t       toState;                        /**< \brief The target state */
	STATE_GuardPtr_t    guard;                          /**< \brief The guard function */
	STATE_ActionPtr_t   actionTransition;               /**< \brief The transition action */
	
} STATE_stateInnerTransition_t;

typedef STATE_stateInnerTransition_t  STATE_stateInnerTransitionTable_t[];

/**
 * State Transition (Outer table)
 */
typedef struct
{
    STATE_state_t                                    fromState;
    STATE_stateInnerTransitionTable_t const *  const pInnerTransitionTable;     /**< \brief Pointer to the transitions valid for this state */ 
    uint16_t                          const          size;                      /**< \brief Size of the inner table in elements */
} STATE_stateOuterTransition_t;

typedef STATE_stateOuterTransition_t  STATE_stateOuterTransitionTable_t[];



/**
 * State Action table. Here, no inner table is used as we do not have guards and not so many actions.
 */
typedef struct
{
    STATE_state_t       state;              /**< \brief The state */
	STATE_ActionPtr_t   actionEntry;        /**< \brief Entry Action of the state */
	STATE_ActionPtr_t   actionExit;         /**< \brief Exit Action of the state */
} STATE_stateAction_t;

typedef STATE_stateAction_t  STATE_stateActionTable_t[];





// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class Statemachine
{
public:
#endif /* Together */

/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/


/**
 * This function will initialise the state machine and process any state actions of the initial state
 * The state machine is implemented as a generic object, Several instances and configurations are supported
 * \param STATE_stateActionTable_t const * const actionTable            : IN - Pointer to the action table
 * \param uint16_t actionTableSize                                      : IN - action table size 
 * \param STATE_state_t state                                           : IN/OUT - Leaving and Resulting state
 * \return RC_SUCCESS or error
 */
RC_t STATE_initState(   STATE_stateActionTable_t const actionTable, 
                        uint16_t actionTableSize,
                        STATE_state_t* state);

/**
 * This function will process the event with the defined state machine
 * The state machine is implemented as a generic object, Several instances and configurations are supported
 * \param STATE_stateTransitionTable_t const * const transitionTable    : IN - Pointer to the transition table
 * \param uint16_t transitionTableSize                                  : IN - transition table size
 * \param STATE_stateActionTable_t const * const actionTable            : IN - Pointer to the action table
 * \param uint16_t actionTableSize                                      : IN - action table size 
 * \param STATE_event_t ev                                              : IN - Event to be processed
 * \param STATE_state_t state                                           : IN/OUT - Leaving and Resulting state
 * \return RC_SUCCESS or error
 */
RC_t STATE_processEvent(STATE_stateOuterTransitionTable_t const transitionTable,
                        uint16_t transitionTableSize,
                        STATE_stateActionTable_t const actionTable, 
                        uint16_t actionTableSize,
                        STATE_event_t ev,
                        STATE_state_t* state);




#ifdef TOGETHER
/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/

private:
    
};
#endif /* Together */

#endif /* STATEMACHINE_H */
