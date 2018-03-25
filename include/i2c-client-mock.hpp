//
//  i2c-client.hpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 25/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#ifndef i2c_client_mock_hpp
#define i2c_client_mock_hpp

#include "i2c-client.hpp"

/** A mock implementation of the I2C client.
 * To be used in environments where WiringPi won't work. */
class I2cClientMock : public I2cClient {
public:
	I2cClientMock();
	virtual ~I2cClientMock() = default;

	/** Returns a random number between 0 and 255.*/
	virtual int i2cRead(int register) override;
};

#endif
