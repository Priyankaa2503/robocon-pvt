int irsensor=2;
int LEDpin=13;
//int irsensor1=A3;
int statussensor=0;
//int duration;
//long distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(irsensor,INPUT);
  pinMode(LEDpin,OUTPUT);
  //Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  statussensor=digitalRead(irsensor);
  if(statussensor==1)
  digitalWrite(LEDpin,HIGH);
  else
  digitalWrite(LEDpin,LOW);
  
  
}
