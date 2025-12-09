#include "MotorDevice.h"
#include <Arduino.h>

MotorDevice::MotorDevice(): motors(STBY_PIN) {}

void MotorDevice::init() {
  if (initialized) return;
  motors.begin();
  motors.setMotorPins(AIN1, AIN2, PWMA, BIN1, BIN2, PWMB);
  initialized = true;
  Serial.println("Motor initialized");
}

void MotorDevice::executeCommand(const String &cmd, JsonObject &params) {
  if (!initialized) {
    Serial.println("Motor not initialized");
    return;
  }
  if (cmd == "drive") {
    int a = params.containsKey("a") ? params["a"] : 0;
    int b = params.containsKey("b") ? params["b"] : 0;
    motors.driveMotorA(a);
    motors.driveMotorB(b);
  } else if (cmd == "brake") {
    motors.brake();
  } else {
    Serial.printf("MotorDevice unknown cmd: %s\n", cmd.c_str());
  }
}
