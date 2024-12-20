#include "day20.h"

Day20::Day20()
{
    dayNumber = 20;
}

void Day20::load(File file)
{
    uint8_t row = 0;
    String line;
    while(file.available())
    {
        line = file.readStringUntil('\n');
        for(uint8_t col = 0; col < line.length(); col++)
        {
            if(line[col] == 'S')
            {
                start = makeCoord(row, col);
                racetrack[makeCoord(row, col)] = 1;
            }
            else if(line[col] == 'E')
            {
                end = makeCoord(row, col);
                racetrack[makeCoord(row, col)] = 0;
            }
            else if(line[col] == '.')
            {
                racetrack[makeCoord(row, col)] = 0;
            }
        }
        row++;
    }
    file.close();

    //Now measure distance to all points
    //Since the track does not branch, this is simple
    uint16_t location = start;
    uint16_t u, r, d, l;
    uint16_t steps = 1;
    while(location != end)
    {
        u = makeNeighbour(location, 'U');
        r = makeNeighbour(location, 'R');
        d = makeNeighbour(location, 'D');
        l = makeNeighbour(location, 'L');
        if(racetrack.count(u) && racetrack[u] == 0)
            location = u;
        else if(racetrack.count(r) && racetrack[r] == 0)
            location = r;
        else if(racetrack.count(d) && racetrack[d] == 0)
            location = d;
        else if(racetrack.count(l) && racetrack[l] == 0)
            location = l;
        
        steps++;
        racetrack[location] = steps;
    }
}

uint64_t Day20::solve1()
{
    int16_t moves[] = {-512, -257, -255, -2, 2, 255, 257, 512};
    for(auto rt : racetrack)
    {
        for(int16_t m : moves)
        {
            if(racetrack.count(rt.first + m) && racetrack[rt.first + m] > rt.second + 2)
            {
                if(!cheatCounts.count(racetrack[rt.first + m] - rt.second - 2))
                    cheatCounts[racetrack[rt.first + m] - rt.second - 2] = 1;
                else
                    cheatCounts[racetrack[rt.first + m] - rt.second - 2]++;
            }
        }
    }

    for(auto cc : cheatCounts)
    {
        M5Cardputer.Display.printf("(%u, %u) ", cc.first, cc.second);
    }
    return 0;
}

uint64_t Day20::solve2()
{
    return 0;
}
