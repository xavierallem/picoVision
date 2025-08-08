#ifndef OPENROUTER_PROVIDER_H
#define OPENROUTER_PROVIDER_H

#include "vision/BaseVisionProvider.h"

/**
 * @class OpenRouterProvider
 * @brief Implements the vision provider interface for OpenRouter.
 */
class OpenRouterProvider : public BaseVisionProvider {
public:
    String analyzeImage(
        NetworkManager& networkManager,
        const ProviderConfig& config,
        const String& image_b64,
        const String& prompt
    ) override;
};

#endif // OPENROUTER_PROVIDER_H
