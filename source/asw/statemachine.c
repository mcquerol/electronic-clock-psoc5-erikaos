/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
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
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "statemachine.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

#define INVALIDINDEX -1

/** return the index of the provided state in the given table 
 **/
sint16_t STATE__getIndexCurrentState(STATE_stateOuterTransitionTable_t const  transitionTable,
                        uint16_t transitionTableSize,
                        STATE_state_t state)
{
    
    sint16_t result = INVALIDINDEX; //error
    
    for (uint16_t i = 0; i < transitionTableSize; i++)
    {
        if (transitionTable[i].fromState == state)
        {
            return i;
        }
    }
    
    return INVALIDINDEX;
}

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
                        STATE_state_t* state)
{
    
    STATE_ActionPtr_t acEntry = 0;
    
    *state = STATE_INITIALSTATE;
    
    //Check if entry actios are present in the init state
    if (0 != actionTable)
    {
        for (uint16_t j = 0; j < actionTableSize; j++)
        {

            if (STATE_INITIALSTATE == actionTable[j].state)
            {
                acEntry = actionTable[j].actionEntry;
                if (0 != acEntry) acEntry();
            }
        }
    }
    
}

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
RC_t STATE_processEvent(STATE_stateOuterTransitionTable_t const  transitionTable,
                        uint16_t transitionTableSize,
                        STATE_stateActionTable_t const actionTable, 
                        uint16_t actionTableSize,
                        STATE_event_t ev,
                        STATE_state_t* state)
{
    STATE_GuardPtr_t guard = 0;
    STATE_ActionPtr_t acTransition = 0;
    STATE_ActionPtr_t acEntry = 0;
    STATE_ActionPtr_t acExit = 0;
    
    
    //Read the state from the watchdog object;
    STATE_state_t currentState = *state;
    STATE_state_t toState = currentState; //Just in case
    
    //Calculate the table index of the outer table

    sint16_t index = STATE__getIndexCurrentState(transitionTable, transitionTableSize, currentState);
    
    //This should never happen
    if (INVALIDINDEX == index)
    {
        return RC_ERROR_BAD_PARAM;
    }
    
    STATE_stateInnerTransitionTable_t const* const pInnerTable = transitionTable[index].pInnerTransitionTable;
	
    uint16_t innerTableSize = 0;
	if (0 != pInnerTable)
	{
		innerTableSize = transitionTable[index].size;
	}
    
    if (0 == pInnerTable || 0 == innerTableSize)
    {
        //No transitions in this state
        return RC_ERROR_INVALID_STATE;
    }
    
    //Iterate through the inner table and find correct transition
    for (uint16_t i = 0; i < innerTableSize; i++)
    {
        if ((*pInnerTable)[i].event == ev)
        {
            //Transition found, let's check the guard
            guard = (*pInnerTable)[i].guard;
            if (0 == guard || TRUE == guard())
            {
                //Transition is valid
                acTransition = (*pInnerTable)[i].actionTransition;
                toState = (*pInnerTable)[i].toState;
                
                //Now lets find exit actions. Note: their might be more than one
                if (0 != actionTable)
                {
                    for (uint16_t j = 0; j < actionTableSize; j++)
                    {
                        if (currentState == actionTable[j].state)
                        {
                            acExit = actionTable[j].actionExit;
                            if (0 != acExit) acExit();
                        }
                    }
                }

                //Lets call the transition action
                if (0 != acTransition) acTransition();
                
                //Now lets find the entry actions. Note: their might be more than one
                if (0 != actionTable)
                {
                    for (uint16_t j = 0; j < actionTableSize; j++)
                    {

                        if (toState == actionTable[j].state)
                        {
                            acEntry = actionTable[j].actionEntry;
                            if (0 != acEntry) acEntry();
                        }
                    }
                }
                
                *state = toState;
                
                //Only one transition will be fired
                break;
            }
        }
    }
    

    
 
    return RC_SUCCESS;
}
