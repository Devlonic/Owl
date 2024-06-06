/*
 * bug fix list
 * if crashed on http.end() - downgrade esp firmware
 * if after first pushing sending is looped - use debouncer
 * if no automatic reset after update: check /reset
 * if after firmware upload wdt caused - try to set flash size to 1mb, or just reupload flash
*/

#include "setup.h"
#include "voids.h"

void setup() {
  delay(1);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(5); // interval in ms
  delay(1);
  Serial.begin(115200);
  delay(100);
  Serial.println("\n\rBEGIN DOORBELL STARTUP");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  wificonnect(ssid,password);
  httpInit();
  Serial.println("\n\rEND DOORBELL STARTUP");
}
int even = 20;
void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    debouncer.update();
    if(debouncer.read() == LOW) sending();
    server.handleClient();
    long int previousMillis = millis();
    
    while(millis() - previousMillis < 50) { server.handleClient();  delay(1); } /*Keep server*/
    
    if(even-- == 0) {
      showWiFiStatus();
      even = 20;
    }
    
  } else { Serial.println("\nLost connection.");wificonnect(ssid,password); }// if connection is lost  
}
