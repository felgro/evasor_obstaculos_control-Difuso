#include "calibracion.h"
#include "Funcion_membresia.h"
#include "infrarojo.h"
//#include "ESC.h"
#include "Wire.h"
//#include "Funciones_membresia.h"
//#include "infra.h"
#include "Adafruit_PWMServoDriver.h"


//////CONTROL DE LA TARJETA DE PWM ADAFRUIT////////////////////////////
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


//////////////////////////////////////////////////////////////////////////////////////

//variables para manipular direccion y velocidad
float pos_servo = 300; //90 grados, hacia el frente
float ESC_vel = 307; //velocidad mas baja hacia adelante
float denominador = 0;
//variables para calculo de reglas
float R1 = 0; float R8 = 0;
float R2 = 0; float R7 = 0;
float R3 = 0; float R6 = 0;
float R4 = 0; float R5 = 0;
float R1_pos = 0; float R1_vel = 0;
float R2_pos = 0; float R2_vel = 0;
float R3_pos = 0; float R3_vel = 0;
float R4_pos = 0; float R4_vel = 0;
float R5_pos = 0; float R5_vel = 0;
float R6_pos = 0; float R6_vel = 0;
float R7_pos = 0; float R7_vel = 0;
float R8_pos = 0; float R8_vel = 0;

//definicion de constantes de salida//SUGENO
float servo_izquierda = 235;
float servo_recto = 300;
float servo_derecha = 350;
//
float vel_baja = 318;
float vel_media = 321;
float vel_alta = 320;
float vel_reversa = 270;
//lecutra de los sensores y funciones de membresia
float S1=0;
float S2=0;
float S3=0;
//
float S1_FMC = 0;
float S2_FMC = 0;
float S3_FMC = 0;
float S1_FML = 0;
float S2_FML = 0;
float S3_FML = 0;
//
int SERVOMAX = 400;
int SERVOMIN = 215;
int a1 = 1;
int aux1 = 0;
void setup()
{

	//Serial.begin(9600);
	pwm.begin();
	pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
	

}

void loop()
{
	if( a1==1)
	{/*
		
		Serial.println("Inicio de calibracion de ESC");
		////////////////////////////////////
		Serial.println("maximo");
		pwm.setPWM(11, 0, SERVOMAX);
		delay(10000);
		Serial.println("minimo");
		pwm.setPWM(11, 0, SERVOMIN);
		delay(2000);
		Serial.println("medio");
		pwm.setPWM(11, 0, 307);
		delay(4000);
		///////////////////////////////////
		Serial.println("ESC calibrado");*/
		pwm.setPWM(11, 0, 307);
		delay(4000);
		pwm.setPWM(15, 0, 300);
		a1 = 3;
		
	}
	
	S1 = Lectura_sensor1();
	S2 = Lectura_sensor2();
	S3 = Lectura_sensor3();

	//Serial.print("S1: ");
	//Serial.println(S1);
	//Serial.print("S2: ");
	//Serial.println(S2);
	//Serial.print("S3: ");
	//Serial.println(S3);

	S1_FMC = FME_Cerca(S1); //sensor izquierdo
	S1_FML = FME_Lejos(S1); //sensor izquierdo
	/*Serial.print("cerca: ");
	Serial.println(S1_FMC);
	Serial.print("lejos: ");
	Serial.println(S1_FML);*/

	S2_FMC = FME_Cerca(S2); //sensor centro
	S2_FML = FME_Lejos(S2); // sensor centro

	S3_FMC = FME_Cerca(S3); //sensor derecha
	S3_FML = FME_Lejos(S3); //sensor derecha

	//Regla 1////
	//izuierdo_cerca && centro_cerca && derecho_cerca THEN servo izquierda && reversa       000
	R1 = min(S1_FMC, S2_FMC);
	R1 = min(R1, S3_FMC);
	R1_pos= R1*servo_izquierda;
	R1_vel = R1*vel_reversa;
	//REGLA2///
	//izquierda_cerca && centro_cerca && derecho_lejos THEN servo izquierda &&reversa //derecha baja       010
	//
	R2 = min(S1_FMC, S2_FMC);
	R2 = min(R2, S3_FML);
	R2_pos = R2*servo_derecha;
	R2_vel = R2*vel_baja;



	//REGLA3///
	//izquierda_cerca && centro_lejos && derecho_cerca THEN servo izquierda && vel reversa      011
	R3 = min(S1_FMC, S2_FML);
	R3 = min(R3, S3_FMC);
	R3_pos = R3*servo_izquierda;
	R3_vel = R3*vel_reversa;
	//REGLA4///
	//izquierda_cerca && centro_lejos && derecho_lejos THEN servo derecha && vel baja      001
	R4 = min(S1_FMC, S2_FML);
	R4 = min(R4, S3_FML);
	R4_pos = R4*servo_derecha;
	R4_vel = R4*vel_baja;

	//REGLA5///
	//izquierda_lejos && centro_cerca && derecho_cerca THEN servo izquierda && vel baja   110
	R5 = min(S1_FML, S2_FMC);
	R5 = min(R5, S3_FMC);
	R5_pos = R5*servo_izquierda;
	R5_vel = R5*vel_baja;

	//REGLA6///
	//izquierda_lejos && centro_cerca && derecho_lejos THEN servo izquierda && vel reversa   100
	R6 = min(S1_FML, S2_FMC);
	R6 = min(R6, S3_FML);
	R6_pos = R6*servo_izquierda;
	R6_vel = R6*vel_reversa;

	//REGLA7///
	//izquierda_lejos && centro_lejos && derecho_cerca THEN servo izquierda && vel baja        111
	R7 = min(S1_FML, S2_FML);
	R7 = min(R7, S3_FMC);
	R7_pos = R7*servo_izquierda;
	R7_vel = R7*vel_baja;

	//REGLA8///
	//izquierda_lejos && centro_lejos && derecho_lejos THEN servo centro && vel media    101
	R8 = min(S1_FML, S2_FML);
	R8 = min(R8, S3_FML);
	R8_pos = R8*servo_recto;
	R8_vel = R8*vel_media;


	//Calculo de centroides
	

	denominador = R1 + R2 + R3 + R4 + R5 + R6 + R7 + R8;
	pos_servo = (R1_pos + R2_pos + R3_pos + R4_pos + R5_pos + R6_pos + R7_pos + R8_pos) / denominador;
	ESC_vel = (R1_vel + R2_vel + R3_vel + R4_vel + R5_vel + R6_vel + R7_vel + R8_vel) / denominador;
	
	//Modificacion de salida de PWM ESC y servo
	/*Serial.print("ESC: ");
	Serial.println(ESC_vel);
	Serial.print("Servo: ");
	Serial.println(pos_servo);
	*/

	pwm.setPWM(15, 0, pos_servo);
	
	if (ESC_vel <= 300)
	{
		//if (aux1 = 1)
		//{
		
		pwm.setPWM(11, 0, 307);
		delay(10);
		pwm.setPWM(11, 0, 220);
		delay(10);
	//}
	//pwm.setPWM(15, 0, pos_servo);
	pwm.setPWM(11, 0, 290);
	//aux1 = 2;
	
	}
	pwm.setPWM(11, 0, ESC_vel);
		
		aux1 = 1;
	
	









}
