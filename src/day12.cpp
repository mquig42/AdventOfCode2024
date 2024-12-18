#include "day12.h"

Day12::Day12()
{
    dayNumber = 12;
}

void Day12::load(File file)
{
    while(file.available())
    {
        grid.push_back(file.readStringUntil('\n'));
    }
    numRows = grid.size();
    numCols = grid[0].length() - 1; //Ignore trailing CR
    file.close();

    char c;
    std::unordered_set<uint16_t> plot;
    for(uint8_t row = 0; row < numRows; row++)
    {
        for(uint8_t col = 0; col < numCols; col++)
        {
            c = getCrop(row, col);
            if(c)
            {
                plot = collectPlot(row, col);
                answer1 += cost1(plot);
                answer2 += cost2(plot);
                plot.clear();
            }
        }
    }
}

uint64_t Day12::solve1()
{
    return answer1;
}

uint64_t Day12::solve2()
{
    return answer2;
}

//Determine the cost of a plot, given by area * perimeter
//The perimeter of any point in the plot is 4 minus the number of neighbours
uint64_t Day12::cost1(std::unordered_set<uint16_t> plot)
{
    uint64_t cost = 0;

    for(uint16_t p : plot)
    {
        cost += 4 - countNeighbours(p, plot);
    }

    return cost * plot.size();
}

//Need to find the number of sides (which is equal to the number of corners)
uint64_t Day12::cost2(std::unordered_set<uint16_t> plot)
{
    uint64_t cost = 0;

    for(uint16_t p : plot)
    {
        cost += countCorners(p, plot);
    }
    //M5Cardputer.Display.printf("%llu * %llu = %llu, ", cost, plot.size(), cost * plot.size());
    return cost * plot.size();
}

//Getter function with bounds checking
char Day12::getCrop(uint8_t row, uint8_t col)
{
    if(row >= numRows || col >= numCols)
        return '\0';
    return grid[row][col];
}

char Day12::getCrop(uint16_t coord)
{
    return getCrop(row(coord), col(coord));
}

//Use bread first search to generate a set of all points in the same plot as given location
std::unordered_set<uint16_t> Day12::collectPlot(uint8_t r, uint8_t c)
{
    std::unordered_set<uint16_t> plot;
    std::queue<uint16_t> q;
    char crop = getCrop(r, c);
    uint16_t point, neighbour;

    q.push(makeCoord(r, c));
    while(!q.empty())
    {
        point = q.front();
        q.pop();
        plot.insert(point);

        neighbour = makeNeighbour(point, 'U');
        if(getCrop(neighbour) == crop)
        {
            grid[row(neighbour)][col(neighbour)] = '\0';
            q.push(neighbour);
        }
        neighbour = makeNeighbour(point, 'R');
        if(getCrop(neighbour) == crop)
        {
            grid[row(neighbour)][col(neighbour)] = '\0';
            q.push(neighbour);
        }
        neighbour = makeNeighbour(point, 'D');
        if(getCrop(neighbour) == crop)
        {
            grid[row(neighbour)][col(neighbour)] = '\0';
            q.push(neighbour);
        }
        neighbour = makeNeighbour(point, 'L');
        if(getCrop(neighbour) == crop)
        {
            grid[row(neighbour)][col(neighbour)] = '\0';
            q.push(neighbour);
        }
    }

    return plot;
}

uint8_t Day12::countNeighbours(uint16_t point, std::unordered_set<uint16_t> plot)
{
    uint8_t count = 0;
    if(plot.count(makeNeighbour(point, 'U')))
        count++;
    if(plot.count(makeNeighbour(point, 'R')))
        count++;
    if(plot.count(makeNeighbour(point, 'D')))
        count++;
    if(plot.count(makeNeighbour(point, 'L')))
        count++;
    return count;
}

//Count the corners of each point in the plot
//There are 8 possible corners, 4 concave and 4 convex
uint8_t Day12::countCorners(uint16_t point, std::unordered_set<uint16_t> plot)
{
    //012
    //3.4
    //567
    bool n[8];
    n[0] = plot.count(makeNeighbour(point, 'U') - 1);
    n[1] = plot.count(makeNeighbour(point, 'U'));
    n[2] = plot.count(makeNeighbour(point, 'U') + 1);
    n[3] = plot.count(makeNeighbour(point, 'L'));
    n[4] = plot.count(makeNeighbour(point, 'R'));
    n[5] = plot.count(makeNeighbour(point, 'D') - 1);
    n[6] = plot.count(makeNeighbour(point, 'D'));
    n[7] = plot.count(makeNeighbour(point, 'D') + 1);

    uint8_t count = 0;

    //Convex top left
    if(!n[1] && !n[3])
        count++;
    //convex top right
    if(!n[1] && !n[4])
        count++;
    //convex bottom right
    if(!n[4] && !n[6])
        count++;
    //convex bottom left
    if(!n[3] && !n[6])
        count++;
    //concave top left
    if(!n[0] && n[1] && n[3])
        count++;
    //concave top right
    if(!n[2] && n[1] && n[4])
        count++;
    //concave bottom right
    if(!n[5] && n[3] && n[6])
        count++;
    //concave bottom left
    if(!n[7] && n[4] && n[6])
        count++;

    return count;
}
