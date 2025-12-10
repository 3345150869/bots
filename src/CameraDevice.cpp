#include "CameraDevice.h"
#include <Arduino.h>

void CameraDevice::init() {
  if (initialized) return;
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = CAM_Y2_GPIO_NUM;
  config.pin_d1 = CAM_Y3_GPIO_NUM;
  config.pin_d2 = CAM_Y4_GPIO_NUM;
  config.pin_d3 = CAM_Y5_GPIO_NUM;
  config.pin_d4 = CAM_Y6_GPIO_NUM;
  config.pin_d5 = CAM_Y7_GPIO_NUM;
  config.pin_d6 = CAM_Y8_GPIO_NUM;
  config.pin_d7 = CAM_Y9_GPIO_NUM;
  config.pin_xclk = CAM_XCLK_GPIO_NUM;
  config.pin_pclk = CAM_PCLK_GPIO_NUM;
  config.pin_vsync = CAM_VSYNC_GPIO_NUM;
  config.pin_href = CAM_HREF_GPIO_NUM;
  config.pin_sscb_sda = CAM_SIOD_GPIO_NUM;
  config.pin_sscb_scl = CAM_SIOC_GPIO_NUM;
  config.pin_pwdn = CAM_PWDN_GPIO_NUM;
  config.pin_reset = CAM_RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_RGB565;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 12;
  config.fb_count = 2;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed: 0x%x\n", err);
    initialized = false;
    return;
  }
  initialized = true;
  Serial.println("Camera initialized");
}

void CameraDevice::captureAndSend() {
  if (!initialized) {
    Serial.println("Camera not initialized");
    return;
  }
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }
  // TODO: 将图像通过 Socket.io 或 HTTP 上报到 Service
  Serial.printf("Captured frame: %u bytes\n", fb->len);
  esp_camera_fb_return(fb);
}

bool CameraDevice::executeCommand(const String &cmd, const JsonObject &params) {
  if (!initialized) {
    Serial.println("Camera not initialized");
    return false;
  }
  if (cmd == "capture") {
    captureAndSend();
    return true;
  } else {
    Serial.printf("CameraDevice unknown cmd: %s\n", cmd.c_str());
    return false;
  }
}
