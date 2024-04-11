#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char *ssid = "";
const char *password = "";
const int ledPin = 2; // Led pin

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<button onclick=\"sendSignal()\">Enviar Sinal</button><script>function sendSignal() {fetch('/signal');}</script>");
}

void handleSignal() {
  digitalWrite(ledPin, HIGH); // Acende o LED
  delay(1000); // Espera 1 segundo
  digitalWrite(ledPin, LOW); // Desliga o LED
  server.send(200, "text/plain", "Sinal recebido!");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to WiFi");

  server.on("/", handleRoot);
  server.on("/signal", handleSignal);

  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
