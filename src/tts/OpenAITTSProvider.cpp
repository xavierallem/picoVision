#include "OpenAITTSProvider.h"
#include <ArduinoJson.h>

AudioBuffer OpenAITTSProvider::synthesize(
    NetworkManager& networkManager,
    const ProviderConfig& config,
    const String& text
) {
    Serial.println("Sending text to OpenAI for speech synthesis...");

    String url = "https://api.openai.com/v1/audio/speech";
    
    JsonDocument doc;
    doc["model"] = config.model;
    doc["input"] = text;
    doc["voice"] = config.voice;

    String requestBody;
    serializeJson(doc, requestBody);

    return networkManager.postForBinary(url, config.api_key, requestBody);
}
