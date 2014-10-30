
//Josh Wears' code, rebuilt into a class

#include <QTRSensors.h>
#include "Driver.h"
#include "DEFINES.h"




DEFINED_PINMODES //this is set up in DEFINES.h

Driver::Driver {
  // Sensor Calibration, Manual Calibration by moving line across sensors
  int i;
  for (i = 0; i < 250; i++){ // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead
    g::qtrrc.calibrate();   
    delay(20);
  }
  delay(2000); // wait for 2s to position the bot before entering the main loop 
}  


int lastError = 0;

void loop()
{   


g::cellcenter = readCellSensor();
  if(g::cellcenter == 1)
  {
  g::isleftwall = isleftwallchk();
  g::isfrontwall = isfrontwallchk();
  g::isrightwall = isrightwallchk();
  setCourse();
  }



  
  /*
  Serial.print(g::cellcenter);
  Serial.println();
  Serial.print(g::isleftwall);
  Serial.print(' '); 
  Serial.print(g::isrightwall);
  Serial.print(' '); 
  Serial.print(g::isfrontwall);
  Serial.print(' '); 
  Serial.println();
*/
  
  unsigned int linesensors[5];
  int position = g::qtrrc.readLine(linesensors); // get calibrated readings along with the line position
  int error = position - 2500;


  // PID Control
  int motorSpeed = Kp * error + Kd * (error - lastError); //Ki is not really needed for line following, Kd should be much bigger than Kp since the derivative of the error is much smaller than the error itself, so to be useful, it should be large
  lastError = error;
  int rightMotorSpeed = rightBaseSpeed + motorSpeed;
  int leftMotorSpeed = leftBaseSpeed - motorSpeed;


  if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed; // prevent the motor from going beyond max speed
  if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed; // prevent the motor from going beyond max speed
  if (rightMotorSpeed < 0) rightMotorSpeed = 0; // keep the motor speed positive
  if (leftMotorSpeed < 0) leftMotorSpeed = 0; // keep the motor speed positive

  {
    digitalWrite(rightMotordir, LOW);
    digitalWrite(rightMotorbrake, LOW);
    analogWrite(rightMotorPWM, rightMotorSpeed);
    digitalWrite(leftMotordir, HIGH);
    digitalWrite(leftMotorbrake, LOW);
    analogWrite(leftMotorPWM, leftMotorSpeed);
  }


} // Loop closing bracket



int readCellSensor()
{
  g::qtrrc1.read(sensorValuesCell);
  int cellposition = 0;
  
  for (unsigned char i = 0; i < NUM_SENSORSCELL; i++)
  {
    Serial.print(sensorValuesCell[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();
  
  if(sensorValuesCell[0] > 600 && sensorValuesCell[1] > 600)//if we are in the center of the cell, stop
  {
    
    analogWrite(rightMotorPWM, 0);
    analogWrite(leftMotorPWM, 0);    
    digitalWrite(rightMotordir, LOW);
    digitalWrite(rightMotorbrake, LOW);
    digitalWrite(leftMotordir, HIGH);
    digitalWrite(leftMotorbrake, LOW);
    delay(1000);
    
    cellposition = 1;
  }
 return cellposition;
}


int isleftwallchk(){
  //Tester code for ultrasonic sensor, NOTE - Pins have not been set!!!, consider for statement to take average
  long pinglefttime, pingleftdist;
  digitalWrite(ltrigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(ltrigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(ltrigPin, LOW);
  pinglefttime = pulseIn(lechoPin, HIGH);
  pingleftdist = (pinglefttime/2) / 29.1;
  /*
  if (pingleftdist < 4) {  
  }
  else {
  }
  if (pingleftdist >= 200 || pingleftdist <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(pingleftdist);
    Serial.println(" cm");
  }
*/
  if (pingleftdist > 10){
  
   return 0;
  }
 else
 {
    return 1;
  }
  
}


int isrightwallchk(){
  //Tester code for ultrasonic sensor, NOTE - Pins have not been set!!!, consider for statement to take average
  long pingrighttime, pingrightdist;
  digitalWrite(rtrigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(rtrigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(rtrigPin, LOW);
  pingrighttime = pulseIn(rechoPin, HIGH);
  pingrightdist = (pingrighttime/2) / 29.1;
  /*
  if (pingrightdist < 4) {  
  }
  else {
  }
  if (pingrightdist >= 200 || pingrightdist <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(pingrightdist);
    Serial.println(" cm");
  }
  */
  if (pingrightdist > 10){
  
   return 0;
  }
 else
 {
    return 1;
  }
  
}


int isfrontwallchk(){
  //Tester code for ultrasonic sensor, NOTE - Pins have not been set!!!, consider for statement to take average
  long pingfronttime, pingfrontdist;
  digitalWrite(ftrigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(ftrigPin, HIGH);
  delayMicroseconds(1000); 
  digitalWrite(ftrigPin, LOW);
  pingfronttime = pulseIn(fechoPin, HIGH);
  pingfrontdist = (pingfronttime/2) / 29.1;
  /*
  if (pingfrontdist < 4) {  
  }
  else {
  }
  if (pingfrontdist >= 200 || pingfrontdist <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(pingfrontdist);
    Serial.println(" cm");
  }
  */
  if (pingfrontdist > 10){
  
   return 0;
  }
 else
 {
    return 1;
  }
  
}


void turnleft()
 {
 digitalWrite(rightMotordir, LOW);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, 90);
 digitalWrite(leftMotordir, LOW);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, 85);
 delay(550);
  digitalWrite(rightMotordir, LOW);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, 85);
 digitalWrite(leftMotordir, HIGH);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, 85);
 delay(300);
 }



 void turnright()
 {
 digitalWrite(rightMotordir, HIGH);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, 110);
 digitalWrite(leftMotordir, HIGH);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, 95);
 delay(750);  
 digitalWrite(rightMotordir, HIGH);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, 95);
 digitalWrite(leftMotordir, HIGH);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, 95);
 delay(350); 
 }
 
 void gostraight()
 {
   return;
 }


 
 void turnaround()
 {
 digitalWrite(rightMotordir, LOW);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, 100);
 digitalWrite(leftMotordir, LOW);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, 100);
 delay(1400);   
 }

void setCourse()
{
    if(g::isleftwall == 0)
   {
   turnleft();
   }
   else if(g::isfrontwall == 0)
   {
   gostraight();
   }
   else if(g::isrightwall == 0)
   {
   turnright();
   }
   else
   {
   turnaround(); 
   }
 
}


