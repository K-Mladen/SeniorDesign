#include <QTRSensors.h>
#include <LiquidCrystal.h>
#include <CriticalPath.h>
#include <DEFINES-TEST.h>
#include <DEFINES.h>
#include <Driver.h>
#include <RoboCtl.h>
#include <RoboState.h>


//RoboCtl torro;

void setup(){
   
  Serial.begin(9600);
  
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
  
  RoboCtl torro;
 
  //torro.setup();  
  
  while(!torro.setCourse()){
  
  };
}

void loop(){
  //RoboCtl torro;
//torro.setCourse();
  
}


