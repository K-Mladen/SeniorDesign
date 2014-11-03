#ifndef ROBOCTL
#define ROBOCTL


#include <QTRSensors.h>
#include "RoboState.h"
#include "CrPath.h"
#include "Driver.h"
#include "DEFINES.h"
#include "DEFINES-TEST.h"

class RoboCtl: private RoboState, private CrPath, private Driver { 
  public:
    //Constructor and destructors
	RoboCtl();
	~RoboCtl();
	 
	//Decision Making
	bool Setcourse();
	
	//Movement Controls
	void turnLeft();
	void turnRight();
	void stepForth();
	void aboutFace();
	 
	//Status
	int getFacing();
	int getM();
	int getN();
	int getIndex

  private:
};

#endif ROBOCTL