#include "day04.h"

Day04::Day04()
{
    dayNumber = 4;
}

void Day04::load(File file)
{
    while(file.available())
    {
        grid.push_back(file.readStringUntil('\n'));
    }
    file.close();
}

uint64_t Day04::solve1()
{
    long count = 0;

    for(int r = 0; r < grid.size(); r++)
    {
        for(int c = 0; c < grid[0].length(); c++)
        {
            count += isXmas(r, c);
        }
    }

    return count;
}

uint64_t Day04::solve2()
{
    long count = 0;

    for(int r = 0; r < grid.size(); r++)
    {
        for(int c = 0; c < grid[0].length(); c++)
        {
            if(isXmas2(r, c))
                count++;
        }
    }

    return count;
}

//Character lookup with bounds checking
char Day04::getChar(uint8_t row, uint8_t col)
{
    if(row < 0 || row >= grid.size() || col < 0 || col >= grid[0].length())
        return 0;
    return grid[row][col];
}

//Returns the number of 'XMAS' straings that begin at the given coords, in any direction
uint8_t Day04::isXmas(uint8_t row, uint8_t col)
{
    int8_t directions[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    String xmas("XMAS");
    bool found;
    uint8_t count = 0;

    for(int d = 0; d < 8; d++)
    {
        found = true;
        for(int i = 0; i < 4; i++)
        {
            if(xmas[i] != getChar(row + i * directions[d][0], col + i * directions[d][1]))
            {
                found = false;
                break;
            }
        }
        if(found)
            count++;
    }
    return count;
}

//Returns true if there is an X-MAS centred on the given coords
bool Day04::isXmas2(uint8_t row, uint8_t col)
{
    bool DR = false;
    bool UR = false;
    if(getChar(row, col) != 'A')
        return false;
    
    if((getChar(row - 1, col - 1) == 'M' && getChar(row + 1, col + 1) == 'S') || (getChar(row - 1, col - 1) == 'S' && getChar(row + 1, col + 1) == 'M'))
        DR = true;
    if((getChar(row + 1, col - 1) == 'M' && getChar(row - 1, col + 1) == 'S') || (getChar(row + 1, col - 1) == 'S' && getChar(row - 1, col + 1) == 'M'))
        UR = true;
    return DR && UR;
}
