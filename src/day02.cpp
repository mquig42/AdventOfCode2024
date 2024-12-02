#include "day02.h"

Day02::Day02()
{
    dayNumber = 2;
}

void Day02::load(File file)
{
    String line;
    while(file.available())
    {
        reports.push_back(parseLine(file.readStringUntil('\n')));
    }
}

long Day02::solve1()
{
    long safeCount = 0;

    for(int i = 0; i < reports.size(); i++)
    {
        if(isSafe(reports[i]))
            safeCount++;
    }

    return safeCount;
}

long Day02::solve2()
{
    long safeCount = 0;

    for(int i = 0; i < reports.size(); i++)
    {
        if(isSafe2(reports[i]))
            safeCount++;
    }

    return safeCount;
}

std::vector<int> Day02::parseLine(String line)
{
    std::vector<int> r;
    int n = 0;

    for(int i = 0; i < line.length(); i++)
    {
        if(line[i] >= '0' && line[i] <= '9')
        {
            n = n * 10 + line[i] - '0';
        }
        else if(line[i] == ' ')
        {
            r.push_back(n);
            n = 0;
        }
    }

    r.push_back(n);

    return r;
}

bool Day02::isSafe(std::vector<int> report)
{
    if(report.size() < 2)
        return false;
    
    bool ascending = report[1] > report[0];

    for(int i = 1; i < report.size(); i++)
    {
        if(ascending && (report[i] - report[i - 1] < 1 || report[i] - report[i - 1] > 3))
            return false;
        if(!ascending && (report[i - 1] - report[i] < 1 || report[i - 1] - report[i] > 3))
            return false;
    }

    return true;
}

bool Day02::isSafe2(std::vector<int> report)
{
    if(report.size() < 2)
        return false;
    
    if(isSafe(report))
        return true;
    
    //Simple brute force approach. Make a bunch of copies, each with a different element removed, and test all of them
    for(int i = 0; i < report.size(); i++)
    {
        std::vector<int> reportCopy;
        for(int j = 0; j < report.size(); j++)
        {
            if(j != i)
                reportCopy.push_back(report[j]);
        }
        if(isSafe(reportCopy))
            return true;
    }

    return false;
}
