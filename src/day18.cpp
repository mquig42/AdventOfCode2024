#include "day18.h"

Day18::Day18()
{
    dayNumber = 18;
}

void Day18::load(File file)
{
    while(file.available())
    {
        bytes.push_back(makeCoord(file.parseInt(), file.parseInt()));
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

//Drop some bytes, then do a bread first search
uint64_t Day18::solve1()
{
    std::unordered_set<uint16_t> corrupted;
    std::unordered_set<uint16_t> visited;
    std::queue<queueNode> q;
    queueNode current;
    uint16_t next;

    for(int i = 0; i < toDrop; i++)
    {
        corrupted.insert(bytes[i]);
    }

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

uint64_t Day18::solve2()
{
    return 0;
}
