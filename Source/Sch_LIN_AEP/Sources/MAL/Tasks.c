/*============================================================================*/
/*                         			AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Tasks.c $
 * $Revision: 1.0 $
 * $Author: Jorge Gomez $
 * $Date: Nov/12/15 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \Tasks
    This file contain the tasks.
    Modify this file to add a new task.
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
/*   1.0 		|  	Nov/13/15		| 	  Added new tasks  	  |  Jorge Gomez  */
/*============================================================================*/
/*   1.1		|   Dic/03/15       |Unnecessary tasks were   |Jose Luis Mtz  */
/*  			|					|		removed			  |	 	          */
/*============================================================================*/
/*                      				 		                              */
/*============================================================================*/
/*
 * $Log: Tasks.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/

#include "MAL/Tasks.h"


/* Constants and types  */
/*============================================================================*/

/*
 * --------------------List of task for the scheduler-----------------------------
 * */
const S_TASK cas_TaskList[NUMBER_OF_TASKS] = 
{
	/*	Name					Execution Period(ticks)		Startup delay(ticks)	*/
	{	Task1_50ticks,					50, 						1	},
/*	{	Taskn,							Period, 				  offset}	Add if you need a new task*/
};


/* Variables */
/*============================================================================*/



/* Private functions prototypes */
/*============================================================================*/



/* Inline functions */
/*============================================================================*/




/* Private functions */
/*============================================================================*/

/*
 * --------Add a new definition if you need a new task--------------------------
 * */

 /**************************************************************
  *  Name                 :  Task1_50ticks
  *  Description          :  Init function of Scheduler module
  *  Parameters           :  void
  *  Return               :  void
  *  Precondition         :  This function must be called after cpu initialization.
  *  Postcondition        :  Function gsc_sch_core_exec can be called.
  **************************************************************/
void Task1_50ticks(void)
{
	Slave_Actions();
}

/* Exported functions */
/*============================================================================*/



 /* Notice: the file ends with a blank new line to avoid compiler warnings */
