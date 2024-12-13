#ifndef DAY13_H
#define DAY13_H
#include "day.h"

class Day13 : public Day
{
    public:
        Day13();
        void load(File file);
    private:
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY13_H
