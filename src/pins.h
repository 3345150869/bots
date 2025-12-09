#ifndef PINS_H
#define PINS_H

// ============ 蜂鸣器 ============
#define BUZZER_PIN 4

// ============ 摄像头 OV2640 (ESP32-S3 DVP 接口) ============
#define CAM_PWDN_GPIO_NUM    -1
#define CAM_RESET_GPIO_NUM   -1
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

// ============ 屏幕 1.54寸 ST7789 (SPI 接口) ============
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  -1

// ============ 音频 I2S (INMP441 + MAX98357) ============
#define I2S_WS   42
#define I2S_SCK  41
#define I2S_SD   1
#define I2S_DOUT 40

// ============ 电机 TB6612FNG ============
#define STBY_PIN 3
#define AIN1     16
#define AIN2     17
#define PWMA     18
#define BIN1     19
#define BIN2     21
#define PWMB     22

#endif
