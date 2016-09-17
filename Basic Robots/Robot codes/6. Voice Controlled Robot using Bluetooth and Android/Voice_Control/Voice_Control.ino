///////////////////////////////////////////////////////////////
// Engineer   - I.Gogul
// College    - Madras Institute of Technology, Chennai
// University - Anna University
// Design     - Voice Controlled Robot using Android
//////////////////////////////////////////////////////////////

#include <SoftwareSerial.h>

#define ECHO_PIN 2
#define TRIGGER_PIN 3
#define MOTOR_INPUT_1_PIN 4
#define MOTOR_INPUT_2_PIN 5
#define MOTOR_INPUT_3_PIN 6
#define MOTOR_INPUT_4_PIN 7
#define SENSOR_LEFT_PIN 8
#define SENSOR_RIGHT_PIN 9
#define RX_PIN 10
#define TX_PIN 11
#define LED_PIN 12

SoftwareSerial BT(TX_PIN, RX_PIN);
String voice;
int obstacleCleared;
void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MOTOR_INPUT_1_PIN, OUTPUT);
  pinMode(MOTOR_INPUT_2_PIN, OUTPUT);
  pinMode(MOTOR_INPUT_3_PIN, OUTPUT);
  pinMode(MOTOR_INPUT_4_PIN, OUTPUT);
  pinMode(SENSOR_LEFT_PIN, INPUT);
  pinMode(SENSOR_RIGHT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

}

void loop() {
  int distance, duration;
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  
  distance = (duration/2) / 29.1;
  
  if(distance <= 10){
    obstacleCleared = 1;     // Obstacle is there
    if(obstacleCleared == 1){
      // Stop
      motor_stop();
      delay(2000);
      // Take a 90 degree right turn
      motor_right();
      delay(1000);
      // Move forward
      motor_forward();
      delay(1000);
      // Take a 90 degree left turn
      motor_left();
      delay(300);
      // Move forward
      motor_forward();

      obstacleCleared = 0; // Obstacle cleared successfully
    }
  }
  else if (digitalRead(SENSOR_LEFT_PIN) == LOW){
    motor_stop();
    delay(2000);
    // Take a 90 degree right turn
    motor_right();
    delay(1000);
    // Move forward
    motor_forward();
  }
  else if (digitalRead(SENSOR_RIGHT_PIN) == LOW){
    motor_stop();
    delay(2000);
    // Take a 90 degree right turn
    motor_left();
    delay(1000);
    // Move forward
    motor_forward();
  }
  else {
    while (BT.available()){  
      delay(10); 
      char c = BT.read(); 
      if (c == '#') { break; } 
        voice += c; 
    }  
    if (voice.length() > 0) {
      Serial.println(voice); 
      if(voice == "*forward") {
        motor_forward();
      } 
      else if(voice == "*back"){
        motor_reverse();
      }
      else if(voice == "*left"){
        motor_left();
      }
      else if(voice == "*right"){
        motor_right();
      }
      else if(voice == "*hold"){
        motor_stop();
      }
      voice="";
    }
  }
}

void motor_stop(){
    digitalWrite(MOTOR_INPUT_1_PIN, LOW);
    digitalWrite(MOTOR_INPUT_2_PIN, LOW);
    digitalWrite(MOTOR_INPUT_3_PIN, LOW);
    digitalWrite(MOTOR_INPUT_4_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
}

void motor_right(){
    digitalWrite(MOTOR_INPUT_1_PIN, HIGH);
    digitalWrite(MOTOR_INPUT_2_PIN, LOW);
    digitalWrite(MOTOR_INPUT_3_PIN, LOW);
    digitalWrite(MOTOR_INPUT_4_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
}

void motor_left(){
    digitalWrite(MOTOR_INPUT_1_PIN, LOW);
    digitalWrite(MOTOR_INPUT_2_PIN, HIGH);
    digitalWrite(MOTOR_INPUT_3_PIN, HIGH);
    digitalWrite(MOTOR_INPUT_4_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
}
void motor_forward(){
    digitalWrite(MOTOR_INPUT_1_PIN, HIGH);
    digitalWrite(MOTOR_INPUT_2_PIN, LOW);
    digitalWrite(MOTOR_INPUT_3_PIN, HIGH);
    digitalWrite(MOTOR_INPUT_4_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
}

void motor_reverse(){
    digitalWrite(MOTOR_INPUT_1_PIN, LOW);
    digitalWrite(MOTOR_INPUT_2_PIN, HIGH);
    digitalWrite(MOTOR_INPUT_3_PIN, LOW);
    digitalWrite(MOTOR_INPUT_4_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
}
