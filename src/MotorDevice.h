#ifndef MOTOR_DEVICE_H
#define MOTOR_DEVICE_H

#include <Tb6612fng.h>
#include <ArduinoJson.h>
#include "pins.h"

class MotorDevice {
public:
  MotorDevice();
  void init();
  bool executeCommand(const String &cmd, const JsonObject &params);
private:
  Tb6612fng motors{STBY_PIN, AIN1, AIN2, PWMA, BIN1, BIN2, PWMB};
  bool initialized = false;
};

#endif
