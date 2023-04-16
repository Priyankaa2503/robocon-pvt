int dir[2]={3,30};
int dirarr[2]={0,1};
int pwm[2] = {4,2};
int spd=0;
int prev = 0;
int i;

void setup() {
  // put your setup code here, to run once:
  for(i=0;i<2;i++)
  {
  pinMode(dir[i],OUTPUT);
  pinMode(pwm[i],OUTPUT);
  }
  Serial.begin(9600);
  Serial.println("Enter the speed:");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
  int spd =Serial.readString().toInt();
  digitalWrite(dir[0],dirarr[0]);
  digitalWrite(dir[1],dirarr[1]);
    if (prev <= spd)
    {
      for (i = prev; i <= spd; i += 5)
      {
        analogWrite(pwm[0],i);
        analogWrite(pwm[1],i);
        delay(15);
        
      }
    }
    else  
    {
      for (i = prev; i >= spd; i -= 5)
      {
        analogWrite(pwm[0],i);
        analogWrite(pwm[1],i);
        delay(15);
      }

    }
    prev = spd;
  }
}

