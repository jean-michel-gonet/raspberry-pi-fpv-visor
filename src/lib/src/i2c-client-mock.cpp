//
//  i2c-client.cpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 25/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include <stdlib.h>

#include "i2c-client-mock.hpp"

I2cClientMock::I2cClientMock() {
	// Nothing to do.
}

int I2cClientMock::i2cRead(int address) {
	return rand() % 256;
}
