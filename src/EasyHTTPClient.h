// EasyHTTPClient.h

#ifndef EasyHTTPClient_h
#define EasyHTTPClient_h

#include <Arduino.h>
#include <EasyHTTP.h>

class EasyHTTPClient {
public:
  EasyHTTPClient(char* ssid, char* password, const char* serverName);

  void setup();
  void sendData();

private:
  char* ssid;
  char* password;
  const char* serverName;
  EasyHTTP http;

  unsigned long lastTime = 0;
  unsigned long timerDelay = 5000;
};

#endif
