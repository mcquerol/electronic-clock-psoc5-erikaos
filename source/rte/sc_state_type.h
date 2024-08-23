
/*
 * Filename: sc_state_type.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 */

#ifndef _H_DEFINE_SC_STATE_TYPE
#define _H_DEFINE_SC_STATE_TYPE

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SC_STATE_INCLUDES */

/* USER CODE END SC_STATE_INCLUDES */



/**********************************************************************
 *       Type Definition for SC_STATE signal    
 **********************************************************************/

/* USER CODE START SC_STATE_USERDEFINITIONS */
typedef enum
{
    
    ISDISPLAYING,
    ISEDITINGMINUTES,
    ISEDITINGHOURS
    
}STATE_enum_t;
/* USER CODE END SC_STATE_USERDEFINITIONS */

typedef 
/* USER CODE START SC_STATE_SIGNALDATADEFINITION */
struct
{
	STATE_enum_t m_state;
} 
/* USER CODE END SC_STATE_SIGNALDATADEFINITION */
SC_STATE_data_t;

/* USER CODE START InitSC_STATE */
#define SC_STATE_INIT_DATA ((SC_STATE_data_t){ISDISPLAYING})
/* USER CODE END InitSC_STATE */


/**
 * Default IN driver API
 * \param SC_STATE_data_t *const data : [OUT] scaled data read from the driver
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_STATE_driverIn(SC_STATE_data_t *const data);



/**
 * Default OUT driver API
 * \param const SC_STATE_data_t  *const data : [IN] signal data for the driver, will be scaled in this function
 * \return RC_SUCCESS is all was ok, error code otherwise
 */
RC_t SC_STATE_driverOut(const SC_STATE_data_t  *const data);


/* USER CODE START SC_STATE_USERFUNCTIONS */

/* USER CODE END SC_STATE_USERFUNCTIONS */


#endif