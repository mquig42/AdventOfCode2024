#ifndef DAY12_H
#define DAY12_H
#include "day.h"

class Day12 : public Day
{
    public:
        Day12();
        void load(File file);
    private:
        std::vector<String> grid;
        
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY12_H
