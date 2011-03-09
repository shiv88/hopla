

$INCLUDE (C:\Program Files\Elsist\Remoter\Lib\Raisonance\Sfr043b300\ElSystemLib.inc)
$INCLUDE (C:\Program Files\Elsist\Remoter\Lib\Raisonance\Sfr036e000\ElPLCLib.inc)


    PUBLIC PLC_L_ElPLCLib
    EXTRN XDATA(PLCRtcData)
    EXTRN XDATA(PLCMaxLoopTime)
    EXTRN XDATA(PLCMinLoopTime)
    EXTRN XDATA(PLCLoopTime)
    EXTRN XDATA(PLCSystemTime)
    EXTRN XDATA(PLCRandom)
    EXTRN XDATA(PLCBackupEnd)
    EXTRN XDATA(PLCBackupOneShot)
    EXTRN XDATA(PLCBackupDisable)
    EXTRN XDATA(PLCRestoreFault)
    EXTRN XDATA(PLCEquFlag)
    EXTRN XDATA(PLCGrtFlag)
    EXTRN XDATA(PLCLesFlag)
    EXTRN XDATA(PLCConvError)
    EXTRN XDATA(PLCMathError)
    EXTRN XDATA(PLCSubIsNegative)
    EXTRN XDATA(PLCPulse1000)
    EXTRN XDATA(PLCPulse500)
    EXTRN XDATA(PLCPulse100)
    EXTRN XDATA(PLCTimeBase12800)
    EXTRN XDATA(PLCTimeBase6400)
    EXTRN XDATA(PLCTimeBase3200)
    EXTRN XDATA(PLCTimeBase1600)
    EXTRN XDATA(PLCTimeBase800)
    EXTRN XDATA(PLCTimeBase400)
    EXTRN XDATA(PLCTimeBase200)
    EXTRN XDATA(PLCTimeBase100)
    EXTRN XDATA(PLCLoopToggle)
    EXTRN XDATA(PLCFirstLoop)
    EXTRN XDATA(PLCClock1000)
    EXTRN XDATA(PLCClock500)
    EXTRN XDATA(PLCClock100)
    EXTRN XDATA(PLCChrReceived)
    EXTRN XDATA(PLCTxBufEmpty)
    EXTRN XDATA(PLCTxBufFull)
    EXTRN XDATA(PLCRxBufEmpty)
    EXTRN CODE(SfrPLC_AlwaysZero)
    EXTRN CODE(SfrPLC_AlwaysOne)

PLCMemoryLogicInputs SET (05000h)
PLCMemoryLogicOutputs SET (05100h)
PLCMemoryFlags SET (00000h)


    CODE_ElPLCLib_CODE SEGMENT CODE
    RSEG CODE_ElPLCLib_CODE

PLC_L_ElPLCLib:

; Line    13 EXTR L SfrPLC_AlwaysOne

; Line    14 DEFG F PLCAlwaysOne L SfrPLC_AlwaysOne KD 0

; Line    16 EXTR L SfrPLC_AlwaysZero

; Line    17 DEFG F PLCAlwaysZero L SfrPLC_AlwaysZero KD 0

; Line    19 EXTR F PLCRxBufEmpty

; Line    20 EXTR F PLCTxBufFull

; Line    21 EXTR F PLCTxBufEmpty

; Line    22 EXTR F PLCChrReceived

; Line    23 EXTR F PLCClock100

; Line    24 EXTR F PLCClock500

; Line    25 EXTR F PLCClock1000

; Line    26 EXTR F PLCFirstLoop

; Line    27 EXTR F PLCLoopToggle

; Line    28 EXTR F PLCTimeBase100

; Line    29 EXTR F PLCTimeBase200

; Line    30 EXTR F PLCTimeBase400

; Line    31 EXTR F PLCTimeBase800

; Line    32 EXTR F PLCTimeBase1600

; Line    33 EXTR F PLCTimeBase3200

; Line    34 EXTR F PLCTimeBase6400

; Line    35 EXTR F PLCTimeBase12800

; Line    36 EXTR F PLCPulse100

; Line    37 EXTR F PLCPulse500

; Line    38 EXTR F PLCPulse1000

; Line    39 EXTR F PLCSubIsNegative

; Line    40 EXTR F PLCMathError

; Line    41 EXTR F PLCConvError

; Line    42 EXTR F PLCLesFlag

; Line    43 EXTR F PLCGrtFlag

; Line    44 EXTR F PLCEquFlag

; Line    45 EXTR F PLCRestoreFault

; Line    46 EXTR F PLCBackupDisable

; Line    47 EXTR F PLCBackupOneShot

; Line    48 EXTR F PLCBackupEnd

; Line    49 EXTR Y PLCRandom

; Line    50 EXTR W PLCSystemTime

; Line    51 EXTR W PLCLoopTime

; Line    52 EXTR W PLCMinLoopTime

; Line    53 EXTR W PLCMaxLoopTime

; Line    59 EXTR Y PLCRtcData

; Line    60 DEFG Y PLCRtcYear Y PLCRtcData KD 0

; Line    61 DEFG Y PLCRtcMonth Y PLCRtcData KD 1

; Line    62 DEFG Y PLCRtcDay Y PLCRtcData KD 2

; Line    63 DEFG Y PLCRtcWeekDay Y PLCRtcData KD 3

; Line    64 DEFG Y PLCRtcHour Y PLCRtcData KD 4

; Line    65 DEFG Y PLCRtcMinute Y PLCRtcData KD 5

; Line    66 DEFG Y PLCRtcSecond Y PLCRtcData KD 6

; Line    67 DEFG Y PLCRtcHundred Y PLCRtcData KD 7
    ret

    END
;
