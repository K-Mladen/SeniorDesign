
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
  mode = WAIT;

  LiquidCrystal::begin(LCD_COLS,LCD_ROWS);
  LiquidCrystal::setCursor(0,0);
  switch(mode){
	case WAIT:   LiquidCrystal::print("WAIT    "); break;
	case SEARCH: LiquidCrystal::print("SEARCH  "); break;
	case STOP:   LiquidCrystal::print("STOP    "); break;
	case SOLVE:  LiquidCrystal::print("SOLVE   "); break;
	default:     LiquidCrystal::print("MODE ERR"); break;
  }
  //LiquidCrystal::print((mode==SEARCH)?"SEARCH  ":"DESTROY ");
  Driver::goStraight();
}

int RoboCtl::setCourse() {
  //int r;
  LiquidCrystal::setCursor(0,0);
  switch(mode){
	case WAIT:   LiquidCrystal::print("WAIT    "); break;
	case SEARCH: LiquidCrystal::print("SEARCH  "); break;
	case STOP:   LiquidCrystal::print("STOPSTOP    "); break;
	case SOLVE:  LiquidCrystal::print("SOLVE   "); break;
	default:     LiquidCrystal::print("MODE ERR"); break;
  }
  LiquidCrystal::setCursor(8,0);
  LiquidCrystal::print("SQUARE   ");
  LiquidCrystal::setCursor(14,0);
  LiquidCrystal::print(String(RoboState::getIndex()));
  if (mode == WAIT) {
	  RoboCtl::toggleMode();
  } else if(mode == SEARCH) {
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
	  
	RoboCtl::stepForth();
	
	if (CrPath::getCompletionState()) {
	  digitalWrite(LED_Done,LOW);
	  if (RoboState::getMapSize()==5) {
		RoboState::reset();
	    mode = STOP;
	  }
	}
  } else if (mode == STOP) {
	  RoboCtl::toggleMode();
  } else if (mode == SOLVE) {
    currentFacing = RoboState::getFacing();
	//nextFacing = RoboCtl::getNextFacing();
	currentIndex = RoboState::getIndex();
	nextIndex = CrPath::getNextStep(stepCount);
	
	currentNS = RoboState::getY(currentIndex);
	nextNS = RoboState::getY(nextIndex);
	currentEW = RoboState::getX(currentIndex);
	nextEW = RoboState::getX(nextIndex);;
	
	
	
	//if (NS == EW) ErrCalls::Err("RoboCtl::getNextFacing -- Diagonal or No movement","STOP");
	if (currentNS != nextNS && nextNS < currentNS) nextFacing = NORTH;
	if (currentNS != nextNS && nextNS > currentNS) nextFacing = SOUTH;
	if (currentEW != nextEW && nextEW < currentEW) nextFacing = EAST;
	if (currentEW != nextEW && nextEW > currentEW) nextFacing = WEST;
	if ((currentEW != nextEW) == (currentNS != nextNS)) mode = ERROR;
	//r = -1;
	RoboState::setFacing(nextFacing);
  }
  	LiquidCrystal::setCursor(0,1);
    switch (RoboState::getFacing()) {
      case NORTH: LiquidCrystal::print("NORTH   "); break;
      case EAST: LiquidCrystal::print("EAST    "); break;
      case WEST: LiquidCrystal::print("WEST    "); break;
	  case SOUTH: LiquidCrystal::print("SOUTH   "); break;
	  default: LiquidCrystal::print("Facing error");
    }
	  
	
	  RoboState::setFacing(nextFacing);
  
  { //LCD Code
  LiquidCrystal::setCursor(0,0);
  switch(nextFacing){
	case NORTH: LiquidCrystal::print("NORTH   "); break;
	case WEST:  LiquidCrystal::print("WEST    "); break;
	case SOUTH: LiquidCrystal::print("SOUTH   "); break;
	case EAST:  LiquidCrystal::print("EAST    "); break;
	default:    LiquidCrystal::print("fac Err "); break;
  }
  LiquidCrystal::print(String(currentFacing));
  
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
  }
  RoboCtl::stepForth();

  return mode; //RoboState::areWeBackYet();
}

void RoboCtl::toggleMode() {
  if(!digitalRead(BUTTON)) {
	  switch(mode) {
	    case STOP: mode = SOLVE; break;
		case WAIT: mode = SEARCH; break;
		default: mode = ERROR;
	  }
  } else {
	  delay(50);
  }
}


void RoboCtl::turnRight() {
  Driver::turnRight();
  RoboState::turnRight();
  if(Driver::isWallChk(LEFT))
    Comms::snap(RoboCtl::getMapIndex(RoboState::getIndex()));
}

void RoboCtl::turnLeft() {
  Driver::turnLeft();
  RoboState::turnLeft();
  if(Driver::isWallChk(LEFT)) 
    Comms::snap(RoboCtl::getMapIndex(RoboState::getIndex()));
}

void RoboCtl::stepForth() {
  RoboState::step();
  if (mode == SEARCH){
    CrPath::setNextStep(RoboState::getIndex());
    if (RoboState::getIndex() != 0){
      Driver::goStraight();
    } else {
	  RoboState::turnBack();
	  RoboState::step();
	  RoboState::turnBack();
    }
    if(Driver::isWallChk(LEFT)){
      Comms::snap(RoboCtl::getMapIndex(RoboState::getIndex()));
    }
  } else if (mode == SOLVE) {
    stepCount++;
	Driver::goStraight();
  }
}


void RoboCtl::aboutFace() { 
  RoboCtl::turnLeft();
  RoboCtl::turnLeft();
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

int RoboCtl::getMode(){
  return mode;
}