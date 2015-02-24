
#include <QTRSensors.h>

#define Kp .090 // experiment to determine this, 
#define Kd 4 // experiment to determine this, slowly increase the speeds and adjust this value. (Note: Kp < Kd) 
#define rightMaxSpeed 250 // max speed of the robot
#define leftMaxSpeed 250 // max speed of the robot
#define rightBaseSpeed 225 // this is the speed at which the motors should spin when the robot is perfectly on the line
#define leftBaseSpeed 225  // this is the speed at which the motors should spin when the robot is perfectly on the line
#define NUM_SENSORSLINE  6     // number of line sensors used
#define NUM_SENSORSCELL  2     // number of line sensors used
#define TIMEOUT       2000  // waits for 2500 us for sensor outputs to go low

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

QTRSensorsRC qtrrc((unsigned char[]) {31, 32, 33, 34, 35, 36},NUM_SENSORSLINE, TIMEOUT);
QTRSensorsRC qtrrc1((unsigned char[]) {30, 37}, NUM_SENSORSCELL, TIMEOUT);
unsigned int sensorValuesLine[NUM_SENSORSLINE];
unsigned int sensorValuesCell[NUM_SENSORSCELL];
int isleftwall = 0;
int isrightwall = 0;
int isfrontwall = 0;
int cellcenter = 0;
int lastError = 0;


void setup()
{
  pinMode(ftrigPin, OUTPUT);
  pinMode(fechoPin, INPUT);
  pinMode(ltrigPin, OUTPUT);
  pinMode(lechoPin, INPUT);
  pinMode(rtrigPin, OUTPUT);
  pinMode(rechoPin, INPUT);
  pinMode(rightMotordir, OUTPUT);
  pinMode(rightMotorbrake, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotordir, OUTPUT);
  pinMode(leftMotorbrake, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);


  // Sensor Calibration, Manual Calibration by moving line across sensors
  int i;
  for (int i = 0; i < 250; i++){ // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead
    qtrrc.calibrate();   
    delay(20);
  }
  delay(2000); // wait for 2s to position the bot before entering the main loop 
  Serial.begin(9600);

}



void loop()
{   


cellcenter = readCellSensor();
  if(cellcenter == 1)
  {
  isleftwall = isleftwallchk();
  isfrontwall = isfrontwallchk();
  isrightwall = isrightwallchk();
  setCourse();
  }


  
  unsigned int linesensors[5];
  int position = qtrrc.readLine(linesensors); // get calibrated readings along with the line position
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
    digitalWrite(rightMotordir, HIGH);
    digitalWrite(rightMotorbrake, LOW);
    analogWrite(rightMotorPWM, rightMotorSpeed);
    digitalWrite(leftMotordir, HIGH);
    digitalWrite(leftMotorbrake, LOW);
    analogWrite(leftMotorPWM, leftMotorSpeed);
  }



} // Loop closing bracket


int readCellSensor()
{
  qtrrc1.read(sensorValuesCell);
  int cellposition = 0;
  
  for (unsigned char i = 0; i < NUM_SENSORSCELL; i++)
  {
    Serial.print(sensorValuesCell[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
  Serial.println();
  
  if (sensorValuesCell[0] < 300 && sensorValuesCell[1] < 300 && sensorValuesCell[2] < 300 && sensorValuesCell[3] < 300 && sensorValuesCell[4] < 300 && sensorValuesCell[5] < 300 && 
      sensorValuesCell[6] < 300 && sensorValuesCell[7] <300)
      gostraight(); 
  else if(sensorValuesCell[0] > 800 && sensorValuesCell[1] > 800)//if we are in the center of the cell, stop
  {
    
    analogWrite(rightMotorPWM, 0);
    analogWrite(leftMotorPWM, 0);    
    digitalWrite(rightMotordir, LOW);
    digitalWrite(rightMotorbrake, LOW);
    digitalWrite(leftMotordir, HIGH);
    digitalWrite(leftMotorbrake, LOW);
    delay(150);
    
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
  if (pingleftdist < 10){
  
   return 1;
  }
 else
 {
    return 0;
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
  if (pingrightdist < 10){
  
   return 1;
  }
 else
 {
    return 0;
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
  if (pingfrontdist < 10){
  
   return 1;
  }
 else
 {
    return 0;
  }
  
}


void turnleft()
 {
 digitalWrite(rightMotordir, HIGH);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, 150);
 digitalWrite(leftMotordir, LOW);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, 150);
 delay(850);
 }



 void turnright()
 {

 digitalWrite(rightMotordir, LOW);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, 150);
 digitalWrite(leftMotordir, HIGH);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, 150);
 delay(850);
 }
 
 void gostraight()
 {
 digitalWrite(rightMotordir, HIGH);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, 150);
 digitalWrite(leftMotordir, HIGH);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, 150);
 delay(500); 
   return;
 }


  void turnaround()
 {
 digitalWrite(rightMotordir, LOW);
 digitalWrite(rightMotorbrake, LOW);
 analogWrite(rightMotorPWM, 150);
 digitalWrite(leftMotordir, HIGH);
 digitalWrite(leftMotorbrake, LOW);
 analogWrite(leftMotorPWM, 150);
 delay(1700);  
 }


void setCourse()
{
    if(isrightwall == 0)
   {
   turnright();
   gostraight();
   return;
   }
   else if(isfrontwall == 0)
   {
   gostraight();
   return;
   }
   else if(isleftwall == 0)
   {
   turnleft();
   gostraight();
   return;
   }
   else
   {
   turnleft();
   turnleft();
   }
}


