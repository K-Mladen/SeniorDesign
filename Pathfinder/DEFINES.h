#ifndef DEFS
#define DEFS

#define TRUE 1
#define FALSE 0


enum card {NORTH,WEST,SOUTH,EAST}
//#define NORTH 0
//#define SOUTH 2
//#define WEST 1
//#define EAST 3

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
    FECHOPIN(22),FTRIGPIN(23),LECHOPIN(24),LTRIGPIN(25),RECHOPIN(26),RTRIGPIN(27),
    LINE0(30),LINE1(31),LINE2(32),LINE3(33),LINE4(34),LINE5(35),LINE6(36),LINE7(37);
  
#define rightMotordir pins::RIGHTMOTORDIR //12
#define rightMotorbrake pins::RIGHTMOTORBRAKE //9
#define rightMotorPWM pins::RIGHTMOTORPWM //3
#define leftMotordir pins::LEFTMOTORDIR //13
#define leftMotorbrake pins::LEFTMOTORBRAKE //8
#define leftMotorPWM pins::LEFTMOTORPWM //11


  
#define ftrigPin pins::FTRIGPIN
#define fechoPin pins::FECHOPIN
#define ltrigPin pins::LTRIGPIN
#define lechoPin pins::LECHOPIN
#define rtrigPin pins::RTRIGPIN
#define rechoPin pins::RECHOPIN

}

#endif