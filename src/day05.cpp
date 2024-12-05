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
        pageList[page] = pos;
        pageLists.push_back(std::map<uint8_t, uint8_t>(pageList));
        pageList.clear();
        //Since every page number is two digits, can use substring to get the middle one
        middles.push_back(line.substring(line.length() / 2 - 1, line.length() / 2 + 1).toInt());
    }

    file.close();
}

long Day05::solve1()
{
    long sum = 0;
    for(int i = 0; i < pageLists.size(); i++)
    {
        if(valid(pageLists[i]))
            sum += middles[i];
    }
    return sum;
}

long Day05::solve2()
{
    return 0;
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
