#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress apIP(192, 168, 1, 1);
const char* apSSID = "ESP8266-Access-Point";

const int m1a = D5;
const int m1b = D6;

const int m2a = D7;
const int m2b = D8;

ESP8266WebServer server(80);

String direction;

void forward()
{
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);

}

void reverse()
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);

}

void right()
{
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
}

void ghomarLeft()
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}

void ghomarRight()
{
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
}
void left()
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
}

void stop()
{
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
}

void handleRoot()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", "");
}

void setup()
{


  Serial.begin(115200);

  // Set up ESP8266 in soft-AP mode
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(apSSID);

  Serial.println("Soft-AP IP address = " + WiFi.softAPIP().toString());


  server.on("/", handleRoot);
  server.begin();

  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);
}

void loop()
{
  server.handleClient();
  direction = server.arg("direction");
  Serial.println(direction);
  if (direction == "f") {
      forward();
      Serial.println("f");
    } else if (direction == "b") {
      reverse();
    } else if (direction == "l") {
      left();
    } else if (direction == "r") {
      right();
    } else if (direction == "s") {
      stop();
    } else if (direction == "z") {
      ghomarLeft();
    } else if (direction == "x") {
      ghomarRight();
    }
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(200);
}
