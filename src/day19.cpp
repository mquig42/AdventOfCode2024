#include "day19.h"

Day19::Day19()
{
    dayNumber = 19;
}

void Day19::load(File file)
{
    //First challenge: We need something like String.split() to separate all those towels
    String firstLine = file.readStringUntil('\n');
    int nextComma;
    int i = 0;
    while(i < firstLine.lastIndexOf(','))
    {
        nextComma = firstLine.indexOf(',', i);
        towels.push_back(firstLine.substring(i, nextComma));
        i = nextComma + 2;
    }
    towels.push_back(firstLine.substring(i, firstLine.indexOf('\r')));

    //empty line between towels and patterns
    file.readStringUntil('\n');

    while(file.available())
    {
        //Read only the pattern, not the newline chars
        patterns.push_back(file.readStringUntil('\r'));
        file.readStringUntil('\n');
    }

    file.close();
}

uint64_t Day19::solve1()
{
    uint32_t sum = 0;
    for(String p : patterns)
    {
        memo.clear();
        if(match1(p, 0))
        {
            sum++;
        }
    }

    return sum;
}

uint64_t Day19::solve2()
{
    return 0;
}

bool Day19::subStrCmp(String str, String sub, uint8_t startIdx)
{
    for(uint8_t i = 0; i < sub.length(); i++)
    {
        if(i + startIdx >= str.length() || str[i + startIdx] != sub[i])
            return false;
    }
    return true;
}

bool Day19::match1(String pattern, uint8_t startIdx)
{
    if(memo.count(startIdx))
        return memo[startIdx];
    
    if(startIdx >= pattern.length())
    {
        memo[startIdx] = true;
        return true;
    }
    
    bool m;
    for(String t : towels)
    {
        if(subStrCmp(pattern, t, startIdx))
        {
            m = match1(pattern, startIdx + t.length());
            if(m)
            {
                memo[startIdx] = true;
                return true;
            }
        }
    }

    memo[startIdx] = false;
    return false;
}
