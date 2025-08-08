#ifndef BASE_VISION_PROVIDER_H
#define BASE_VISION_PROVIDER_H

#include <Arduino.h>
#include "core/types.h"
#include "hal/CameraManager.h"
#include "services/NetworkManager.h"

/**
 * @class BaseVisionProvider
 * @brief Abstract base class for vision model providers.
 * 
 * Defines the interface for sending an image and a prompt to a vision model
 * and receiving a textual description.
 */
class BaseVisionProvider {
public:
    virtual ~BaseVisionProvider() {}

    /**
     * @brief Analyzes an image with a given prompt.
     * 
     * @param networkManager A reference to the network manager for making API calls.
     * @param config The provider-specific configuration (API key, model, etc.).
     * @param image_b64 The Base64-encoded image data.
     * @param prompt The text prompt to send with the image.
     * @return A String containing the model's response.
     */
    virtual String analyzeImage(
        NetworkManager& networkManager,
        const ProviderConfig& config,
        const String& image_b64,
        const String& prompt
    ) = 0;
};

#endif // BASE_VISION_PROVIDER_H
