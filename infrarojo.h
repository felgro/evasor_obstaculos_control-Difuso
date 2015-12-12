// infrarojo.h

#ifndef _INFRAROJO_h
#define _INFRAROJO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

float Lectura_sensor1();
float Lectura_sensor2();
float Lectura_sensor3();
