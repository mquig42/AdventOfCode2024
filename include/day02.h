#ifndef DAY02_H
#define DAY02_H
#include "day.h"

class Day02 : public Day
{
    public:
        Day02();
        void load(File file);
    private:
        std::vector<std::vector<int>> reports;
        long solve1();
        long solve2();
        std::vector<int> parseLine(String line);
        bool isSafe(std::vector<int> report);
        bool isSafe2(std::vector<int> report);
};

#endif //DAY01_H
