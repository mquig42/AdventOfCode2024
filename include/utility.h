//Some functions that are useful for more than one different puzzle
#ifndef UTILITY_H
#define UTILITY_H
#include <M5Cardputer.h>

uint16_t makeCoord(uint8_t row, uint8_t col);
uint16_t makeNeighbour(uint16_t coord, char direction);
uint8_t row(uint16_t coord);
uint8_t col(uint16_t coord);

#endif //UTILITY_H
