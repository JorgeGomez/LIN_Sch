/*============================================================================*/
/*                        			 AEP 	                                  */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*
 * $Source: LINflex.c 
 * $Revision: 1.0 
 * Authors: Jorge Gomez. 
 * $Date: December 02, 2015 
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/* LINFLEX Initialization, configuration and ISR.    
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
/*   1.0    | 02/12/2015 | Added LIN initialization function | Jorge Gomez    */
/*          |            | and basic functionality           |                */
/*============================================================================*/

/* Includes */
/*============================================================================*/
#include "HAL\LINflex.h"
#include "HAL\IntcInterrupts.h"
/*============================================================================*/

/* Constants and types  */
/*============================================================================*/
/*============================================================================*/

/* Variables */
/*============================================================================*/

T_UBYTE		rub_Rx_ID = 0;			/*Variable for Received ID      */
T_CMDTYPE	re_SlvCmd = cmd_NONE;	/*Variable for Received Command */
T_UBYTE 	rub_status_lin = 0;

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
 *  Name                 :  Rx_ISR
 *  Description          :  Check LINFlex Rx flag and Transfer Data
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  And Rx interrupt must occur.
 *  Postcondition        :  Get the data on the buffer.
 **************************************************************/
PRIVATE_FCT void init_Slave_mode(void) 
{
	/*----------------------------------------------------------------------------------*/
	/*								Start Configuration									*/
	/*----------------------------------------------------------------------------------*/
	LINFLEX_0.LINCR1.B.INIT  = 1;     /* Put LINFlex hardware in initialization mode     */    
	while(LINFLEX_0.LINSR.B.LINS != 1)
	{
		/*Wait for INIT state*/
	} 
	
	/*----------------------------------------------------------------------------------*/
	/*								Slave Configuration 								*/
	/*----------------------------------------------------------------------------------*/
	
	LINFLEX_0.UARTCR.B.UART = 0;	  /* UART working on LIN mode                       */
	LINFLEX_0.LINCR1.B.MBL   = 0x03;  /* LIN Master Break Length: 13 bits               */ 
	LINFLEX_0.LINCR1.B.BF    = 1;     /* Bypass Filter: Enabled                         */ 
	LINFLEX_0.LINCR1.B.MME   = 0;     /* Master Mode Enable: Slave                      */    
	LINFLEX_0.LINCR1.B.SBDT  = 0;     /* Slave Mode Break Detection Threshold:  11 bits */
	LINFLEX_0.LINCR1.B.RBLM  = 0;     /* Receive Buffer: Not Locked on overrun          */
	LINFLEX_0.LINCR1.B.CCD   = 0;     /* Checksum Calculation is done by hardware.      */
	LINFLEX_0.LINCR1.B.CFD   = 0;     /* Checksum field: Enabled                        */ 
	LINFLEX_0.LINCR1.B.LASE  = 1;     /* LIN Slave Automatic Resynchronization: disabled*/
	
	/*----------------------------------------------------------------------------------*/
	/*								Error Detection Configuration						*/
	/*----------------------------------------------------------------------------------*/
	
	LINFLEX_0.LINCR2.B.IOBE = 1; /*Idle on bit error: Disabled, Bit error does not reset state machine*/
	
	/*----------------------------------------------------------------------------------*/
	/*								Interrupt Configuration								*/
	/*----------------------------------------------------------------------------------*/
	
	LINFLEX_0.LINIER.B.DTIE  = 1;  /*Interruption generated when data transmitted flag (DTF) is set in LINSR or UARTSR.                      */
	LINFLEX_0.LINIER.B.HRIE  = 1;  /*Interrupt generated when a valid LIN header has been received, that is, HRF bit in LINSR is set.        */
	LINFLEX_0.LINIER.B.DRIE  = 1;  /*Interruption generated when data received flag (DRF) in LINSR or UARTSR is set.                         */
	
}


/**************************************************************
 *  Name                 :  Rx_ISR
 *  Description          :  Check LINFlex Rx flag and Transfer Data
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  And Rx interrupt must occur.
 *  Postcondition        :  Get the data on the buffer.
 **************************************************************/
PRIVATE_FCT void Set_baudrate(void)
{
	/* LFDIV = Mantissa + (Fractional/16)
	 * Tx/Rx_baud = (fperiph_set_1_clk /(16 × LFDIV)  with 0.01% Error  */

	LINFLEX_0.LINIBRR.R = 208;/* Mantissa 	= 208*/
	LINFLEX_0.LINFBRR.R = 5;  /* Fractional = 5 */
	
	/* LFDIV = 208 + (5/16) = 208.3125
	 * Tx/Rx_baud = (64000000 /(16 × 208.3125) = 19201.9 with 0.01% Error  */
}


/**************************************************************
 *  Name                 :  Rx_ISR
 *  Description          :  Check LINFlex Rx flag and Transfer Data
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  And Rx interrupt must occur.
 *  Postcondition        :  Get the data on the buffer.
 **************************************************************/
PRIVATE_FCT void init_LINflex_filter_submode(void)
{
	LINFLEX_0.IFER.R = 0x0003;  /*Activate filters 0 to 3 */
	LINFLEX_0.IFMR.R = 0x0000;  /*Filters in list mode */
}	


/**************************************************************
 *  Name                 :  Rx_ISR
 *  Description          :  Check LINFlex Rx flag and Transfer Data
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  And Rx interrupt must occur.
 *  Postcondition        :  Get the data on the buffer.
 **************************************************************/
PRIVATE_FCT void init_ID_list(void)
{
	/*--------------------------------------------------------*/
	/*Configure the filters*/		/*| Name:			|	Dir	|	Len	|	ID	|	Chksum	 |*/
									/*|-----------------|-------|-------|-------|------------|*/
	LINFLEX_0.IFCR[0].R = 0x010F; 	/*| MASTER_CMD_ALL,	|	RX,	|	1,	|	CF,	|	Enhanced |*/
	LINFLEX_0.IFCR[1].R = 0x0413; 	/*| MASTER_CMD_SLV4,|	RX,	|	1,	|	D3,	|	Enhanced |*/
	LINFLEX_0.IFCR[2].R = 0x0A23;	/*| SLAVE4_RSP,		|	TX,	|	2,	|	A3,	|	Enhanced |*/
	LINFLEX_0.IFCR[3].R = 0x1E09;	/*| SLAVE4_ID,		|	TX,	|	7,	|	73,	|	Enhanced |*/
									/*--------------------------------------------------------*/
}


/**************************************************************
 *  Name                 :  Rx_ISR
 *  Description          :  Check LINFlex Rx flag and Transfer Data
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  And Rx interrupt must occur.
 *  Postcondition        :  Get the data on the buffer.
 **************************************************************/
PRIVATE_FCT void init_LIN_handlers(void)
{
	/*----------------------------------------------------------------------------------*/
	/*								Start the normal mode								*/
	/*----------------------------------------------------------------------------------*/
	LINFLEX_0.LINCR1.B.INIT = 0; 	/*Change LINflex to operational mode*/
	while(LINFLEX_0.LINSR.B.LINS != 2)
	{
		/*Wait for IDLE state*/
	}
	
	INTC_InstallINTCInterruptHandler(Rx_ISR, 79, 2);
	INTC_InstallINTCInterruptHandler(Tx_ISR, 80, 3);
	//INTC_InstallINTCInterruptHandler(Error_ISR, 81, 4);
	INTC.CPR.R = 0x0;
}


/* Exported functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  init_LINflex_Slv
 *  Description          :  Init the Linflex
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The correct initialization of the startup code.
 *  Postcondition        :  The LINflex module is enable to work with the ID’s for slave 4.
 **************************************************************/
void init_LINflex_Slv(void)
{
	init_Slave_mode();
	Set_baudrate();
	init_LINflex_filter_submode();
	init_ID_list();
	init_LIN_handlers();
}

/**************************************************************
 *  Name                 :  Rx_ISR
 *  Description          :  Check LINFlex Rx flag and Transfer Data
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  And Rx interrupt must occur.
 *  Postcondition        :  Get the data on the buffer.
 **************************************************************/
void Rx_ISR(void)
{
	LIN_Slv_StateMachine(RX_INTERRUPT);
	
	while (1 != LINFLEX_0.LINSR.B.RMB) {}  		/* Wait for Release Message Buffer to get the ID*/
	
	LIN_Slv_StateMachine(RX_INTERRUPT);
	
	rub_RxID = 0;
	
	LINFLEX_0.LINSR.B.DRF = 1;
	LINFLEX_0.LINSR.B.HRF = 1;
	LINFLEX_0.LINSR.B.RMB = 1;
}


/**************************************************************
 *  Name                 :  Tx_ISR
 *  Description          :  Check LINFlex Tx flag and Transfer Data
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  And Tx interrupt must occur.
 *  Postcondition        :  Put the data on the buffer.
 **************************************************************/
void Tx_ISR(void)
{
	//LINFLEX_0.BIDR.B.DIR = 0; /* BDR direction - write */
	LIN_Slv_StateMachine(RX_INTERRUPT);
	
	LIN_Slv_StateMachine(RX_INTERRUPT);
	
	LINFLEX_0.LINCR2.B.DTRQ = 1;
	LINFLEX_0.LINSR.B.HRF = 1;
	LINFLEX_0.LINSR.B.DTF = 1;
	

}


/**************************************************************
 *  Name                 :  Error_ISR
 *  Description          :  Interrupt function when error flag is detected
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  And Tx interrupt must occur.
 *  Postcondition        :  Get the data on the buffer.
 **************************************************************/
void Error_ISR(void)
{
	LINFLEX_0.LINESR.B.BEF = 1; /* Clearing Bit Error Flag */
}

/*============================================================================*/

/* Notice: the file ends with a blank new line to avoid compiler warnings */

