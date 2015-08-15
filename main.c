
#include <stdio.h>
#include <stdlib.h>


#include "i2c.h"
#include "pca9685.h"


#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50


int calcTicks(float impulseMs, int hertz)
{
	float cycleMs = 1000.0f / hertz;
	return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}

/**
 * input is [0..1]
 * output is [min..max]
 */
float map(float input, float min, float max)
{
	return (input * max) + (1 - input) * min;
}


int main(void)
{
	printf("PCA9685 servo example\n");
	printf("Connect a servo to any pin. It will rotate to random angles\n");

	// Setup with pinbase 300 and i2c location 0x40
	int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0)
	{
		printf("Error in setup\n");
		return fd;
	}

	// Reset all output
	pca9685PWMReset(fd);


	// Set servo to neutral position at 1.5 milliseconds
	// (View http://en.wikipedia.org/wiki/Servo_control#Pulse_duration)
	float millis = 1.5;
	int tick = calcTicks(millis, HERTZ);
	


	int active = 1;

		// That's a hack. We need a random number < 1
		millis = 2;
		tick = calcTicks(millis, HERTZ);
		while(1){
			pwmWrite(PIN_BASE + 0, 200);
			delay(3000);
			pwmWrite(PIN_BASE + 0, 300);
			delay(3000);
		}
	

	return 0;
}