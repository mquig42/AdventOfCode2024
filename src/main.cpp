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
#include "day11.h"
#include "day12.h"
#include "day13.h"
#include "day14.h"
#include "day15.h"

//Pins for SD card
#define SD_SPI_SCK_PIN  40
#define SD_SPI_MISO_PIN 39
#define SD_SPI_MOSI_PIN 14
#define SD_SPI_CS_PIN   12

Day *selectDay(int n);

void setup()
{
	auto cfg = M5.config();
	M5Cardputer.begin(cfg);

	//init SD card
	SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
	SD.begin(SD_SPI_CS_PIN, SPI, 25000000);

	Day *day = selectDay(25); 

	day->load(SD.open("/AoC_Data/15.txt"));
	day->solveBoth(&M5Cardputer.Display);

	delete(day);
}

void loop()
{

}

Day *selectDay(int n)
{
	Day *d;
    switch(n)
	{
		case 1:
			d = new Day01();
			break;
		case 2:
			d = new Day02();
			break;
		case 3:
			d = new Day03();
			break;
		case 4:
			d = new Day04();
			break;
		case 5:
			d = new Day05();
			break;
		case 6:
			d = new Day06();
			break;
		case 7:
			d = new Day07();
			break;
		case 8:
			d = new Day08();
			break;
		case 9:
			d = new Day09();
			break;
		case 10:
			d = new Day10();
			break;
		case 11:
			d = new Day11();
			break;
		case 12:
			d = new Day12();
			break;
		case 13:
			d = new Day13();
			break;
		case 14:
			d = new Day14();
			break;
		default:
			d = new Day15();
			break;
	}

	return d;
}
