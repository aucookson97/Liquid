#include <SPI.h>
#include <WiFi.h>

int networkNum = -1;
char networkPass[] = "36026616";
int wifiStatus = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  while(!Serial) ;

  // attempt to connect using WEP encryption:
  Serial.println("Initializing Wifi...");
  printMacAddress(); 

  // scan for existing networks:
  Serial.println("Scanning available networks...");
  findNetworks();
 // Serial.print("Enter Network Selection #: ");
 wifiStatus = WiFi.begin(WiFi.SSID(0), networkPass);

 if (wifiStatus != WL_CONNECTED) {
  Serial.println("Connection Unsuccessful");
  while (true);
 } else {
  Serial.println("Connection Established");
 }

}

void loop() {

/*
  if (wifiStatus == WL_CONNECTED) {
    Serial.println("Connected");
  } else {
    if (networkNum == -1 && Serial.available() > 0) {
      networkNum = Serial.read();
      Serial.println("Enter Network Password: ");
    } else if (networkNum > -1 && sizeof(networkPass) == 1 && Serial.available() > 0) {
      networkPass = Serial.readString();
    } else if (wifiStatus == WL_IDLE_STATUS && networkNum > -1 && sizeof(networkPass) > 1) {
      Serial.println("Attempting to Connect to WiFi Network...");
      wifiStatus = WiFi.begin(WiFi.SSID(networkNum), networkPass);
  
      if (wifiStatus != WL_CONNECTED) {
        Serial.println("Couldn't establish a WiFi connected")
        while(true);
        delay(500);
      } else {
        Serial.println("Connection Established");
      }
    }
  }
  */
  
  delay(10);
  
 // delay(10000);
  // scan for existing networks:
  //Serial.println("Scanning available networks...");
  //findNetworks();
  
}

void findNetworks() {
  Serial.println("** Scanning Networks **");
  byte numSsid = WiFi.scanNetworks();

  for (int thisNet = 0; thisNet<numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    Serial.println(WiFi.encryptionType(thisNet));
  }
}


void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];                     
  // print your MAC address:
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
}
