#include <QTRSensors.h>
#include "DEFINES.h"
#include "DEFINES-TEST.h"
#include "Driver.h"
#include "Arduino.h"


//all global variables, defines here --I'll put them where they need to go



//END of globals

Driver::Driver(){
  setup();
}

Driver::Driver(noInit i) {}
Driver::~Driver(){}

void Driver::setup(){
  isleftwall = 0;
  isrightwall = 0;
  isfrontwall = 0;
  cellcenter = 0;
  lastError = 0;
  qtrrc.init((unsigned char[]) {31, 32, 33, 34, 35, 36},NUM_SENSORSLINE, TIMEOUT);
  qtrrc1.init((unsigned char[]) {30, 37}, NUM_SENSORSCELL, TIMEOUT);
    int i;
  for (int i = 0; i < 250; i++){ // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead
    qtrrc.calibrate();   
    delay(20);
  }
}

int Driver::isCenteredChk(){ 
  //aka readCellSensor
  qtrrc1.read(sensorValuesCell);
/*  
  for (unsigned char i = 0; i < NUM_SENSORSCELL; i++)
  {
    Serial.print("SensorValues");
    Serial.print(sensorValuesCell[i]);
    Serial.print(' '); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();
  */
  if(sensorValuesCell[0] > 800 && sensorValuesCell[1] > 800)//if we are in the center of the cell, stop
  {
    
    analogWrite(rightMotorPWM, 0);
    analogWrite(leftMotorPWM, 0);    
    digitalWrite(rightMotordir, LOW);
    digitalWrite(rightMotorbrake, LOW);
    digitalWrite(leftMotordir, HIGH);
    digitalWrite(leftMotorbrake, LOW);
    //delay(150);
    
    return 1;
  } else return 0;
 //return cellPosition;
}
  
int Driver::isLeftWallChk(){
    //Tester code for ultrasonic sensor, NOTE - Pins have not been set!!!, consider for statement to take average
  long pinglefttime, pingleftdist;
  digitalWrite(ltrigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(ltrigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(ltrigPin, LOW);
  pinglefttime = pulseIn(lechoPin, HIGH);
  pingleftdist = (pinglefttime/2) / 29.1;
  
  if (pingleftdist < 10){
  
    return 1;
  }
  else
  {
    return 0;
  }
}  
 
int Driver::isRightWallChk(){
//Tester code for ultrasonic sensor, NOTE - Pins have not been set!!!, consider for statement to take average
  long pingrighttime, pingrightdist;
  digitalWrite(rtrigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(rtrigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(rtrigPin, LOW);
  pingrighttime = pulseIn(rechoPin, HIGH);
  pingrightdist = (pingrighttime/2) / 29.1;
  
  if (pingrightdist < 10){
  
   return 1;
  }
  else
  {
    return 0;
  }
}

int Driver::isFrontWallChk(){
  long pingfronttime, pingfrontdist;
  digitalWrite(ftrigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(ftrigPin, HIGH);
  delayMicroseconds(1000); 
  digitalWrite(ftrigPin, LOW);
  pingfronttime = pulseIn(fechoPin, HIGH);
  pingfrontdist = (pingfronttime/2) / 29.1;

  
  if (pingfrontdist < 10){
  
   return 1;
  }
 else
 {
    return 0;
  }
}

void Driver::turnLeft(){
 digitalWrite(rightMotordir, HIGH);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, 150);
 digitalWrite(leftMotordir, LOW);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, 150);
 delay(900);
}

void Driver::turnRight(){
 digitalWrite(rightMotordir, LOW);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, 150);
 digitalWrite(leftMotordir, HIGH);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, 150);
 delay(900);
}

void Driver::goStraight(){
  digitalWrite(rightMotordir, HIGH);
  digitalWrite(rightMotorbrake, LOW);
  analogWrite(rightMotorPWM, 150);
  digitalWrite(leftMotordir, HIGH);
  digitalWrite(leftMotorbrake, LOW);
  analogWrite(leftMotorPWM, 150);
  delay(500); 
 
  while(!isCenteredChk()){ 
	PID_Drive();
  }
}

void Driver::PID_Drive(){
  //Serial.print("PID Call: ");
  //Serial.println(millis());
  position = qtrrc.readLine(linesensors); // get calibrated readings along with the line position
  error = position - 2500;
  motorSpeed = Kp * error + Kd * (error - lastError); //Ki is not really needed for line following, Kd should be much bigger than Kp since the derivative of the error is much smaller than the error itself, so to be useful, it should be large
  lastError = error;
  rightMotorSpeed = rightBaseSpeed + motorSpeed;
  leftMotorSpeed = leftBaseSpeed - motorSpeed;
  
  Serial.print(linesensors[0]);
  Serial.print(" ");
  Serial.print(linesensors[1]);
  Serial.print(" ");
  Serial.print(linesensors[2]);
  Serial.print(" ");
  Serial.print(linesensors[3]);
  Serial.print(" ");
  Serial.print(linesensors[4]);
  Serial.print(" ");
  Serial.print(linesensors[5]);
  Serial.print(" ");
  Serial.print(linesensors[6]);
  Serial.println(" ");
  
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