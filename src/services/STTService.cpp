#include "STTService.h"
#include "core/Config.h"
#include <ArduinoJson.h>

STTService::STTService(NetworkManager& nm) : networkManager(nm) {}

void STTService::setProvider(std::unique_ptr<BaseSTTProvider> provider) {
    sttProvider = std::move(provider);
}

String STTService::transcribe(const ProviderConfig& config, AudioBuffer& audioBuffer) {
    if (!sttProvider) {
        Serial.println("ERROR: STT provider not set!");
        return "";
    }
    if (!audioBuffer.data || audioBuffer.size == 0) {
        Serial.println("ERROR: Invalid audio buffer passed to STTService.");
        return "";
    }
    return sttProvider->transcribe(networkManager, config, audioBuffer);
}