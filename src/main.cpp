#include "EasyHTTPClient.h"

 char* ssid = "www";
 char* password  = "P29hSk73bu";
  const char* serverName = "http://192.168.178.44:5000";

EasyHTTPClient httpClient(ssid, password, serverName);

void setup() {
  httpClient.setup();
}

void loop() {
  httpClient.sendData();
}
