int dir[4]={3,17 ,15,30};
int pwm[4]={4,13,12,2};
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
    digitalWrite(dir[0],LOW);
    analogWrite(pwm[0],100);
    digitalWrite(dir[2],LOW);
    analogWrite(pwm[2],100);
    delay(2000);
    analogWrite(pwm[0],0);
    analogWrite(pwm[2],0);
    delay(1000);

    digitalWrite(dir[1],HIGH);
    analogWrite(pwm[1],100);
    digitalWrite(dir[3],LOW);
    analogWrite(pwm[3],100);
    delay(2000);
    analogWrite(pwm[1],0);
    analogWrite(pwm[3],0);    
    delay(1000);

    digitalWrite(dir[0],HIGH);
    analogWrite(pwm[0],100);
    digitalWrite(dir[2],HIGH);
    analogWrite(pwm[2],100);
    delay(2000);
    analogWrite(pwm[0],0);
    analogWrite(pwm[2],0);
    delay(1000);

    digitalWrite(dir[1],LOW);
    analogWrite(pwm[1],100);
    digitalWrite(dir[3],HIGH);
    analogWrite(pwm[3],100);
    delay(2000);
    // analogWrite(pwm[1],0);
    // analogWrite(pwm[3],0);    
    //delay(1000);




}
