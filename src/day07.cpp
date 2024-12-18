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
    uint64_t sum = 0;

    for(equation eq : equations)
    {
        if(calibrate2(eq.value, eq.operands.front(), eq.operands.begin()._M_next(), eq.operands.end()))
            sum += eq.value;
    }

    return sum;
}

Day07::equation Day07::parseLine(String line)
{
    uint64_t val = 0;
    uint16_t n = 0;
    std::forward_list<uint16_t> operands;
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
            operands.push_front(n);
            n = 0;
        }
        i++;
    }

    operands.reverse();
    return {val, operands};
}

//If the equation can be balanced by adding + and * operators, return its value
//Otherwise return 0
uint64_t Day07::calibrate1(equation eq)
{
    uint64_t result;
    int currentOps; //bit mask representing operator list. 0 for +, 1 for *

    //2^(n-1)
    uint8_t operandCount = listSize(eq.operands);
    int opLimit = 1;
    for(int i = 1; i < operandCount; i++)
    {
        opLimit *= 2;
    }

    for(int i = 0; i < opLimit; i++)
    {
        result = eq.operands.front();
        currentOps = i;
        for(auto it = eq.operands.begin()._M_next(); it != eq.operands.end(); it++)
        {
            if(currentOps & 1)
                result *= *it;
            else
                result += *it;
            currentOps /= 2;
        }
        if(result == eq.value)
            return result;
    }

    return 0;
}

//Counts the number of elements in a list. This should be part of the std::forward_list class, but it isn't.
uint8_t Day07::listSize(std::forward_list<uint16_t> lst)
{
    uint8_t count = 0;
    for(uint16_t n : lst)
        count++;
    return count;
}

//The bitmask approach I used for part 1 won't work for three operators
//I've used Racket before, so my thoughts now naturally lead to linked lists and recursion
//though I have to use iterators here. Car and cdr are more elegant.
bool Day07::calibrate2(uint64_t goal, uint64_t acc, std::forward_list<uint16_t>::iterator begin, std::forward_list<uint16_t>::iterator end)
{
    if(begin == end)
        return acc == goal;
    else if(calibrate2(goal, acc + *begin, begin._M_next(), end))
        return true;
    else if(calibrate2(goal, acc * *begin, begin._M_next(), end))
        return true;
    else if(calibrate2(goal, concat(acc, *begin), begin._M_next(), end))
        return true;

    return false;
}

//Concatenates two integers.
//I'm taking advantage of the fact that the input only contains operands with 1 to 3 digits
uint64_t Day07::concat(uint64_t a, uint16_t b)
{
    if(b < 10)
        return a * 10 + b;
    else if(b < 100)
        return a * 100 + b;
    else
        return a * 1000 + b;
}
