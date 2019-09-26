/*
 *  This sketch demonstrates how to scan WiFi networks. 
 *  The API is almost the same as with the WiFi Shield library, 
 *  the most obvious difference being the different file you need to include:
 */
//#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//https://github.com/schinken/SimpleTimer
#include <SimpleTimer.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxxxxxxxxxxxxxxxxx";

float vref = 3.3;
float resolution = vref / 1023.0;
float temperature;

SimpleTimer timer;

BLYNK_CONNECTED() {
  // Request Blynk server to re-send latest values for all pins
  Blynk.syncAll();
}

void setup()
{
  Serial.begin(9600);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  Blynk.begin(auth, "xxxxxxxxxxx", "yyyyyyyyyyyyyy");
  timer.setInterval(60000, sendUptime);
}

void sendUptime()
{
  float temperature = analogRead(A0);//lm35 is connected to pin A0 on NodeMcu
  temperature = (temperature * resolution);
  temperature = temperature * 100.0;
  //Serial.print("LM35 temperature: ");//serial print the value 
  //Serial.println(temperature);
  Blynk.virtualWrite(V0, temperature);//send the value to blynk application
}

void loop()
{
  Blynk.run();
  timer.run();
}
