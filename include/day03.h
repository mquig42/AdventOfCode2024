#ifndef DAY03_H
#define DAY03_H
#include "day.h"

class Day03 : public Day
{
    public:
        Day03();
        void load(File file);
    private:
        long solve1();
        long solve2();
};

#endif //DAY03_H
