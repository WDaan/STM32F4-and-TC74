#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cmsis_os2.h"  
#include <math.h>
#include "Driver_I2C.h"

#define TEMP_ADDRESS 0x48
#define _I2C_Driver_(n)  Driver_I2C##n
#define  I2C_Driver_(n) _I2C_Driver_(n)
extern ARM_DRIVER_I2C    I2C_Driver_(3);
#define ptrI2C         (&I2C_Driver_(3))


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
