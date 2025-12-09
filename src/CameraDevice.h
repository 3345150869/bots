#ifndef CAMERA_DEVICE_H
#define CAMERA_DEVICE_H

#include <esp_camera.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "pins.h"

class CameraDevice {
public:
  void init();
  void captureAndSend();  // 示例：捕获图像发到 Service
  void executeCommand(const String &cmd, JsonObject &params);
private:
  bool initialized = false;
};

#endif
