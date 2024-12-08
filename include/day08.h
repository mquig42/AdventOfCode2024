#ifndef DAY08_H
#define DAY08_H
#include <unordered_map>
#include "day.h"
#include "utility.h"

class Day08 : public Day
{
    public:
        Day08();
        void load(File file);
    private:
        std::unordered_map<char, std::vector<uint16_t>> antennas;
        uint8_t numRows, numCols;
        
        uint64_t solve1();
        uint64_t solve2();
};

#endif //DAY08_H
