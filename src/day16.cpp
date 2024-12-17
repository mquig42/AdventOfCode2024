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

        row++;
    }

    file.close();
}

//I'm not sure there's enough memory to do Dijkstra's algorithm on a 141x141 grid with direction as part of state
//There isn't. It works for the sample though.
uint64_t Day16::solve1()
{
    uint16_t nextPos;
    uint8_t nextDir;
    queueNode current;

    visited[{start, 1}] = 0;
    unvisited.push({start, 1, 0});

    while(!unvisited.empty())
    {
        current = unvisited.top();
        unvisited.pop();

        if(current.position == end)
            return current.score;
        
        //From any state there are 3 possible moves:
        //Rotate left, rotate right, and go forward
        //nextPos represents the position directly in front
        if(current.direction == up)
            nextPos = makeCoord(row(current.position) - 1, col(current.position));
        else if(current.direction == right)
            nextPos = makeCoord(row(current.position), col(current.position) + 1);
        else if(current.direction == down)
            nextPos = makeCoord(row(current.position) + 1, col(current.position));
        else
            nextPos = makeCoord(row(current.position), col(current.position) - 1);
        
        //If nextPos is a valid space and hasn't already been reached by a shorter path, add it to unvisited
        if(spaces.count(nextPos) && (visited.count({nextPos, current.direction}) == 0 || visited[{nextPos, current.direction}] > current.score + 1))
        {
            unvisited.push({nextPos, current.direction, current.score + 1});
            visited[{nextPos, current.direction}] = current.score + 1;
        }
        
        //Turn right
        nextDir = (current.direction + 1) % 4;
        if(visited.count({current.position, nextDir}) == 0 || visited[{current.position, nextDir}] > current.score + 1000)
        {
            unvisited.push({current.position, nextDir, current.score + 1000});
            visited[{current.position, nextDir}] = current.score + 1000;
        }

        //Turn left
        nextDir = (current.direction + 3) % 4;
        if(visited.count({current.position, nextDir}) == 0 || visited[{current.position, nextDir}] > current.score + 1000)
        {
            unvisited.push({current.position, nextDir, current.score + 1000});
            visited[{current.position, nextDir}] = current.score + 1000;
        }
    }

    return 0;
}

uint64_t Day16::solve2()
{
    return 0;
}
