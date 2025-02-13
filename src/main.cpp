#include "EasyHTTPClient.h"

 char* ssid = "";
 char* password  = "";
  const char* serverName = "";

EasyHTTPClient httpClient(ssid, password, serverName);

void setup() {
  httpClient.setup();
}

void loop() {
  httpClient.sendData();
}
