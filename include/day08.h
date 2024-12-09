#ifndef DAY08_H
#define DAY08_H
#include <unordered_map>
#include <unordered_set>
#include "day.h"
#include "utility.h"

class Day08 : public Day
{
    public:
        Day08();
        void load(File file);
    private:
        std::unordered_map<char, std::vector<uint16_t>> antennas;
        std::unordered_set<uint16_t> antinodes;
        uint8_t numRows, numCols;
        
        uint64_t solve1();
        uint64_t solve2();
        uint8_t findAntinodes(uint16_t a1, uint16_t a2, uint8_t multiplier);
        void findAntinodes2(uint16_t a1, uint16_t a2);
};

#endif //DAY08_H
