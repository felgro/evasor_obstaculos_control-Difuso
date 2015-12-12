// 
// 
// 

#include "Funcion_membresia.h"


//Funciones de membresia de entrada 
// Tres sensores de entrada con dos funciones de membresia cada uno (Mismas fm para las tres entradas):
///////////////////////////////////////////////////////////
// CERCA, TRAPEZOIDAL [0 0 15 40]//

float Entrada1c = 0;
float Entrada1l = 0;
float div1 = 0;
float div2 = 0;
float sum1 = 0;
float sum2 = 0;
float multi1 = 0;
float multi2 = 0;

float FME_Cerca(float Lectura1)
{
	//float Entrada1c = 0;
	if (Lectura1 <= 15) { Entrada1c = 1; }
	else if (Lectura1 > 15 && Lectura1 <= 40)
	{
		div1 = -.04;
		sum1 = Lectura1 - 15;
		multi1 = div1*sum1;

		Entrada1c = multi1 + 1;// ((-1 / 20) * (Lectura1 - 10)) + 1; //Ecuacion de la recta 
		//Serial.print("Entrada1c: ");
		//Serial.println(Entrada1c);
	}

	else if (Lectura1 > 40) Entrada1c = 0;
	return Entrada1c;

}
///////////////////////////////////////////////////////////

//Lejos, Trapezoidal [15 40 -- --]
float FME_Lejos(float Lectura1)
{
	//float Entrada1l = 0;
	if (Lectura1 < 15) Entrada1l = 0;
	else if (Lectura1 >= 15 && Lectura1 <= 40)
	{	
		div2 = 0.04;
		sum2 = Lectura1 - 15;
		Entrada1l = div2*sum2;// ((.04)*(Lectura1 - 15)); // Ecuacion de la recta 
		//Serial.print("Entrada1L: ");
		//Serial.println(Entrada1l);
	}
	else if (Lectura1 > 40) Entrada1l = 1;

	return Entrada1l;
}
//////////////////////////////////////////////////////////
