/*******************************************************************************
* File Name: JS_Y.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_JS_Y_H) /* Pins JS_Y_H */
#define CY_PINS_JS_Y_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "JS_Y_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 JS_Y__PORT == 15 && ((JS_Y__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    JS_Y_Write(uint8 value);
void    JS_Y_SetDriveMode(uint8 mode);
uint8   JS_Y_ReadDataReg(void);
uint8   JS_Y_Read(void);
void    JS_Y_SetInterruptMode(uint16 position, uint16 mode);
uint8   JS_Y_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the JS_Y_SetDriveMode() function.
     *  @{
     */
        #define JS_Y_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define JS_Y_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define JS_Y_DM_RES_UP          PIN_DM_RES_UP
        #define JS_Y_DM_RES_DWN         PIN_DM_RES_DWN
        #define JS_Y_DM_OD_LO           PIN_DM_OD_LO
        #define JS_Y_DM_OD_HI           PIN_DM_OD_HI
        #define JS_Y_DM_STRONG          PIN_DM_STRONG
        #define JS_Y_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define JS_Y_MASK               JS_Y__MASK
#define JS_Y_SHIFT              JS_Y__SHIFT
#define JS_Y_WIDTH              1u

/* Interrupt constants */
#if defined(JS_Y__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in JS_Y_SetInterruptMode() function.
     *  @{
     */
        #define JS_Y_INTR_NONE      (uint16)(0x0000u)
        #define JS_Y_INTR_RISING    (uint16)(0x0001u)
        #define JS_Y_INTR_FALLING   (uint16)(0x0002u)
        #define JS_Y_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define JS_Y_INTR_MASK      (0x01u) 
#endif /* (JS_Y__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define JS_Y_PS                     (* (reg8 *) JS_Y__PS)
/* Data Register */
#define JS_Y_DR                     (* (reg8 *) JS_Y__DR)
/* Port Number */
#define JS_Y_PRT_NUM                (* (reg8 *) JS_Y__PRT) 
/* Connect to Analog Globals */                                                  
#define JS_Y_AG                     (* (reg8 *) JS_Y__AG)                       
/* Analog MUX bux enable */
#define JS_Y_AMUX                   (* (reg8 *) JS_Y__AMUX) 
/* Bidirectional Enable */                                                        
#define JS_Y_BIE                    (* (reg8 *) JS_Y__BIE)
/* Bit-mask for Aliased Register Access */
#define JS_Y_BIT_MASK               (* (reg8 *) JS_Y__BIT_MASK)
/* Bypass Enable */
#define JS_Y_BYP                    (* (reg8 *) JS_Y__BYP)
/* Port wide control signals */                                                   
#define JS_Y_CTL                    (* (reg8 *) JS_Y__CTL)
/* Drive Modes */
#define JS_Y_DM0                    (* (reg8 *) JS_Y__DM0) 
#define JS_Y_DM1                    (* (reg8 *) JS_Y__DM1)
#define JS_Y_DM2                    (* (reg8 *) JS_Y__DM2) 
/* Input Buffer Disable Override */
#define JS_Y_INP_DIS                (* (reg8 *) JS_Y__INP_DIS)
/* LCD Common or Segment Drive */
#define JS_Y_LCD_COM_SEG            (* (reg8 *) JS_Y__LCD_COM_SEG)
/* Enable Segment LCD */
#define JS_Y_LCD_EN                 (* (reg8 *) JS_Y__LCD_EN)
/* Slew Rate Control */
#define JS_Y_SLW                    (* (reg8 *) JS_Y__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define JS_Y_PRTDSI__CAPS_SEL       (* (reg8 *) JS_Y__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define JS_Y_PRTDSI__DBL_SYNC_IN    (* (reg8 *) JS_Y__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define JS_Y_PRTDSI__OE_SEL0        (* (reg8 *) JS_Y__PRTDSI__OE_SEL0) 
#define JS_Y_PRTDSI__OE_SEL1        (* (reg8 *) JS_Y__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define JS_Y_PRTDSI__OUT_SEL0       (* (reg8 *) JS_Y__PRTDSI__OUT_SEL0) 
#define JS_Y_PRTDSI__OUT_SEL1       (* (reg8 *) JS_Y__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define JS_Y_PRTDSI__SYNC_OUT       (* (reg8 *) JS_Y__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(JS_Y__SIO_CFG)
    #define JS_Y_SIO_HYST_EN        (* (reg8 *) JS_Y__SIO_HYST_EN)
    #define JS_Y_SIO_REG_HIFREQ     (* (reg8 *) JS_Y__SIO_REG_HIFREQ)
    #define JS_Y_SIO_CFG            (* (reg8 *) JS_Y__SIO_CFG)
    #define JS_Y_SIO_DIFF           (* (reg8 *) JS_Y__SIO_DIFF)
#endif /* (JS_Y__SIO_CFG) */

/* Interrupt Registers */
#if defined(JS_Y__INTSTAT)
    #define JS_Y_INTSTAT            (* (reg8 *) JS_Y__INTSTAT)
    #define JS_Y_SNAP               (* (reg8 *) JS_Y__SNAP)
    
	#define JS_Y_0_INTTYPE_REG 		(* (reg8 *) JS_Y__0__INTTYPE)
#endif /* (JS_Y__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_JS_Y_H */


/* [] END OF FILE */
