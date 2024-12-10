#ifndef DAY09_H
#define DAY09_H
#include "day.h"

class Day09 : public Day
{
    public:
        Day09();
        void load(File file);
    private:
        uint16_t numFiles = 0;
        std::vector<uint8_t> input;

        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY09_H
