#ifndef DAY04_H
#define DAY04_H
#include "day.h"

class Day04 : public Day
{
    public:
        Day04();
        void load(File file);
    private:
        std::vector<String> grid;
        long solve1();
        long solve2();
        char getChar(uint8_t row, uint8_t col);
        uint8_t isXmas(uint8_t row, uint8_t col);
        bool isXmas2(uint8_t row, uint8_t col);
};

#endif //DAY04_H
