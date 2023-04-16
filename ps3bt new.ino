#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb);  // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
PS3BT PS3(&Btd);  // This will just create the instance
//PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;
//bool arr[4]={1,1,1,1};
//bool clockwise[4]={1,0,1,1};

// int dir[4]={15,17,10,8};
// int pwm[4]={12,13,11,9};

int dir[2][2] = { { 8, 17 }, { 15, 10 } };
int pwm[2][2] = { { 9, 13 }, { 12, 11 } };
int axis = 0, sign = 0;
int count = 0;
// int direct[2][2] = {{1, 0}, {0, 0}};
// int clockwise[4] = {0, 0, 0, 0};

int dwnwd, upwd, rtwd, lftwd, clk, anticlk, temp, temp1, temp2;
void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial)
    ;  // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1)
      ;  //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; i++) {
      pinMode(dir[i][j], OUTPUT);
      pinMode(pwm[i][j], OUTPUT);
    }
  }
}

void loop() {
  Usb.Task();

  // if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
  //   if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {


  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    upwd = map(PS3.getAnalogHat(LeftHatY), 137, 255, 0, 100);
    dwnwd = map(PS3.getAnalogHat(LeftHatY), 117, 0, 0, 100);
    rtwd = map(PS3.getAnalogHat(RightHatX), 137, 255, 0, 100);
    lftwd = map(PS3.getAnalogHat(RightHatX), 117, 0, 0, 100);
    clk = map(PS3.getAnalogButton(L2), 0, 255, 0, 100);
    anticlk = map(PS3.getAnalogButton(R2), 0, 255, 0, 100);
    if (PS3.getAnalogButton(L2) < 10 || PS3.getAnalogButton(R2) < 10) {
      if (PS3.getAnalogHat(LeftHatY) < 137 && PS3.getAnalogHat(LeftHatY) > 117) {
        analogWrite(pwm[axis][sign], 0);
        analogWrite(pwm[axis][!sign], 0);
      }

      if (PS3.getAnalogHat(RightHatX) < 137 && PS3.getAnalogHat(RightHatX) > 117) {
        analogWrite(pwm[!axis][sign], 0);
        analogWrite(pwm[!axis][!sign], 0);
      }
    }

    if (PS3.getAnalogHat(LeftHatY) < 117)  //forward
    {
      digitalWrite(dir[axis][sign], !sign);
      analogWrite(pwm[axis][sign], upwd);
      digitalWrite(dir[axis][!sign], !sign);
      analogWrite(pwm[axis][!sign], upwd);
    }

    if (PS3.getAnalogHat(LeftHatY) > 137)
    //backward
    {
      digitalWrite(dir[axis][sign], sign);
      analogWrite(pwm[axis][sign], dwnwd);
      digitalWrite(dir[axis][!sign], sign);
      analogWrite(pwm[axis][!sign], dwnwd);
    }

    if (PS3.getAnalogHat(RightHatX) > 137)
    //rightwards
    {
      digitalWrite(dir[!axis][sign], sign);
      analogWrite(pwm[!axis][sign], rtwd);
      digitalWrite(dir[!axis][!sign], sign);
      analogWrite(pwm[!axis][!sign], rtwd);
      ;
    }
    if (PS3.getAnalogHat(RightHatX) < 117) {
      //leftwards
      digitalWrite(dir[!axis][sign], !sign);
      analogWrite(pwm[!axis][sign], lftwd);
      digitalWrite(dir[!axis][!sign], !sign);
      analogWrite(pwm[!axis][!sign], lftwd);
    }

    if (PS3.getAnalogButton(L2) > 10) {
      //clockwise

      digitalWrite(dir[axis][sign], !sign);
      digitalWrite(dir[!axis][sign], !sign);
      digitalWrite(dir[axis][!sign], sign);
      digitalWrite(dir[!axis][!sign], sign);

      analogWrite(pwm[axis][sign], clk);
      analogWrite(pwm[!axis][sign], clk);
      analogWrite(pwm[axis][!sign], clk);
      analogWrite(pwm[!axis][!sign], clk);
    }
    if (PS3.getAnalogButton(R2) > 10) {
      //anticlockwise
      // for (int i = 0; i < 4; i++) {
      //   digitalWrite(dir[i][0], !(clockwise[i]));
      //   analogWrite(dir[i][1], R2);
      // }
      digitalWrite(dir[axis][sign], sign);
      digitalWrite(dir[!axis][sign], sign);
      digitalWrite(dir[axis][!sign], !sign);
      digitalWrite(dir[!axis][!sign], !sign);

      analogWrite(pwm[axis][sign], anticlk);
      analogWrite(pwm[!axis][sign], anticlk);
      analogWrite(pwm[axis][!sign], anticlk);
      analogWrite(pwm[!axis][!sign], anticlk);
    }
    //axis-change
    if (PS3.getButtonClick(L1)) {
      sign = !(axis ^ sign);
      axis = !axis;
    }
    if (PS3.getButtonClick(R1)) {
      sign = (axis ^ sign);
      axis = !axis;
    }
  }
}