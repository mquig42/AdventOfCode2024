#ifndef DAY20_H
#define DAY20_H
#include <unordered_map>
#include "day.h"
#include "utility.h"

class Day20 : public Day
{
    public:
        Day20();
        void load(File file);
    private:
        //Key is coordinate position, value is distance from start
        std::unordered_map<uint16_t, uint16_t> racetrack;
        uint16_t start, end;

        //Used only for testing with sample data
        std::unordered_map<uint8_t, uint8_t> cheatCounts;
        
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY20_H
