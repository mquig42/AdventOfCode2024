#ifndef DAY17_H
#define DAY17_H
#include "day.h"

class Day17 : public Day
{
    public:
        Day17();
        void load(File file);
        void solveBoth(LovyanGFX* display);
    private:
        int64_t REG_A, REG_B, REG_C;
        uint8_t ip;
        std::vector<uint8_t> instructions;

        uint64_t solve1();
        uint64_t solve2();
        std::vector<uint8_t> run();
        int64_t getCombo(uint8_t operand);
        bool cmpVectors(std::vector<uint8_t> a, std::vector<uint8_t> b);
        uint64_t recursive2(uint64_t testValue);
};

#endif //DAY17_H
