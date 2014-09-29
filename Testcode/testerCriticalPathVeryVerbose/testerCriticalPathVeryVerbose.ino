#include <CriticalPath.h>
#include <DEFINES.h>
#include <DEFINES-TEST.h>

//Tester program for CriticalPath.h written by Mladen Kojic.
// The advantage this version has is that it will show the intermediate steps of the algorithm as the path is calculated, but it is very wordy.
// DATE: 29 SEPTEMBER 2014  ALGORITHM DESIGN BY: MLADEN KOJIC  CODE BY: MLADEN KOJIC

void setup(){
  int it = 0;

  Serial.begin(9600);
}
void loop(){
  crPath path;
  int it,it1;
  int list[] = TESTCASE;
  Serial.println("Begin");
  for (it = 0; list[it]!=-1; it++){
    Serial.println(it);
    path.setNextStep(list[it]);
    Serial.print("Current Path: ");
    for(it1 = 0; it1 <= it; it1++){
      Serial.print(path.getNextStep(it1));
      Serial.print(" ");
    }
    Serial.println("end");
  }
  Serial.print("it = ");
  Serial.println(it);
  Serial.println("done--waiting");
  while(1){
    delay(1000);
  }
}
