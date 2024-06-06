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

char *ssid = "AndriyMax";
char *password = "ac1771bb";
//uint8_t mac[] = {0xC0, 0xA5, 0xDD, 0x08, 0x62, 0xA4}; // old mecrusys
uint8_t mac[] = {0x78, 0x8C, 0xB5, 0x66, 0x3D, 0xE9}; // 78-8c-b5-66-3d-e9

int lastStatusSensor = 0;
int n = 0;
int countPressed = 0;
