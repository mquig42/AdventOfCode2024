#include <Arduino.h>
#include <M5Cardputer.h>
#include <SPI.h>
#include <SD.h>

#include "day.h"
#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"
#include "day06.h"
#include "day07.h"
#include "day08.h"
#include "day09.h"
#include "day10.h"

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

	day.load(SD.open("/AoC_Data/10.txt"));
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
		case 3:
			static Day03 d3;
			return d3;
		case 4:
			static Day04 d4;
			return d4;
		case 5:
			static Day05 d5;
			return d5;
		case 6:
			static Day06 d6;
			return d6;
		case 7:
			static Day07 d7;
			return d7;
		case 8:
			static Day08 d8;
			return d8;
		case 9:
			static Day09 d9;
			return d9;
		default:
			static Day10 d10;
			return d10;
	}
}
