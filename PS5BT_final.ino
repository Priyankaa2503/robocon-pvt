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

/* You can create the instance of the PS5BT class in two ways */
// This will start an inquiry and then pair with the PS5 controller - you only have to do this once
// You will need to hold down the PS and Share button at the same time, the PS5 controller will then start to blink rapidly indicating that it is in pairing mode
//PS5BT PS5(&Btd, PAIR);

// After that you can simply create the instance like so and then press the PS button on the device
PS5BT PS5(&Btd);
uint32_t ps_timer;

int spd[2] = { 12, 13 };
int dir[2] = { 15, 17 };
int mdpwm = 11;
int mddir = 10;
int phase[2] = { 1, 1 };
int dcv[2] = { 31, 33 };

void setup() {
  Serial.begin(115200);
#if !defined(_MIPSEL_)
  while (!Serial)
    ;  // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1)
      ;  // Halt
  }
  Serial.print(F("\r\nPS5 Bluetooth Library Started"));

  for (int j = 0; j < 2; j++) {
    pinMode(spd[j], OUTPUT);
    pinMode(dir[j], OUTPUT);
    pinMode(dcv[j], OUTPUT);
  }
  digitalWrite(dcv[0], LOW);

  digitalWrite(dcv[1], LOW);
}
void loop() {
  Usb.Task();
  if (PS5.getButtonPress(PS)) {
    if (millis() - ps_timer > 1000)
      PS5.disconnect();
  } else
    ps_timer = millis();
  int spd1, spd2;

  if (PS5.getAnalogHat(LeftHatX) > 137 || PS5.getAnalogHat(LeftHatX) < 117 || PS5.getAnalogHat(LeftHatY) > 137 || PS5.getAnalogHat(LeftHatY) < 117 || PS5.getAnalogHat(RightHatX) > 137 || PS5.getAnalogHat(RightHatX) < 117 || PS5.getAnalogHat(RightHatY) > 137 || PS5.getAnalogHat(RightHatY) < 117) {

    int rt = map(PS5.getAnalogHat(RightHatX), 0, 255, -100, 100);
    int lt = map(PS5.getAnalogHat(LeftHatY), 0, 255, -100, 100);
    spd1 = lt + rt;
    spd2 = lt - rt;
    if (spd1 > 100) {
      spd1 = 100;
    } else if (spd1 < -100) {
      spd1 = -100;
    }
    if (spd2 > 100) {
      spd2 = 100;
    } else if (spd2 < -100) {
      spd2 = -100;
    }

    if (spd1 < 0) {
      digitalWrite(dir[0], phase[0]);
    } else if (spd1 > 0) {
      digitalWrite(dir[0], !phase[0]);
    }
    if (spd2 < 0) {
      digitalWrite(dir[1], phase[1]);
    } else if (spd2 > 0) {
      digitalWrite(dir[1], !phase[1]);
    }

    analogWrite(spd[0], abs(spd1));
    analogWrite(spd[1], abs(spd2));

  }

  else if (PS5.getAnalogHat(LeftHatY) > 117 && PS5.getAnalogHat(LeftHatY) < 137 && PS5.getAnalogHat(RightHatX) > 117 && PS5.getAnalogHat(RightHatX) < 137)  //stop
  {

    analogWrite(spd[0], 0);
    analogWrite(spd[1], 0);
  }

  if (PS5.getButtonClick(TRIANGLE)) {

    digitalWrite(dcv[0], HIGH);
    digitalWrite(dcv[1], LOW);
    digitalWrite(dcv[0], LOW);
    digitalWrite(dcv[1], LOW);
  }
  if (PS5.getButtonClick(CIRCLE)) {
    digitalWrite(dcv[0], LOW);
    digitalWrite(dcv[1], HIGH);
    digitalWrite(dcv[0], LOW);
    digitalWrite(dcv[1], LOW);
  }
  if (PS5.getAnalogButton(L2) > 10 && PS5.getAnalogButton(R2) < 10)  //clockwise
  {

    digitalWrite(mddir, HIGH);
    analogWrite(mdpwm, 50);

  } else if (PS5.getAnalogButton(R2) > 10 && PS5.getAnalogButton(L2) < 10)  //anticlockwise
  {

    digitalWrite(mddir, LOW);
    analogWrite(mdpwm, 50);

  }


  else  //stop
  {
    analogWrite(mdpwm, 0);
  }
}