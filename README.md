# Thingspeak 
To upload data to remote monitoring 

(https://github.com/niwantha33/Thignspeak) 

# Initial Setup ( Hardware requirement)

1.  ESp Wroom-2 module 
2.  DHT 11 senosor 
3.  Some resistors 
4.  3.3V power supply (DC) 
5.  LDR Senosr
6.  Ultrasonic Senosr ( to check water level)
7.  LEDs 
8.  jumpers
9.  DOT PCB (Very small)
10. Pin headers
11. Soldering iron 
12. Some flux 
13. USB to TLL ( For initial software updates )

# Making PCB for ESp Wroom-2 
before connecting other sensors need to make a pcb for mounting of ESP Wroom-2 module 
dot board was used for connecting pin headers and the ESP Wroom-2 pins

after connecting ESP Wroom-2 pins and the header , then need to use USB to TLL connector 
for connecting of ESp Wroom-2 and the Laptop.

ESP Wroom-2           USB to TLL

RX --------Logic Converter-----------> Tx
Tx --------Logic Converter-----------> Rx
EN,VCC -----------------> 3.3V ( ESP Wroom-2 maximum voltage is 3.6V) 

do not connect 5V to ESp Wroom-2 , this will damage the entire board. 

# make a account in Thingspeak 

You need to make a acount in Thingspeak , then note down the API write Key 
then, using get method you can upload the fields as shown in below;

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
  
  
#Get Method;
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" +
  "Connection: close\r\n\r\n");
  
# Response from Server 

while (client.available()) {
   String line = client.readStringUntil('\r');
  Serial.print(line); // Server result ( response from server)
  }
  
  








