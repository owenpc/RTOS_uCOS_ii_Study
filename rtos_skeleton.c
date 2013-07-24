//change line 56,57/62,63 of makefile if using windows/ubuntu
#include"includes.h"
OS_STK task1_stack[256],task2_stack[256]; // init stack //see os_cpu.h for data types.
void task1(void *data1); //task prototype
void task2(void *data2);
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
								// two tasks with same priority cannot be initialized. 
	OSTaskCreate(task2, (void *)0, &task2_stack[255], 5);
	//other tasks created here.
	//.
	//.
	
	//initialize resources here
	
	OSStart(); //starts multitasking
}

void task1(void *data){
	data1 = data1; //passing the data but not used. to suppress warning, this is used. 
	inittimer();
	while(1){ //all tasks must have infinite loop
	}
}
void task1(void *data){
	data2 = data2; //passing the data but not used. to suppress warning, this is used. 
	while(1){ //all tasks must have infinite loop
	}
}
