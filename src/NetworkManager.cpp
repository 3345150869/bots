#include "NetworkManager.h"
#include <Arduino.h>

NetworkManager::NetworkManager() {}

void NetworkManager::begin() {
  // 如果已连接 WiFi，则直接尝试连接 service（此处可扩展读取持久化配置）
  if (WiFi.isConnected()) {
    Serial.println("WiFi 已连接，尝试连接 Service");
    // TODO: 从持久化读取 serviceHost/servicePort
    if (serviceHost.length()) connectToService(serviceHost, servicePort);
  } else {
    startAP();
    startConfigServer();
  }
}

void NetworkManager::loop() {
  server.handleClient();

  // Socket.io 客户端循环（如果已配置）
  if (configured) {
    // 底层库需要定期调用 loop
    socketClient.loop();
  }
}

void NetworkManager::startAP() {
  const char *ssid = "DeskPetAP";
  const char *password = "password";
  Serial.printf("Starting AP: %s\n", ssid);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress ip = WiFi.softAPIP();
  Serial.printf("AP IP: %s\n", ip.toString().c_str());
}

void NetworkManager::startConfigServer() {
  server.on("/", HTTP_GET, [this]() {
    server.send(200, "text/plain", "DeskPet config endpoint");
  });

  // POST /config with form fields: ssid, password, service_host, service_port
  server.on("/config", HTTP_POST, [this]() { handleConfig(); });

  server.begin();
  Serial.println("Config server started at /config (POST)");
}

void NetworkManager::handleConfig() {
  // 读取表单字段
  String ssid = server.arg("ssid");
  String password = server.arg("password");
  String svc = server.arg("service_host");
  String svc_port = server.arg("service_port");

  if (ssid.length() == 0 || password.length() == 0) {
    server.send(400, "text/plain", "missing ssid or password");
    return;
  }

  server.send(200, "text/plain", "received");
  Serial.println("Received WiFi credentials, attempting to connect...");

  // 立即在后台尝试连接主 WiFi
  connectToWiFi(ssid, password);

  if (svc.length()) {
    serviceHost = svc;
    if (svc_port.length()) servicePort = (uint16_t)svc_port.toInt();
  }
}

void NetworkManager::connectToWiFi(const String &ssid, const String &password) {
  // 切换为 STA 模式并连接
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.printf("Connecting to WiFi '%s'...\n", ssid.c_str());

  unsigned long start = millis();
  const unsigned long timeout = 20000;
  while (WiFi.status() != WL_CONNECTED && (millis() - start) < timeout) {
    delay(500);
    Serial.print('.');
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected. IP: ");
    Serial.println(WiFi.localIP());
    // 关闭 AP（如果还在运行）
    WiFi.softAPdisconnect(true);

    // 尝试连接服务
    if (serviceHost.length()) connectToService(serviceHost, servicePort);
  } else {
    Serial.println("WiFi connect failed, restarting AP for retry");
    startAP();
  }
}

void NetworkManager::connectToService(const String &host, uint16_t port) {
  Serial.printf("Connecting to Service %s:%u\n", host.c_str(), port);

  // SocketIoClient 使用底层 client，直接给出主机与端口
  // 注意：具体路径/握手可能需要在服务端配置兼容
  socketClient.begin(host.c_str(), port);

  // 基本事件回调
  socketClient.on("connect", []() {
    Serial.println("Socket.io connected");
  });
  socketClient.on("disconnect", []() {
    Serial.println("Socket.io disconnected");
  });
  socketClient.on("message", [](const char *payload, size_t length) {
    Serial.printf("Socket message: %.*s\n", (int)length, payload);
  });

  // 标记为已配置以在 loop 中定期调用 socketClient.loop()
  configured = true;
}
