#ifndef SPI_H
#define SPI_H

#include <stdint.h>

void Eteint_Led();

void SPI_MasterInit(void);

void SPI_MasterTransmit(char cData);

void envoie_Led(uint8_t data1, uint8_t data2);

void printLetter(char letter[]);

#endif //SPI_H