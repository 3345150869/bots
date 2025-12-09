#include "AudioDevice.h"
#include <Arduino.h>

// Default I2S pins (match main.cpp)
const int I2S_WS = 42;
const int I2S_SCK = 41;
const int I2S_DOUT = 40;

void AudioDevice::init() {
  if (initialized) return;
  audio.setPinout(I2S_SCK, I2S_WS, I2S_DOUT);
  audio.setI2SMode(I2S_PHILIPS_MODE);
  audio.setVolume(10);
  initialized = true;
  Serial.println("Audio initialized");
}

void AudioDevice::executeCommand(const String &cmd, JsonObject &params) {
  if (!initialized) {
    Serial.println("Audio not initialized");
    return;
  }
  if (cmd == "setVolume") {
    int v = params.containsKey("vol") ? params["vol"] : 10;
    audio.setVolume(v);
  } else {
    Serial.printf("AudioDevice unknown cmd: %s\n", cmd.c_str());
  }
}
