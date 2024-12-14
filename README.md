# WebSocketServer

WebSocketServer is a WebSocket server library for Arduino, specifically designed for the ESP32 platform. This library allows you to create a WebSocket server on your ESP32 device, enabling real-time communication between the ESP32 and web clients.

## Features

- Easy-to-use API for setting up a WebSocket server
- Support for handling multiple WebSocket connections
- Ability to broadcast messages to all connected clients
- Customizable message handling with callback functions
- Built-in ping mechanism to monitor connection status

## Requirements

- ESP32 development board
- Arduino IDE with ESP32 board support installed
- WiFi network for the ESP32 to connect to

## Installation

1. Download the library from the [GitHub repository](https://github.com/fabianober/WebSocketServer).
2. Extract the downloaded ZIP file.
3. Copy the `WebSocketServer` folder to your Arduino libraries directory (usually located at `~/Documents/Arduino/libraries`).

## Usage

### Basic Example

The example is provided in the `examples` folder of the library. Run it on your ESP32 device to start a WebSocket server and then use the web.html in the same folder to connect to the server.
