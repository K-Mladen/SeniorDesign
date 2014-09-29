#include <CriticalPath.h>
#include <DEFINES.h>

#include <DEFINES-TEST.h>


//Tester program for CriticalPath.h written by Mladen Kojic.
// The advantage this version has is that it will show only the critical path. This will probably become part of the main control loop.
// DATE: 29 SEPTEMBER 2014  ALGORITHM DESIGN BY: MLADEN KOJIC  CODE BY: MLADEN KOJIC

void setup(){
  int it = 0;

  Serial.begin(9600);
}
void loop(){
  crPath path;
  int it;
  int list[] = TESTCASE;
  Serial.println("Begin");
  for (it = 0; list[it]!=-1; it++){
    path.setNextStep(list[it]);
  }
  Serial.print("Critical Path: ");
  for(it = 0; path.getNextStep(it)!=0; it++){
    Serial.print(path.getNextStep(it));
    Serial.print(" ");
  }
  Serial.print("Total Steps = ");
  Serial.println(it);
  Serial.println("done--waiting");
  while(1){
    delay(1000);
  }
}
