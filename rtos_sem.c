#include"includes.h"
#include"uart.h"
#include<util/delay.h>
OS_STK task1_stack[256],task2_stack[256],task3_stack[256]; //,task4_stack[256]; 
OS_EVENT *semph;
void task1(void *data); 
void task2(void *data);
void task3(void *data);
//void task4(void *data);
void inittimer(); 
INT8U err;


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
	//OSTaskCreate(task4, (void *)0, &task4_stack[255], 7);
	semph = OSSemCreate(3);
	
	u1init();
	
	OSStart(); 
	u1txstr("\n ");
}

void task1(void *data){
	data = data; 
	inittimer();
	while(1){ 
		OSSemPend(semph, 0, &err);
		if(err == OS_NO_ERR){
			u1txstr("\nTask1");
			//STimeDly(30);
		}
		OSTimeDly(120);
		err = OSSemPost(semph);
		if(err == OS_NO_ERR){
			u1txstr("\nSemaphore 1 released");
		}	
		//OSTimeDly(122);		
		//OSTaskSuspend(4);
		//u1txstr("\nTask1 after delay");
		}
}
void task2(void *data){
	data = data; 
	while(1){ 
		OSSemPend(semph, 0, &err);
		if(err == OS_NO_ERR){
			u1txstr("\nTask2");
			//STimeDly(30);
		
		OSTimeDly(60);
		err = OSSemPost(semph);
		if(err == OS_NO_ERR){
			u1txstr("\nSemaphore 2 released");
		}
		}	
		//OSTimeDly(122);		
		//OSTaskSuspend(4);
		//u1txstr("\nTask1 after delay");
	}
}
void task3(void *data){
	data = data; 
	while(1){ 
		OSSemPend(semph, 0, &err);
		if(err == OS_NO_ERR){
			u1txstr("\nTask3");
			//STimeDly(30);
		
		OSTimeDly(50);
		err = OSSemPost(semph);
		if(err == OS_NO_ERR){
			u1txstr("\nSemaphore 3 released");
		}	
		}		
		//OSTimeDly(122);		
		//OSTaskSuspend(4);
		//u1txstr("\nTask1 after delay");
	}
}
/*void task4(void *data){
	data = data; 
	while(1){ 
		OSSemPend(semph, 0, &err);
		if(err == OS_NO_ERR){
			u1txstr("\nTask4");
			//STimeDly(30);
		
		OSTimeDly(40);
		err = OSSemPost(semph);
		if(err == OS_NO_ERR){
			u1txstr("\nSemaphore 4 released");
		}	
		}		
		//OSTimeDly(122);		
		//OSTaskSuspend(4);
		//u1txstr("\nTask1 after delay");
	}
} */

