//
//  service-locator.hpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 22/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "car-service-torment-ecx.hpp"
#include "image-capture-service-from-camera.hpp"
#include "i2c-client-wiringpi.hpp"
#include "i2c-client-mock.hpp"

#ifndef service_locator_hpp
#define service_locator_hpp

class ServiceLocator {
public:
	static ServiceLocator* getInstance();
	static CarService* newCarService();
	static ImageCaptureService* newImageCaptureService();
	static I2cClient* newI2cClient();
	
	ServiceLocator();
	virtual ~ServiceLocator() = default;

private:
	static ServiceLocator* instance;
	static CarServiceTormentECX* carService;
	static ImageCaptureServiceFromCamera* imageCaptureService;
	static I2cClient* i2cClient;
};
#endif
