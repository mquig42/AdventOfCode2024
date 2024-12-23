#ifndef DAY22_H
#define DAY22_H
#include "day.h"

class Day22 : public Day
{
    public:
        Day22();
        void load(File file);
    private:
        std::vector<uint32_t> secrets;
        std::vector<std::vector<int8_t>> prices;

        uint64_t solve1();
        uint64_t solve2();
        uint32_t nextSecret(uint32_t secret);
        uint8_t buyerPrice(std::vector<int8_t> buyer, int8_t a, int8_t b, int8_t c, int8_t d);
};

#endif //DAY22_H
