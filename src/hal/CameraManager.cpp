#include "CameraManager.h"
#include <Arduino.h>

CameraManager::CameraManager() {
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = CAM_PIN_D0;
    config.pin_d1 = CAM_PIN_D1;
    config.pin_d2 = CAM_PIN_D2;
    config.pin_d3 = CAM_PIN_D3;
    config.pin_d4 = CAM_PIN_D4;
    config.pin_d5 = CAM_PIN_D5;
    config.pin_d6 = CAM_PIN_D6;
    config.pin_d7 = CAM_PIN_D7;
    config.pin_xclk = CAM_PIN_XCLK;
    config.pin_pclk = CAM_PIN_PCLK;
    config.pin_vsync = CAM_PIN_VSYNC;
    config.pin_hsync = CAM_PIN_HSYNC;
    config.pin_sscb_sda = CAM_PIN_SIOD;
    config.pin_sscb_scl = CAM_PIN_SIOC;
    config.pin_pwdn = CAM_PIN_PWDN;
    config.pin_reset = CAM_PIN_RESET;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG; // Use JPEG for smaller image size
    
    // Frame size and quality can be adjusted to balance detail and payload size.
    // SVGA (800x600) is a good starting point.
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12; // 0-63, lower means higher quality and larger size
    config.fb_count = 1; // Use 1 frame buffer to save RAM
}

bool CameraManager::begin() {
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return false;
    }
    Serial.println("Camera Manager Initialized");
    return true;
}

camera_fb_t* CameraManager::captureImage() {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        Serial.println("Camera capture failed");
        return nullptr;
    }
    return fb;
}

void CameraManager::releaseImage(camera_fb_t* fb) {
    if (fb) {
        esp_camera_fb_return(fb);
    }
}
