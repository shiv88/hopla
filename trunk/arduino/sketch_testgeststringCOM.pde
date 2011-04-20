#include <DHT22.h>

// Data wire is plugged into port 7 on the Arduino
// Connect a 4.7K resistor between VCC and the data pin (strong pullup)
#define DHT22_PIN 7

#define DBG_FIRSTLOOP 0x0001
#define DBG_PARSECOM  0x0002
#define DBG_GETSTRINGCOM 0x0004

char debuglevel=  DBG_PARSECOM | DBG_GETSTRINGCOM ;
#define CMDLINEMAXLEN 32
static char cmdline[CMDLINEMAXLEN];
static char argcnt;
static char argvect[6];
static char chptr=0;

// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);

// ritorna 1 se la stringa e' completata con successo con un \n
// ritorna 0 se sta ancora leggendo la string
// ritorna <0 per errori
char GetstringCOM()
{
char *p;
char c, i, retval;

  if (Serial.available() > 0)
  {
    c= Serial.read(); // Read the received character.
    if ( (isalnum(c) || isspace(c) || (c == ':')) && (c!= 13) ) 
    {
      cmdline[chptr]=c;
      chptr++;

      if (debuglevel & DBG_GETSTRINGCOM)
      {
        Serial.print("c:");
        Serial.print (c);
        Serial.print (" cmdline[]:");
        Serial.print (cmdline[chptr-1]);
        Serial.print (" chptr");
        Serial.println (chptr);

      }

      if (chptr==CMDLINEMAXLEN) //overflow
      {
        chptr=0;
        cmdline[0]='\0';
	if (debuglevel & DBG_GETSTRINGCOM) 
          Serial.println("Error 1- cmdline overflow");
        return (-1);
      }
    }    
    else if (c==13) //enter fine della riga di comando
    {
      cmdline[chptr]='\0';
      chptr=0;
      if (debuglevel & DBG_GETSTRINGCOM)
      {
        Serial.print("cmdline=");
        Serial.println(cmdline);
      }
      return (1);	
    }
  }
  return (0);
}

struct cmd_descr {
 char cmd[10];
 char argnum;
 };
 
struct cmd_descr commandlist[]= { 
{"nop", 0 },
{"readtemp", 0},
{"readhum", 0}
};


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
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("DHT22 Library Demo with COM parser");
}

void loop(void)
{ 
  char i;
  DHT22_ERROR_t errorCode;

  if (GetstringCOM() > 0)
  { 
    Serial.print ("Comando letto:");
    Serial.println (cmdline);
    i=ParseCOM(cmdline, &argcnt, argvect);
      Serial.print ("Comando ParseCOM:");
      Serial.println (i,DEC);  
}
  
  
}
