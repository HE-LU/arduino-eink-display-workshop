#include "logs.h"

void logSetup()
{
	Serial.begin(BAUD_RATE);
	Serial.println();
	Serial.flush();
}

void log(const char* text)
{
	if(LOGS_ENABLED)
	{
		Serial.print(text);
		Serial.flush();
	}
}

void logln(const char* text)
{
	if(LOGS_ENABLED)
	{
		Serial.println(text);
		Serial.flush();
	}
}

void log(const int text)
{
	if(LOGS_ENABLED)
	{
		Serial.print(text);
		Serial.flush();
	}
}

void logln(const int text)
{
	if(LOGS_ENABLED)
	{
		Serial.println(text);
		Serial.flush();
	}
}

void log(const String text)
{
	if(LOGS_ENABLED)
	{
		Serial.print(text);
		Serial.flush();
	}
}

void logln(const String text)
{
	if(LOGS_ENABLED)
	{
		Serial.println(text);
		Serial.flush();
	}
}