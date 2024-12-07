#ifndef DAY07_H
#define DAY07_H
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
            std::vector<uint16_t> operands;
        };

        std::vector<equation> equations;

        uint64_t solve1();
        uint64_t solve2();
        Day07::equation parseLine(String line);
        uint64_t calibrate1(equation eq);
};

#endif //DAY07_H
