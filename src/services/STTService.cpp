#include "STTService.h"
#include "core/Config.h"
#include <ArduinoJson.h>

STTService::STTService(NetworkManager& nm) : networkManager(nm) {}

String STTService::transcribeAudio(const uint8_t* audioData, size_t dataSize) {
    Serial.println("Sending audio to OpenRouter for transcription...");

    String url = "https://openrouter.ai/api/v1/audio/transcriptions";
    String response = networkManager.postMultipart(url, OPENROUTER_API_KEY, audioData, dataSize, OPENROUTER_STT_MODEL);

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, response);

    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return "Error parsing response";
    }

    return doc["text"].as<String>();
}
