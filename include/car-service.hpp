//
//  car-controller.hpp
//  raspberry-pi-fpv-visor
//
//  Created by Jean-Michel Gonet on 01/03/18.
//  Copyright © 2018 Jean-Michel Gonet. All rights reserved.
//

#ifndef car_service_hpp
#define car_service_hpp

#include "notifier.hpp"

/** Describes the car status.*/
class CarStatus {
public:
	/** The current speed, in km/h*/
	double currentSpeed;
	
	/** The current accumulator charge, in V.*/
	double accumulatorCharge;
	
	/** The current position of the steering wheel.
	 * An integer between 0 (completely to the left) 
	 * and 255 (completely to the right).
	 */
	int positionSteering;

	/** The current position of the accelerator.
	 * An integer between 0 (completely to the left)
	 * and 255 (completely to the right).
	 */
	int positionAccelerator;
};

/** Describes a class to retrieve the car status.
 */
class CarService : public Notifier {
public:
	virtual ~CarService() = default;

	/** Returns the lates captured car status.*/
	virtual CarStatus getLastStatus() = 0;
};

#endif
