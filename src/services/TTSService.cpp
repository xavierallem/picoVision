#include "TTSService.h"
#include "core/Config.h"
#include <ArduinoJson.h>

TTSService::TTSService(NetworkManager& nm) : networkManager(nm) {}

AudioBuffer TTSService::synthesizeSpeech(const String& text) {
    Serial.println("Sending text to OpenAI for speech synthesis...");

    String url = "https://api.openai.com/v1/audio/speech";
    
    JsonDocument doc;
    doc["model"] = OPENAI_TTS_MODEL;
    doc["input"] = text;
    doc["voice"] = OPENAI_TTS_VOICE;

    String requestBody;
    serializeJson(doc, requestBody);

    return networkManager.postForBinary(url, OPENAI_API_KEY, requestBody);
}

