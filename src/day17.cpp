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
    /*display->printf("Register A: %lld\n", REG_A);
    display->printf("Register B: %lld\n", REG_B);
    display->printf("Register C: %lld\n", REG_C);
    display->printf("\n");
    for(uint8_t i : instructions)
        display->printf("%d,", i);*/

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
    uint64_t testVal = 0;
    uint64_t counter = 0;
    std::vector<uint8_t> output;

    do
    {
        counter++;
        REG_A = testVal;
        ip = 0;
        output = run();
        if(cmpVectors(output, instructions))
        {
            M5Cardputer.Display.printf("%d ", output.size());
            if(output.size() == instructions.size())
                break;
            testVal *= 8;
        }
        else
        {
            testVal++;
        }
    } while (true);
    M5Cardputer.Display.printf("\n%llu attempts\n", counter);
    
    return testVal;
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
