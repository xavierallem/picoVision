#include "DisplayManager.h"

#ifdef PICOVISION_HAS_DISPLAY

DisplayManager::DisplayManager() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}

bool DisplayManager::begin(int sda, int scl) {
    Wire.begin(sda, scl);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        return false;
    }
    display.display();
    delay(2000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("Display Initialized");
    display.display();
    Serial.println("Display Manager Initialized");
    return true;
}

void DisplayManager::showMessage(const String& message, bool clearDisplay) {
    if (clearDisplay) {
        display.clearDisplay();
    }
    display.setCursor(0,0);
    display.println(message);
    display.display();
}

void DisplayManager::clear() {
    display.clearDisplay();
    display.display();
}

#endif // PICOVISION_HAS_DISPLAY
