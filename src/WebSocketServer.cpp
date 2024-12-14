#include "WebSocketServer.h"

// Constructor: Initializes the WebSocketServer with WiFi credentials, LED pin, and WebSocket port
WebSocketServer::WebSocketServer(const char *ssid, const char *password, int ledPin, int wsPort)
    : ssid(ssid), password(password), ledPin(ledPin), wsPort(wsPort), wsServer(wsPort), clientConnected(false)
{
}

// Begin: Starts the WebSocket server and connects to WiFi
void WebSocketServer::begin()
{
    Serial.begin(115200);
    Serial.println("Starting WebSocketServer");

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    Serial.println("Connecting to WiFi");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.println("Connected to WiFi");

    wsServer.begin();

    Serial.println("WebSocketServer started on port " + String(wsPort));

    wsServer.onEvent([this](uint8_t num, WStype_t type, uint8_t *payload, size_t length)
                     { this->handleWebSocket(num, type, payload, length); });

    pingTicker.attach(5, staticSendPing, this);

    Serial.println("WebSocketServer ready");
}

// Loop: Handles WebSocket server events
void WebSocketServer::loop()
{
    wsServer.loop();
}

// BroadcastMessage: Sends a message to all connected clients with a specified log level
void WebSocketServer::broadcastMessage(const String &message, Level level)
{
    String levelStr;
    switch (level)
    {
    case INFO:
        levelStr = "INFO";
        break;
    case WARNING:
        levelStr = "WARNING";
        break;
    case ERROR:
        levelStr = "ERROR";
        break;
    }
    String mutableMessage = levelStr + "::" + message;
    wsServer.broadcastTXT(mutableMessage);
}

// SetMessageCallback: Registers a callback function for a specific message
void WebSocketServer::setMessageCallback(const String &message, std::function<void()> callback)
{
    messageCallbacks[message] = callback;
}

// StaticSendPing: Static method to call the instance's sendPing method
void WebSocketServer::staticSendPing(WebSocketServer *instance)
{
    instance->sendPing(); // Call the instance's sendPing method
}

// SendPing: Sends a ping message with the current timestamp to all connected clients
void WebSocketServer::sendPing()
{
    // Get the current timestamp
    const auto p1 = std::chrono::system_clock::now();
    wsServer.broadcastTXT("PING::" + String(std::chrono::duration_cast<std::chrono::seconds>(
                                                p1.time_since_epoch())
                                                .count()));
}

// HandleWebSocket: Handles WebSocket events such as connection, disconnection, and incoming messages
void WebSocketServer::handleWebSocket(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
    if (type == WStype_CONNECTED)
    {
        clientConnected = true;
    }
    else if (type == WStype_DISCONNECTED)
    {
        clientConnected = false;
    }
    else if (type == WStype_TEXT)
    {
        String message = String((char *)payload).substring(0, length);
        if (messageCallbacks.find(message) != messageCallbacks.end())
        {
            messageCallbacks[message]();
        }
    }
}