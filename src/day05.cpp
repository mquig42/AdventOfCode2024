#include "day05.h"

Day05::Day05()
{
    dayNumber = 5;
}

void Day05::load(File file)
{
    String line;
    uint8_t lo, hi, page, pos;
    std::map<uint8_t, uint8_t> pageList;

    //Read rules, break on empty line
    while(file.available())
    {
        line = file.readStringUntil('\n');
        if(line.length() == 1)
            break;
        
        lo = line.substring(0, 2).toInt();
        hi = line.substring(3, 5).toInt();
        rules.push_back({lo, hi});
    }

    //Read page lists
    while(file.available())
    {
        page = 0;
        pos = 0;
        line = file.readStringUntil('\n');
        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] >= '0' && line[i] <= '9')
                page = page * 10 + line[i] - '0';
            else
            {
                pageList[page] = pos;
                page = 0;
                pos++;
            }
        }
        pageLists.push_back(std::map<uint8_t, uint8_t>(pageList));
        pageList.clear();
    }

    file.close();
}

uint64_t Day05::solve1()
{
    long sum = 0;

    for(int i = 0; i < pageLists.size(); i++)
    {
        if(valid(pageLists[i]))
            sum += middle(pageLists[i]);
    }

    return sum;
}

uint64_t Day05::solve2()
{
    long sum = 0;

    for(int i = 0; i < pageLists.size(); i++)
    {
        if(!valid(pageLists[i]))
            sum += fix(pageLists[i]);
    }

    return sum;
}

//Validates a page list
bool Day05::valid(std::map<uint8_t, uint8_t> pageList)
{
    for(rule r : rules)
    {
        if(pageList.count(r.lo) && pageList.count(r.hi) && pageList[r.lo] > pageList[r.hi])
            return false;
    }

    return true;
}

//Return the middle page after correctly reordering the list
uint8_t Day05::fix(std::map<uint8_t, uint8_t> pageList)
{
    bool swapped;
    uint8_t tmp;

    //Sorting algorithm: swap any pair of pages that breaks a rule until no rules are broken
    do
    {
        swapped = false;
        for(rule r : rules)
        {
            if(pageList.count(r.lo) && pageList.count(r.hi) && pageList[r.lo] > pageList[r.hi])
            {
                swapped = true;
                tmp = pageList[r.lo];
                pageList[r.lo] = pageList[r.hi];
                pageList[r.hi] = tmp;
            }
        }
    } while (swapped);
    
    return middle(pageList);
}

//Returns the middle page of a list
uint8_t Day05::middle(std::map<uint8_t, uint8_t> pageList)
{
    uint8_t middlePos = pageList.size() / 2;

    for(auto page : pageList)
    {
        if(page.second == middlePos)
            return page.first;
    }

    return -1;
}
