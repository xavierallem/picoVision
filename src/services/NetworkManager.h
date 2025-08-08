#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <Arduino.h>
#include "hal/Audio.h" // Using AudioBuffer for consistency

class NetworkManager {
public:
    NetworkManager();
    void begin();
    bool isConnected();
    
    // Sends a JSON POST request and expects a JSON string response
    String post(const String& url, const String& payload, const String& apiKey = "");

    // Sends a multipart/form-data POST request for file uploads
    String postMultipart(const String& url, const String& apiKey, const uint8_t* data, size_t dataSize, const String& model);

    // Sends a JSON POST request and expects a binary response (like an audio file)
    AudioBuffer postForBinary(const String& url, const String& apiKey, const String& payload);

private:
    void connectWiFi();
};

#endif // NETWORK_MANAGER_H
