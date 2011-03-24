

#include <C:\Program Files\Elsist\Remoter\Lib\Raisonance\Sfr043b300\ElSystemLib.h>
#include <C:\Program Files\Elsist\Remoter\Lib\Raisonance\Sfr036e000\ElPLCLib.h>

#define PLC_BACKUP_COPY_START_ADDRESS 0x5200
at 0x5000 unsigned char PLCMemoryLogicInputs[256];
at 0x5100 unsigned char PLCMemoryLogicOutputs[256];
at 0x0000 unsigned char PLCMemoryFlags[1472];
PLCRTCDATA PLCRtcData;

unsigned char PLCLogicInputDebouncingTime[24] = {
10,10,10,10,10,10,10,10,
10,10,10,10,10,10,10,10,
10,10,10,10,10,10,10,10,
};
unsigned char PLCLogicInputDebouncingBuffer[24];
at 0x5CC unsigned long PLC_DW_P1ZonaNotte;
at 0x5D0 unsigned long PLC_DW_P1ZonaGiorno;
at 0x5D4 unsigned long PLC_DW_P1ZonaBagni;
at 0x5D8 unsigned long PLC_DW_P0ZonaUnica;
at 0x5C0 unsigned char PLCBackupDummy0[12];
#pragma noinitstaticvar
at PLC_BACKUP_COPY_START_ADDRESS BACKUPHEADERSTRUCT PLCBackupHeader;
at (PLC_BACKUP_COPY_START_ADDRESS+sizeof(BACKUPHEADERSTRUCT)) unsigned char PLCBackupDataArea[184];
#pragma initstaticvar

//[End of File]
