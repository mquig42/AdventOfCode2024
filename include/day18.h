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
        virtual void solveBoth(LovyanGFX* display);
    private:
        struct queueNode
        {
            uint16_t location;
            uint32_t steps;
        };

        std::unordered_set<uint16_t> corrupted;
        std::vector<uint16_t> bytes;
        uint8_t maxDim = 70; //The space is square, so this is maxRow and maxCol
        uint16_t toDrop = 1024;

        uint64_t solve1();
        uint64_t solve2();
        uint32_t findPath();
};

#endif //DAY18_H
