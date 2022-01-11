#include <Servo.h>
const int trigPin = 3;
const int echoPin = 2;
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int sensorPin = A1;
int potpin = A2;
int therm=A0;
int val;
int lightCal;

int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

Servo myServo; 
void setup() {
   Serial.begin(9600);
  myServo.attach(4);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}

void loop() {
 val = analogRead(potpin); 
 val = map(val, 0, 1023, 0, 180);// scale it for use with the servo (value between 0 and 180)  
  myServo.write(val);                  // sets the servo position according to the scaled value
  delay(15);
  
  func();
}

void func()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  Vo = analogRead(therm);
  val = analogRead(potpin); 
  int temp = analogRead(therm);
  int light = analogRead(sensorPin);// reads the value of the potentiometer (value between 0 and 1023) 
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
  
  duration = pulseIn(echoPin, HIGH);
  lightCal = analogRead(sensorPin);
  distance = duration * 0.034 / 2;
  char pot_text[30];
  char light_text[30];
  char temp_text[30];
  char distance_text[30];

  dtostrf(val, 10, 10, pot_text);
  dtostrf(light, 10, 10, light_text);
  dtostrf(temp, 10, 10, temp_text);
  dtostrf(distance, 10, 10, distance_text);
  
  char text[125];
  snprintf(text, 125, "%s,%s,%s,%s", pot_text, light_text, temp_text, distance_text);
  Serial.println(text);
}