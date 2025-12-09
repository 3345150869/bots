#include "BuzzerDevice.h"
#include <Arduino.h>

void BuzzerDevice::init() {
  if (initialized) return;
  pinMode(BUZZER_PIN, OUTPUT);
  initialized = true;
  Serial.println("Buzzer initialized");
}

void BuzzerDevice::executeCommand(const String &cmd, JsonObject &params) {
  if (!initialized) {
    Serial.println("Buzzer not initialized");
    return;
  }
  if (cmd == "beep") {
    int freq = params.containsKey("freq") ? params["freq"] : 1000;
    int dur = params.containsKey("dur") ? params["dur"] : 500;
    tone(BUZZER_PIN, freq, dur);
  } else {
    Serial.printf("BuzzerDevice unknown cmd: %s\n", cmd.c_str());
  }
}
