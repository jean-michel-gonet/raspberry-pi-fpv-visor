//
//  i2c-client.hpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 25/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#ifndef i2c_client_wiringpi_hpp
#define i2c_client_wiringpi_hpp

#include "i2c-client.hpp"

/** An implementation of the I2C client using WiringPi library.
 * To be used only in Raspberry Pi. */
class I2cClientWiringPi : public I2cClient {
public:
	I2cClientWiringPi();
	virtual ~I2cClientWiringPi() = default;

	virtual int i2cRead(int c) override;
	virtual int initialize();
private:
	int file_i2c;
	unsigned char buffer[60] = {0};
};

#endif
