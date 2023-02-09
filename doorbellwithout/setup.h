#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Bounce2.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#define BUTTON_PIN 0

ESP8266WiFiMulti WiFiMulti;
Bounce debouncer = Bounce();
ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

char *ssid = "";
char *password = "";
int lastStatusSensor = 0;
int n = 0;
