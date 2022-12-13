#ifndef SPI_H
#define SPI_H

void SPI_MasterInit(void);

void SPI_MasterTransmit(char cData);

void Eteint_Led();

void envoie_Led(uint8_t data1, uint8_t data2);



#endif //SPI_H