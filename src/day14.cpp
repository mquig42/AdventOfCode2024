#include "day14.h"

Day14::Day14()
{
    dayNumber = 14;
}

void Day14::load(File file)
{
    int8_t px, py, vx, vy;

    while(file.available())
    {
        px = file.parseInt();
        py = file.parseInt();
        vx = file.parseInt();
        vy = file.parseInt();
        input.push_back({px, py, vx, vy});
    }
    input.pop_back();

    //Example and full input use different-sized rooms
    //Automatically detect based on number of robots
    if(input.size() < 32)
    {
        x_size = 11;
        y_size = 7;
    }
    else
    {
        x_size = 101;
        y_size = 103;
    }

    file.close();
}

uint64_t Day14::solve1()
{
    int quadrantCounts[5] = {0};
    for(robot r : input)
    {
        quadrantCounts[quadrant(r, 100)]++;
    }

    uint64_t safetyFactor = 1;
    for(int i = 0; i < 4; i++)
    {
        safetyFactor *= quadrantCounts[i];
    }

    return safetyFactor;
}

uint64_t Day14::solve2()
{
    M5Cardputer.Display.printf("Part 2: ");
    int32_t cursorX = M5Cardputer.Display.getCursorX();
    int32_t cursorY = M5Cardputer.Display.getCursorY();
    
    uint32_t t = 0;
    while(t < 7051) //Calculated manually
    {
        //Clear the portions of the screen that will be updated
        M5Cardputer.Display.setColor(BLACK);
        M5Cardputer.Display.setTextColor(BLACK);
        M5Cardputer.Display.setCursor(cursorX, cursorY);
        M5Cardputer.Display.printf("%d", t);
        M5Cardputer.Display.fillRect(138, 31, 102, 104);

        //Print number
        M5Cardputer.Display.setColor(GREEN);
        M5Cardputer.Display.setTextColor(GREEN);
        t++;
        M5Cardputer.Display.setCursor(cursorX, cursorY);
        M5Cardputer.Display.printf("%d", t);

        //Display robot positions
        for(int i = 0; i < input.size(); i++)
        {
            updatePosition(input[i]);
        }
    }

    //Reset cursor position
    M5Cardputer.Display.setCursor(0, cursorY);
    return t;
}

//returns the quadrant (0-3) the robot will be in after seconds
//Using mod like this doesn't work for negative numbers, which most of the robots have
//Find a way to fix that.
uint8_t Day14::quadrant(robot r, uint16_t seconds)
{
    int16_t x = (r.px + seconds * r.vx) % x_size;
    int16_t y = (r.py + seconds * r.vy) % y_size;
    uint8_t x_mid = x_size / 2;
    uint8_t y_mid = y_size / 2;

    if(x < 0)
        x += x_size;
    if(y < 0)
        y += y_size;

    if(x < x_mid && y < y_mid)
        return 0;
    else if(x > x_mid && y < y_mid)
        return 1;
    else if(x < x_mid && y > y_mid)
        return 2;
    else if(x > x_mid && y > y_mid)
        return 3;
    else
        return 4;
}

//Advance the robot's position by one second and draw it on the screen
void Day14::updatePosition(robot &r)
{
    int16_t x = (r.px + r.vx) % x_size;
    int16_t y = (r.py + r.vy) % y_size;
    if(x < 0)
        x += x_size;
    if(y < 0)
        y += y_size;
    
    r.px = x;
    r.py = y;

    M5Cardputer.Display.drawPixel(x + 138, y + 31);
}
