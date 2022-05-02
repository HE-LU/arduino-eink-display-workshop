#ifndef _WIFI_H_
#define _WIFI_H_

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include "logs.h"

#define MULTI_WIFI_COUNT 2
#define WIFI_CONNECT_TIMEOUT_IN_SECONDS 5

bool connectToMultiWiFi(const char* ssids[MULTI_WIFI_COUNT], const char* passwords[MULTI_WIFI_COUNT]);
void disconnectWiFi();

#endif
