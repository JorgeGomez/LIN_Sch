/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: BlinkingLedsApp.c $
 * $Revision: 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Nov/12/15 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \BlinkingLedsApp
    Provide the application for each task.
    Do the embedded LEDs blink.
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
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION 	|  		DATE  		|     COMMENT	     	  |		AUTHOR 	  */
/*----------------------------------------------------------------------------*/
/*   1.0 		|  	Nov/13/15		| 		added task		  |  Jorge Gomez  */
/*============================================================================*/
/*                      					 	                              */
/*============================================================================*/
/*
 * $Log: BlinkingLedsApp.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "Application/BlinkingLedsApp.h"


/* Constants and types  */
/*============================================================================*/



/* Variables */
/*============================================================================*/



/* Private functions prototypes */
/*============================================================================*/



/* Inline functions */
/*============================================================================*/




/* Private functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  toggle_led1
 *  Description          :  Function for the task number 1
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  This function must each 10 ticks.
 *  Postcondition        :  The LED 1 changes.
 **************************************************************/
void toggle_led1(void)
{
	led_toggle(LED_1);
}

/* Exported functions */
/*============================================================================*/



 /* Notice: the file ends with a blank new line to avoid compiler warnings */
