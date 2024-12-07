#include "day06.h"

Day06::Day06()
{
    dayNumber = 6;
}

void Day06::load(File file)
{
    uint8_t row, col;
    String line;

    row = 0;
    while(file.available())
    {
        line = file.readStringUntil('\n');
        numCols = line.length() - 1; //-1 because readStringUntil('\n') includes the CR as the last char (but not the LF)
        for(col = 0; col < line.length(); col++)
        {
            if(line[col] == '#')
                obstacles.insert(makeCoord(row, col));
            if(line[col] == '^')
                guardStart = makeCoord(row, col);
        }
        row++;
    }
    numRows = row;
    file.close();
}

long Day06::solve1()
{
    std::unordered_set<uint16_t> visited;
    uint8_t direction = 0;
    uint16_t guardPos = guardStart;
    uint16_t newPos;

    visited.insert(guardPos);
    while(row(guardPos) < numRows && col(guardPos) < numCols)
    {
        newPos = makeCoord(row(guardPos) + directions[direction][0], col(guardPos) + directions[direction][1]);
        while(obstacles.count(newPos))
        {
            direction = (direction + 1) % 4;
            newPos = makeCoord(row(guardPos) + directions[direction][0], col(guardPos) + directions[direction][1]);
        }
        visited.insert(newPos);
        guardPos = newPos;
    }

    //Subtract 1 because the loop doesn't end until after an out-of-bounds location has been visited
    return visited.size() - 1;
}

//To solve this, need to implement loop detection and try adding an obstacle to every empty space
//Loop detection is simple, need to store a set of all visited states (position and direction)
//which means I can't just store a bunch of uint16_ts, I need to actually put my own struct in a set
//Seems similar to something from last year. Day 16: The Floor Will Be Lava
long Day06::solve2()
{
    long count = 0;
    uint16_t pos;

    for(uint8_t r = 0; r < numRows; r++)
    {
        M5Cardputer.Display.clear();
        M5Cardputer.Display.setCursor(0, 48);
        M5Cardputer.Display.printf("%d", r);
        for(uint8_t c = 0; c < numCols; c++)
        {
            pos = makeCoord(r, c);
            if(pos != guardStart && !obstacles.count(pos))
            {
                obstacles.insert(pos);
                if(loops())
                    count++;
                obstacles.erase(pos);
            }
        }
    }

    M5Cardputer.Display.setCursor(0, 32);
    return count;
}

//Simple way of storing two uint8_t as one uint16_t
uint16_t Day06::makeCoord(uint8_t row, uint8_t col)
{
    return row * 256 + col;
}

uint8_t Day06::row(uint16_t coord)
{
    return coord / 256;
}

uint8_t Day06::col(uint16_t coord)
{
    return coord % 256;
}

bool Day06::loops()
{

    std::unordered_set<state, state> visited;
    uint8_t direction = 0;
    uint16_t guardPos = guardStart;
    uint16_t newPos;

    visited.insert({guardPos, direction});
    while(row(guardPos) < numRows && col(guardPos) < numCols)
    {
        newPos = makeCoord(row(guardPos) + directions[direction][0], col(guardPos) + directions[direction][1]);
        while(obstacles.count(newPos))
        {
            direction = (direction + 1) % 4;
            newPos = makeCoord(row(guardPos) + directions[direction][0], col(guardPos) + directions[direction][1]);
        }
        if(visited.count({newPos, direction}))
            return true;

        visited.insert({newPos, direction});
        guardPos = newPos;
    }
    return false;
}
