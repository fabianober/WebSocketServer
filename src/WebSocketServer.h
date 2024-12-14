#ifndef WebSocketServer_h
#define WebSocketServer_h

#include <WiFi.h>
#include <WebSocketsServer.h>
#include <Ticker.h>
#include <Arduino.h>
#include <functional>
#include <chrono>
#include <map>
#include <string>

enum Level
{
    INFO,
    WARNING,
    ERROR
};

class WebSocketServer
{
public:
    WebSocketServer(const char *ssid, const char *password, int ledPin, int wsPort = 81);
    void begin();
    void loop();
    void broadcastMessage(const String &message, Level level = INFO);
    void setMessageCallback(const String &message, std::function<void()> callback);

private:
    const char *ssid;
    const char *password;
    int ledPin;
    int wsPort;
    WebSocketsServer wsServer;
    Ticker pingTicker;
    bool clientConnected;
    std::map<String, std::function<void()>> messageCallbacks;

    static void staticSendPing(WebSocketServer *instance);
    void sendPing();
    void handleWebSocket(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
};

#endif