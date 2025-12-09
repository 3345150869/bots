#ifndef CAMERA_DEVICE_H
#define CAMERA_DEVICE_H

#include <esp_camera.h>
#include <ArduinoJson.h>
#include <Arduino.h>

class CameraDevice {
public:
  void init();
  void captureAndSend();  // 示例：捕获图像发到 Service
  void executeCommand(const String &cmd, JsonObject &params);
private:
  // 使用默认引脚定义（与 main.cpp 保持一致）
  const int CAM_PWDN_GPIO_NUM = -1;
  const int CAM_RESET_GPIO_NUM = -1;
  const int CAM_XCLK_GPIO_NUM = 15;
  const int CAM_SIOD_GPIO_NUM = 4;
  const int CAM_SIOC_GPIO_NUM = 5;
  const int CAM_Y9_GPIO_NUM = 16;
  const int CAM_Y8_GPIO_NUM = 17;
  const int CAM_Y7_GPIO_NUM = 18;
  const int CAM_Y6_GPIO_NUM = 12;
  const int CAM_Y5_GPIO_NUM = 10;
  const int CAM_Y4_GPIO_NUM = 8;
  const int CAM_Y3_GPIO_NUM = 9;
  const int CAM_Y2_GPIO_NUM = 11;
  const int CAM_VSYNC_GPIO_NUM = 6;
  const int CAM_HREF_GPIO_NUM = 7;
  const int CAM_PCLK_GPIO_NUM = 13;
  bool initialized = false;
};

#endif
