#include "cmsis_os2.h"  
#include "dialog.h"
void bubblesort(uint8_t invoer[], uint8_t lengte);
char * arrayToString(uint8_t * arr, uint8_t len);
uint32_t getTemp(uint8_t *val);
void numArrayToString(char * str, uint8_t * arr, uint8_t len);
void setTextInt(TEXT_Handle hObj, const uint8_t val);
void State_Init();
void setFanState(uint8_t state);
void setInfoMessage(const char * str);
void setSuccessMessage();
void handleTemperature();
void readUSB();
void writeLog();

typedef struct{
	uint8_t fan_mode; //auto = 0, manual = 1
	uint8_t temperature;
	uint8_t fan_state; //OFF = 0, ON = 1
	uint8_t desired;
} State;