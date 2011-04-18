
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


// function prototipes       

// ritorna valore vettore comfortP1 dalle i:00 alle i:59
unsigned char get_comfortP1(unsigned char i);

// scrive in mem non volatile il valore c nel vettore comfortP1 dalle i:00 alle i:59
void put_comfortP1(unsigned char i, unsigned char c);
