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
  pinMode(LED_Done,OUTPUT);
  
  Serial.print("Beginning calibration");
  RoboCtl torro;
 
  //torro.setup();  
  
  Serial.print("Starting Course");
  while(1){
    Serial.print("Act");
    torro.setCourse();
    Serial.println("ion");
  };
  Serial.print("Toggle");
  torro.toggleMode();
  while(1) {
   torro.setCourse();
  } 
}

void loop(){
  //RoboCtl torro;
//torro.setCourse();
  
}


