#ifndef I2C_H_
#define I2C_H_
#include <inttypes.h>

#define BUFFER_SIZE 0x01  //1 byte buffer

void I2C(int, int);
void I2CClose();
uint8_t dataBuffer[BUFFER_SIZE];
uint8_t read_byte(uint8_t);
uint8_t write_byte(uint8_t, uint8_t);



#endif /* I2C_H_ */
