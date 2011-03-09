/*-----------------------------------------------------------------------------+
|       Copyright (c), 3iP, 2007                                               |
|       File: FSM.c    Finite State Multi-SubMachines                          |
+--------------+-------+----------------------------------------------+--------+
|     DATE     |VERSION| HISTORY/CHANGES                              |   BY   |
|  (MM/DD/YY)  | VX.Y  |                                              |        |
+--------------+-------+----------------------------------------------+--------+
|   12/01/07   | 0.1.1 | Start of implementation.                     |   IB   |
|   15/05/07   | 0.1.2 | Redefinition of AI/DI/DO/AO                  |   IB   |
|    1/06/07   | 0.1.3 | New project structure                        |   IB   |
|    3/07/07   | 0.2.0 | Cuceglio home implementation/ only heating   |   IB   |
|    17/2/08   | 0.2.1 | Cuceglio home implementation/ only heating   |   IB   |
|    19/11/10  | 0.3.0 | Cuceglio home implementation/ only heating   |   IB   |
|              |       | simplified                                   |        |
|    19/11/10  | 0.3.1 | Cuceglio home implementation/ only heating   |   IB   |
|              |       | more simplified                              |        |
|    19/11/10  | 0.4.0 | Cuceglio home implementation/ only heating   |   IB   |
|              |       | simplified  + Serial communication           |        |
|    19/11/10  | 0.4.1 | tolto accesso diretto PLCOPI e PLCRTCHOur e  |   IB   |
|              |       | ripristinato vettore DI esterno statico.     |        |
|              |       | Risolto b2.                                  |        |
|     4/1/11   | 0.5.0 | tolto utilizzo Modbus per debug.             |   IB   |
|              |       | Risolto b1                                   |        |
|     6/2/11   | 0.6.0 | Aggiunto termostato T2, cam Paolo            |   IB   |
|              |       | Aggiunto comando S - Stato totale            |        |
|     25/2/11  | 0.6.1 | Aggiunto termostato T3, soggiorno            |   IB   |
|              |       | ottimizz.switch/case controllo T0/1/2/3      |        | 
|              |       | Aggiunto comando S - Stato totale            |        |
|  26/2/11 wip | 0.7.0 | Aggiunto Misura tempo di accensione          |   IB   |
|              |       | Aggiunta comando leggi tempo di accensione   |        |
|              |       | Ottimizzazione dimensione codice oggetto     |        |
|  27/2/11 wip | 0.7.1 | Aggiunta statistiche giornaliere per un anno |   IB   |
|              |       | Risolto b3                                   |        |
+--------------+-------+----------------------------------------------+-------*/

//buglist
// 0.4.0: b1 non sempre risponde ai comandi via seriali, alcune volte bisogna ripeterli 3-4 volte prima di avere risposta. Risolto in 0.5.0
// 0.4.0: b2 non parte mai la caldaia !!! Risolto in 0.4.1
// 0.7.0: b3 errore calcolo minuti al cambio giorno
// 0.7.0: b4 manca possibilita' di settare il giorno del rtc

// -----------------------------------------------------------------------------
// FILE INCLUSIONS
// -----------------------------------------------------------------------------
#include <stdio.h>
#include <ElSystemLib.h>
#include <ElPLCLib.h>

#define TERMOSTATOP1CORR 0
#define TERMOSTATOP0 1
#define TERMOSTATOP1PAOLO 2
#define TERMOSTATOP1GIORNO 3

#define HEATER_ON 0
#define ZONA1N 4
#define ZONA1G 5
#define ZONA1B 6
#define ZONAP0 7

/** Logic boolean value  */
/* False is 0, not zero is true                      */
//typedef char Logic;

#ifndef TRUE
  #define TRUE 1
#endif

#ifndef FALSE
  #define FALSE 0
#endif

#define MAXDI 16
#define MAXDO 8

// -----------------------------------------------------------------------------
// debug mode and variable declarations
// -----------------------------------------------------------------------------
//#define DBG_LEVEL
#ifdef DBG_LEVEL
    char dbg1;
    char dbg2;
#endif

// -----------------------------------------------------------------------------
// global variable declarations
// -----------------------------------------------------------------------------

BOOL DI[MAXDI]={
0, // TERMOSTATOP1CORR 0
0, // TERMOSTATOP0 1
0, // TERMOSTATOP1PAOLO2  stanza paolo
0, //TEMOSTATOP1GIORNO
0,0,0,0,0,0,0,0,0,0,0,0 };

BOOL DO[MAXDO]={
0, //HEATER_ON 0
0,0,0,
0, // ZONA1N 4
0, // ZONA1G 5
0, // ZONA1B 6
0 // ZONAP0 7
};

static int nextaction=0;
int openvalves=0;
//int antiicing;
RTCDATA RtcData; //Rtc data structure

// @Section("Custom Function - 0.7.0")  Misura tempo di accensione
RTCDATA RtcPLCSTARTTime,RtcONTime, RtcTimeNow; //Rtc data structure
unsigned int PreviousStatus, TotMinutiON, TotOreON;
// @Section("Custom Function - 0.7.1")  statistiche
unsigned int StatMinutiON[12][31];

// -----------------------------------------------------------------------------
// HEATING ZONES CONFIGURATION
// -----------------------------------------------------------------------------


// B=bathroom
// X = all off
// N= zona notte + corridoi + bagni
// G= zona giorno + corridoi + bagni
// A= All ON

char comfortP0[24]={
'A','A','A','A','A','A',
'A','A','A','A','A','A',
'A','A','A','A','A','A',
'A','A','A','A','A','A' }; 
 
char comfortP1[24]={
'X', // dalle 00:00 alle 00:59 -> tutto spento
'X','X','X','X','X',// dalle 1:00 alle 5:59 -> tutto spento 
'B', // dalle 6:00 alle 6:59 -> zona bagni
'A', // dalle 7:00 alle 7:59 -> tutto acceso 
'G','G','G','G','G', // dalle 8:00 alle 12:59 -> Bagni + Zona Giorno + Corridoi
'A','A', // tutto acceso dalle 13:00 alle 14:59
'G','G','G','G','G', // dalle 15:00 alle 19:59 -> Bagni + Zona Giorno 
'A','A','A',// dalle 20:00 alle 22:59 -> tutto acceso
'N' }; // dalle 23:00 alle 23:59 -> zona notte+corridoi+bagni 


// function prototipes
//void   ManageHeatingInputs(void);
void   ManageHeatingOutputs(void);         
void ParseCOM(void);
char ExecuteCmd(unsigned char , unsigned char );
// -----------------------------------------------------------------------------
// CUSTOM FUNCTION
// -----------------------------------------------------------------------------

// @Section("Custom Function - C Entry point")
void CustomFunction(void)
{
SERIALSTRUCT SerialStruct; //Serial parameters
int i,j;

    if (PLCFirstLoop)
    {

 // Enable the serial communication on serial port "" and define parameters.
 // Set serial at 19200, e, 8. DTR automatically managed without any time
        SetTermIOVectors(IOSerialPortA); //Set the serial port A as I/O console
        GetSerialMode(&SerialStruct); //Get communication mode
        SerialStruct.Mode.DTRComplement=FALSE; //Complement the DTR signal
        SerialStruct.Mode.EchoFlush=FALSE; //Flush the echo
        SerialStruct.Mode.RxCtrlDisable=TRUE; //Disable Rx control characters
        SerialStruct.Mode.DTRManagement=2; //Define the DTR management
        SerialStruct.Mode.WaitLoop=FALSE; //FALSE:No wait, TRUE:Wait
        SerialStruct.Mode.ParityEnabled=TRUE; //Enables the parity management
        SerialStruct.Mode.ParityType=TRUE; //FALSE:Odd parity, TRUE:Even parity
        SerialStruct.Mode.BitNumber=TRUE; //FALSE:7 bit, TRUE:8 bit
        SerialStruct.Mode.WaitLoop=FALSE; //FALSE:No wait, TRUE:Wait
        SerialStruct.Mode.Baud=6; //Baud rate
        SerialStruct.DTROnTime=0; //DTR On wait time
        SerialStruct.DTROffTime=0; //DTR Off delay time
        SetSerialMode(&SerialStruct); //Set communication mode

        // @Section("Custom Function - 0.7.0")  misura tempo di accensione
        PreviousStatus = 0;
        TotMinutiON=TotOreON=0;
        GetRtc (&RtcPLCSTARTTime);
       // @Section("Custom Function - 0.7.1")  statistiche
        for (i=0;i<12;i++)
            for (j=0;j<31;j++)
                StatMinutiON[i][j]=0; 

#ifdef DBG_LEVEL
        printf("first loop/n");
        dbg1 = 1; //1 ==> first loop
        dbg2 = 1; 
#endif
    }

    //cambiato il 20/11/2010 mattina
    DI[TERMOSTATOP0] = PLCOpI(TERMOSTATOP0);
	DI[TERMOSTATOP1CORR] = PLCOpI(TERMOSTATOP1CORR);           
	DI[TERMOSTATOP1PAOLO] = PLCOpI(TERMOSTATOP1PAOLO);           
	DI[TERMOSTATOP1GIORNO] = PLCOpI(TERMOSTATOP1GIORNO);
     	
    // input/outpout via seriale
    ParseCOM();

    // Gestione sequenziale degli Input e degli Output e della seriale, con periodo di un secondo
    if (PLCPulse1000)
    {
        if (nextaction==2)
            nextaction=0;

        switch (nextaction)
        {
            case 0: //void   ManageHeatingInputs(void);
//cambiato il 20/11/2010 mattina
//		    DI[TERMOSTATOP0] = PLCOpI(TERMOSTATOP0);
//		    DI[TERMOSTATOP1] = PLCOpI(TERMOSTATOP1);           
#ifdef DBG_LEVEL
        if (dbg1 == 1)
        {
            printf("first loop : case 0. Pass order: %d /n", dbg2);
            dbg2++;
        }
#endif

            break;

            case 1:
#ifdef DBG_LEVEL
        if (dbg1 == 1)
        {
            printf("first loop : case 1. Pass order: %d/n", dbg2);
            dbg2++;
        }        
#endif
                ManageHeatingOutputs();
                break;

	        case 2:
		        ParseCOM();
		        break;

            default:
                return;
        }
        nextaction++;
    } 
}


void ParseCOM(void)
{
static unsigned char cmd=0;
static unsigned char op_len;
static unsigned char op_cnt;
static unsigned char parm1;
char c;

// Manage the serial port "A" tick.
    SetTermIOVectors(IOSerialPortA); //Set the serial port A as I/O console
    TermIOTick(); //Manage the selected I/O console

   if (GetRxChars())
    {

        // Read the received character.
        c=GetCh();

        // a seconda del comando e' previsto dopo un operando di lunghezza op_len
        switch (c)
        {
            case 'H': //impostazione ora. Operando 2chr: hh
            case 'm': //impostazione minuti. Operando 2chr: mm 
            case 'M': //impostazione mese ed anno. Operando 2chr: MM
            case 'Y': //impostazione anno. Operando 2chr: YY
    	    case 'C': //leggi vettore confort Piano 1. Operando 2chr: 00-23
	        case 'D': //leggi vettore confort Piano 0. Operando 2chr: 00-23
	        case 'I': //leggi input  x (00-15)
	        case 'O': //leggi output x (00-07)
	            cmd=c;
	            op_len=2; 
  	            op_cnt= parm1=0;
                break;

//configurazine vettore comfort piano 1
            case 'X': //imposta tutto spento alle ore hh. Operando 2chr: hh
    	    case 'A': //imposta tutto acceso alle ore hh. Operando 2chr: hh
	        case 'G': //imposta zona giorno accesa alle ore hh. Operando 2chr: hh
	        case 'N': //imposta zona notte accesa alle ore hh. Operando 2chr: hh
	        case 'B': //imposta zona bagni accesa alle ore hh. Operando 2chr: hh
	            cmd=c;
	            op_len=2; 
  	            op_cnt= parm1=0;
                break;

//configurazine vettore comfort piano 0
            case 'x': //imposta tutto spento alle ore hh. Operando 2chr: hh
    	    case 'a': //imposta tutto acceso alle ore hh. Operando 2chr: hh
	        case 'g': //imposta zona giorno accesa alle ore hh. Operando 2chr: hh
	        case 'n': //imposta zona notte accesa alle ore hh. Operando 2chr: hh
	        case 'b': //imposta zona notte accesa alle ore hh. Operando 2chr: hh
	            cmd=c;
	            op_len=2; 
  	            op_cnt= parm1=0;
                break;

            case 'S': //leggi stato
            case 'T': //leggi ora

	            cmd=c;
	            ExecuteCmd(cmd, parm1);
	            op_len= op_cnt= cmd = parm1 = 0; //reset 
                break;

         case '0': case '1': case '2': case '3': case '4':
         case '5': case '6': case '7': case '8': case '9':
            op_cnt++;
		    if ((op_len == 0) || (cmd==0) || (op_len<op_cnt))
		    {	// errore !
			    cmd=op_len=op_cnt=parm1=0; //reset
//                printf("inside ParseCOM.switch.3; cmd %u\n", cmd);

                break;
		    }    
		    if (op_cnt == 1) 
            {
			    parm1= (c - '0') ;
//                printf("char1=%u\n",parm1);
                break;
            }
		    if (op_cnt == 2) 
			{
                parm1= (c - '0') + parm1*10;
//                printf("char1=%u\n",parm1);
//                printf("inside ParseCOM.switch.5; cmd %u\n", cmd);

		        ExecuteCmd(cmd, parm1);
	            cmd=op_len=op_cnt = parm1=0;            
	            return;
            }
            default:
		        cmd=op_len=op_cnt= parm1=0;            
	        return;
        }
  }
}

char ExecuteCmd(unsigned char cmd, unsigned char parm1)
{
//static RTCDATA RtcData; //Rtc data structure
char i;
//  printf ("inside ExcuteCMD. cmd=%u parm1=%u", cmd, parm1);
  
    // Manage the serial port tick.
    SetTermIOVectors(IOSerialPortA); //Set the serial port A as I/O console
    TermIOTick(); //Manage the selected I/O console

    GetRtc(&RtcData); //Read the current RTC registers

    switch (cmd)
    {
        case 'H': //impostazione ora. Operando 2chr: hh
        if (parm1>23)
            return (-1); 
        RtcData.Hour = parm1;
        SetRtc(&RtcData); //Write the RTC registers with the new values
        break; 

        case 'm': //impostazione minuti. Operando 2chr: mm 
        if (parm1>59) 
            return (-1);
        RtcData.Minute = parm1;
        SetRtc(&RtcData); //Write the RTC registers with the new values
        break;

        case 'M': //impostazione mese. Operando 2chr: MM
        if ((parm1>0) && (parm1<13)) 
        {
                RtcData.Month = parm1;
                SetRtc(&RtcData); //Write the RTC registers with the new values
            break;
        }
        return (-1);

        case 'Y': //impostazione anno. Operando 2chr: YY
        if (parm1>99)
            return (-1);     
        RtcData.Year = parm1;
        SetRtc(&RtcData); //Write the RTC registers with the new values
        break;

    	case 'C': //leggi vettore confort Piano 1. Operando 2chr: 00-23
        if (parm1>23) 
        {
            printf ( "errore input ora > 23. Inserire 2 cifre dopo il comando C. Es C21\n");
            return (-1);
        }
        printf ( "piano 1 dalle %u:00 alle %u:59 %c\n", parm1, parm1, comfortP1[parm1]);
        break;
         
        case 'D': //leggi vettore confort Piano 0. Operando 2chr: 00-23
        if (parm1>23) 
        {
            printf ( "errore input ora > 23. Inserire 2 cifre dopo il comando D. Es D19\n");
            return (-1);
        }
        printf ( "piano 0 dalle %u:00 alle %u:59 %c\n", parm1, parm1, comfortP0[parm1]);
        break;

	    case 'I': //leggi input  x (00-15)
        if (parm1>15) 
        {
            printf ( "errore input > 15. Inserire 2 cifre dopo il comando I. Es I01\n");
            return (-1);
        }

        printf ( "input %u: %u\n", parm1, DI[parm1] );
        break;

	 case 'O': //leggi output x (00-07)
        if (parm1>7)
        {
            printf ( "errore input > 7. Inserire 2 cifre dopo il comando O. Es O06\n");
            return (-1);
        }
        printf ( "output %u: %u\n", parm1, PLCOpO(parm1) );
        break;

	    case 'S': //leggi stato
        // @Section("Custom Function - 0.7.0") - riduzione object code usando cicli for
        // 24 byte comfort vector piano 0
/*        printf ( "%c%c%c%c", comfortP0[0],comfortP0[1],comfortP0[2],comfortP0[3]);
        printf ( "%c%c%c%c", comfortP0[4],comfortP0[5],comfortP0[6],comfortP0[7]);
        printf ( "%c%c%c%c", comfortP0[8],comfortP0[9],comfortP0[10],comfortP0[11]);
        printf ( "%c%c%c%c", comfortP0[12],comfortP0[13],comfortP0[14],comfortP0[15]);
        printf ( "%c%c%c%c", comfortP0[16],comfortP0[17],comfortP0[18],comfortP0[19]);
        printf ( "%c%c%c%c", comfortP0[20],comfortP0[21],comfortP0[22],comfortP0[23]);

        // 24 byte comfort vector piano 1
        printf ( "%c%c%c%c", comfortP1[0],comfortP1[1],comfortP1[2],comfortP1[3]);
        printf ( "%c%c%c%c", comfortP1[4],comfortP1[5],comfortP1[6],comfortP1[7]);
        printf ( "%c%c%c%c", comfortP1[8],comfortP1[9],comfortP1[10],comfortP1[11]);
        printf ( "%c%c%c%c", comfortP1[12],comfortP1[13],comfortP1[14],comfortP1[15]);
        printf ( "%c%c%c%c", comfortP1[16],comfortP1[17],comfortP1[18],comfortP1[19]);
        printf ( "%c%c%c%c", comfortP1[20],comfortP1[21],comfortP1[22],comfortP1[23]);
*/
        for (i=0;i<24;i++) printf ( "%c", comfortP0[i]);
        for (i=0;i<24;i++) printf ( "%c", comfortP1[i]);

        // 16 byte input
//        printf ( "%u%u%u%u", DI[0],DI[1],DI[2],DI[3] );
//        printf ( "%u%u%u%u", DI[4],DI[5],DI[6],DI[7] );
//        printf ( "%u%u%u%u", DI[8],DI[9],DI[10],DI[11] );
//        printf ( "%u%u%u%u", DI[12],DI[13],DI[14],DI[15] );
        for (i=0;i<16;i++) printf ( "%u", DI[i]);

        // 8 byte output
        printf ( "%u%u%u%u", PLCOpO(0), PLCOpO(1), PLCOpO(2), PLCOpO(3) );
        printf ( "%u%u%u%u", PLCOpO(4), PLCOpO(5), PLCOpO(6), PLCOpO(7) );
 
        // misura tempo di accensione
        // @Section("Custom Function - 0.7.0") leggi tempo di accensione
        printf ( "\nPLC ON FROM: %u %u %u - %u:%u ", RtcPLCSTARTTime.Day, RtcPLCSTARTTime.Month, RtcPLCSTARTTime.Year, RtcPLCSTARTTime.Hour, RtcPLCSTARTTime.Minute );
        printf ( "\nLAST CALDAIA ON: %u %u %u - %u:%u ", RtcONTime.Day, RtcONTime.Month, RtcONTime.Year, RtcONTime.Hour, RtcONTime.Minute );
        printf ( "\nCALDAIA ON FROM%u", TotMinutiON);
    
        printf ( "\n");
 
        break;

	    case 'T': //leggi real time clock
        printf ( "real time clock: %u %u %u - %u:%u:%u\n ", RtcData.Day, RtcData.Month, RtcData.Year, RtcData.Hour, RtcData.Minute, RtcData.Second );
        break;

//configurazine vettore comfort piano 1
        case 'X': //imposta tutto spento alle ore hh. Operando 2chr: hh
    	case 'A': //imposta tutto acceso alle ore hh. Operando 2chr: hh
	    case 'G': //imposta zona giorno accesa alle ore hh. Operando 2chr: hh
	    case 'N': //imposta zona notte accesa alle ore hh. Operando 2chr: hh
	    case 'B': //imposta zona notte accesa alle ore hh. Operando 2chr: hh
	    if (parm1>23) 
        {
            printf ( "errore input ora > 23. Inserire 2 cifre dopo il comando %c. Es %c19\n",cmd,cmd);
            return (-1);
        }
            comfortP1[parm1]=cmd;
            printf ( "piano 1 impostato ad %c dalle %u:00 alle %u:59\n", comfortP1[parm1],parm1, parm1);
            break;

//configurazine vettore comfort piano 0
            case 'x': //imposta tutto spento alle ore hh. Operando 2chr: hh
    	    case 'a': //imposta tutto acceso alle ore hh. Operando 2chr: hh
	        case 'g': //imposta zona giorno accesa alle ore hh. Operando 2chr: hh
	        case 'n': //imposta zona notte accesa alle ore hh. Operando 2chr: hh
            case 'b': //imposta zona notte accesa alle ore hh. Operando 2chr: hh
            if (parm1>23) 
            {
                printf ( "errore input ora > 23. Inserire 2 cifre dopo il comando %c. Es %c19\n",cmd,cmd);
                return (-1);
            }
            comfortP0[parm1]=cmd+'X'-'x';
            printf ( "piano 0 impostato ad %c dalle %u:00 alle %u:59\n", comfortP0[parm1],parm1, parm1);
            break;
    }
	return (0);
}

void   ManageHeatingOutputs(void)
{

    GetRtc(&RtcData); //Read the current RTC registers

    DO[ZONA1B]= FALSE ; // zona bagni e corridoio 
    DO[ZONA1G]= FALSE;
    DO[ZONA1N]= FALSE;
    DO[ZONAP0]= FALSE ; // unica zona al piano 0   
    openvalves = 0;     

    // First level heating zones corridoio
    if (DI[TERMOSTATOP1CORR])
    {
//        switch(comfortP1[PLCRtcHour])
          switch(comfortP1[RtcData.Hour])
        {
        case 'A':
        case 'N':
        case 'G':
        case 'B':
            DO[ZONA1B] = TRUE ; // zona bagni e corridoio sempre on
            openvalves++;
            break;
      
        case 'X':
        default:
            DO[ZONA1B] = FALSE ; // tutto spento
            break;
        }
    }

    // First level heating zones Paolo
    // @Section("Custom Function - 0.6.0")
    // @Section("Custom Function - 0.6.1")
    if (DI[TERMOSTATOP1PAOLO])
    {
//        switch(comfortP1[PLCRtcHour])
          switch(comfortP1[RtcData.Hour])
        {
        case 'A':
        case 'N':
            DO[ZONA1N] =TRUE;
            openvalves++;
            break;
        case 'G':
        case 'B':
        case 'X':
        default:
            DO[ZONA1N] =FALSE;
            break;
        }
    }

   // 0.6.1: First level heating zones SOGGIORNO
   // @Section("Custom Function - 0.6.1")
    if (DI[TERMOSTATOP1GIORNO])
    {
//        switch(comfortP1[PLCRtcHour])
          switch(comfortP1[RtcData.Hour])
        {
        case 'A':
        case 'G':
            DO[ZONA1G] =TRUE;
            openvalves++;
            break;
        case 'N':
        case 'B':
        case 'X':
        default:
            DO[ZONA1G] =FALSE;
            break;
        }
    }

    // Level zero heating zone
    if (DI[TERMOSTATOP0])
    {
        switch(comfortP0[RtcData.Hour])
        {
        case 'A':
        case 'N':
        case 'G':
        case 'B':
            DO[ZONAP0]= TRUE ; // unica zona al piano 0
            openvalves++;
            break;

        default:
            DO[ZONAP0] = FALSE ; // unica zona al piano 0
            break;
        }
    }

// Open/Close VALVES
    PLCOpO(ZONA1B)= DO[ZONA1B];
    PLCOpO(ZONA1G)= DO[ZONA1G];
    PLCOpO(ZONA1N)= DO[ZONA1N];
    PLCOpO(ZONAP0)= DO[ZONAP0];


// Switch on heater only if at last a zone need heating
    if  ( (DI[TERMOSTATOP0] || DI[TERMOSTATOP1CORR] || DI[TERMOSTATOP1PAOLO]|| DI[TERMOSTATOP1GIORNO]) && openvalves ) 
	    PLCOpO(HEATER_ON)= TRUE; 
    else 
	    PLCOpO(HEATER_ON)= FALSE; 

    
// 0.7.0 Antiicing management, upgrade per azionare rolling tutte le valvole
// LASCIO SEMPRE ALMENO UNA VALVOLA APERTA PER PERMETTERE IL DEICING, GESTITO DALLA CALDAIA
// @Section("Custom Function - 0.7.0")
    if (!openvalves) 
    {
        switch(RtcData.Hour%3)
        {   
	    case 0: PLCOpO(ZONA1B)= TRUE ; // zona bagni e corridoio P1    
                break;
        case 1: PLCOpO(ZONAP0)= TRUE ; // unica zona al piano 0
                break;
        case 2: PLCOpO(ZONA1G)= TRUE ; //  zona giorno P1
                break;
        case 3: PLCOpO(ZONA1N)= TRUE ; //  zona notte P1
                break;
        }
    }


// gestisco accensine/spegnimento a cavallo di 2 giorni
// @Section("Custom Function - 0.7.1")  statistiche
        if (RtcData.Day>RtcONTime.Day) // cambiato giorno in questo ciclo
        {
            TotMinutiON +=  
              ((24 *60 + 60)
              -(RtcONTime.Hour  *60 + RtcONTime.Minute  ));

            StatMinutiON[RtcONTime.Month-1][RtcONTime.Day-1]=TotMinutiON;
            TotMinutiON=0;
            GetRtc (&RtcONTime);
        }

// misura tempo di accensione
// @Section("Custom Function - 0.7.0")
    if (openvalves && !PreviousStatus) //si e' acceso adesso
    {
        GetRtc (&RtcONTime);
        PreviousStatus = TRUE;
 //       if (PLCOpO(ZONA1N)) PreviousStatus = K_ZONA1N;
 //       if (PLCOpO(ZONA1G)) PreviousStatus += K_ZONA1G;
 //       if (PLCOpO(ZONA1B)) PreviousStatus += K_ZONA1B;
 //       if (PLCOpO(ZONAP0)) PreviousStatus += K_ZONAP0;

    }
    else if (!openvalves && PreviousStatus) //si e' spento adesso
    {
        // GetRtc (&RtcTimeNow);
 
        TotMinutiON +=  
             (RtcData.Hour *60 + RtcData.Minute )
            -(RtcONTime.Hour  *60 + RtcONTime.Minute  ); 
    
//    TotOreON = TotOreON+ (unsigned int)(TotMinutiON/60);
//    TotMinutiON=(unsigned int)(TotMinutiON%60);
        PreviousStatus=FALSE;
}
//        TotTermoON += PreviousStatus;

}
