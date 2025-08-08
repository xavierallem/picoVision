#include "Audio.h"

AudioManager::AudioManager() : mp3(nullptr), buff(nullptr), out(nullptr) {}

bool AudioManager::begin(const I2SConfig& config) {
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_TX),
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false
    };

    i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);

    i2s_pin_config_t pin_config = {
        .bck_io_num = config.mic_sck_pin,
        .ws_io_num = config.mic_ws_pin,
        .data_out_num = config.speaker_dout_pin,
        .data_in_num = config.mic_sd_pin
    };

    i2s_set_pin(I2S_PORT, &pin_config);

    Serial.println("Audio Manager Initialized (I2S Driver with Speaker)");
    return true;
}

AudioBuffer AudioManager::recordAudio(int duration_ms) {
    const int wavHeaderSize = 44;
    const int channels = 1;
    size_t pcmDataSize = (SAMPLE_RATE * BITS_PER_SAMPLE * channels / 8) * (duration_ms / 1000.0);
    size_t wavDataSize = wavHeaderSize + pcmDataSize;
    
    uint8_t* wavBuffer = (uint8_t*)malloc(wavDataSize);
    if (!wavBuffer) {
        Serial.println("Failed to allocate memory for WAV buffer");
        return {nullptr, 0};
    }

    uint8_t* pcmBuffer = wavBuffer + wavHeaderSize;

    Serial.printf("Recording %d seconds of audio...\n", duration_ms / 1000);
    size_t bytesRead = 0;
    i2s_read(I2S_PORT, pcmBuffer, pcmDataSize, &bytesRead, portMAX_DELAY);
    
    Serial.println("Finished recording.");
    createWavHeader(wavBuffer, bytesRead);

    return {wavBuffer, wavHeaderSize + bytesRead};
}

void AudioManager::playAudio(AudioBuffer& buffer) {
    if (!buffer.data || buffer.size == 0) {
        Serial.println("Error: playAudio called with empty buffer.");
        return;
    }

    out = new AudioOutputI2S();
    // The I2S port can be shared between input and output, so we must stop input first.
    i2s_driver_uninstall(I2S_PORT);
    out->SetPinout(I2S_MIC_SCK_PIN, I2S_MIC_WS_PIN, I2S_SPEAKER_DOUT_PIN);

    buff = new AudioFileSourceBuffer(buffer.data, buffer.size);
    mp3 = new AudioGeneratorMP3();

    Serial.println("Starting audio playback...");
    mp3->begin(buff, out);
    while (mp3->isRunning()) {
        if (!mp3->loop()) {
            mp3->stop();
            Serial.println("Playback finished.");
        }
    }

    // Clean up
    delete mp3;
    delete buff;
    delete out;
    mp3 = nullptr;
    buff = nullptr;
    out = nullptr;

    releaseAudio(buffer);
    
    // Re-initialize I2S for recording
    begin({I2S_MIC_SCK_PIN, I2S_MIC_WS_PIN, I2S_MIC_SD_PIN, I2S_SPEAKER_DOUT_PIN});
}

void AudioManager::releaseAudio(AudioBuffer& buffer) {
    if (buffer.data) {
        free(buffer.data);
        buffer.data = nullptr;
        buffer.size = 0;
    }
}

void AudioManager::createWavHeader(uint8_t* header, size_t pcmDataSize) {
    const int channels = 1;
    header[0] = 'R'; header[1] = 'I'; header[2] = 'F'; header[3] = 'F';
    uint32_t fileSize = pcmDataSize + 36;
    header[4] = (byte)(fileSize & 0xFF);
    header[5] = (byte)((fileSize >> 8) & 0xFF);
    header[6] = (byte)((fileSize >> 16) & 0xFF);
    header[7] = (byte)((fileSize >> 24) & 0xFF);
    header[8] = 'W'; header[9] = 'A'; header[10] = 'V'; header[11] = 'E';
    header[12] = 'f'; header[13] = 'm'; header[14] = 't'; header[15] = ' ';
    header[16] = 16; header[17] = 0; header[18] = 0; header[19] = 0;
    header[20] = 1; header[21] = 0;
    header[22] = channels; header[23] = 0;
    uint32_t sampleRate = SAMPLE_RATE;
    header[24] = (byte)(sampleRate & 0xFF);
    header[25] = (byte)((sampleRate >> 8) & 0xFF);
    header[26] = (byte)((sampleRate >> 16) & 0xFF);
    header[27] = (byte)((sampleRate >> 24) & 0xFF);
    uint32_t byteRate = SAMPLE_RATE * channels * BITS_PER_SAMPLE / 8;
    header[28] = (byte)(byteRate & 0xFF);
    header[29] = (byte)((byteRate >> 8) & 0xFF);
    header[30] = (byte)((byteRate >> 16) & 0xFF);
    header[31] = (byte)((byteRate >> 24) & 0xFF);
    header[32] = channels * BITS_PER_SAMPLE / 8; header[33] = 0;
    header[34] = BITS_PER_SAMPLE; header[35] = 0;
    header[36] = 'd'; header[37] = 'a'; header[38] = 't'; header[39] = 'a';
    header[40] = (byte)(pcmDataSize & 0xFF);
    header[41] = (byte)((pcmDataSize >> 8) & 0xFF);
    header[42] = (byte)((pcmDataSize >> 16) & 0xFF);
    header[43] = (byte)((pcmDataSize >> 24) & 0xFF);
}