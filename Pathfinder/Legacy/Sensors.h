#ifndef SENSORS
#define SENSORS

#include "DEFINES.h"
#include "DEFINES-TEST.h"

namespace Sensors {
    struct NoInit; //empty object used in overloaded function
	
    class Reflectance {
    public:
	  Reflectance();
	  Reflectance(NoInit);
	  int readCellSensor(unsigned int []);
	
	
	private:
      QTRSensorsRC qtrrc((unsigned char[]) {pins::LINE1, pins::LINE2, pins::LINE3, pins::LINE4, pins::LINE5, pins::LINE6},NUM_SENSORSLINE, TIMEOUT);
      QTRSensorsRC qtrrc1((unsigned char[]) {pins::LINE0, pins::LINE7}, NUM_SENSORSCELL, TIMEOUT);  
	  unsigned int sensorValuesLine[NUM_SENSORSLINE];
      unsigned int sensorValuesCell[NUM_SENSORSCELL];
  }
  
  class Pings {
    public:
      int isleftwallchk();
      int isrightwallchk();
      int isfrontwallchk();
  
    private:
      int isleftwall = 0;
      int isrightwall = 0;
      int isfrontwall = 0;
  
      iswall(int side);
  
  }
}


#endif