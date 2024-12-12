#ifndef DAY11_H
#define DAY11_H
#include <cmath>
#include <unordered_map>
#include "day.h"

class Day11 : public Day
{
    public:
        Day11();
        void load(File file);
    private:
        std::unordered_map<uint64_t, uint32_t> counts;

        uint64_t solve1();
        uint64_t solve2();
        void blink();
        void increaseCount(std::unordered_map<uint64_t, uint32_t> &c, uint64_t key, uint32_t value);
};

#endif //DAY11_H
