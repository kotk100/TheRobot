
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "arduino.h"
#include "PCA9685.h"



int main(void)
{
	pthread_t sensorData;
	if(pthread_create(&sensorData, NULL, sensorDataUpdateBegin, NULL))
		fprintf(stderr, "ERROR creating sensorData thread");
			
/*
	PCA9685(1, 0x40);
	while(1){
		setPWM(5, 307);
		fprintf(stderr, "%d \n", getPWM(5));
		delay(2000);
		setPWM(5, 409);
		fprintf(stderr, "%d \n", getPWM(5));
		delay(2000);
		setPWM(5, 205);
		fprintf(stderr, "%d \n", getPWM(5));
		delay(2000);
		fprintf(stderr, "en cikel");
	}
*/
	
	pthread_exit(NULL);
}
