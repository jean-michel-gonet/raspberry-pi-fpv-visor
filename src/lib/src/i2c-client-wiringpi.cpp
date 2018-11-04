//
//  i2c-client.cpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 25/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include <unistd.h>            // Needed for 'read' function.
#include <fcntl.h>             // Needed for 'open' function.
#include <sys/ioctl.h>         // Needed for 'ioctl' function.

#include <iostream>
#include <cerrno>
#include <cstring>

#include "i2c-client-wiringpi.hpp"

// Find this definition in linux/i2c-dev.h, which I haven't included
// to ease cross-compiler compilation.
#define I2C_SLAVE	0x0703	/* Use this slave address */

I2cClientWiringPi::I2cClientWiringPi() {
	// Nothing to do.
}

int I2cClientWiringPi::initialize() {
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0) {
		std::cout << "Failed to open the i2c bus: " << std::strerror(errno) << '\n';
		return -errno;
	}
	return 0;
}

int I2cClientWiringPi::i2cRead(int address) {
	if (ioctl(file_i2c, I2C_SLAVE, address) < 0) {
		std::cout << "Failed to acquire bus address " << address << ": " << std::strerror(errno) << '\n';
		return -1;
	}

	// read() returns the number of bytes actually read, 
	// if it doesn't match then an error occurred 
	// (e.g. no response from the device)
	int length = 1;
	if (read(file_i2c, buffer, length) != length) {
		std::cout << "Failed to read bus address " << address << ": " << std::strerror(errno) << '\n';
		return -1;
	}
	
	return buffer[0];
}
