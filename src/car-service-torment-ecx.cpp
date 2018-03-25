//
//  car-controller.cpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 01/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "car-service-torment-ecx.hpp"

CarServiceTormentECX::CarServiceTormentECX():
latestCarStatus() {
	// Nothing to do.
}

bool CarServiceTormentECX::refresh() {
	
	latestCarStatus.currentSpeed = 25.3;
	latestCarStatus.accumulatorCharge = 8.2;
	latestCarStatus.positionSteering = 190;
	latestCarStatus.positionAccelerator = 85;
	
	return true;
}

void CarServiceTormentECX::setNotificationCallback(std::function<void ()> n) {
	notifyCapture = n;
}

CarStatus CarServiceTormentECX::getLastStatus() {
	return latestCarStatus;
}
