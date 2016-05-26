/*--------------------------------------------------
 * Name: main.h
 * Purpose: CMSIS-RTOS Pong Demo
 *--------------------------------------------------
 * Modification History                                                       
 *   Oct. 2015 Created
 * Copyright (c) mark.fisher@uea.ac.uk                     
 *--------------------------------------------------*/
#ifndef _MAIN_H
#define _MAIN_H

#include "cmsis_os.h"

#define __FI    1               /* Font index 16x24 */

/* Mailbox */
typedef struct {
  uint32_t pdl; /* paddle position */
} mail_t;

osMailQDef(mail_box, 1, mail_t);
osMailQId  mail_box;

/* Mutex */
osMutexDef(mut_GLCD);
osMutexId mut_GLCD; /* Mutex to control GLCD access */

/* Function Prototypes for Tasks */
void taskGLCD (void const *argument);
void taskBall (void const *argument);
void taskADC (void const *argument);

/* Declare Task IDs */
osThreadId tid_taskGLCD;  /* id of thread: taskGLCD */
osThreadId tid_taskBall;  /* id of thread: taskGreq */
osThreadId tid_taskADC;  /* id of thread: taskMotor */

/* Define Threads */
osThreadDef(taskGLCD, osPriorityNormal, __FI, 0);
osThreadDef(taskBall, osPriorityNormal, __FI, 0);
osThreadDef(taskADC, osPriorityNormal, __FI, 0);

#endif /* _MAIN_H */
