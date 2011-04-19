
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


#include <stdio.h>
#include <string.h>
//#include <ctype.h>
#include "parser.h"


char s[32];
static char argcnt;
static char retval;
static char argvect[6];
static chptr;

// -----------------------------------------------------------------------------
// CUSTOM FUNCTION
// -----------------------------------------------------------------------------

main()
{
char i; 

strcpy(s, "status");
retval=ParseCOM(s, &argcnt, argvect);
printf("\ntest01: in:%s out:",s); 
printf(" retval:%d Num. arg:%d",retval,argcnt);
for (i=0; i<argcnt; i++)
    	printf(" arg%d:%d ",i+1, argvect[i]);


strcpy(s, "timeset    ");
retval=ParseCOM(s, &argcnt, argvect);
printf("\ntest02: in:%s out:",s); 
printf(" retval:%d Num. arg:%d",retval,argcnt);
for (i=0; i<argcnt; i++)
    	printf(" arg%d:%d ",i+1, argvect[i]);

strcpy(s, "timeset 1 22  ");
retval=ParseCOM(s, &argcnt, argvect);
printf("\ntest03: in:%s out:",s); 
printf(" retval:%d Num. arg:%d",retval,argcnt);
for (i=0; i<argcnt; i++)
    	printf(" arg%d:%d ",i+1, argvect[i]);

strcpy(s, "timeset 1 22 33 ");
retval=ParseCOM(s, &argcnt, argvect);
printf("\ntest04: in:%s out:",s); 
printf(" retval:%d Num. arg:%d",retval,argcnt);
for (i=0; i<argcnt; i++)
    	printf(" arg%d:%d ",i+1, argvect[i]);


strcpy(s, "timeread 1 22 33 ");
retval=ParseCOM(s, &argcnt, argvect);
printf("\ntest05: in:%s out:",s); 
printf(" retval:%d Num. arg:%d",retval,argcnt);
for (i=0; i<argcnt; i++)
    	printf(" arg%d:%d ",i+1, argvect[i]);

strcpy(s, "dataset 21:12:4");
retval=ParseCOM(s, &argcnt, argvect);
printf("\ntest06: in:%s out:",s); 
printf(" retval:%d Num. arg:%d",retval,argcnt);
for (i=0; i<argcnt; i++)
    	printf(" arg%d:%d ",i+1, argvect[i]);


strcpy(s, "dataread ");
retval=ParseCOM(s, &argcnt, argvect);
printf("\ntest07: in:%s out:",s); 
printf(" retval:%d Num. arg:%d",retval,argcnt);
for (i=0; i<argcnt; i++)
    	printf(" arg%d:%d \n",i+1, argvect[i]);

/*printf("test parser:");

fgets ( s, 31, stdin);
printf("\nInput string:%s",s);
	retval=ParseCOM(s, &argcnt, argvect);
	printf("\nretval:%d \nNumero argomenti:%d",retval,argcnt);
if (argcnt == 3 )
    	printf("\narg1:%d - arg2:%d - arg3:%d\n",argvect[0], argvect[1],argvect[2]);
*/

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


