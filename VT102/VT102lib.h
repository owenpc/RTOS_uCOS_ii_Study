/*****************************************************************
Filename	: VT102lib.h
Target		: ATmega128/64
Frequency	: 16Mhz
Compiler	: avr-gcc
Author		: TEAM ThinkLABS
Description	: this is VT102 Library
*****************************************************************/

#ifndef VT102lib_h
#define VT102lib_h

#include "myuart.h"

#define  COLOR_BLACK     0                       /* VT102 Color Codes                                  */
#define  COLOR_RED       1
#define  COLOR_GREEN     2
#define  COLOR_YELLOW    3
#define  COLOR_BLUE      4
#define  COLOR_MAGENTA   5
#define  COLOR_CYAN      6
#define  COLOR_WHITE     7

/*-------------------------------------------------------------------------------
---------------------------Function Prototype------------------------------------
-------------------------------------------------------------------------------*/


// Clears the screen -------  Parameter: foreground and background color of the scree.
void DispClrScr (unsigned char fgcolor, unsigned char bgcolor);


//Passing the attribute to the character -------  Parameter: foreground and background color of the character.
void Attribute (unsigned char fgcolor, unsigned char bgcolor);


//Displays the string on the specified location on the screen ----- Parameter: (X-axis & Y-axis co-ordinate), the base address of the string, foreground and background color of the character.
void DispStr (unsigned char x, unsigned char y, unsigned char *s, unsigned char fgcolor, unsigned char bgcolor);


//Displays the character on the specified location on the screen ----- Parameter: (X-axis & Y-axis co-ordinate), ascii value of the character, foreground and background color of the character.
void DispChar (unsigned char x, unsigned char y, unsigned char c, unsigned char fgcolor, unsigned char bgcolor);


//Displays a vertical bar from the specified location (x,y) to location (x, (y+len))----Parameter: (X-axis & Y-axis co-ordinate), length of the bar in blocks ascii value of the character for displaying bar, foreground and background color of the character.
void DispVBar (unsigned char x, unsigned char y, unsigned char len,unsigned char c, unsigned char fgcolor, unsigned char bgcolor);


//Displays a Horizontal bar from the specified location (x,y) to location ( (x+len), y)----Parameter: (X-axis & Y-axis co-ordinate), length of the bar in blocks ,ascii value of the character for displaying bar, foreground and background color of the character.
void DispHBar (unsigned char x, unsigned char y, unsigned char len,unsigned char c, unsigned char fgcolor, unsigned char bgcolor);


//Draws a line from co-ordinate (x1,y1) to co-ordinate (x2,y2)------Parameter: (X1-axis & Y1-axis co-ordinate), (X2-axis & Y2-axis co-ordinate), ascii value of the character for displaying bar, foreground and background color of the character.
void DispStBar (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char c, unsigned char fgcolor, unsigned char bgcolor);


//Draws a cross line from co-ordinate (x1,y1) to co-ordinate (x2,y2)------Parameter: (X1-axis & Y1-axis co-ordinate), (X2-axis & Y2-axis co-ordinate), ascii value of the character for displaying bar, foreground and background color of the character.
void DispCrsBar (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char c, unsigned char fgcolor, unsigned char bgcolor);


/*-------------------------------------------------------------------------------
---------------------------Function definition-----------------------------------
-------------------------------------------------------------------------------*/

void Attribute (unsigned char fgcolor, unsigned char bgcolor)
{
    UART_Transmit_char(0x1b);
    UART_Transmit_char('[');
    UART_Transmit_num(30 + fgcolor);
    UART_Transmit_char(';');
    UART_Transmit_num(40 + bgcolor);
    UART_Transmit_char('m');
}

void DispStr (unsigned char x, unsigned char y, unsigned char *s, unsigned char fgcolor, unsigned char bgcolor)
{
    Attribute(fgcolor, bgcolor);
    UART_Transmit_char(0x1B);
    UART_Transmit_char('[');
    UART_Transmit_num(y);
    UART_Transmit_char(';');
    UART_Transmit_num(x);
    UART_Transmit_char('H');
    UART_Transmit_string(s);
}

void DispChar (unsigned char x, unsigned char y, unsigned char c, unsigned char fgcolor, unsigned char bgcolor)
{
    Attribute(fgcolor, bgcolor);
    UART_Transmit_char(0x1B);
    UART_Transmit_char('[');
    UART_Transmit_num(y);
    UART_Transmit_char(';');
    UART_Transmit_num(x);
    UART_Transmit_char('H');
    UART_Transmit_char(c);
}

void DispVBar (unsigned char x, unsigned char y, unsigned char len,unsigned char CHAR, unsigned char fgcolor, unsigned char bgcolor)
{
    while(len!=0)
	{
		DispChar (x,y,CHAR,fgcolor,bgcolor);
		y++;
		len--;
	}
}

void DispHBar (unsigned char x, unsigned char y, unsigned char len,unsigned char CHAR, unsigned char fgcolor, unsigned char bgcolor)
{
    while(len!=0)
	{
		DispChar (x,y,CHAR,fgcolor,bgcolor);
		x++;
		len--;
	}
}

void DispStBar (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char c, unsigned char fgcolor, unsigned char bgcolor)
{
	if(x1==x2)
	{
		do
		{
			if(y1>y2)
			{
			DispChar (x2,y2,c,fgcolor,bgcolor);y2++;
			}
			else if(y2>y1)
			{
			DispChar (x1,y1,c,fgcolor,bgcolor);y1++;
			}
		}while(y1!=y2);
	}
	else if(y1==y2)
	{
		do
		{
			if(x1>x2)
			{
			DispChar (x2,y2,c,fgcolor,bgcolor);x2++;
			}
			else if(x2>x1)
			{
			DispChar (x1,y1,c,fgcolor,bgcolor);x1++;
			}
		}while(x1!=x2);
	}
}

void DispCrsBar (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char c, unsigned char fgcolor, unsigned char bgcolor)
{
	if( ((x1-x2)==(y1-y2)) || ((x2-x1)==(y2-y1)) || ((x1-x2)==(y2-y1)) || ((x2-x1)==(y1-y2)) )
	{
		if( ( (x1>x2) && (y1<y2) ) )
		{
		do
		{
		x1--;
		y1++;
		}while(y1<=y2);
		}
		
		else if( ( (x1<x2) && (y1>y2) ) )
		{
		do
		{
		DispChar (x1,y1,c,fgcolor,bgcolor);
		x1++;
		y1--;
		}while(y1>=y2);
		}
		
		else if( ( (x1<x2) && (y1<y2) ) )
		{
		do
		{
		DispChar (x1,y1,c,fgcolor,bgcolor);
		x1++;
		y1++;
		}while(y1<=y2);
		}		
		
		else if( ( (x1>x2) && (y1>y2) ) )
		{
		do
		{
		DispChar (x1,y1,c,fgcolor,bgcolor);
		x1--;
		y1--;
		}while(y1>=y2);
		}
	}
}

void DispClrScr (unsigned char fgcolor, unsigned char bgcolor)
{
    Attribute(fgcolor,bgcolor);
    UART_Transmit_string("\x1B[2J");
}

#endif
