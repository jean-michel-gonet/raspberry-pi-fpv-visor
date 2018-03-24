//
//  service-locator.hpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 22/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "car-service.hpp"
#include "image-capture-service-from-camera.hpp"

#ifndef service_locator_hpp
#define service_locator_hpp

class ServiceLocator {
public:
	static ServiceLocator* getInstance();
	static CarService* newCarService();
	static ImageCaptureService* newImageCaptureService();
	
	ServiceLocator();
	virtual ~ServiceLocator() = default;

private:
	static ServiceLocator* instance;
	static CarService* carService;
	static ImageCaptureService* imageCaptureService;
};
#endif
