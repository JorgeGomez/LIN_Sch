/*============================================================================*/
/*                         			AEP 	                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*
 * Source: LIN_Slave4.h
 * Revision: 1.0
 * Authors: Jorge Gomez.
 * Date: December 03, 2015
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/* LIN state machine
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
/*   1.0    | 02/12/2015 | Added LIN State machine function  | Jorge Gomez    */
/*============================================================================*/
#ifndef LIN_SLAVE4_H_
#define LIN_SLAVE4_H_


/* Includes */
/*============================================================================*/
#include "HAL/MPC5606B.h"
#include "HAL/stdtypedef.h"
#include "HAL/LINflex.h"
#include "Application/Slave_Actions.h"

/*============================================================================*/

/* Constants and types */
/*============================================================================*/

typedef enum
{
	TX_INTERRUPT,
	RX_INTERRUPT
}E_INTERRUPT_EVNT;

typedef enum
{
	IDLE,
	TX_ID,
	RX_ID
}E_LIN_STATES;

#define MASTER_CMD_ALL 		0x0F   		/* ID: CF */ 
#define MASTER_CMD_SLV4 	0x13  		/* ID: D3 */
#define SLAVE4_RSP 			0x23       	/* ID: A3 */
#define SLAVE4_ID 			0x09        /* ID: 73 */

/*Get data bytes of the buffer*/
#define GETBYTE_ID			((T_UBYTE)(LINFLEX_0.BIDR.B.ID))
#define GETBYTE_DATA0		((T_UBYTE)(LINFLEX_0.BDRL.B.DATA0))

/*Put data bytes on the buffer*/
#define PUTBYTE_DATA0		(LINFLEX_0.BDRL.B.DATA0)
#define PUTBYTE_DATA1		(LINFLEX_0.BDRL.B.DATA1)
#define PUTBYTE_DATA2		(LINFLEX_0.BDRL.B.DATA2)
#define PUTBYTE_DATA3		(LINFLEX_0.BDRM.B.DATA4)
#define PUTBYTE_DATA4		(LINFLEX_0.BDRM.B.DATA5)
#define PUTBYTE_DATA5		(LINFLEX_0.BDRM.B.DATA6)
#define RESTART_LIN_STMCH	(LINFLEX_0.LINCR2.B.DDRQ = 1)
/*============================================================================*/

/* Exported Variables */
/*============================================================================*/
/*============================================================================*/


/* Exported functions prototypes */
/*============================================================================*/
PUBLIC_FCT void LIN_Slv_StateMachine(E_INTERRUPT_EVNT le_event);
/*============================================================================*/

#endif /* LIN_SLAVE4_H_ */
