int m1 = 16; //Left forward GPIO D0
int m2 = 5; // left backward GPIO D1
int m3 = 4; // right forward GPIO D2
int m4 = 0; // right backward GPIO D3

#include <ESP8266WiFi.h> // Library for Wifi in Esp
#include <WiFiClient.h> // library for wifi client
#include <ESP8266WebServer.h> // library for server

String command;      // String to store app command state.

const char* ssid = "Arunodaya"; // Wifi name
const char* pass1 = "car12345"; //Wifi Password

ESP8266WebServer server(80); 

void setup() {
  // put your setup code here, to run once:
 pinMode(m1, OUTPUT);
 pinMode(m2, OUTPUT);
 pinMode(m3, OUTPUT);
 pinMode(m4, OUTPUT);

 Serial.begin(9600); // Serial monitor
  
 digitalWrite(m1, LOW); // motor off
 digitalWrite(m2, LOW);
 digitalWrite(m3, LOW);
 digitalWrite(m4, LOW);

 // Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,pass1);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();  
}

void goAhead()
{
 digitalWrite(m1, HIGH);
 digitalWrite(m2, LOW);
 digitalWrite(m3, HIGH);
 digitalWrite(m4, LOW);
}

void goBack()
 {
  digitalWrite(m1, LOW);
 digitalWrite(m2, HIGH);
 digitalWrite(m3, LOW);
 digitalWrite(m4, HIGH);
}

void goRight()
{
  digitalWrite(m1, HIGH);
 digitalWrite(m2, LOW);
 digitalWrite(m3, LOW);
 digitalWrite(m4, HIGH);
}

void goLeft()
{
digitalWrite(m1, LOW);
 digitalWrite(m2, HIGH);
 digitalWrite(m3, HIGH);
 digitalWrite(m4, LOW);
}

void stopRobot()
{
  digitalWrite(m1, LOW);
 digitalWrite(m2, LOW);
 digitalWrite(m3, LOW);
 digitalWrite(m4, LOW);
}

void loop() {
 server.handleClient();

  command = server.arg("State");

  if (command == "F")
    goAhead();

  else if (command == "B")
    goBack();

  else if (command == "L")
    goLeft();

  else if (command == "R")
    goRight();

  else if (command == "S")
    stopRobot();

}

void HTTP_handleRoot(void)
{
  if (server.hasArg("State"))
  {
    Serial.println(server.arg("State"));
  }
  server.send(200, "text/html", "");
  delay(1);
}
