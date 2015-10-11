/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Name        : PCA9685.cpp
 * Author      : Georgi Todorov
 * Version     :
 * Created on  : Dec 9, 2012
 *
 * Copyright © 2012 Georgi Todorov  <terahz@geodar.com>
 */


#include "PCA9685.h"

void reset();
//! Constructor takes bus and address arguments
/*!
 \param bus the bus to use in /dev/i2c-%d.
 \param address the device address on bus
 */
void PCA9685(int bus, int address) {
	I2C(bus,address);
	reset();
	setPWMFreq(60);
}

//! Sets PCA9685 mode to 00
void reset() {
	write_byte(MODE1, 0x00); //Normal mode
	write_byte(MODE2, 0x04); //totem pole
}
//! Set the frequency of PWM
/*!
 \param freq desired frequency. 40Hz to 1000Hz using internal 25MHz oscillator.
 */
void setPWMFreq(int freq) {
	uint8_t prescale_val = (CLOCK_FREQ / 4096 / freq)  - 1;
	write_byte(MODE1, 0x10); //sleep
	write_byte(PRE_SCALE, prescale_val); // multiplyer for PWM frequency
	write_byte(MODE1, 0x80); //restart
	write_byte(MODE2, 0x04); //totem pole (default)
}

//! PWM a single channel
/*!
 \param led channel to set PWM value for
 \param value 0-4095 value for PWM
 */
void setPWM(uint8_t led, int value) {
	setPWMOnOff(led, 0, value);
}


//! PWM a single channel with custom on time
/*!
 \param led channel to set PWM value for
 \param on_value 0-4095 value to turn on the pulse
 \param off_value 0-4095 value to turn off the pulse
 */
void setPWMOnOff(uint8_t led, int on_value, int off_value) {
	write_byte(LED0_ON_L + LED_MULTIPLYER * (led - 1), on_value & 0xFF);
	write_byte(LED0_ON_H + LED_MULTIPLYER * (led - 1), on_value >> 8);
	write_byte(LED0_OFF_L + LED_MULTIPLYER * (led - 1), off_value & 0xFF);
	write_byte(LED0_OFF_H + LED_MULTIPLYER * (led - 1), off_value >> 8);
}

int getPWM(uint8_t led){
	int ledval = 0;
	ledval = read_byte(LED0_OFF_H + LED_MULTIPLYER * (led-1));
	ledval = ledval & 0xf;
	ledval <<= 8;
	ledval += read_byte(LED0_OFF_L + LED_MULTIPLYER * (led-1));
	return ledval;
}


void servoControl(uint8_t servo, int angle)
{
	
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
}


// <editor-fold defaultstate="collapsed" desc="Arduino sensor code">
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
// </editor-fold>






