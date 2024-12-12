#include "day12.h"

Day12::Day12()
{
    dayNumber = 12;
}

void Day12::load(File file)
{
    while(file.available())
    {
        grid.push_back(file.readStringUntil('\n'));
    }
    file.close();
}

uint64_t Day12::solve1()
{
    return 0;
}

uint64_t Day12::solve2()
{
    return 0;
}
