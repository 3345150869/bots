#ifndef AUDIO_DEVICE_H
#define AUDIO_DEVICE_H

#include <Audio.h>
#include <ArduinoJson.h>

class AudioDevice {
public:
  void init();
  void executeCommand(const String &cmd, JsonObject &params);
private:
  Audio audio;
  bool initialized = false;
};

#endif
