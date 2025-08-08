#ifndef OLLAMA_PROVIDER_H
#define OLLAMA_PROVIDER_H

#include "vision/BaseVisionProvider.h"

/**
 * @class OllamaProvider
 * @brief Implements the vision provider interface for a local Ollama server.
 */
class OllamaProvider : public BaseVisionProvider {
public:
    String analyzeImage(
        NetworkManager& networkManager,
        const ProviderConfig& config,
        const String& image_b64,
        const String& prompt
    ) override;
};

#endif // OLLAMA_PROVIDER_H
