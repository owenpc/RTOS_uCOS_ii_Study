#include"includes.h"
#include"uart.h"
#include<util/delay.h>
OS_STK task1_stack[256],task2_stack[256];

OS_EVENT *mymutex;
OS_EVENT *myq;
void task1(void *data); 
void task2(void *data);
void inittimer(); 
INT8U err;
INT8U mymsg[45] = "\tMessage to be transferred to Mbox";
void *qmsg[5]; //[45];

void inittimer(){ 
	TCNT0=0;
	TCCR0=0x07; 
	TIMSK=1;
}

void main(){
	OSInit(); 
	OSTaskCreate(task1, (void *)0, &task1_stack[255], 5); 
	OSTaskCreate(task2, (void *)0, &task2_stack[255], 6);
	mymutex = OSMutexCreate(4,&err);
	myq = OSQCreate(qmsg, 10);
	u1init();
	DDRC=0xff;
	OSStart(); 
}

void task1(void *data){
	data = data; 
	inittimer();
	INT8U errmutex, errq;
	while(1){ 
		PORTC=~(1<<0);
		u1txstr("\nTask1");
		OSMutexPend(mymutex, 0, &errmutex);
		if(err == OS_NO_ERR){
			errq=OSQPost(myq, mymsg);
			if(errq == OS_NO_ERR){
				u1txstr("\nMessage transferred to Queue");
			}
			else if(errq == OS_Q_FULL){
				u1txstr("\nQueue is full!");
			}			
		}
		OSMutexPost(mymutex);
		//u1txstr("\nMutex released by Task 1");
		OSTimeDly(61);		
	}
}
void task2(void *data){
	data = data; 
	INT8U errmutex, errq;
	void *rcvmsg;	
	while(1){ 
		PORTC=~(1<<1);
		OSMutexPend(mymutex, 0, &errmutex);
		if(errmutex == OS_NO_ERR)
		{
			u1txstr("\nMutex acq by Task2");
			rcvmsg=OSQPend(myq, 10, errq);
			if(errq==OS_NO_ERR){
				u1txstr("\nMessage read by 2:");
				u1txstr(rcvmsg);
			}
			else{ //if(errq == OS_Q_FULL){
				u1txstr("\nNo message in Queue!");
			}
		}
		OSMutexPost(mymutex);
		OSTimeDly(183);
	}
}		

