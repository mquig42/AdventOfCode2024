#include "day13.h"

Day13::Day13()
{
    dayNumber = 13;
}

void Day13::load(File file)
{
    uint8_t ax, ay, bx, by;
    uint16_t goalx, goaly;

    while(file.available())
    {
        ax = file.parseInt();
        ay = file.parseInt();
        bx = file.parseInt();
        by = file.parseInt();
        goalx = file.parseInt();
        goaly = file.parseInt();
        input.push_back({ax, ay, bx, by, goalx, goaly});
    }
    input.pop_back();
    file.close();
}

uint64_t Day13::solve1()
{
    uint64_t sum = 0;

    for(clawMachine machine : input)
    {
        sum += solveMachine(machine);
    }

    return sum;
}

uint64_t Day13::solve2()
{
    uint64_t sum = 0;

    for(clawMachine machine : input)
    {
        sum += solveMachine2(machine);
    }

    return sum;
}

//Return smallest number of tokens required to solve the machine, or 0 if it's impossible
uint16_t Day13::solveMachine(clawMachine machine)
{
    uint16_t cost = UINT16_MAX;

    //Thought about doing something better here (Dijkstra), but sometimes it's best to solve part 1 the dumb way to find out what part 2 is.
    //Premature optimization and all that. Anyway, this works fine for part 1 and nothing I was planning would have worked for part 2.
    for(uint8_t a = 0; a <= 100; a++)
    {
        for(uint8_t b = 0; b <= 100; b++)
        {
            if(a * machine.ax + b * machine.bx == machine.goalx && a * machine.ay + b * machine.by == machine.goaly && 3 * a + b < cost)
            {
                cost = 3 * a + b;
            }
        }
    }

    if(cost == UINT16_MAX)
        return 0;

    return cost;
}

//Return smallest number of tokens required to solve the machine, or 0 if it's impossible
//New solution based on linear algebra
uint64_t Day13::solveMachine2(clawMachine machine)
{
    //Do all calculations in 64 bit
    int64_t ax = machine.ax;
    int64_t ay = machine.ay;
    int64_t bx = machine.bx;
    int64_t by = machine.by;
    int64_t gx = machine.goalx + 10000000000000;
    int64_t gy = machine.goaly + 10000000000000;

    //Use modulus to see if solution is an integer
    if((ay * gx - ax * gy) % (ay * bx - ax * by) != 0 || (by * gx - bx * gy) % (ax * by - ay * bx) != 0)
        return 0;
    
    //Calculate solution
    return (ay * gx - ax * gy) / (ay * bx - ax * by) + 3 * ((by * gx - bx * gy) / (ax * by - ay * bx));
}
