
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


#include <string.h>
#include <ctype.h>
#include "parser.h"

struct cmd_descr commandlist[]= { 
{"nop", 0 },
{"status", 0},
{"timeset", 3},
{"timeread",3}, 
{"dataset", 3},
{"dataread",0} 
};



#define CMDLINEMAXLEN 32

// valori di ritorno negativi --> errori: 
// -1:  non trovato comando
// -16: separatore non trovato o non corretto
// -32: stringa di input terminata \0 prima di aver letto tutti i parametri previsti
// valori di ritorno positivi --> ok, numero del comando

char ParseCOM(char *s, char *argcnt, char *argvect)
{
char *p;
char i, retcmd=0;
char num_comandi;

	// calcolo quanti comandi sono descritti nel vettore commandlist
	num_comandi=sizeof(commandlist)/sizeof(commandlist[0]);

	// cerco il comando nel vettore commandlist
        for (retcmd=0;retcmd<num_comandi;retcmd++)
        	if ( (strstr(s,commandlist[retcmd].cmd)) )
            		break; //trovato il comando 
        if (retcmd== num_comandi) // non ho trovato comandi
            return (-1);

        p=s+strlen(commandlist[retcmd].cmd);

        for (i=0; i<commandlist[retcmd].argnum; i++)
        {
		//errore mi attendo un separatore
		if ( ((*p)!=' ') && ((*p) != ':') )
			return (16);
           
		//skip all white spaces
		while (isspace(*p) || ((*p)==':'))
			p++; 

		//errore string terminata prima di aver letto tutti i parametri
		if ((*p)== '\0') 
			return (-32);

		//convert all digits
        	argvect[i]=0;
		while (isdigit(*p))
                	argvect[i] = argvect[i]*10 + (*(p++))-'0';          
	}    

	// return parameter
	*argcnt=commandlist[retcmd].argnum;
	return (retcmd);       
}
