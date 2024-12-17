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

//This definitely will not run on a Cardputer
//It worked successfully on a desktop computer
uint64_t Day16::solve1()
{
    runDijkstra();
    return bestScore;
}

uint64_t Day16::solve2()
{
    return allPaths.size();
}

//Dijkstra's algorithm, set to run until all possible paths have been explored
//It stores the length of the shortest path, and a set of all points on any shortest path
//in the class vars bestScore and allPaths
void Day16::runDijkstra()
{
    uint16_t nextPos;
    uint8_t nextDir;
    queueNode current;
    std::unordered_map<state, uint32_t, state> visited;
    std::priority_queue<queueNode> unvisited;

    visited[{start, 1}] = 0;
    unvisited.push({ start, 1, 0 });

    while (!unvisited.empty())
    {
        current = unvisited.top();
        unvisited.pop();

        std::unordered_set<uint16_t> path(current.path);
        path.insert(current.position);

        if (current.position == end && current.score <= bestScore)
        {
            bestScore = current.score;
            for (uint16_t p : path)
                allPaths.insert(p);
        }

        //From any state there are 3 possible moves:
        //Rotate left, rotate right, and go forward
        //nextPos represents the position directly in front
        if (current.direction == up)
            nextPos = makeCoord(row(current.position) - 1, col(current.position));
        else if (current.direction == right)
            nextPos = makeCoord(row(current.position), col(current.position) + 1);
        else if (current.direction == down)
            nextPos = makeCoord(row(current.position) + 1, col(current.position));
        else
            nextPos = makeCoord(row(current.position), col(current.position) - 1);

        //If nextPos is a valid space and hasn't already been reached by a shorter path, add it to unvisited
        if (spaces.count(nextPos) && (visited.count({ nextPos, current.direction }) == 0 || visited[{nextPos, current.direction}] >= (current.score + 1)))
        {
            unvisited.push({ nextPos, current.direction, current.score + 1, path });
            visited[{nextPos, current.direction}] = current.score + 1;
        }

        //Turn right
        nextDir = (current.direction + 1) % 4;
        if (visited.count({ current.position, nextDir }) == 0 || visited[{current.position, nextDir}] >= (current.score + 1000))
        {
            unvisited.push({ current.position, nextDir, current.score + 1000, path });
            visited[{current.position, nextDir}] = current.score + 1000;
        }

        //Turn left
        nextDir = (current.direction + 3) % 4;
        if (visited.count({ current.position, nextDir }) == 0 || visited[{current.position, nextDir}] >= (current.score + 1000))
        {
            unvisited.push({ current.position, nextDir, current.score + 1000, path });
            visited[{current.position, nextDir}] = current.score + 1000;
        }
    }
}
