

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
#pragma noinitstaticvar
at PLC_BACKUP_COPY_START_ADDRESS BACKUPHEADERSTRUCT PLCBackupHeader;
at (PLC_BACKUP_COPY_START_ADDRESS+sizeof(BACKUPHEADERSTRUCT)) unsigned char PLCBackupDataArea[128];
#pragma initstaticvar

//[End of File]
