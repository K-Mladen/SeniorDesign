#include <QTRSensors.h>
#include "DEFINES.h"
#include "DEFINES-TEST.h"
#include "Driver.h"
#include "Arduino.h"


Driver::Driver(){
  setup();
}

Driver::Driver(noInit i) {}
Driver::~Driver(){}

void Driver::setup(){
  cellcenter = 0;
  lastError = 0;
  qtrrc.init((unsigned char[]) {RC_1, RC_2, RC_3, RC_4, RC_5, RC_6},NUM_SENSORSLINE, TIMEOUT);
  qtrrc1.init((unsigned char[]) {RC_0, RC_7}, NUM_SENSORSCELL, TIMEOUT);
    int i;
  for (int i = 0; i < 250; i++){ // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead
    qtrrc.calibrate();   
    delay(20);
  }
}

int Driver::isCenteredChk(){ 
  qtrrc1.read(sensorValuesCell);
  if(sensorValuesCell[0] > 800 && sensorValuesCell[1] > 800)//if we are in the center of the cell, stop
  {
    
    //stop();
    
    return 1;
  } else return 0;
}
 
int Driver::isWallChk(int side){
  static const int trig[] = {ltrigPin,ftrigPin,rtrigPin};
  static const int echo[] = {lechoPin,fechoPin,rechoPin};
  static const int AVE_COUNT = 1;
  static int it = 0;
  digitalWrite(trig[side], LOW); 
  pingtime = 0;
  for(it=0;it<AVE_COUNT;it++){
    delayMicroseconds(2);
    digitalWrite(trig[side], HIGH);
    delayMicroseconds(10);
    digitalWrite(trig[side], LOW);
    pingtime += pulseIn(echo[side], HIGH);
  }	
  pingdist = (pingtime/2) / 29.1;
  return (pingdist < 15*AVE_COUNT);
}

void Driver::turnLeft(){
 digitalWrite(rightMotordir, HIGH);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, rightMaxSpeed);
 digitalWrite(leftMotordir, LOW);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, leftMaxSpeed);
 delay(450);
}

void Driver::turnRight(){
 digitalWrite(rightMotordir, LOW);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, rightMaxSpeed);
 digitalWrite(leftMotordir, HIGH);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, leftMaxSpeed);
 delay(450);
}

void Driver::goStraight(){
  digitalWrite(rightMotordir, HIGH);
  digitalWrite(rightMotorbrake, LOW);
  analogWrite(rightMotorPWM, rightMaxSpeed);
  digitalWrite(leftMotordir, HIGH);
  digitalWrite(leftMotorbrake, LOW);
  analogWrite(leftMotorPWM, leftMaxSpeed);
  delay(500); 
  time = millis();
  while(!isCenteredChk()){ 
	PID_Drive();
	if (millis() > time + 2000) {
		  digitalWrite(rightMotordir, HIGH);
          digitalWrite(rightMotorbrake, LOW);
          analogWrite(rightMotorPWM, rightMaxSpeed);
          digitalWrite(leftMotordir, HIGH);
          digitalWrite(leftMotorbrake, LOW);
          analogWrite(leftMotorPWM, leftMaxSpeed);
          delay(500);
		  time = millis();
	}
  }
}

void Driver::PID_Drive(){
  position = qtrrc.readLine(linesensors); // get calibrated readings along with the line position
  error = position - 2500;
  motorSpeed = Kp * error + Kd * (error - lastError); //Ki is not really needed for line following, Kd should be much bigger than Kp since the derivative of the error is much smaller than the error itself, so to be useful, it should be large
  lastError = error;
  rightMotorSpeed = rightBaseSpeed + motorSpeed;
  leftMotorSpeed = leftBaseSpeed - motorSpeed;
  
   if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
   if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
   if (rightMotorSpeed < 0) rightMotorSpeed = 0; // keep the motor speed positive
   if (leftMotorSpeed < 0) leftMotorSpeed = 0; // keep the motor speed positive

  
  digitalWrite(rightMotordir, HIGH);
  digitalWrite(rightMotorbrake, LOW);
  analogWrite(rightMotorPWM, rightMotorSpeed);
  digitalWrite(leftMotordir, HIGH);
  digitalWrite(leftMotorbrake, LOW);
  analogWrite(leftMotorPWM, leftMotorSpeed); 
}

void Driver::stop(){
    analogWrite(rightMotorPWM, 0);
    analogWrite(leftMotorPWM, 0);    
    digitalWrite(rightMotordir, LOW);
    digitalWrite(rightMotorbrake, LOW);
    digitalWrite(leftMotordir, HIGH);
    digitalWrite(leftMotorbrake, LOW);
}