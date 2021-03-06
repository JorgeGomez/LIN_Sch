/*============================================================================*/
/*                       			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Slave_Actions.c $
 * $Revision: version 1.0$
 * $Author: Jose Luis Martinez $
 * $Date: 03/12/2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
    short description in one sentence end with dot.
    detailed
    multiline
    description of the file
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
/*============================================================================*/
/*                    REUSE HISTORY - taken over from                         */
/*============================================================================*/
/*  DATABASE           |        PROJECT     | FILE VERSION (AND INSTANCE)     */
/*----------------------------------------------------------------------------*/
/*                     |LIN network Slave 4 |            1.0                  */
/*					   |					|       Source/Application        */
/*----------------------------------------------------------------------------*/
/*                     |Added comments 		|            1.1                  */
/*					   |					|       Source/Application        */
/*----------------------------------------------------------------------------*/
/*                     |Added condition to  |            1.2                  */
/*					   |keep toggling		|       Source/Application        */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: Slave_Actions.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "Application/Slave_Actions.h"


/* Constants and types  */
/*============================================================================*/



/* Variables */
/*============================================================================*/
T_SLV_STAT re_SlaveStatus = ENABLED;
T_LEDSTAT re_LEDStatus = L_ON;


/* Private functions prototypes */
/*============================================================================*/
PRIVATE_FCT void LED_StateMachine(T_CMDTYPE le_slvcmd);


/* Inline functions */
/*============================================================================*/




/* Private functions */
/*============================================================================*/
/**************************************************************
*  Name                 :  Slave_Actions
*  Description          :  Change the Status of the slave and the LED called every 50ms
*  Parameters           :  void
*  Return               :  void
*  Precondition         :  The periodic task is called
*  Postcondition        :  The slave change its status
*  Req. 				:  7.3 and 7.7 to 7.9
*  SW design			:  5.6
**************************************************************/
void Slave_Actions(void)
{
	if(re_SlvCmd != cmd_NONE)
	{
		if(re_SlaveStatus == ENABLED)
		{
			if (re_SlvCmd == cmd_disable_slv)
			{
				re_SlaveStatus = DISABLED;
			}
			else
			{
				LED_StateMachine(re_SlvCmd);
			}
		}
		else if(re_SlaveStatus == DISABLED)
		{
			if(re_SlvCmd == cmd_enable_slv)
			{
				re_SlaveStatus = ENABLED;
			}
			else 
			{
				LED_StateMachine(cmd_NONE);
			}
			
		}
		else{}
	}
	else{}

}

/**************************************************************
*  Name                 :  LED_StateMachine
*  Description          :  State machine of the behavior of the LED, executed every 50ms
*  Parameters           :  T_CMDTYPE
*  Return               :  void
*  Precondition         :  The periodic task is called
*  Postcondition        :  Switch the status of the LED
*  Req.					:  7.4 to 7.6 and 7.10 to 7.12
*  SW design			:  5.7
**************************************************************/
PRIVATE_FCT void LED_StateMachine(T_CMDTYPE le_slvcmd)
{
	switch(re_LEDStatus)
	{
		case L_OFF:
				led_off(LED_1);
				re_LEDStatus = L_OFF;

				if(le_slvcmd == cmd_LED_toggling)
				{
					led_toggle(LED_1);
					re_LEDStatus = TOGGLING;
				}
				else if(le_slvcmd == cmd_LED_on)
				{
					led_on(LED_1);
					re_LEDStatus = L_ON;
				}
				else{/*Do nothing*/}
			break;
			
		case TOGGLING:
				led_toggle(LED_1);
				re_LEDStatus = TOGGLING;
				if(le_slvcmd == cmd_LED_off)
				{
					led_off(LED_1);
					re_LEDStatus = L_OFF;
				}
				else if(le_slvcmd == cmd_LED_on)
				{
					led_on(LED_1);
					re_LEDStatus = L_ON;
				}
				else{/*Do nothing*/}
			break;
			
		case L_ON:
				led_on(LED_1);
				re_LEDStatus = L_ON;	
				if(le_slvcmd == cmd_LED_off)
				{
					led_off(LED_1);
					re_LEDStatus = OFF;
				}
				else if(le_slvcmd == cmd_LED_toggling)
				{
					led_toggle(LED_1);
					re_LEDStatus = TOGGLING;
				}
				else{/*Do nothing*/}
			break;
			
		default:
				re_LEDStatus = L_ON;
			break;
	}
}

/* Exported functions */
/*============================================================================*/



/* Notice: the file ends with a blank new line to avoid compiler warnings */
