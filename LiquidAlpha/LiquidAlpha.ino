#include <SoftwareSerial.h>
#include <SPI.h>
#include <WiFi.h>

SoftwareSerial Blue(10, 11); //RX, TX


bool btConnected = false;

const byte numChars = 48;
char receivedChars[numChars];
char message[32];
boolean newData = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Blue.begin(9600);

 // printMacAddress();

  
}

void loop() {
  receiveData();
  //sendData();
  showData();

  if (strstr(receivedChars, "POPULATE") != NULL) {
    strcpy(message, "CLEAR");
    sendMessage(message, strlen(message));
    delay(100);
    strcpy(message, "WIFI:Potato Network");
    sendMessage(message, strlen(message));
    delay(100);
    strcpy(message, "WIFI:YoloSwag");
    sendMessage(message, strlen(message));
    delay(100);
    strcpy(message, "WIFI:You Kids Get Off My Lan");
    sendMessage(message, strlen(message));
    strcpy(receivedChars, "");
  }
}

void sendMessage(char message[], int message_length) {
  int i;
  Serial.println();
  Serial.println(message_length);
  for (i = 0; i < message_length; i++) {
    Blue.write(message[i]);  
    Serial.print(message[i]);
  }
  Blue.write('\n');
}

void sendData() {
  static boolean sendInProgress = false;
  char startMarker = '<';
  char endMarker = '>';
  char rc;
  while (Serial.available() > 0) {
    rc = Serial.read();
    if (sendInProgress) {
      if (rc != endMarker) {
        Blue.write(rc);
        Serial.print(rc);
      } else {
       // Blue.write(endMarker);
        Blue.write('\n');
        sendInProgress = false;
        //Serial.print(endMarker);
      }
    } else if (rc == startMarker){
      Serial.print("\nSending: ");
      //Blue.write(startMarker);
      //Serial.print(startMarker);
      sendInProgress = true;
    }
  }
}

void receiveData() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Blue.available() > 0 && newData == false) {
        rc = Blue.read();
        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showData() {
    if (newData == true) {
        Serial.print("New Data: ");
        Serial.println(receivedChars);
        newData = false;
    }
}
/*
  if (Blue.available()) {
    char data = Blue.read();
    Serial.print(data);
    if (data == '*') {
      btConnected = true;
      lastBT = millis();
      Serial.println("Bluetooth Connection Confirmed. Scanning for WiFi Networks.");
      findNetworks();
    }
  }

  if (btConnected) {
    if (Blue.available()) {
      char data = Blue.read();
      Serial.print(data);
    }

    char buf[16] = "";
    sprintf(buf, "Con: %lu", millis());
    Blue.write(buf);

    if (millis() - lastBT > timeout) {
      //btConnected = false;
      //Serial.println("Lost Bluetooth Connection");
    }
  }
  */

void findNetworks() {
  Serial.println("** Scanning Networks **");
  byte numSsid = WiFi.scanNetworks();

  for (int thisNet = 0; thisNet<numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    //Serial.print(WiFi.SSID(thisNet));
    char buf[30];
    String message = "WIFI:";
    message.concat(WiFi.SSID(thisNet));
    message.toCharArray(buf, message.length());
    Serial.print(buf);
    Blue.write(buf); // Send WiFi Network SSIDs to App
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    Serial.println(WiFi.encryptionType(thisNet));
  }
}

void printMacAddress() {
  // the MAC address of WiFi Shield
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
