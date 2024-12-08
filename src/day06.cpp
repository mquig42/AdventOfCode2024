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

uint64_t Day06::solve1()
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
    //We need a record of the guard's path for part 2, not including the starting point or (out of bounds) final point
    //Copy to a vector because an unordered_set uses too much memory
    visited.erase(guardStart);
    visited.erase(guardPos);
    for(uint16_t v : visited)
        visitedVec.push_back(v);
    
    //Add 1 because we removed the starting point
    return visited.size() + 1;
}

//Solution 1: the loops() function simulates the guard's movement and uses an unordered_set of previously visited states to detect loops
//Try loops() after adding an obstacle to each empty space. Runtime 15 minutes 27 seconds
//Solution 2: If a space isn't part of the guard's original route, then adding an obstacle to it won't change anything, right?
//Only test those spaces instead of every empty one. Runtime 3 minutes 7 seconds
//Solution 3: change loops() to only store a set of previously visited turning points, instead of the entire path. Runtime 9 seconds
uint64_t Day06::solve2()
{
    long count = 0;

    for(uint16_t v : visitedVec)
    {
        obstacles.insert(v);
        if(loops())
            count++;
        obstacles.erase(v);
    }

    return count;
}

bool Day06::loops()
{

    std::unordered_set<state, state> visitedStates;
    uint8_t direction = 0;
    uint16_t guardPos = guardStart;
    uint16_t newPos;

    visitedStates.insert({guardPos, direction});
    while(row(guardPos) < numRows && col(guardPos) < numCols)
    {
        newPos = makeCoord(row(guardPos) + directions[direction][0], col(guardPos) + directions[direction][1]);
        while(obstacles.count(newPos))
        {
            if(visitedStates.count({newPos, direction}))
                return true;
            visitedStates.insert({newPos, direction});
            direction = (direction + 1) % 4;
            newPos = makeCoord(row(guardPos) + directions[direction][0], col(guardPos) + directions[direction][1]);
        }
        guardPos = newPos;
    }
    return false;
}
