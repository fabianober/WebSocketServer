#include <WebSocketServer.h>

const char *ssid = "YourSSID";
const char *password = "YourPassword";
WebSocketServer webSocketServer(ssid, password, 35, 81);

void toggleLED()
{
    static bool ledState = false;
    ledState = !ledState;
    digitalWrite(35, ledState ? HIGH : LOW);
}

void setup()
{
    webSocketServer.begin();
    webSocketServer.setMessageCallback("LED", toggleLED);
}

void loop()
{
    webSocketServer.loop();
}