#ifndef DAY13_H
#define DAY13_H
#include "day.h"

class Day13 : public Day
{
    public:
        Day13();
        void load(File file);
    private:
        struct clawMachine
        {
            uint8_t ax;
            uint8_t ay;
            uint8_t bx;
            uint8_t by;
            uint16_t goalx;
            uint16_t goaly;
        };
        std::vector<clawMachine> input;

        uint64_t solve1();
        uint64_t solve2();
        uint16_t solveMachine(clawMachine machine);
};

#endif //DAY13_H
