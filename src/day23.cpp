#include "day23.h"

Day23::Day23()
{
    dayNumber = 23;
}

void Day23::load(File file)
{
    //Going to store the computers as coords to avoid using too many Strings
    String line;
    uint16_t a, b;
    bool containsA, containsB;

    while(file.available())
    {
        line = file.readStringUntil('\n');
        a = makeCoord(line[0], line[1]);
        b = makeCoord(line[3], line[4]);

        connections[a].insert(b);
        connections[b].insert(a);

        containsA = false;
        containsB = false;
        for(uint16_t c : computers)
        {
            if(c == a)
                containsA = true;
            if(c == b)
                containsB = true;
        }

        if(!containsA)
            computers.push_back(a);
        if(!containsB)
            computers.push_back(b);
    }
    file.close();
}

//What a mess, but at least it works
//slow though. Maybe find a different way to iterate through all the computers that only considers connected ones?
uint64_t Day23::solve1()
{
    uint64_t count = 0;
    for(uint16_t i = 0; i + 2 < computers.size(); i++)
    {
        for(uint16_t j = i + 1; j + 1 < computers.size(); j++)
        {
            for(uint16_t k = j + 1; k < computers.size(); k++)
            {
                if(row(computers[i]) == 't' || row(computers[j]) == 't' || row(computers[k]) == 't')
                {
                    if(connections[computers[i]].count(computers[j]) &&
                       connections[computers[i]].count(computers[k]) &&
                       connections[computers[j]].count(computers[k]))
                    {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

uint64_t Day23::solve2()
{
    return 0;
}
