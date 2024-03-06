#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* SSID = "nne";
const char* pass = "1122334455";

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

void handleData()
{
  if (server.method() == HTTP_POST)
  {
    direction = server.arg("direction");
    Serial.print("Direction from client :- ");
    Serial.println(direction);

    if (direction == "f") {
      forward();
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
  else
  {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(405, "text/plain", "method Not Allowed");
  }
}

void setup()
{

  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);

  Serial.begin(115200);

  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, pass);
  Serial.println();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("...");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("Ip address:- ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
      Serial.println("MDNS responder started");
  }

  server.on("/data", handleData);
  server.begin();
}

void loop()
{
  server.handleClient();
  MDNS.update();
}
