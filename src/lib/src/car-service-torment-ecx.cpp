//
//  car-controller.cpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 01/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#include <stdio.h>

#include "car-service-torment-ecx.hpp"

const int CarServiceTormentECX::REFRESH_RATE_IN_MS = 100;

CarServiceTormentECX::CarServiceTormentECX():
mustStop(false),
separatedThread(nullptr),
i2cClient(nullptr) {
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
		for (int n = 0; n < 7; n++) {
			switch(n) {
				case 1:
					d = i2cClient->i2cRead(19);
					latestCarStatus.currentSpeed = d / 7;
					break;
				case 3:
					d = i2cClient->i2cRead(22);
					d = latestCarStatus.accumulatorCharge * d / 255;
					latestCarStatus.pwm = d;
					break;
				case 5:
					d = i2cClient->i2cRead(12);
					latestCarStatus.accumulatorCharge = d / 25;
					break;
				case 0:
				case 4:
					i = i2cClient->i2cRead(17);
					latestCarStatus.positionSteering = i;
					break;
				case 2:
				case 6:
					i = i2cClient->i2cRead(16);
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

CarStatus CarServiceTormentECX::getLastStatus() {
	return latestCarStatus;
}

void CarServiceTormentECX::setI2cClient(I2cClient* c) {
	i2cClient = c;
}

