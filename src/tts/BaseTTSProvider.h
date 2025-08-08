#ifndef BASE_TTS_PROVIDER_H
#define BASE_TTS_PROVIDER_H

#include <Arduino.h>
#include "core/types.h"
#include "services/NetworkManager.h"
#include "hal/Audio.h"

/**
 * @class BaseTTSProvider
 * @brief Abstract base class for Text-to-Speech (TTS) model providers.
 * 
 * Defines the interface for sending text to a TTS model
 * and receiving synthesized audio.
 */
class BaseTTSProvider {
public:
    virtual ~BaseTTSProvider() {}

    /**
     * @brief Synthesizes speech from text using the TTS model.
     * 
     * @param networkManager A reference to the network manager for making API calls.
     * @param config The provider-specific configuration (API key, model, voice, etc.).
     * @param text The text to synthesize.
     * @return An AudioBuffer containing the synthesized audio data. Returns an empty buffer on failure.
     */
    virtual AudioBuffer synthesize(NetworkManager& networkManager, const ProviderConfig& config, const String& text) = 0;
};

#endif // BASE_TTS_PROVIDER_H