#include "day.h"

void Day::solveBoth(LovyanGFX* display)
{
    char s[255];
    sprintf(s, "Advent of Code 2024 Day %d", dayNumber);
    display->drawString(s, 0, 10);

	sprintf(s, "Part 1: %d", solve1());
	display->drawString(s, 0, 20);

    sprintf(s, "Part 2: %d", solve2());
	display->drawString(s, 0, 30);
}
