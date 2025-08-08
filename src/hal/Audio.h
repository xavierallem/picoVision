#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <Arduino.h>
#include "driver/i2s.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "core/types.h"

// A simple struct to hold audio data and its size
struct AudioBuffer {
    uint8_t* data;
    size_t size;
};

/**
 * @class AudioManager
 * @brief Manages all audio functions: recording and playback.
 */
class AudioManager {
public:
    AudioManager();
    
    /**
     * @brief Initializes the I2S driver for both microphone and speaker.
     * @param config The I2S pin configuration.
     * @return True on success, false on failure.
     */
    bool begin(const I2SConfig& config);
    
    AudioBuffer recordAudio(int duration_ms);
    void playAudio(AudioBuffer& buffer);
    void releaseAudio(AudioBuffer& buffer);

private:
    const i2s_port_t I2S_PORT = I2S_NUM_0;
    const int SAMPLE_RATE = 16000;
    const int BITS_PER_SAMPLE = 16;

    AudioGeneratorMP3* mp3;
    AudioFileSourceBuffer* buff;
    AudioOutputI2S* out;

    void createWavHeader(uint8_t* header, size_t pcmDataSize);
};

#endif // AUDIO_MANAGER_H
