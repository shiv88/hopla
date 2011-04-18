#ifndef BOOL
#define BOOL unsigned char
#endif

void CustomFunction(void);

//Rtc data structure fake
typedef struct {
char Hour;
char Minute;
char Second;
char Day;
char Month;
char Year;
} RTCDATA ;




//Seerial structure fake
typedef struct {
char DTRComplement;
char EchoFlush;
char RxCtrlDisable;
char Mode;
char DTRManagement;
char WaitLoop;
char ParityEnabled;
char ParityType;
char BitNumber;
char WaitLoop;
char Baud;
} MODESTRUCT;


//Seerial structure fake
typedef struct {
MODESTRUCT Mode;
char DTROnTime;
char DTROffTime;
} SERIALSTRUCT;

extern char PLCFirstLoop;
extern char IOSerialPortA; 
void SetTermIOVectors(char);
void TermIOTick (void);
BOOL GetRxChars (void);
char GetCh(void);
void SetRtc(RTCDATA *RtcData); 
void GetRtc(RTCDATA *RtcData); 
void SetSerialMode(SERIALSTRUCT *SerialStruct) ;


#define FALSE 0
#define TRUE 1

extern BOOL PLCPulse1000;
extern unsigned char PLC_output[];
extern unsigned char PLC_input[];

#define PLCOpO(x) PLC_output[x]
#define PLCOpI(x) PLC_input[x]

#define PLCOpO(x) PLC_output[x]
 