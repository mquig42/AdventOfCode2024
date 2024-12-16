#ifndef DAY15_H
#define DAY15_H
#include <unordered_set>
#include "day.h"

class Day15 : public Day
{
    public:
        Day15();
        void load(File file);
    private:
        std::unordered_set<uint16_t> walls;
        std::unordered_set<uint16_t> boxes;
        uint16_t robot;
        String instructions;
        int8_t up = -100;
        int8_t right = 1;
        int8_t down = 100;
        int8_t left = -1;

        uint64_t solve1();
        uint64_t solve2();
        void moveRobot(char instr);
};

#endif //DAY15_H
