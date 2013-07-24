#include"includes.h"
#include"uart.h"
OS_STK task1_stack[256]; // init stack
void task1(void *data); //task prototype
void inittimer(); //timer init prototype

//init timer and interrupt. make changes in os_cfg.h for ticks per second
void inittimer(){ //this function called in highest priority task
	TCNT0=0;
	TCCR0=0x07; // divide by 1024. Hence, 61 ticks per second. 
	TIMSK=1;
}

void main(){
	OSInit(); //init OS. call it before OSStart()
	
	//create tasks, mutex, semaphore etc here
	OSTaskCreate(task1, (void *)0, &task1_stack[255], 4); //(pointer to task, pointer to data. (void *)0 <-- pointer of type void. used if no data to be passed
								//, pointer to TOS, priority -> from 4 to 59. 0->3 and 60->63 reserved.
	//other tasks created here.
	//.
	//.
	
	//initialize resources here
	u1init();
	DDRC=0xff;
	DDRD&=~((1<<6)|(1<<7));
	PORTD|=((1<<6)|(1<<7));
	
	OSStart(); //starts multitasking
}

void task1(void *data){
	data = data; //passing the data but not used. to suppress warning, this is used. 
	inittimer();
	while(1){ //all tasks must have infinite loop
	if(!(PIND&(1<<6)))
		PORTC=0x00;
	else if(!(PIND&(1<<7)))
		PORTC=0xff;
	}	
}

