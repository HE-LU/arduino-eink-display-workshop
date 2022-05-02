#ifndef _LOGS_H_
#define _LOGS_H_

#include <Arduino.h>

#define LOGS_ENABLED true
#define BAUD_RATE 74880

void logSetup();
void log(const char* text);
void logln(const char* text);
void log(const int text);
void logln(const int text);
void log(const String text);
void logln(const String text);

#endif
