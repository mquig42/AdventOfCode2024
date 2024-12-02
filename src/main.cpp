#include <Arduino.h>
#include <M5Cardputer.h>
#include <SPI.h>
#include <SD.h>

#include "day.h"
#include "day01.h"

//Pins for SD card
#define SD_SPI_SCK_PIN  40
#define SD_SPI_MISO_PIN 39
#define SD_SPI_MOSI_PIN 14
#define SD_SPI_CS_PIN   12

void setup()
{
	auto cfg = M5.config();
	M5Cardputer.begin(cfg);

	//init SD card
	SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
	SD.begin(SD_SPI_CS_PIN, SPI, 25000000);

	Day01 day;

	day.load(SD.open("/AoC_Data/1.txt"));
	day.solveBoth(&M5Cardputer.Display);
}

void loop()
{

}