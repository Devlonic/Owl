void HTTP_init(void) {
  HTTP.on("/wifiMode", HTTP_GET, []() {
    jsonWrite(configSetup, "wifiMode", HTTP.arg("wifiMode"));
    saveConfig();                 // Функция сохранения данных во Flash
    HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  });
  HTTP.on("/ssid", HTTP_GET, []() {
    jsonWrite(configSetup, "ssid", HTTP.arg("ssid"));
    jsonWrite(configSetup, "password", HTTP.arg("password"));
    saveConfig();                 // Функция сохранения данных во Flash
    HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  });
   // --------------------Получаем SSDP со страницы
  HTTP.on("/ssidap", HTTP_GET, []() {
    jsonWrite(configSetup, "ssidAP", HTTP.arg("ssidAP"));
    jsonWrite(configSetup, "passwordAP", HTTP.arg("passwordAP"));
    saveConfig();                 // Функция сохранения данных во Flash
    HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  });
  // --------------------Выдаем данные configJson
  HTTP.on("/config.live.json", HTTP_GET, []() {
    outData();
    HTTP.send(200, "application/json", configJson);
  });
  // -------------------Выдаем данные configSetup
  HTTP.on("/config.setup.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", configSetup);
  });
  // -------------------Выдаем данные configSetup
  HTTP.on("/restart", HTTP_GET, []() {
    String restart = HTTP.arg("device");          // Получаем значение device из запроса
    if (restart == "ok") {                         // Если значение равно Ок
      HTTP.send(200, "text / plain", "Reset OK"); // Oтправляем ответ Reset OK
      ESP.restart();                                // перезагружаем модуль
    }
    else {                                        // иначе
      HTTP.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
    }
  });
  HTTP.on("/test", HTTP_GET, []() {
    String curtime = HTTP.arg("curtime");          // Получаем значение device из запроса
    String curdate = HTTP.arg("curdate");          // Получаем значение device из запроса
    dutyNY(curtime, curdate);
    
    HTTP.send(200, "text / plain", "Tested");       
  });
  HTTP.on("/voice", HTTP_GET, []() {
    String volume = HTTP.arg("volume");         
    if (volume.toInt() <= 30 && volume.toInt() >= 0) {                         
      mp3_set_volume(volume.toInt());
      jsonWrite(configSetup, "voiceVolume", volume);
      saveConfig();   
      String ans = "OK ";
      ans+=volume;
      HTTP.send(200, "text / plain", ans); 
    }
    else {                                        // иначе
      HTTP.send(200, "text / plain", "error."); 
    }
  });
  
  HTTP.on("/sensor", HTTP_GET, []() {
    String sensor = HTTP.arg("sensor");
    String responce = "";
    String answer;
    Serial.println(sensor);
    countAnswer++;
    answer += "OK ";
    answer += sensor;
    answer += countAnswer;
    
    if (sensor == "alert") {
      HTTP.send(200, "text / plain", answer);
      //logListAdd(sensor);
      alert();
    } else if(sensor == "hello") {
      HTTP.send(200, "text / plain", answer);
      //send_message(1);
      doorbell();
    }
    Serial.print("Continue ");
    Serial.print(countAnswer);
    Serial.println(" times");
  });
  // Добавляем функцию Update для перезаписи прошивки по WiFi при 1М(256K SPIFFS) и выше
  httpUpdater.setup(&HTTP);
  // Запускаем HTTP сервер
  HTTP.begin();
}
String getURL(String urls) {
  String answer = "";
  HTTPClient aaaa;
  aaaa.begin(urls); //HTTP
  int httpCode = aaaa.GET();
  if (httpCode == HTTP_CODE_OK) {
    answer = aaaa.getString();
  }
  aaaa.end();
  return answer;
}
