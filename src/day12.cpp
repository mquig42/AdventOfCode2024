#include "day12.h"

Day12::Day12()
{
    dayNumber = 12;
}

void Day12::load(File file)
{
    //NOTE: Can I do random file access? Might be able to build the plots structure directly,
    //without using memory for grid.
    //I figure if I can separate out each plot, I should be able to figure out the rest.
    //Store each plot as a set of points. There was a puzzle last year to get the area of a shape
    //from the points on its edge, and I might be able to use that here.
    //That way I don't need to store the interior.
    while(file.available())
    {
        grid.push_back(file.readStringUntil('\n'));
    }
    numRows = grid.size();
    numCols = grid[0].length() - 1; //Ignore trailing CR
    file.close();

    char c;
    for(uint8_t row = 0; row < numRows; row++)
    {
        for(uint8_t col = 0; col < numCols; col++)
        {
            c = getCrop(row, col);
            if(c)
            {
                plots.push_back(collectPlot(row, col));
            }
        }
    }
}

uint64_t Day12::solve1()
{
    uint64_t sum = 0;
    for(std::unordered_set<uint16_t> plot : plots)
    {
        sum += cost1(plot);
    }

    return sum;
}

uint64_t Day12::solve2()
{
    return 0;
}

//Determine the cost of a plot, given by area * perimeter
uint64_t Day12::cost1(std::unordered_set<uint16_t> plot)
{
    uint64_t cost = 0;

    for(uint16_t p : plot)
    {
        cost += 4 - countNeighbours(p, plot);
    }

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
        grid[row(point)][col(point)] = '\0';
        plot.insert(point);

        neighbour = makeNeighbour(point, 'U');
        if(getCrop(neighbour) == crop)
            q.push(neighbour);
        neighbour = makeNeighbour(point, 'R');
        if(getCrop(neighbour) == crop)
            q.push(neighbour);
        neighbour = makeNeighbour(point, 'D');
        if(getCrop(neighbour) == crop)
            q.push(neighbour);
        neighbour = makeNeighbour(point, 'L');
        if(getCrop(neighbour) == crop)
            q.push(neighbour);
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
