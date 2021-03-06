
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

RoboCtl::RoboCtl(int m)  : LiquidCrystal::LiquidCrystal(static_cast<uint8_t>(LCD_RS),static_cast<uint8_t>(LCD_EN),
	                          static_cast<uint8_t>(LCD_D0),static_cast<uint8_t>(LCD_D1),static_cast<uint8_t>(LCD_D2),static_cast<uint8_t>(LCD_D3)),
						   RoboState::RoboState(m), CrPath::CrPath(m), Driver::Driver(), Comms::Comms() {
  RoboCtl::setup();
}

//RoboCtl::RoboCtl(noInit i) {}

RoboCtl::~RoboCtl() {}


void RoboCtl::setup() {
  stepCount = 0;
  passedGo = 0;
  mode = READY;
  setLEDReady(OFF);
  setLEDDone(OFF);

  LiquidCrystal::begin(LCD_COLS,LCD_ROWS);
  LiquidCrystal::setCursor(0,0);
  switch(mode){
	case READY:   LiquidCrystal::print("READY  "); break;
	case SEARCH: LiquidCrystal::print("SEARCH  "); break;
	case STOP:   LiquidCrystal::print("STOP    "); break;
	case SOLVE:  LiquidCrystal::print("SOLVE   "); break;
	case DONE:   LiquidCrystal::print("DONE    "); break;
	case RETURN: LiquidCrystal::print("RETURN  "); break;
	default:     LiquidCrystal::print("MODE ERR"); break;
  }
  //LiquidCrystal::print((mode==SEARCH)?"SEARCH  ":"DESTROY ");
  //Driver::goStraight();
}

int RoboCtl::nextAction() {
  //int r;
  LiquidCrystal::setCursor(0,0);
  switch(mode){
	case READY:  LiquidCrystal::print("READY   "); break;
	case SEARCH: LiquidCrystal::print("SEARCH  "); break;
	case STOP:   LiquidCrystal::print("STOP    "); break;
	case SOLVE:  LiquidCrystal::print("SOLVE   "); break;
	case DONE:   LiquidCrystal::print("DONE    "); break;
	case RETURN: LiquidCrystal::print("RETURN  "); break;
	default:     LiquidCrystal::print("MODE ERR"); break;
  }
  LiquidCrystal::setCursor(8,0);
  LiquidCrystal::print("SQUARE   ");
  LiquidCrystal::setCursor(14,0);
  LiquidCrystal::print(String(RoboState::getIndex()));
  if (mode == READY) {
	  RoboCtl::toggleMode();
  } else if(mode == SEARCH || mode == RETURN) {
	stopButton();
    if(!Driver::isWallChk(LEFT)) { 
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print("    LEFT");
	  RoboCtl::turnLeft();
	  //RoboCtl::stepForth();
	 // r = WEST;
	} else if (!Driver::isWallChk(FRONT)) {
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print(" FORWARD");
	  //RoboCtl::stepForth();
	  //r = NORTH;
	} else if (!Driver::isWallChk(RIGHT)) {
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print("   RIGHT");
	  RoboCtl::turnRight();
	  //RoboCtl::stepForth();
	//  r = EAST;
	} else {
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print("    BACK");
	  RoboCtl::aboutFace();
	  //RoboCtl::stepForth();
	//  r = SOUTH;
	}
	  
	LiquidCrystal::setCursor(0,1);
    switch (RoboState::getFacing()) {
      case NORTH: LiquidCrystal::print("NORTH   "); break;
      case EAST: LiquidCrystal::print("EAST    "); break;
      case WEST: LiquidCrystal::print("WEST    "); break;
	  case SOUTH: LiquidCrystal::print("SOUTH   "); break;
	  default: LiquidCrystal::print("Facing error");
    }
	  
	RoboCtl::stepForth();
	
	if (CrPath::getCompletionState() && mode == SEARCH) {
	  setLEDDone(ON);
	  // if (RoboState::getMapSize()==5) { //change to always do return mode? verify with rules first
		// RoboState::reset();
	    // mode = STOP;
	  // } else {
		mode = RETURN;
	  //}
	}
	
	if (mode == RETURN && CrPath::getNextStep(passedGo) == RoboState::getIndex()) {
	  if(passedGo) {
		mode = STOP;
	  } else {
	    passedGo = 1;
	  }
	}
  } else if (mode == STOP) {
	  RoboCtl::toggleMode();
  } else if (mode == SOLVE) {
    currentFacing = RoboState::getFacing();
    nextFacing = RoboCtl::getNextFacing();
	if (nextFacing == -1) {
      stepCount++;
	  return mode;
    }
    LiquidCrystal::setCursor(0,0);
    switch(nextFacing){
	  case NORTH: LiquidCrystal::print("NORTH   "); break;
      case WEST:  LiquidCrystal::print("WEST    "); break;
      case SOUTH: LiquidCrystal::print("SOUTH   "); break;
      case EAST:  LiquidCrystal::print("EAST    "); break;
      default:    LiquidCrystal::print("fac Err "); break;
    }
    LiquidCrystal::setCursor(0,1);
    switch(currentFacing){
      case NORTH: LiquidCrystal::print("NORTH   "); break;
      case WEST:  LiquidCrystal::print("WEST    "); break;
      case SOUTH: LiquidCrystal::print("SOUTH   "); break;
      case EAST:  LiquidCrystal::print("EAST    "); break;
      default:    LiquidCrystal::print("fac Err "); break;
    }
  
    if(currentFacing == nextFacing){
      LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print(" FORWARD");
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
    RoboCtl::stepForth();
	//r = -1;
  }
  
  return mode; //RoboState::areWeBackYet();
}

void RoboCtl::toggleMode() {
  if(!digitalRead(BUTTON)) {
	  setLEDReady(OFF);
	  setLEDDone(OFF);
	  switch(mode) {
	    case STOP: mode = SOLVE; break;
		case READY: mode = SEARCH; break;
		default: mode = ERROR;
	  }
	  RoboState::reset();
  } else {
	  RoboCtl::stop();
	  setLEDReady(ON);
	  delay(50);
  }
}


void RoboCtl::turnRight() {
  if (mode == SEARCH && RoboState::getMapSize() > 5) {
    if(Driver::isWallChk(LEFT)) {
	  RoboCtl::stop();
      Comms::snap(RoboCtl::getMapIndex(RoboState::getIndex()));
	}
  }
  Driver::turnRight();
  RoboState::turnRight();
}

void RoboCtl::turnLeft() {
  if (mode == SEARCH && RoboState::getMapSize() > 5) {
    if(Driver::isWallChk(LEFT)) {
	  RoboCtl::stop();
      Comms::snap(RoboCtl::getMapIndex(RoboState::getIndex()));
	}
  }
  Driver::turnLeft();
  RoboState::turnLeft();
}

void RoboCtl::stepForth() {
  RoboState::step();
  if (mode == SEARCH){
    CrPath::setNextStep(RoboState::getIndex());
    if (RoboState::getMapSize() > 5) {
      if(Driver::isWallChk(LEFT)) {
		RoboCtl::stop();
        Comms::snap(RoboCtl::getMapIndex(RoboState::getIndex()));
	  }
    }
    if (RoboState::getIndex() != 0){
      Driver::goStraight();
    } else {
	  RoboState::turnBack();
	  RoboState::step();
	  RoboState::turnBack();
    }
  } else if (mode == SOLVE) {
	if (currentIndex != RoboState::getMapSize()) {
    stepCount++;
	Driver::goStraight();
	} else {
	  mode = DONE;
	  //digitalWrite(LED_Ready,LOW); //HIGH = OFF, LOW = ON
	  setLEDDone(ON);
	}
  }	else if (mode == RETURN) {
    if(Driver::isWallChk(LEFT)){
      Comms::snap(RoboCtl::getMapIndex(RoboState::getIndex()));
    }
    Driver::goStraight();
  }
}


void RoboCtl::aboutFace() { 
  RoboCtl::turnRight();
  RoboCtl::turnRight();
}

int RoboCtl::getNextFacing()
{
  currentIndex = RoboState::getIndex();
  nextIndex = CrPath::getNextStep(stepCount);
  if (currentIndex == nextIndex) return -1;

  LiquidCrystal::setCursor(8,0);
  LiquidCrystal::print("        ");
  LiquidCrystal::setCursor(8,0);
  LiquidCrystal::print(String(currentIndex));
  LiquidCrystal::print(" to ");
  LiquidCrystal:: print(String(nextIndex));
  
  currentNS = RoboState::getY(currentIndex);
  nextNS = RoboState::getY(nextIndex);
  currentEW = RoboState::getX(currentIndex);
  nextEW = RoboState::getX(nextIndex);;
  
  NS = (currentNS != nextNS);
  EW = (currentEW != nextEW);
  //if (NS == EW) ErrCalls::Err("RoboCtl::getNextFacing -- Diagonal or No movement","STOP");
  if (!EW && nextNS < currentNS) return NORTH;
  else if (!EW && nextNS > currentNS) return SOUTH;
  else if (!NS && nextEW < currentEW) return EAST;
  else if (!NS && nextEW > currentEW) return WEST;
  else mode = ERROR;
  return -1;
  //this section should never be reached
  //ErrCalls::Err("RoboCtl::getNextFacing -- Did not return properly","STOP");
}

void RoboCtl::stop(){
	Driver::stop();
}

int RoboCtl::getMapIndex(int i) {
  //implements a lookup-table based search to get map's index
  // 									from internal index
  const int index7x7[49] = {7,6,5,4,3,2,1,14,13,12,11,10,9,8,21,20,19,18,17,16,15,28,27,26,25,24,23,22,35,34,33,32,31,30,29,42,41,40,39,38,37,36,49,48,47,46,45,44,43};
  const int index6x6[37] = {6,5,4,3,2,1,13,12,11,10,9,8,20,19,18,17,16,15,27,26,25,24,23,22,34,33,32,31,30,29,41,40,39,38,37,36,48}; //= //needs setup
  //const int index5x5[25]; //= //needs setup
  int mapSize = RoboState::getMapSize();
  
  if(mapSize==7) {
    return index7x7[i];
  } else if (mapSize == 6) {
    return index6x6[i];
  }// else if (mapSize == 5) {
    //return index5x5[i];
  //} else {
    //return -1;
  //}
}

void RoboCtl::stopButton() {
	if(!digitalRead(21)) {
	  RoboState::reset();
	  mode = SOLVE;
	}
}

int RoboCtl::getMode() {
  return mode;
}

void RoboCtl::setLEDReady(int val){
	digitalWrite(LED_Ready,val);
}

void RoboCtl::setLEDDone(int val){
	digitalWrite(LED_Done,!val);
}