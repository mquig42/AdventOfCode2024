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

        uint64_t solve1();
        uint64_t solve2();
        uint32_t nextSecret(uint32_t secret);
};

#endif //DAY22_H
