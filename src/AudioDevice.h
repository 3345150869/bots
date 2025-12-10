#ifndef AUDIO_DEVICE_H
#define AUDIO_DEVICE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "driver/i2s.h"
#include "pins.h"

class AudioDevice {
public:
  void init();
  bool executeCommand(const String &cmd, const JsonObject &params);
private:
  void configureI2S();
  bool initialized = false;
  int volume = 10;
};

#endif
