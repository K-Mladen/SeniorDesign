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
	} else if (!Driver::isFrontWallChk())
	  RoboCtl::stepForth();
	} else if (!Driver::isRightWallChk())
	  RoboCtl::turnRight();
	}
  } else {
  
  }

}


RoboCtl::turnRight() {
  Driver::turnRight();
  RoboState::turnRight();
  Comms::snap(index);
}

RoboCtl::turnLeft() {
  Driver::turnLeft();
  RoboState::turnLeft();
  Comms::snap(index);
}

RoboCtl::stepForth() {
  Driver::goStraight();
  RoboState::step();
  Comms::snap(index);
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

RoboCtl::getIndex() {

}