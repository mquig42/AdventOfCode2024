#include "day03.h"

Day03::Day03()
{
    dayNumber = 3;
}

void Day03::load(File file)
{
    file.readString().toCharArray(puzzleInput, 32768);
    file.close();
}

long Day03::solve1()
{
    char oper[4]; //Enough space for a 3 digit number plus null terminator
    int idx, op1, op2;
    long sum = 0;

    MatchState ms(puzzleInput);

    idx = 0;
    while(true)
    {
        if(ms.Match("mul%((%d+),(%d+)%)", idx) == 0)
            break;
        op1 = atoi(ms.GetCapture(oper, 0));
        op2 = atoi(ms.GetCapture(oper, 1));
        sum += op1 * op2;
        idx = ms.MatchStart + ms.MatchLength;
    }

    return sum;
}

long Day03::solve2()
{
    return 0;
}
