#include <Wire.h>
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>
#include "DHT.h"
DHT dht(32, DHT11);
#define relay 33
#define green 23
#define blue 19
#define red 18

char ssid[] = "UMR-LAB_2";
char wifiPassword[] = "Ubon2565";

//website > create esp8266 > copy data and paste below.
char username[] = "be1f8690-a5ee-11ed-b193-d9789b2af62b";
char password[] = "9912a0cce4ba397137e6b3db0612b8310a5de679";
char clientID[] = "cdefd8f0-a5f2-11ed-8d53-d7cd1025126a";
float temp(NAN), hum(NAN), tempf(NAN);

void setup() {
  //Config pin modes
  pinMode(relay, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  dht.begin();
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
  delay(2000);
}

CAYENNE_OUT(0){
  float temp = dht.readTemperature();
  Cayenne.virtualWrite(0, temp);
}

CAYENNE_OUT(1){
  float hum = dht.readHumidity();
  Cayenne.virtualWrite(1, hum);
}

CAYENNE_OUT(2){
  float tempf = dht.readTemperature(true);
  Cayenne.virtualWrite(2, tempf);
}

CAYENNE_IN(12){
  int i = getValue.asInt();
  if (i == 1) { digitalWrite(relay, HIGH); }
  else {
    digitalWrite(relay, LOW);
  }
}

CAYENNE_IN(13){
  int i = getValue.asInt();
  if (i == 1) { digitalWrite(green, HIGH); }
  else {
    digitalWrite(green, LOW);
  }
}

CAYENNE_IN(14){
  int i = getValue.asInt();
  if (i == 1) { digitalWrite(blue, HIGH); }
  else {
    digitalWrite(blue, LOW);
  }
}

CAYENNE_IN(15){
  int i = getValue.asInt();
  if (i == 1) { digitalWrite(red, HIGH); }
  else {
    digitalWrite(red, LOW);
  }
}

