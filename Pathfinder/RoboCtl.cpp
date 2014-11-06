#include <QTRSensors.h>
#include "RoboCtl.h"
#include "RoboState.h"
#include "CrPath.h"
#include "Driver.h"
#include "Comms.h"
#include "DEFINES.h"
#include "DEFINES-TEST.h"

RoboCtl::RoboCtl() {}

RoboCtl::~RoboCtl() {}



void RoboCtl::setCourse() {
  if(g::mode == SEARCH) {
    if(!Driver::isLeftWallChk()) { 
	  RoboCtl::turnLeft();
	  } else if (!Driver::isFrontWallChk()) {
	  RoboCtl::stepForth();
	  } else if (!Driver::isRightWallChk()) {
	  RoboCtl::turnRight();
	  } else {
	  RoboCtl::aboutFace();
	  }
  } else {
    RoboCtl::nextAction(stepCount)
  }

}


RoboCtl::turnRight() {
  Driver::turnRight();
  RoboState::turnRight();
  if(Driver::isRightWallChk()) Comms::snap(RoboCtl::getMapIndex());
}

RoboCtl::turnLeft() {
  Driver::turnLeft();
  RoboState::turnLeft();
  if(Driver::isLeftWallChk()) Comms::snap(RoboCtl::getMapIndex());
}

RoboCtl::stepForth() {
  Driver::goStraight();
  RoboState::step();
  if(Driver::isFrontWallChk()) Comms::snap(RoboCtl::getMapIndex());
  if(!g::mode==SEARCH) stepCount++;
}


RoboCtl::aboutFace() { 
  RoboCtl::turnLeft();
  RoboCtl::turnLeft();
}


int RoboCtl::getNextFacing(i);
{
  currentNS = roboState::getY();
  nextNS = roboState::getY(i);
  currentEW = roboState::getX();
  nextEW = roboState::getX(i);
  
  byte NS = static_cast<byte>!(currentNS == nextNS);
  byte EW = static_cast<byte>!(currentEW == nextEW);
  //if (NS == EW) ErrCalls::Err("RoboCtl::getNextFacing -- Diagonal or No movement","STOP");
  if (NS && nextNS < currentNS) return NORTH;
  if (NS && nextNS > currentNS) return SOUTH;
  if (EW && nextEW < currentEW) return EAST;
  if (EW && nextEW > currentEW) return WEST;
  //this section should never be reached
  //ErrCalls::Err("RoboCtl::getNextFacing -- Did not return properly","STOP");
}

void RoboCtl::nextAction(i) {
  currentFacing = RoboState::getFacing();
  nextFacing = RoboCtl::getNextFacing(i);
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
  return
}

RoboCtl::getMapIndex(i) {
  //implements a lookup-table based search to get map's index
  // 									from internal index
  const int index7x7[49]; //= //needs setup
  const int index6x6[36]; //= //needs setup
  const int index5x5[25]; //= //needs setup
  
  if(mapSize==7) {
    return index7x7[i];
  } else if (mapSize == 6) {
    return index6x6[i];
  } else if (mapSize == 5) {
    return index5x5[i];
  } else {
    return -1;
  }
}
