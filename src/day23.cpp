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

    while(file.available())
    {
        line = file.readStringUntil('\n');
        a = makeCoord(line[0], line[1]);
        b = makeCoord(line[3], line[4]);

        connections[a].insert(b);
        connections[b].insert(a);
    }
    file.close();
}

//solve2() does its own printing, since the answer is not an integer.
void Day23::solveBoth(LovyanGFX* display)
{
    display->setTextColor(GREEN);
    display->setTextFont(2);

    display->printf("Advent of Code 2024 Day %d\n", dayNumber);
    display->printf("Part 1: %llu\n", solve1());
    solve2();
}

//What a mess, but at least it works
//slow though. Maybe find a different way to iterate through all the computers that only considers connected ones?
uint64_t Day23::solve1()
{
    std::vector<uint16_t> computers;
    for(auto i : connections)
        computers.push_back(i.first);

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
    std::unordered_set<uint16_t> R;
    std::unordered_set<uint16_t> P;
    std::unordered_set<uint16_t> X;

    for(auto i : connections)
        P.insert(i.first);
    
    bronKerbosch(R, P, X);

    std::vector<uint16_t> lanComputers;
    for(uint16_t i : biggestGroup)
        lanComputers.push_back(i);
    
    std::sort(lanComputers.begin(), lanComputers.end());

    M5Cardputer.Display.printf("Part 2: ");
    for(uint16_t i : lanComputers)
        M5Cardputer.Display.printf("%c%c ", row(i), col(i));
    M5Cardputer.Display.printf("\n");

    return 0;
}

void Day23::bronKerbosch(std::unordered_set<uint16_t> &R, std::unordered_set<uint16_t> &P, std::unordered_set<uint16_t> &X)
{
    if(P.empty() && X.empty())
    {
        if(biggestGroup.size() < R.size())
            biggestGroup = R;
    }
    while(!P.empty())
    {
        uint16_t v = *P.begin();
        std::unordered_set<uint16_t> newR = R;
        newR.insert(v);
        std::unordered_set<uint16_t> newP;
        for(uint16_t i : connections[v])
        {
            if(P.count(i))
                newP.insert(i);
        }
        std::unordered_set<uint16_t> newX;
        for(uint16_t i : connections[v])
        {
            if(X.count(i))
                newX.insert(i);
        }
        bronKerbosch(newR, newP, newX);
        P.erase(v);
        X.insert(v);
    }
}
