/*---------------------------------------------------
 * Recipe   RTOS_Pong_c8v0
 * Name:    pong_utils.c
 * Purpose: Pong Prototype - CMSIS-RTOS Version
 *---------------------------------------------------
 *
 * Modification History
 * 06.02.14 Created
 * 20.10.15 Modified for RTOS
 * 26.01.16 Updated for CMSIS 2.0
 *
 * Dr Mark Fisher, CMP, UEA, Norwich, UK
 *--------------------------------------------------*/

#include "stm32f7xx_hal.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"
#include "ball.c"
#include <stdlib.h>
//#include "custom_font.h"
#include "pong_utils.h"

/* Globals */
extern GLCD_FONT     GLCD_Font_16x24;
extern GLCD_FONT     GLCD_customFont_16x24;
extern GameInfo thisGame;
BallInfo init_pstn;

/****************************************************
*  game_Init()
*  Initialize some game parameters.
*****************************************************/
void game_Initialize(void) {
	thisGame.apple.x = (WIDTH-CHAR_W)/2;
	thisGame.apple.y = (HEIGHT-CHAR_H)/2;
	thisGame.apple.score = 50;
	thisGame.snake.direction = 1;
	thisGame.snake.x = 5;
	thisGame.snake.y = 5;
	/*
	thisGame.ball.dirn = 1;
  thisGame.ball.x = (WIDTH-CHAR_W)/2;
  thisGame.ball.y = (HEIGHT-CHAR_H)/2;
	thisGame.p1.x = 0;
	thisGame.p1.y = 0;
	*/
}

void erase_ball(void) {
  //GLCD_DrawChar ( thisGame.ball.x, thisGame.ball.y, ' '); 	
}

void draw_ball(void) {
  //GLCD_DrawChar ( thisGame.ball.x, thisGame.ball.y, 0x81); 
	GLCD_DrawBitmap ( thisGame.apple.x, thisGame.apple.y, gimp_image.width, gimp_image.height, gimp_image.pixel_data);
}

/****************************************************
* update_player(unsigned int *)
* Read the ADC and draw the player 1's paddle				
*****************************************************/
void update_player(void) {
  //int paddleValue;
  //static int lastValue = 0;

  //paddleValue = thisGame.p1.y;
  /* Erase Paddle */
	//GLCD_DrawChar (0, lastValue, ' '); 	
  /* Draw Paddle */
  //GLCD_SetFont (&GLCD_customFont_16x24);
	//GLCD_DrawChar (0, paddleValue, 0x00 ); 	
  //GLCD_SetFont (&GLCD_Font_16x24);
	//lastValue = paddleValue;
} 

/****************************************************
*  undate_ball()
*  update the ball position
*  depending on direction of travel
*****************************************************/
void update_ball(void) {
	/*
	switch (thisGame.ball.dirn) {
		case 0: thisGame.ball.x++;
						break;
		case 1: thisGame.ball.x++;
						thisGame.ball.y--;
						break;
		case 2: thisGame.ball.y--;
						break;
		case 3: thisGame.ball.x--;
						thisGame.ball.y--;
						break;
		case 4: thisGame.ball.x--;
						break;
		case 5: thisGame.ball.x--;
						thisGame.ball.y++;
						break;
		case 6: thisGame.ball.y++;
						break;
		case 7: thisGame.ball.x++;
						thisGame.ball.y++;			
	}*/
}

void new_apple(void){
	int naX;
	int naY;
	naX = rand()%WIDTH;
	naY = rand()%HEIGHT;
	/*
	 if(naX > WIDTH){
        naX = naX - WIDTH;
    }
    if(naY > HEIGHT){
        naY = naY - HEIGHT;
    }*/
    thisGame.apple.x = naX;
    thisGame.apple.y = naY;
    //create new apple with these coordinates
}



void checkCollision(){
		TailSegment *temp;
     //3 checks

    //if outside bounds
    if ((thisGame.snake.x<0) || thisGame.snake.y<0 || thisGame.snake.x>WIDTH || thisGame.snake.y>HEIGHT){
        //collision
        //game over
    }
    //if colliding with apple
    if((thisGame.snake.x == thisGame.apple.x) + (thisGame.snake.y == thisGame.apple.y)){
        //remove apple
        //updateScore();
        new_apple();
        //drawApple();
    }
    //if colliding with tail, do node-to-node traversal for this
    temp = thisGame.snake.next; //Move to First Node
    do {
            //Do Your Operation
            //Statement 1-N
            if((thisGame.snake.x == temp->x) && (thisGame.snake.y == temp->y)){
                //game over
            }
            temp = temp->next; //Move Pointer to Next Node
        } while (temp != NULL);

}


