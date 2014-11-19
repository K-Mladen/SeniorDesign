#ifndef ROBOCTL
#define ROBOCTL


#include <QTRSensors.h>
#include "RoboState.h"
#include "CriticalPath.h"
#include "Driver.h"
#include "Comms.h"
#include "DEFINES.h"
#include "DEFINES-TEST.h"

class RoboCtl: private RoboState, private CrPath, private Driver, private Comms,public LiquidCrystal { 
  public:
    //Constructor and destructors
	RoboCtl();
	RoboCtl(noInit i);

	~RoboCtl();
	 
    void setup();

	 
	//Decision Making
	void setCourse();

  private:
	
    int mode;

	//Movement Controls
	void turnLeft();
	void turnRight();
	void stepForth();
	void aboutFace();
	 
	//Status
	int getMapIndex(int);
	int getNextFacing();
	
	//Decision making / function caller
	void nextAction();
	int stepCount;
    int currentNS;
    int nextNS;
    int currentEW;
    int nextEW;
  
    int NS;
    int EW;
};

#endif ROBOCTL