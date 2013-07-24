#include"includes.h"
#include"uart.h"
#define FLAG_BIT (1<<1)
OS_STK task1_stack[256],task2_stack[256]; 
OS_FLAG_GRP *myflag;
void task1(void *data); 
void task2(void *data);
INT8U errflag;
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
	myflag = OSFlagCreate(0, &errflag);
	u1init();
	DDRC = 0xff;	
	OSStart(); 
	
}

void task1(void *data){
	data = data; 
	inittimer();
	INT8U err;
	OS_FLAGS value;
	while(1){ 
		PORTC=0xAA;
		value = OSFlagPost(myflag, FLAG_BIT, OS_FLAG_SET, &err);
		if(err == OS_NO_ERR){
			u1txstr("\nFlag updated");
		}
		OSTimeDly(61);	
	}
}
void task2(void *data){
	data = data; 
	INT8U err, msg[30];
	OS_FLAGS whichflag, currflagval;
	INT8U temp[30];
	while(1){ 
		PORTC=0x55;
		whichflag = OSFlagPend(myflag, FLAG_BIT, OS_FLAG_WAIT_SET_ANY, 0, &err);
		if(err == OS_NO_ERR){
			u1txstr("\nFlag read");
			sprintf(temp, "\nFlags = %p", whichflag);
			u1txstr(temp);
		}
		OSTimeDly(61);
	}
}
		

