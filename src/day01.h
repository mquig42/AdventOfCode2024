#ifndef DAY01_H
#define DAY01_H
#include "day.h"

class Day01 : public Day
{
    public:
        Day01();
        virtual void load(File file);
    private:
        std::vector<long> list1;
	    std::vector<long> list2;
        virtual long solve1();
        virtual long solve2();
};

#endif //DAY01_H