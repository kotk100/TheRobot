
#include <stdio.h>
#include <stdlib.h>

#include "i2c.h"




int main(void)
{
	initI2CConnection();
	while(1){
		uint8_t* data = getSensorData();
		for(int i = 0; i < 8; i++)
			fprintf(stderr, "%d  /  ", (int)data[i]);   
		fprintf(stderr, "\n");   
		delay(200);
	}
}