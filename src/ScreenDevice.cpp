#include "ScreenDevice.h"
#include <Arduino.h>

void ScreenDevice::init() {
  if (initialized) return;
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("AI Desk Pet Ready", 10, 10, 2);
  initialized = true;
  Serial.println("Screen initialized");
}

bool ScreenDevice::executeCommand(const String &cmd, const JsonObject &params) {
  if (!initialized) {
    Serial.println("Screen not initialized");
    return false;
  }
  if (cmd == "drawText") {
    const char *text = params["text"].is<const char*>() ? params["text"].as<const char*>() : "";
    int x = params["x"].is<int>() ? params["x"].as<int>() : 0;
    int y = params["y"].is<int>() ? params["y"].as<int>() : 0;
    int font = params["font"].is<int>() ? params["font"].as<int>() : 2;
    tft.drawString(text, x, y, font);
    return true;
  } else {
    Serial.printf("ScreenDevice unknown cmd: %s\n", cmd.c_str());
    return false;
  }
}
