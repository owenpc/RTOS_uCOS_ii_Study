#include"includes.h"
#include"uart.h"
#include<util/delay.h>
OS_STK task1_stack[256],task2_stack[256]; 
void task1(void *data); 
void task2(void *data);
void inittimer(); 


void inittimer(){ 
	TCNT0=0;
	TCCR0=0x07; 
	TIMSK=1;
}

void main(){
	OSInit(); 
	OSTaskCreate(task1, (void *)0, &task1_stack[255], 4); 
	OSTaskCreate(task2, (void *)0, &task2_stack[255], 5);
	
	u1init();
	
	OSStart(); 
}

void task1(void *data){
	data = data; 
	inittimer();
	while(1){ 
		u1txstr("\nTask1 before delay");
		OSTimeDly(61);
		//OSTaskSuspend(4);
		u1txstr("\nTask1 after delay");
		}
}
void task2(void *data){
	data = data; 
	while(1){ 
		u1txstr("\nTask2 before delay");
		OSTimeDly(183);		
		//OSTaskResume(4);
		u1txstr("\nTask2 after delay");
		//_delay_ms(1000);
	}
}
