#include <Servo.h>
Servo servo1;
int trigPin = 6; 
int angle=0;
int echoPin = 10;
long distance;
int duration;
void setup() 
{
Serial.begin(9600);
servo1.attach(9); 
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}
void loop()
{
//To clear the trigpin condition	
  digitalWrite(trigPin, LOW);
   	delayMicroseconds(2);
/* Sets the trigPin HIGH (ACTIVE) for 10 microseconds 
   which generates ultrasound*/
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
  	digitalWrite(trigPin, LOW);
/* Reads the echoPin, returns the sound wave 
travel time in microseconds*/
  	duration = pulseIn(echoPin, HIGH);
//here duration is the total time (original+reflected wave)
//hence time is divided by 2
	distance = duration*0.034/2;
/*map function scales one range to another
syntax: map(value, fromLow, fromHigh, toLow, toHigh)
here values between 10 and 80 is mapped to values in the range 
0 to 90 and corresponding angle is given as output.
when distance between object and ultrasonic sensor is 10(fromLow) 
the angle of the servo motor is 0 degrees(toLow) and
when distance between object and ultrasonic sensor is 80(fromHigh) 
the angle of the servo motor is 90 degrees(toHigh)*/
	angle=map(distance,10,80,0,90);
  	Serial.println(angle);
  	servo1.write(angle);
}
