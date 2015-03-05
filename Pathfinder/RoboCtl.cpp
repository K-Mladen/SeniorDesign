
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

#ifdef LCD_CONNECTED
RoboCtl::RoboCtl()  : LiquidCrystal::LiquidCrystal(static_cast<uint8_t>(LCD_RS),static_cast<uint8_t>(LCD_EN),
	                          static_cast<uint8_t>(LCD_D0),static_cast<uint8_t>(LCD_D1),static_cast<uint8_t>(LCD_D2),static_cast<uint8_t>(LCD_D3)) {
  RoboCtl::setup();
}
#else
RoboCtl::RoboCtl() {
  RoboCtl::setup();
}
#endif

//RoboCtl::RoboCtl(noInit i) {}

RoboCtl::~RoboCtl() {}


void RoboCtl::setup() {
  stepCount = 1;
  mode = SEARCH;
  #ifdef SERIAL_MODE
  Serial.println("RoboCtl Setup");
  #endif
  #ifdef LCD_CONNECTED  
  LiquidCrystal::begin(LCD_COLS,LCD_ROWS);
  LiquidCrystal::setCursor(0,0);
  LiquidCrystal::print((mode==SEARCH)?"SEARCH  ":"DESTROY ");
  #endif
  #ifdef SERIAL_MODE
  Serial.println("Done RoboCtl Setup");
  #endif
}

void RoboCtl::setCourse() {
  //int r;
  Serial.print("Mode "); Serial.println((mode == SEARCH)?"Search":"Nonsearch");
  if(mode == SEARCH) { 
    if(!Driver::isWallChk(LEFT)) { 
      #ifdef LCD_CONNECTED
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print("    LEFT");
	  #endif
	  #ifdef SERIAL_MODE
      Serial.println("left nowall");
      #endif
	  RoboCtl::turnLeft();
	  RoboCtl::stepForth();
	 // r = WEST;
	  } else if (!Driver::isWallChk(FRONT)) {
      #ifdef LCD_CONNECTED
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print(" FORWARD");
	  #endif
	  #ifdef SERIAL_MODE
      Serial.println("front nowall");
      #endif
	  RoboCtl::stepForth();
	  //r = NORTH;
	  } else if (!Driver::isWallChk(RIGHT)) {
      #ifdef LCD_CONNECTED
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print("   RIGHT");
	  #endif
	  #ifdef SERIAL_MODE
      Serial.println("right nowall");
      #endif
	  RoboCtl::turnRight();
	  RoboCtl::stepForth();
	//  r = EAST;
	  } else {
      #ifdef LCD_CONNECTED
	  LiquidCrystal::setCursor(8,1);
      LiquidCrystal::print("    BACK");
	  #endif
	  #ifdef SERIAL_MODE
      Serial.println("allwalls");
      #endif
	  RoboCtl::aboutFace();
	  RoboCtl::stepForth();
	//  r = SOUTH;
	  }
	  if (CrPath::getCompletionState()) mode = SPIN;
  } else if (mode == SPIN){
	  RoboCtl::aboutFace();
  } else {
    RoboCtl::nextAction();
	//r = -1;
  }
  
  #ifdef LCD_CONNECTED
  LiquidCrystal::setCursor(8,0);
  LiquidCrystal::print("SQUARE   ");
  LiquidCrystal::setCursor(15,0);
  LiquidCrystal::print(String(RoboState::getIndex()));
  #endif
  
  #ifdef SERIAL_MODE
  Serial.print("square ");
  Serial.println(RoboState::getIndex());
  #endif
  
  return; //RoboState::areWeBackYet();
}

void RoboCtl::toggleMode() {
  mode=(mode!=SEARCH)?SEARCH:DESTROY;  
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
  Driver::goStraight();
  RoboState::step();
  if(Driver::isWallChk(LEFT))
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
  currentFacing = RoboState::getFacing();
  nextFacing = RoboCtl::getNextFacing();
  if(currentFacing == nextFacing){
    #ifdef LCD_CONNECTED
	LiquidCrystal::setCursor(8,1);
    LiquidCrystal::print(" FORWARD");
	#endif
    RoboCtl::stepForth();
  } else if((currentFacing == NORTH && nextFacing == EAST) ||
			(currentFacing == EAST && nextFacing == SOUTH) ||
			(currentFacing == SOUTH && nextFacing == WEST) ||
			(currentFacing == WEST && nextFacing == NORTH) ){
    #ifdef LCD_CONNECTED
	LiquidCrystal::setCursor(8,1);
    LiquidCrystal::print("   RIGHT");
	#endif
    RoboCtl::turnRight();
  } else if((currentFacing == NORTH && nextFacing == WEST) ||
            (currentFacing == WEST && nextFacing == SOUTH) ||
			(currentFacing == SOUTH && nextFacing == EAST) ||
			(currentFacing == EAST && nextFacing == NORTH) ){
	#ifdef LCD_CONNECTED
	LiquidCrystal::setCursor(8,1);
    LiquidCrystal::print("    LEFT");		
	#endif
	RoboCtl::turnLeft();
  } else if((currentFacing == NORTH && nextFacing == SOUTH) ||
            (currentFacing == SOUTH && nextFacing == NORTH) ||
			(currentFacing == EAST && nextFacing == WEST) ||
			(currentFacing == WEST && nextFacing == EAST) ){
    #ifdef LCD_CONNECTED
	LiquidCrystal::setCursor(8,1);
    LiquidCrystal::print("    BACK");
	#endif
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

