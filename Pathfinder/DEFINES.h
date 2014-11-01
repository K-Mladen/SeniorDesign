#ifndef DEFS
#define DEFS

#define TRUE 1
#define FALSE 0


enum {NORTH,WEST,SOUTH,EAST}
//#define NORTH 0
//#define SOUTH 2
//#define WEST 1
//#define EAST 3

enum {FORWARD, BACKWARD}

const int MAXPATHSIZE(50)
const int DEFAULTMAPSIZE(5)

#define Kp .030 // experiment to determine this, 
#define Kd 2 // experiment to determine this, slowly increase the speeds and adjust this value. (Note: Kp < Kd) 
#define rightMaxSpeed 105 // max speed of the robot
#define leftMaxSpeed 105 // max speed of the robot
#define rightBaseSpeed 79 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed 80  // this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORSLINE  6     // number of line sensors used
#define NUM_SENSORSCELL  2     // number of line sensors used
#define TIMEOUT       2000  // waits for 2500 us for sensor outputs to go low


//pins
namespace pins {


  const int 
    RIGHTMOTORPWM(3),LEFTMOTORBRAKE(8),RIGHTMOTORBRAKE(9),LEFTMOTORPWM(11),RIGHTMOTORDIR(12),LEFTMOTORDIR(13),
    FECHO(22),FTRIG(23),LECHO(24),LTRIG(25),RECHO(26),RTRIG(27),
    LINE0(30),LINE1(31),LINE2(32),LINE3(33),LINE4(34),LINE5(35),LINE6(36),LINE7(37);
}

	
#define rightMotordir pins::RIGHTMOTORDIR //12
#define rightMotorbrake pins::RIGHTMOTORBRAKE //9
#define rightMotorPWM pins::RIGHTMOTORPWM //3
#define leftMotordir pins::LEFTMOTORDIR //13
#define leftMotorbrake pins::LEFTMOTORBRAKE //8
#define leftMotorPWM pins::LEFTMOTORPWM //11


  
#define ftrigPin pins::FTRIG
#define fechoPin pins::FECHO
#define ltrigPin pins::LTRIG
#define lechoPin pins::LECHO
#define rtrigPin pins::RTRIG
#define rechoPin pins::RECHO



#define DEFINED_PINMODES \\
  pinMode(pins::FTRIG, OUTPUT); \\
  pinMode(pins::FECHO, INPUT); \\
  pinMode(pins::LTRIG, OUTPUT); \\
  pinMode(pins::LECHO, INPUT); \\
  pinMode(pins::RTRIG, OUTPUT); \\
  pinMode(pins::RECHO, INPUT); \\
  pinMode(pins::RIGHTMOTORDIR, OUTPUT); \\
  pinMode(pins::RIGHTMOTORBRAKE, OUTPUT); \\
  pinMode(pins::RIGHTMOTORPWM, OUTPUT); \\
  pinMode(pins::LEFTMOTORDIR, OUTPUT); \\
  pinMode(pins::LEFTMOTORBRAKE, OUTPUT); \\
  pinMode(pins::LEFTMOTORPWM, OUTPUT); \\

 namespace glob { 
/*
 QTRSensorsRC qtrrc((unsigned char[]) {pins::LINE1, pins::LINE2, pins::LINE3, pins::LINE4, pins::LINE5, pins::LINE6},NUM_SENSORSLINE, TIMEOUT);
QTRSensorsRC qtrrc1((unsigned char[]) {pins::LINE0, pins::LINE7}, NUM_SENSORSCELL, TIMEOUT);
unsigned int sensorValuesLine[NUM_SENSORSLINE];
unsigned int sensorValuesCell[NUM_SENSORSCELL];
*/

int cellcenter = 0;
}

#endif