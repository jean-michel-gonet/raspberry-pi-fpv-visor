//
//  i2c-client.cpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 25/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <stdio.h>

#include "i2c-client-wiringpi.hpp"

I2cClientWiringPi::I2cClientWiringPi() {
//	printf("Hello World\n");
}

int I2cClientWiringPi::i2cRead(int c) {
	return 125;//wiringPiI2CRead(c);
}
