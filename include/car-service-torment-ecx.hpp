//
//  car-service-bldc.hpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 25/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#ifndef car_service_torment_ecx_hpp
#define car_service_torment_ecx_hpp

#include <thread>

#include "car-service.hpp"

/** Implementation of a car service to retrieve informations from the Torment-ECX.*/
class CarServiceTormentECX : public CarService {
public:
	static const int REFRESH_RATE_IN_MS;
	CarServiceTormentECX();
	virtual ~CarServiceTormentECX();
	virtual CarStatus getLastStatus() override;
	virtual void setNotificationCallback(std::function<void ()> n) override;

private:
	bool mustStop;
	std::thread* separatedThread;
	CarStatus latestCarStatus;
	std::function<void ()> notifyCapture;
	void refresh();
	void start();
	void stop();
};

#endif


