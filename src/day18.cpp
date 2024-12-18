#include "day18.h"

Day18::Day18()
{
    dayNumber = 18;
}

void Day18::load(File file)
{
    uint8_t c;
    while(file.available())
    {
        //Data is given in col,row format. Swap the order
        c = file.parseInt();
        bytes.push_back(makeCoord(file.parseInt(), c));
    }
    bytes.pop_back();

    //Detect sample input and use smaller map
    if(bytes.size() < 1024)
    {
        maxDim = 6;
        toDrop = 12;
    }

    file.close();
}

//Overriding again because part 2 output isn't an integer
void Day18::solveBoth(LovyanGFX* display)
{
    display->setTextColor(GREEN);
    display->setTextFont(2);

    display->printf("Advent of Code 2024 Day %d\n", dayNumber);
    display->printf("Part 1: %llu\n", solve1());
    uint16_t lastByte = solve2();
    display->printf("Part 2: %d,%d\n", col(lastByte), row(lastByte));
}

//Drop some bytes, then call pathfinding function
uint64_t Day18::solve1()
{
    for(int i = 0; i < toDrop; i++)
    {
        corrupted.insert(bytes[i]);
    }

    return findPath();
}

//Use a binary search to solve faster
uint64_t Day18::solve2()
{
    uint16_t lo = toDrop;
    uint16_t hi = bytes.size() - 1;
    uint16_t n;

    while(hi - lo > 1)
    {
        n = (lo + hi) / 2;
        corrupted.clear();
        for(int i = 0; i <= n; i++)
        {
            corrupted.insert(bytes[i]);
        }
        
        if(findPath())
            lo = n;
        else
            hi = n;
    }
    return bytes[hi];
}

//Use a bread first search to find shortest path to exit
//Return 0 if no path could be found
uint32_t Day18::findPath()
{
    std::unordered_set<uint16_t> visited;
    std::queue<queueNode> q;
    queueNode current;
    uint16_t next;

    visited.insert(0);
    q.push({0, 0});
    while(!q.empty())
    {
        current = q.front();
        q.pop();

        if(row(current.location) == maxDim && col(current.location) == maxDim)
            return current.steps;

        next = makeNeighbour(current.location, 'U');
        if(row(next) <= maxDim && col(next) <= maxDim && !corrupted.count(next) && !visited.count(next))
        {
            visited.insert(next);
            q.push({next, current.steps + 1});
        }
        next = makeNeighbour(current.location, 'R');
        if(row(next) <= maxDim && col(next) <= maxDim && !corrupted.count(next) && !visited.count(next))
        {
            visited.insert(next);
            q.push({next, current.steps + 1});
        }
        next = makeNeighbour(current.location, 'D');
        if(row(next) <= maxDim && col(next) <= maxDim && !corrupted.count(next) && !visited.count(next))
        {
            visited.insert(next);
            q.push({next, current.steps + 1});
        }
        next = makeNeighbour(current.location, 'L');
        if(row(next) <= maxDim && col(next) <= maxDim && !corrupted.count(next) && !visited.count(next))
        {
            visited.insert(next);
            q.push({next, current.steps + 1});
        }
    }
    return 0;
}
