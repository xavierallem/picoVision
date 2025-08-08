#include "PicoVisionSDK.h"
#include "vision/OllamaProvider.h"

PicoVisionSDK::PicoVisionSDK() : 
    networkManager(),
    visionService(networkManager),
    sttService(networkManager),
    ttsService(networkManager) 
{}

bool PicoVisionSDK::begin(const PicoVisionConfig& config) {
    sdk_config = config;

    // Initialize hardware
    networkManager.begin(sdk_config.wifi_ssid.c_str(), sdk_config.wifi_password.c_str());
    cameraManager.begin();
    audioManager.begin(sdk_config.i2s_config);
#ifdef PICOVISION_HAS_DISPLAY
    displayManager.begin(sdk_config.i2c_sda_pin, sdk_config.i2c_scl_pin);
#endif

    // --- Initialize AI Service Providers ---

    // Vision Provider
    if (sdk_config.vision_provider.provider_name.equalsIgnoreCase("ollama")) {
        visionService.setProvider(std::make_unique<OllamaProvider>());
        Serial.println("Using Ollama for Vision Service.");
    } else {
        visionService.setProvider(std::make_unique<OpenRouterProvider>());
        Serial.println("Using OpenRouter for Vision Service.");
    }

    // STT Provider
    sttService.setProvider(std::make_unique<WhisperProvider>());
    
    // TTS Provider
    ttsService.setProvider(std::make_unique<OpenAITTSProvider>());

    Serial.println("PicoVision SDK Initialized.");
    return true;
}
