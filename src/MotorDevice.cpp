#include "MotorDevice.h"
#include <Arduino.h>

MotorDevice::MotorDevice() {}

void MotorDevice::init() {
  if (initialized) return;
  motors.begin();
  initialized = true;
  Serial.println("Motor initialized");
}

bool MotorDevice::executeCommand(const String &cmd, const JsonObject &params) {
  if (!initialized) {
    Serial.println("Motor not initialized");
    return false;
  }
  if (cmd == "drive") {
    float a = params["a"].is<float>() ? params["a"].as<float>() : 0.0;
    float b = params["b"].is<float>() ? params["b"].as<float>() : 0.0;
    // Convert from -100..100 range to -1.0..1.0 range expected by TB6612FNG library
    float velocityA = a / 100.0;
    float velocityB = b / 100.0;
    motors.drive(velocityA, velocityB);
    return true;
  } else if (cmd == "brake") {
    motors.brake();
    return true;
  } else {
    Serial.printf("MotorDevice unknown cmd: %s\n", cmd.c_str());
    return false;
  }
}
