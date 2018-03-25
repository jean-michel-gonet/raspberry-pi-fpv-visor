//
//  car-service-bldc.hpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 25/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#ifndef car_service_bldc_hpp
#define car_service_bldc_hpp

#include "car-service.hpp"

/** Implementation of a car service to retrieve informations from the Torment-ECX.*/
class CarServiceTormentECX : public CarService {
public:
	CarServiceTormentECX();
	virtual ~CarServiceTormentECX() = default;
	virtual CarStatus getLastStatus() override;
	virtual void setNotificationCallback(std::function<void ()> n) override;

private:
	CarStatus latestCarStatus;
	std::function<void ()> notifyCapture;
	bool refresh();
};

#endif


