// EasyHTTPClient.cpp

#include "EasyHTTPClient.h"
#include <ArduinoJson.h>

EasyHTTPClient::EasyHTTPClient(char* ssid, char* password, const char* serverName)
  : ssid(ssid), password(password), serverName(serverName), http(ssid, password) {}

void EasyHTTPClient::setup() {
  Serial.begin(115200);
  http.connectWiFi();
  http.setBaseURL(serverName);
}

void EasyHTTPClient::sendData() {
  DynamicJsonDocument doc(32);
  String payload = "";

  doc["image"] = "";
  serializeJson(doc, payload);
  String response = http.post("/ai", payload);
  Serial.println(response);

  delay(3000);
}
