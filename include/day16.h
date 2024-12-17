#ifndef DAY16_H
#define DAY16_H
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "day.h"
#include "utility.h"

class Day16 : public Day
{
    public:
        Day16();
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

        struct queueNode
        {
            uint16_t position;
            uint8_t direction;
            uint32_t score;
            std::unordered_set<uint16_t> path;
            bool operator<(const queueNode &b) const
            {
                return score > b.score; //Easiest way to make queue give minimum value instead of maximum
            }
        };

        uint8_t up = 0;
        uint8_t right = 1;
        uint8_t down = 2;
        uint8_t left = 3;

        std::unordered_set<uint16_t> spaces;
        std::unordered_set<uint16_t> allPaths;
        uint64_t bestScore = UINT64_MAX;
        uint16_t start, end;

        uint64_t solve1();
        uint64_t solve2();
        void runDijkstra();
};

#endif //DAY16_H
