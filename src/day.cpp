#include "day.h"

void Day::solveBoth(LovyanGFX* display)
{
    display->setTextColor(GREEN);
    display->setTextFont(2);

    display->printf("Advent of Code 2024 Day %d\n", dayNumber);
	display->printf("Part 1: %llu\n", solve1());
    display->printf("Part 2: %llu\n", solve2());
}
