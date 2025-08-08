#ifndef WHISPER_PROVIDER_H
#define WHISPER_PROVIDER_H

#include <Arduino.h>
#include "core/types.h"
#include "services/NetworkManager.h"

/**
 * @class WhisperProvider
 * @brief Placeholder for a Whisper (STT) provider.
 * 
 * This class would implement the logic to send audio to a Whisper API
 * and receive transcribed text.
 */
class WhisperProvider {
public:
    // Placeholder for transcription method
    String transcribe(AudioBuffer& audioBuffer) {
        // In a real implementation, this would send audioBuffer.data to the Whisper API
        // and return the transcribed text.
        Serial.println("WhisperProvider: Transcribing audio (placeholder)...");
        // For now, just return a dummy response
        return "This is a transcribed text from Whisper.";
    }
};

#endif // WHISPER_PROVIDER_H
