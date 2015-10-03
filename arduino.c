#include "arduino.h"
#include <pthread.h>
#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define len 8
#define SensorsAddr 0x32

char data[len];

void initI2CConnection(){
	bcm2835_init();
	bcm2835_i2c_begin();
}

uint8_t * getSensorData() {
	bcm2835_i2c_setSlaveAddress(SensorsAddr);
	bcm2835_i2c_read(data, len);
	return data;
}

void *sensorDataUpdateBegin(){
	initI2CConnection();
	
	while(1){
		uint8_t* data = getSensorData();
		for(int i = 0; i < 8; i++)
			fprintf(stderr, "%d  /  ", (int)data[i]);   
		fprintf(stderr, "\n");   
		delay(200);
	}
	pthread_exit(NULL);
}
