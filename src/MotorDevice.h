#ifndef MOTOR_DEVICE_H
#define MOTOR_DEVICE_H

#include <TB6612FNG.h>
#include <ArduinoJson.h>
#include "pins.h"

class MotorDevice {
public:
  MotorDevice();
  void init();
  void executeCommand(const String &cmd, JsonObject &params);
private:
  TB6612FNG motors;
  bool initialized = false;
};

#endif
