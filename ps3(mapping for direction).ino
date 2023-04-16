#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd); // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;
int dir[4]={3,17 ,15,30};
bool 
int pwm[4]={4,13,12,2};
int spd;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  for(int i=0;i< 4;i++){
  pinMode(dir[i],OUTPUT);
  pinMode(pwm[i],OUTPUT);
  }
  
}
void loop() {
  Usb.Task();

  // if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
  //   if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
  //     Serial.print(F("\r\nLeftHatX: "));
  //     Serial.print(PS3.getAnalogHat(LeftHatX));
  //     Serial.print(F("\tLeftHatY: "));
  //     Serial.print(PS3.getAnalogHat(LeftHatY));
  //     if (PS3.PS3Connected) { // The Navigation controller only have one joystick
  //       Serial.print(F("\tRightHatX: "));
  //       Serial.print(PS3.getAnalogHat(RightHatX));
  //       Serial.print(F("\tRightHatY: "));
  //       Serial.print(PS3.getAnalogHat(RightHatY));
  //     }
  //   }

  if (PS3.PS3Connected || PS3.PS3NavigationConnected){
    if(PS3.getAnalogHat(LeftHatY) > 137 )
    {  
     spd= map(PS3.getAnalogHat(LeftHatY),137,255,0,100);
     digitalWrite( dir[0], LOW);
     analogWrite(pwm[0],spd);
     digitalWrite( dir[2], LOW);
     analogWrite(pwm[2], spd);
     
    }
    if(PS3.getAnalogHat(LeftHatY) < 117 )
    {
      spd = map( PS3.getAnalogHat(LeftHatY),117,0,0,100);
      digitalWrite( dir[0], HIGH);
      analogWrite(pwm[0], spd);
      digitalWrite( dir[2], HIGH);
      analogWrite(pwm[2], spd);
      
    }

    if(PS3.getAnalogHat(RightHatX) > 137 )
    {
      spd=map( PS3.getAnalogHat(RightHatX),137,255,0,100);
      digitalWrite( dir[1], HIGH);
      analogWrite(pwm[1], spd);
      digitalWrite( dir[3], LOW);
      analogWrite(pwm[3], spd);
    }    
    if( PS3.getAnalogHat(RightHatX) < 117 )
    {
      spd= map( PS3.getAnalogHat(RightHatX),117,0,0,100);
      digitalWrite( dir[1], LOW)
      analogWrite(pwm[1], spd)
      digitalWrite( dir[3], HIGH)
      analogWrite(pwm[3], spd)
      
    }
  }  
  if (PS3.getAnalogButton(L2)>10)
  {
     spd=map(PS3.getAnalogButton(L2),0,255,0,100);
     digitalWrite( dir[0], HIGH);
     digitalWrite( dir[2], LOW);
     digitalWrite( dir[1], LOW);
     digitalWrite( dir[3],HIGH);
    for(int i=0;i<4;i=i++)
    {
      analogWrite(pwm[i], spd);     
    }

  }
  {
     spd=map(PS3.getAnalogButton(R2),0,255,0,100);
     digitalWrite( dir[0], LOW);
  if(PS3.getAnalogButton(R2)>10)
     digitalWrite( dir[2], HIGH);
     digitalWrite( dir[1], HIGH);
     digitalWrite( dir[3],LOW);
    for(int i=0;i<4;i=i++)
    {
      analogWrite(pwm[i], spd);     
    }
  }
}

