#ifndef TTS_SERVICE_H
#define TTS_SERVICE_H

#include "services/NetworkManager.h"
#include "hal/Audio.h"

class TTSService {
public:
    TTSService(NetworkManager& nm);
    
    // Synthesizes speech and returns the audio data in a buffer
    AudioBuffer synthesizeSpeech(const String& text);

private:
    NetworkManager& networkManager;
};

#endif // TTS_SERVICE_H
