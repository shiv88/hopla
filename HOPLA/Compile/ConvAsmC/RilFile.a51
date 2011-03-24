

$INCLUDE (C:\Program Files\Elsist\Remoter\Lib\Raisonance\Sfr043b300\ElSystemLib.inc)
$INCLUDE (C:\Program Files\Elsist\Remoter\Lib\Raisonance\Sfr036e000\ElPLCLib.inc)


    PUBLIC PLC_L_RilFile
    PUBLIC PLC_O_0
    PUBLIC PLC_O_1
    PUBLIC PLC_O_2
    PUBLIC PLC_O_3
    PUBLIC PLC_O_4
    PUBLIC PLC_O_5
    PUBLIC PLC_O_6
    PUBLIC PLC_O_7
    PUBLIC PLC_I_0
    PUBLIC PLC_I_1
    PUBLIC PLC_I_2
    PUBLIC PLC_I_3
    PUBLIC PLC_I_4
    PUBLIC PLC_I_5
    PUBLIC PLC_I_6
    PUBLIC PLC_I_7
    PUBLIC PLC_I_8
    PUBLIC PLC_I_9
    PUBLIC PLC_I_10
    PUBLIC PLC_I_11
    PUBLIC PLC_I_12
    PUBLIC PLC_I_13
    PUBLIC PLC_I_14
    PUBLIC PLC_I_15
    PUBLIC PLC_F_1
    EXTRN XDATA(PLC_DW_P0ZonaUnica)
    EXTRN XDATA(PLC_DW_P1ZonaBagni)
    EXTRN XDATA(PLC_DW_P1ZonaGiorno)
    EXTRN XDATA(PLC_DW_P1ZonaNotte)
    EXTRN CODE(CustomFunction)

PLCMemoryLogicInputs SET (05000h)
PLCMemoryLogicOutputs SET (05100h)
PLCMemoryFlags SET (00000h)

PLC_O_0 EQU PLCMemoryLogicOutputs+00h
PLC_O_1 EQU PLCMemoryLogicOutputs+01h
PLC_O_2 EQU PLCMemoryLogicOutputs+02h
PLC_O_3 EQU PLCMemoryLogicOutputs+03h
PLC_O_4 EQU PLCMemoryLogicOutputs+04h
PLC_O_5 EQU PLCMemoryLogicOutputs+05h
PLC_O_6 EQU PLCMemoryLogicOutputs+06h
PLC_O_7 EQU PLCMemoryLogicOutputs+07h
PLC_I_0 EQU PLCMemoryLogicInputs+00h
PLC_I_1 EQU PLCMemoryLogicInputs+01h
PLC_I_2 EQU PLCMemoryLogicInputs+02h
PLC_I_3 EQU PLCMemoryLogicInputs+03h
PLC_I_4 EQU PLCMemoryLogicInputs+04h
PLC_I_5 EQU PLCMemoryLogicInputs+05h
PLC_I_6 EQU PLCMemoryLogicInputs+06h
PLC_I_7 EQU PLCMemoryLogicInputs+07h
PLC_I_8 EQU PLCMemoryLogicInputs+08h
PLC_I_9 EQU PLCMemoryLogicInputs+09h
PLC_I_10 EQU PLCMemoryLogicInputs+010h
PLC_I_11 EQU PLCMemoryLogicInputs+011h
PLC_I_12 EQU PLCMemoryLogicInputs+012h
PLC_I_13 EQU PLCMemoryLogicInputs+013h
PLC_I_14 EQU PLCMemoryLogicInputs+014h
PLC_I_15 EQU PLCMemoryLogicInputs+015h
PLC_F_1 EQU PLCMemoryFlags+01h

    CODE_RilFile_CODE SEGMENT CODE
    RSEG CODE_RilFile_CODE

PLC_L_RilFile:

; Line    12 SVIW O 0

; Line    13 SVIW O 1

; Line    14 SVIW O 2

; Line    15 SVIW O 3

; Line    16 SVIW O 4

; Line    17 SVIW O 5

; Line    18 SVIW O 6

; Line    19 SVIW O 7

; Line    20 SVIW I 0

; Line    21 SVIW I 1

; Line    22 SVIW I 2

; Line    23 SVIW I 3

; Line    24 SVIW I 4

; Line    25 SVIW I 5

; Line    26 SVIW I 6

; Line    27 SVIW I 7

; Line    28 SVIW I 8

; Line    29 SVIW I 9

; Line    30 SVIW I 10

; Line    31 SVIW I 11

; Line    32 SVIW I 12

; Line    33 SVIW I 13

; Line    34 SVIW I 14

; Line    35 SVIW I 15

; Line    37 ORGR

; Line    38 LODF F 1
    mov   dptr,#PLC_F_1+0
    movx  a,@dptr
    cpl   a

; Line    39 TASK L CustomFunction
    anl   a,#001h
    jz    Lbl$_0
    push  acc
    lcall CustomFunction
    pop   acc
Lbl$_0:

; Line    43 DEFB DW P1ZonaNotte

; Line    44 DEFB DW P1ZonaGiorno

; Line    45 DEFB DW P1ZonaBagni

; Line    46 DEFB DW P0ZonaUnica
    ret

    END
;
