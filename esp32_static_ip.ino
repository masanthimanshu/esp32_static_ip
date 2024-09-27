#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "GWN14";
const char *password = "tbm0htr2";
const char *deviceId = "device1234";

WebServer server(80);

void setup()
{
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.config(IPAddress(192, 168, 8, 76), IPAddress(192, 168, 8, 1), IPAddress(255, 255, 255, 0));
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }

  Serial.print("Connected! IP: ");
  Serial.println(WiFi.localIP());

  server.on("/deviceId", []()
            { server.send(200, "text/plain", deviceId); });

  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}
