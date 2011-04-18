/*-----------------------------------------------------------------------------+
|       Copyright (c), Ignazio Binanti                                         |
|       File: retain.h                                                         |
+--------------+-------+----------------------------------------------+--------+
|     DATE     |VERSION| HISTORY/CHANGES                              |   BY   |
|  (MM/DD/YY)  | VX.Y  |                                              |        |
+--------------+-------+----------------------------------------------+--------+
|  24/3/11 wip | 0.0.1 | test compress to backup                      |   IB   |
+--------------+-------+----------------------------------------------+--------+
|  12/4/11 wip | 0.0.0 | intodotto test automatico                    |   IB   |
+--------------+-------+----------------------------------------------+-------*/

unsigned long  comfortbackup1, comfortbackup2, comfortbackup3;
char simboli [8]={'X','B', 'N', ' ', 'G', ' ',  ' ', 'A'};

// function prototipes  
#include "retain.h"     

// ritorna valore vettore comfortP1 dalle i:00 alle i:59
unsigned char get_comfortP1(unsigned char i)
{

    if (i<8) 
        return (simboli [(char) (((comfortbackup1 << (4*i)) >> 28) & 0b111)] ); 
    
    if (i<16)  
        return (simboli [(char) (((comfortbackup2 << (4*(i-8))) >> 28) & 0b111)] );

    return (simboli [(char) (((comfortbackup3 << (4*(i-16))) >> 28) & 0b111)] );   
}


void put_comfortP1(unsigned char i, unsigned char c)
{
unsigned long temp;
char j;

    for (j = sizeof(simboli) / sizeof(*simboli) -1; j>=0; j--)
        if (simboli[j]==c)
            break;

    if (i<8) {
        temp = ~( 0b01110000000000000000000000000000 >> (4*i) ); //  mask per azzerare i 3 bit del i/esimo nibble da modificare  
        comfortbackup1 &= temp;
        comfortbackup1 |= ((j<<28) >> (4*i));
    } 
    else if (i<16) {
        temp = ~( 0b01110000000000000000000000000000 >> (4*(i-8)) );    // mask per azzerare i 3 bit del i/esimo nibble da modificare     
        comfortbackup2 &= temp;
        comfortbackup2 |= ((j<<28) >> (4*(i-8)));
    }
    else {
        temp = ~( 0b01110000000000000000000000000000 >> (4*(i-16)) );    // mask per azzerare i 3 bit del i/esimo nibble da modificare
        comfortbackup3 &= temp;
        comfortbackup3 |= ((j<<28) >> (4*(i-16)));
    }
}

