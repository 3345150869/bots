#pragma once

#include <WiFi.h>
#include <WebServer.h>
#include <SocketIoClient.h>

class NetworkManager {
public:
  NetworkManager();
  void begin();
  void loop();

private:
  void startAP();
  void startConfigServer();
  void handleConfig();
  void connectToWiFi(const String &ssid, const String &password);
  void connectToService(const String &host, uint16_t port);

  WebServer server{80};
  SocketIoClient socketClient;
  bool configured = false;
  String serviceHost = "";
  uint16_t servicePort = 3000;
};
