#ifndef DAY03_H
#define DAY03_H
#include <Regexp.h>
#include "day.h"

class Day03 : public Day
{
    public:
        Day03();
        void load(File file);
    private:
        char puzzleInput[32768]; //32kB
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY03_H
