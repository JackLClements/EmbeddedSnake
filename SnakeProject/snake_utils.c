#include "snake_utils.h"
#include "snake.c"
#include "ADC.h"
#include "GLCD.h"
#include "stdio.h"
#include <stdlib.h>

//Initialise game
void setupGame(){
	
}

void updateSnakeHead(){
	
}

void updateSnakeBody(){
	
}

void drawNewApple(){
	int newX, newY;
	newX = rand();
	newY = rand();
	if(newX > MAX_X){
		newX = newX - MAX_X;
	}
	if(newY > MAX_Y){
		newY = newY - MAX_Y;
	}
	//create new apple with these coordinates
}

void updateScore(){
	//if collision with apple
	//update score
	//glcd display string
}

void checkCollision(){
	//if outside bounds
	if ((Snake.snake.x<0) || Snake.snake.y<0 || Snake.snake.x>MAX_X || Snake.snake.y>MAX_Y){
		//collision
		//game over
	}
	//3 checks
	//if colliding with tail, do node-to-node traversal for this
	//if colliding with apple
	if((Snake.snake.x == Apple.apple.x) + (Snake.snake.y == Apple.apple.y)){
		//remove apple
		updateScore();
		drawNewApple();
	}
	//http://www.c4learn.com/data-structure/traversing-through-singly-linked-list/
}

