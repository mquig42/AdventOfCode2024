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
    private:
        std::unordered_map<uint16_t, std::unordered_set<uint16_t>> connections;
        std::vector<uint16_t> computers;

        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY23_H
