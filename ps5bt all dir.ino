/*
 Example sketch for the PS5 Bluetooth library - developed by Kristian Sloth Lauszus
 For more information visit the Github repository: github.com/felis/USB_Host_Shield_2.0 or
 send me an e-mail: lauszus@gmail.com
 */

#include <PS5BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb);  // You have to create the Bluetooth Dongle instance like so

/* You can create the instancNe of the PS5BT class in two ways */
// This will start an inquiry and then pair with the PS5 controller - you only have to do this once
// You will need to hold down the PS and Share button at the same time, the PS5 controller will then start to blink rapidly indicating that it is in pairing mode
//  PS5BT PS5(&Btd, PAIR);

// After that you can simply create the instance like so and then press the PS button on the device
PS5BT PS5(&Btd);

bool printAngle = false, printTouch = false;
uint16_t lastMessageCounter = -1;
uint8_t player_led_mask = 0;
bool microphone_led = false;
uint32_t ps_timer;
int dir[] = { 15, 17 };  //17,13 are right wheel
int pwm[] = { 12, 13 };  //15,12 are left wheel
bool arr[2] = { 1, 1 };
bool clockwise[2] = { 0, 1 };
int pins[2] = { 35, 37 };
int valLH,valRH;
// int motor3 = ;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial)
    ;  // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1)
      ;  // Halt
  }
  Serial.print(F("\r\nPS5 Bluetooth Library Started"));

  for (int i = 0; i < 2; i++) {
    pinMode(dir[i], OUTPUT);
    pinMode(pwm[i], OUTPUT);
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  Usb.Task();

  if (PS5.connected() && lastMessageCounter != PS5.getMessageCounter()) {

    lastMessageCounter = PS5.getMessageCounter();
    if (PS5.getButtonPress(PS)) {
      if (millis() - ps_timer > 1000)
        PS5.disconnect();
    }

    valLH = map(PS5.getAnalogHat(LeftHatY), 0, 255, -100, 100);
    valRH = map(PS5.getAnalogHat(RightHatX), 0, 255,-100, 100);
    
    spd1=valLH+valRH;
    spd2=valLH-valRH;

    if(spd1>100)
      spd1=100;
    



    if(upwd>10)
    {
      if(rtwd>10)
      {
        spd1=upwd+rtwd;
        spd2=upwd-rtwd;

      }
      else
      {
        spd1=upwd+lftwd;
        spd2=upwd-lftwd;
      }
    }
    else(dwnwd<0)
    {
      if(<0)
      {
        spd1=dwnwd+rtwd;
        spd2=dwnwd-rtwd;

      }
      else
      {
        spd1=dwnwd+lftwd;
        spd2=dwnwd-lftwd;
      }

    }
 

  
  }
}