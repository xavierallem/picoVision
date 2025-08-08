#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "core/Config.h"

#ifdef PICOVISION_HAS_DISPLAY

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

/**
 * @class DisplayManager
 * @brief Manages the OLED display for showing status messages.
 * 
 * This entire class is compiled only if PICOVISION_HAS_DISPLAY is defined.
 */
class DisplayManager {
public:
    DisplayManager();
    
    /**
     * @brief Initializes the I2C display.
     * @param sda The I2C SDA pin.
     * @param scl The I2C SCL pin.
     * @return True on success, false on failure.
     */
    bool begin(int sda, int scl);

    /**
     * @brief Displays a message on the screen.
     * @param message The text to display.
     * @param clearDisplay Whether to clear the display before showing the message.
     */
    void showMessage(const String& message, bool clearDisplay = true);

    /**
     * @brief Clears the display screen.
     */
    void clear();

private:
    Adafruit_SSD1306 display;
    const int SCREEN_WIDTH = 128;
    const int SCREEN_HEIGHT = 64;
};

#endif // PICOVISION_HAS_DISPLAY
#endif // DISPLAY_MANAGER_H
