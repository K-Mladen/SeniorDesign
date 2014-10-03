

#include "DEFINES.h"
#include "RoboState.h"

RoboState::RoboState(){
  setMapsize(DEFAULTMAPSIZE);
}
RoboState::RoboState(int m){
  setMapsize(m);
  entry = m*m;
  x = y = -1;
  
}
RoboState::~RoboState(){}

RoboState::setMapSize(int m) {
  n = m;
}

int RoboState::FirstSquare() {
  x = calX(entry);
  y = calY(entry);
  index = entry;
  return 0;
}


int RoboState::calX(int i) {
  x = (i-1)%n;
  return x;
}

int RoboState::calY(int i) {
  y = (i-1)/n;
  return y;
}

int RoboState::calIndex(int iX, int iY) {
  index = (iX * iY)++;
  return index;
}