#include"includes.h"
#include"uart.h"
#define FLAG_BIT1 (1<<3)
#define FLAG_BIT2 (1<<4)
#define FLAG_BIT_CHK (1<<3)|(1<<4)
OS_STK task1_stack[256],task2_stack[256], task3_stack[256]; 
OS_FLAG_GRP *myflag;
void task1(void *data); 
void task2(void *data);
void task3(void *data);
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
	OSTaskCreate(task3, (void *)0, &task3_stack[255], 6);
	myflag = OSFlagCreate(0, &errflag);
	u1init();
	DDRC = 0xff;	
	DDRD = 0x00;
	PORTD = 0xff;
	OSStart(); 
	
}

void task1(void *data){
	data = data; 
	inittimer();
	INT8U err;
	OS_FLAGS value;
	while(1){ 
		PORTC=0xFE;
		if(!(PIND&(1<<6))){
			u1txstr("\nSwitch 1 pressed");			
			value = OSFlagPost(myflag, FLAG_BIT1, OS_FLAG_SET, &err);
			if(err == OS_NO_ERR){
				u1txstr("\nFlag set in task 1");
			}
		}
		else{
			u1txstr("\nSwitch 1 not pressed");
			value = OSFlagPost(myflag, FLAG_BIT1, OS_FLAG_CLR, &err);
			if(err == OS_NO_ERR){
				u1txstr("\nFlag cleared in task 1");
			}
		}
		OSTimeDly(61);
	}
}
void task2(void *data){
	data = data; 
	inittimer();
	INT8U err;
	OS_FLAGS value;
	while(1){ 
		PORTC=0xFD;
		if(!(PIND&(1<<7))){
			u1txstr("\nSwitch 2 pressed");			
			value = OSFlagPost(myflag, FLAG_BIT2, OS_FLAG_SET, &err);
			if(err == OS_NO_ERR){
				u1txstr("\nFlag set in task 2");
			}
		}
		else{
			u1txstr("\nSwitch 2 not pressed");
			value = OSFlagPost(myflag, FLAG_BIT2, OS_FLAG_CLR, &err);
			if(err == OS_NO_ERR){
				u1txstr("\nFlag cleared in task 2");
			}
		}
		OSTimeDly(122);	
	}
}
void task3(void *data){
	data = data; 
	INT8U err;
	OS_FLAGS whichflag;
	INT8U temp[30];
	while(1){ 
		PORTC=0xFB;
		whichflag = OSFlagPend(myflag, FLAG_BIT_CHK, OS_FLAG_WAIT_SET_ANY, 61, &err); 
		// '+ OS_FLAG_CONSUME' after OS_FLAG_WAIT_SET_ALL clears the flags after the conditions are met. (without quotes)
		if(err == OS_NO_ERR){
			if(whichflag == 0x18){
				u1txstr("\nCorrect flag condition\t\t");
				sprintf(temp, "Flags = %p", whichflag);
				u1txstr(temp);
			}
			else{
				u1txstr("\nIncorrect flag condition\t");
				sprintf(temp, "Flags = %p", whichflag);
				u1txstr(temp);
			}
		}
		else{
			u1txstr("\nIncorrect flag condition\t");
			sprintf(temp, "Flags = %p", whichflag);
			u1txstr(temp);
		}
		OSTimeDly(30);
	}
}
		

