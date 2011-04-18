#include "ELSystemLib.h"

RTCDATA fakeRtcData;
char fakechar;

char PLCFirstLoop;
char IOSerialPortA; 


main ()
{
printf("main");
PLCFirstLoop=1;
IOSerialPortA =0;
CustomFunction();


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
;
}


char GetCh(void)
{
return (fakechar);
}



BOOL PLCPulse1000;
unsigned char PLC_output[8];
unsigned char PLC_input[16];

 