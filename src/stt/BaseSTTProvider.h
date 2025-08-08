#ifndef BASE_STT_PROVIDER_H
#define BASE_STT_PROVIDER_H

#include <Arduino.h>
#include "core/types.h"
#include "services/NetworkManager.h"
#include "hal/Audio.h"

/**
 * @class BaseSTTProvider
 * @brief Abstract base class for Speech-to-Text (STT) model providers.
 * 
 * Defines the interface for sending audio data to an STT model
 * and receiving transcribed text.
 */
class BaseSTTProvider {
public:
    virtual ~BaseSTTProvider() {}

    /**
     * @brief Transcribes audio data using the STT model.
     * 
     * @param networkManager A reference to the network manager for making API calls.
     * @param config The provider-specific configuration (API key, model, etc.).
     * @param audioBuffer The buffer containing the audio data to transcribe.
     * @return A String containing the transcribed text. Returns an empty string on failure.
     */
    virtual String transcribe(NetworkManager& networkManager, const ProviderConfig& config, AudioBuffer& audioBuffer) = 0;
};

#endif // BASE_STT_PROVIDER_H