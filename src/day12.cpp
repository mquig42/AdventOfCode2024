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
}

uint64_t Day12::solve1()
{
    return 0;
}

uint64_t Day12::solve2()
{
    return 0;
}
