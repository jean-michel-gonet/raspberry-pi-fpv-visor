//
//  i2c-client.hpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 25/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#ifndef i2c_client_hpp
#define i2c_client_hpp

/** Describes the interface of a I2C clients. */
class I2cClient {
public:
	virtual ~I2cClient() = default;

	/** Simple device read. 
	 * Some devices present data when you read them without having to 
	 * do any register transactions.*/
	 virtual int i2cRead(int address) = 0;
};

#endif
