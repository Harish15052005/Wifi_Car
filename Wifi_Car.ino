#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h> 

int m1a = D1;
int m1b = D2;
int m2a = D3;
int m2b = D4;



String data;         

ESP8266WebServer server(80);      

unsigned long previousMillis = 0;

String sta_ssid = "Wifi";      
String sta_password = "11223344";  


void HTTP_handleRoot(void){
  server.send ( 200, "text/html", "Wifi Car!!!" );       
  if( server.hasArg("State") ){
     Serial.println(server.arg("State"));
  }
}

void setup(){
  Serial.begin(115200);    
  Serial.println();
 
    
  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);
  
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
  analogWrite(m1a, 0);
  analogWrite(m1b, 0);

  WiFi.mode(WIFI_STA);
  WiFi.begin(sta_ssid.c_str(), sta_password.c_str());
  Serial.println("");
  Serial.print("Connecting to: ");
  Serial.println(sta_ssid);

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;
  while (WiFi.status() != WL_CONNECTED && currentMillis - previousMillis <= 10000) {
    delay(500);
    Serial.print(".");
    currentMillis = millis();
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("*WiFi-STA-Mode*");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    delay(3000);
  } else {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Wifi Car");
    IPAddress myIP = WiFi.softAPIP();
    Serial.println("");
    Serial.println("WiFi failed connected to " + sta_ssid);
    Serial.println("");
    Serial.println("*WiFi-AP-Mode*");
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    delay(3000);
  }

  
 

  server.on ( "/", HTTP_handleRoot );       
  server.onNotFound ( HTTP_handleRoot );    
  server.begin();                           
}

void loop() {
    server.handleClient();       
    
      data = server.arg("State");
      if (data == "F") Forward();          
      else if (data == "B") Backward();
      else if (data == "R") TurnRight();
      else if (data == "L") TurnLeft();
      else if (data == "S") stop();
}


void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}

void Forward(){ 
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
}

void Backward(){
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
}

void TurnLeft(){
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, HIGH);
  digitalWrite(m1a, HIGH);
  digitalWrite(m1b, LOW);
}

void TurnRight(){
  digitalWrite(m2a, HIGH);
  digitalWrite(m2b, LOW);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, HIGH);
}

void stop()
{  
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
}


