#include <Arduino.h>
#include <M5Cardputer.h>
#include <SPI.h>
#include <SD.h>

#include "day.h"
#include "day01.h"
#include "day02.h"
#include "day03.h"

//Pins for SD card
#define SD_SPI_SCK_PIN  40
#define SD_SPI_MISO_PIN 39
#define SD_SPI_MOSI_PIN 14
#define SD_SPI_CS_PIN   12

Day &selectDay(int n);

void setup()
{
	auto cfg = M5.config();
	M5Cardputer.begin(cfg);

	//init SD card
	SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
	SD.begin(SD_SPI_CS_PIN, SPI, 25000000);

	Day &day = selectDay(25); 

	day.load(SD.open("/AoC_Data/03.txt"));
	day.solveBoth(&M5Cardputer.Display);
}

void loop()
{

}

Day &selectDay(int n)
{
    switch(n)
	{
		case 1:
			static Day01 d1;
			return d1;
		case 2:
			static Day02 d2;
			return d2;
		default:
			static Day03 d;
			return d;
	}
}
