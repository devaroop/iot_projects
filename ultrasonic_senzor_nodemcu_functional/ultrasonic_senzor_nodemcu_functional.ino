/*
********************************************
14CORE ULTRASONIC DISTANCE SENSOR CODE TEST
********************************************
*/
#define TRIGGER 4 //D2
#define ECHO    5 //D1
#define LED_1   16 //full led D0
#define LED_2   14 //D5
#define LED_3   12 //D6
#define LED_4   13 //D7
#define LED_5   15 //empty led D8
#define ALARM   3 //RX

// NodeMCU Pin D2 > TRIGGER | Pin D1  > ECHO

//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
//#include <WiFi.h>
extern "C" {
#include "user_interface.h"
}
//#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";
void setup() {
  Serial.begin (9600);
  Serial.println("SETUP....");
  WiFi.forceSleepBegin();                  // turn off ESP8266 RF
  //Blynk.begin(auth, ssid, pass);
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);

  //LED's and alarm
  pinMode(ALARM, OUTPUT); //alarm
  
  pinMode(LED_1, OUTPUT); //top led
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT); //empty led

  digitalWrite(ALARM, LOW);
  Serial.println("SETUP COMPLETE");
}

void loop() {
  Serial.println("INIT.....");
  //digitalWrite(BUILTIN_LED, HIGH);
  long duration, distance;
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = (duration/2) / 29.1;

  if(distance <= 0 || distance >= 400) {
    Serial.print(distance);
    Serial.println("OUT OF RANGE");
    delay(500);
    return;
  }
  
//height of tank: 83 cms
//equal divisions: 83/7 = ~12 cms

  if (distance <= 78) {
    digitalWrite(LED_5, HIGH);
  }
  else {
    digitalWrite(LED_5, LOW);
  }

  if (distance <= 68) {
    digitalWrite(LED_4, HIGH);
  }
  else {
    digitalWrite(LED_4, LOW);
  }

  if (distance <= 57) {
    digitalWrite(LED_3, HIGH);
  }
  else {
    digitalWrite(LED_3, LOW);
  }

  if (distance <= 46) {
    digitalWrite(LED_2, HIGH);
  }
  else {
    digitalWrite(LED_2, LOW);
  }

  if (distance <= 30) {
    digitalWrite(LED_1, HIGH);
  }
  else {
    digitalWrite(LED_1, LOW);
  }

  if (distance <= 22) {
    digitalWrite(ALARM, HIGH);
  }
  else {
    digitalWrite(ALARM, LOW);
  }

  Serial.print(distance);
  Serial.println("Centimeter:");
  //Blynk.virtualWrite(V5, distance);
  delay(1000);
  //Blynk.run();
}
