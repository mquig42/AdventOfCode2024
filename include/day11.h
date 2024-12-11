#ifndef DAY11_H
#define DAY11_H
#include <cmath>
#include "day.h"

class Day11 : public Day
{
    public:
        Day11();
        void load(File file);
    private:
        std::vector<uint32_t> input;

        uint64_t solve1();
        uint64_t solve2();
        uint64_t blink(uint64_t n, uint8_t numBlinks);
};

#endif //DAY11_H
