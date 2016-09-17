#include <Servo.h>

Servo myServo;
#define echoPin 3
#define triggerPin 4

void setup() {
  myServo.attach(2);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Variables to calculate time and distance
  int duration, distance;
  
  // Digital 1 to trigger pin to send the ultrasonic wave
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(triggerPin, LOW);
  
  // Use pulseIn to detect HIGH in echoPin
  duration = pulseIn(echoPin, HIGH);
  
  // Divide by 2 and convert it into centimeters by dividing it by 29.1 
  distance = (duration/2) / 29.1;

  if(distance < 15){
    myServo.write(0);
  }
  else{
    myServo.write(0);
    delay(1000);
    myServo.write(45);
    delay(1000);
    myServo.write(90);
    delay(1000);
    myServo.write(130);
    delay(1000);
    myServo.write(180);
    delay(1000);
  }
}
