
/*
init RC's

are we in cellcenter ? -- RoboCtl

PID_Drive

int readCellSensor() T/F Cell Center

int is(N)wallchk()  T/F

void turn(N)()

void gostraight
*/

#ifndef DRIVER
#define DRIVER

#include <QTRSensors.h>
#include "DEFINES.h"
#include "DEFINES-TEST.h"

class Driver {
  public:
  Driver();
  ~Driver();
  
  byte isCenteredChk(); //readCellSensor
  
  byte isLeftWallChk();
  byte isRightWallChk();
  byte isFrontWallChk();
  
  void turnLeft();
  void turnRight();
  void goStraight();
  
  private:
  //byte move(byte dir);
  //byte isWallChk(byte dir);
  void PID_Drive();
  
  int isleftwall(0), isrightwall(0), isfrontwall(0), cellcenter(0)
  unsigned int sensorValuesLine[NUM_SENSORSLINE], sensorValuesCell[NUM_SENSORSCELL]
}

#endif