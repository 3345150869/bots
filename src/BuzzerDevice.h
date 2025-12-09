#ifndef BUZZER_DEVICE_H
#define BUZZER_DEVICE_H

#include <Arduino.h>
#include <ArduinoJson.h>

class BuzzerDevice {
public:
  void init();
  void executeCommand(const String &cmd, JsonObject &params);
private:
  const int BUZZER_PIN = 4;
  bool initialized = false;
};

#endif
