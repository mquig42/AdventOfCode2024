#ifndef DAY17_H
#define DAY17_H
#include "day.h"

class Day17 : public Day
{
    public:
        Day17();
        void load(File file);
    private:
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY17_H
