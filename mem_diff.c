#include"includes.h"
#include"uart.h"
OS_STK task1_stack[256],task2_stack[256],task3_stack[256],task4_stack[256]; 
OS_MEM *memory;
INT8U buff[3][20]; //memorypartition
INT8U *msg, *ptr1, *ptr2, *ptr3;
INT8U errmem;
int a,b,c;
void task1(void *data); 
void task2(void *data);
void task3(void *data);
void task4(void *data);
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
	memory = OSMemCreate(&buff[0][0], 3, 20, &errmem); //keep number of bytes/block same as that defined in memory partition	
	u1init();
	DDRC = 0xff;	
	DDRD = 0x00;
	PORTD = 0xff;
	DDRE = 0x00;
	PORTE = 0xff;
	OSStart(); 	
}
void task1(void *data){
	data = data; 
	inittimer();
	INT8U err;
	INT8U buf[15];
	INT8U *t1msg = "AAA T1 AAA";
	//INT8U *ptr1;
	while(1){ 
		//a=0;		
		PORTC=0xFE;
		u1txstr("\n\rEntered into task 1");
		if(!(PIND&(1<<PD6))){
			a=1;			
			msg = OSMemGet(memory, &err);
			if(msg!=(INT8U *)0){
				sprintf(buf, "\nMemory T1 %p", msg);
				u1txstr(buf);
				u1txstr("\nBlock of data obtained ");
				ptr1 = msg;
				strcpy(msg, t1msg);
				u1txstr(ptr1);
				u1txstr("\nMessage stored\n");
				//u1txstr(ptr1);
			}
		}
		u1txstr("\nLeaving task 1");
		OSTimeDly(61);
	}
}
void task2(void *data){
	data = data; 
	//inittimer();
	INT8U err;
	INT8U buf[15];
	INT8U *t2msg = "BBB T2 BBB";
	//INT8U *ptr2;
	while(1){ 
		//b=0;		
		PORTC=0xFD;
		u1txstr("\n\rEntered into task 2");
		if(!(PIND&(1<<PD7))){
			b=1;			
			msg = OSMemGet(memory, &err);
			if(msg!=(INT8U *)0){
				sprintf(buf, "\nMemory T2 %p", msg);
				u1txstr(buf);
				u1txstr("\nBlock of data obtained ");
				ptr2 = msg;
				strcpy(msg, t2msg);
				u1txstr(ptr2);
				u1txstr("\nMessage stored");
			}
		}
		u1txstr("\nLeaving task 2");
		OSTimeDly(61);
	}
}
void task3(void *data){
	data = data; 
	//inittimer();
	INT8U err;
	INT8U buf[15];
	INT8U *t3msg = "CCC T3 CCC";
	//INT8U *ptr3;
	while(1){ 
		//c=0;		
		PORTC=0xFC;
		u1txstr("\n\rEntered into task 3");
		if(!(PINE&(1<<PE6))){
			c=1;			
			msg = OSMemGet(memory, &err);
			if(msg!=(INT8U *)0){
				sprintf(buf, "\nMemory T3 %p", msg);
				u1txstr(buf);
				u1txstr("\nBlock of data obtained ");
				ptr3 = msg;
				strcpy(msg, t3msg);
				u1txstr(ptr3);
				u1txstr("\nMessage stored");
			}
		}
		u1txstr("\nLeaving task 3");
		OSTimeDly(61);
	}
}
void task4(void *data){
	data = data; 
	INT8U err, buf[15];
	while(1){ 
		PORTC=0x00;
		u1txstr("\n\rEntered into task 4");		
		if(!(PINE&(1<<PE7))){
			if(a==1){
				sprintf(buf, "\nMemory T1 %p", ptr1);
				u1txstr(buf);
				u1txstr("\nData read from memory block 1 = ");
				u1txstr(ptr1);
				err = OSMemPut(memory, (void *)ptr1);
				if(err == OS_NO_ERR){
					u1txstr("\nMemory from block 1 removed");
				}
				a=0;
			}
			if(b==1){
				sprintf(buf, "\nMemory T2 %p", ptr2);
				u1txstr(buf);
				u1txstr("\nData read from memory block 2 = ");
				u1txstr(ptr2);
				err = OSMemPut(memory, (void *)ptr2);
				if(err == OS_NO_ERR){
					u1txstr("\nMemory from block 2 removed");
				}
				b=0;
			}
			if(c==1){
				sprintf(buf, "\nMemory T3 %p", ptr3);
				u1txstr(buf);
				u1txstr("\nData read from memory block 3 = ");
				u1txstr(ptr3);
				err = OSMemPut(memory, (void *)ptr3);
				if(err == OS_NO_ERR){
					u1txstr("\nMemory from block 3 removed");
				}
				c=0;
			}
		}
		u1txstr("\nLeaving task 4");
		OSTimeDly(61);
	}
}
