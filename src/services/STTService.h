#ifndef STT_SERVICE_H
#define STT_SERVICE_H

#include "services/NetworkManager.h"
#include <Arduino.h>

class STTService {
public:
    STTService(NetworkManager& nm);
    String transcribeAudio(const uint8_t* audioData, size_t dataSize);

private:
    NetworkManager& networkManager;
};

#endif // STT_SERVICE_H
