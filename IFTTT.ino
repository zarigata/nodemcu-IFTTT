#include "IFTTTWebhook.h"
#include <ESP8266WiFi.h>
//----------------------
#define ssid "SSDI"
#define password "PASSWORD"
#define IFTTT_API_KEY "YOUR GENERATED KEY"
#define IFTTT_EVENT_NAME "EVENT NAME"
//-----------------------------
//ARDUINO ID
int cl = 5;
int sent = 14;
int button = 4;
int buttonState = 0;
//-----------------------------
void setup() {
  Serial.begin(115200);
 // while (!Serial) {
 // }
  Serial.println(" ");
  Serial.println(" ");
  connectToWifi();
  pinMode (cl , OUTPUT);
  pinMode (button , INPUT);
  pinMode (sent , OUTPUT);
  //ESP.deepSleep(wakePin);

}



void connectToWifi() {
  digitalWrite(cl, LOW);
  Serial.print("Connecting to: "); //uncomment next line to show SSID name
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  Serial.println(" ");// print an empty line
  Serial.print("Attempting to connect: ");

  //try to connect for 10 seconds
  int i = 20;
  while (WiFi.status() != WL_CONNECTED && i >= 0) {
    delay(700);
    Serial.print(i);
    Serial.print(", ");
    i--;
  }
  Serial.println(" ");// print an empty line

  //print connection result
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected.");
    Serial.println(" ");// print an empty line
    Serial.print("NodeMCU ip address: ");
    Serial.println(WiFi.localIP());
    analogWrite(cl , 15);
  }
  else {
    Serial.println("Connection failed - check your credentials or connection");
    delay(60000);
    ESP.restart();
  }
}
void loop()
{
  buttonState = digitalRead(button);
  if (buttonState == 1)
  {
    analogWrite(sent , 50);
    IFTTTWebhook hook(IFTTT_API_KEY, IFTTT_EVENT_NAME);
   // hook.trigger();
    Serial.println("SENT");
    delay (5000);

  }
  if (buttonState == 0)
  {
    analogWrite(sent , LOW);
    Serial.println("NOT   SENT");
    delay (100);
  }
}
