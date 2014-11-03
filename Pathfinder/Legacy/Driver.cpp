#include "Defines.h"
#include "DEFINES-TEST.h"
#include "Driver.h"



//construct
Driver::Driver() {
}

Driver::~Driver(){
}

int turnRight() {
  return move(BACKWARD,FORWARD);
}

int turnLeft(){
  return move(FORWARD,BACKWARD);
}
  
int turnAround(){
  int rval(0);
  rval = move(BACKWARD,FORWARD);
  rval *= move(BACKWARD,FORWARD);
  return rval;
}

int goStraight(){
  return move(FORWARD,BACKWARD);
}

int move(int lMDir, int rMDir) {
  int timer(0);
  byte lline(0), rline(0);
  //adjust MDir's -- FORWARD/BACKWARD to HIGH/LOW respectively
  #ifdef ERRMSG
    ErrMsg = (rMDir != FORWARD || rMDir != BACKWARD) ? 
				"rMDir set as neither FORWARD nor Backward" : 
				NULL;
    if (ErrMsg) logErrState();
	ErrMsg = (lMDir != FORWARD && lMDir != BACKWARD) ? 
				"lMDir set as neither FORWARD NOR BACKWARD" : 
				NULL;
	if (ErrMsg) logErrState();
  #endif
  
  digitalWrite(rightMotorDir,rMDir == FORWARD ? HIGH : LOW);
  digitalWrite(leftMotorDir,lMDir == FORWARD ? HIGH : LOW);
  digitalWrite(leftMotorPWM,LEFT_MOTOR_PWM_BASE);
  digitalWrite(rightMotorPWM,RIGHT_MOTOR_PWM_BASE);
  timer = millis();
  do {
    lline = (lline||poll(LEFT))
	rline = (rline||poll(RIGHT));
  }  while(millis() < timer + 500 && lline + rline < 2);
  
  //stop motors
  digitalWrite(rightMotorPWM,0);
  digitalWrite(leftMotorPWM,0);
  
  return (lline && rline); //returns 1 if turn is confirmed, 0 if timer based
}

  
}