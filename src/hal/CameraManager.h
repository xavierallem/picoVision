#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "esp_camera.h"

// AI-Thinker ESP32-CAM Pin Map
#define CAM_PIN_PWDN 32
#define CAM_PIN_RESET -1 //software reset will be performed
#define CAM_PIN_XCLK 0
#define CAM_PIN_SIOD 26
#define CAM_PIN_SIOC 27
#define CAM_PIN_D7 35
#define CAM_PIN_D6 34
#define CAM_PIN_D5 39
#define CAM_PIN_D4 36
#define CAM_PIN_D3 21
#define CAM_PIN_D2 19
#define CAM_PIN_D1 18
#define CAM_PIN_D0 5
#define CAM_PIN_VSYNC 25
#define CAM_PIN_HSYNC 23
#define CAM_PIN_PCLK 22

class CameraManager {
public:
    CameraManager();
    bool begin();
    camera_fb_t* captureImage();
    void releaseImage(camera_fb_t* fb);

private:
    camera_config_t config;
};

#endif // CAMERA_MANAGER_H
