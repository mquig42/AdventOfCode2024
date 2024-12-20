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
    //Cheating for 2 picoseconds results in 8 possible moves
    //which, due to the way my coordinates work, can be represented as integers
    //"move up 2 spaces", for example, is -512
    int16_t moves[] = {-512, -257, -255, -2, 2, 255, 257, 512};
    uint64_t count = 0;
    
    for(auto rt : racetrack)
    {
        for(int16_t m : moves)
        {
            if(racetrack.count(rt.first + m) && racetrack[rt.first + m] > rt.second + 101)
            {
                count++;
            }
        }
    }

    return count;
}

uint64_t Day20::solve2()
{
    return 0;
}
