// WiFi doc: https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html

#include "wifi.h"

ESP8266WiFiMulti wifiMulti;

bool connectToMultiWiFi(const char* ssids[MULTI_WIFI_COUNT], const char* passwords[MULTI_WIFI_COUNT])
{
	logln("Connecting to multi WiFi");
	WiFi.mode(WIFI_STA);

	for(int i = 0; i < MULTI_WIFI_COUNT; i++)
	{
		log("Adding access point: ");
		logln(ssids[i]);
		wifiMulti.addAP(ssids[i], passwords[i]);
	}

	int status = wifiMulti.run(WIFI_CONNECT_TIMEOUT_IN_SECONDS * 1000);
	log("WiFi status: ");
	logln(status);

	if(status == WL_CONNECTED)
	{
		log("Connected to ");
		logln(WiFi.SSID());
	}
	else
	{
		logln("WiFi connection error");
	}

	return WiFi.status() == WL_CONNECTED;
}

void disconnectWiFi()
{
	WiFi.mode(WIFI_OFF);
}