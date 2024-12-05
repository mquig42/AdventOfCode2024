#ifndef DAY05_H
#define DAY05_H
#include <map>
#include "day.h"

class Day05 : public Day
{
    public:
        Day05();
        void load(File file);
    private:
        struct rule
        {
            uint8_t lo;
            uint8_t hi;
        };

        std::vector<rule> rules;
        std::vector<std::map<uint8_t, uint8_t>> pageLists; //key: page number, value: position
        std::vector<uint8_t> middles; //Stores just the middle page number of each page list

        long solve1();
        long solve2();
        bool valid(std::map<uint8_t, uint8_t> pageList);
};

#endif //DAY05_H
