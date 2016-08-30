#include <ESP8266WiFi.h>
float T;// Temperature 
float H;// Humidity
float L;// LDR value
float U;// Ultra sonic data
int Count  =  0;// number of counts 

const char* ssid     = "TP"; // Wifi name (hotspot)
const char* password = "12345678"; // Password

const char* host = "api.thingspeak.com"; //

const char* privateKey = "J8G801QXNJU86DW7"; // Write API Key from thingspeak

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  Count ++;
  if (Count>32000) {// this is because of Count is "Int"
    Count =0;
  }
  Thingspeak(T,H,L,U,Count);

}


void Thingspeak(float TEM, float HUM, float LDR, float ULT,int count) { // number of field which required to send to server
  WiFiClient client; // Creating Wifi client

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections

  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }


  // We now create a URI for the request
  String url = "/update";
  // url += streamId;
  url += "?key=";
  url += privateKey;
  url += "&field1="; // Things peak field1
  url += TEM; // value that need  put to field1
  url += "&field2=";// Things peak field1
  url += HUM; // value that need  put to field1
  url += "&field3=";
  url += LDR;
  url += "&field4=";
  url += ULT;
  url += "&status=";
  url += count; // Number of count that transmitted to the thingspeak Server

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');

    Serial.print(line); // Server result ( response from server)
  }

  Serial.println();
  Serial.println("closing connection");
}
