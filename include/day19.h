#ifndef DAY19_H
#define DAY19_H
#include "day.h"

class Day19 : public Day
{
    public:
        Day19();
        void load(File file);
    private:
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY19_H
