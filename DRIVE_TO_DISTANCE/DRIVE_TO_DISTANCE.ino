// This code was made by Miguel
#include <math.h>
const int PWM_PIN = 7;
const int DIR_PIN = 6;

const int RESET_PIN = 11;

const int ENCODER_A = 2;
const int ENCODER_B = 3;
 
volatile float encoderCount = 0;
 
const int LIMIT_PIN = 9;

volatile float degree;
float distance;
 
void setup() {
  // put your setup code here, to run once:
  pinMode(LIMIT_PIN, INPUT_PULLUP);
  pinMode(PWM_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
 
pinMode(RESET_PIN, INPUT);

  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
 
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR, RISING);
 
  Serial.begin(9600);
 analogWrite(PWM_PIN, 0);
}
 
void loop() {
  
  runtoDistance(0.5,3.14,25);

if (digitalRead(RESET_PIN) == HIGH){
   encoderCount = 0;
    degree = 0;
}
 Serial.print("distance: ");
 Serial.println(distance);
}
 
void encoderISR() {
  int bState = digitalRead(ENCODER_B);
  if (bState == HIGH) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}

int runtoDistance(float radius, float dist, float speed){
  degree = encoderCount*360/1600;
  distance = degree*(radius*M_PI / 180);
   if (digitalRead(LIMIT_PIN) == LOW && distance <= dist) {
  digitalWrite(DIR_PIN, HIGH);
  analogWrite(PWM_PIN, speed);
  }else if (digitalRead(LIMIT_PIN) == HIGH && distance >= dist){
    analogWrite(PWM_PIN, 0);
    
  }
}