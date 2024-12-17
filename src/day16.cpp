#include "day16.h"

Day16::Day16()
{
    dayNumber = 16;
}

void Day16::load(File file)
{
    String line;
    uint8_t row = 0;
    while(file.available())
    {
        line = file.readStringUntil('\n');
        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] == 'S')
            {
                start = makeCoord(row, i);
                spaces.insert(makeCoord(row, i));
            }
            else if(line[i] == 'E')
            {
                end = makeCoord(row, i);
                spaces.insert(makeCoord(row, i));
            }
            else if(line[i] == '.')
            {
                spaces.insert(makeCoord(row, i));
            }
        }
    }

    file.close();
}

//I'm not sure there's enough memory to do Dijkstra's algorithm on a 141x141 grid with direction as part of state
uint64_t Day16::solve1()
{
    return 0;
}

uint64_t Day16::solve2()
{
    return 0;
}
