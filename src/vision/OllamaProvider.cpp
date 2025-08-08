#include "OllamaProvider.h"
#include <ArduinoJson.h>

String OllamaProvider::analyzeImage(
    NetworkManager& networkManager,
    const ProviderConfig& config,
    const String& image_b64,
    const String& prompt
) {
    JsonDocument doc;
    doc["model"] = config.model;
    doc["prompt"] = prompt;
    doc["stream"] = false;
    doc.createNestedArray("images").add(image_b64);

    String requestBody;
    serializeJson(doc, requestBody);

    // Note: Ollama typically does not require an API key.
    String response = networkManager.post(config.endpoint, requestBody);

    // Parse the response
    JsonDocument responseDoc;
    deserializeJson(responseDoc, response);
    return responseDoc["response"].as<String>();
}
