#ifndef DAY_H
#define DAY_H
#include <M5Cardputer.h>
#include <SPI.h>
#include <SD.h>

class Day
{
    public:
        int dayNumber = 0;
        virtual void load(File file) = 0;
        virtual void solveBoth(LovyanGFX* display);
    private:
        virtual long solve1() = 0;
        virtual long solve2() = 0;
};

#endif //DAY_H
