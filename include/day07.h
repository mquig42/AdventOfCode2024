#ifndef DAY07_H
#define DAY07_H
#include "day.h"

class Day07 : public Day
{
    public:
        Day07();
        void load(File file);
    private:
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY07_H
