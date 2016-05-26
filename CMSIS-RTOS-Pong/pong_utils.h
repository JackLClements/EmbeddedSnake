/*--------------------------------------------------
 * Name:    main.h
 * Purpose: pong function prototypes and defs
 *--------------------------------------------------
 *
 * Modification History
 * 06.02.14 Created
 * 09.12.15 Updated (uVision5.17 + DFP2.6.0)
 *
 * Dr Mark Fisher, CMP, UEA, Norwich, UK
 *--------------------------------------------------*/
#ifndef _PONG_UTILS_H
#define _PONG_UTILS_H

#define wait_delay HAL_Delay
#define WIDTH		GLCD_WIDTH
#define HEIGHT	GLCD_HEIGHT
#define CHAR_H  GLCD_Font_16x24.height                  /* Character Height (in pixels) */
#define CHAR_W  GLCD_Font_16x24.width                  /* Character Width (in pixels)  */
#define BAR_W   6									  /* Bar Width (in pixels) */
#define BAR_H		24				          /* Bar Height (in pixels) */
#define T_LONG	1000                /* Long delay */
#define T_SHORT 5                   /* Short delay */

typedef struct {
	  int dirn;
	  int x; 
	  int y; 
	} BallInfo;

typedef struct {
	  int x;
	  int y;
	} PaddleInfo;

	
typedef struct TailSegment TailSegment;
struct TailSegment{
     int x;
     int y;
     TailSegment *next; 
 };
	
typedef struct {
	int x;
	int y;
	int direction;
	TailSegment *next;
	TailSegment *last;
} Snake;

typedef struct {
	int x;
	int y;
	int score;
} Apple;
	
typedef struct {
	unsigned int num_ticks;
	Snake snake;
	Apple apple;
  } GameInfo;

/* Function Prototypes */
void game_Initialize(void);
void erase_ball (void);
void draw_ball (void);
void update_ball (void);
void update_player (void);
void checkCollision (void);	
void new_apple(void);

#endif /* _PONG_UTILS_H */
