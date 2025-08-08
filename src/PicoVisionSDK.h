#ifndef PICOVISION_SDK_H
#define PICOVISION_SDK_H

#include "core/types.h"
#include "hal/CameraManager.h"
#include "hal/AudioManager.h"
#include "services/NetworkManager.h"
#include "services/VisionService.h"
#include "services/STTService.h"
#include "services/TTSService.h"
#include "hal/DisplayManager.h" // Include for DisplayManager
// Concrete Vision Providers are included in .cpp where they are instantiated
// #include "vision/OpenRouterProvider.h"
// #include "vision/OllamaProvider.h"
#include "stt/BaseSTTProvider.h"
#include "stt/OpenRouterSTTProvider.h"
#include "tts/BaseTTSProvider.h"
#include "tts/OpenAITTSProvider.h"
#include <memory>

/**
 * @class PicoVisionSDK
 * @brief The main entry point for the PicoVision SDK.
 * 
 * This class initializes and manages all hardware and AI services.
 */
class PicoVisionSDK {
public:
    PicoVisionSDK();

    /**
     * @brief Initializes the SDK and all its components.
     * @param config The configuration struct for the SDK.
     * @return True if initialization was successful, false otherwise.
     */
    bool begin(const PicoVisionConfig& config);

    // Publicly accessible managers and services
    CameraManager cameraManager;
    AudioManager audioManager;
    NetworkManager networkManager;
    VisionService visionService;
    STTService sttService;
    TTSService ttsService;
#ifdef PICOVISION_HAS_DISPLAY
    DisplayManager displayManager; // Add DisplayManager
#endif

private:
    PicoVisionConfig sdk_config;
};

#endif // PICOVISION_SDK_H
