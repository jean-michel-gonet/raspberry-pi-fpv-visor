#include "i2c-client-wiringpi.hpp"

#include "gmock/gmock.h"

/**
 * Entry point for testing.
 */
int main(int argc, char** argv) {
   std::cout << "main-test:Hello\n";  
   testing::InitGoogleMock(&argc, argv);
   return RUN_ALL_TESTS();
}

TEST(I2CClientWiringPiXX, CanBeCalled) { 
   I2cClientWiringPi i2cClient;
   std::cout << "i2c-client-wiring-pi: Hello\n";  
}
