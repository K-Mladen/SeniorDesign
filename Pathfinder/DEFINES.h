#ifndef DEFS
#define DEFS



//Constants

#define LEFT 0
#define FRONT 1
#define RIGHT 2

#define NORTH 0
#define SOUTH 2
#define WEST 1
#define EAST 3

#define FORWARD 0
#define BACKWARD 1

#define SEARCH 0
#define DESTROY 1
#define SPIN 2

#define HIGH 1
#define LOW 0

#define FALSE 0
#define TRUE 1

#define LCD_COLS 16
#define LCD_ROWS 2

//Mladen's Constants
#define MAXPATHSIZE 50
#define DEFAULTMAPSIZE 5

//Chuck's Constants
#define DATARATE 9600

//Josh's Constants
#define Kp .090 // experiment to determine this, 
#define Kd 4 // experiment to determine this, slowly increase the speeds and adjust this value. (Note: Kp < Kd) 
#define rightMaxSpeed 250 // max speed of the robot
#define leftMaxSpeed 250 // max speed of the robot
#define rightBaseSpeed 225 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed 225  // this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORSLINE  6     // number of line sensors used
#define NUM_SENSORSCELL  2     // number of line sensors used
#define TIMEOUT       2000  // waits for 2500 us for sensor outputs to go low


//Pin Numbers

#define LCD_RS 2
#define LCD_EN 3
#define LCD_D0 4
#define LCD_D1 5
#define LCD_D2 6
#define LCD_D3 7

#define CAMERA_PULSE 20

#define RC_0 30
#define RC_1 31
#define RC_2 32
#define RC_3 33
#define RC_4 34
#define RC_5 35
#define RC_6 36
#define RC_7 37

#define rightMotordir 42
#define rightMotorbrake 9
#define rightMotorPWM 44
#define leftMotordir 43
#define leftMotorbrake 8 
#define leftMotorPWM 45

#define ftrigPin 50
#define fechoPin 51

#define ltrigPin 52
#define lechoPin 53

#define rtrigPin 48
#define rechoPin 49

#define LED_Done 13

#endif