#include <Arduino.h>
#include <M5Cardputer.h>
#include <SPI.h>
#include <SD.h>

//Pins for SD card
#define SD_SPI_SCK_PIN  40
#define SD_SPI_MISO_PIN 39
#define SD_SPI_MOSI_PIN 14
#define SD_SPI_CS_PIN   12

void setup()
{
	auto cfg = M5.config();
	M5Cardputer.begin(cfg);
	M5Cardputer.Display.drawString("Advent of Code 2024", 0, 10);

	//init SD card
	SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
	SD.begin(SD_SPI_CS_PIN, SPI, 25000000);

	File file = SD.open("/AoC_Data/1_Test.txt");
	M5Cardputer.Display.drawString(file.readStringUntil('\n'), 0, 20);
	file.close();
}

void loop()
{

}