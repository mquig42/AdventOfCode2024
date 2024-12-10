#ifndef DAY10_H
#define DAY10_H
#include <set>
#include "day.h"
#include "utility.h"

class Day10 : public Day
{
    public:
        Day10();
        void load(File file);
    private:
        std::vector<String> heightmap;
        int numRows, numCols;

        uint64_t solve1();
        uint64_t solve2();
        uint16_t score(uint8_t row, uint8_t col);
        std::set<uint16_t> nines(uint8_t row, uint8_t col);
};

#endif //DAY10_H
