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
i2cClient(nullptr),
mustStop(false)  {
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
	double d;
	int i;
	while(!mustStop) {
		for (int n = 0; n < 4; n++) {
			switch(n) {
				case 0:
					d = i2cClient->i2cRead(0);
					latestCarStatus.currentSpeed = d / 7;
					break;
				case 1:
					d = i2cClient->i2cRead(1);
					latestCarStatus.accumulatorCharge = d / 25;
					break;
				case 2:
					i = i2cClient->i2cRead(2);
					latestCarStatus.positionSteering = i;
					break;
				case 3:
					i = i2cClient->i2cRead(3);
					latestCarStatus.positionAccelerator = i;
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

void CarServiceTormentECX::setI2cClient(I2cClient* c) {
	i2cClient = c;
}

