#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";

ESP8266WebServer server(80); // Create a web server on port 80

int ledPin = 13;  // Pin connected to LED

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  
  // Define routes for turning LED on and off
  server.on("/turnon", []() {
    digitalWrite(ledPin, HIGH);
    server.send(200, "text/plain", "LED is ON");
  });

  server.on("/turnoff", []() {
    digitalWrite(ledPin, LOW);
    server.send(200, "text/plain", "LED is OFF");
  });
  
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
