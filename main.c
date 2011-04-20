#include "ELSystemLib.h"

RTCDATA fakeRtcData;
char fakechar;
BOOL fakegetrxchar;
BOOL PLCPulse1000;
unsigned char PLC_output[8];
unsigned char PLC_input[16];
char PLCFirstLoop;
char IOSerialPortA; 

#define TERMOSTATOP1CORR 0
#define TERMOSTATOP0 1 
#define TERMOSTATOP1PAOLO 2
#define TERMOSTATOP1GIORNO 3

#define HEATER_ON 0
#define ZONA1N 4
#define ZONA1G 5
#define ZONA1B 6
#define ZONAP0 7

void fakeTTY(char *s)
{
char i;
  fakegetrxchar=TRUE;
//  strcpy (s,"timeread\r");
  for (i=0; i<strlen(s);i++)
  {
    fakechar=s[i];
    CustomFunction();
  }
  fakegetrxchar=FALSE;
}

void printoutput(void)
{
  if (PLC_output[HEATER_ON]) printf ("HEATER_ON - ");
    else printf ("HEATER_OFF - ");
  if (PLC_output[ZONA1N]) printf ("ZONA1N_ON - ");
    else printf ("ZONA1N_OFF - ");
  if (PLC_output[ZONA1G]) printf ("ZONA1G_ON - ");
    else printf ("ZONA1G_OFF - ");
  if (PLC_output[ZONA1B]) printf ("ZONA1B_ON - ");
    else printf ("ZONA1B_OFF - ");
  if (PLC_output[ZONAP0]) printf ("ZONAP0_ON");
    else printf ("ZONAP0_OFF");
  printf ("\n");
}

main ()
{
int i;
char s[40];


  PLCFirstLoop=TRUE;
  PLCPulse1000 = FALSE;
  IOSerialPortA =0;
  CustomFunction();
  printoutput();
 
  PLCFirstLoop=FALSE;
  PLCPulse1000 = TRUE;
  PLC_input[TERMOSTATOP1CORR]=1;
  PLC_input[TERMOSTATOP0]=1;
  PLC_input[TERMOSTATOP1PAOLO]=1;
  PLC_input[TERMOSTATOP1GIORNO]=1;
  fakeRtcData.Hour=6;
  CustomFunction();
  CustomFunction();
  printoutput();

/*
  fakeRtcData.Hour=7;
  CustomFunction();
  CustomFunction();
  printoutput();

  fakeRtcData.Hour=8;
  CustomFunction();
  CustomFunction();
  printoutput();

  fakegetrxchar=TRUE;
  strcpy (s,"timeread\r");
  for (i=0; i<strlen(s);i++)
  {
    fakechar=s[i];
    CustomFunction();
  }
  fakegetrxchar=FALSE;

  fakegetrxchar=TRUE;
  strcpy (s,"status\r");
  for (i=0; i<strlen(s);i++)
  {
    fakechar=s[i];
    CustomFunction();
  }
  fakegetrxchar=FALSE;
*/
 fakeTTY("timeset 07:55\r");
 fakeTTY("dataset 20 4 11\r");
 fakeTTY("status\r");
 fakeTTY("timeread\r");


}

void SetTermIOVectors(char c)
{
;
}

void GetSerialMode(SERIALSTRUCT *SerialStruct)
{
; 
}

void SetSerialMode(SERIALSTRUCT *SerialStruct) //Set communication mode
{
;
}

//Read the current RTC registers
void    GetRtc(RTCDATA *RtcData) 
{
  RtcData->Hour = fakeRtcData.Hour;
  RtcData->Minute = fakeRtcData.Minute;
  RtcData->Second = fakeRtcData.Second;
  RtcData->Day = fakeRtcData.Day;
  RtcData->Month = fakeRtcData.Month;
  RtcData->Year = fakeRtcData.Year;
}

//SetRTC registers
void SetRtc(RTCDATA *RtcData) 
{
  fakeRtcData.Hour =   RtcData->Hour ;
  fakeRtcData.Minute = RtcData->Minute;
  fakeRtcData.Second = RtcData->Second ;
  fakeRtcData.Day = RtcData->Day;
  fakeRtcData.Month = RtcData->Month ;
  fakeRtcData.Year = RtcData->Year ;
}


void TermIOTick (void)
{
;
}

BOOL GetRxChars (void)
{
return (fakegetrxchar);
}


char GetCh(void)
{
return (fakechar);
}




 