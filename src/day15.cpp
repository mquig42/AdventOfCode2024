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
        
        //Make map for part 1
        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] == '#')
                walls.insert(row * 100 + i);
            else if(line[i] == 'O')
                boxes.insert(row * 100 + i);
            else if(line[i] == '@')
                robot = row * 100 + i;
        }

        //Make map for part 2
        line.replace("#", "##");
        line.replace(".", "..");
        line.replace("O", "[]");
        line.replace("@", "@.");
        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] == '#')
                walls2.insert(row * 100 + i);
            else if(line[i] == '[')
                boxes2.insert(row * 100 + i);
            else if(line[i] == '@')
                robot2 = row * 100 + i;
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

    //These are no longer needed. Might as well free some memory.
    walls.clear();
    boxes.clear();

    return sum;
}

uint64_t Day15::solve2()
{
    for(char i : instructions)
    {
        moveRobot2(i);
    }

    uint64_t sum = 0;
    for(uint16_t b : boxes2)
    {
        sum += b;
    }

    return sum;
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

void Day15::moveRobot2(char instr)
{
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
    
    //Positions of any box the robot could push depends on direction
    if(direction == left)
    {
        if(boxes2.count(robot2 + 2 * direction))
        {
            if(canMoveBox2(robot2 + 2 * direction, direction))
            {
                moveBox2(robot2 + 2 * direction, direction);
                robot2 += direction;
            }
        }
        else if(!walls2.count(robot2 + direction))
        {
            robot2 += direction;
        }
    }
    else if(direction == right)
    {
        if(boxes2.count(robot2 + direction))
        {
            if(canMoveBox2(robot2 + direction, direction))
            {
                moveBox2(robot2 + direction, direction);
                robot2 += direction;
            }
        }
        else if(!walls2.count(robot2 + direction))
        {
            robot2 += direction;
        }
    }
    else
    {
        //When moving up or down, there are two places a box could be
        uint16_t box = 0;
        if(boxes2.count(robot2 + direction - 1))
            box = robot2 + direction - 1;
        else if(boxes2.count(robot2 + direction))
            box = robot2 + direction;

        if(box != 0)
        {
            if(canMoveBox2(box, direction))
            {
                moveBox2(box, direction);
                robot2 += direction;
            }
        }
        else if(!walls2.count(robot2 + direction))
        {
            robot2 += direction;
        }
    }
}

//Given a direction and the position of the LEFT side of a box,
//Can the box be moved?
bool Day15::canMoveBox2(uint16_t pos, int8_t direction)
{
    if(direction == left || direction == right)
    {
        //Iterative
        uint16_t space = pos + 2 * direction;
        while(boxes2.count(space))
            space += 2 * direction;
        
        //Boxes are two spaces wide, but we're only moving one.
        //So, if direction is left, we might have skipped over an empty space
        if(direction == left)
            space += 1;
        
        return !walls2.count(space);
    }
    else
    {
        //Check for walls
        if(walls2.count(pos + direction) || walls2.count(pos + direction + 1))
            return false;
        
        //Check for box directly above/below this one
        //If there is, then we only need one recursive call
        if(boxes2.count(pos + direction))
            return canMoveBox2(pos + direction, direction);
        
        //Check for offset boxes. There may be two of them
        bool lBox = true;
        bool rBox = true;
        if(boxes2.count(pos + direction - 1))
            lBox = canMoveBox2(pos + direction - 1, direction);
        if(boxes2.count(pos + direction + 1))
            rBox = canMoveBox2(pos + direction + 1, direction);
        
        return(lBox && rBox);
    }
}

//Move a box, plus any other boxes it pushes
//Use canMoveBox2 first to verify, this does not check
void Day15::moveBox2(uint16_t pos, int8_t direction)
{
    //Move any boxes this one pushes first
    if(direction == left || direction == right)
    {
        //For left and right, there can be only one
        if(boxes2.count(pos + 2 * direction))
        {
            moveBox2(pos + 2 * direction, direction);
        }
    }
    else
    {
        //For up and down, there could be a pushed box in 3 different positions
        if(boxes2.count(pos + direction - 1))
            moveBox2(pos + direction - 1, direction);
        if(boxes2.count(pos + direction))
            moveBox2(pos + direction, direction);
        if(boxes2.count(pos + direction + 1))
            moveBox2(pos + direction + 1, direction);
    }

    //Now move this box
    boxes2.erase(pos);
    boxes2.insert(pos + direction);
}
