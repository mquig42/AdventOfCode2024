#ifndef DAY07_H
#define DAY07_H
#include <forward_list>
#include "day.h"

class Day07 : public Day
{
    public:
        Day07();
        void load(File file);
    private:
        struct equation
        {
            uint64_t value;
            std::forward_list<uint16_t> operands;
        };

        std::vector<equation> equations;

        uint64_t solve1();
        uint64_t solve2();
        Day07::equation parseLine(String line);
        uint64_t calibrate1(equation eq);
        uint8_t listSize(std::forward_list<uint16_t> lst);
        bool calibrate2(uint64_t goal, uint64_t acc, std::forward_list<uint16_t>::iterator begin, std::forward_list<uint16_t>::iterator end);
        uint64_t concat(uint64_t a, uint16_t b);
};

#endif //DAY07_H
