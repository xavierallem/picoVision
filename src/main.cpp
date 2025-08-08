#include <Arduino.h>
#include "PicoVisionSDK.h"
#include "core/Config.h" // For loading credentials

PicoVisionSDK sdk;

// --- Pin Definitions ---
#define BUTTON_PIN 13 
#define LED_PIN 4

// RTC_GPIO_NUM_13 is the corresponding RTC pin for GPIO 13
#define BUTTON_WAKEUP_PIN RTC_GPIO_NUM_13

void handle_interaction() {
  digitalWrite(LED_PIN, HIGH); 
  Serial.println("Button pressed. Starting interaction.");
#ifdef PICOVISION_HAS_DISPLAY
  sdk.displayManager.showMessage("Button pressed.\nStarting interaction.");
#endif
  
  // 1. Record Audio
#ifdef PICOVISION_HAS_DISPLAY
  sdk.displayManager.showMessage("Recording Audio...");
#endif
  AudioBuffer recordedAudio = sdk.audioManager.recordAudio(3000);

  // 2. Transcribe Audio
#ifdef PICOVISION_HAS_DISPLAY
  sdk.displayManager.showMessage("Transcribing Audio...");
#endif
  String question = sdk.sttService.transcribe(sdk.sdk_config.stt_provider, recordedAudio);
  sdk.audioManager.releaseAudio(recordedAudio);
  
  Serial.printf("Transcription: \"%s\"\n", question.c_str());
  if (question.isEmpty()) {
      Serial.println("Transcription failed. Aborting.");
#ifdef PICOVISION_HAS_DISPLAY
      sdk.displayManager.showMessage("Transcription failed.\nAborting.");
#endif
      digitalWrite(LED_PIN, LOW);
      return;
  }

  // 3. Capture Image
#ifdef PICOVISION_HAS_DISPLAY
  sdk.displayManager.showMessage("Capturing Image...");
#endif
  camera_fb_t* fb = sdk.cameraManager.captureImage();
  if (!fb) {
    Serial.println("Failed to capture image.");
#ifdef PICOVISION_HAS_DISPLAY
    sdk.displayManager.showMessage("Image capture failed.");
#endif
    digitalWrite(LED_PIN, LOW);
    return;
  }

  // 4. Analyze Image with the transcribed question
#ifdef PICOVISION_HAS_DISPLAY
  sdk.displayManager.showMessage("Analyzing Image...");
#endif
  String description = sdk.visionService.analyzeImage(sdk.sdk_config.vision_provider, fb, question);
  sdk.cameraManager.releaseImage(fb);

  // 5. Synthesize and Play Response
  if (!description.isEmpty()) {
    Serial.printf("Vision Response: \"%s\"\n", description.c_str());
#ifdef PICOVISION_HAS_DISPLAY
    sdk.displayManager.showMessage("Synthesizing Speech...");
#endif
    Serial.println("Synthesizing response to audio...");
    AudioBuffer speech = sdk.ttsService.synthesize(sdk.sdk_config.tts_provider, description);
#ifdef PICOVISION_HAS_DISPLAY
    sdk.displayManager.showMessage("Playing Response...");
#endif
    sdk.audioManager.playAudio(speech);
  } else {
    Serial.println("Failed to get vision description.");
#ifdef PICOVISION_HAS_DISPLAY
    sdk.displayManager.showMessage("Vision failed.");
#endif
  }

  digitalWrite(LED_PIN, LOW);
  Serial.println("Interaction complete. Entering deep sleep.\n");
#ifdef PICOVISION_HAS_DISPLAY
  sdk.displayManager.showMessage("Interaction complete.\nSleeping...");
#endif
  // A small delay to ensure the serial message is sent before sleeping
  delay(100); 
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Configure the button pin as a wake-up source
  esp_sleep_enable_ext0_wakeup(BUTTON_WAKEUP_PIN, 0); // Wake up when button is LOW

  // Check if we were woken up from deep sleep
  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) {
    // Woken up by button, proceed to initialize and handle interaction
    PicoVisionConfig config;
    config.wifi_ssid = WIFI_SSID;
    config.wifi_password = WIFI_PASSWORD;
    config.i2s_config = {I2S_MIC_SCK_PIN, I2S_MIC_WS_PIN, I2S_MIC_SD_PIN, I2S_SPEAKER_DOUT_PIN};
    config.i2c_sda_pin = I2C_SDA_PIN; // Populate I2C SDA pin
    config.i2c_scl_pin = I2C_SCL_PIN; // Populate I2C SCL pin
    config.vision_provider.provider_name = VISION_PROVIDER;
    if (String(VISION_PROVIDER).equalsIgnoreCase("ollama")) {
        config.vision_provider.model = OLLAMA_VISION_MODEL;
        config.vision_provider.endpoint = OLLAMA_ENDPOINT;
    } else {
        config.vision_provider.api_key = OPENROUTER_API_KEY;
        config.vision_provider.model = OPENROUTER_VISION_MODEL;
    }
    config.stt_provider = { "openrouter", OPENROUTER_API_KEY, OPENROUTER_STT_MODEL };
    config.tts_provider = { "openai", OPENAI_API_KEY, OPENAI_TTS_MODEL, "", OPENAI_TTS_VOICE };
    
    sdk.begin(config);
    handle_interaction();
  } else {
    // First boot
    Serial.println("\n========================================\n");
    Serial.println("      PicoVision SDK Initialized      ");
    Serial.println("========================================\n");
#ifdef PICOVISION_HAS_DISPLAY
    PicoVisionConfig config; // Temporary config for display init
    config.i2c_sda_pin = I2C_SDA_PIN;
    config.i2c_scl_pin = I2C_SCL_PIN;
    // Only initialize display manager for first boot message
    sdk.displayManager.begin(config.i2c_sda_pin, config.i2c_scl_pin);
    sdk.displayManager.showMessage("PicoVision SDK\nInitialized.\nPress button.");
#endif
    Serial.println("Entering deep sleep. Press the button to start.");
    delay(100);
    esp_deep_sleep_start();
  }
}

void loop() {
  // This loop will not be reached. The device will either be in deep sleep
  // or will be rebooting from a wake-up event and handling the interaction
  // within the setup() function.
}
