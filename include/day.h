#ifndef DAY_H
#define DAY_H
#include <M5Cardputer.h>
#include <SPI.h>
#include <SD.h>

class Day
{
    public:
        int dayNumber = 0;
        virtual ~Day() = default;
        virtual void load(File file) = 0;
        virtual void solveBoth(LovyanGFX* display);
    private:
        virtual uint64_t solve1() = 0;
        virtual uint64_t solve2() = 0;
};

#endif //DAY_H
