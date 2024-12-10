#include "day10.h"

Day10::Day10()
{
    dayNumber = 10;
}

void Day10::load(File file)
{
    while(file.available())
    {
        heightmap.push_back(file.readStringUntil('\n'));
    }
    numRows = heightmap.size();
    numCols = heightmap[0].length() - 1; //Ignore the trailing CR
    file.close();
}

uint64_t Day10::solve1()
{
    uint64_t sum = 0;

    for(int r = 0; r < numRows; r++)
    {
        for(int c = 0; c < numCols; c++)
        {
            if(heightmap[r][c] == '0')
            {
                sum += nines(r, c).size();
            }
        }
    }

    return sum;
}

uint64_t Day10::solve2()
{
    uint64_t sum = 0;

    for(int r = 0; r < numRows; r++)
    {
        for(int c = 0; c < numCols; c++)
        {
            if(heightmap[r][c] == '0')
            {
                sum += score(r, c);
            }
        }
    }

    return sum;
}

//Doing it this way means the program actually runs, but comes up with the wrong answer
//Sometimes it works, sometimes it returns a value that's much too high. Why?
//Because the score isn't the number of trails, it's the number of /distinct/ 9s that can be reached by a trail
//This algorithm double-counts any 9s reachable by multiple trails
//Which is the solution to part 2
uint16_t Day10::score(uint8_t row, uint8_t col)
{
    uint16_t s = 0;
    char h = heightmap[row][col];
    if(h == '9')
        return 1;
    
    if(row > 0 && heightmap[row - 1][col] == h + 1)
        s += score(row - 1, col);
    if(col + 1 < numCols && heightmap[row][col + 1] == h + 1)
        s += score(row, col + 1);
    if(row + 1 < numRows && heightmap[row + 1][col] == h + 1)
        s += score(row + 1, col);
    if(col > 0 && heightmap[row][col - 1] == h + 1)
        s += score(row, col - 1);
    
    return s;
}

std::set<uint16_t> Day10::nines(uint8_t row, uint8_t col)
{
    std::set<uint16_t> r;
    char h = heightmap[row][col];
    if(h == '9')
    {
        r.insert(makeCoord(row, col));
        return r;
    }
    
    std::set<uint16_t> other;
    if(row > 0 && heightmap[row - 1][col] == h + 1)
    {
        other = nines(row - 1, col);
        r.insert(other.begin(), other.end());
    }
    if(col + 1 < numCols && heightmap[row][col + 1] == h + 1)
    {
        other = nines(row, col + 1);
        r.insert(other.begin(), other.end());
    }
    if(row + 1 < numRows && heightmap[row + 1][col] == h + 1)
    {
        other = nines(row + 1, col);
        r.insert(other.begin(), other.end());
    }
    if(col > 0 && heightmap[row][col - 1] == h + 1)
    {
        other = nines(row, col - 1);
        r.insert(other.begin(), other.end());
    }
    
    return r;
}
