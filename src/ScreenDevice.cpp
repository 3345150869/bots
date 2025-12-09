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

void ScreenDevice::executeCommand(const String &cmd, JsonObject &params) {
  if (!initialized) {
    Serial.println("Screen not initialized");
    return;
  }
  if (cmd == "drawText") {
    const char *text = params.containsKey("text") ? params["text"] : "";
    int x = params.containsKey("x") ? params["x"] : 0;
    int y = params.containsKey("y") ? params["y"] : 0;
    int font = params.containsKey("font") ? params["font"] : 2;
    tft.drawString(text, x, y, font);
  } else {
    Serial.printf("ScreenDevice unknown cmd: %s\n", cmd.c_str());
  }
}
