#ifndef DAY23_H
#define DAY23_H
#include "day.h"
#include "utility.h"
#include <unordered_map>
#include <unordered_set>

class Day23 : public Day
{
    public:
        Day23();
        void load(File file);
        void solveBoth(LovyanGFX* display);
    private:
        std::unordered_map<uint16_t, std::unordered_set<uint16_t>> connections;
        std::unordered_set<uint16_t> biggestGroup;

        uint64_t solve1();
        uint64_t solve2();
        void bronKerbosch(std::unordered_set<uint16_t> &R, std::unordered_set<uint16_t> &P, std::unordered_set<uint16_t> &X);
};

#endif //DAY23_H
