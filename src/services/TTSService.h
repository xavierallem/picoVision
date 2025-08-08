#ifndef TTS_SERVICE_H
#define TTS_SERVICE_H

#include "services/NetworkManager.h"
#include "tts/BaseTTSProvider.h"
#include "hal/Audio.h"
#include "core/types.h"
#include <Arduino.h>
#include <memory>

/**
 * @class TTSService
 * @brief Manages the process of synthesizing speech with a configured TTS provider.
 */
class TTSService {
public:
    TTSService(NetworkManager& nm);

    /**
     * @brief Sets the TTS provider to be used for speech synthesis.
     * @param provider A unique_ptr to an object that implements BaseTTSProvider.
     */
    void setProvider(std::unique_ptr<BaseTTSProvider> provider);
    
    /**
     * @brief Synthesizes speech from text using the configured provider.
     * 
     * @param config The provider-specific configuration.
     * @param text The text to synthesize.
     * @return An AudioBuffer containing the synthesized audio data. Returns an empty buffer on failure.
     */
    AudioBuffer synthesize(const ProviderConfig& config, const String& text);

private:
    NetworkManager& networkManager;
    std::unique_ptr<BaseTTSProvider> ttsProvider;
};

#endif // TTS_SERVICE_H
