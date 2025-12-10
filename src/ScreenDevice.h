#ifndef SCREEN_DEVICE_H
#define SCREEN_DEVICE_H

#include "pins.h"
#include <TFT_eSPI.h>
#include <ArduinoJson.h>

class ScreenDevice {
public:
  void init();
  bool executeCommand(const String &cmd, const JsonObject &params);
private:
  TFT_eSPI tft;
  bool initialized = false;
};

#endif
