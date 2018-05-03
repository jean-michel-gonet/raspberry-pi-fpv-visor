#include "catch.hpp"
#include "i2c-client.hpp"
#include "car-service.hpp"
#include "car-service-torment-ecx.hpp"


/** A mock implementation of the I2C client.
 * To be used in environments where WiringPi won't work. */
class I2cClientMock2 : public I2cClient {
public:
	I2cClientMock2() {
		// Nothing special;
	};
	
	virtual ~I2cClientMock2() = default;
	
	/** Returns the value of the specified address. */
	virtual int i2cRead(int address) override {
		return address;
	};
};

SCENARIO("Torment Car Service Fetches the appropriate addresses") {
	GIVEN( "An initialized Tormet Car Service") {
		I2cClientMock2 i2cClientMock;
		CarServiceTormentECX carService;
		carService.setI2cClient(&i2cClientMock);
		
		WHEN( "Waiting enough time") {
			carService.start();
			std::this_thread::sleep_for(std::chrono::milliseconds(CarServiceTormentECX::REFRESH_RATE_IN_MS * 10));
			
			THEN ( "The car status is updated ") {
				CarStatus carStatus = carService.getLastStatus();
				REQUIRE( carStatus.accumulatorCharge == 0.48 );
				REQUIRE( carStatus.currentSpeed  - 2.7142857143 < 0.01 );
				REQUIRE( carStatus.positionAccelerator == 16 );
				REQUIRE( carStatus.positionSteering == 17 );
			}
		}
		
	}
}
