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
#define KINETIS 0
/*============================================================================*/

/* Variables */
/*============================================================================*/

T_UBYTE		rub_Rx_ID = 0;			/*Variable for Received ID      */
T_CMDTYPE	re_SlvCmd = cmd_NONE;	/*Variable for Received Command */
T_UBYTE 	rub_status_lin = 0;

/*============================================================================*/

/* Private functions prototypes */
/*============================================================================*/
PRIVATE_FCT void Rx_ISR(void);
PRIVATE_FCT void Tx_ISR(void);
PRIVATE_FCT void Error_ISR(void);
PRIVATE_FCT void init_Slave_mode(void);
PRIVATE_FCT void Set_baudrate(void);
PRIVATE_FCT void init_LINflex_filter_submode(void);
PRIVATE_FCT void init_ID_list(void);
PRIVATE_FCT void init_LIN_handlers(void);
/*============================================================================*/



/* Inline functions */
/*============================================================================*/
/*============================================================================*/

/* Private functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  init_Slave_mode
 *  Description          :  Starts the slave mode configuration
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The correct initialization of the startup code..
 *  Postcondition        :  Set on init mode the LINflex.
 **************************************************************/
PRIVATE_FCT void init_Slave_mode(void) 
{
	/*----------------------------------------------------------------------------------*/
	/*								Start Configuration									*/
	/*----------------------------------------------------------------------------------*/
	LINFLEX_0.LINCR1.B.SLEEP  = 0;
	LINFLEX_0.LINCR1.B.INIT  = 1;     /* Put LINFlex hardware in initialization mode     */    

	/*----------------------------------------------------------------------------------*/
	/*								Slave Configuration 								*/
	/*----------------------------------------------------------------------------------*/
	
	LINFLEX_0.UARTCR.B.UART = 0;	  /* UART working on LIN mode                       */
	LINFLEX_0.LINCR1.B.MBL   = 0x03;  /* LIN Master Break Length: 13 bits               */ 
	LINFLEX_0.LINCR1.B.BF    = 0;     /* Bypass Filter: Enabled                         */ 
	LINFLEX_0.LINCR1.B.MME   = 0;     /* Master Mode Enable: Slave                      */    
	LINFLEX_0.LINCR1.B.SBDT  = 0;     /* Slave Mode Break Detection Threshold:  11 bits */
	LINFLEX_0.LINCR1.B.RBLM  = 0;     /* Receive Buffer: Not Locked on overrun          */
	LINFLEX_0.LINCR1.B.CCD   = 0;     /* Checksum Calculation is done by hardware.      */
	LINFLEX_0.LINCR1.B.CFD   = 0;     /* Checksum field: Enabled                        */ 
	LINFLEX_0.LINCR1.B.LASE  = 1;     /* LIN Slave Automatic Resynchronization: enabled */
	
	/*----------------------------------------------------------------------------------*/
	/*								Error Detection Configuration						*/
	/*----------------------------------------------------------------------------------*/
	
	LINFLEX_0.LINCR2.B.IOBE = 0; /*Idle on bit error: Disabled, Bit error does not reset state machine*/
	LINFLEX_0.LINTCSR.B.IOT = 0;
	/*	
	 * LINFLEX_0.LINIER.B.CEIE = 1;	
	 * LINFLEX_0.LINIER.B.HEIE = 1;	
	 * LINFLEX_0.LINIER.B.BEIE = 0;	ERRors
	*/
	/*----------------------------------------------------------------------------------*/
	/*								Interrupt Configuration								*/
	/*----------------------------------------------------------------------------------*/
	
	LINFLEX_0.LINIER.B.DTIE  = 1;  /*Interruption generated when data transmitted flag (DTF) is set in LINSR or UARTSR.                      */
	LINFLEX_0.LINIER.B.HRIE  = 1;  /*Interrupt generated when a valid LIN header has been received, that is, HRF bit in LINSR is set.        */
	LINFLEX_0.LINIER.B.DRIE  = 1;  /*Interruption generated when data received flag (DRF) in LINSR or UARTSR is set.                         */
	
}


/**************************************************************
 *  Name                 :  Set_baudrate
 *  Description          :  Sets the baudrate
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The linflex must be on init mode.
 *  Postcondition        :  The baud rate is setted.
 *  Req					 :				
 **************************************************************/
PRIVATE_FCT void Set_baudrate(void)
{
	/* LFDIV = Mantissa + (Fractional/16)
	 * Tx/Rx_baud = (fperiph_set_1_clk /(16 × LFDIV)  */
	LINFLEX_0.LINIBRR.R = 416;	/* Mantissa   = 416           br= 9600*/ 
	LINFLEX_0.LINFBRR.R = 11;  	/* Fractional = 11 */

	/* LFDIV = 416 + (11/16) = 416.6875
	 * Tx/Rx_baud = (64000000 /(16 × 416.6875) = 9599.52 with 0.005% Error  */
}


/**************************************************************
 *  Name                 :  init_LINflex_filter_submode
 *  Description          :  Initializes the filter submode
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The linflex must be on init mode.
 *  Postcondition        :  Initialize the filter submode.
 **************************************************************/
PRIVATE_FCT void init_LINflex_filter_submode(void)
{
	LINFLEX_0.IFER.R = 0x0000;  /*Deactivates filters 0 to 3 */
	LINFLEX_0.IFMR.R = 0x0000;  /*Filters in list mode */
	LINFLEX_0.IFER.R = 0xF;	/*Activates filters 0 to 3 */
}	


/**************************************************************
 *  Name                 :  Rx_ISR
 *  Description          :  Initializes the filter list
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The linflex must be on init mode.
 *  Postcondition        :  Get the data on the buffer.
 **************************************************************/
PRIVATE_FCT void init_ID_list(void)
{
	/* ______________________________________________________ */
	/*| Name:			|	Dir	|	Len	|	ID	|	Chksum	 |*/
	/*|_________________|_______|_______|_______|____________|*/
	/*| MASTER_CMD_ALL,	|	RX,	|	1,	|	CF,	|	Enhanced |*/
	/*| MASTER_CMD_SLV4,|	RX,	|	1,	|	D3,	|	Enhanced |*/
	/*| SLAVE4_RSP,		|	TX,	|	2,	|	A3,	|	Enhanced |*/
	/*| SLAVE4_ID,		|	TX,	|	7,	|	73,	|	Enhanced |*/
	/*|_________________|_______|_______|_______|____________|*/
	/*Configure the filters*/
	
	/*SLAVE4_RSP*/
	LINFLEX_0.IFCR[0].B.ID = 0x23;
	LINFLEX_0.IFCR[0].B.DIR = 1;
#if(KINETIS)
	LINFLEX_0.IFCR[0].B.CCS = 0;
#endif
#if(KINETIS == 0)
	LINFLEX_0.IFCR[0].B.CCS = 1;
#endif
	LINFLEX_0.IFCR[0].B.DFL = 1;
	
	/*MASTER_CMD_ALL*/
	LINFLEX_0.IFCR[1].B.ID = 0x0F;
	LINFLEX_0.IFCR[1].B.DIR = 0;
#if(KINETIS)
	LINFLEX_0.IFCR[1].B.CCS = 0;
#endif
#if(KINETIS == 0)
	LINFLEX_0.IFCR[1].B.CCS = 1;
#endif
	LINFLEX_0.IFCR[1].B.DFL = 0;
	
	
	/*SLAVE4_ID*/
	LINFLEX_0.IFCR[2].B.ID = 0x33;
	LINFLEX_0.IFCR[2].B.DIR = 1;
#if(KINETIS)
	LINFLEX_0.IFCR[2].B.CCS = 0;
#endif
#if(KINETIS == 0)
	LINFLEX_0.IFCR[2].B.CCS = 1;
#endif
	LINFLEX_0.IFCR[2].B.DFL = 6;
	
	
	/*MASTER_CMD_SLV4*/
	LINFLEX_0.IFCR[3].B.ID = 0x13;
	LINFLEX_0.IFCR[3].B.DIR = 0;
#if(KINETIS)
	LINFLEX_0.IFCR[3].B.CCS = 0;
#endif
#if(KINETIS == 0)
	LINFLEX_0.IFCR[3].B.CCS = 1;
#endif
	LINFLEX_0.IFCR[3].B.DFL = 0;
	
}


/**************************************************************
 *  Name                 :  init_LIN_handlers
 *  Description          :  Init the interrupts
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The linflex must be on init mode.
 *  Postcondition        :  Get the data on the buffer.
 **************************************************************/
PRIVATE_FCT void init_LIN_handlers(void)
{
	/*----------------------------------------------------------------------------------*/
	/*								Start the normal mode								*/
	/*----------------------------------------------------------------------------------*/
	LINFLEX_0.LINCR1.B.INIT = 0; 	/*Change LINflex to operational mode*/

	INTC_InstallINTCInterruptHandler(&Rx_ISR, 79, 2);
	INTC_InstallINTCInterruptHandler(&Tx_ISR, 80, 3);
	//INTC_InstallINTCInterruptHandler(Error_ISR, 81, 4);
	INTC.CPR.R = 0x0;



}
/*============================================================================*/

/* Exported functions */
/*============================================================================*/

/**************************************************************
 *  Name                 :  init_LINflex_Slv
 *  Description          :  Init the Linflex in general
 *  Parameters           :  void
 *  Return               :  void
 *  Precondition         :  The correct initialization of the startup code.
 *  Postcondition        :  The LINflex module is enable to work with the ID’s for slave 4.
 *  SW design			 :	5.4
 *  Req. 				 :	4.0 to 4.15 and 7.13
 **************************************************************/
void init_LINflex_Slv(void)
{
	init_Slave_mode(); 				/*Initializes the lin flex in slave mode*/
	Set_baudrate();					/*Sets the Linflex baudrate*/
	init_LINflex_filter_submode();	/*Initializes the filter mode*/
	init_ID_list();					/*Initiliazes the ID list*/
	init_LIN_handlers();			/*Initializes the ISR handlers for Tx and Rx*/
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
	
	rub_Rx_ID = 0;
	
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
	
	rub_Rx_ID = GETBYTE_ID;
	if(LINFLEX_0.LINSR.B.HRF)
	{
		LINFLEX_0.BIDR.B.DIR = 1; /* BDR direction - write */

		LIN_Slv_StateMachine(TX_INTERRUPT);
		LIN_Slv_StateMachine(TX_INTERRUPT);

		LINFLEX_0.LINSR.B.HRF = 1;
	}
	else if(LINFLEX_0.LINSR.B.DTF)
	{
		LINFLEX_0.LINSR.B.DTF = 1;
	}
	rub_Rx_ID = 0;

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

