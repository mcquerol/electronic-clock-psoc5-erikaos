
/*
 * Filename: sc_clock_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#ifndef _H_DEFINE_SC_CLOCK_TYPE
#define _H_DEFINE_SC_CLOCK_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_CLOCK_INCLUDES */
#include "statemachine.h" 
/* USER CODE END SC_CLOCK_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_CLOCK signal    
 **********************************************************************/

/* USER CODE START SC_CLOCK_USERDEFINITIONS */
typedef struct
{
   CLOCK_state_t    m_state;
   STATE_stateOuterTransitionTable_t*   m_transitions;
   STATE_stateOuterAction_t*    m_stateActions;
   uint8_t     m_value;
   CLOCK_font_t     m_font; 
    
} CLOCK_widget_t;

typedef struct
{
  CLOCK_state_t;    m_containerState;
  STATE_stateOuterTransitionTable_t*   m_transitions;
  STATE_stateOuterAction_t*    m_stateActions;
  CLOCK_active_widget_t     m_activeWidget;
  CLOCK_widget_t    m_hours;
  CLOCK_widget_t    m_minutes;
    
    
} CLOCK_data_t;
/* USER CODE END SC_CLOCK_USERDEFINITIONS */

typedef 
/* USER CODE START SC_CLOCK_SIGNALDATADEFINITION */
struct
{
	CLOCK_data_t m_clock;
} 
/* USER CODE END SC_CLOCK_SIGNALDATADEFINITION */
SC_CLOCK_data_t;

/* USER CODE START InitSC_CLOCK */

#define SC_CLOCK_INIT_DATA ((SC_CLOCK_data_t){})
/* USER CODE END InitSC_CLOCK */


/**
 * Default IN driver API
 * \param SC_CLOCK_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_CLOCK_driverIn(SC_CLOCK_data_t *const data);



/**
 * Default OUT driver API
 * \param const SC_CLOCK_data_t  *const data : [IN] signal data for the driver, will be scaled in this function
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_CLOCK_driverOut(const SC_CLOCK_data_t  *const data);


/* USER CODE START SC_CLOCK_USERFUNCTIONS */

/* USER CODE END SC_CLOCK_USERFUNCTIONS */


#endif