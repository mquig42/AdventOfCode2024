#ifndef DAY09_H
#define DAY09_H
#include "day.h"

class Day09 : public Day
{
    public:
        Day09();
        void load(File file);
    private:
        std::vector<int16_t> disk;
        
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY09_H
