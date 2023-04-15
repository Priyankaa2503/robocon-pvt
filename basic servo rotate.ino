#include<Servo.h>
int servopin=9;
int angle=0;
Servo servo1;

void setup()
{
  servo1.attach(servopin);
}
void loop()
{
  for(angle=0;angle<=180;angle++)
  {
    servo1.write(angle);
    delay(15);
  }
  for(angle=180;angle>=0;angle--)
  {
    servo1.write(angle);
    delay(15);
  }
  
    
      
}