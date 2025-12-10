#include "AudioDevice.h"
#include <Arduino.h>

void AudioDevice::configureI2S() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 64
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  i2s_driver_install((i2s_port_t)0, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)0, &pin_config);
  i2s_set_clk((i2s_port_t)0, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);
}

void AudioDevice::init() {
  if (initialized) return;
  configureI2S();
  initialized = true;
  Serial.println("Audio initialized");
}

bool AudioDevice::executeCommand(const String &cmd, const JsonObject &params) {
  if (!initialized) {
    Serial.println("Audio not initialized");
    return false;
  }
  if (cmd == "setVolume") {
    int v = params["vol"].is<int>() ? params["vol"].as<int>() : 10;
    volume = constrain(v, 0, 100);
    // Note: Volume control would require additional hardware or software processing
    Serial.printf("Volume set to: %d\n", volume);
    return true;
  } else {
    Serial.printf("AudioDevice unknown cmd: %s\n", cmd.c_str());
    return false;
  }
}
