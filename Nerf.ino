#include <Servo.h>
Servo PAN;
Servo TILT;
Servo SHOOT;

int incoming=0,pan_pos=90,tilt_pos=75,shoot_pos=110;
int MOTOR = 12;
void setup() { 
  //pinMode(MOTOR,OUTPUT);
  SHOOT.attach(9);  // attaches the first servo on pin 9 to the servo object
  PAN.attach(10);  // attaches the second servo on pin 10 to the servo object
  TILT.attach(11);  // attaches the third servo on pin 11 to the servo object
  Serial.begin(9600);
  SHOOT.write(shoot_pos);
  delay(100);
  PAN.write(pan_pos);
  //limit pan motor from 5 degree to 175 degree
  delay(100);
  TILT.write(tilt_pos);
  //limit tilt motor from 75 degree to 135 degree
  delay(1200);
 
  analogWrite(MOTOR,0);
  Serial.println("READY......\n");
}

void loop() {
  if (Serial.available() > 0) {
    incoming = Serial.read();
    //Serial.print(incoming);
  }
  if (incoming == 50) {
    if(tilt_pos >= 135)
      tilt_pos = tilt_pos;
    else
      tilt_pos = tilt_pos + 5;
    TILT.write(tilt_pos);
    Serial.print("UP @ ");
    Serial.print(tilt_pos);
    Serial.println("deg");
    delay(200);
  }
  if (incoming == 56) {
    if(tilt_pos <= 75)
      tilt_pos = tilt_pos;
    else
      tilt_pos = tilt_pos - 5;
    TILT.write(tilt_pos);
    Serial.print("DOWN @ ");
    Serial.print(tilt_pos);
    Serial.println("deg");
    delay(200);
  }
  if (incoming == 52) {
    if(pan_pos <= 5)
      pan_pos = pan_pos;
    else
      pan_pos=pan_pos-5;
    PAN.write(pan_pos);
    Serial.print("LEFT @ ");
    Serial.print(pan_pos);
    Serial.println("deg");
    delay(200);
  }
  if (incoming == 54) {
    if(pan_pos >= 135)
      pan_pos = pan_pos;
    else
      pan_pos=pan_pos+5;
    PAN.write(pan_pos);
    Serial.print("RIGHT @ ");
    Serial.print(pan_pos);
    Serial.println("deg");
    delay(200);
  }
  if (incoming == 53) {
    Serial.println("SHOOOOOT!!!");
    for (int i = 0; i < 55; i=i+2) {
    SHOOT.write(shoot_pos+i);
    delay(40);
  }
  for (int i = 55; i > 0; i=i-2) {
    SHOOT.write(shoot_pos+i);
    delay(40);
  }
  }
  if (incoming == 48) {
    Serial.println("MOTOR = OFF");
    analogWrite(MOTOR,0);
    delay(100);
  }
  if (incoming == 49) {
    Serial.println("MOTOR = ON");
    analogWrite(MOTOR,140);
    delay(100);
  }
  else {
    incoming = 0;
    delay(10);
  }
}
