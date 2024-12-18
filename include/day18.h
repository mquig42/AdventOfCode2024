#ifndef DAY18_H
#define DAY18_H
#include <unordered_set>
#include <queue>
#include "day.h"
#include "utility.h"

class Day18 : public Day
{
    public:
        Day18();
        void load(File file);
    private:
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY18_H
