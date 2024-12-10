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
    String inputStr = file.readStringUntil('\r');
    bool isFile = true;
    for(char c : inputStr)
    {
        if(isFile)
            numFiles++;
        isFile = !isFile;
        input.push_back(c - '0');
    }

    file.close();
}

//Since there isn't enough RAM to simulate the fragging process, calculate a checksum directly from the input
//Two indices, one starts at the beginning, the other at the end. Also use beginID and endID to keep track of file IDs
//For files, simply multiply beginID by addr for every block of the file
//For empty space, use end and endID to find files from the end and add them to the checksum.
uint64_t Day09::solve1()
{
    uint64_t checksum = 0;              //File system checksum
    uint32_t addr = 0;                  //Memory address
    int begin = 0;                      //Index that starts at beginning of input and increases
    uint16_t beginID = 0;               //file ID of input[begin]
    int end = input.size() - 1;         //Index that starts at end of input and decreases
    uint16_t endID = numFiles - 1;      //file ID of input[end]
    bool isFile = true;                 //Does input[begin] represent a file or empty space?
    uint8_t fileCounter = input[end];   //Number of blocks at end that haven't yet been moved

    while(begin < end)
    {
        if(isFile)
        {
            for(int i = 0; i < input[begin]; i++)
            {
                checksum += addr * beginID;
                addr++;
            }
            isFile = false;
            begin++;
            beginID++;
        }
        else
        {
            for(int i = 0; i < input[begin]; i++)
            {
                if(fileCounter <= 0)
                {
                    end -= 2; //dec by 2 to skip empty space and go to the next file
                    fileCounter = input[end];
                    endID--;
                }
                checksum += addr * endID;
                fileCounter--;
                addr++;
            }
            isFile = true;
            begin++;
        }
    }

    return checksum + addr * beginID; //One block wasn't counted. Add it now.
}

//Might actually be able to simulate part 2. Store a list of tuples representing file ID and size in blocks (-1 for empty)
//So instead of 2 bytes per block, it's 3 bytes per file. Can't use a linked list, the pointers would take up too much space,
//but a vector should do. Nope, still too big.
//Have to use a similar approach to part 1
uint64_t Day09::solve2()
{
    std::vector<uint8_t> reallocated(input);
    uint64_t checksum = 0;
    uint32_t addr = 0;
    int end = input.size() - 1;
    uint16_t endID = numFiles - 1;
    bool isFile = true;

    //For each file, iterating backwards from the end
    for(int end = input.size() - 1; end >= 0; end -= 2)
    {
        //Find an empty address with enough space to move the file to
        addr = 0;
        isFile = true;
        for(int i = 0; i < end; i++)
        {
            if((!isFile) && (reallocated[i] >= input[end]))
            {
                //Update the reallocated table.
                //Make the empty space entry smaller and the preceding file entry bigger to reflect the new file being moved
                reallocated[i] -= input[end];
                reallocated[i - 1] += input[end];
                break;
            }
            isFile = !isFile;
            addr += reallocated[i];
        }

        //Add file to checksum
        for(int i = 0; i < input[end]; i++)
            checksum += (addr + i) * endID;
        
        endID--;
    }

    return checksum;
}
