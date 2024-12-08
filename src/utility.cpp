#include "utility.h"

//Simple way of storing two uint8_t as one uint16_t
uint16_t makeCoord(uint8_t row, uint8_t col)
{
    return row * 256 + col;
}

uint8_t row(uint16_t coord)
{
    return coord / 256;
}

uint8_t col(uint16_t coord)
{
    return coord % 256;
}
