#ifndef DAY23_H
#define DAY23_H
#include "day.h"

class Day23 : public Day
{
    public:
        Day23();
        void load(File file);
    private:
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY23_H
