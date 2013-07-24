#include"includes.h"
#include"uart.h"
#include<util/delay.h>
OS_STK task1_stack[256],task2_stack[256],task3_stack[256],task4_stack[256]; 
void task1(void *data); 
void task2(void *data);
void task3(void *data);
void task4(void *data); //need to change max number of tasks in os_cfg.h
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
	OSTaskCreate(task3, (void *)0, &task3_stack[255], 6);
	OSTaskCreate(task4, (void *)0, &task4_stack[255], 7);
	
	u1init();
	
	OSStart(); 
}

void task1(void *data){
	data = data; 
	inittimer();
	while(1){ 
		u1txstr("\n1before");
		_delay_ms(2000);
		OSTaskSuspend(4);
		u1txstr("\n1after");
		_delay_ms(2000);
	}
}
void task2(void *data){
	data = data; 
	while(1){ 
		u1txstr("\n2before");
		_delay_ms(2000);		
		OSTaskSuspend(5);
		u1txstr("\n2after");
		_delay_ms(2000);
	}
}
void task3(void *data){
	data = data; 
	while(1){ 
		u1txstr("\n3before");
		_delay_ms(2000);		
		OSTaskSuspend(6);
		u1txstr("\n3after");
		_delay_ms(2000);
	}
}
void task4(void *data){
	data = data; 
	while(1){ 
		u1txstr("\n4before");
		_delay_ms(2000);		
		u1txstr("\nresume1");		
		OSTaskResume(4);
		u1txstr("\nresume2");
		OSTaskResume(5);
		u1txstr("\nresume3");
		OSTaskResume(6);
		u1txstr("\n4after");
		_delay_ms(2000);
	}
}
