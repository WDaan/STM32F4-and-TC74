#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cmsis_os2.h"  
#include <math.h>
#include "Driver_I2C.h"
#include "dialog.h"
#include "util.h"
#include "USBH_MSC.h" 


#define TEMP_ADDRESS 0x48
#define _I2C_Driver_(n)  Driver_I2C##n
#define  I2C_Driver_(n) _I2C_Driver_(n)
extern ARM_DRIVER_I2C    I2C_Driver_(3);
#define ptrI2C         (&I2C_Driver_(3))

//window handler
extern WM_HWIN MainhWin;


//STATE///
State state;

void State_Init(){
	getTemp(&state.temperature);
	state.fan_state = 0;
	state.fan_mode = 0;
	state.desired = 255;
};
//////////


//temp sensor
uint32_t getTemp(uint8_t *val) {
	uint8_t data = 0;
	ptrI2C->MasterTransmit(TEMP_ADDRESS, &data, 1, true);
  while (ptrI2C->GetStatus().busy);
  if (ptrI2C->GetDataCount() != 1) return -1;
  ptrI2C->MasterReceive(TEMP_ADDRESS, val, 1, false);
  while (ptrI2C->GetStatus().busy);
  if (ptrI2C->GetDataCount() != 1) return -1;
  return 0;
}

void handleTemperature(){
	if(state.fan_mode == 0 && state.temperature > state.desired){ //too hot
		setFanState(1);
	}else if(state.fan_mode == 0 && state.temperature < state.desired){ //too cold || good
		setFanState(0);
	}
}

void readUSB(){
	static unsigned int result; 
	static FILE *f;
	char fbuf[200] = { 0 };	
	
	result = USBH_MSC_DriveMount ("U0:"); 
		if (result == USBH_MSC_OK) { 
			f = fopen ("test.txt", "r"); 
			if (f) { 
				fread (fbuf, sizeof (fbuf), 1, f); 
				fclose (f); 
			} 
		}
		setInfoMessage(fbuf);
}

char buf[250] = {0};

void writeLog(){
	//prepare string to write

  char fanState[8] = {0};
  char fanMode[8] = {0};
  if(state.fan_mode == 0){ sprintf(fanMode, "%s", "AUTO"); }
  else {    sprintf(fanMode, "%s", "MANUAL"); }
  if(state.fan_state == 0) { sprintf(fanState, "%s", "OFF"); }
  else { sprintf(fanState, "%s", "ON"); }
	
  sprintf(buf, "Temperature: %d - Fanstate: %s - Fanmode: %s - Desired Temperature: %d\r\n", state.temperature, fanState, fanMode, state.desired);
	//
	
	static unsigned int result; 
	static FILE *f;
	
	result = USBH_MSC_DriveMount("U0:"); 
		if (result == USBH_MSC_OK) { 
			f = fopen("test.txt", "a"); 
			if (f) { 
				fwrite(buf, strlen(buf), 1, f);
				fclose(f);
				setInfoMessage("Logged succesfully");				
			} 
		} else {
			setInfoMessage("LOG FAILED");
		}
}

void setTextInt(TEXT_Handle hObj, const uint8_t val){
	char str[12];
	sprintf(str, "%d", val);
  TEXT_SetText(hObj, str);
}

void setInfoMessage(const char * str){
	WM_HWIN hItem = WM_GetDialogItem(MainhWin, 0x80b);
  TEXT_SetText(hItem, str);
}

void setSuccessMessage(){
	WM_HWIN hItem = WM_GetDialogItem(MainhWin, 0x80b);
  TEXT_SetText(hItem, "Success");
}


void setFanState(uint8_t status){
	state.fan_state = status;
	WM_HWIN hItem = WM_GetDialogItem(MainhWin, 0x808);
	if(status == 1){ //ON
		TEXT_SetText(hItem, "ON");
	}else if(status == 0){ //OFF{
		TEXT_SetText(hItem, "OFF");
	}
}




void bubblesort(uint8_t * arr, uint8_t len) 
 {
    uint8_t temp;
    for (uint8_t j = 0; j < len; j++) 
    {
       for (uint8_t i = 1; i < len - j; i++) 
       {
          if(arr[i-1] > arr[i]) 
          {
             temp = arr[i];
             arr[i] = arr[i-1];
             arr[i-1] = temp;
          }
       }
    }
 }
 
 void numArrayToString(char * str, uint8_t * arr, uint8_t len) {
	 uint8_t i=0;
   uint8_t index = 0;
   for (i=0; i<len-1; i++)
			index += sprintf(&str[index], "%d - ", arr[i]);
    index += sprintf(&str[index], "%d", arr[i]);
 }

 void generateRandomNumberArray(uint8_t * arr, uint8_t len){
	 for(uint8_t i = 0; i <len; i++){
		 arr[i] = rand() % 100;
	 }
 }
