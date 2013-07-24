#include"VT102lib.h"
#include"myuart.h"
#include<avr/io.h>
#include<util/delay.h>
void main(){
	UART_config(9600);
	DispClrScr(COLOR_WHITE, COLOR_WHITE);
	while(1){
	DispHBar(10,5,16,'A',COLOR_BLUE,COLOR_RED);
	_delay_ms(500);
	DispHBar(10,5,16,'B',COLOR_RED,COLOR_BLUE);
	_delay_ms(500);
	}
}
