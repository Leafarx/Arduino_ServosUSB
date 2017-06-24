/*
  ASCII table

 Prints out byte values in all possible formats:
 * as raw binary values
 * as ASCII-encoded decimal, hex, octal, and binary values

 For more on ASCII, see http://www.asciitable.com and http://en.wikipedia.org/wiki/ASCII

 The circuit:  No external hardware needed.

 created 2006
 by Nicholas Zambetti
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 <http://www.zambetti.com>

 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);

unsigned int pos0=172; // ancho de pulso en cuentas para pocicion 0°
unsigned int pos180=565; // ancho de pulso en cuentas para la pocicion 180°

int i = 0;
char data[2];

void setup() {
  servos.begin();  
  servos.setPWMFreq(60); //Frecuecia PWM de 60Hz o T=16,66ms
   //Initialize serial and wait for port to open:
  Serial.begin(9600);
  Serial2.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}


void loop() {
  /*
  for (int duty = pos0; duty < pos180; duty=duty+10) {
    for(int n=0;n<16;n++)
    {
      servos.setPWM(n,0,duty);
    }   
  }
  delay(1000);
  for (int duty = pos180; duty > pos0; duty=duty-10) {
    for(int n=0;n<16;n++)
    {
      servos.setPWM(n,0,duty);
    }   
  }
  delay(1000);
*/
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    //char inChar = (char)Serial.read();
    int angulo, inInt;
    int servo_motor;
    inInt = Serial.parseInt();
    servo_motor = inInt / 1000;
    angulo = inInt % 1000;
    if( angulo >= 0 && angulo <=180)
      setServo(servo_motor, angulo);
    
    //Serial.print( angulo);
  }
}

void setServo(uint8_t n_servo, int angulo) {
  int duty;
  duty=map(angulo,0,180,pos0, pos180);
  servos.setPWM(n_servo, 0, duty);  
}
