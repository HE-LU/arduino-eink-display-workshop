#include <EEPROM.h>

long eepromExample(long val1, long val2, long val3)
{
	long previousVal1 = 0;
	long previousVal2 = 0;
	long previousVal3 = 0;

	EEPROM.begin(sizeof(long) * 10);

	EEPROM.get(0, previousVal1);
	EEPROM.get(sizeof(long), previousVal2);
	EEPROM.get(sizeof(long) * 2, previousVal3);

	EEPROM.put(0, val1);
	EEPROM.put(sizeof(long), val2);
	EEPROM.put(sizeof(long) * 2, val3);

	EEPROM.commit();

	return val1 + val2 + val3;
}
