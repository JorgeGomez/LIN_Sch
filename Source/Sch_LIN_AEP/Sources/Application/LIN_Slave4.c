/*============================================================================*/
/*                        			 AEP 	                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*
 * $Source: LIN_Slave4.c 
 * $Revision: 1.0 
 * Authors: Jorge Gomez. 
 * $Date: December 03, 2015 
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/* LINFLEX State machine.    
*/
/*============================================================================*/
/* COPYRIGHT (C) CONTINENTAL AUTOMOTIVE 2014                                  */
/* AUTOMOTIVE GROUP, Interior Division, Body and Security                     */
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
/*   1.0    | 03/12/2015 | 	Added the state machine	 		 | Jorge Gomez    */
/*============================================================================*/

/* Includes */
/*============================================================================*/
#include "Application/LIN_Slave4.h"

/*============================================================================*/

/* Constants and types  */
/*============================================================================*/
const T_SCALAR cub_TeamNumber = 8;
const T_ARRAY caub_Names = {'J', 'G', 'G', 'J', 'M', 'V'};


/*============================================================================*/

/* Variables */
/*============================================================================*/
E_LIN_STATES re_SlvState = IDLE;


/*============================================================================*/

/* Private functions prototypes */
/*============================================================================*/
/*============================================================================*/

/* Inline functions */
/*============================================================================*/
/*============================================================================*/

/* Private functions */
/*============================================================================*/
/*============================================================================*/

/**************************************************************
 *  Name                 :  LIN_Slv_StateMachine
 *  Description          :  State machine for the actualization of the parameters of the slave 4
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  An interrupt must occur.
 *  Postcondition        :  Acquires the data of LIN.
 **************************************************************/
void LIN_Slv_StateMachine(E_INTERRUPT_EVNT le_event) 
{
	switch(re_SlvState)
	{
		case IDLE:
				if(le_event == RX_INTERRUPT)
				{
					rub_RxID = GETBYTE_ID;
					re_SlvState = RX_ID;
				}
				else if(le_event == TX_INTERRUPT)
				{
					rub_RxID = GETBYTE_ID;
					re_SlvState = TX_ID;
				}
				else
				{
					re_SlvState = IDLE; 		/*Guard condition*/
				}
			break;
			
		case RX_ID:
				if((rub_RxID == MASTER_CMD_ALL) || (rub_RxID == MASTER_CMD_SLV4))
				{
					re_SlvCmd = GETBYTE_DATA0;
					re_SlvState = IDLE; 
				}
				else
				{
					re_SlvState = IDLE; 		/*Guard condition*/
					RESTART_LIN_STMCH;
				}
			break;
			
		case TX_ID:
				if(rub_RxID == SLAVE4_RSP)
				{
					PUTBYTE_DATA0 = re_LEDStatus;
					PUTBYTE_DATA1 = re_SlaveStatus;
					re_SlvState = IDLE; 
				}
				else if(rub_RxID == SLAVE4_ID)
				{
					PUTBYTE_DATA0 = cub_TeamNumber;
					PUTBYTE_DATA1 = caub_Names.e[0];
					PUTBYTE_DATA2 = caub_Names.e[1];
					PUTBYTE_DATA3 = caub_Names.e[2];
					PUTBYTE_DATA4 = caub_Names.e[4];
					PUTBYTE_DATA5 = caub_Names.e[5];
					re_SlvState = IDLE; 
				}
				else
				{
					re_SlvState = IDLE;		/*Guard condition*/
					RESTART_LIN_STMCH;
				}
			break;
			
		default:
			re_SlvState = IDLE;			/*Guard condition*/
			break;
	}
}


/* Exported functions */
/*============================================================================*/


/*============================================================================*/

/* Notice: the file ends with a blank new line to avoid compiler warnings */
