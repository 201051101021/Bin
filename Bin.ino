#include <Servo.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include "binary.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

long lastMsg = 0;
char msg[50];
int value = 0;
int dhtPin = 13;
float humi , temp;
DHT dht(13, DHT11);
int trigPin = 14;
int echoPin = 12;
long distance;
long duration;

LiquidCrystal_I2C lcd(0x3F,20,4);

const char* ssid = "ManPai";
const char* password = "Chaaymja2";
const char* mqtt_server = "8d1308905f42.sn.mynetname.net";
const char* mqttuser = "dove";
const char* mqttpass = "dove1234";
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dht.begin();
  
}
void dhtGet() {
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  if (isnan(temp) || isnan(humi)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" *C \t");
    Serial.print('\n');
    lcd.begin();                       
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.print("Humidity: ");
    lcd.print(humi);
    lcd.print(" %");
    lcd.setCursor(1,2);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print(" celsius");
    delay(1000);
  }
}

void ultra() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("distance: ");
  Serial.println(distance);
  delay(1000);
}

void loop() {
  dhtGet();
  ultra();
}
