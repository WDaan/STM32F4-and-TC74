#include "cmsis_os2.h"                                        // CMSIS RTOS header file
#include "USBH_MSC.h" 
#include "util.h"
#include <string.h>
char fbuf[200] = { 0 }; 

extern void Init_Timers(void);
extern State state;

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Thread (void *argument);                                 // thread function
osThreadId_t tid_Thread;                                      // thread id
 
int Init_Thread (void) {
 
  tid_Thread = osThreadNew (Thread, NULL, NULL);
  if (!tid_Thread) return(-1);
  
  return(0);
}
 
void Thread (void *argument) {
	Init_Timers();
	USBH_Initialize (0);
	while (1) {
		writeLog();
		osDelay (5000); 
	}
}
