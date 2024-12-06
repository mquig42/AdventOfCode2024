#ifndef DAY06_H
#define DAY06_H
#include <unordered_set>
#include "day.h"

class Day06 : public Day
{
    public:
        Day06();
        void load(File file);
    private:
        uint8_t numRows, numCols;
        uint16_t guardStart;
        std::unordered_set<uint16_t> visited;
        std::unordered_set<uint16_t> obstacles;

        long solve1();
        long solve2();
        uint16_t makeCoord(uint8_t row, uint8_t col);
        uint8_t row(uint16_t coord);
        uint8_t col(uint16_t coord);
};

#endif //DAY06_H
