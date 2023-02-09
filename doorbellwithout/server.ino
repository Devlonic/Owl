void handleRoot() {
  server.send(200, "text/plain", "1");
}
int testDoorBell() {
  server.send(200, "text/plain", sendingOneTime());
}

void httpInit() {
  // Добавляем функцию Update для перезаписи прошивки по WiFi при 1М(256K SPIFFS) и выше
  httpUpdater.setup(&server);

  server.on("/", handleRoot);
  server.on("/test", testDoorBell);
  server.on("/restart", HTTP_GET, []() {
    String restart = server.arg("device");          // Получаем значение device из запроса
    if (restart == "ok") {                         // Если значение равно Ок
      server.send(200, "text / plain", "Reset OK"); // Oтправляем ответ Reset OK
      ESP.restart();                                // перезагружаем модуль
    }
    else {                                        // иначе
      server.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
    }
  });
    // Запускаем server сервер
  server.begin();
}
String getURL(String urls) {
  String answer = "";
  HTTPClient http;
  http.begin(urls); //HTTP
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    answer = http.getString();
  }
  http.end();
  return answer;
}
