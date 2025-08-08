#include "TTSService.h"
#include "core/Config.h"
#include <ArduinoJson.h>

TTSService::TTSService(NetworkManager& nm) : networkManager(nm) {}

void TTSService::setProvider(std::unique_ptr<BaseTTSProvider> provider) {
    ttsProvider = std::move(provider);
}

AudioBuffer TTSService::synthesize(const ProviderConfig& config, const String& text) {
    if (!ttsProvider) {
        Serial.println("ERROR: TTS provider not set!");
        return {nullptr, 0};
    }
    return ttsProvider->synthesize(networkManager, config, text);
}