// 
// 
// 

#include "infrarojo.h"




float Lectura_sensor1()
{
	analogReference(EXTERNAL);

	// LEER ENTRADA ANALOGICA A6:
	int sensorValue1 = analogRead(A6);
	// CONVERTIR LA LECTURA A VOLTAJE, (COUNTS--->VOLTAJE) (REFERENCIA 3.3V EXTERNA------>1023):
	float voltage1 = sensorValue1 * (3.16 / 1000);
	//CALCULAR LA DISTANCIA A PARTIR DEL VOLTAJE LEIDO
	//A PARTIR DE APROXIMACION POLINOMICA 4 ORDEN A LA CURVA DEL SENSOR 
	float pot1 = 211.19*voltage1;
	float pot2 = 142.31*pow(voltage1, 2);
	float pot3 = 43.475*pow(voltage1, 3);
	float pot4 = 4.8962*pow(voltage1, 4);
	float  distancia1 = pot4 - pot3 + pot2 - pot1 + 134.96;
	//Serial.println(distancia1);
	return distancia1;
}
 
float Lectura_sensor2()
{
	analogReference(EXTERNAL);

	// LEER ENTRADA ANALOGICA A7:
	int sensorValue2 = analogRead(A7);
	// CONVERTIR LA LECTURA A VOLTAJE, (COUNTS--->VOLTAJE) (REFERENCIA 3.3V EXTERNA------>1023):
	float voltage2 = sensorValue2 * (3.16 / 1000);
	//CALCULAR LA DISTANCIA A PARTIR DEL VOLTAJE LEIDO
	//A PARTIR DE APROXIMACION POLINOMICA 4 ORDEN A LA CURVA DEL SENSOR 
	float pot1_2 = 211.19*voltage2;
	float pot2_2 = 142.31*pow(voltage2, 2);
	float pot3_2 = 43.475*pow(voltage2, 3);
	float pot4_2 = 4.8962*pow(voltage2, 4);
	float  distancia2 = pot4_2 - pot3_2 + pot2_2 - pot1_2 + 134.96;
	//	Serial.println(distancia2);
	return distancia2;
}

float Lectura_sensor3()
{
	analogReference(EXTERNAL);

	// LEER ENTRADA ANALOGICA A8:
	int sensorValue3 = analogRead(A8);
	// CONVERTIR LA LECTURA A VOLTAJE, (COUNTS--->VOLTAJE) (REFERENCIA 3.3V EXTERNA------>1023):
	float voltage3 = sensorValue3 * (3.16 / 1000);
	//CALCULAR LA DISTANCIA A PARTIR DEL VOLTAJE LEIDO
	//A PARTIR DE APROXIMACION POLINOMICA 4 ORDEN A LA CURVA DEL SENSOR 
	float pot1_3 = 211.19*voltage3;
	float pot2_3 = 142.31*pow(voltage3, 2);
	float pot3_3 = 43.475*pow(voltage3, 3);
	float pot4_3 = 4.8962*pow(voltage3, 4);
	float  distancia3 = pot4_3 - pot3_3 + pot2_3 - pot1_3 + 134.96;
	//Serial.println(distancia3);
	return distancia3;
}
