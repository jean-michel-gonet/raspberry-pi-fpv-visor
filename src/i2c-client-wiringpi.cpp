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
#include <linux/i2c-dev.h>     // Needed for 'I2C_SLAVE' constant.

#include <iostream>
#include <cerrno>
#include <cstring>

#include "i2c-client-wiringpi.hpp"

I2cClientWiringPi::I2cClientWiringPi() {
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0) {
		std::cout << "Failed to open the i2c bus: " << std::strerror(errno) << '\n';
	}
}

int I2cClientWiringPi::i2cRead(int addr) {
	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0) {
		std::cout << "Failed to acquire bus address " << addr << ": " << std::strerror(errno) << '\n';
		return -1;
        }

	//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
        int length = 1;
        if (read(file_i2c, buffer, length) != length) {
		std::cout << "Failed to read bus address " << addr << ": " << std::strerror(errno) << '\n';
		return -1;
        }
	return buffer[0];
}
