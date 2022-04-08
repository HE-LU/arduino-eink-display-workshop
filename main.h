#ifndef _MAIN_H_
#define _MAIN_H_

#include <ArduinoJson.h>
#include "data.h"

#define JSON_BUFFER_SIZE 1024 // buffer size: https://arduinojson.org/assistant/

int main();
StaticJsonDocument<JSON_BUFFER_SIZE> loadData(String url);
DataHolder parseData(StaticJsonDocument<JSON_BUFFER_SIZE>& jsonBuffer);
void displayData(DataHolder data);
String alignText(String text, int length, bool toLeft);
long eepromExample(long val1, long val2, long val3);

#endif
