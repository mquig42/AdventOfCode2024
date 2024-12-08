#include "day08.h"

Day08::Day08()
{
    dayNumber = 8;
}

void Day08::load(File file)
{
    String line;
    int r = 0;

    while(file.available())
    {
        line = file.readStringUntil('\n');
        numCols = line.length() - 1; //-1 to ignore the CR at the end
        for(int c = 0; c < numCols; c++)
        {
            if(line[c] != '.')
            {
                antennas[line[c]].push_back(makeCoord(r, c));
            }
        }
        r++;
    }

    numRows = r;
    
    file.close();
}

uint64_t Day08::solve1()
{
    return 0;
}

uint64_t Day08::solve2()
{
    return 0;
}
