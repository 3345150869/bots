#ifndef SCREEN_DEVICE_H
#define SCREEN_DEVICE_H

#include <TFT_eSPI.h>
#include <ArduinoJson.h>
#include "pins.h"

class ScreenDevice {
public:
  void init();
  void executeCommand(const String &cmd, JsonObject &params);
private:
  TFT_eSPI tft;
  bool initialized = false;
};

#endif
