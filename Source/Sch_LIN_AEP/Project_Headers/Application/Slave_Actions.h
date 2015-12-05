/*============================================================================*/
/*                                  AEP		                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Slave_Actions.h $
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
/*					   |					|  Project_Headers/Application    */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: filename.h  $
  ============================================================================*/
#ifndef SLAVE_ACTIONS_H_
#define SLAVE_ACTIONS_H_

/* Includes */
/*============================================================================*/
#include "HAL/stdtypedef.h"
#include "HAL/MainConfig.h"
#include "HAL/LINflex.h"
#include "Signaltypes.h"

/* Constants and types */
/*============================================================================*/


/* Exported Variables */
/*============================================================================*/
PUBLIC_DATA T_SLV_STAT re_SlaveStatus;
PUBLIC_DATA T_LEDSTAT re_LEDStatus;

/* Exported functions prototypes */
/*============================================================================*/
 PUBLIC_FCT void Slave_Actions (void);
 


#endif /* Notice: the file ends with a blank new line to avoid compiler warnings */
