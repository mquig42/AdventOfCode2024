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
    char oper[4]; //Enough space for a 3 digit number plus null terminator
    int idx, op1, op2, mulIdx, dontIdx;
    long sum = 0;
    bool enabled = true;

    MatchState ms(puzzleInput);

    idx = 0;
    mulIdx = 0;
    dontIdx = 0;
    while(true)
    {
        if(!enabled)
        {
            //If not enabled, search for a do() instruction.
            //If one is found, re-enable and set index to just after it
            //If not, then there are no relevant instructions remaining, so break.
            if(ms.Match("do%(%)", idx) == 0)
                break;
            enabled = true;
            idx = ms.MatchStart + ms.MatchLength;
        }
        else
        {
            if(ms.Match("don't%(%)", idx) == 1)
                dontIdx = ms.MatchStart + ms.MatchLength;
            if(ms.Match("mul%((%d+),(%d+)%)", idx) == 0)
                break;
            
            mulIdx = ms.MatchStart + ms.MatchLength;
            if(dontIdx > idx && dontIdx < mulIdx)
            {
                //We have encountered a don't() instruction before the next mul()
                enabled = false;
                idx = dontIdx;
            }
            else
            {
                //Currently enabled. Same logic as part 1
                op1 = atoi(ms.GetCapture(oper, 0));
                op2 = atoi(ms.GetCapture(oper, 1));
                sum += op1 * op2;
                idx = mulIdx;
            }
        }
    }

    return sum;
}
