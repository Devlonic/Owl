// to open decoder - compile project
// if config is failed - check existion config.json
// if config is large - no issution/working about it check FLASH memory
// if FS files can`t upload - check esp8266fs.jar version. On 0.4.0 working, OR! downgrade esp plate, just close terminal
// if is impossible to update config.json into runtime - check FLASH memory
// if OWL have infinity blink after Wireless Update - update fail - reupdate by wire
//TROUBLES

#include "set.h"

void setup() {
  
  Serial.begin(9600);
  delay(5);
  Serial.println("");
  //Запускаем файловую систему
  Serial.println("Start 4-FS");
  FS_init();
  Serial.println("Step7-FileConfig");
  configSetup = readFile("config.json", 4096);
  jsonWrite(configJson, "SSDP", jsonRead(configSetup, "SSDP"));
  Serial.println(configSetup);
  Serial.println("Start 1-WIFI");
  //Запускаем WIFI
  
  String _wifiMode = jsonRead(configSetup, "wifiMode");
  //if(_wifiMode == "sta") {
    WIFIinit();
  //} else {
   // StartAPMode();  
  //
  Serial.println("Start 8-Time");
  // Получаем время из сети
  Time_init();
  //Настраиваем и запускаем SSDP интерфейс
  Serial.println("Start 3-SSDP");
  SSDP_init();
  //Настраиваем и запускаем HTTP интерфейс
  Serial.println("Start 2-WebServer");
  HTTP_init();
  mp3setup();
  
  allready();
  Serial.println("Ready!");
}

void loop() {
  HTTP.handleClient();
  //dutyNY(GetTime(), GetDate()); // activate when ny 2023
  delay(1); 
  dnsServer.processNextRequest();
}
