#include "utility.h"

//Simple way of storing two uint8_t as one uint16_t
uint16_t makeCoord(uint8_t row, uint8_t col)
{
    return row * 256 + col;
}

//Given a coord and direction, generate the neighbouring coord in that direction
uint16_t makeNeighbour(uint16_t coord, char direction)
{
    switch(direction)
    {
        case 'U':
            return coord - 256;
        case 'R':
            return coord + 1;
        case 'D':
            return coord + 256;
        case 'L':
            return coord - 1;
    }
    return 0;
}

uint8_t row(uint16_t coord)
{
    return coord / 256;
}

uint8_t col(uint16_t coord)
{
    return coord % 256;
}
