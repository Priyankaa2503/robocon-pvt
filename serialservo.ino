#include<Servo.h>
int servopin = 9;
int angle = 0;
int i;
int prev = 0;
int j = 0;
Servo myservo;
void setup() {
  // put your setup code here, to run once:
  myservo.attach(servopin);
  Serial.begin(9600);
  Serial.println("Enter the angle:");
}

void loop()
{
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0)
  {
    int angle =Serial.readString().toInt();;
    Serial.println(angle);
    Serial.println(prev);
    

    if (prev <= angle)
    {
      for (i = prev; i <= angle; i += 5)
      {
        myservo.write(i);
        delay(15);
      }
    }
    else
    {
      for (i = prev; i >= angle; i -= 5)
      {
        myservo.write(i);
        delay(15);
      }

    }
    prev = angle;

  }



}
