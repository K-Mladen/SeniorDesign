
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

struct noInit {};


class Driver {
  public:
  Driver();
  Driver(noInit);
  ~Driver();
  void setup();
  
  int isCenteredChk(); //readCellSensor
  
  int isLeftWallChk();
  int isRightWallChk();
  int isFrontWallChk();
  
  void turnLeft();
  void turnRight();
  void goStraight();
  
  private:
  QTRSensorsRC qtrrc, qtrrc1;
  //int move(int dir);
  //int isWallChk(int dir);
  void PID_Drive();

  
  
  //from josh
  int isleftwall, isrightwall, isfrontwall, cellcenter;
  unsigned int sensorValuesLine[NUM_SENSORSLINE], sensorValuesCell[NUM_SENSORSCELL];
    unsigned int linesensors[6];
	int lastError;
	int position;
	int error;
	int motorSpeed;
	int rightMotorSpeed;
	int leftMotorSpeed;
	//int cellPosition;
	
	
	
};

#endif