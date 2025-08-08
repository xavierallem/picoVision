#ifndef STT_SERVICE_H
#define STT_SERVICE_H

#include "services/NetworkManager.h"
#include "stt/BaseSTTProvider.h"
#include "hal/Audio.h"
#include "core/types.h"
#include <Arduino.h>
#include <memory>

/**
 * @class STTService
 * @brief Manages the process of transcribing audio with a configured STT provider.
 */
class STTService {
public:
    STTService(NetworkManager& nm);

    /**
     * @brief Sets the STT provider to be used for transcription.
     * @param provider A unique_ptr to an object that implements BaseSTTProvider.
     */
    void setProvider(std::unique_ptr<BaseSTTProvider> provider);

    /**
     * @brief Transcribes audio data using the configured provider.
     * 
     * @param config The provider-specific configuration.
     * @param audioBuffer The buffer containing the audio data to transcribe.
     * @return A String containing the transcribed text. Returns an empty string on failure.
     */
    String transcribe(const ProviderConfig& config, AudioBuffer& audioBuffer);

private:
    NetworkManager& networkManager;
    std::unique_ptr<BaseSTTProvider> sttProvider;
};

#endif // STT_SERVICE_H
