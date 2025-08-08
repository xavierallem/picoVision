#include "OpenRouterProvider.h"
#include <ArduinoJson.h>

String OpenRouterProvider::analyzeImage(
    NetworkManager& networkManager,
    const ProviderConfig& config,
    const String& image_b64,
    const String& prompt
) {
    JsonDocument doc;
    doc["model"] = config.model;
    
    JsonObject msg = doc.createNestedArray("messages").createNestedObject();
    msg["role"] = "user";
    
    JsonArray content = msg.createNestedArray("content");
    
    JsonObject text_obj = content.createNestedObject();
    text_obj["type"] = "text";
    text_obj["text"] = prompt;

    JsonObject img_obj = content.createNestedObject();
    img_obj["type"] = "image_url";
    img_obj["image_url"]["url"] = "data:image/jpeg;base64," + image_b64;

    String requestBody;
    serializeJson(doc, requestBody);

    String response = networkManager.post("https://openrouter.ai/api/v1/chat/completions", requestBody, config.api_key);

    // Parse the response
    JsonDocument responseDoc;
    deserializeJson(responseDoc, response);
    return responseDoc["choices"][0]["message"]["content"].as<String>();
}
