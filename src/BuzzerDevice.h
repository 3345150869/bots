#ifndef BUZZER_DEVICE_H
#define BUZZER_DEVICE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "pins.h"

class BuzzerDevice {
public:
  void init();
  void executeCommand(const String &cmd, JsonObject &params);
private:
  bool initialized = false;
};

#endif
