#include "day07.h"

Day07::Day07()
{
    dayNumber = 7;
}

void Day07::load(File file)
{
    while(file.available())
    {
        equations.push_back(parseLine(file.readStringUntil('\n')));
    }

    file.close();
}

//Some of the numbers in today's input are quite big. The largest is 48 bits, and the sum of all of them is 52,
//so a uint64_t will be enough
uint64_t Day07::solve1()
{
    uint64_t sum = 0;

    for(equation eq : equations)
    {
        sum += calibrate1(eq);
    }

    return sum;
}

//Speculation: part 2 may be "You see some more elephants holding - and / operators"
//Close, it's actually just one more operator which concatenates numbers
uint64_t Day07::solve2()
{
    return 0;
}

Day07::equation Day07::parseLine(String line)
{
    uint64_t val = 0;
    uint16_t n = 0;
    std::vector<uint16_t> operands;
    int i = 0;

    //First number of line is the value
    while(line[i] >= '0' && line[i] <= '9')
    {
        val = val * 10 + line[i] - '0';
        i++;
    }

    //Other numbers are operands
    i += 2;
    while(i < line.length())
    {
        if(line[i] >= '0' && line[i] <= '9')
            n = n * 10 + line[i] - '0';
        else
        {
            operands.push_back(n);
            n = 0;
        }
        i++;
    }

    return {val, operands};
}

//If the equation can be balanced by adding + and * operators, return its value
//Otherwise return 0
uint64_t Day07::calibrate1(equation eq)
{
    uint64_t result;
    int currentOps;

    //2^(n-1)
    int opLimit = 1;
    for(int i = 1; i < eq.operands.size(); i++)
    {
        opLimit *= 2;
    }

    for(int i = 0; i < opLimit; i++)
    {
        result = eq.operands[0];
        currentOps = i;
        for(int j = 1; j < eq.operands.size(); j++)
        {
            if(currentOps & 1)
                result *= eq.operands[j];
            else
                result += eq.operands[j];
            currentOps /= 2;
        }
        if(result == eq.value)
            return result;
    }

    return 0;
}
