#include <CriticalPath.h>
#include <DEFINES-TEST.h>
#include <DEFINES.h>
#include <RoboCtl.h>
#include <RoboState.h>

//TESTCODE FOR ROBOSTATE.H BY MLADEN KOJIC ON OCTOBER 3 2014

namespace g {
  crPath road;
  RoboState toro(5);
  int it = 0;
  int list[] = TESTCP;
  int nextstep = 0;
  int nextX = 0;
  int nextY = 0;
  int currX = 0;
  int currY = 0;
}

void setup(){
  Serial.begin(9600);
  Serial.println(" ");
  Serial.print("Critical Path: ");
  for(g::it = 0; g::list[g::it]>0; g::it++) {
    g::road.setNextStep(g::list[g::it]);
    Serial.print(g::road.getNextStep(g::it));
    Serial.print(" ");
  }
  Serial.println("End");
  g::it = 0;
  
  g::nextstep = g::road.getNextStep(g::it);
  Writeitall();
  g::toro.step();
  g::nextX = g::toro.getX(g::nextstep);
  g::nextY = g::toro.getY(g::nextstep);
  g::it++;
}

void loop(){
  g::currX = g::nextX;
  g::currY = g::nextY;
  g::nextstep = g::road.getNextStep(g::it);
  Writeitall();
  g::nextX = g::toro.getX(g::nextstep);
  g::nextY = g::toro.getY(g::nextstep);
  if(g::nextX == g::currX) {
    if (g::nextY < g::currY) { //need to go north
      if (g::toro.getFacing() == EAST) {
        g::toro.turnLeft();
      } else if (g::toro.getFacing() == WEST) {
        g::toro.turnRight();
      } else if (g::toro.getFacing() == SOUTH) {
        g::toro.turnBack();
      }
      g::toro.step();
    } else if (g::nextY > g::currY) { //need to go south
      if (g::toro.getFacing() == WEST) {
        g::toro.turnLeft();
      } else if (g::toro.getFacing() == EAST) {
        g::toro.turnRight();
      } else if (g::toro.getFacing() == NORTH) {
        g::toro.turnBack();
      }
      g::toro.step();
    } else {
      Serial.println("ERROR Next Step is Current Step NS");
    }
  } else if (g::nextY == g::currY) {
    if (g::nextX < g::currX) { //need to go EAST
      if (g::toro.getFacing() == SOUTH) {
        g::toro.turnLeft();
      } else if (g::toro.getFacing() == NORTH) {
        g::toro.turnRight();
      } else if (g::toro.getFacing() == WEST) {
        g::toro.turnBack();
      }
      g::toro.step();
    } else if (g::nextX > g::currX) { //need to go WEST
      if (g::toro.getFacing() == NORTH) {
        g::toro.turnLeft();
      } else if (g::toro.getFacing() == SOUTH) {
        g::toro.turnRight();
      } else if (g::toro.getFacing() == EAST) {
        g::toro.turnBack();
      }
      g::toro.step();
    } else {
      Serial.println("ERROR Next Step is Current Step EW");
      Serial.print("nexty ");
      Serial.print(g::nextY);
      Serial.print(" curry ");
      Serial.print(g::currY);
      Serial.print(" nextx ");
      Serial.print(g::nextX);
      Serial.print(" currx ");
      Serial.println(g::currX);
    }
  }
        
  g::it++;
  while(g::it>11){}
  
}

void Writeitall(){
  Serial.print("Facing: ");
  Serial.print(g::toro.getFacing());
  Serial.print(" X: ");
  Serial.print(g::toro.getX());
  Serial.print(" Y: ");
  Serial.print(g::toro.getY());
  Serial.print(" Index: ");
  Serial.println(g::toro.getIndex());
  Serial.print("Next Step: ");
  Serial.println(g::nextstep);


}
