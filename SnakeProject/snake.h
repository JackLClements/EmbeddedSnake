#ifndef _SNAKE_H
#define _SNAKE_H
#include "GLCD_SPI_STM32F10x.c"
#include "cmsis_os.h"
#include "stdint.h"
#include "stddef.h"

typedef struct{
	int x;
	int y;
	struct TailSegment *next;
} TailSegment;

typedef struct SNAKES{
	int x;
	int y;
	int direction; //left/right/up/down 1/2/3/4
	int tailSize;
	TailSegment *next;
	TailSegment *last;
} Snake;

typedef struct{
	int score;
	int gameOver;
	Snake gameSnake;
} GameInfo;

typedef struct{
	int x;
	int y;
} Apple;

//variables
Snake snake1;
//Threads, yo

osThreadId displayThread;
osThreadId scoreThread;
osThreadId movementThread;

/*Function Prototypes*/
void display(void const *argument);
void updateGameLogic(void);
void controls(void);
void updateTail(void);
void updateScore(void);

#endif