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
        std::vector<int8_t> priceList;
        for(int i=0; i<2000; i++)
        {
            priceList.push_back(s % 10);
            s = nextSecret(s);
        }
        priceList.push_back(s % 10);
        //Only store this for sample input
        //We don't have enough memory for the full input
        if(secrets.size() < 8)
            prices.push_back(priceList);
        sum += s;
    }

    return sum;
}

//Total brute-force method, though I did optimize it by storing the price lists
//instead of recalculating them for every sequence. This means it uses too much memory
//for the full input, so I disabled that. On the Cardputer, it can (slowly) solve the sample.
//Even on a desktop, solving the full input takes several minutes.
uint64_t Day22::solve2()
{
    uint64_t best_price = 0;
    uint64_t seq_price;
    for (int8_t a = -9; a <= 9; a++)
    {
        for (int8_t b = -0; b <= 9; b++)
        {
            for (int8_t c = -9; c <= 9; c++)
            {
                for (int8_t d = -9; d <= 9; d++)
                {
                    seq_price = 0;
                    for (int i = 0; i < prices.size(); i++)
                    {
                        seq_price += buyerPrice(prices[i], a, b, c, d);
                    }

                    if (seq_price > best_price)
                        best_price = seq_price;
                }
            }
        }
    }

    return best_price;
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

uint8_t Day22::buyerPrice(std::vector<int8_t> buyer, int8_t a, int8_t b, int8_t c, int8_t d)
{
    for (uint16_t i = 1; i + 3 < buyer.size(); i++)
    {
        if (buyer[i] - buyer[i - 1] == a)
            if (buyer[i + 1] - buyer[i] == b)
                if (buyer[i + 2] - buyer[i + 1] == c)
                    if (buyer[i + 3] - buyer[i + 2] == d)
                        return buyer[i + 3];
    }
    return 0;
}
