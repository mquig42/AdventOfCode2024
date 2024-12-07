#ifndef DAY06_H
#define DAY06_H
#include <unordered_set>
#include "day.h"

class Day06 : public Day
{
    public:
        Day06();
        void load(File file);
    private:
        struct state
        {
            uint16_t position;
            uint8_t direction;

            bool operator==(state s) const
            {
                return this->position == s.position && this->direction == s.direction;
            }

            size_t operator()(state s) const
            {
                return s.position;
            }
        };

        int8_t directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        uint8_t numRows, numCols;
        uint16_t guardStart;
        std::unordered_set<uint16_t> obstacles;
        std::vector<uint16_t> visitedVec;

        uint64_t solve1();
        uint64_t solve2();
        uint16_t makeCoord(uint8_t row, uint8_t col);
        uint8_t row(uint16_t coord);
        uint8_t col(uint16_t coord);
        bool loops();
};

#endif //DAY06_H
