#include "DEFINES.H"
#include "DEFINES-TEST.H"
#include "Comms.h"
#include "Arduino.h"

Comms::Comms(){
	Comms::setup();
}
Comms::~Comms(){}

void Comms::setup(){
	Serial1.begin(DATARATE);
	digitalWrite(CAMERA_PULSE,HIGH);
}

void Comms::snap(int cell_num){
  digitalWrite(CAMERA_PULSE,LOW);
  digitalWrite(CAMERA_PULSE,HIGH);
  Serial1.println(cell_num);
  while(digitalRead(CAMERA_RESPONSE)){}
  
  return;
}