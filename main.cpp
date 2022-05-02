#include "main.h"

String SPREADSHEET_URL = "https://sheets.googleapis.com/v4/spreadsheets/XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX/values/"
						 "Arduino?alt=json&valueRenderOption=FORMATTED_VALUE&key=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

// MULTI_WIFI_COUNT is set to 2 by default!
const char* WIFI_SSIDS[MULTI_WIFI_COUNT] = {"XXXXXXXXXXXXXXXX", ""};
const char* WIFI_PASSWORDS[MULTI_WIFI_COUNT] = {"XXXXXXXXXXXXXXXX", ""};

int main()
{
	if(connectToMultiWiFi(WIFI_SSIDS, WIFI_PASSWORDS))
	{
		StaticJsonDocument<JSON_BUFFER_SIZE> jsonBufferData;
		loadData(SPREADSHEET_URL, &jsonBufferData);
		disconnectWiFi();

		DataHolder dataHolder = parseData(&jsonBufferData);

		displayData(dataHolder);
	}
	else
	{
		displayNoWiFiConnection();
	}

	return 0;
}

void loadData(String url, StaticJsonDocument<JSON_BUFFER_SIZE>* jsonBuffer)
{
	logln("Loading data from: " + String(url));

	WiFiClientSecure wifiClient;
	wifiClient.setInsecure();
	wifiClient.setBufferSizes(JSON_BUFFER_SIZE, JSON_BUFFER_SIZE);
	wifiClient.connect(url, 80);

	HTTPClient httpClient;
	httpClient.begin(wifiClient, url);

	int httpStatus = httpClient.GET();

	log("HTTP status code: ");
	logln(httpStatus);

	if(httpStatus == 200)
	{
		String payload = httpClient.getString();
		httpClient.end();

		log("Payload: ");
		logln(payload);

		DeserializationError parseError = deserializeJson(*jsonBuffer, payload);

		if(parseError)
		{
			logln("JSON parse error");
		}
		else
		{
			logln("Parsing JSON data success");
			return;
		}
	}
	else
	{
		httpClient.end();
		logln("HTTP response error");
	}
}

DataHolder parseData(StaticJsonDocument<JSON_BUFFER_SIZE>* jsonBuffer)
{
	const char* header = (*jsonBuffer)["values"][0][0];

	const char* symbol1 = (*jsonBuffer)["values"][1][0];
	const char* value1 = (*jsonBuffer)["values"][1][1];
	const char* change1 = (*jsonBuffer)["values"][1][2];
	// const char* item1 = alignText(symbol1, 7, true); // + alignText(value1, 7, false) + alignText(change1, 9, false);

	const char* symbol2 = (*jsonBuffer)["values"][2][0];
	const char* value2 = (*jsonBuffer)["values"][2][1];
	const char* change2 = (*jsonBuffer)["values"][2][2];
	// const char* item2 = alignText(symbol2, 7, true); // + alignText(value2, 7, false) + alignText(change2, 9, false);

	const char* symbol3 = (*jsonBuffer)["values"][3][0];
	const char* value3 = (*jsonBuffer)["values"][3][1];
	const char* change3 = (*jsonBuffer)["values"][3][2];
	// const char* item3 = alignText(symbol3, 7, true); // + alignText(value3, 7, false) + alignText(change3, 9, false);

	const char* portfolioValue = (*jsonBuffer)["values"][4][0];
	const char* portfolioReturn = (*jsonBuffer)["values"][4][1];
	const char* portfolioGain = (*jsonBuffer)["values"][4][2];
	const char* footer = portfolioValue; // + "  " + portfolioReturn + "  " + portfolioGain;

	return DataHolder(header, value1, value2, value3, footer);
}
