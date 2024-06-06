void debug() {
  Serial.println(n=n+1);
}
void displayAvailableAPs() {
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.print(" ");
      Serial.print(WiFi.BSSIDstr(i));
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");
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
     
     if (httpCode == 200) {
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
  countPressed++;
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
     if (httpCode == 200) {
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
  displayAvailableAPs();
  WiFi.begin(ssidcur, passcur, 0, mac);
  //WiFi.begin(ssidcur, passcur);
  Serial.print("Connecting to ");
  Serial.print(ssidcur);
  Serial.print(" ");
  Serial.println("{0xC0, 0xA5, 0xDD, 0x08, 0x62, 0xA4}");
  int ttemp = 10;
  while (--ttemp > 0 && WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  if(WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected to ");  
    Serial.print(ssidcur);
    Serial.print(" ");
    Serial.println(WiFi.BSSIDstr());
    Serial.print(" ");
    Serial.println(WiFi.localIP());
    Serial.print(" ");
    Serial.println(WiFi.macAddress());
    return 1;
  } else {
    Serial.print("No connection to ");
    Serial.println(ssidcur);
    return 0;
  }
}

void showWiFiStatus() {
    Serial.println("");
    Serial.print(WiFi.SSID());
    Serial.print(" (");
    Serial.print(WiFi.RSSI());
    Serial.print(") ");
    Serial.print(WiFi.BSSIDstr());
    Serial.println("");
}



template<typename T>
void myLog(T msg) {
  Serial.print(msg);
}

template<typename T>
void myLogLN(T msg) {
  Serial.println(msg);
}
