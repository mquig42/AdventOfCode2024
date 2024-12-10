#include "day09.h"

Day09::Day09()
{
    dayNumber = 9;
}

//How to represent input?
//There are 10,000 files in my input, representing total disk space of 94,595 blocks
//File IDs will be between 0 and 9999, which fits in a uint16_t
//At 2 bytes per block, an array of all blocks will take up 189,190kB, which is less than the RAM on a Cardputer
//Might be tight though. UPDATE: tried it, didn't fit. Can I use the MicroSD card? Might be slow. Or is there a clever way?
void Day09::load(File file)
{
    int16_t fileID = 0;
    bool isFile = true;
    int8_t c = file.read() - '0';

    while(c >= 0 && c <= 9)
    {
        for(int i = 0; i < c; i++)
        {
            if(isFile)
                disk.push_back(fileID);
            else
                disk.push_back(-1);
        }

        if(isFile)
            fileID++;
        
        isFile = !isFile;
        c = file.read() - '0';
    }

    file.close();
}

uint64_t Day09::solve1()
{
    return 0;
}

uint64_t Day09::solve2()
{
    return 0;
}
