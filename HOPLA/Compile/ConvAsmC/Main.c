

#include <C:\Program Files\Elsist\Remoter\Lib\Raisonance\Sfr043b300\ElSystemLib.h>
#include <C:\Program Files\Elsist\Remoter\Lib\Raisonance\Sfr036e000\ElPLCLib.h>

#include <stdio.h>

extern void PLC_L_ElPLCLib(void);
extern void PLC_L_RilFile(void);
extern PLCRTCDATA PLCRtcData;
extern unsigned char PLCMemoryLogicInputs[];
extern unsigned char PLCMemoryLogicOutputs[];
extern unsigned char PLCMemoryFlags[];

static BACKUPFUNSTRUCT PLCUserBackupInfo={
    (void*)0x0580, //Source data address
    16, //Number of double words to backup
    0, //Backup Memory Type
    0x00005200L, //Backup memory address
};

code PLCREMOTERPROJECTINFO PLCRemoterProjectInfo = {
                         26,
                         2,
                         11,
                         15,
                         33,
                         40,
                         29,
                         8,
                         2,
                         2,
                         "HOPLA",
                         0x5000, 256,
                         0x5100, 256,
                         0x0000, 1472,
                         };


void Main(void);

void Main(void)
{
    if(((*(unsigned long*)&SystemConfig) & 0x00020000) == 0)
    {
        ACC = (unsigned char)&PLCRemoterProjectInfo;

        PLCRtcDataPtr = &PLCRtcData;

        SfrPLC_StartUp();

        SfrPLC_ProgramRestore(&PLCUserBackupInfo);
    }

    while(1)
    {
        SfrPLC_ProgramBackup(&PLCUserBackupInfo);

        SfrPLC_ProgramBegin();

        SfrPLC_InputAcq(0x0000, 0x0000, 0x0000);
        SfrPLC_InputAcq(0x0000, 0x0001, 0x0008);
        SfrPLC_InputAcq(0x0000, 0x0002, 0x0010);

        SfrPLC_RTClock();

        PLC_L_ElPLCLib();
        PLC_L_RilFile();

        SfrPLC_OutputMng(0x0000, 0x0000, 0x0000);

        SfrPLC_ProgramEnd();

        if(((*(unsigned long*)&SystemConfig) & 0x00010000) != 0)
            return;
    }
}
//[End of File]
