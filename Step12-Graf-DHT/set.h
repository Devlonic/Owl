#include <ESP8266WiFi.h>        //Содержится в пакете. Видео с уроком http://esp8266-arduinoide.ru/step1-wifi
#include <ESP8266WebServer.h>   //Содержится в пакете. Видео с уроком http://esp8266-arduinoide.ru/step2-webserver
#include <ESP8266SSDP.h>        //Содержится в пакете. Видео с уроком http://esp8266-arduinoide.ru/step3-ssdp
#include <ESP8266HTTPClient.h>
#include <FS.h>                 //Содержится в пакете. Видео с уроком http://esp8266-arduinoide.ru/step4-fswebserver
//                    ПЕРЕДАЧА ДАННЫХ НА WEB СТРАНИЦУ. Видео с уроком http://esp8266-arduinoide.ru/step5-datapages/
//                    ПЕРЕДАЧА ДАННЫХ С WEB СТРАНИЦЫ.  Видео с уроком http://esp8266-arduinoide.ru/step6-datasend/
#include <ArduinoJson.h>        //Установить из менеджера библиотек. https://arduinojson.org/
//                    ЗАПИСЬ И ЧТЕНИЕ ПАРАМЕТРОВ КОНФИГУРАЦИИ В ФАЙЛ. Видео с уроком http://esp8266-arduinoide.ru/step7-fileconfig/
#include <ESP8266HTTPUpdateServer.h>  //Содержится в пакете.  Видео с уроком http://esp8266-arduinoide.ru/step8-timeupdate/
#include <DNSServer.h> //Содержится в пакете.  // Для работы символьных имен в режиме AP отвечает на любой запрос например: 1.ru
// Библиотеки устройств
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

     
// Объект для обнавления с web страницы
ESP8266HTTPUpdateServer httpUpdater;

// Web интерфейс для устройства
ESP8266WebServer HTTP(80);

// Для файловой системы
File fsUploadFile;

// Для работы символьных имен в режиме AP
DNSServer dnsServer;
// Датчик DHT

#define led 2
int jk = 0;
String configSetup = "{}";
String configJson = "{}";
int port = 80;
int jkl = 30;

int countAnswer;
bool alertStart = false;
bool todaySaid = false;
bool twothreesaid[] = {false, false, false, false};

String currentTime = "";
String currentDate = "";
