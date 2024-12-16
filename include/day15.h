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

        std::unordered_set<uint16_t> walls2;
        std::unordered_set<uint16_t> boxes2; //Stores only the left side of each box
        uint16_t robot2;

        String instructions;
        int8_t up = -100;
        int8_t right = 1;
        int8_t down = 100;
        int8_t left = -1;

        uint64_t solve1();
        uint64_t solve2();
        void moveRobot(char instr);
        void moveRobot2(char instr);
        bool canMoveBox2(uint16_t pos, int8_t direction);
        void moveBox2(uint16_t pos, int8_t direction);
};

#endif //DAY15_H
