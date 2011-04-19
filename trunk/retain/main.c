
/*-----------------------------------------------------------------------------+
|       Copyright (c), IB, 2011                                                |
|       File:                                                                  |
+--------------+-------+----------------------------------------------+--------+
|     DATE     |VERSION| HISTORY/CHANGES                              |   BY   |
|  (MM/DD/YY)  | VX.Y  |                                              |        |
+--------------+-------+----------------------------------------------+--------+
|  17/3/11 wip | 0.0.1 | test compress to backup                      |   IB   |
|              |       |                                              |        |
+--------------+-------+----------------------------------------------+-------*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char s[32];
static char argcnt;
static char retval;
unsigned long  comfortbackup1, comfortbackup2, comfortbackup3;

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
#include "retain.h" 
  
// -----------------------------------------------------------------------------
// CUSTOM FUNCTION
// -----------------------------------------------------------------------------

main()
{
unsigned char i,j; 



comfortbackup2= comfortbackup3=comfortbackup1=0b10101010101010101010101010101010;
    printf("test01:\nb1=%x b2=%x b3=%x",  (unsigned int)comfortbackup1, 
    (unsigned int)comfortbackup2, 
    (unsigned int)comfortbackup3);

for (i=0;i<24;i++)
	put_comfortP1(i, comfortP1[i]);

printf("\nb1=%x b2=%x b3=%x",  (unsigned int)comfortbackup1, 
    (unsigned int)comfortbackup2, 
    (unsigned int)comfortbackup3);

for (i=0;i<24;i++)
	printf("[%d]=%c/%c ",i,comfortP1[i], get_comfortP1(i));


}


