#include "cmsis_os2.h"                                        // CMSIS RTOS header file
#include "USBH_MSC.h" 
char fbuf[200] = { 0 };

extern void Init_Timers(void);

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
 
  static unsigned int result; 
	static FILE *f; 
	Init_Timers();
	USBH_Initialize (0); 
	while (1) { 
		result = USBH_MSC_DriveMount ("U0:");
		if (result == USBH_MSC_OK) { 
			f = fopen ("Test.txt", "r"); 
			if (f) { fread (fbuf, sizeof (fbuf), 1, f); 
				fclose (f); 
			} 
		} 
		osDelay (1000); 
	}
}
