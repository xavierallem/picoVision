#ifndef PICOVISION_TYPES_H
#define PICOVISION_TYPES_H

#include <Arduino.h>

/**
 * @brief Configuration for AI model providers.
 */
struct ProviderConfig {
    String provider_name; // e.g., "openrouter", "ollama"
    String api_key;
    String model;
    String endpoint;
    String voice; // For TTS
};

/**
 * @brief Configuration for the I2S hardware interface.
 */
struct I2SConfig {
    // Microphone Pins
    int mic_sck_pin;
    int mic_ws_pin;
    int mic_sd_pin;
    // Speaker Pin
    int speaker_dout_pin;
};

/**
 * @brief Main configuration struct for the PicoVision SDK.
 * 
 * This struct is passed to the sdk.begin() method to configure all
 * hardware and services at runtime.
 */
struct PicoVisionConfig {
    // Network
    String wifi_ssid;
    String wifi_password;

    // Hardware
    I2SConfig i2s_config;
    int i2c_sda_pin;
    int i2c_scl_pin;

    // Services
    ProviderConfig vision_provider;
    ProviderConfig stt_provider;
    ProviderConfig tts_provider;
};

#endif // PICOVISION_TYPES_H
