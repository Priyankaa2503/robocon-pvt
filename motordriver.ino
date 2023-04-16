int dir[4]={30,3,15,17};
int pwm[4]={2,4,12,13};
int spd=100;
void setup() {
  // put your setup code here, to run once:
  for(int i=0;i< 4;i++){
  pinMode(dir[i],OUTPUT);
  pinMode(pwm[i],OUTPUT);
  }

}

void loop() 
{
  // put your main code here, to run repeatedly:
  delay(1000);
for(int i=0;i<4;i++)
{
  digitalWrite(dir[i],HIGH);
  analogWrite(pwm[i],spd);
}
delay(3000);
for(int i=0;i <4;i++)
{
  analogWrite(pwm[i],0);
}
delay(1000);
for(int i=0;i<4;i++)
{
  digitalWrite(dir[i],LOW);
  analogWrite(pwm[i],spd);
}
delay(3000);
for(int i=0;i<4;i++)
{
  analogWrite(pwm[i],0);
}
delay(1000);
// digitalWrite(17,HIGH);
//    analogWrite(2,spd);
//    delay(3000);
//     analogWrite(2,0);
//     delay(spd0);
//     digitalWrite(17,LOW);
//   analogWrite(2,spd);
//   delay(3000);
//     analogWrite(2,0);
//   delay(spd0);

 }
