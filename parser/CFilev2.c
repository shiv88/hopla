
/*-----------------------------------------------------------------------------+
|       Copyright (c), 3iP, 2007                                               |
|       File: FSM.c    Finite State Multi-SubMachines                          |
+--------------+-------+----------------------------------------------+--------+
|     DATE     |VERSION| HISTORY/CHANGES                              |   BY   |
|  (MM/DD/YY)  | VX.Y  |                                              |        |
+--------------+-------+----------------------------------------------+--------+
|  1/3/11 wip  | 0.0.1 | nuovo parser                                 |   IB   |
|              |       |                                              |        |
+--------------+-------+----------------------------------------------+-------*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char s[32];
static char argcnt;
static char retval;
static char argvect[6];
static chptr;
struct cmd_descr {
 char cmd[10];
 char argnum;
 }  commandlist[]= { {"nop", 0 }, {"status", 0}, {"timeset", 3}, {"timeread",3}, {"dataset", 3},{"dataread",3} };

// function prototipes       
char ParseCOM(char  *, char *); //restituisce 0:no command, oppure il numero del comando
char ExecuteCmd(unsigned char , unsigned char );
// -----------------------------------------------------------------------------
// CUSTOM FUNCTION
// -----------------------------------------------------------------------------

main()
{
char i; 

printf("test parser:");
fgets ( s, 31, stdin);
printf("\nInput string:%s",s);
	retval=ParseCOM(&argcnt, argvect);
	printf("\nretval:%d \nNumero argomenti:%d",retval,argcnt);
if (argcnt == 3 )
    	printf("\narg1:%d - arg2:%d - arg3:%d\n",argvect[0], argvect[1],argvect[2]);


/*    if (retval != 0)
    {
        printf("retval: %c argcnt:%c \n", retval, argcnt);
        while (i<argcnt)
        {
            printf("argm %c = %c\n", i+1, argvect[i]);
            i++;
        }
    }
*/

}


#define CMDLINEMAXLEN 32

char ParseCOM(char *argcnt, char *argvect)
{
char *p;
char i, retcmd;

        for (retcmd=0;retcmd<6;retcmd++)
        	if ( (strstr(s,commandlist[retcmd].cmd)) )
            		break; //trovato il comando 
	        	
        if (retcmd== 6) // non ho trovato comandi
            return (-16);

        p=s+strlen(commandlist[retcmd].cmd);

        for (i=0; i<commandlist[retcmd].argnum; i++)
        {
		//errore mi attendo un separatore
		if ( ((*p)!=' ') && ((*p) != ':') )
			return (-retcmd-16*1);
           
		//skip all white spaces
		while (isspace(*p) || ((*p)==':'))
			p++; 

		//errore string terminata prima di aver letto tutti i parametri
		if ((*p)== '\0') 
			return (-retcmd-16*2);

		//convert all digits
        	argvect[i]=0;
		while (isdigit(*p))
                	argvect[i] = argvect[i]*10 + (*(p++))-'0';          
	}    

	// return parameter
	*argcnt=commandlist[retcmd].argnum;
	return (retcmd);       
}

char ExecuteCmd(unsigned char cmd, unsigned char parm1)
{
;
}

void   ManageHeatingOutputs(void)
{

  ;

}