#ifndef DEFS
#define DEFS




enum {NORTH,WEST,SOUTH,EAST};
enum {LEFT=0,FRONT=1,RIGHT=2};
//#define NORTH 0
//#define SOUTH 2
//#define WEST 1
//#define EAST 3

enum {FORWARD, BACKWARD};
enum {SEARCH,DESTROY,SPIN};
//enum {HIGH = 1, LOW = 0};
enum {FALSE = 0, TRUE = 1};
#define LCD_COLS 16
#define LCD_ROWS 2

#define MAXPATHSIZE 50
#define DEFAULTMAPSIZE 5

#define Kp .090 // experiment to determine this, 
#define Kd 4 // experiment to determine this, slowly increase the speeds and adjust this value. (Note: Kp < Kd) 
#define rightMaxSpeed 250 // max speed of the robot
#define leftMaxSpeed 250 // max speed of the robot
#define rightBaseSpeed 225 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed 225  // this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORSLINE  6     // number of line sensors used
#define NUM_SENSORSCELL  2     // number of line sensors used
#define TIMEOUT       2000  // waits for 2500 us for sensor outputs to go low



#define LCD_RS 2
#define LCD_EN 3
#define LCD_D0 4
#define LCD_D1 5
#define LCD_D2 6
#define LCD_D3 7

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

#define LED_Done 10

#endif