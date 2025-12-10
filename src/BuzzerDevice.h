#ifndef BUZZER_DEVICE_H
#define BUZZER_DEVICE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "pins.h"

class BuzzerDevice {
public:
  void init();
  bool executeCommand(const String &cmd, const JsonObject &params);
private:
  bool initialized = false;
};

#endif
