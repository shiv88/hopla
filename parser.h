
/*-----------------------------------------------------------------------------+
|       Copyright ... 2011                                                     |
|       File: parser.h    mini parser x com port                               |
+--------------+-------+----------------------------------------------+--------+
|     DATE     |VERSION| HISTORY/CHANGES                              |   BY   |
|  (MM/DD/YY)  | VX.Y  |                                              |        |
+--------------+-------+----------------------------------------------+--------+
|  1/3/11 wip  | 0.0.1 | nuovo parser                                 |   IB   |
+--------------+-------+----------------------------------------------+--------+
|  11/4/11 wip | 0.0.2 | nuova struttura, finalizzata a test autom.   |   IB   |
+--------------+-------+----------------------------------------------+-------*/


struct cmd_descr {
 char cmd[10];
 char argnum;
 };



// function prototipes       
char ParseCOM(char *s, char *argcnt, char *argvect);  //restituisce 0:no command, oppure il numero del comando
