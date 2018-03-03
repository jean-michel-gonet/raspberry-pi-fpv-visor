//
//  car-controller.hpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 01/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#ifndef car_service_hpp
#define car_service_hpp

#include <stdio.h>

class CarStatus {
public:
	int currentSpeed;
	int accumulatorCharge;
	int positionSteering;
	int positionAccelerator;
};

class CarService {
public:
	CarService();
	virtual ~CarService() = default;
	
	bool refreshStatus();
	CarStatus getCarStatus();

private:
	CarStatus carStatus;
};

#endif /* car_controller_hpp */
