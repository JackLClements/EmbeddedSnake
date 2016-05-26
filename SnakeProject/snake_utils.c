#include "snake_utils.h"
#include "snake.h"
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

void newApple(){
	int newX, newY;
	newX = rand();
	newY = rand();
	if(newX > MAX_X){
		newX = newX - MAX_X;
	}
	if(newY > MAX_Y){
		newY = newY - MAX_Y;
	}
	apple1.x = newX;
	apple1.y = newY;
	//create new apple with these coordinates
}

void eraseApple(){
	GLCD_DrawChar(apple1.x, apple1.y, ' ');
}

void drawApple(){
	GLCD_DrawBitmap ( thisGame.ball.x, thisGame.ball.y, gimp_image.width,gimp_image.height, gimp_image.pixel_data);
}

void drawHead(){
	
}

void drawBody(){
	
}

void eraseHead(){
	
}

void eraseBody(){
	
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
	
}

