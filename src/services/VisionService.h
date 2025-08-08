#ifndef VISION_SERVICE_H
#define VISION_SERVICE_H

#include "services/NetworkManager.h"
#include "hal/CameraManager.h"
#include "vision/BaseVisionProvider.h"
#include "core/types.h"
#include <memory>

/**
 * @class VisionService
 * @brief Manages the process of analyzing an image with a configured vision provider.
 */
class VisionService {
public:
    VisionService(NetworkManager& nm);

    /**
     * @brief Sets the vision provider to be used for analysis.
     * @param provider A unique_ptr to an object that implements BaseVisionProvider.
     */
    void setProvider(std::unique_ptr<BaseVisionProvider> provider);

    /**
     * @brief Analyzes an image using the configured provider.
     * 
     * This method handles Base64 encoding the image before passing it to the provider.
     * 
     * @param config The provider-specific configuration.
     * @param image The camera frame buffer containing the image.
     * @param prompt The text prompt to send with the image.
     * @return A String containing the model's response. Returns an empty string on failure.
     */
    String analyzeImage(const ProviderConfig& config, camera_fb_t* image, const String& prompt);

private:
    NetworkManager& networkManager;
    std::unique_ptr<BaseVisionProvider> visionProvider;

    String base64Encode(const uint8_t* data, size_t size);
};

#endif // VISION_SERVICE_H
