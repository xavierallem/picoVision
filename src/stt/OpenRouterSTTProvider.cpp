#include "OpenRouterSTTProvider.h"
#include <ArduinoJson.h>

String OpenRouterSTTProvider::transcribe(
    NetworkManager& networkManager,
    const ProviderConfig& config,
    AudioBuffer& audioBuffer
) {
    Serial.println("Sending audio to OpenRouter for transcription...");

    String url = "https://openrouter.ai/api/v1/audio/transcriptions";
    String response = networkManager.postMultipart(url, config.api_key, audioBuffer.data, audioBuffer.size, config.model);

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, response);

    if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return "Error parsing response";
    }

    return doc["text"].as<String>();
}
