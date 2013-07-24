#include"includes.h"
#include"uart.h"
#include<util/delay.h>
OS_STK task1_stack[256],task2_stack[256],task3_stack[256]; 

OS_EVENT *mymutex;
OS_EVENT *mymbox;
void task1(void *data); 
void task2(void *data);
void task3(void *data);
void inittimer(); 
INT8U err;
INT8U mymsg[45] = "\tMessage to be transferred to Mbox";

void inittimer(){ 
	TCNT0=0;
	TCCR0=0x07; 
	TIMSK=1;
}

void main(){
	OSInit(); 
	OSTaskCreate(task1, (void *)0, &task1_stack[255], 5); 
	OSTaskCreate(task2, (void *)0, &task2_stack[255], 6);
	OSTaskCreate(task3, (void *)0, &task3_stack[255], 7);
	mymutex = OSMutexCreate(4,&err);
	mymbox = OSMboxCreate((void *)0);
	u1init();
	DDRC=0xff;
	OSStart(); 
}

void task1(void *data){
	data = data; 
	inittimer();
	INT8U errmutex, errmbox;
	while(1){ 
		PORTC=~(1<<0);
		u1txstr("\nTask1");
		OSMutexPend(mymutex, 0, &errmutex);
		if(err == OS_NO_ERR){
			errmbox=OSMboxPost(mymbox, mymsg);
			if(errmbox = OS_NO_ERR){
				u1txstr("\nMessage transferred to MBox");
			}			
			OSTimeDly(5);
			PORTC=0xff;
		}
		OSMutexPost(mymutex);
		//u1txstr("\nMutex released by Task 1");
		OSTimeDly(61);		
	}
}
void task2(void *data){
	data = data; 
	INT8U errmutex, errmbox;
	void *rcvmsg;	
	while(1){ 
		PORTC=~(1<<1);
		OSMutexPend(mymutex, 0, &errmutex);
		if(errmutex == OS_NO_ERR)
		{
			u1txstr("\nMutex acq by Task2");
			rcvmsg=OSMboxPend(mymbox, 10, errmbox);
			if(errmbox==OS_NO_ERR){
				u1txstr("\nMessage read by 2:");
				u1txstr(rcvmsg);
			}
		}
		OSMutexPost(mymutex);
		OSTimeDly(183);
	}
}		
void task3(void *data){
	data = data; 
	INT8U errmutex, errmbox;
	void *rcvmsg;	
	while(1){ 
		PORTC=~(1<<2);
		OSMutexPend(mymutex, 0, &errmutex);
		if(errmutex == OS_NO_ERR)
		{
			u1txstr("\nMutex acq by Task3");
			rcvmsg=OSMboxPend(mymbox, 10, errmbox);
			if(errmbox==OS_NO_ERR){
				u1txstr("\nMessage read by 3:");
				u1txstr(rcvmsg);
			}
		}
		OSMutexPost(mymutex);
		OSTimeDly(183);
	}
}		


