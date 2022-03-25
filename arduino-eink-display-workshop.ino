#include "main.h"

#define DEEP_SLEEP 1 // in minutes
#define BAUD_RATE 57600

// This method is run only once on the device start-up
void setup()
{
	// Init
	uint64_t timestampStart = micros();
	Serial.begin(BAUD_RATE);
	Serial.println();

	// Run Main program
	main();

	// Go into Deep Sleep
	uint64_t timestampEnd = micros();
	uint64_t runtimeLengthMicros = timestampEnd - timestampStart;
	uint64_t deepSleepMicros = DEEP_SLEEP * 60 * 1000 * 1000;
	ESP.deepSleep(deepSleepMicros - runtimeLengthMicros); // x minutes in microseconds
}

// This method is called in a loop
void loop() { }
