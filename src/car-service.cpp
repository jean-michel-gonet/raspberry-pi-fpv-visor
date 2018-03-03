//
//  car-controller.cpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 01/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "car-service.hpp"

CarService::CarService() {
	// Nothing to do.
}

bool CarService::refreshStatus() {
	
	carStatus.accumulatorCharge = 10;
	carStatus.positionAccelerator = 20;
	carStatus.currentSpeed = 30;
	carStatus.positionSteering = 40;
	
	return true;
}

CarStatus CarService::getCarStatus() {
	CarStatus cs;
	
	cs.accumulatorCharge = carStatus.accumulatorCharge;
	cs.positionAccelerator = carStatus.positionAccelerator;
	cs.currentSpeed = carStatus.currentSpeed;
	cs.positionSteering = carStatus.positionSteering;
	
	return cs;
}
