#ifndef _SNAKE_H
#define _SNAKE_H

typedef struct{
	int x;
	int y;
	int tailSize;
} Snake;

typedef struct{
	int score;
	int gameOver;
	Snake gameSnake;
} GameInfo;

#endif