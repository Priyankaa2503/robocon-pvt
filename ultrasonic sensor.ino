int trigPin=9;
int echoPin=10;
int distance;
long duration;
void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  
}

void loop()
{
  //To clear the trigpin condition
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.println("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  delay(1000);             
}
