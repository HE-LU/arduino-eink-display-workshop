#include "display.h"

void displayNoWiFiConnection()
{
	display.init(BAUD_RATE);
	display.setRotation(3); // landscape
	display.setFullWindow();
	display.firstPage();

	int16_t textBoundsX, textBoundsY;
	uint16_t textBoundsWidth, textBoundsHeight;

	uint16_t displayWidth = display.width() - 1;
	uint16_t displayHeight = display.height() - 1;

	char* title = "No WiFi Connection!";

	do
	{
		display.fillScreen(GxEPD_WHITE);

		// Text
		display.setTextColor(GxEPD_BLACK);
		display.setFont(&FreeSerif12pt7b);

		display.getTextBounds(title, 0, 0, &textBoundsX, &textBoundsY, &textBoundsWidth, &textBoundsHeight);
		uint16_t textX = ((display.width() - textBoundsWidth) / 2) - textBoundsX;
		uint16_t textY = ((display.height() - textBoundsHeight) / 2) - textBoundsY;

		display.setCursor(textX, textY);
		display.print(title);

		// Rectangle
		display.drawLine(0, 0, displayWidth, 0, GxEPD_BLACK);
		display.drawLine(0, 0, 0, displayHeight, GxEPD_BLACK);
		display.drawLine(displayWidth, 0, displayWidth, displayHeight, GxEPD_BLACK);
		display.drawLine(0, displayHeight, displayWidth, displayHeight, GxEPD_BLACK);

	} while(display.nextPage());
}

void displayData(DataHolder data)
{
	display.init(BAUD_RATE);
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

char* alignText(char* text, int length, bool toLeft)
{
	if(sizeof(text) < length)
	{
		char newText[length];

		if(toLeft)
		{
			strcpy(newText, text);
			for(int i = 0; i < (length - sizeof(text)); i++)
				strcat(newText, " ");
		}
		else
		{
			for(int i = 0; i < (length - sizeof(text)); i++)
				strcat(newText, " ");
			strcat(newText, text);
		}
		return newText;
	}

	return text;
}