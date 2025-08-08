#ifndef OPENAI_TTS_PROVIDER_H
#define OPENAI_TTS_PROVIDER_H

#include "BaseTTSProvider.h"

/**
 * @class OpenAITTSProvider
 * @brief Implements the TTS provider interface for OpenAI's TTS API.
 */
class OpenAITTSProvider : public BaseTTSProvider {
public:
    AudioBuffer synthesize(NetworkManager& networkManager, const ProviderConfig& config, const String& text) override;
};

#endif // OPENAI_TTS_PROVIDER_H
