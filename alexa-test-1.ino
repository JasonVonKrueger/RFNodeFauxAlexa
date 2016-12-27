#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <RCSwitch.h>
#include "fauxmoESP.h"

#define WIFI_SSID ""
#define WIFI_PASS ""
#define SERIAL_BAUDRATE                 115200

fauxmoESP fauxmo;
RCSwitch mySwitch;

// -----------------------------------------------------------------------------
// Wifi
// -----------------------------------------------------------------------------

void wifiSetup() {

    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void callback(const char * device_name, bool state) {
  Serial.print("Device "); Serial.print(device_name); 
  Serial.print(" state: ");

  if ( (strcmp(device_name, "lamp 1") == 0) ) {
    // this just sets a variable that the main loop() does something about
    if (state) {
      mySwitch.send(5510451, 24);
    } else {
      mySwitch.send(5510460, 24);
    }
  }

  if ( (strcmp(device_name, "lamp 2") == 0) ) {
    // this just sets a variable that the main loop() does something about
    if (state) {
      mySwitch.send(5518595, 24);
    } else {
      mySwitch.send(5518604, 24);
    }
  }

  if ( (strcmp(device_name, "both lamps") == 0) ) {
    // this just sets a variable that the main loop() does something about
    if (state) {
      mySwitch.send(5518595, 24);
      mySwitch.send(5510451, 24);
    } else {
      mySwitch.send(5518604, 24);
      mySwitch.send(5510460, 24);
    }
  }
  
  //if (state) {
  //  Serial.println("ON");
  //   mySwitch.send(5510451, 24);
  //} else {
  //  Serial.println("OFF");
  //   mySwitch.send(5510460, 24);
  // }
}

void setup() {
    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println("FauxMo demo sketch");
    Serial.println("After connection, ask Alexa/Echo to 'turn <devicename> on' or 'off'");

    // Wifi
    wifiSetup();
    
    // iniit rf switch
    mySwitch = RCSwitch();
    mySwitch.enableTransmit(13);
    mySwitch.setPulseLength(185);
    mySwitch.setRepeatTransmit(9);
   // mySwitch.send(5510451, 24);
    delay(15);
   // mySwitch.send(5510460, 24);
        
    // Fauxmo
    fauxmo.addDevice("relay");
    fauxmo.addDevice("lamp 1");
    fauxmo.addDevice("lamp 2");
    fauxmo.addDevice("both lamps");
    fauxmo.onMessage(callback);
}

void loop() {
}
