
/**
 *
 *
 * By: ApoAlquaary
 *
 */

#include <Arduino.h>
#include "WiFi.h"
#include "ThingSpeak.h"

#define CHANNEL_ID // write the ID
#define CHANNEL_API_KEY // write the API Key


#define WIFI_TIMEOUT_MS 20000
#define WIFI_NETWORK "SSID"
#define WIFI_PASSWORD "Password"

WiFiClient client;

int counter = 0;

void connectToWifi(){
  Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
  unsigned long startAttempTime = millis();

  while(WiFi.status() != WL_CONNECTED && millis() - startAttempTime < WIFI_TIMEOUT_MS){
    Serial.print(".");
    delay(100);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Faild!");
  }else{
    Serial.println(WiFi.localIP());
  }

}

int sensor =4 ;
int yesil_led = 23;
int kirmizi_led = 22;
int zil = 21;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  connectToWifi();
  ThingSpeak.begin(client);
  pinMode(sensor, INPUT);
  pinMode(yesil_led, OUTPUT);
  pinMode(kirmizi_led, OUTPUT);
  pinMode(zil, OUTPUT);

}

void loop() {
  counter++;
  // put your main code here, to run repeatedly:
  Serial.println("nice\n");
  int X = digitalRead(sensor);

  if(X == false){
    digitalWrite(yesil_led, HIGH);
    digitalWrite(kirmizi_led, LOW);
    digitalWrite(zil, LOW);

  }else{
    digitalWrite(kirmizi_led, HIGH);
    digitalWrite(zil, HIGH);
    digitalWrite(yesil_led, LOW);

  }
  ThingSpeak.writeField(CHANNEL_ID, 1, X, CHANNEL_API_KEY);
  delay(500);
}
