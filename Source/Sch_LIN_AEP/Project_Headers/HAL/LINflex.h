/*============================================================================*/
/*                         			AEP 	                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*
 * Source: LINflex.h
 * Revision: 1.0
 * Authors: Jorge Gomez.
 * Date: December 02, 2015
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/* header - LINFLEX Initialization, configuration and ISR
*/
/*============================================================================*/
/* COPYRIGHT (C) CONTINENTAL AUTOMOTIVE 2014                                  */
/* AUTOMOTIVE GROUP, Automotive Entry Program                                 */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/* REVISION |   DATE     |          COMMENT                  |    AUTHOR      */
/*----------------------------------------------------------------------------*/
/*   1.0    | 02/12/2015 | Added LIN initialization function | Jorge Gomez    */
/*          |            | header 				             |                */
/*============================================================================*/
#ifndef LINFLEX_H_
#define LINFLEX_H_


/* Includes */
/*============================================================================*/
#include "HAL/MPC5606B.h"
#include "HAL/stdtypedef.h"
#include "Application/LIN_Slave4.h"

/*============================================================================*/

/* Constants and types */
/*============================================================================*/

typedef enum
{
	DISABLED,
	ENABLED
}T_SLV_STAT;

typedef enum
{
	cmd_NONE,
	cmd_LED_on,
	cmd_LED_off,
	cmd_LED_toggling,
	cmd_disable_slv,
	cmd_enable_slv
}T_CMDTYPE;

typedef enum
{
	OFF,
	ON,
	TOGGLING
}T_LEDSTAT;


typedef T_UBYTE T_SCALAR;

typedef struct{
	T_UBYTE e[6];
} T_ARRAY;

/*============================================================================*/

/* Exported Variables */
/*============================================================================*/
/*============================================================================*/
PUBLIC_DATA T_UBYTE		rub_RxID;			/*Variable for Received ID      */
PUBLIC_DATA T_CMDTYPE	re_SlvCmd;	/*Variable for Received Command */

/* Exported functions prototypes */
/*============================================================================*/
PUBLIC_FCT void init_LINflex_Slv(void);
PUBLIC_FCT void Rx_ISR(void);
PUBLIC_FCT void Tx_ISR(void);
PUBLIC_FCT void Error_ISR(void);
/*============================================================================*/

#endif /* LINFLEX_H_ */
