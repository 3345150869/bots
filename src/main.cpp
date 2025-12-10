#include <Arduino.h>
#include <WiFi.h>  // 联网（可选连 Node 服务器）
#include <esp_camera.h>  // OV2640 摄像头
#include <Tb6612fng.h>   // TB6612FNG 电机驱动
#include <ArduinoJson.h>
#include "pins.h"        // 集中管理的引脚定义
#include <TFT_eSPI.h>    // ST7789 屏幕
#include "NetworkManager.h"  // 网络与配网管理
#include "CameraDevice.h"
#include "ScreenDevice.h"
#include "AudioDevice.h"
#include "MotorDevice.h"
#include "BuzzerDevice.h"

NetworkManager net;

// 硬件模块封装实例
CameraDevice camera;
ScreenDevice screen;
AudioDevice audioDev;
MotorDevice motor;
BuzzerDevice buzzer;

void setup() {
  Serial.begin(115200);
  // 硬件初始化保留在 Device 层，各模块可以进一步封装为类
  // 初始化各硬件模块（封装）
  screen.init();
  buzzer.init();
  motor.init();
  audioDev.init();
  camera.init();

  // 启动网络管理（若无 WiFi 则进入 AP 配网）
  net.begin();
}

void loop() {
  // 示例: 蜂鸣器响
  JsonDocument beepDoc;
  buzzer.executeCommand("beep", beepDoc.to<JsonObject>());  // 示例调用
  delay(1000);

  // 示例: 电机转
  JsonDocument doc;
  JsonObject params = doc.to<JsonObject>();
  params["a"] = 255;
  params["b"] = 255;
  motor.executeCommand("drive", params);
  delay(1000);
  JsonDocument brakeDoc;
  motor.executeCommand("brake", brakeDoc.to<JsonObject>());
  delay(1000);

  // 网络任务（处理 AP 配网和 Socket.io）
  net.loop();

  // TODO: 将摄像头、音频与显示等模块抽象为类并在此调用
  delay(10);  // 循环延时
}