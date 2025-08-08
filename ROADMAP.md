# PicoVision SDK Development Roadmap

This document outlines the planned features and improvements for the PicoVision SDK.

## Phase 1: Core SDK Foundation (✅ Completed)
- [x] **Project Scaffolding:** Set up a PlatformIO project structure.
- [x] **Project Plan:** Create a comprehensive `README.md` with a roadmap.
- [x] **Core SDK Class:** Implement the main `PicoVisionSDK.h` entry point.
- [x] **Configuration Management:** Create a secure structure for managing Wi-Fi and API credentials (`Config.h`).
- [x] **Networking Service:** Implement a robust `NetworkManager` with a focus on secure HTTPS (TLS) connections.

## Phase 2: Hardware Abstraction Layer (HAL) (✅ Completed)
- [x] **Camera Manager:** Implement a non-blocking camera service for capturing high-quality images.
- [x] **Audio Manager:** Implement I2S drivers for microphone and a placeholder for speaker output.

## Phase 3: AI Service Integrations (✅ Completed)
- [x] **Vision Service:** Create a service to send image data to a vision model API (Ollama, OpenRouter).
- [x] **Speech-to-Text (STT) Service:** Create a service to send audio data to the Whisper API.
- [x] **Text-to-Speech (TTS) Service:** Create a service to fetch audio data from the OpenAI TTS API.

## Phase 4: SDK Refactoring & Robustness (✅ Completed)
- [x] **Provider Abstraction:** Refactor services to use a provider model for easy extension. (STT and TTS services refactored to use provider pattern)
- [x] **Configuration Struct:** Replace `#define` macros with a `PicoVisionConfig` struct for runtime configuration.
- [x] **Improved Error Handling:** Return meaningful error codes/objects instead of printing to Serial.
- [x] **Code Comments:** Add Doxygen-style comments to all public headers.
- [x] **Code Formatting:** Add a `.clang-format` file for consistent style.
- [x] **Documentation Overhaul:** Create a user-focused `README.md` and a `ROADMAP.md`.

## Phase 5: Future Features
- [x] **Speaker Driver:** Implement a full I2S speaker driver with MP3 decoding for audio playback. (Partial: I2S driver and MP3 decoding implemented, but full integration might need more work)
- [ ] **Display Support:** Add a HAL for small OLED or LCD displays to show status and responses. (✅ Completed)
- [ ] **Bluetooth Low Energy (BLE):** Implement BLE for communication with a companion mobile app (e.g., for configuration).
- [x] **Power Management:** Add deep sleep and power-saving features to maximize battery life.
- [x] **Example Applications:** Create more detailed and varied example applications. (`main.cpp` serves as a functional example)
- [ ] **Unit & Integration Tests:** Build a testing framework for validating SDK components.
