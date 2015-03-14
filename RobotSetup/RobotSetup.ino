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
  int it;
  
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
  pinMode(CAMERA_PULSE,OUTPUT);
  pinMode(BUTTON,INPUT_PULLUP);
  pinMode(SIZE6, INPUT);
  pinMode(SIZE7, INPUT);
  
  
  Serial.print("Beginning calibration");
  RoboCtl torro;
  
  digitalWrite(LED_Done,HIGH);
  
  //Serial.println(" - - Starting Course");
  while(torro.getMode() != DONE){

    torro.nextAction();
//    for(it = 0; it <50; it++){
//      Serial.print(String(torro.getNextStep(it)));
//      Serial.print(", ");
//    }
//    Serial.println(";");
  } 
  torro.stop();
}

void loop(){
  //RoboCtl tor ro;
//torro.setCourse();
  
}


