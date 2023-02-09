/*
 * bug fix list
 * if crashed on http.end() - downgrade esp firmware
 * if after first pushing sending is looped - use debouncer
 * if no automatic reset after update: check /reset
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
  WiFi.mode(WIFI_STA);
  wificonnect(ssid,password);
  httpInit();
}
void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    debouncer.update();
    if(debouncer.read() == LOW) sending();
    server.handleClient();
    long int previousMillis = millis();
    while(millis() - previousMillis < 50) { server.handleClient();  delay(1); } /*Keep server*/
  } else { Serial.println("\nLost connection.");wificonnect(ssid,password); }// if connection is lost  
}
