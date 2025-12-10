#include "BuzzerDevice.h"
#include <Arduino.h>

void BuzzerDevice::init() {
  if (initialized) return;
  pinMode(BUZZER_PIN, OUTPUT);
  initialized = true;
  Serial.println("Buzzer initialized");
}

bool BuzzerDevice::executeCommand(const String &cmd, const JsonObject &params) {
  if (!initialized) {
    Serial.println("Buzzer not initialized");
    return false;
  }
  if (cmd == "beep") {
    int freq = params["freq"].is<int>() ? params["freq"].as<int>() : 1000;
    int dur = params["dur"].is<int>() ? params["dur"].as<int>() : 500;
    tone(BUZZER_PIN, freq, dur);
    return true;
  } else {
    Serial.printf("BuzzerDevice unknown cmd: %s\n", cmd.c_str());
    return false;
  }
}
