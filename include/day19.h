#ifndef DAY19_H
#define DAY19_H
#include <unordered_map>
#include "day.h"

class Day19 : public Day
{
    public:
        Day19();
        void load(File file);
    private:
        std::vector<String> towels;
        std::vector<String> patterns;
        std::unordered_map<uint8_t, bool> memo;
        
        uint64_t solve1();
        uint64_t solve2();
        bool subStrCmp(String str, String sub, uint8_t startIdx);
        bool match1(String pattern, uint8_t startIdx);
};

#endif //DAY19_H
