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

//This finds the correct answer for the sample input, but is off by one for the real input
//I'm not including the starting position, that may have something to do with it
//Why the discrepancy between inputs though?
long Day06::solve1()
{
    int8_t directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    uint8_t direction = 0;
    uint16_t guardPos = guardStart;
    uint16_t newPos;

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

long Day06::solve2()
{
    return 0;
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
