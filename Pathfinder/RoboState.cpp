

#include "DEFINES.h"
#include "RoboState.h"
#include "Arduino.h"


//-----------------------\\
//--------PUBLIC---------\\
//-----------------------\\

RoboState::RoboState(){
  setMapSize(DEFAULTMAPSIZE);
  entry = DEFAULTMAPSIZE*DEFAULTMAPSIZE-DEFAULTMAPSIZE+1;
  index = x = y = -1;
  facing = NORTH;
}

RoboState::RoboState(int m){
  setMapSize(m);
  entry = m*m-m+1;
  index = x = y = -1;
  facing = NORTH;
}

RoboState::~RoboState(){}

int RoboState::step(){
  if (index < 0){
    return firstSquare();
  }
  
  do {  
	if        (facing == NORTH) {
      y--;
    } else if (facing == SOUTH) {
      y++;
	} else if (facing == WEST) {
      x++;
	} else if (facing == EAST) {
	  x--;
	}
  } while(facingAdj());
    index = calIndex(x,y);
	/* Serial.print("Current x ");
	Serial.print(x);
	Serial.print(" || Current y ");
	Serial.println(y);
	 */return index;
}

void RoboState::turnRight() {
  switch (facing) {
    case NORTH:
      facing = WEST;
      break;
    case EAST:
      facing = NORTH;
      break;
    case SOUTH:
      facing = EAST;
      break;
    case WEST:
	  facing = SOUTH;
	  break;
  }
  
//  facing = facing - NORTH + EAST; //assume facing NORTH, turning right will make you face EAST -- this allows for the numbers to be changed later
  //facingAdj(); //put facing within 0=<x<4
}

void RoboState::turnLeft() {
  switch (facing) {
    case NORTH:
	  facing = EAST;
	  break;
	case EAST:
	  facing = SOUTH;
	  break;
	case SOUTH:
	  facing = WEST;
	  break;
	case WEST:
	  facing = NORTH;
	  break;
    }
  //facing = facing - NORTH + WEST; //assume facing NORTH, turning left will make you face WEST -- this allows for the numbers to be changed later
//  facingAdj(); //put facing within 0=<x<4
}

void RoboState::turnBack() {
    switch (facing) {
    case NORTH:
	  facing = SOUTH;
	  break;
	case EAST:
	  facing = WEST;
	  break;
	case SOUTH:
	  facing = NORTH;
	  break;
	case WEST:
	  facing = EAST;
	  break;
    }
  //facing = facing - NORTH + SOUTH; //assume facing NORTH, turning back will make you face SOUTH -- this allows for the numbers to be changed later
  //facingAdj(); //put facing within 0=<x<4
}

int RoboState::areWeBackYet(){
  return (index == entry && facing == NORTH);
}

int RoboState::getX() {
  return x;
}

int RoboState::getX(int i) {
  return calX(i);
}

int RoboState::getY() {
  return y;
}

int RoboState::getY(int i) {
  return calY(i);
}

int RoboState::getIndex() {
  return index;
}

int RoboState::getFacing() {
  return facing;
}

int RoboState::getMapSize(){
  return n;
}




//------------------------\\
//--------PRIVATE---------\\
//------------------------\\



int RoboState::calX(int i) {
  return (i-1)%n;
}

int RoboState::calY(int i) {
  return (int)((i-1)/n);
}

int RoboState::calIndex(int iX, int iY) {
  return (1 + iX + iY*n);
}

bool RoboState::facingAdj() {
  if        (facing>3) {
    facing%=4;
	return true;
  } else if (facing < 0) {
    facing = 4 - ((0 - facing)%4);
	return true;
  } else {
  return false;
  }
}

int RoboState::firstSquare() {
  x = calX(entry);
  y = calY(entry);
  index = entry;
  return index;
}

void RoboState::setMapSize(int m) {
  n = m;
}