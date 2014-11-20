
#include <QTRSensors.h>
#include <LiquidCrystal.h>
#include "RoboCtl.h"
#include "RoboState.h"
#include "CriticalPath.h"
#include "Driver.h"
#include "Comms.h"
#include "DEFINES.h"
#include "DEFINES-TEST.h"
#include "Arduino.h"

RoboCtl::RoboCtl()  : LiquidCrystal::LiquidCrystal(static_cast<uint8_t>(LCD_RS),static_cast<uint8_t>(LCD_EN),
	                          static_cast<uint8_t>(LCD_D0),static_cast<uint8_t>(LCD_D1),static_cast<uint8_t>(LCD_D2),static_cast<uint8_t>(LCD_D3)) {
  RoboCtl::setup();
}

//RoboCtl::RoboCtl(noInit i) {}

RoboCtl::~RoboCtl() {}


void RoboCtl::setup() {
  stepCount = 1;
  mode = SEARCH;
  LiquidCrystal::begin(LCD_COLS,LCD_ROWS);
  LiquidCrystal::setCursor(0,0);
  LiquidCrystal::print((mode==SEARCH)?"SEARCH  ":"DESTROY ");
}

int RoboCtl::setCourse() {
  if(mode == SEARCH) {
    if(!Driver::isLeftWallChk()) { 
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print("    LEFT");
	  RoboCtl::turnLeft();
	  RoboCtl::stepForth();
	  } else if (!Driver::isFrontWallChk()) {
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print(" FORWARD");
	  RoboCtl::stepForth();
	  } else if (!Driver::isRightWallChk()) {
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print("   RIGHT");
	  RoboCtl::turnRight();
	  RoboCtl::stepForth();
	  } else {
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print("    BACK");
	  RoboCtl::aboutFace();
	  RoboCtl::stepForth();
	  }
  } else {
    RoboCtl::nextAction();
  }
  
  LiquidCrystal::setCursor(8,0);
  LiquidCrystal::print("SQUARE   ");
  LiquidCrystal::setCursor(15,0);
  LiquidCrystal::print(String(RoboState::getIndex()));
  
  return RoboState::areWeBackYet();
}


void RoboCtl::turnRight() {
  Driver::turnRight();
  RoboState::turnRight();
  if(Driver::isLeftWallChk())
    Comms::snap(RoboCtl::getMapIndex(RoboState::getIndex()));
}

void RoboCtl::turnLeft() {
  Driver::turnLeft();
  RoboState::turnLeft();
  if(Driver::isLeftWallChk()) 
    Comms::snap(RoboCtl::getMapIndex(RoboState::getIndex()));
}

void RoboCtl::stepForth() {
  Driver::goStraight();
  RoboState::step();
  if(Driver::isLeftWallChk())
    Comms::snap(RoboCtl::getMapIndex(RoboState::getIndex()));
  if ( mode != SEARCH ) stepCount++;
}


void RoboCtl::aboutFace() { 
  RoboCtl::turnLeft();
  RoboCtl::turnLeft();
}

int RoboCtl::getNextFacing()
{
  nextIndex = CrPath::getNextStep(stepCount);
  currentNS = RoboState::getY();
  nextNS = RoboState::getY(nextIndex);
  currentEW = RoboState::getX();
  nextEW = RoboState::getX(nextIndex);;
  
  NS = (currentNS != nextNS);
  EW = (currentEW != nextEW);
  //if (NS == EW) ErrCalls::Err("RoboCtl::getNextFacing -- Diagonal or No movement","STOP");
  if (NS && nextNS < currentNS) return NORTH;
  if (NS && nextNS > currentNS) return SOUTH;
  if (EW && nextEW < currentEW) return EAST;
  if (EW && nextEW > currentEW) return WEST;
  //this section should never be reached
  //ErrCalls::Err("RoboCtl::getNextFacing -- Did not return properly","STOP");
}

void RoboCtl::nextAction() {
  int currentFacing = RoboState::getFacing();
  int nextFacing = RoboCtl::getNextFacing();
  if(currentFacing == nextFacing){
    LiquidCrystal::setCursor(8,1);
    LiquidCrystal::print(" FORWARD");
    RoboCtl::stepForth();
  } else if((currentFacing == NORTH && nextFacing == EAST) ||
			(currentFacing == EAST && nextFacing == SOUTH) ||
			(currentFacing == SOUTH && nextFacing == WEST) ||
			(currentFacing == WEST && nextFacing == NORTH) ){
    LiquidCrystal::setCursor(8,1);
    LiquidCrystal::print("   RIGHT");
    RoboCtl::turnRight();
  } else if((currentFacing == NORTH && nextFacing == WEST) ||
            (currentFacing == WEST && nextFacing == SOUTH) ||
			(currentFacing == SOUTH && nextFacing == EAST) ||
			(currentFacing == EAST && nextFacing == NORTH) ){
	LiquidCrystal::setCursor(8,1);
    LiquidCrystal::print("    LEFT");		
	RoboCtl::turnLeft();
  } else if((currentFacing == NORTH && nextFacing == SOUTH) ||
            (currentFacing == SOUTH && nextFacing == NORTH) ||
			(currentFacing == EAST && nextFacing == WEST) ||
			(currentFacing == WEST && nextFacing == EAST) ){
    LiquidCrystal::setCursor(8,1);
    LiquidCrystal::print("    BACK");
    RoboCtl::aboutFace();
  }
}

int RoboCtl::getMapIndex(int i) {
  //implements a lookup-table based search to get map's index
  // 									from internal index
  const int index7x7[49]={7,6,5,4,3,2,1,14,13,12,11,10,9,8,21,20,19,18,17,16,15,28,27,26,25,24,23,22,35,34,33,32,31,30,29,42,41,40,39,38,37,36,49,48,47,46,45,44,43}; //= //needs setup
  //const int index6x6[36]; //= //needs setup
  //const int index5x5[25]; //= //needs setup
  int mapSize = RoboState::getMapSize();
  
  //if(mapSize==7) {
    return index7x7[i];
  //} else if (mapSize == 6) {
    //return index6x6[i];
  //} else if (mapSize == 5) {
    //return index5x5[i];
  //} else {
    //return -1;
  //}
}

