#ifndef OPENROUTER_STT_PROVIDER_H
#define OPENROUTER_STT_PROVIDER_H

#include "BaseSTTProvider.h"

/**
 * @class OpenRouterSTTProvider
 * @brief Implements the STT provider interface for OpenRouter's Whisper API.
 */
class OpenRouterSTTProvider : public BaseSTTProvider {
public:
    String transcribe(NetworkManager& networkManager, const ProviderConfig& config, AudioBuffer& audioBuffer) override;
};

#endif // OPENROUTER_STT_PROVIDER_H
