#include "day11.h"

Day11::Day11()
{
    dayNumber = 11;
}

void Day11::load(File file)
{
    while(file.available())
    {
        input.push_back(file.parseInt());
    }
    file.close();
}

uint64_t Day11::solve1()
{
    return 0;
}

uint64_t Day11::solve2()
{
    return 0;
}
