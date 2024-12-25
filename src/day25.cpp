#include "day25.h"

Day25::Day25()
{
    dayNumber = 25;
}

void Day25::load(File file)
{
    String lines[8];
    std::array<uint8_t, 5> counters;
    while(file.available())
    {
        //Read every line in this group
        for(int i = 0; i < 8; i++)
        {
            lines[i] = file.readStringUntil('\n');
        }

        for(int i = 0; i < 5; i++)
            counters[i] = 0;
        
        for(int r = 1; r < 6; r++)
        {
            for(int c = 0; c < 5; c++)
            {
                if(lines[r][c] == '#')
                    counters[c]++;
            }
        }

        if(lines[0] == "#####\r")
            locks.push_back(counters);
        else
            keys.push_back(counters);
    }
    file.close();
}

void Day25::solveBoth(LovyanGFX *display)
{
    display->setTextColor(GREEN);
    display->setTextFont(2);

    display->printf("Advent of Code 2024 Day %d\n", dayNumber);

    uint64_t count = 0;
    for(int l = 0; l < locks.size(); l++)
    {
        for(int k = 0; k < keys.size(); k++)
        {
            count += match(locks[l], keys[k]);
        }
    }

    display->printf("There are %llu combinations\n", count);
    display->printf("Merry Christmas\n");
}

uint64_t Day25::solve1()
{
    return 0;
}

uint64_t Day25::solve2()
{
    return 0;
}

bool Day25::match(std::array<uint8_t, 5> lock, std::array<uint8_t, 5> key)
{
    for(int i = 0; i < 5; i ++)
    {
        if(lock[i] + key[i] > 5)
            return false;
    }
    return true;
}
