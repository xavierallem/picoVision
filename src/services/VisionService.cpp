#include "VisionService.h"
#include "mbedtls/base64.h"

VisionService::VisionService(NetworkManager& nm) : networkManager(nm) {}

void VisionService::setProvider(std::unique_ptr<BaseVisionProvider> provider) {
    visionProvider = std::move(provider);
}

String VisionService::analyzeImage(const ProviderConfig& config, camera_fb_t* image, const String& prompt) {
    if (!visionProvider) {
        Serial.println("ERROR: Vision provider not set!");
        return "";
    }
    if (!image) {
        Serial.println("ERROR: Invalid image buffer passed to VisionService.");
        return "";
    }

    String image_b64 = base64Encode(image->buf, image->len);
    if (image_b64.length() == 0) {
        Serial.println("ERROR: Base64 encoding failed.");
        return "";
    }

    return visionProvider->analyzeImage(networkManager, config, image_b64, prompt);
}

String VisionService::base64Encode(const uint8_t* data, size_t size) {
    size_t output_size = 0;
    mbedtls_base64_encode(NULL, 0, &output_size, data, size);

    // The output buffer needs to be a String, so we allocate it dynamically.
    // Using a std::vector<unsigned char> is safer here.
    std::vector<unsigned char> output_buf(output_size);

    if (mbedtls_base64_encode(output_buf.data(), output_size, &output_size, data, size) != 0) {
        return ""; // Encoding failed
    }

    return String((char*)output_buf.data());
}
