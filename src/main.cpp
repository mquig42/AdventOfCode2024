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

	std::vector<long> list1;
	std::vector<long> list2;
	long sum = 0;

	File file = SD.open("/AoC_Data/1.txt");
	while(file.available())
	{
		list1.push_back(file.parseInt());
		list2.push_back(file.parseInt());
	}
	file.close();

	//This method of reading files adds a 0 to the end of each list
	//Maybe that's how it interprets EOF. Anyway, remove it
	list1.pop_back();
	list2.pop_back();

	//Part 1
	std::sort(list1.begin(), list1.end());
	std::sort(list2.begin(), list2.end());

	for(int i = 0; i < list1.size(); i++)
	{
		sum += std::abs(list1[i] - list2[i]);
	}

	char s[255];
	sprintf(s, "Part 1: %d", sum);
	M5Cardputer.Display.drawString(s, 0, 20);

	//Part 2
	long prev_val = -1;
	long similarity = 0;
	int j = 0;
	int count = 0;
	sum = 0;

	for(int i = 0; i < list1.size(); i++)
	{
		if(list1[i] == prev_val)
			sum += similarity;
		else
		{
			count = 0;
			while(list2[j] < list1[i])
				j++;
			while(list2[j] == list1[i])
			{
				count++;
				j++;
			}
			similarity = list1[i] * count;
			sum += similarity;
			prev_val = list1[i];
		}
	}

	sprintf(s, "Part 2: %d", sum);
	M5Cardputer.Display.drawString(s, 0, 30);
}

void loop()
{

}