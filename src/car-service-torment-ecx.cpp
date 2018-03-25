//
//  car-controller.cpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 01/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include "car-service-torment-ecx.hpp"

const int CarServiceTormentECX::REFRESH_RATE_IN_MS = 1000;

CarServiceTormentECX::CarServiceTormentECX():
separatedThread(nullptr),
mustStop(false)  {
	start();
}

CarServiceTormentECX::~CarServiceTormentECX() {
	stop();
}

void CarServiceTormentECX::start() {
	if (!separatedThread) {
		mustStop = false;
		separatedThread = new std::thread([this] { refresh(); });
	}
}

void CarServiceTormentECX::stop() {
	mustStop = true;
	if (separatedThread) {
		separatedThread->join();
	}
}

void CarServiceTormentECX::refresh() {
	while(!mustStop) {
		for (int n = 0; n < 4; n++) {
			switch(n) {
				case 0:
					latestCarStatus.currentSpeed = 25.3;
					break;
				case 1:
					latestCarStatus.accumulatorCharge = 8.2;
					break;
				case 2:
					latestCarStatus.positionSteering = 190;
					break;
				case 3:
					latestCarStatus.positionAccelerator = 85;
					break;
			}
			
			std::this_thread::sleep_for(std::chrono::milliseconds(REFRESH_RATE_IN_MS));

			if (mustStop) {
				break;
			}
		}
	}
}

void CarServiceTormentECX::setNotificationCallback(std::function<void ()> n) {
	notifyCapture = n;
}

CarStatus CarServiceTormentECX::getLastStatus() {
	return latestCarStatus;
}
