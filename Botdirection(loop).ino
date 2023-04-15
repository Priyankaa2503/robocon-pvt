int dir[4]={17,14,15,16};
int pwm[4]={2,5,4,3};
bool clock=1;
void setup() {
  // put your setup code here, to run once:
  for(int i=0;i< 4;i++){
  pinMode(dir[i],OUTPUT);
  pinMode(pwm[i],OUTPUT);
  }

}


void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  for(int i=0;i<4;i=i+2)
  {
    digitalWrite(dir[i],HIGH);
    analogWrite(pwm[i],100);
  }
    delay(2000);
    for(int i=0;i<4;i=i+2)
 {
    analogWrite(pwm[i],0);
 }
    delay(1000);
    for(int i=1;i<4;i=i+2)
 {    
    digitalWrite(dir[i],HIGH);
    analogWrite(pwm[i],100);
  }
    delay(2000);
    for(int i=1;i<4;i=i+2)
  {  
    analogWrite(pwm[i],0);
  }
    delay(1000);
  for(int i=0;i<4;i=i+2)
  {
    digitalWrite(dir[i],LOW);
    analogWrite(pwm[i],100);
  }  
  delay(2000);
  for(int i=0;i<4;i=i+2)
  {
    analogWrite(pwm[i],0);
  }
  delay(1000);
  for(int i=1;i<4;i=i+2)
  {    
    digitalWrite(dir[i],LOW);
    analogWrite(pwm[i],100);
  }
    delay(2000);
    for(int i=1;i<4;i=i+2)
  {  
    analogWrite(pwm[i],0);
  }
}
