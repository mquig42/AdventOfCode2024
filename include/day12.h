#ifndef DAY12_H
#define DAY12_H
#include <unordered_set>
#include "day.h"
#include "utility.h"

class Day12 : public Day
{
    public:
        Day12();
        void load(File file);
    private:
        std::vector<String> grid;
        uint8_t numRows, numCols;
        std::vector<std::unordered_set<uint16_t>> plots;

        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY12_H
