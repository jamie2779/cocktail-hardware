//서보모터 사용법
#include<Servo.h>

Servo myServo;

void setup(){
  myServo.attach(9);
}

void loop(){

  myServo.write(60);
  delay(2000);
  myServo.write(100);
  delay(2000);
}