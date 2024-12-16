#include "day15.h"

Day15::Day15()
{
    dayNumber = 15;
}

void Day15::load(File file)
{
    String line;
    int row = 0;

    //Read map. Break on the empty line between the map and the instructions
    while(file.available())
    {
        line = file.readStringUntil('\n');
        if(line.length() == 1)
            break;
        
        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] == '#')
                walls.insert(row * 100 + i);
            else if(line[i] == 'O')
                boxes.insert(row * 100 + i);
            else if(line[i] == '@')
                robot = row * 100 + i;
        }
        row++;
    }

    instructions = file.readString();
    instructions.replace("\r\n", "");
    file.close();
}

uint64_t Day15::solve1()
{
    for(char i : instructions)
    {
        moveRobot(i);
    }

    uint64_t sum = 0;
    for(uint16_t b : boxes)
    {
        sum += b;
    }

    return sum;
}

uint64_t Day15::solve2()
{
    return 0;
}

void Day15::moveRobot(char instr)
{
    //target position will be given by robot + direction
    int8_t direction;
    if(instr == '^')
        direction = up;
    else if(instr == '>')
        direction = right;
    else if(instr == 'v')
        direction = down;
    else if(instr == '<')
        direction = left;
    else
        return;
    
    //Target position could be:
    //1. Wall
    //2. Empty space
    //3a. box or boxes with empty space after
    //3b. box or boxes with wall after
    if(boxes.count(robot + direction))
    {
        //Move boxes
        //Find the first space in direction that isn't a box
        //If it isn't a wall, move the robot and the box in front of it
        uint16_t space = robot + direction;
        while(boxes.count(space))
            space += direction;
        
        if(!walls.count(space))
        {
            boxes.erase(robot + direction);
            boxes.insert(space);
            robot += direction;
        }
    }
    else if(!walls.count(robot + direction))
    {
        //Empty space. Just move
        robot += direction;
    }
}
