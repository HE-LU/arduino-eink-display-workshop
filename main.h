#ifndef _MAIN_H_
#define _MAIN_H_

#include <ArduinoJson.h>

#include "logs.h"
#include "data.h"
#include "display.h"
#include "wifi.h"
#include "examples.h"

#define JSON_BUFFER_SIZE 1024 // buffer size: https://arduinojson.org/assistant/

int main();
void loadData(String url, StaticJsonDocument<JSON_BUFFER_SIZE>* jsonBuffer);
DataHolder parseData(StaticJsonDocument<JSON_BUFFER_SIZE>* jsonBuffer);

#endif
