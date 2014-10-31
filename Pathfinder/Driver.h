#ifndef DRIVER
#define DRIVER

#include "Defines.h"
#include "DEFINES-TEST.h"



class Driver: private Sensors::Reflectance {
  public:
    //Constructors, Destructors
	Driver();
	//Driver(inits &); --> Define inits class for this...?
	~Driver();
	
	turnRight();
	turnLeft();
	turnAround();
	goStraight
	
	private:
	move(int leftMotorDir, int rightMotorDir);
}

#endif