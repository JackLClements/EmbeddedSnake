#ifndef _SNAKE_H
#define _SNAKE_H

typedef struct{
	int x;
	int y;
	int direction; //left/right/up/down 1/2/3/4
	int tailSize;
	TailSegment *next;
	TailSegment *last;
} Snake;

typedef struct{
	int x;
	int y;
	struct TailSegment *next;
} TailSegment;

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
struct Snake player;
//Threads, yo
osThreadId displayThread;
osThreadId scoreThread;
osThreadId movementThread;
/*Function Prototypes*/
void display(void);
void updateGameLogic(void);
void controls(void);
void updateTail(void);
void updateScore(void);

#endif