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



RoboCtl::setCourse() {
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
}


RoboCtl::aboutFace() { 
  RoboCtl::turnLeft();
  RoboCtl::turnLeft();
}


RoboCtl::getFacing() {

}

RoboCtl::getN() {

}

RoboCtl::getM() {


}

RoboCtl::getMapIndex(i) {
  //implements a lookup-table based search to get map's index
  // 									from internal index
  const int index7x7[49]; = //needs setup
  const int index6x6[36]; = //needs setup
  const int index5x5[25]; = //needs setup
  
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
