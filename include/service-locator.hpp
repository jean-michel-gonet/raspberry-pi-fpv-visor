//
//  service-locator.hpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 22/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "car-service.hpp"

#ifndef service_locator_hpp
#define service_locator_hpp

class ServiceLocator {
public:
	static ServiceLocator* getInstance();
	static CarService* newCarService();
	
	ServiceLocator();
	virtual ~ServiceLocator() = default;

private:
	static ServiceLocator* instance;
	static CarService* carService;
};
#endif
