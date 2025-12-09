#include <Arduino.h>
#include <WiFi.h>  // 联网（可选连 Node 服务器）
#include <esp_camera.h>  // OV2640 摄像头
#include <TFT_eSPI.h>    // ST7789 屏幕
#include <TB6612FNG.h>   // TB6612FNG 电机驱动
#include <Audio.h>       // 从 ESP8266Audio 库，用于 I2S 音频
#include "NetworkManager.h"  // 网络与配网管理

// 引脚定义（面包板自定义，根据你的连接调整）
#define BUZZER_PIN 4    // BB 蜂鸣器

// 摄像头 OV2640 (ESP32-S3 DVP 接口)
#define CAM_PWDN_GPIO_NUM    -1  // 无需
#define CAM_RESET_GPIO_NUM   -1  // 无需
#define CAM_XCLK_GPIO_NUM    15
#define CAM_SIOD_GPIO_NUM    4
#define CAM_SIOC_GPIO_NUM    5
#define CAM_Y9_GPIO_NUM      16
#define CAM_Y8_GPIO_NUM      17
#define CAM_Y7_GPIO_NUM      18
#define CAM_Y6_GPIO_NUM      12
#define CAM_Y5_GPIO_NUM      10
#define CAM_Y4_GPIO_NUM      8
#define CAM_Y3_GPIO_NUM      9
#define CAM_Y2_GPIO_NUM      11
#define CAM_VSYNC_GPIO_NUM   6
#define CAM_HREF_GPIO_NUM    7
#define CAM_PCLK_GPIO_NUM    13

// 屏幕 1.54寸 ST7789 (SPI 接口)
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  -1  // 或接复位引脚

// 音频 I2S (INMP441 麦克风 + MAX98357 放大器)
#define I2S_WS   42  // Word Select (LRCLK)
#define I2S_SCK  41  // Bit Clock (BCLK)
#define I2S_SD   1   // INMP441 数据输出
#define I2S_DOUT 40  // MAX98357 数据输入

// 电机 TB6612FNG (示例 2 个电机，扩展到 4 个麦克纳姆轮)
#define STBY_PIN 3   // STBY 启用
#define AIN1     16
#define AIN2     17
#define PWMA     18  // PWM A
#define BIN1     19
#define BIN2     21
#define PWMB     22  // PWM B

TFT_eSPI tft = TFT_eSPI();  // 屏幕实例
TB6612FNG motors(STBY_PIN);  // 电机驱动实例
Audio audio;  // 音频实例

NetworkManager net;

void setup() {
  Serial.begin(115200);
  // 硬件初始化保留在 Device 层，各模块可以进一步封装为类
  // 初始化屏幕
  tft.init();
  tft.setRotation(0);  // 根据方向调整
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("AI Desk Pet Ready", 10, 10, 2);

  // 初始化蜂鸣器
  pinMode(BUZZER_PIN, OUTPUT);

  // 初始化电机 (TB6612FNG)
  motors.begin();
  motors.setMotorPins(AIN1, AIN2, PWMA, BIN1, BIN2, PWMB);

  // 初始化音频 I2S
  audio.setPinout(I2S_SCK, I2S_WS, I2S_DOUT);  // 输出到 MAX98357
  audio.setI2SMode(I2S_PHILIPS_MODE);  // 标准模式
  audio.setVolume(10);  // 音量

  // 启动网络管理（若无 WiFi 则进入 AP 配网）
  net.begin();
}

void loop() {
  // 示例: 蜂鸣器响
  tone(BUZZER_PIN, 1000, 500);  // 1kHz, 0.5s
  delay(1000);

  // 示例: 电机转 (麦克纳姆轮需 kinematics，这里简单前后)
  motors.driveMotorA(255);  // 全速前进
  motors.driveMotorB(255);
  delay(1000);
  motors.brake();  // 刹车
  delay(1000);

  // 网络任务（处理 AP 配网和 Socket.io）
  net.loop();

  // TODO: 将摄像头、音频与显示等模块抽象为类并在此调用
  delay(10);  // 循环延时
}