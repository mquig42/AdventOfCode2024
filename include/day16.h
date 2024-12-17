#ifndef DAY16_H
#define DAY16_H
#include <unordered_set>
#include "day.h"
#include "utility.h"

class Day16 : public Day
{
    public:
        Day16();
        void load(File file);
    private:
        std::unordered_set<uint16_t> spaces;
        uint16_t start, end;

        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY16_H
