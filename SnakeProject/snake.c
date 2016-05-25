#include "snake.h"
#include "GLCD.h"
#include "stdint.h"
#include "stddef.h"
#include "stm32f10x_cl.h"
#include "core_cm3.h"
#include "system_stm32f10x_cl.h"
#include "cmsis_os.h"
#include "RTX_CM_lib.h"

void createSnake(Snake *snake) {
	snake->x = 5;
	snake->y = 5;
	snake->direction = 1;
	snake->tailSize = 5;
}

void display(void const *argument) {
	for (;;) {
		//display code
		osSignalWait(0x01, osWaitForever);
		osSignalSet(movementThread, 0x01);	
	}
}

void movement(void const *argument) {
	for (;;) {
		osSignalWait(0x01, osWaitForever);
		osSignalSet(scoreThread, 0x01);
		
		//traverse linked list
		struct TailSegment *temp = start; //Move to First Node
		int prevX;
		int prevY;
		do {
			//Do Your Operation
			//Statement 1-N
			temp->x = prevX;
			temp->y = prevY;
			temp = temp->next; //Move Pointer to Next Node

		} while (temp != NULL);
	}
}

void score(void const *argument) {
	for (;;) {
		osSignalWait(0x01, osWaitForever);
		osSignalSet(displayThread, 0x01);
	}
}

/*Main - initialise, start RTX kernel and play game */
int main(void) {
	SystemCoreClockUpdate();
	GLCD_Initialize();
	GLCD_SetBackColor(Black);
	GLCD_Clear(Black);
	GLCD_SetTextColor(White);
	
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