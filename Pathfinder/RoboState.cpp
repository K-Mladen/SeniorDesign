

#include "DEFINES.h"
#include "RoboState.h"


//-----------------------\\
//--------PUBLIC---------\\
//-----------------------\\

RoboState::RoboState(){
  setMapsize(DEFAULTMAPSIZE);
}

RoboState::RoboState(int m){
  setMapsize(m);
  entry = m*m;
  x = y = -1;
  
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
      x--;
	} else if (facing == EAST) {
	  x++;
	}
  } while(facingAdj());
    calIndex();
	return index;
}

void turnRight() {
  facing = facing - NORTH + EAST; //assume facing NORTH, turning right will make you face EAST -- this allows for the numbers to be changed later
  facingadj(); //put facing within 0=<x<4
}

void turnLeft() {
  facing = facing - NORTH + WEST; //assume facing NORTH, turning left will make you face WEST -- this allows for the numbers to be changed later
  facingadj(); //put facing within 0=<x<4
}

void turnBack() {
  facing = facing - NORTH + SOUTH; //assume facing NORTH, turning back will make you face SOUTH -- this allows for the numbers to be changed later
  facingadj(); //put facing within 0=<x<4
}

int RoboState::getX() {
  return x;
}

int RoboState::getY() {
  return y;
}

int RoboState::getIndex() {
  return index;
}

//------------------------\\
//--------PRIVATE---------\\
//------------------------\\



void RoboState::calX(int i) {
  return (i-1)%n;
}

void RoboState::calY(int i) {
  return (int)((i-1)/n);
}

void RoboState::calIndex(int iX, int iY) {
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

int RoboState::FirstSquare() {
  x = calX(entry);
  y = calY(entry);
  index = entry;
  return index;
}

void RoboState::setMapSize(int m) {
  n = m;
}