#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <GxEPD2_3C.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeSerif9pt7b.h> // fonts: https://github.com/adafruit/Adafruit-GFX-Library/tree/master/Fonts

#include "main.h"
#include "display.h"
#include "wifi.h"
#include "examples.h"

const String SPREADSHEET_URL = "https://sheets.googleapis.com/v4/spreadsheets/XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX/values/"
							   "Arduino?alt=json&valueRenderOption=FORMATTED_VALUE&key=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
const String WIFI_SSIDS[ARRAY_SIZE] = {"wifi1", "wifi2"};
const String WIFI_PASSWORDS[ARRAY_SIZE] = {"pass1", "pass2"};

int main()
{
	//connectToWiFi(WIFI_SSIDS[0], WIFI_PASSWORDS[0]);
	connectToMultiWiFi(WIFI_SSIDS, WIFI_PASSWORDS);
	StaticJsonDocument<JSON_BUFFER_SIZE> data = loadData(SPREADSHEET_URL);
	disconnectWiFi();

	DataHolder dataHolder = parseData(data);

	displayData(dataHolder);
	return 0;
}

StaticJsonDocument<JSON_BUFFER_SIZE> loadData(String url)
{
	Serial.println("Loading data from: " + url);

	WiFiClientSecure wifiClient;
	wifiClient.setInsecure();
	wifiClient.connect(url, 80);

	HTTPClient httpClient;
	httpClient.begin(wifiClient, url);

	int httpStatus = httpClient.GET();
	String payload = httpClient.getString();
	httpClient.end();

	Serial.print("HTTP status code: ");
	Serial.println(httpStatus);
	Serial.print("Payload: ");
	Serial.println(payload);

	if(httpStatus == 200)
	{
		StaticJsonDocument<JSON_BUFFER_SIZE> jsonBuffer;
		DeserializationError parseError = deserializeJson(jsonBuffer, payload);

		if(parseError)
		{
			Serial.println("JSON parse error");
		}
		else
		{
			Serial.println("Parsing JSON data success");
			return jsonBuffer;
		}
	}
	else
	{
		Serial.println("HTTP response error");
	}

	return StaticJsonDocument<JSON_BUFFER_SIZE>();
}

DataHolder parseData(StaticJsonDocument<JSON_BUFFER_SIZE>& jsonBuffer)
{
	String header = jsonBuffer["values"][0][0].as<String>();

	String symbol1 = jsonBuffer["values"][1][0].as<String>();
	String value1 = jsonBuffer["values"][1][1].as<String>();
	String change1 = jsonBuffer["values"][1][2].as<String>();
	String item1 = alignText(symbol1, 7, true) + alignText(value1, 7, false) + alignText(change1, 9, false);

	String symbol2 = jsonBuffer["values"][2][0].as<String>();
	String value2 = jsonBuffer["values"][2][1].as<String>();
	String change2 = jsonBuffer["values"][2][2].as<String>();
	String item2 = alignText(symbol2, 7, true) + alignText(value2, 7, false) + alignText(change2, 9, false);

	String symbol3 = jsonBuffer["values"][3][0].as<String>();
	String value3 = jsonBuffer["values"][3][1].as<String>();
	String change3 = jsonBuffer["values"][3][2].as<String>();
	String item3 = alignText(symbol3, 7, true) + alignText(value3, 7, false) + alignText(change3, 9, false);

	String portfolioValue = jsonBuffer["values"][4][0].as<String>();
	String portfolioReturn = jsonBuffer["values"][4][1].as<String>();
	String portfolioGain = jsonBuffer["values"][4][2].as<String>();
	String footer = portfolioValue + "  " + portfolioReturn + "  " + portfolioGain;

	return DataHolder(header, item1, item2, item3, footer);
}

void displayData(DataHolder data)
{
	display.init(115200);
	display.setRotation(3); // landscape
	display.setFullWindow();
	display.firstPage();

	int16_t textBoundsX, textBoundsY;
	uint16_t textBoundsWidth, textBoundsHeight;

	uint16_t displayWidth = display.width() - 1;
	uint16_t displayHeight = display.height() - 1;
	uint16_t paddingHorizontal = 8;
	uint16_t paddingTop = 21;
	uint16_t lineHeight = 24;
	uint16_t linePadding = 4;

	do
	{
		display.fillScreen(GxEPD_WHITE);
		display.setFont(&FreeSerif9pt7b);

		// header text
		display.setTextColor(GxEPD_RED);
		display.getTextBounds(data.header, 0, 0, &textBoundsX, &textBoundsY, &textBoundsWidth, &textBoundsHeight);
		uint16_t headerX = ((display.width() - textBoundsWidth) / 2) - textBoundsX;
		display.setCursor(headerX, paddingTop);
		display.print(data.header);

		// header line
		uint16_t headerLineY = lineHeight + linePadding;
		display.drawLine(paddingHorizontal, headerLineY, displayWidth - paddingHorizontal, headerLineY, GxEPD_RED);

		// text 1
		display.setTextColor(GxEPD_BLACK);
		display.setCursor(paddingHorizontal, paddingTop + lineHeight);
		display.print(data.item1);

		// text 2
		display.setCursor(paddingHorizontal, paddingTop + lineHeight * 2);
		display.print(data.item2);

		// text 3
		display.setCursor(paddingHorizontal, paddingTop + lineHeight * 3);
		display.print(data.item3);

		// footer line
		uint16_t footerLineY = (lineHeight * 4) + linePadding;
		display.drawLine(paddingHorizontal, footerLineY, displayWidth - paddingHorizontal, footerLineY, GxEPD_RED);

		// footer text
		display.setTextColor(GxEPD_RED);
		display.getTextBounds(data.footer, 0, 0, &textBoundsX, &textBoundsY, &textBoundsWidth, &textBoundsHeight);
		uint16_t footerX = ((display.width() - textBoundsWidth) / 2) - textBoundsX;
		display.setCursor(footerX, paddingTop + lineHeight * 4);
		display.print(data.footer);

		// rectangle
		display.drawLine(0, 0, displayWidth, 0, GxEPD_BLACK);
		display.drawLine(0, 0, 0, displayHeight, GxEPD_BLACK);
		display.drawLine(displayWidth, 0, displayWidth, displayHeight, GxEPD_BLACK);
		display.drawLine(0, displayHeight, displayWidth, displayHeight, GxEPD_BLACK);

	} while(display.nextPage());
}

String alignText(String text, int length, bool toLeft)
{
	while(text.length() < length)
	{
		if(toLeft)
		{
			text = text + " ";
		}
		else
		{
			text = " " + text;
		}
	}
	return text;
}
