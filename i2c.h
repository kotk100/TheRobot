/* 
 * File:   i2c.h
 * Author: Ziga
 *
 * Created on 15. avgust 2015, 9:13
 */

#ifndef I2C_H
#define	I2C_H

#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void initI2CConnection();
uint8_t * getSensorData();

#endif
