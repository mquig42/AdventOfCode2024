#include "day22.h"

Day22::Day22()
{
    dayNumber = 22;
}

void Day22::load(File file)
{
    while(file.available())
    {
        secrets.push_back(file.parseInt());
    }
    secrets.pop_back();
    file.close();
}

uint64_t Day22::solve1()
{
    uint64_t sum = 0;
    for(uint32_t s : secrets)
    {
        for(int i=0; i<2000; i++)
        {
            s = nextSecret(s);
        }
        sum += s;
    }

    return sum;
}

uint64_t Day22::solve2()
{
    return 0;
}

uint32_t Day22::nextSecret(uint32_t secret)
{
    //Pruning will ensure that the final answer is 32-bit, but intermediate values might not be
    uint64_t secret64 = secret;

    secret64 = (secret64 ^ (secret64 * 64)) % 16777216;
    secret64 = (secret64 ^ (secret64 / 32)) % 16777216;
    secret64 = (secret64 ^ (secret64 * 2048)) % 16777216;

    return secret64;
}
