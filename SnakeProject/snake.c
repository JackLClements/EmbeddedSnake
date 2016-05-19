#include "snake.h"

void createSnake(Struct Snake *snake){
	snake->x = 5;
	snake->y = 5;
	snake->direction = 1;
	snake->tailSize = 5;
}

void display(void const *argument){
	for(;;){
		//display code
		osSignalWait(0x01, osWaitForever);
		osSignalSet(movementThread, 0x01);
	}
}

void movement(void const *argument){
	for(;;){
		osSignalWait(0x01, osWaitForever);
		osSignalSet(scoreThread, 0x01);
	}
}

void score(void const *argument){
	for(;;){
		osSignalWait(0x01, osWaitForever);
		osSignalSet(displayThread, 0x01);
	}
}

/*Main - initialise, start RTX kernel and play game */
int main(void){
	SystemCoreClockUpdate();
	GLCD_setup();
	mut_GLCD = ofMutexCreate(osMutex(mut_GLCD));
	
	createSnake(*player);
	//wait
	//osSignalWait(0x01, osWaitForever);
	
	//update ?
	
	scoreThread = osThreadCreate(osThread(score), NULL);
	movementThread = osThreadCreate(osThread(movement), NULL);
	displayThread = osThreadCreate(osThread(display), NULL);
	
	osSignalSet(displayThread, 0x01); //start first thread
	//
	/*
	osSignalSet(scoreThread, 0x01);
	osSignalSet(movementThread, 0x01);
	osSignalSet(displayThread, 0x01);
	*/
	
	
}