#ifndef DAY14_H
#define DAY14_H
#include "day.h"

class Day14 : public Day
{
    public:
        Day14();
        void load(File file);
    private:
        struct robot
        {
            int8_t px;
            int8_t py;
            int8_t vx;
            int8_t vy;
        };
        uint8_t x_size, y_size;
        std::vector<robot> input;

        uint64_t solve1();
        uint64_t solve2();
        uint8_t quadrant(robot r, uint16_t seconds);
};

#endif //DAY14_H
