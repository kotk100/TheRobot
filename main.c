
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "PCA9685.h"



int main(void)
{
/*
	pthread_t sensorData;
 *	int temp = pthread_create(&sensorData, NULL, sensorDataUpdateBegin, NULL);
	if(temp){
		fprintf(stderr, "ERROR creating sensorData thread");
 *		exit(-1);
 *	}
*/
			
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
	
/*
	pthread_exit(NULL);
*/
}
