#ifndef ROBOCTL
#define ROBOCTL


#include <QTRSensors.h>
#include <LiquidCrystal.h>
#include "RoboState.h"
#include "CriticalPath.h"
#include "Driver.h"
#include "Comms.h"
#include "DEFINES.h"
#include "DEFINES-TEST.h"

#ifdef LCD_CONNECTED
class RoboCtl: private RoboState, private CrPath, private Driver, private Comms, public LiquidCrystal { 
#else
class RoboCtl: private RoboState, private CrPath, private Driver, private Comms { 	
#endif
  public:
    //Constructor and destructors
	RoboCtl();
	//RoboCtl(noInit i) : LiquidCrystal(1,LCD_RS,255,LCD_EN,LCD_D0,LCD_D1,LCD_D2,LCD_D3,0,0,0,0);

	~RoboCtl();
	 
    void setup();

	 
	//Decision Making
	void setCourse();
	void nextAction();
	void toggleMode();

  private:
	
    int mode;
	int currentFacing;
	int nextFacing;

	//Movement Controls
	void turnLeft();
	void turnRight();
	void stepForth();
	void aboutFace();
	 
	//Status
	int getMapIndex(int);
	int calNextNS();
	int calNextEW();
	int getNextFacing();
	
	//Decision making / function caller
	int nextIndex;
	int stepCount;
    int currentNS;
    int nextNS;
    int currentEW;
    int nextEW;
  
    int NS;
    int EW;
};

#endif ROBOCTL