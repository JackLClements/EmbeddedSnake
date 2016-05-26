/**
  ******************************************************************************
  * @file    main.c 
  * @author  mark.fisher@uea.ac.uk
  * @version V1.0.1
  * @date    05-02-2016
  * @brief   Pong Game (using multiple threads)
  ******************************************************************************
  * @attention
  *
  * Note: The functions:
  *   SystemClock_Config ( )
  *   CPU_CACHE_Enable ( )
  * are copied from the uVision5 examples provided with DFP supporting the board.
  *
  ******************************************************************************
  */

#include "stm32f7xx_hal.h"
#include "stm32746g_discovery_sdram.h"
#include "RTE_Components.h"
#include "GLCD_Config.h"
#include "Board_GLCD.h"
#include "Board_Touch.h"
#include "main.h"
#include "pong_utils.h"


/* Globals */
extern GLCD_FONT     GLCD_Font_16x24;
GameInfo thisGame;


#ifdef RTE_CMSIS_RTOS_RTX
extern uint32_t os_time;

uint32_t HAL_GetTick(void) { 
  return os_time; 
}
#endif

/**
  * System Clock Configuration
  *   System Clock source            = PLL (HSE)
  *   SYSCLK(Hz)                     = 200000000
  *   HCLK(Hz)                       = 200000000
  *   AHB Prescaler                  = 1
  *   APB1 Prescaler                 = 4
  *   APB2 Prescaler                 = 2
  *   HSE Frequency(Hz)              = 25000000
  *   PLL_M                          = 25
  *   PLL_N                          = 400
  *   PLL_P                          = 2
  *   PLL_Q                          = 8
  *   VDD(V)                         = 3.3
  *   Main regulator output voltage  = Scale1 mode
  *   Flash Latency(WS)              = 6
  */
static void SystemClock_Config (void) {
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;  
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Activate the OverDrive to reach the 200 MHz Frequency */
  HAL_PWREx_EnableOverDrive();
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
}

/**
  * CPU L1-Cache enable
  */
static void CPU_CACHE_Enable (void) {

  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

/*--------------------------------------------------
 *      Thread 1 'taskGLCD':   
 *--------------------------------------------------*/
void taskGLCD (void const *argument) {
  //BallInfo init_pstn = thisGame.ball;

	for (;;) {
      //thisGame.p1.y = mail->pdl;				
  	  

			osMutexWait(mut_GLCD, osWaitForever);	
			//GLCD_ClearScreen();
			//GLCD_DrawHLine(0, 0, GLCD_SIZE_X);
      update_player();
			
      draw_ball();		
		  new_apple();
			osMutexRelease(mut_GLCD);

			osDelay(T_SHORT);
			osSignalSet(tid_taskBall, 0x0001);
	}
}

/*--------------------------------------------------
 *      Thread 2 'taskBall':   
 *--------------------------------------------------*/
void taskBall (void const *argument) {

	for (;;) {
    osSignalWait(0x0001, osWaitForever);

    update_ball();   
    checkCollision();

    osSignalSet(tid_taskGLCD, 0x0001);
	}
}

/*--------------------------------------------------
 *      Thread 2 'taskADC':   
 *--------------------------------------------------*/
void taskADC (void const *argument) {
  int16_t paddleValue; 
  TOUCH_STATE  tsc_state;
  
  
  
	for (;;) {
    //mail_t *mail = (mail_t*)osMailAlloc(mail_box, 
                                       //osWaitForever);
    //ADC_StartConversion();
		//adcValue = ADC_GetValue ();
    Touch_GetState (&tsc_state); /* Get touch state */   
    if (tsc_state.pressed) {
      paddleValue =  tsc_state.y;
    }
    		
		//mail->pdl = paddleValue;
		//osMailPut(mail_box, mail);
    osDelay(T_SHORT);
	}
}

/*********************************************************************
*
*       Main
*/
int main (void) {
  CPU_CACHE_Enable();                       /* Enable the CPU Cache           */
  HAL_Init();                               /* Initialize the HAL Library     */
  BSP_SDRAM_Init();                         /* Initialize BSP SDRAM           */
  SystemClock_Config();                     /* Configure the System Clock     */
  
  game_Initialize();
	//ADC_Initialize();
  Touch_Initialize(); 
	GLCD_Initialize ();
	GLCD_SetBackgroundColor (GLCD_COLOR_BLACK);
  GLCD_ClearScreen (); 
	GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
  GLCD_SetFont (&GLCD_Font_16x24);
  
  mail_box = osMailCreate(osMailQ(mail_box), NULL);
  mut_GLCD = osMutexCreate(osMutex(mut_GLCD));
 
  tid_taskGLCD = osThreadCreate(osThread(taskGLCD), NULL);
  tid_taskBall = osThreadCreate(osThread(taskBall), NULL);
  tid_taskADC = osThreadCreate(osThread(taskADC), NULL);

  osDelay(osWaitForever);
  while(1)
    ;
  
}
