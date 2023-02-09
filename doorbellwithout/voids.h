void debug() {
  Serial.println(n=n+1);
}
String sendingOneTime() {
    bool sended = false;
    HTTPClient http;
    Serial.print("[HTTP] Sending \"/sensor?sensor=hello\" \n");
    http.begin("http://192.168.1.6/sensor?sensor=hello"); //HTTP  
    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();
    String payload;
    if (httpCode > 0) {
     Serial.printf("[HTTP] GET... code: %d\n", httpCode);
     
     if (httpCode == HTTP_CODE_OK) {
        sended = true;
        payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      payload = http.errorToString(httpCode);
    }
    http.end();
    return payload;
}
void sending() {
  int times = 4;
  bool sended = false;
  while(times-- && !sended) {
    HTTPClient http;
    Serial.print("[HTTP] Sending \"/sensor?sensor=hello\" \n");
    http.begin("http://192.168.1.6/sensor?sensor=hello"); //HTTP  
    Serial.print("[HTTP] GET...\n");
    int httpCode = http.GET();
    if (httpCode > 0) {
     Serial.printf("[HTTP] GET... code: %d\n", httpCode);
     if (httpCode == HTTP_CODE_OK) {
        sended = true;
        String payload = http.getString();
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  
  http.end();
  delay(500);
  }
  for (int t = 5; t > 0; t--) {
    Serial.printf("[DELAY] WAIT %d...\n", t);
    delay(1000);
  }
}
int obstacle() {
  debouncer.update();
  int value = debouncer.read();
  return value;
}
bool wificonnect(char* ssidcur, char* passcur) {
  WiFi.begin(ssidcur, passcur);
  Serial.print("Connecting to ");
  Serial.println(ssidcur);
  int ttemp = 10;
  while (--ttemp > 0 && WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  if(WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected to ");  
    Serial.println(ssidcur);
    return 1;
  } else {
    Serial.print("No connection to ");
    Serial.println(ssidcur);
    return 0;
  }
}
