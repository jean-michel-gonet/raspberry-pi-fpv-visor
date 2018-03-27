//
//  service-locator.cpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 22/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "service-locator.hpp"

ServiceLocator* ServiceLocator::instance = nullptr;

CarServiceTormentECX* ServiceLocator::carService = nullptr;

ImageCaptureServiceFromCamera* ServiceLocator::imageCaptureService = nullptr;

I2cClientWiringPi* ServiceLocator::i2cClient = nullptr;

ServiceLocator::ServiceLocator() {
	// Nothing to do.
}

ServiceLocator* ServiceLocator::getInstance() {
	if (instance == nullptr) {
		instance = new ServiceLocator();
	}
	return instance;
}

CarService* ServiceLocator::newCarService() {
	if (carService == nullptr) {
		carService = new CarServiceTormentECX();
		carService->setI2cClient(newI2cClient());
		carService->start();
	}
	return carService;
}

ImageCaptureService * ServiceLocator::newImageCaptureService() {
	if (imageCaptureService == nullptr) {
		imageCaptureService = new ImageCaptureServiceFromCamera();
	}
	return imageCaptureService;
}

I2cClient* ServiceLocator::newI2cClient() {
	if (i2cClient == nullptr) {
		i2cClient = new I2cClientWiringPi();
	}
	return i2cClient;
}
