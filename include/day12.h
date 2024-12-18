#ifndef DAY12_H
#define DAY12_H
#include <unordered_set>
#include <queue>
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
        uint64_t cost1(std::unordered_set<uint16_t> plot);
        char getCrop(uint8_t row, uint8_t col);
        char getCrop(uint16_t coord);
        std::unordered_set<uint16_t> collectPlot(uint8_t r, uint8_t c);
        uint8_t countNeighbours(uint16_t point, std::unordered_set<uint16_t> plot);
};

#endif //DAY12_H
