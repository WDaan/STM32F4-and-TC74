
#include "cmsis_os2.h"
#include "GUI.h"
#include <string.h>
#include <stdio.h>

#include "dialog.h"
extern WM_HWIN CreateBubblesort(void);
extern uint8_t temperature_response;

/*----------------------------------------------------------------------------
 *      GUIThread: GUI Thread for Single-Task Execution Model
 *---------------------------------------------------------------------------*/
#define GUI_THREAD_STK_SZ    (2048U)

static void         GUIThread (void *argument);         /* thread function */
static osThreadId_t GUIThread_tid;                      /* thread id */
static uint64_t     GUIThread_stk[GUI_THREAD_STK_SZ/8]; /* thread stack */

static const osThreadAttr_t GUIThread_attr = {
  .stack_mem  = &GUIThread_stk[0],
  .stack_size = sizeof(GUIThread_stk),
  .priority   = osPriorityIdle 
};

int Init_GUIThread (void) {

  GUIThread_tid = osThreadNew(GUIThread, NULL, &GUIThread_attr);
  if (GUIThread_tid == NULL) {
    return(-1);
  }

  return(0);
}

__NO_RETURN static void GUIThread (void *argument) {
  (void)argument;

  GUI_Init();           /* Initialize the Graphics Component */

  /* Add GUI setup code here */
	//GUI_DispString("Hello World!");
	 WM_HWIN hWin=CreateBubblesort();
	
  while (1) {
    char str[12];
		sprintf(str, "%d", temperature_response);
		
    WM_HWIN hItem = WM_GetDialogItem(hWin, 0x807);
    TEXT_SetText(hItem, str);
    /* All GUI related activities might only be called from here */  
		GUI_Exec();         /* Execute all GUI jobs ... Return 0 if nothing was done. */	
		GUI_X_ExecIdle();   /* Nothing left to do for the moment ... Idle processing */
		GUI_TOUCH_Exec();
		
	}
}
