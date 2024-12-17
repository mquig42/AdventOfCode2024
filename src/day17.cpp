#include "day17.h"

Day17::Day17()
{
    dayNumber = 17;
}

void Day17::load(File file)
{
    REG_A = file.parseInt();
    REG_B = file.parseInt();
    REG_C = file.parseInt();
    while(file.available())
    {
        instructions.push_back(file.parseInt());
    }
    instructions.pop_back();

    file.close();
}

//Override solveBoth because, for the first time this year, the puzzle answer is not an integer
void Day17::solveBoth(LovyanGFX *display)
{
    display->setTextColor(GREEN);
    display->setTextFont(2);

    display->printf("Advent of Code 2024 Day %d\n", dayNumber);

    solve1();
    display->printf("Part 2: %llu\n", solve2());
}

uint64_t Day17::solve1()
{
    ip = 0;

    M5Cardputer.Display.printf("Part 1: ");
    std::vector<uint8_t> output = run();

    M5Cardputer.Display.printf("%d", output[0]);
    for(int i = 1; i < output.size(); i++)
    {
        M5Cardputer.Display.printf(",%d", output[i]);
    }
    M5Cardputer.Display.printf("\n");
    return 0;
}

uint64_t Day17::solve2()
{
    return recursive2(0);
}

std::vector<uint8_t> Day17::run()
{
    uint8_t instr;
    uint8_t operand;
    std::vector<uint8_t> output;

    while(ip < instructions.size())
    {
        instr = instructions[ip];
        operand = instructions[ip + 1];

        switch(instr)
        {
            case 0: //ADV
                REG_A = REG_A >> getCombo(operand);
                ip += 2;
                break;
            case 1: //BXL
                REG_B = REG_B ^ operand;
                ip += 2;
                break;
            case 2: //BST
                REG_B = getCombo(operand) & 0b0111;
                ip += 2;
                break;
            case 3: //JNZ
                if(REG_A)
                    ip = operand;
                else
                    ip += 2;
                break;
            case 4: //BXC
                REG_B = REG_B ^ REG_C;
                ip += 2;
                break;
            case 5: //OUT
                output.push_back(getCombo(operand) & 0b0111);
                ip += 2;
                break;
            case 6: //BDV
                REG_B = REG_A >> getCombo(operand);
                ip += 2;
                break;
            case 7: //CDV
                REG_C = REG_A >> getCombo(operand);
                ip += 2;
                break;
        }
    }

    return output;
}

//Returns the value of a combo operand
int64_t Day17::getCombo(uint8_t operand)
{
    if(operand == 4)
        return REG_A;
    else if(operand == 5)
        return REG_B;
    else if(operand == 6)
        return REG_C;
    else if(operand == 7)
        M5Cardputer.Display.printf("ERROR 7");

    return operand;
}

//Takes two vectors. a.size <= b.size
//Returns true if all n elements in a match the last n elements of b
bool Day17::cmpVectors(std::vector<uint8_t> a, std::vector<uint8_t> b)
{
    int offset = b.size() - a.size();
    for(int i = 0; i < a.size(); i++)
    {
        if(a[i] != b[i + offset])
            return false;
    }

    return true;
}

//My iterative solution took a long time by getting caught in false sets
//This approach is much faster
//Explanation of approach:
//If the initial value of REG_A is expressed in octal, each digit of it generates one digit of output
//In reverse order, because we only read the lowest 3 bits on each pass through the program
//Try all 8 digits starting with 0. If we find one that generates the correct last digit of output,
//keep that digit for now (multiply by 8), and try all 8 possibilities for the second digit,
//and so on until we have all of them.
//If we have tried all 8 possibilities and not found a match, then one or more of the earlier digits we found must be wrong
//Step back and try different possibilities for them.
uint64_t Day17::recursive2(uint64_t testValue)
{
    std::vector<uint8_t> output;
    uint64_t r;
    for(int i = 0; i < 8; i++)
    {
        REG_A = testValue + i;
        ip = 0;
        output = run();
        if(cmpVectors(output, instructions))
        {
            if(output.size() == instructions.size())
                return testValue + i;
            else
            {
                r = recursive2((testValue + i) * 8);
                if(r)
                    return r;
            }
        }
    }

    return 0;
}
