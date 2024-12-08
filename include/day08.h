#ifndef DAY08_H
#define DAY08_H
#include "day.h"

class Day08 : public Day
{
    public:
        Day08();
        void load(File file);
    private:
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY08_H
