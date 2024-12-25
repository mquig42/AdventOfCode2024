#ifndef DAY25_H
#define DAY25_H
#include "day.h"

class Day25 : public Day
{
    public:
        Day25();
        void load(File file);
        void solveBoth(LovyanGFX* display);
    private:
        std::vector<std::array<uint8_t, 5>> keys;
        std::vector<std::array<uint8_t, 5>> locks;

        uint64_t solve1();
        uint64_t solve2();
        bool match(std::array<uint8_t, 5> lock, std::array<uint8_t, 5> key);
};

#endif //DAY25_H
