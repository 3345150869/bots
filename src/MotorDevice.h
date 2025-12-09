#ifndef MOTOR_DEVICE_H
#define MOTOR_DEVICE_H

#include <TB6612FNG.h>
#include <ArduinoJson.h>

class MotorDevice {
public:
  MotorDevice();
  void init();
  void executeCommand(const String &cmd, JsonObject &params);
private:
  // Default pins (as in main.cpp)
  const int STBY_PIN = 3;
  const int AIN1 = 16;
  const int AIN2 = 17;
  const int PWMA = 18;
  const int BIN1 = 19;
  const int BIN2 = 21;
  const int PWMB = 22;
  TB6612FNG motors;
  bool initialized = false;
};

#endif
