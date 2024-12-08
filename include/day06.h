#ifndef DAY06_H
#define DAY06_H
#include <unordered_set>
#include "day.h"
#include "utility.h"

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
        bool loops();
};

#endif //DAY06_H
