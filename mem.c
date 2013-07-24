#include"includes.h"
#include"uart.h"
OS_STK task1_stack[256],task2_stack[256]; 
OS_MEM *memory;
INT8U buff[2][20]; //memorypartition
INT8U *msg, *ptr1;
INT8U errmem;
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
	memory = OSMemCreate(&buff[0][0], 2, 10, &errmem);	
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
	INT8U buf[15];
	INT8U *t1msg = "AAA T1 AAA";
	while(1){ 
		PORTC=0xAA;
		u1txstr("\n\rEntered into task 1");
		if(!(PIND&(1<<PD6))){
			msg = OSMemGet(memory, &err);
			if(msg!=(INT8U *)0){
				sprintf(buf, "\nMemory T1 %p", msg);
				u1txstr(buf);
				u1txstr("\nBlock of data obtained");
				ptr1 = msg;
				strcpy(msg, t1msg);
				u1txstr(ptr1);
				u1txstr("\nMessage stored");
			}
		}
		u1txstr("\nLeaving task 1");
		OSTimeDly(61);
	}
}
void task2(void *data){
	data = data; 
	INT8U err, buf[15];
	while(1){ 
		PORTC=0x55;
		u1txstr("\n\rEntered into task 2");		
		if(!(PIND&(1<<PD7))){
			sprintf(buf, "\nMemory T1 %p", ptr1);
			u1txstr(buf);
			u1txstr("\nData read from memory block = ");
			u1txstr(ptr1);
			err = OSMemPut(memory, (void *)ptr1);
			if(err == OS_NO_ERR){
				u1txstr("\nMemory removed");
			}
		}
		u1txstr("\nLeaving task 2");
		OSTimeDly(61);
	}
}
