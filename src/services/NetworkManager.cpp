#include "NetworkManager.h"
#include "core/Config.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

NetworkManager::NetworkManager() {}

void NetworkManager::begin() {
    connectWiFi();
}

bool NetworkManager::isConnected() {
    return (WiFi.status() == WL_CONNECTED);
}

void NetworkManager::connectWiFi() {
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

String NetworkManager::post(const String& url, const String& payload, const String& apiKey) {
    if (!isConnected()) return "{\"error\":\"wifi_disconnected\"}";

    WiFiClientSecure client;
    HTTPClient http;
    client.setInsecure();

    if (http.begin(client, url)) {
        http.addHeader("Content-Type", "application/json");
        if (apiKey.length() > 0) {
            http.addHeader("Authorization", "Bearer " + apiKey);
        }
        
        int httpCode = http.POST(payload);
        if (httpCode > 0) {
            String response = http.getString();
            http.end();
            return response;
        } else {
            String errorPayload = "{\"error\":\"http_post_failed\", \"code\":\"" + http.errorToString(httpCode) + "\", \"response\":\"" + http.getString() + "\"}";
            http.end();
            return errorPayload;
        }
    } else {
        return "{\"error\":\"http_connection_failed\"}";
    }
}

AudioBuffer NetworkManager::postForBinary(const String& url, const String& apiKey, const String& payload) {
    if (!isConnected()) return {nullptr, 0};

    WiFiClientSecure client;
    HTTPClient http;
    client.setInsecure();

    if (http.begin(client, url)) {
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", "Bearer " + apiKey);
        
        int httpCode = http.POST(payload);
        if (httpCode == 200) {
            int len = http.getSize();
            uint8_t* buffer = (uint8_t*)malloc(len);
            if (!buffer) {
                Serial.println("Failed to allocate memory for audio buffer");
                http.end();
                return {nullptr, 0};
            }
            WiFiClient* stream = http.getStreamPtr();
            stream->readBytes(buffer, len);
            http.end();
            return {buffer, (size_t)len};
        } else {
            Serial.printf("[HTTP] Binary POST failed, error %d: %s\n", httpCode, http.getString().c_str());
            http.end();
            return {nullptr, 0};
        }
    } else {
        return {nullptr, 0};
    }
}

String NetworkManager::postMultipart(const String& url, const String& apiKey, const uint8_t* data, size_t dataSize, const String& model) {
    if (!isConnected()) return "{\"error\":\"wifi_disconnected\"}";

    WiFiClientSecure client;
    HTTPClient http;
    client.setInsecure();

    if (http.begin(client, url)) {
        String boundary = "----WebKitFormBoundary7MA4YWxkTrZu0gW";
        http.addHeader("Content-Type", "multipart/form-data; boundary=" + boundary);
        http.addHeader("Authorization", "Bearer " + apiKey);

        String start_request = "--" + boundary + "\r\n";
        start_request += "Content-Disposition: form-data; name=\"file\"; filename=\"audio.wav\"\r\n";
        start_request += "Content-Type: audio/wav\r\n\r\n";

        String end_request = "\r\n--" + boundary + "\r\n";
        end_request += "Content-Disposition: form-data; name=\"model\"\r\n\r\n";
        end_request += model + "\r\n";
        end_request += "--" + boundary + "--\r\n";

        size_t total_len = start_request.length() + dataSize + end_request.length();
        
        http.setContentLength(total_len);
        WiFiClient* stream = http.getStreamPtr();
        stream->write(start_request.c_str(), start_request.length());
        stream->write(data, dataSize);
        stream->write(end_request.c_str(), end_request.length());
        
        int httpCode = http.POST((uint8_t*)nullptr, 0);
        
        if (httpCode == 200) {
            String response = http.getString();
            http.end();
            return response;
        } else {
            String responseBody = http.getString();
            Serial.printf("[HTTP] Multipart POST failed, error %d: %s\n", httpCode, responseBody.c_str());
            http.end();
            return "{\"error\":\"http_multipart_failed\", \"code\":" + String(httpCode) + "}";
        }
    } else {
        return "{\"error\":\"http_connection_failed\"}";
    }
}