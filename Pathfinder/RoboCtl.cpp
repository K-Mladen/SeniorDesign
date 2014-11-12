#include <QTRSensors.h>
#include "RoboCtl.h"
#include "RoboState.h"
#include "CriticalPath.h"
#include "Driver.h"
#include "Comms.h"
#include "DEFINES.h"
#include "DEFINES-TEST.h"
#include "Arduino.h"

RoboCtl::RoboCtl() {
  setup();
}

RoboCtl::RoboCtl(noInit i) {}

RoboCtl::~RoboCtl() {}


void RoboCtl::setup() {
  stepCount = 1;
  mode = SEARCH;
}

void RoboCtl::setCourse() {
  if(mode == SEARCH) {
    if(!Driver::isLeftWallChk()) { 
	  RoboCtl::turnLeft();
	  RoboCtl::stepForth();
	  } else if (!Driver::isFrontWallChk()) {
	  RoboCtl::stepForth();
	  } else if (!Driver::isRightWallChk()) {
	  RoboCtl::turnRight();
	  RoboCtl::stepForth();
	  } else {
	  RoboCtl::aboutFace();
	  RoboCtl::stepForth();
	  }
  } else {
    RoboCtl::nextAction();
  }

}


void RoboCtl::turnRight() {
  Driver::turnRight();
  RoboState::turnRight();
  if(Driver::isRightWallChk())
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
  if(Driver::isFrontWallChk())
    Comms::snap(RoboCtl::getMapIndex(RoboState::getIndex()));
  if ( mode != SEARCH ) stepCount++;
}


void RoboCtl::aboutFace() { 
  RoboCtl::turnLeft();
  RoboCtl::turnLeft();
}


int RoboCtl::getNextFacing()
{
  int currentNS = RoboState::getY();
  int nextNS = RoboState::getY(stepCount);
  int currentEW = RoboState::getX();
  int nextEW = RoboState::getX(stepCount);
  
  int NS = (currentNS != nextNS);
  int EW = (currentEW != nextEW);
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
    RoboCtl::stepForth();
  } else if((currentFacing == NORTH && nextFacing == EAST) ||
			(currentFacing == EAST && nextFacing == SOUTH) ||
			(currentFacing == SOUTH && nextFacing == WEST) ||
			(currentFacing == WEST && nextFacing == NORTH) ){
    RoboCtl::turnRight();
  } else if((currentFacing == NORTH && nextFacing == WEST) ||
            (currentFacing == WEST && nextFacing == SOUTH) ||
			(currentFacing == SOUTH && nextFacing == EAST) ||
			(currentFacing == EAST && nextFacing == NORTH) ){
	RoboCtl::turnLeft();
  } else if((currentFacing == NORTH && nextFacing == SOUTH) ||
            (currentFacing == SOUTH && nextFacing == NORTH) ||
			(currentFacing == EAST && nextFacing == WEST) ||
			(currentFacing == WEST && nextFacing == EAST) ){
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
